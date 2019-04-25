#===============================================================================
# @brief    Scons make file
# Copyright (c) 2016 NEUL LIMITED
#===============================================================================

import os
#import re
from string import Template
import SCons.Builder
from SCons.Script import *
#import sys
import subprocess
from DoxyConfig import *


FILLED_BY_SCONS_HEADER = ['#---------------------------------------------------------------------------',
                          '# Filled by Build Scons',
                          '#---------------------------------------------------------------------------']

def create_doxygen_file(env, target, source, doxy_opts_dict):
    if os.path.dirname(str(target)) != '':
        if not os.path.exists(os.path.dirname(str(target))):
            os.makedirs(os.path.dirname(str(target)))

    with open( str(target) , 'w') as doxy_cfg_file:

        # Copy the template file
        with open( str(source), "r" ) as doxy_template_file:
            doxy_cfg_file.write(doxy_template_file.read())

        # Add the Specific build system information
        for line in FILLED_BY_SCONS_HEADER:
            doxy_cfg_file.write(line +'\n')

        # Add any additional tags given in the target
        for key, val in doxy_opts_dict.iteritems():
            doxy_cfg_file.write('\n')
            if key in ['INPUT', 'INCLUDE_PATH', 'TAGFILES']:
                doxy_cfg_file.write(" \\\n".join(['%s = ' % key] + ['"%s"' % v for v in val]) + '\n')
            elif key in ['PREDEFINED']:
                predefines_for_doxygen = []
                for cppdef_element in val:
                    # The CPPDEFINES cones as a list which could contain either strings or dictionaries with
                    # the keys being the define and the value its value

                    if type(cppdef_element) is dict:
                        predefines_for_doxygen.extend(['%s=%s' % (k, ('"' + v[2:-2] + '"') if v.startswith('\\"') and v.endswith('\\"') else v) for k,v in cppdef_element.items()])
                    elif type(cppdef_element) is tuple:
                        k, v = cppdef_element[0], cppdef_element[1]
                        predefines_for_doxygen.extend(['%s=%s' % (k, ('"' + v[2:-2] + '"') if v.startswith('\\"') and v.endswith('\\"') else v)])
                    else:
                        predefines_for_doxygen.append('%s' % cppdef_element)
                doxy_cfg_file.write(" \\\n".join(['%s = ' % key] + predefines_for_doxygen) + '\n')
            else:
                doxy_cfg_file.write("%s = %s\n" % (key,val))

        return 0

    return 1

## Update the doxygen options dictionary with additional parameters.
# This is done at build time for options that need data after scons has completed
# the config phase. E.g list of tagfiles available in this build 
def update_doxy_options_dict(env, doxy_opts_dict):
    #Only run if something to add to cfg files (curently only TAGFILES need to be added in this way)
    if 'DOXY_TAGFILES_SRC' in env and 'DOXYGEN_TAGFILES' in env:
        tagfiles = set(env['DOXYGEN_TAGFILES'])
        tagfiles.update(env['DOXY_TAGFILES_SRC'])

        links = generate_doxy_tagfile_attrib(sorted(tagfiles), env['DOXY_MODULES_OUTPATH'], env['DOXY_MODULE_DOC_INDEX_PATH'], ignore_module=env['DOXY_MODULE_NAME'])
        doxy_opts_dict['TAGFILES'] = links

## Creates a doxygen config file based on a template and with added parameters stored
# in a dictionary in the construction env variable DOXY_OPTIONS 
def create_doxygen_file_from_env(env, target, source):
    out_file = target[0].path
    in_file = source[0].path
    doxy_opts_dict=env['DOXY_OPTIONS']
    update_doxy_options_dict(env, doxy_opts_dict)

    return create_doxygen_file(env, out_file, in_file, doxy_opts_dict)

## Takes a list of tagfiles for modules and creates the string with the relative link locations to the 
# modules html files.  It is used for the Doxygen option TAGFILES
# @param src_tagfiles    Tagfiles
# @param component_path  Path to where the modules have their html output
# @param docindex_path   Path of the html dir of where the current doc being built which is to include these tagfiles
# @param ignore_module   A module in the tagfile list to ignore, used to remove the same modules tagfile being included by itself.
def generate_doxy_tagfile_attrib(src_tagfiles, component_path, docindex_path, ignore_module=None):
    tagfiles_attrib = []
    for tagfile in sorted(src_tagfiles):
        tag_filename = os.path.split(tagfile)
        tagfile_component = os.path.splitext(tag_filename[1])
        if not ignore_module or tagfile_component[0] != ignore_module:
            relpath = os.path.relpath(os.path.join(component_path, tagfile_component[0], 'html'),docindex_path)
            relpath = str(relpath).replace('\\', '/') #Doxygen has a problem with the slashes for the actual(relative) html file locations, this swap seems to work.

            tagfile_rel = os.path.relpath(tagfile, start=os.path.join(Dir('#').abspath) ) 
            tagfile_input_str = tagfile_rel + " = " + relpath
            tagfiles_attrib.append(tagfile_input_str)

    return tagfiles_attrib

## Takes a list of tagfiles for modules and creates the string with the relative link locations to the 
# modules html files index file.  It is used to insert links to modules in documention
# @param src_tagfiles    Tagfiles
# @param component_path  Path to where the modules have their html output
# @param docindex_path   Path of the html dir of where the current doc being built which is to include these tagfiles
# @param ignore_module   A module in the tagfile list to ignore, used to remove links to itself.
def generate_doxy_md_tagfile_links(src_tagfiles, component_path, docindex_path, ignore_module=None):
    links = []
    for tagfile in src_tagfiles:
        tag_filename = os.path.split(tagfile)
        tagfile_component = os.path.splitext(tag_filename[1])
        if not ignore_module or tagfile_component[0] != ignore_module:
            relpath = os.path.relpath(os.path.join(component_path, tagfile_component[0], 'html', 'index.html'), docindex_path)

            #Add Component meta data for linking on doc pages
            #TODO: Once more formatting and content work is done this autogen markdown text should be in a spearate class dealing with autogen doxy output
            taglink = '[Component ' +  tagfile_component[0] + '](' + relpath +')'
            links.append(taglink)

    if len(links) == 0: links = ['None']

    return links

## Create a doxygen template dictionary.
def doxy_setup_template_dict(component_links=None):
    template_dict = {}
    if component_links: template_dict['components'] ='\n\n'.join(component_links)
    return template_dict


## Create a file from a template file containing tags that are filled in from tag definitions
# in the provided dictionary  
def doxy_page_from_template(env, target, source, tdict):
    retcode = 1

    if not os.path.exists(os.path.dirname(str(target))):
        os.makedirs(os.path.dirname(str(target)))

    with open( str(target) , 'w' ) as mainpage:
        # Copy the template file
        with open( str(source), 'r' ) as template_file:
            src = Template(template_file.read())
            res = src.substitute(tdict)
            mainpage.write(res)
            retcode = 0

    return target


## Create a doxgen document file based on its template file.
# A template dictionary contains keys containing strings to insert where the relevant key tag
# is found within the template file 
def create_dox_pages(env, target, source):
    retcode = 1

    if 'DOXY_TAGFILES_SRC' in env and 'DOXYGEN_TAGFILES' in env:
        tagfiles = set(env['DOXYGEN_TAGFILES'])
        tagfiles.update(env['DOXY_TAGFILES_SRC'])

        links = generate_doxy_md_tagfile_links(sorted(tagfiles), env['DOXY_MODULES_OUTPATH'], env['DOXY_MODULE_DOC_INDEX_PATH'], ignore_module=env['DOXY_MODULE_NAME'])
        doxy_tmpl_dict = doxy_setup_template_dict(component_links=links)

        for src, dst in zip(source, target):
            doxy_page_from_template(env, dst, src, doxy_tmpl_dict)

        retcode = 0

    return retcode

## LwIP has its own doxyfile and doxygen has to be called in the LwIP dir.  This action
# changes dir to the right location before calling doxygen
def generate_lwip_doxygen_builder_action(target, source, env):
    # TODO: IOT-11779: Remove this hardcoded path by moving LWIP tools to lwip SConscript 
    lwip_cwd = env.Dir("src/lib/lwip/lwip-2.0.3/doc/doxygen").path
    doxyfile = os.path.relpath(source[0].path, lwip_cwd)
    doxyfilelog = source[0].path + '.log'
    with open(doxyfilelog,"wb") as log:
        subprocess.check_call([env['DOXYGEN_EXE'], doxyfile],
            cwd=lwip_cwd, stdout=log)

## Emitter used for building document pages from templates.
def doxy_docpages_emitter(target, source, env):
    targets = []
    srcdir = Dir('.').srcnode()
    targets = [File(t.get_path(dir=srcdir))  for t in target]

    return targets, source

## Source Scanner that reads in a config file and determines the sources
def DoxySrcScanner(node, env, path):
    doxcfg = DoxyConfig(doxyCfgFile=node.abspath, rootPath=env.Dir("#").path)
    doxcfg.readDox()
    allSrcFiles = doxcfg.getSources()
    allSrcNodes = [env.File(srcfile) for srcfile in allSrcFiles]

    return allSrcNodes

## Source Scanner check function
def IsDoxyfile(node, env):
    return os.path.isfile(node.path)

def generate(env):
    """
    Add builders and construction variables for the Doxygen tool in tools/doxygen
    """
    
    if int(ARGUMENTS.get('VERBOSE', 0)) == 0:
        env["DOXYGEN_LWIP_COMSTR"] = "Running LWIP Doxygen $SOURCE"
        env["DOXYGEN_CFGFILE_COMSTR"] = "Creating Doxygen doxyfile $SOURCE"
        env["DOXYGEN_PAGE_COMSTR"] = "Creating $TARGET doc page from template $SOURCE"
        env["DOXYGEN_COMSTR"] = "Running Doxygen $TARGET from $SOURCE"

    doxygenlwipdoc_builder = SCons.Builder.Builder(
        action= Action(generate_lwip_doxygen_builder_action, "$DOXYGEN_LWIP_COMSTR"),
        src_suffix ='.doxyfile',
    )

    doxygen_cfgfile_builder = SCons.Builder.Builder(
        action= Action(create_doxygen_file_from_env, "$DOXYGEN_CFGFILE_COMSTR"),
        src_suffix ='.doxyfile',
        single_source=True,
    )

    doxygen_create_pages = SCons.Builder.Builder(
        action= Action(create_dox_pages, "$DOXYGEN_PAGE_COMSTR"),
        src_suffix ='.doxtmpl',
        emitter = doxy_docpages_emitter,
    )

    doxy_srcscanner = env.Scanner(
        DoxySrcScanner, "DoxySrcScanner",
        scan_check=IsDoxyfile,
    )

    doxy_action_str = [
        "${DOXYGEN_EXE} ${SOURCE} > ${SOURCE}.log",
    ]

    doxy_builder = SCons.Builder.Builder(
        action=Action(doxy_action_str, "$DOXYGEN_COMSTR"),
        target_factory=env.fs.Entry,
        single_source=True,
        source_scanner=doxy_srcscanner,
    )

    env.Append(BUILDERS={
        'DoxygenCfgFile':    doxygen_cfgfile_builder,
        'DoxygenLwipDoc': doxygenlwipdoc_builder,
        'DoxygenCreatePage' : doxygen_create_pages,
        'Doxygen': doxy_builder,
    })

    env.AppendUnique(
        DOXYGEN_EXE='doxygen.exe',
    )

def exists(env):
    """
    Make sure doxygen exists.
    """
    return env.Detect("doxygen")


