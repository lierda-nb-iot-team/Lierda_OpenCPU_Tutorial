import os
from copy import copy
from SCons.Script import *
from EnvironmentUtils import NeulBuildConfig, NeulTargetConfig
from common_tools import get_all_subdirectories
import VersionInfo
from DoxyOptions import *
from neuldoxygen import generate_doxy_tagfile_attrib



DEFAULT_DOXYOPTIONS_DICT = {'PROJECT_NAME'      : '"NB-IoT Software Reference Manual"',
                            'PROJECT_BRIEF'     : '"Developement Kit, Protocol Stack, Drivers and OS Software References"',
                            'HAVE_DOT'          : 'YES',
                            'CALL_GRAPH'        : 'YES',
                            'CALLER_GRAPH'      : 'YES'
                           }


class DoxyDoc:
    def __init__(self, name, env, workingdir=None):
        self.name = name
        self.env = env
        self.base_path = Dir('#').abspath
        
        # workingdir the directory in which doxygen is executed.
        if workingdir is None:
            self.workingdir = self.base_path
        else:
            self.workingdir = workingdir
 
        self.doxy_files = set()     # Contains input src files to use 
        self.doxy_paths = set()     # Contains input src paths to use
        self.tagfiles = []          # Contains tagfiles to be included

        self.doxy_files_unfiltered = set()      # Contains input src files to use that do not get passed through any white/black lists
        self.doxy_paths_unfiltered = set()      # Contains input src files to use that do not get passed through any white/black lists

        #All component modules output docs, e.g. its own html files are stored near where the main application html files will be.
        #non nbiot app builds needs to include the os type in the output folder path definitions. 
        #self.modules_outpath = os.path.join(NeulTargetConfig.get_build_dir(env), 'app', NeulTargetConfig.get_application(env), 'components')
        os_based_output_path = os.path.join(NeulTargetConfig.get_build_dir(env), NeulTargetConfig.get_build_os(env))
        self.modules_outpath = os.path.join(os_based_output_path, 'components')
        self.env['DOXY_MODULES_OUTPATH'] = self.modules_outpath

        # Building the main doc in the src/sconscript requires different cfg to sub-modules
        if self.name == 'app':
            self.is_component = False
            self.name = NeulTargetConfig.get_application(env)  #Change name to the actual application name

            # Set output path for 'app' which is the one running is the src/sconscript to be depandant on the os type
            # instead of self.output_path = Dir(os.path.join('.', 'app', self.name))
            self.output_path = Dir(os_based_output_path)
            self.html_output_path = self.output_path
            self.dox_path = Dir(os.path.join('.','app', self.name,'dox'))
        else:
            self.is_component = True
            self.output_path = Dir('.')
            self.html_output_path = Dir(os.path.join(self.modules_outpath, self.name))
            self.dox_path = Dir(os.path.join('.','dox'))


        self.tagfilename = self.env.File(self.name + '.doxtag')
        self.doxyfilename = self.name + "_main.doxyfile"
        self.doc_index_path = os.path.join(self.html_output_path.abspath, 'html')

        self.building_tagfile = False
        self.build_doxtmpl_files = True

        self.doxytarget = os.path.join(self.doc_index_path, 'index.html')

        self.options_common = None
        self.init_options_config()

    def copy(self):
        # Copy this object, typically used so that multiple doxygen builder calls can be done for the same input src set.
        # Need to also copy the doxygen options object stored so that it can be configured independantly for each build. 
        copy_obj =copy(self)
        copy_obj.options_common = self.options_common.copy()
        return copy_obj

    def add_files(self, files):
        self.doxy_files.update(files)

    def add_paths(self, paths):
        self.doxy_paths.update(paths)

    def add_files_nofilter(self, files):
        self.doxy_files_unfiltered.update(files)

    def add_paths_nofilter(self, paths):
        self.doxy_paths_unfiltered.update(paths)

    def add_tagfiles(self, tagfiles):
        self.tagfiles.extend(tagfiles)

    def _doxy_input_filter_white(self, s_input):
        whitelist_paths = set()
        for d in [ os.path.join(self.base_path, di) for di in NeulBuildConfig.get_only_document_paths()]:
            whitelist_paths.add(d)
            whitelist_paths.update(get_all_subdirectories(d))

        input_set = s_input
        inc_set = input_set & whitelist_paths

        #excluded set will in also include any files that where in s_input so go through and check each one.
        excl_set = input_set - whitelist_paths
        w_ext = None
        if NeulBuildConfig.get_only_document_extensions():
            w_ext = [os.path.splitext(ext)[1] for ext in NeulBuildConfig.get_only_document_extensions()]

        for f in excl_set:
            if os.path.isfile(f):
                d, fn = os.path.split(f)
                n, ext = os.path.splitext(fn)
                if d in whitelist_paths:
                    if not w_ext or ext in w_ext:
                        inc_set.add(f)

        return inc_set

    def init_options_config(self, cfg_env=None):
        pnumber = "%s" % VersionInfo.read_string("VERSION_STRING")

        self.options_common = DoxyOptions(env=cfg_env, proj_num=pnumber, override_dict=NeulBuildConfig.get_doxygen_additional_tags(), default_dict=DEFAULT_DOXYOPTIONS_DICT)

        self.options_common.add_option('PREDEFINED', self.env['CPPDEFINES'])
        self.options_common.set_output(self.html_output_path.path)

        if NeulBuildConfig.doxygen_quiet_mode: self.options_common.add_option('QUIET', 'YES')

        # Turn off by default the inclusion of external modules/files found in tagfiles from getting
        # listed with all of the current components modules/files etc...
        self.options_common.add_option('EXTERNAL_GROUPS', 'NO')
        self.options_common.add_option('EXTERNAL_PAGES', 'NO')


    def configure_options(self, input_src=None, module_title=None, allexternals=False):
        self.options_common.add_input(input_src)
        self.options_common.set_proj_brief(module_title)
        if allexternals: self.options_common.add_option('ALLEXTERNALS', 'YES')

        if self.env['DOXYGEN_INCLUDE_TAGFILES'] is True and self.building_tagfile is False:
            input_tagfiles_src = generate_doxy_tagfile_attrib(self.tagfiles, self.modules_outpath, self.doc_index_path, ignore_module = self.name)
            self.options_common.add_input_tagfile_entries(input_tagfiles_src)

        # Get all the folders in the include path which are subdirectories of 'src'
        include_paths_for_doxygen = ['%s' % os.path.relpath(s, start=self.base_path) for s in self.env['CPPPATH'] if os.path.exists(s)]
        self.options_common.add_include_paths(include_paths_for_doxygen)

        warnlog_filename = self.doxyfilename + '.warn.log'
        self.options_common.add_option('WARN_LOGFILE', os.path.join(self.output_path.path, warnlog_filename))

    def config_tagfile_only(self):
            self.doxyfilename = self.name + "_component_tag.doxyfile"
            self.building_tagfile = True
            self.doxytarget = self.tagfilename.abspath

            tagfilename = os.path.relpath(self.tagfilename.abspath, self.workingdir)
            self.options_common.set_output_tagfile(tagfilename, tagfile_only=True)

    ## Configure and run the doxygen builder to build a tagfile for this module.
    def build_tag(self, apply_whitelist=False, apply_blacklist=False, doxyfile_template_file=None):
        self._prebuild()

        # Copy object and the doxygen options dictionary so that it can confifured to build for tagfiles. 
        tag_doc = self.copy()
        tag_doc.config_tagfile_only()

        return tag_doc._build(apply_whitelist, apply_blacklist, doxyfile_template_file)

    def build_html(self, apply_whitelist=False, apply_blacklist=False, doxyfile_template_file=None):
        self._prebuild()

        # This current doc object is being used to config and build the html doc.
        doxyfile, doxy = self._build(apply_whitelist, apply_blacklist, doxyfile_template_file)

        # For html doc building the target given to the builder is the index file that is generated
        # associate the output html path with the index file target for Cleaning purposes.
        self.env.Clean(doxy, self.doc_index_path)
        return doxyfile, doxy

    def _prebuild(self):
        # For all doxygen type builds we need to call only once the builder to convert any additional module
        # doc template files to actual doc files to include in the doxyfile. 
        # TODO: This needs to move to a better place where all doxy content/formatting code is done...maybe 
        # a separate class to keep framework and content separate...
        if self.build_doxtmpl_files:

            doxy_tmpl_env = self.env.Clone()
            # Template Doc builds need the final list of tagfiles that is only available after scons has run through the config phase.
            # Copy the list ref for DOXYGEN_TAGFILES into this environment so that it is available when building the config file.
            if not self.building_tagfile:
                doxy_tmpl_env['DOXY_TAGFILES_SRC'] = self.env['DOXYGEN_TAGFILES']

            doxy_tmpl_env['DOXY_MODULE_DOC_INDEX_PATH'] = self.doc_index_path
            doxy_tmpl_env['DOXY_MODULE_NAME'] = self.name

            srclist =  self.dox_path.srcnode().glob('*.doxtmpl')
            self.module_doc_pages = doxy_tmpl_env.DoxygenCreatePage(source=srclist)
            doxy_tmpl_env.Depends(self.module_doc_pages, doxy_tmpl_env['DOXY_TAGFILES_SRC'])

            self.module_doc_pages = [f.abspath for f in self.module_doc_pages]
            self.build_doxtmpl_files = False


    def _build(self, apply_whitelist=False, apply_blacklist=False, doxyfile_template_file=None):
        # Source list used by the target
        src_input = self.doxy_files | self.doxy_paths

        src_input_unfiltered = self.doxy_files_unfiltered | self.doxy_paths_unfiltered

        if apply_whitelist is True:
            #Apply paths whitelist
            #This is to allow backwards compatibility with the 'only_document_paths' variable that a few target builds use.  This will be removed at somepoint
            #as a list of modules to be doxygenated should be the input of each target.
            src_input = self._doxy_input_filter_white(src_input)

        # TODO: Implement blacklist filter, may need to search within paths, or could use in combination
        # with doxygens filtering abilities 
        #if apply_blacklist is True:
            #Apply a blacklist filter 
            #src_input = DoxyInputFilterBlack(src_input, blacklist_filter)

        # Src input to doxygen is list of filtered files/paths and those to be added unfiltered. 
        src_input = src_input | src_input_unfiltered

        doxy_file_env = self.env.Clone()
        if not self.building_tagfile:
            # Doc builds need the final list of tagfiles that is only available after scons has run through the config phase.
            # Copy the list ref for DOXYGEN_TAGFILES into this environment so that it is available when building the config file.
            doxy_file_env['DOXY_TAGFILES_SRC'] = self.env['DOXYGEN_TAGFILES']

        doxy_file_env['DOXY_MODULE_DOC_INDEX_PATH'] = self.doc_index_path
        doxy_file_env['DOXY_MODULE_NAME'] = self.name

        src_input.update(self.module_doc_pages)

        self.options_common.add_to_env(doxy_file_env)

        src_input_rel = []
        for s in src_input:
            path = str(s)
            if os.path.isabs(path):
                path = os.path.relpath(path, self.workingdir)
            src_input_rel.append(path)
        self.configure_options(input_src=sorted(src_input_rel))

        if doxyfile_template_file:
            doxyfile_template_path = doxyfile_template_file
        else:
            doxyfile_template_path = os.path.join(self.base_path, 'doxygen','doxyfile.template')

        # Create doxygen config file using template for defaults.
        doxyfile = doxy_file_env.DoxygenCfgFile(target=os.path.join (self.output_path.abspath, self.doxyfilename), source=doxyfile_template_path)

        doxy_file_env.Depends(doxyfile, self.module_doc_pages)  #Explicity depend on doc files being built so they exist before the cfgfile is generated.

        if self.is_component is True:
            # Possible bug in doxygen not creating components or tagfiles output dir? so create them first here...
            #if not os.path.exists(self.modules_outpath): os.makedirs(self.modules_outpath)
            if not os.path.exists(self.html_output_path.abspath):  Execute(Mkdir(self.html_output_path.abspath))


        # Call the doxygen builder, it takes the config file from which it scans for sources and targets at config time.
        doxy = self.env.Doxygen(target=self.doxytarget, source=doxyfile)

        doxyfilelog = doxyfile + '.log'
        doxyfilelogwarn = doxyfile + '.warn.log'
        self.env.Clean(doxy, doxyfilelog)
        self.env.Clean(doxy, doxyfilelogwarn)

        return doxyfile, doxy


