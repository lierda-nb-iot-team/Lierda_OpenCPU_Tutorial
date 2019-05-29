#===============================================================================
# @brief    Scons make file
# Copyright (c) 2016-2018 Huawei Technologies Co. Ltd
#===============================================================================

# BuildType         - build types used per target
# NeulBuildConfig   - global build configuration
# NeulTargetConfig  - per target configuration (scons_targets.py)
# NeulPackageConfig - per package configuration (scons_targets.py)

import re
import time
import datetime
from SCons.Script import *
import VersionInfo

# We've always needed this.
class BuildType:
    ARM = 0
    CXXTEST = 1
    ROBOT_TEST = 2
    DOXYGEN = 3
    LINT = 4
    CXXTEST_ALL = 5
    SOURCE_PACKAGE = 6
    ARM_COVERAGE = 7
    MAX_BUILD_TYPE = 8

# CodeLoader Versons
B150_CODELOADER_VERSION = 0
B180_CODELOADER_VERSION = 2
B200_CODELOADER_VERSION = 3

build_name = [None] * BuildType.MAX_BUILD_TYPE
build_name[BuildType.ARM] = 'arm'
build_name[BuildType.CXXTEST] = 'cxxtest'
build_name[BuildType.ROBOT_TEST] = 'robot_test'
build_name[BuildType.DOXYGEN] = 'doxygen'
build_name[BuildType.LINT] = 'pclint'
build_name[BuildType.SOURCE_PACKAGE] = 'src_package'
build_name[BuildType.CXXTEST_ALL] = 'cxxtest_all'
build_name[BuildType.ARM_COVERAGE] = 'arm_coverage'

# Minimal set of local tools required to build ARM standalone
minimal_tools = [
                  #os.path.join('tools', 'FirmwarePackager', '*'),
                  #os.path.join('tools', 'FirmwarePackager', '*', '*'),
                  os.path.join('tools','SCons','arm_tools.py'),
                  os.path.join('tools','SCons','common_tools.py'),
                  os.path.join('tools','SCons','EnvironmentUtils.py'),
                  os.path.join('tools','SCons','ModuleUtils.py'),
                  os.path.join('tools','SCons','VersionInfo.py'),
                  os.path.join('tools','scripts','elftodu.py'),
                  os.path.join('tools','scripts','mem_stats.py'),
                  os.path.join('tools','neul_yaml.py'),
                  os.path.join('site_scons','site_tools','neuldoxygen','*.py'),
                  os.path.join('site_scons','site_tools','DoxyConfig','*.py'),
                  os.path.join('site_scons','site_tools','FirmwarePackager.py'),
                ]


CORE_RELATIVE_FOLDERS = {
    'security_core':    ['security_core',    'shared', 'shared_as'],
    'protocol_core':    ['protocol_core',    'shared', 'shared_ap'],
    'application_core': ['application_core', 'shared', 'shared_ap', 'shared_as'],
    }


# get the size of a file in bytes from it's path
def fileSize(path):
    file_path = os.path.join(Dir('#').abspath, path)
    if os.path.isfile(file_path):
        stats = os.stat(file_path)
        return stats.st_size
    else:
        return 0

# We can place here any build parameters we need across
# the build framework, such as paths to tools and the likes
class NeulBuildConfig:
    root = os.path.join(Dir('#').abspath)

    CTYPESGEN_PATH = os.path.join(root, 'tools', 'ctypesgen', 'ctypesgen.py')
    CXXTEST_LOC = os.path.join(root, 'tools', 'cxxtest-4.4')
    CXXTESTGEN_PATH = os.path.join(CXXTEST_LOC, 'bin', 'cxxtestgen')
    CXXTEST_ALL_STUBS = os.path.join(root, 'src', 'app', 'nbiot', 'test', 'cxxtest_all', 'stubs')
    FSMGEN_PATH = os.path.join(root, 'tools', 'fsmgen', 'fsmgen.py')
    MESSAGEXML_PATH = os.path.join(root, 'tools', 'MessageXmlGen', 'MessageXmlGen.py')
    MESSAGEXML_CONFIG = os.path.join(root, 'tools', 'MessageXmlGen', 'MessageXmlGen.cfg')
    MESSAGE_RULES = os.path.join(root, 'tools', 'MessageXmlGen', 'MessageRules.xml')
    XML_PATH = os.path.join(root, 'tools', 'MessageXmlGen', 'xml.exe')
    XSD_PATH = os.path.join(root, 'tools', 'MessageXmlGen', 'Messages.xsd')
    STACKUSAGE_PATH = os.path.join(root, 'tools', 'StackUsage', 'StackUsage.py')
    DRMEMORY = ""

    # Common to the Robot and embedded builds
    COMMON_CCFLAGS = [
        '-std=gnu99',
        '-Wall',
        #'-Werror',
        '-Wextra',

        '-Wmissing-declarations',
        '-Winit-self',
        '-Wmissing-include-dirs',
        '-Wtrampolines',
        '-Wundef',
        '-Wpointer-arith',
        '-Wlogical-op',
        '-Wstrict-prototypes',
        '-Wmissing-prototypes',
        '-Wjump-misses-init',

        # We disable this warning AFTER we've enabled all others,
        '-Wno-missing-include-dirs',

        '-fno-strict-aliasing',
    ]

    # Common to all builds.
    COMMON_CPPDEFINES = [
        'TARGET_PROCESSOR_FAMILY_BOUDICA',

        # Used by COAP
        'WITH_LWIP'
    ]

    ROBOT_KEYWORDS_LIB_PATH = os.path.join(root, 'src', 'app', 'nbiot', 'test', 'robot', 'StackKeywords.py')
    all_public_headers = []
    selected_tests = []

    if "TIMESTAMP" in ARGUMENTS:
        build_timestamp = int(ARGUMENTS["TIMESTAMP"])
    else:
        build_timestamp = int(time.time())

    build_xml = False

    @staticmethod
    def add_public_headers(headers):
        NeulBuildConfig.all_public_headers.extend(headers)

    @staticmethod
    def set_selected_tests(module_names_list):
        NeulBuildConfig.selected_tests.extend( module_names_list )

    @staticmethod
    def get_selected_tests():
        return NeulBuildConfig.selected_tests

    @staticmethod
    def set_build_info(info):
        NeulBuildConfig.only_document_paths = info['only_document_paths'] if info.has_key('only_document_paths') else ['src']
        NeulBuildConfig.only_document_extensions = info['only_document_extensions'] if info.has_key('only_document_extensions') else None
        NeulBuildConfig.doxygen_additional_tags = info['doxygen_additional_tags'] if info.has_key('doxygen_additional_tags') else {}
        NeulBuildConfig.srcrelease_ext_precedence = info['srcrelease_ext_precedence'] if info.has_key('srcrelease_ext_precedence') else ['.srcrelease']

        if NeulBuildConfig.only_document_extensions:
            fpattern = ",".join(NeulBuildConfig.only_document_extensions)
            NeulBuildConfig.doxygen_additional_tags['FILE_PATTERNS'] = fpattern

    @staticmethod
    def get_build_timestamp():
        return NeulBuildConfig.build_timestamp

    @staticmethod
    def get_build_time_string():
        return datetime.datetime.utcfromtimestamp( NeulBuildConfig.build_timestamp ).isoformat()


    @staticmethod
    def get_build_version_string():
        version_string = VersionInfo.read_string("VERSION_STRING")
        print "Using version string:", version_string
        return {'FIRMWARE_VERSION_STRING' : '\\"' + version_string + '\\"' }

    @staticmethod
    def get_build_git_hash():
        git_hash = VersionInfo.read_string("GIT_HASH")
        print "Using git hash:", git_hash
        return {'FIRMWARE_GIT_HASH' : '\\"' + git_hash + '\\"' }

    @staticmethod
    def get_build_dir_root():
        return os.path.join(Dir('#').abspath, 'build_scons')

    @staticmethod
    def get_root_dir():
        return NeulBuildConfig.root

    @staticmethod
    def set_drmemory(value):
        drmemory = os.path.join(Dir('#').abspath, 'tools', 'drmemory', 'bin', 'drmemory.exe')
        drmemory_suppress = os.path.join(Dir('tools').srcnode().abspath, 'drmemory', 'suppress.txt')
        drmemory = File(drmemory).srcnode().abspath + " -show_reachable -suppress %s -src_whitelist *build_scons*,*src* -src_whitelist_frames 4096 -report_leak_max -1 -exit_code_if_errors 1 -batch -lib_blacklist python??.dll!* -check_uninit_blacklist UMEngx86.dll" % drmemory_suppress
        NeulBuildConfig.DRMEMORY = drmemory + value + " -- "

    @staticmethod
    def get_build_xml():
        return NeulBuildConfig.build_xml

    @staticmethod
    def get_minimal_build_tools():
        tools = []
        for i in minimal_tools:
            tools.append(Glob(os.path.join(Dir('#').srcnode().abspath, i)))
        return tools

    @staticmethod
    def get_only_document_paths():
        return NeulBuildConfig.only_document_paths

    @staticmethod
    def get_only_document_extensions():
        return NeulBuildConfig.only_document_extensions

    @staticmethod
    def get_doxygen_additional_tags():
        return NeulBuildConfig.doxygen_additional_tags

    @staticmethod
    def get_srcrelease_ext_precedence():
        return NeulBuildConfig.srcrelease_ext_precedence

    @staticmethod
    def get_signature_dirname():
        return ('signature')

    @staticmethod
    def get_sha_dirname():
        return ('sha256')

    @staticmethod
    def postprocess_cmdline_args_and_options(overide=False):
        if NeulBuildConfig.modules:
            if 'mac' in NeulBuildConfig.modules: NeulBuildConfig.modules.update(['mac_ul','mac_dl'])
            if 'rlc' in NeulBuildConfig.modules: NeulBuildConfig.modules.update(['rlc_ul','rlc_dl'])

        if overide:
            # Doxygen related overide changes.
            # Added to ensure current SDK docs build as it was.
            NeulBuildConfig.doxy_enable_tagfiles = False
            NeulBuildConfig.doxy_build_single = True


    @staticmethod
    def store_cmdline_args():

        NeulBuildConfig.modules = ARGUMENTS.get('modules', None)
        if NeulBuildConfig.modules:
            # Using sets to ensure unique entries only in NeulBuildConfig.modules
            NeulBuildConfig.modules =  set(NeulBuildConfig.modules.split(','))

        NeulBuildConfig.doxygen_quiet_mode = True
        if int(ARGUMENTS.get('VERBOSE', 0)) != 0:
            NeulBuildConfig.doxygen_quiet_mode = False

    @staticmethod
    def store_cmdline_options():

        NeulBuildConfig.doxy_enable_tagfiles = GetOption('doxy_enable_tagfiles')
        NeulBuildConfig.doxy_api_only        = GetOption('doxy_api_only')
        NeulBuildConfig.doxy_build_single    = GetOption('doxy_build_single')


# We can place here any per-package build parameters
# Per-package build (ones that change per package, e.g. build_chip are in here

class NeulPackageConfig:

    @staticmethod
    def set_build_info_per_package(info, env, signing_asset_name):
        perPackageDict = {}
        build_chip = 'none'

        # check consistent chip in package
        for build in info['builds']:
            if build_chip is 'none':
                build_chip = build['chip']
            elif build_chip != build['chip']:
                build['chip']
                raise RuntimeError("Inconsistent package configuration: different build_chip specified: %s" % build_chip + '!=' + build['chip'])
        perPackageDict['build_chip'] = build_chip

        perPackageDict['built_files'] = info['built']
        perPackageDict['package_name'] = info['name']
        perPackageDict['authentication_mode'] = signing_asset_name

        perPackageDict['customer_list'] = info['customer']

        # set signing asset root
        if signing_asset_name is None or signing_asset_name in 'none':
            perPackageDict['securityAssetRoot'] = 'none'
        elif signing_asset_name in ['DEVELOPMENT','MIXED']:
            perPackageDict['securityAssetRoot'] = os.path.join('authentication')
            sys.path.append(perPackageDict['securityAssetRoot'])
        else:
            perPackageDict['securityAssetRoot'] = os.path.join('authentication', 'test', signing_asset_name)
            sys.path.append(perPackageDict['securityAssetRoot'])

        perPackageDict['certificateDir'] =  os.path.join(perPackageDict['securityAssetRoot'], 'public',   perPackageDict['build_chip'], 'certificates')
        perPackageDict['keystoreDir']    =  os.path.join(perPackageDict['securityAssetRoot'], 'public',   perPackageDict['build_chip'], 'keystores')

        # save to the env
        env.Append(NEULDEV_PER_PACKAGE = perPackageDict)

    @staticmethod
    def get_build_chip(env):
        perTargetDict = env['NEULDEV_PER_PACKAGE']
        return perTargetDict['build_chip']

    @staticmethod
    def get_package_name(env):
        perTargetDict = env['NEULDEV_PER_PACKAGE']
        return perTargetDict['package_name']

    @staticmethod
    def get_built_files(env):
        perTargetDict = env['NEULDEV_PER_PACKAGE']
        return perTargetDict['built_files']

    @staticmethod
    def get_signing_asset_root(env):
        perTargetDict = env['NEULDEV_PER_PACKAGE']
        return perTargetDict['securityAssetRoot']

    @staticmethod
    def get_certificate_dir(env):
        perTargetDict = env['NEULDEV_PER_PACKAGE']
        return perTargetDict['certificateDir']

    @staticmethod
    def get_keystore_dir(env):
        perTargetDict = env['NEULDEV_PER_PACKAGE']
        return perTargetDict['keystoreDir']

    @staticmethod
    def get_authentication_mode(env):
        perTargetDict = env['NEULDEV_PER_PACKAGE']
        return perTargetDict['authentication_mode']

    @staticmethod
    def get_customer_list(env):
        perTargetDict = env['NEULDEV_PER_PACKAGE']
        return perTargetDict['customer_list']


# We can place here any per-target build parameters
# Common parameters used across build framework should be in NeulBuildConfig
# Per-target build (ones that change per target, e.g. core_image are in here

class NeulTargetConfig:

    @staticmethod
    def set_build_info_per_target(info, env, signing_asset_name, codeloader_version = 3):
        perTargetDict = {}
        perTargetDict['codeloader_version'] = codeloader_version
        perTargetDict['core'] = 'none'
        perTargetDict['build_memory_config'] = 'none'
        perTargetDict['build_prelink_script'] = 'none'
        perTargetDict['securityAssetRoot'] = 'none'
        perTargetDict['signatureMapLoaded'] = False
        perTargetDict['signingAsset'] = None
        perTargetDict['signatureAlgoName'] = None
        perTargetDict['build_core'] = 'none'
        perTargetDict['target_application'] = 'none'

        # instantiate passed-in data
        perTargetDict['build_os'] = info.get('os', 'none')
        perTargetDict['build_drivers_set'] = info.get('drivers_set', 'none')
        perTargetDict['support_libs'] = info.get('support_libs', [])
        perTargetDict['support_libs_whole'] = info.get('support_libs_whole', []) # other libs that will be under the --whole-archive option
        perTargetDict['build_defines'] = info.get('defines', [])
        perTargetDict['build_lint_clean_dirs'] = info.get('lint_clean_dirs', []) # No clean lint folders by default
        perTargetDict['precompiled_libs'] = info.get('precompiled_libs', [])
        perTargetDict['release_as_libs'] = info.get('release_as_libs', [])
        perTargetDict['build_application'] = info.get('application', 'none')
        perTargetDict['binary_name'] = info.get('binary_name', 'none')
        perTargetDict['optimisation'] = info.get('optimisation', 'none')
        perTargetDict['unwind'] = info.get('unwind', 'none')
        perTargetDict['stackdump'] = info.get('stackdump', 'none')
        perTargetDict['image_slot'] =  info.get('image_slot', 'none')
        perTargetDict['build_chip'] = info.get('chip', 'none')
        perTargetDict['build_type'] = info.get('type', BuildType.MAX_BUILD_TYPE)
        perTargetDict['build_platform'] =  info.get('platform', 'none')
        perTargetDict['build_precompiled_libs'] = info.get('precompiled_libs', [])
        perTargetDict['build_chip_os_type'] = info.get('os_type', 'none')
        perTargetDict['target'] = info.get('target', 'none')

        if info.has_key('target'):
            perTargetDict['target_application'] = info['target']
        elif info.has_key('application'):
            perTargetDict['target_application'] = info['application']

        if info.has_key('core'):
            perTargetDict['build_core'] = info['core']
            if info.has_key('memory_config'):
                perTargetDict['build_memory_config'] = info['memory_config']
                perTargetDict['build_prelink_script'] = os.path.join(Dir('#').abspath,'src','config','memory',info['memory_config'],info['chip'],info['core'],'linker.prelds')

        # if we're upgrading, extract the source and dest targets
        perTargetDict['upgrade_src'] = info.get('upgrade_src', None)
        perTargetDict['upgrade_dest'] = info.get('upgrade_dest', None)
        perTargetDict['upgrader_otp_write'] = info.get('upgrader_otp_write', False)
        perTargetDict['upgrade_src_codeloader_version'] = info.get('upgrade_src_codeloader_version', 0)

        # set signing asset root
        if signing_asset_name is None or  signing_asset_name in 'none':
            perTargetDict['securityAssetRoot'] = 'none'
        elif signing_asset_name in ['DEVELOPMENT','MIXED']:
            perTargetDict['securityAssetRoot'] = os.path.join('authentication')
            sys.path.append(perTargetDict['securityAssetRoot'])
        else:
            perTargetDict['securityAssetRoot'] = os.path.join('authentication', 'test', signing_asset_name)
            sys.path.append(perTargetDict['securityAssetRoot'])

        if perTargetDict['securityAssetRoot'] != 'none':
            # read signing assets if present
            try:
                import SignatureMap
                perTargetDict['signatureMapLoaded'] = True
                perTargetDict['signingAsset'] = SignatureMap.SigningAsset
                perTargetDict['signatureAlgoName'] = SignatureMap.AlgorithmName
            except ImportError:
                raise RuntimeError("Failed to load SignatureMap from: ", perTargetDict['securityAssetRoot'])
                perTargetDict['signatureMapLoaded'] = False

            perTargetDict['certificateDir'] =  os.path.join(perTargetDict['securityAssetRoot'], 'public',   perTargetDict['build_chip'], 'certificates')
            perTargetDict['keystoreDir']    =  os.path.join(perTargetDict['securityAssetRoot'], 'public',   perTargetDict['build_chip'], 'keystores')

        # save to the env
        env.Append(NEULDEV_PER_TARGET = perTargetDict)

    @staticmethod
    def get_build_core(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_core']

    @staticmethod
    def get_build_os(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_os']

    @staticmethod
    def get_funwind(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        if (perTargetDict['unwind'] == 'on' or perTargetDict['unwind'] == 'none'):
            return 'on'
        elif  perTargetDict['unwind'] == 'off':
            return 'off'
        else:
            sys.exit('Error unwind illegal value')
        return flags

    @staticmethod
    def get_stackdump_flag(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        if (perTargetDict['stackdump'] == 'on' or perTargetDict['stackdump'] == 'none'):
            return 'on'
        elif  perTargetDict['stackdump'] == 'off':
            return 'off'
        else:
            sys.exit('Error stackdump illegal value')
        return flags

    @staticmethod
    def get_drivers_set(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_drivers_set']

    @staticmethod
    def get_build_platform(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_platform']

    @staticmethod
    def set_build_type(type):
        perTargetDict = env['NEULDEV_PER_TARGET']
        perTargetDict['build_type'] = type

    @staticmethod
    def get_build_type(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_type']

    @staticmethod
    def get_build_type_name(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return build_name[perTargetDict['build_type']]

    @staticmethod
    def get_support_libs(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['support_libs']

    @staticmethod
    def get_support_libs_whole(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['support_libs_whole']

    @staticmethod
    def get_build_defines(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_defines']

    @staticmethod
    def get_build_lint_clean_dirs(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_lint_clean_dirs']

    @staticmethod
    def get_build_dir(env):
        return os.path.join(Dir('#').abspath, NeulTargetConfig.get_relative_build_dir(env))

    @staticmethod
    def get_build_precompiled_libs(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_precompiled_libs']

    @staticmethod
    def get_build_release_as_libs(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_release_as_libs']

    @staticmethod
    def get_image_slot(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['image_slot']

    @staticmethod
    def get_build_chip(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_chip']

    @staticmethod
    def get_build_chip_define(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        target_defines = [{'TARGET_CHIP' : '\\"' + perTargetDict['build_chip'] + '\\"' }]
        if perTargetDict['upgrade_dest'] not in [None, '']:
            target_defines.append({'UPGRADER_SSB_DEST_BIN' : '\\"precompiled' + '/' + perTargetDict['upgrade_dest'] + '/' + 'ssb.bin\\"'})
            target_defines.append({'UPGRADER_SSB_DEST_SHA256' : '\\"precompiled' + '/' + perTargetDict['upgrade_dest'] + '/' + 'ssb.sha256\\"'})
        if perTargetDict['upgrade_src'] not in [None, '']:
            target_defines.append({'UPGRADER_SSB_SRC_BIN' : '\\"precompiled' + '/' + perTargetDict['upgrade_src'] + '/' + 'ssb.bin\\"'})
            target_defines.append({'UPGRADER_SSB_SRC_SHA256' : '\\"precompiled' + '/' + perTargetDict['upgrade_src'] + '/' + 'ssb.sha256\\"'})
            target_defines.append({'UPGRADER_SSB_SRC_BIN_SIZE' : str( fileSize( os.path.join('precompiled', perTargetDict['upgrade_src'], 'ssb.bin'))) + 'ul' })
        if perTargetDict['upgrader_otp_write']:
            target_defines.append({'UPGRADER_SSB_WRITE_OTP' : '\\"' + str( perTargetDict['upgrader_otp_write'] ) + '\\"'})
        return target_defines

    @staticmethod
    def get_relative_build_dir(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        if "BUILDNAME" in env:
            buildname = env["BUILDNAME"]
        else:
            buildname = build_name[perTargetDict['build_type']]
        #Check if the app folder has a build_core folder. If it has create the output there
        if perTargetDict['build_core'] in next(os.walk(os.path.join(Dir('#').abspath,'src','app',perTargetDict['build_application'])))[1]:
            path =  os.path.join('build_scons', buildname, perTargetDict['build_platform'], perTargetDict['target_application'], perTargetDict['build_core'] )
        else:
            path =  os.path.join('build_scons', buildname, perTargetDict['build_platform'], perTargetDict['target_application'] )
        return path

    @staticmethod
    def get_update_src_codeloader_version(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['upgrade_src_codeloader_version']

    @staticmethod
    def get_build_chip_family(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        if( 'Hi21' in perTargetDict['build_chip'] ):
            return 'Hi21XX'
        return perTargetDict['build_chip']

    @staticmethod
    def get_build_chip_os_type(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_chip_os_type']

    @staticmethod
    def get_memory_config(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_memory_config']

    @staticmethod
    def get_build_prelink_script(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        if perTargetDict['build_prelink_script'] == 'none':
            return None
        else:
            return perTargetDict['build_prelink_script']

    @staticmethod
    def get_codeloader_version(env, compat = None):
        perTargetDict = env['NEULDEV_PER_TARGET']
        if (compat in ['B180']):
            codeloader_version =  B180_CODELOADER_VERSION
        else:
            codeloader_version = perTargetDict['codeloader_version']
        return codeloader_version

    @staticmethod
    def get_binary_name(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        # Default to the core name with the _core suffix removed.
        name = perTargetDict['build_core'][:-5]
        if perTargetDict['binary_name'] != 'none':
            name = perTargetDict['binary_name']
        return name

    @staticmethod
    # barf if we get something unexpected
    def get_build_flags(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        flags = []
        # optimisation flag
        if perTargetDict['optimisation'] != 'none':
            flags.append(perTargetDict['optimisation'])
        else:
            flags.append('-O1')
        # unwind
        unwind_flag = NeulTargetConfig.get_funwind(env)
        if (unwind_flag == 'on'):
            flags.append('-funwind-tables')
        elif   unwind_flag == 'off':
            flags.append('-fno-unwind-tables')
        else:
            sys.exit('Error unwind illegal value')
        return flags

    @staticmethod
    def get_application(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['build_application']

    @staticmethod
    def get_target_application(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['target_application']

    @staticmethod
    def get_signing_asset_root(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['securityAssetRoot']

    @staticmethod
    def get_certificate_dir(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['certificateDir']

    @staticmethod
    def get_keystore_dir(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['keystoreDir']

    @staticmethod
    def get_signing_asset_list(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['signatureMapLoaded'], perTargetDict['signingAsset']

    @staticmethod
    def get_signing_signature_algo_name(env):
        perTargetDict = env['NEULDEV_PER_TARGET']
        return perTargetDict['signatureAlgoName']

    @staticmethod
    def get_signing_assets(env, image_slot):
        perTargetDict = env['NEULDEV_PER_TARGET']
        cert_path = None
        priv_key_path = None
        priv_key_password = None

        if not perTargetDict['signatureMapLoaded']:
            print("Signature Asset Map Not Loaded")
        if perTargetDict['signatureMapLoaded']:
            perSlotAssetsList = perTargetDict['signingAsset'][image_slot]
            returnAssetList = []
            for perSlotAssets in perSlotAssetsList:
                if (perSlotAssets['cert_filename'] in 'unsigned') and (perSlotAssets['private_key_filename'] in 'unsigned'):
                    cert_path = 'unsigned'
                    priv_key_path = 'unsigned'
                else:
                    cert_path = os.path.join(perTargetDict['certificateDir'], perSlotAssets['cert_filename'])
                    priv_key_path = os.path.join(perTargetDict['securityAssetRoot'], 'private', perTargetDict['build_chip'], perSlotAssets['private_key_filename'])
                returnAssetList.append({'cert_path' : cert_path, 'priv_key_path' : priv_key_path, 'priv_key_password' : priv_key_password})
        return returnAssetList

# return each directory path that leads to the supplied file path
def path_walk(path):
    head,tail =  os.path.split(str(path))
    if tail:
        return((head,) + path_walk(head))
    else:
        return((head,))
