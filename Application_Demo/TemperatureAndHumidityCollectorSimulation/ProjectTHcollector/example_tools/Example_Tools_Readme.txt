/******************************************************************************
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
 ******************************************************************************/
 
 Example Tools
 =============
 
 This directory contains example tools that demonstrate functionality to enable the development of bespoke solutions. 
 They are not provided as production-ready tooling.
 
 GenerateKeystore.py
 -------------------
 
 Function: Generate and print keystores for Secure Boot
 
 Examples:
    GenerateKeystore.py -printkeystore -iks keystore_1.keystore
    GenerateKeystore.py -createkeystore -ksid 1 -cert1 appsa_root_cert_rsa4096.der -use1 4
    
Implementation Language: 
    Python 2.7

Requirements:
    The following python packages may need to be installed to enable GenerateKeystore.py to operate. 
        asn1crypto-0.22.0-py2.py3-none-any.whl
        cffi-1.10.0-cp27-cp27m-win32.whl
        crypto_modules_python27.rar
        cryptography-1.9-cp27-cp27m-win32.whl
        enum34-1.1.6-py2-none-any.whl
        idna-2.5-py2.py3-none-any.whl
        ipaddress-1.0.18-py2-none-any.whl
        pip-9.0.1-py2.py3-none-any.whl
        pycparser-2.18.tar.gz
        python-crypto-pip-six.rar
        six-1.10.0-py2.py3-none-any.whl
