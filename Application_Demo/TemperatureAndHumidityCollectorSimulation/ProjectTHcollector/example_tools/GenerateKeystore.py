#!/usr/local/bin/python2.7
# encoding: utf-8

'''
GenerateKeystore -- Neul Software Keystore Generator

GenerateKeystore is a tool to create a keystore from a set of RootCA certificates

It is provided as an example only and is not supported

Copyright (c) 2018 Huawei Technologies Co. Ltd
'''
from __future__ import print_function

from ConfigParser import NoSectionError
import ConfigParser
from argparse import ArgumentParser
from argparse import RawDescriptionHelpFormatter
import logging.config
import os
import sys
import hashlib
import logging
import struct

cmsAvailable = False
try:
    import asn1crypto.cms as cms
    import asn1crypto.algos as algos
    import asn1crypto.core as core
    cmsAvailable = True
except ImportError:
    pass

cryptographyAvailable = False
try:
    from cryptography.hazmat.primitives import serialization
    from cryptography.hazmat.backends import default_backend
    from cryptography.hazmat.primitives import hashes
    from cryptography.hazmat.primitives.asymmetric import ec
    from cryptography.hazmat.primitives.asymmetric import rsa
    from cryptography.hazmat.primitives.asymmetric import padding
    from cryptography import x509
    from cryptography import exceptions
    cryptographyAvailable = True
except ImportError:
    pass

def checkCryptoCMSInstalled():
    if cmsAvailable is False or cryptographyAvailable is False:
        logging.debug("One of cmsAvailable(%s) or cryptographyAvailable(%s) is not True" %(str(cmsAvailable), str(cryptographyAvailable)))
        return False
    return True

KEYSTORE_MAGIC = b"\xD5\x54\x2A\x80"

__programname__ = 'GenerateKeystore'
__version__ = 0.3
__date__ = '2017-10-18'
__updated__ = '2018-03-22'

TESTRUN = 0
PROFILE = 0

def printData(name,data):
    print("%s" % name)
    logging.debug("\Name: %s" % name)
    if data is not None:
        logging.debug("\tLength: %d" % len(data))
        logging.debug("\t%s" % "".join(x.encode('hex') for x in data))
        print("\tLength: %d" % len(data))
        print("\t%s" % "".join(x.encode('hex') for x in data))

def loadCertificate(certificateFilename):
    logging.debug("Loading certificate '%s'" % certificateFilename)
    try:
        with open(certificateFilename, mode='rb') as f:
            fileContent = f.read()
            f.close()
        return fileContent
    except (IOError, OSError) as e:
        logging.error("Error loading file '%s' - exception %s" % (certificateFilename, str(e)))
        return None

def createKeystoreKey(certFile, usage):
    key = {}
    loadedCertificate = loadCertificate(certFile)
    signerCertificate = x509.load_der_x509_certificate(loadedCertificate, default_backend())

    key['publicKey'] = signerCertificate.public_key().public_bytes(serialization.Encoding.DER, serialization.PublicFormat.SubjectPublicKeyInfo) # PEM or DER, SubjectPublicKeyInfo or PKCS1
    key['subjectKeyIdentifier'] = signerCertificate.extensions.get_extension_for_class(x509.SubjectKeyIdentifier).value.digest

    publicKey = signerCertificate.public_key()
    if isinstance(publicKey, rsa.RSAPublicKey):
        key['keyAlgorithm'] = [ 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01 ]
        key['keyAlgorithmParams'] = [ ]
    elif isinstance(publicKey, ec.EllipticCurvePublicKey):
        key['keyAlgorithm'] = [ 0x06, 0x07, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01 ]
        if publicKey.curve.name == "secp256r1":
            key['keyAlgorithmParams'] = [ 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07 ]
        else:
            key['keyAlgorithmParams'] = [ ]
    else:
        logging.error("Error parsing certificate, unknown key type")
        raise ValueError('Error parsing certificate, unknown key type')
        key['keyAlgorithm'] = [ ]   #Or do we just fail
        key['keyAlgorithmParams'] = [ ]

    key['keyUsage'] = usage
    return key

def writeKeystore(keystoreFilename, keystore_id, keystore):
    logging.info("Writing file '%s'" % keystoreFilename)
    ks = struct.pack("<b", keystore_id)
    try:
        with open(keystoreFilename, mode='wb') as f:
            # write header
            f.write( KEYSTORE_MAGIC ) # 4 bytes
            f.write( ks ) # 1 byte

            for key in keystore:
                ku = struct.pack("<I", key['keyUsage']) # 4 bytes
                kal = struct.pack("<B", len(key['keyAlgorithm'])) # 1 byte
                kapl = struct.pack("<B", len(key['keyAlgorithmParams'])) # 1 byte
                ksl = struct.pack("<H", len(key['subjectKeyIdentifier']))  # 2 bytes
                kpl = struct.pack("<H", len(key['publicKey']))  # 2 bytes
                f.write( ku ) # 4 bytes
                f.write( kal ) # 1 byte
                f.write( kapl ) # 1 byte
                f.write( ksl ) # 2 bytes
                f.write( kpl ) # 2 bytes
                f.write( bytearray(key['keyAlgorithm'])) # variable byte
                f.write( bytearray(key['keyAlgorithmParams'])) # variable byte
                f.write( bytearray(key['subjectKeyIdentifier'])) # variable byte
                f.write( bytearray(key['publicKey'])) # variable byte
            # all done
            f.close()
    except (IOError, OSError) as e:
        logging.error("Error writing file '%s' - exception %s" % (keystoreFilename, str(e)))


def readKeystore(keystoreFilename):
    logging.info("Reading file '%s'" % keystoreFilename)
    keystore = []
    try:
        with open(keystoreFilename, mode='rb') as f:
            # write header
            keystore_magic_in = f.read(4) # 4 byte
            printData("magic",keystore_magic_in)
            if keystore_magic_in != KEYSTORE_MAGIC:
                return -2, None
            # read keystore ID
            keystore_id = struct.unpack("<b", f.read(1))[0] # 1 byte
            while True:
                key = {}
                # read key usage
                ku_in = f.read(4) # 4 byte s
                if len(ku_in) == 0:
                    break
                if len(ku_in) != 4:
                    return -3, None
                key['keyUsage'] = struct.unpack("<I",ku_in)[0]
                # read length of key algorithm
                kal_bytes = f.read(1) # 1 byte
                if len (kal_bytes) != 1:
                    return -4, None
                kal = struct.unpack("<B",kal_bytes)[0]
                # read length of key algorithm parameters
                kapl_bytes = f.read(1) # 1 byte
                if len (kapl_bytes) != 1:
                    return -5, None
                kapl = struct.unpack("<B",kapl_bytes)[0]
                # read length of subject key identifier
                ksl_bytes = f.read(2) # 2 byte
                if len (ksl_bytes) != 2:
                    return -6, None
                ksl = struct.unpack("<H",ksl_bytes)[0]
                # read length of public key
                pkl_bytes = f.read(2) # 2 byte
                if len (pkl_bytes) != 2:
                    return -7, None
                pkl = struct.unpack("<H",pkl_bytes)[0]
                # read  key algorithm
                key['keyAlgorithm'] = f.read(kal) # kal bytes
                if len ( key['keyAlgorithm'] ) != kal:
                    return -8, None
                # read  key algorithm parameters
                key['keyAlgorithmParams'] = f.read(kapl) # kal bytes
                if len ( key['keyAlgorithmParams'] ) != kapl:
                    return -9, None
                # read subject key identifier
                key['subjectKeyIdentifier'] = f.read(ksl) # ksl bytes
                if len ( key['subjectKeyIdentifier'] ) != ksl:
                    return -10, None
                # read public key
                key['publicKey'] = f.read(pkl) # pkl bytes
                #if len ( key['publicKey'] ) != pkl:
                #    return -11, None
                keystore.append(key)
            # all done
            f.close()
    except (IOError, OSError) as e:
        logging.error("Error reading file '%s' - exception %s" % (keystoreFilename, str(e)))
        return -2, None

    return keystore_id, keystore

def generateKeystoreHashFile(keystoreFilename, hashFilename):

    logging.info("Generate Keystore Hash file '%s'" % hashFilename )
    keystore = []
    try:
        with open(keystoreFilename, mode='rb') as f:
            # write header
            keystore_magic_in = f.read(4) # 4 byte
            if keystore_magic_in != KEYSTORE_MAGIC:
                return -2
            # read keystore ID
            f.read(1) # 1 byte

            # the rest is the keystore, so load it as a blob
            keystore = f.read()
            f.close()
    except (IOError, OSError) as e:
        logging.error("Error reading file '%s' - exception %s" % (keystoreFilename, str(e)))
        return -1

    sha = hashlib.sha256( keystore )

    try:
        with open(hashFilename, mode='wb') as f:
            f.write(sha.digest())
            f.close()
    except (IOError, OSError) as e:
        logging.debug("Error writing file '%s' - exception %s" % (hashFilename, str(e)))
        return -1

    return 0

def printKeystore(keystore_id, loadedKeystore):
    if keystore_id < 0:
        print ("error, keystore failed to decode: ", keystore_id)
    else:
        print("Keystore id: ", keystore_id)
        for keystore in loadedKeystore:
            printData("keyAlgorithm: ", keystore['keyAlgorithm'])

            printData("subjectKeyIdentifier: ", keystore['subjectKeyIdentifier'])
            print("keyUsage: ", keystore['keyUsage'])
            printData("keyAlgorithmParams: ", keystore['keyAlgorithmParams'])
            printData("publicKey: ", keystore['publicKey'])

def main(argv=None):  # IGNORE:C0111
    '''Command line options.'''

    if argv is None:
        argv = sys.argv
    else:
        sys.argv.extend(argv)

    program_name = os.path.basename(sys.argv[0])
    program_version = "v%s" % __version__
    program_build_date = str(__updated__)
    program_version_message = '%%(prog)s %s (%s)' % (program_version, program_build_date)
    program_shortdesc = __import__('__main__').__doc__.split("\n")[1]
    program_license = '''%s

  Copyright 2017 Neul Ltd. All rights reserved.

  Distributed on an "AS IS" basis without warranties
  or conditions of any kind, either express or implied.

USAGE
''' % program_shortdesc

    print("%s %s (%s)" % (__programname__, program_version, program_build_date))

    default_config_files = [os.path.join(os.path.dirname(os.path.realpath(__file__)), __programname__ + ".cfg"), os.path.join(os.path.expanduser("~"), "." + __programname__ + ".cfg")]
    CONFIG_SECTION = __programname__

    try:
        # Setup argument parser
        argparser = ArgumentParser(description=program_license, formatter_class=RawDescriptionHelpFormatter)

        # generic commands
        argparser.add_argument("-V", "--version", action='version', version=program_version_message)

        # generic options
        argparser.add_argument("-c", "--config", dest="config", metavar="FILE", default=None, help="Configuration file.")
        argparser.add_argument("-v", "--verbose", dest="verbose", action="count", help="set verbosity level [default: %(default)s]")

        # specific options
        argparser.add_argument("-ksid", "--keystoreid", dest="keystoreid", default=None, action="append", help="keystore 0 (SiVendor) or 1 (Customer)")
        argparser.add_argument("-cert1", "--certificate1", dest="certificate1", default=None, action="append", help="X509 Public Key Certificate (DER)")
        argparser.add_argument("-cert2", "--certificate2", dest="certificate2", default=None, action="append", help="X509 Public Key Certificate (DER)")
        argparser.add_argument("-cert3", "--certificate3", dest="certificate3", default=None, action="append", help="X509 Public Key Certificate (DER)")
        argparser.add_argument("-cert4", "--certificate4", dest="certificate4", default=None, action="append", help="X509 Public Key Certificate (DER)")
        argparser.add_argument("-use1", "--use1", dest="use1", default=None, help="Keystore Key use")
        argparser.add_argument("-use2", "--use2", dest="use2", default=None, help="Keystore Key use")
        argparser.add_argument("-use3", "--use3", dest="use3", default=None, help="Keystore Key use")
        argparser.add_argument("-use4", "--use4", dest="use4", default=None, help="Keystore Key use")
        argparser.add_argument("-iks", "--inputkeystore", dest="input_keystore", default=None, help="Keystore File")

        # Actions
        argparser.add_argument("-createkeystore", "--createkeystore", dest="createkeystore", action="store_true", default=False, help="Create a Keystore")
        argparser.add_argument("-printkeystore", "--printkeystore", dest="printkeystore", action="store_true", default=False, help="Print Keystore (takes no arguements)")

        # Process arguments
        commandline_options = vars(argparser.parse_args())

        logging_configured = False

        cfg_defaults = {
            # Command line options defaults
            'verbose' : 0,
            'certificate1' : None,
            'certificate2' : None,
            'certificate3' : None,
            'certificate4' : None,
            'use1' : None,
            'use2' : None,
            'use3' : None,
            'use4' : None,
        }

        # Make sure all our options are strings.
        config_defaults = {}
        for k, v in cfg_defaults.items():
            if v != None:
                config_defaults[k] = str(v)
            else:
                config_defaults[k] = None

        config = ConfigParser.SafeConfigParser(config_defaults)

        if commandline_options['config']:
            configfile = os.path.abspath(commandline_options['config'])
            if configfile in config.read(configfile):
                try:
                    logging.config.fileConfig(configfile)
                    logging_configured = True
                except NoSectionError:
                    pass

            if not config.has_section(CONFIG_SECTION):
                config.add_section(CONFIG_SECTION)
        else:
            # Try loading defaults if no command line options given.
            for configfile in default_config_files:
                if configfile in config.read(configfile):
                    try:
                        logging.config.fileConfig(configfile)
                        logging_configured = True
                    except NoSectionError:
                        pass
                    break
        # Add section if we don't have one
        if not config.has_section(CONFIG_SECTION):
            config.add_section(CONFIG_SECTION)

        # Override settings with settings from command line.
        for k, v in commandline_options.items():
            if v != None:
                if isinstance(v, list):
                    config.set(CONFIG_SECTION, k, "|".join(v))
                else:
                    config.set(CONFIG_SECTION, k, str(v))

        # We should now have a config option parser with everything set...
        # If we are verbose when add logging to std
        verbose = config.get(CONFIG_SECTION, 'verbose')
        if verbose and verbose != "0":
            console_handler = logging.StreamHandler(sys.stdout)
            console_handler.setLevel(logging.CRITICAL)  # set later by set_log_level_from_verbose() in interactive sessions
            console_handler.setFormatter(logging.Formatter('%(asctime)s: %(levelname)s: %(message)s'))

            loglevel = logging.DEBUG
            if verbose == '1':
                loglevel = logging.ERROR
            if verbose == '2':
                loglevel = logging.WARNING
            elif verbose == '3':
                loglevel = logging.INFO

            console_handler.setLevel(loglevel)
            logging.root.addHandler(console_handler)

            if not logging_configured:
                logging.root.setLevel(loglevel)
            logging_configured = True

        if not logging_configured:
            logging.basicConfig(level=logging.CRITICAL, format="%(asctime)s: %(levelname)s: %(message)s", stream=sys.stderr)

        logging.debug("Logging configured")

        logging.info("%s %s (%s)" % (__programname__, program_version, program_build_date))

        foundAction = False
        # -----------------------------------------------------------------------
        # Sign an image
        if commandline_options.get('createkeystore', None):
            foundAction = True
            logging.info("Create Keystore")

            # keystore id
            keystoreID = int(config.get(CONFIG_SECTION, 'keystoreid'))

            # load assets
            signerCertificateFilename = [
                config.get(CONFIG_SECTION, 'certificate1'),
                config.get(CONFIG_SECTION, 'certificate2'),
                config.get(CONFIG_SECTION, 'certificate3'),
                config.get(CONFIG_SECTION, 'certificate4')
            ]

            for cert in signerCertificateFilename:
                if cert is not None:
                    if os.path.isfile(cert) is not True:
                        logging.error("Certificate file does not exist.", cert)
                        print("Certificate file does not exist.", cert)
                        return -1

            signerCertificateUse = [
                config.get(CONFIG_SECTION, 'use1'),
                config.get(CONFIG_SECTION, 'use2'),
                config.get(CONFIG_SECTION, 'use3'),
                config.get(CONFIG_SECTION, 'use4')
            ]

            paramAdded = False
            for cert, use in zip(signerCertificateFilename, signerCertificateUse):
                if cert is not None and use is not None:
                    paramAdded = True

            if not paramAdded:
                logging.error("No certificate/use specified.")
                print("No certificate/use specified.")
                return -1

            # generate keystore
            keystore = []
            for certFile, certUse in zip(signerCertificateFilename, signerCertificateUse):
                if certFile is not None:
                    keystore.extend([createKeystoreKey(certFile, int(certUse)) ])

            # write to a fixed name for now
            cwd = os.getcwd()
            dir_path = os.path.dirname(os.path.realpath(__file__))
            keystore_name = 'keystore_' + str(keystoreID)
            outfile = os.path.join(cwd, keystore_name) +  '.keystore'
            hashfile= os.path.join(cwd, keystore_name) + '.sha256'

            # logging.info("Writing file '%s'" % outfile)
            print("Writing file '%s'" % outfile)
            writeKeystore(outfile, keystoreID, keystore)
            # logging.info("Writing keystore hash file '%s'" % hashfile)
            print("Writing keystore hash file '%s'" % hashfile)
            generateKeystoreHashFile(outfile, hashfile)

        # -----------------------------------------------------------------------
        # Print Keystore
        if commandline_options.get('printkeystore', None):
            foundAction = True
            logging.info("Print Keystore")

            keystoreFilename = config.get(CONFIG_SECTION, 'input_keystore')
            if keystoreFilename is None:
                logging.error("Could not load keystore %s" % keystoreFilename)
                print("Could not load keystore %s" % keystoreFilename)
                return -1

            logging.info("Keystore: %s" %  keystoreFilename)
            print("Keystore: %s" %  keystoreFilename)

            keystore_id, loadedKeystore = readKeystore(keystoreFilename)
            printKeystore(keystore_id, loadedKeystore)

        # -----------------------------------------------------------------------

        if not foundAction:
            logging.error("No action specified.")
            print("No action specified.")
            return -1

        return 0

    except KeyboardInterrupt:
        ### handle keyboard interrupt ###
        return 0
    except Exception, e:
        indent = len(program_name) * " "
        sys.stderr.write(program_name + ": " + repr(e) + "\n")
        sys.stderr.write(indent + "  for help use --help")
        return 2

if __name__ == "__main__":
    if TESTRUN:
        import doctest
        doctest.testmod()
    if PROFILE:
        import cProfile
        import pstats
        profile_filename = __programname__ + '_profile.txt'
        cProfile.run('main()', profile_filename)
        statsfile = open("profile_stats.txt", "wb")
        p = pstats.Stats(profile_filename, stream=statsfile)
        stats = p.strip_dirs().sort_stats('cumulative')
        stats.print_stats()
        statsfile.close()
        sys.exit(0)
    sys.exit(main())
