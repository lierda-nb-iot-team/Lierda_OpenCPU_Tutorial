#===============================================================================
# @brief    Scons make file
# Copyright (c) 2016-2018 Huawei Technologies Co. Ltd
#===============================================================================

import os
import re
import itertools
from SCons.Script import *
from EnvironmentUtils import *
from common_tools import *
from pprint import pprint
from DoxyDoc import *

# The top level XML generation needs an include path which has the build_scons
# private directory for each module which uses an FSM, so remember that here as
# we don't have a good way to pass that information back to the top level. The
# XML generation code reaches in and reads this when it wants it.
fsm_inc_dirs = []

class MembersFromInit(object):
    def __init__(self, **args):
        # Set the keyword arguments as attributes on this instance.
        # That means we can instantiate the class like MembersFromInit(thing=2,
        # thang="jjj") and end up with self.thing=2 and self.thang="jjj"
        for a in args:
            setattr(self, a, args[a])

class TestAndLib(MembersFromInit):
    pass

class Test(MembersFromInit):
    pass

# It is assumed this is instantiated within a module SConscript,
# so I'm taking it that all paths are relative to the module the
# instance is created for.
class Module:
    def __init__(self, name, env, components = None, sources = None, public_inc_dirs = None, private_inc_dirs = None, additional_release_files = None, cpp_defines = None):
        self.name = name
        self.env = self.oenv = env  #self.env is overwritten later in the module, self.oenv should always contain the original src/sconscript env
        self.components = [] if components is None else components
        self.module_test_opt_libs = []
        self.module_test_libs_to_link = []
        self.subproducts = []
        self.doxy_files = []                ## Contains individual files to process for this module and its sub-modules.
        self.doxy_paths = []                ## Contains paths to source files to process for this module and its sub-modules.
        self.doxy_tagfiles = []             ## List of generated doxygen tagfiles
        self.doxy_html_cfgfiles_out = []    ## Doxygen config file targets for html doc builds
        self.doxy_html_docs_out = []        ## Doxygen html doc targets
        self.doxy_tag_cfgfiles_out = []     ## Doxygen config file targets for tagfile builds
        self.doxy_tag_docs_out = []         ## Doxygen tagfile targets


        # Source public and private to keep implemented behaviour
        self.source_files  = Flatten(sources) if sources is not None else sources

        if public_inc_dirs is None:
            self.public_inc_dirs = [os.path.join(Dir('.').srcnode().abspath, 'public')]
        else:
            self.public_inc_dirs = public_inc_dirs

        env.Append(CPPPATH = self.public_inc_dirs)

        if private_inc_dirs is None:
            self.private_inc_dirs = [os.path.join(Dir('.').srcnode().abspath, 'private')]
        else:
            self.private_inc_dirs = private_inc_dirs

        self.additional_release_files  = [] if additional_release_files is None else additional_release_files
        self.cpp_defines  = [] if cpp_defines is None else cpp_defines


    def __iadd__(self, other):
        # Will add files/paths and build outputs from another module object to this module
        self.doxy_files.extend(other.doxy_files)
        self.doxy_paths.extend(other.doxy_paths)
        self.doxy_tagfiles.extend(other.doxy_tagfiles)
        self.doxy_html_cfgfiles_out.extend(other.doxy_html_cfgfiles_out)
        self.doxy_html_docs_out.extend(other.doxy_html_docs_out)
        self.doxy_tag_cfgfiles_out.extend(other.doxy_tag_cfgfiles_out)
        self.doxy_tag_docs_out.extend(other.doxy_tag_docs_out)

        return self

    def add_module_test_optional_lib(self, module):
        """
        Module tests sometimes need to be linked against another library,
        for instance, RRC needs the ASN library to be module-tested.
        We can't get it in with how the current build system conventions,
        but we can use this method to specify what libraries to link against,
        when we compile for module tests.
        """
        self.module_test_opt_libs.append(module)

    ## Allows individual files to be added as a private file for doxygen builds
    # for modules that do not follow the private/public path structure.
    def additional_module_doxy_private_files(self, f):
        if not NeulBuildConfig.doxy_api_only: self._additional_module_doxy_files(f)

    ## Allows individual files to be added as a public file for doxygen builds
    # for modules that do not follow the private/public path structure.
    def additional_module_doxy_public_files(self, f):
        self._additional_module_doxy_files(f)

    ## Adds a file or list/set of files to the list of input files for doxygen builds.  
    def _additional_module_doxy_files(self, f):
        # Only add files to doxy file lists if module is to be included.
        if NeulBuildConfig.modules is None or self.name in NeulBuildConfig.modules:
            try:
                _ = f + ''      # basically tests to determine if files_or_dirs is a list(iterable) or string only.
                self.doxy_files.append(f)
            except:
                self.doxy_files.extend(f)

    # helper functions to build a library and export the include paths
    def build(self, env):
        return self._build()

    def _build(self):

        # Get the build artifacts of all submodules.
        for component in self.components:
            if NeulTargetConfig.get_build_type(self.env) == BuildType.DOXYGEN:
                component_results = SConscript(os.path.join(component, 'SConscript'), {'env': self.env })
                self += component_results
            else:
                built_lib = SConscript(os.path.join(component, 'SConscript'), {'env': self.env })
                self.subproducts.append( built_lib )

            # Special case: If this module wants to link against a subproduct for module tests,
            # add the build lib to a list. We do this for RRC and ASN library.
            if component in self.module_test_opt_libs:
                # Note CXXTEST product is a TestAndLib object, so extract just the libs.
                if NeulTargetConfig.get_build_type(self.env) == BuildType.CXXTEST_ALL:
                    self.module_test_libs_to_link.append(built_lib.libs)
                elif NeulTargetConfig.get_build_type(self.env) is not BuildType.DOXYGEN:
                    self.module_test_libs_to_link.append(built_lib)

                if 'LIBS' in self.env:
                    self.module_test_libs_to_link.append(self.env['LIBS'])

        self.robot_kwrd_lib = []
        if os.path.exists(os.path.join('.', 'test', 'robot')):
            self.robot_kwrd_lib = Glob(os.path.join('.', 'test', 'robot', '*.py'))

        self.robot_kwrd_lib.append(NeulBuildConfig.ROBOT_KEYWORDS_LIB_PATH)
        if self.source_files is None:
            self.source_files = Glob(os.path.join('private', '*.c'))

        # For Doxygen builds we need to keep env as the env from src/sconscript, this allows us to
        # build doxy config files with data generated at the end of the scons config phase
        if NeulTargetConfig.get_build_type(self.env) is not BuildType.DOXYGEN: 
            fsm_sources = self.autogen_fsms()

            # For fsm generated code to compile, we need to provide access to the private
            # header files so files under build_scons can see them. Similarly, src needs to 
            # see the generated header files under build_scons. If we add 'private' to CPPPATH,
            # it will make it look like the generated FSM files are under the source tree, in 'private'.
            # Of course, we want this to apply only for this module, so we clone the environment
            # to leave the common CPPPATH unaffected
            self.env = self.env.Clone()
            if fsm_sources is not None:
                self.env.Append(CPPPATH = os.path.join(Dir('.').abspath, 'private'))
                fsm_inc_dirs.append(os.path.join(Dir('.').abspath, 'private'))
                for fsm_source in fsm_sources:
                    if fsm_source not in self.source_files:
                        self.source_files.extend([fsm_source])

            # Progagate the "STACKUSAGE_OPTFILES" environment variable up to the parent environment
            # TODO: Find a simpler way to get the autogenerated .opt file paths to the right place
            # Note: This may not be needed now as autogen_fsms() does not use the cloned env where optfile seems to be set in.
            if 'STACKUSAGE_OPTFILES' in self.env:
                for optfile in self.env['STACKUSAGE_OPTFILES']:
                    if optfile not in self.oenv['STACKUSAGE_OPTFILES']:
                        self.oenv.Append(STACKUSAGE_OPTFILES = optfile)

        elif NeulBuildConfig.modules is None or self.name in NeulBuildConfig.modules:
            fsm_sources = self.autogen_fsms()

        if NeulTargetConfig.get_build_type(self.env) == BuildType.ROBOT_TEST:
            self.subproducts.extend( self._build_robot_tests() )
        elif NeulTargetConfig.get_build_type(self.env) == BuildType.ARM or \
             NeulTargetConfig.get_build_type(self.env) == BuildType.ARM_COVERAGE:
            self.subproducts.extend( self.env.Library(target = self.name, source = self.source_files) )
        elif NeulTargetConfig.get_build_type(self.env) == BuildType.CXXTEST:
            self.subproducts.extend( self._build_unit_tests() )
        elif NeulTargetConfig.get_build_type(self.env) == BuildType.LINT:
            if self.source_files != []:
                self.subproducts.extend( self.env.PcLintLob(target = self.name, source = self.source_files) )

        elif NeulTargetConfig.get_build_type(self.env) is BuildType.DOXYGEN:
            # Build this module only if it is included in this build. By default all is built.
            if NeulBuildConfig.modules is None or self.name in NeulBuildConfig.modules:
                for dir in self.public_inc_dirs:
                    if os.path.exists(dir): self.doxy_paths.append(dir)

                # Cmdline option indicating to build with modules public interface only 
                if not NeulBuildConfig.doxy_api_only:
                    for dir in self.private_inc_dirs:
                        if os.path.exists(dir): self.doxy_paths.append(dir)

                    # Add the fsm source path
                    fsm_path = os.path.join(Dir('.').abspath, 'private')
                    if os.path.exists(fsm_path): self.doxy_paths.append(fsm_path)

                #For now just add the dox path to the list to include any .md files
                #Later if templates are used files generated from the template will need to be added individually
                #to self.doxy_files
                dox_path = os.path.join(Dir('.').srcnode().abspath, 'dox')
                if os.path.exists(dox_path): self.doxy_paths.append(dox_path)

                for f in self.additional_release_files:
                    if os.path.exists(str(f)): self.doxy_files.append(str(f))

                # If this module is identified to be built as a separate set of doxygen docs call 
                # the build function. OTherwise all files are passed upwards to the parent module.
                if 'DOXY_COMPONENT' in self.env and self.env['DOXY_COMPONENT'] is self.name:
                    is_doxy_component = True
                else:
                    is_doxy_component = False

                if not NeulBuildConfig.doxy_build_single and is_doxy_component:
                    self._build_component_doxy()

            return self

        elif NeulTargetConfig.get_build_type(self.env) is BuildType.SOURCE_PACKAGE:
            return self

        elif NeulTargetConfig.get_build_type(self.env) == BuildType.CXXTEST_ALL:
            self.subproducts.extend( self._build_cxxtest_all() )

        return self.subproducts

    def autogen_fsms(self):
        fsm_path = os.path.join(Dir('.').srcnode().abspath, 'fsm')
        out_path = os.path.join(Dir('.').abspath, 'private')
        return generate_fsm_sources(self.env, fsm_path, out_path)

    def _build_robot_tests(self):
        test_results = []
        all_headers = []
        self.source_files.extend(Glob(os.path.join('.', 'test', 'robot', 'stubs', '*.c')))
        self.env.Prepend(CPPPATH = os.path.join(Dir('.').srcnode().abspath, 'test', 'robot', 'stubs'))
        self.env.Append(CPPPATH = os.path.join(Dir('.').srcnode().abspath, 'private'))
        self.robot_tests = Glob(os.path.join('.', 'test', 'robot', '*.txt'))
        tests_to_run = []

        # Run only matching tests, if specified from command line
        if len(NeulBuildConfig.get_selected_tests()) > 0:
            for i in self.robot_tests:
                for s in NeulBuildConfig.get_selected_tests():
                    if s in str(i):
                        tests_to_run.append(i)
        else:
            tests_to_run = self.robot_tests

        if len(tests_to_run) >0 :
            # Remove duplicate entries
            self.source_files = sorted(set(self.source_files))
            sos = [ self.env.SharedObject(File(src)) for src in self.source_files ]
            self.lib = self.env.SharedLibrary(self.name, sos, LIBS = self.module_test_libs_to_link)
            test_results = self.env.run_robot_tests(self.name, self.lib, self.robot_kwrd_lib, self.source_files, tests_to_run)

        return test_results

    def _build_unit_tests(self):
        unit_tests = []
        self.cxxtests = Glob(os.path.join('.', 'test', 'cxxtest', '*.h'))
        self.source_files.extend(Glob(os.path.join('.', 'test', 'cxxtest', 'stubs', '*.c')))
        for dirname in self.private_inc_dirs:
            self.env.Prepend(CPPPATH = dirname)
        self.env.Prepend(CPPPATH = os.path.join(Dir('.').srcnode().abspath, 'test', 'cxxtest', 'stubs'))

        if self.cxxtests:
            self.lib = self.env.Library(self.name, self.source_files)
            for t in self.cxxtests:
                # The build environment is different for each test, because
                # each one may have different LINKFLAGS depending on what
                # is declared as __wrap in the _test.h file.
                test_env = self.env.Clone()

                if 'LIBS' in self.env:
                    self.module_test_libs_to_link.append(self.env['LIBS'])

                p = test_env.Cxxtest(t, [self.lib], [self.lib] + self.module_test_libs_to_link)
                unit_tests.extend(p)

        # Return a list of all executables, one for each unit test
        return unit_tests

    def _build_cxxtest_all(self):
        """
        These are Cxxtests which link against a library composed of the whole system.
        """
        tests = Glob(os.path.join('.', 'test', 'cxxtest_all', '*.h'))
        self.env.Prepend(CPPPATH = os.path.join(Dir('.').srcnode().abspath, 'private'))

        # Allow Helper functions for tests from all layers
        self.source_files.extend(Glob(os.path.join('.', 'test', 'cxxtest_all', 'helper', '*.c')))

        test_list = []
        lib = self.env.Library(self.name, self.source_files)
        for t in tests:
            # The build environment is different for each test, because
            # each one may have different LINKFLAGS depending on what
            # is declared as __wrap in the _test.h file.
            test_env = self.env.Clone()

            # Add the paths to the helper interface files
            for helper_path in test_env['HELPERPATH']:
                test_env.Prepend(CPPPATH = test_env['HELPERPATH'])

            test_list.append(Test(test=t, env=test_env))

        ret = TestAndLib(libs = lib, tests= test_list)
        return [ret]

    def _build_component_doxy(self):

        # Calls to this function means that this module is going to be built as a standalone doxygen module.
        # Its tagfile will be built so that it can be included elsewhere like the top level main doc.

        # Create and init a doxydoc object with the files and paths tio be used for this module.
        doxydoc = DoxyDoc(self.name,self.oenv)
        doxydoc.add_files(self.doxy_files)
        doxydoc.add_paths(self.doxy_paths)
        doxydoc.add_tagfiles(self.oenv['DOXYGEN_TAGFILES'])

        title = 'Component ' + self.name
        doxydoc.configure_options(module_title=title, allexternals=True)

        # If Module is being called to generate a tagfile then set that up otherwise html doc is generated. 
        if self.env['DOXYGEN_GENERATE_TAGFILES'] is True:
            # Module being called to generate tagfile only
            doxyfile_tag, doxy_tag = doxydoc.build_tag()
            self.doxy_tag_cfgfiles_out.append(doxyfile_tag)
            self.doxy_tag_docs_out.extend(doxy_tag)

        # Call function to configure building of html doc.
        doxyfile_html, doxy_html = doxydoc.build_html()

        self.doxy_html_cfgfiles_out.append(doxyfile_html)
        self.doxy_html_docs_out.extend(doxy_html)


        # Module building its doc, so clear files/paths.  Parent module will include this modules output tagfile and/or html output.
        self.doxy_files = []
        self.doxy_paths = []

        return

    def get_sources(self):
        return self.source_files

    def get_public_inc_dirs(self):
        return self.public_inc_dirs

    def get_private_inc_dirs(self):
        return self.private_inc_dirs

    def get_additional_release_files(self):
        return self.additional_release_files

    def get_name(self):
        return self.name

    def get_additional_files(self):
        return self.aditional_files

    def add_module(self, sm):
        self.source_files.extend(sm.get_sources())
        self.public_inc_dirs.extend(sm.get_public_inc_dirs())
        self.private_inc_dirs.extend(sm.get_private_inc_dirs())
        self.additional_release_files.extend(sm.get_additional_release_files())

    def add_public_inc_dirs(self, public_inc_dirs_list):
        self.public_inc_dirs.extend(public_inc_dirs_list)

    def add_private_inc_dirs(self, private_inc_dirs_list):
        self.private_inc_dirs.extend(private_inc_dirs_list)

    def add_cpp_defines(self, cpp_defines_list):
        self.cpp_defines.extend(cpp_defines_list)

    def get_cpp_defines(self):
        return self.cpp_defines
