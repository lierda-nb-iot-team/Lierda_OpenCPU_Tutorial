#===============================================================================
# @brief    Scons make file
# Copyright (c) 2016 NEUL LIMITED
#===============================================================================

from SCons.Script import *
from EnvironmentUtils import NeulBuildConfig, NeulTargetConfig
import VersionInfo

import subprocess
import hashlib

ImageSignVerifyAvailable = False
try:
    import ImageSignVerify
    ImageSignVerifyAvailable = True
except ImportError:
    pass

def checkCryptographyInstalled():
    if ImageSignVerifyAvailable:
        return ImageSignVerify.checkCryptoCMSInstalled()
    else:
        return False

def create_sha_file(target, source, env):
    with open( str(source[0]), "rb" ) as bin_file, open( str(target[0]), "w") as sha_file:
        sha = hashlib.sha256( bin_file.read() )
        bin_file.close()
        # Write SHA using same format as sha256sum gnu utility
        sha_file.write( sha.hexdigest() + ' *' + os.path.basename( str(source[0]) ))
        sha_file.close()

# create signature files
# always a sha256
def create_signature_sha256(target, source, env):
    with open( str(source[0]), "rb" ) as bin_file, open( str(target[0]), "wb") as sig_sha_file:
        sha = hashlib.sha256( bin_file.read() )
        bin_file.close()
        # Write SHA using same format as sha256sum gnu utility
        sig_sha_file.write( sha.digest() )
        sig_sha_file.close()

# create signature files
# ecc or rsa with dev keys
def create_signature_der(target, source, env):

    # load image
    coreImageFilename = str(source[0])

    # we've not set a signing root, return but don't fail
    # only warn on a chip that should be signed
    if (NeulTargetConfig.get_signing_asset_root(env) in 'none'):
        print("No signing root specified. Images will not be signed.")
        return

    # load assets
    # returns an array of signerCertificateFilename, signerPrivateKeyFilename, signerPrivateKeyPassword

    signerAssetList = NeulTargetConfig.get_signing_assets(env, NeulTargetConfig.get_image_slot(env))

    signatureNumber = 0
    for signerAsset in signerAssetList:
        signerCertificateFilename = signerAsset['cert_path']
        signerPrivateKeyFilename = signerAsset['priv_key_path']
        signerPrivateKeyPassword = signerAsset['priv_key_password']
        # if no signature specified, don't sign and fail
        if signerCertificateFilename is None or signerPrivateKeyFilename is None:
            raise SCons.Errors.StopError("No certificate or private key specified.")

        # if actively unsigned, don't sign and don't fail
        if signerCertificateFilename in 'unsigned' or signerPrivateKeyFilename in 'unsigned':
            return

        # if signature specified, but file doesn't exist, don't sign and fail
        if not os.path.exists(signerCertificateFilename) or not os.path.exists(signerPrivateKeyFilename):
            raise SCons.Errors.StopError("Specified certificate or private key file does not exist: %s" % signerCertificateFilename + ' ' + signerPrivateKeyFilename)

        # sign image
        print("Signing image with certificate and key: %s" % coreImageFilename + ' ' + signerCertificateFilename + ' ' + signerPrivateKeyFilename + ' ' + NeulTargetConfig.get_signing_signature_algo_name(env))
        signature = ImageSignVerify.signImage(coreImageFilename, signerCertificateFilename, signerPrivateKeyFilename, NeulTargetConfig.get_signing_signature_algo_name(env), signerPrivateKeyPassword)
        if signature is None:
            raise SCons.Errors.StopError("Failed to sign image.")

        outputDERFilename = str(target[signatureNumber])
        signatureNumber += 1
        if outputDERFilename is None:
            raise SCons.Errors.StopError("No signature file specified.")

        sign_success = ImageSignVerify.writeDataFile(outputDERFilename, signature)
        if  not sign_success:
            raise SCons.Errors.StopError("Failed to write signature file %s." % outputDERFilename)

def create_version_file(target, source, env):
    # Find version information in env['CPPDEFINES']
    version_number = 0
    version_string = 'none'
    for cpp_define in env['CPPDEFINES']:
        if 'APPLICATION_VERSION_NUMBER' in cpp_define:
            version_number = cpp_define[1]
        if 'APPLICATION_VERSION_STRING' in cpp_define:
            version_string = str( cpp_define[1] )[2:-2]   # Remove leading and trailing \"

    with open( str(target[0]), "w") as ver_file:
        if version_number > 0:
            ver_file.write( 'VERSION_NUMBER: %s\n' % str(version_number) )
        if version_string is not 'none':
            ver_file.write( 'VERSION_STRING: %s\n' % (NeulBuildConfig.get_build_time_string() + ' ' + version_string) )
        else:
            ver_file.write( 'VERSION_STRING: %s\n' % (NeulBuildConfig.get_build_time_string() + ' ' + VersionInfo.read_string("VERSION_STRING")) )
        ver_file.write( 'TIMESTAMP: %s\n' % hex( NeulBuildConfig.get_build_timestamp() )[2:] )
        ver_file.write( 'GITHASH: %s\n' % VersionInfo.read_string("GIT_HASH") )
        ver_file.close()

# Return the path of libgcc used by the compiler in use
def find_arm_libgcc_include_dir(env):
    command = env['CC'] + ' --print-libgcc-file-name'
    libgcc_fname = subprocess.check_output(command, shell=True)
    libgcc_path = os.path.join(os.path.dirname(libgcc_fname), 'include')
    return libgcc_path

def modify_targets_sha256(target, source, env):
    target_filename = os.path.basename(str(target[0]))
    target_dirname = os.path.dirname(str(target[0]))
    target_newtarget = os.path.join(target_dirname, NeulBuildConfig.get_sha_dirname(), target_filename)
    target[0] = target_newtarget

    return target, source

def modify_targets_signature_bin(target, source, env):
    target_filename = os.path.basename(str(target[0]))
    target_dirname = os.path.dirname(str(target[0]))
    target_newtarget = os.path.join(target_dirname, NeulBuildConfig.get_signature_dirname(), target_filename)
    target[0] = target_newtarget

    return target, source

def modify_targets_signature_der(target, source, env):
    target_filename = os.path.basename(str(target[0]))
    target_main_name, target_extension = os.path.splitext(target_filename)
    target_dirname = os.path.dirname(str(target[0]))
    target_number = 0
    target= []
    signerAssetList = NeulTargetConfig.get_signing_assets(env, NeulTargetConfig.get_image_slot(env))
    for signerAsset in signerAssetList:
        outputDERFilename = target_main_name + str(target_number + 1) + target_extension
        target.append(os.path.join(target_dirname, NeulBuildConfig.get_signature_dirname(), outputDERFilename))
        target_number += 1

    return target, source

# Setup the ARM compiler toolchain to the specified Environment
def install_arm_tools(env, NeulBuildConfig):
    # Override the default GNU names with the target compiler. Avoids creating lots of new tool files.
    env['AR'] = 'arm-none-eabi-ar'
    env['AS'] = 'arm-none-eabi-gcc'
    env['CC'] = 'arm-none-eabi-gcc'
    env['CXX'] = 'arm-none-eabi-g++'
    env['LINK'] = 'arm-none-eabi-gcc'
    env['RANLIB'] = 'arm-none-eabi-ranlib'
    env['OBJCOPY'] = 'arm-none-eabi-objcopy'
    env['OBJDUMP'] = 'arm-none-eabi-objdump'
    env['PROGSUFFIX'] = '.elf'
    env['CTYPESGEN'] = NeulBuildConfig.CTYPESGEN_PATH
    env['MESSAGEXML'] = NeulBuildConfig.MESSAGEXML_PATH
    env['MESSAGEXMLCONFIG'] = NeulBuildConfig.MESSAGEXML_CONFIG
    env['MESSAGERULES'] = NeulBuildConfig.MESSAGE_RULES
    env['STACKUSAGE'] = NeulBuildConfig.STACKUSAGE_PATH
    env['XML'] = NeulBuildConfig.XML_PATH
    env['XSD'] = NeulBuildConfig.XSD_PATH

    env['ELFTODU'] = 'python ' + File(os.path.join('tools', 'scripts', 'elftodu.py')).srcnode().abspath
    env['MEMSTATS'] = 'python ' + File(os.path.join('tools', 'scripts', 'mem_stats.py')).srcnode().abspath

    # Set CCFLAGS
    CCFlags = NeulBuildConfig.COMMON_CCFLAGS + [
        '-fomit-frame-pointer',
        '-ffreestanding',
        '-fdata-sections',
        '-ffunction-sections',
        '--short-enums',
        '-specs=nano.specs',
        # See explicit CPPPATH addition below
        '-nostdinc',
        '-nostdlib',
        '-pipe',
        '-mno-unaligned-access',
        '-mcpu=cortex-m0',
        '-march=armv6-m',
        '-mthumb',
        '-Wimplicit-fallthrough=2'
    ]
    env.Append(CCFLAGS =  CCFlags )
    env['ASFLAGS'] = env['CCFLAGS']

    # When using "-nostdinc", need to explicitly tell the compiler about the internal include path we do use.
    env.Append(CPPPATH = find_arm_libgcc_include_dir(env))

    LinkFlags = [
        '-Wl,--gc-section,--cref,--relax,-M',
        '-Wl,-Map=' + os.path.join(NeulTargetConfig.get_relative_build_dir(env), NeulTargetConfig.get_binary_name(env) + '.map'),

        # The 'prelinker' file is preprocessed by the C preprocessor to generate the atcual linker lds file.
        # Need to generate the file name in line with what the builder (see below) generates.
        '-Wl,-T' + os.path.join(NeulTargetConfig.get_relative_build_dir(env), os.path.splitext( os.path.basename(NeulTargetConfig.get_build_prelink_script(env)) )[0] + '.lds' ),
        '-mcpu=cortex-m0',
        '-march=armv6-m',
        '-mthumb'
    ]
    env.Append(LINKFLAGS = [ LinkFlags ])

    # Ensure libraries are repeatedly linked, as there is a circular dependency! This makes assumptions about the
    # actual link command (see link.py in the site wide scons/Tools directory).
    env[ 'LIB_GROUP_PREFIX' ] = ['-Wl,--start-group']
    env[ 'LIB_GROUP_SUFIX'  ] = ['-Wl,--end-group']
    env[ 'WHOLE_ARCHIVE_LIBFLAGS' ]= [ '-Wl,--whole-archive',
                                      '${_stripixes(LIBLINKPREFIX, WHOLE_ARCHIVE_LIBS, LIBLINKSUFFIX, LIBPREFIXES, LIBSUFFIXES, __env__)}',
                                      '-Wl,--no-whole-archive']
    env['LINKCOM']= '$LINK -o $TARGET $LINKFLAGS $__RPATH $SOURCES $_LIBDIRFLAGS $LIB_GROUP_PREFIX $_LIBFLAGS $WHOLE_ARCHIVE_LIBFLAGS $LIB_GROUP_SUFIX'

    # Force creation of a THIN libary, which allows libraries to be linked together into a single library.
    # Use REPLACE as opposed to APPEND, as using append would cause "rc T" which doesn't work!
    env.Replace(ARFLAGS = [ 'rcT' ])

    env.Append(BUILDERS = {'Binary': binary_builder})
    env.Append(BUILDERS = {'ShaBinary': sha_binary_builder})
    env.Append(BUILDERS = {'SignatureBinary': sig_binary_builder})
    env.Append(BUILDERS = {'Listing': listing_builder})
    env.Append(BUILDERS = {'LinkFile': linker_builder})
    env.Append(BUILDERS = {'DuFile': du_builder})
    env.Append(BUILDERS = {'MemFile': mem_stats_builder})
    env.Append(BUILDERS = {'StackUsageFile': stack_builder})
    env.Append(BUILDERS = {'ShaFile': sha_builder})
    env.Append(BUILDERS = {'SHA256_SignatureFile': sha256_signature_builder})
    env.Append(BUILDERS = {'Generate_SignatureFile': der_signature_builder})
    env.Append(BUILDERS = {'VerFile': ver_builder})

    # Other tools may need this to allow for "-nostdinc", as we then need to explicitly add the arm include directory
    env.AddMethod(find_arm_libgcc_include_dir)

# Convert from ELF to binary in sha directory
sha_binary_builder = Builder(
        action = Action('$OBJCOPY --gap-fill 0xFF -O binary $SOURCE $TARGET', 'Generating $TARGET ...'),
        suffix ='.bin',
    src_suffix ='.elf',
    emitter = modify_targets_sha256
)

# Convert from ELF to binary in signature directory
sig_binary_builder = Builder(
        action = Action('$OBJCOPY --gap-fill 0xFF -O binary $SOURCE $TARGET', 'Generating $TARGET ...'),
        suffix ='.bin',
    src_suffix ='.elf',
    emitter = modify_targets_signature_bin
)

# Convert from ELF to binary
binary_builder = Builder(
        action = Action('$OBJCOPY --gap-fill 0xFF -O binary $SOURCE $TARGET', 'Generating $TARGET ...'),
        suffix ='.bin',
    src_suffix ='.elf'
)

# Generate listing file
listing_builder = Builder(
        action =  Action('$OBJDUMP $SOURCE -x -S > $TARGET', 'Generating $TARGET ...'),
        suffix ='.lst',
    src_suffix ='.elf'
)

# This Builder generates a linker .lds file from a .prelds file by passing it trough the gcc preprocessor.
# That way we can use #includes and symbols in the memory origins and regions.
# Re-use the 'standard' CC line, but with additional options "-C -E -P -xc"
linker_builder = Builder(
        action = Action ('$CC -C -E -P -xc -o $TARGET -c $CFLAGS $CCFLAGS $_CCCOMCOM $SOURCES', 'Generating $TARGET ...'),
        suffix = '.lds',
    src_suffix = '.prelds',

    # Use standard C dependency scanner. Forces install of header files needed incase of library builds.
    source_scanner = SCons.Scanner.C.CScanner(),
)

du_builder = Builder(
    action = Action ('$ELFTODU $SOURCE > $TARGET', 'Generating $TARGET ...'),
    suffix ='.du',
    src_suffix ='.elf'
)

mem_stats_builder = Builder(
    action = Action ('$MEMSTATS $SOURCES > $TARGET', 'Generating $TARGET ...'),
    suffix ='.mem',
    src_suffix = ['.lst', '.du']
)

sha_builder = Builder(
    action = Action (create_sha_file, 'Generating sha $TARGET ...'),
    suffix ='.sha',
    src_suffix ='.bin'
)

sha256_signature_builder = Builder(
    action = Action (create_signature_sha256, 'Generating sha256 $TARGET ...'),
    suffix ='.sha256',
    src_suffix ='.bin',
    emitter = modify_targets_sha256
)

der_signature_builder = Builder(
    action = Action (create_signature_der, 'Generating der $TARGET ...'),
    suffix ='.der',
    src_suffix ='.bin',
    emitter = modify_targets_signature_der
)

ver_builder = Builder(
    action = Action (create_version_file, 'Generating ver $TARGET ...'),
    suffix ='.ver',
    src_suffix ='.bin'
)

stack_builder = Builder(
    action = Action(
        'python $STACKUSAGE $SOURCES $TARGET',
        'Generating Stack Usage Report in $TARGET ...' if not ARGUMENTS.get("VERBOSE", 0) else ""
    ),
    suffix = '',
    src_suffix = ['.lst', '.opt'],
)

