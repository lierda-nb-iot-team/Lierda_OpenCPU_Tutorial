/*
 *  Minimal configuration for TLS 1.2 with PSK and AES-CCM ciphersuites
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
/*
 * Minimal configuration for TLS 1.2 with PSK and AES-CCM ciphersuites
 * Distinguishing features:
 * - no bignum, no PK, no X509
 * - fully modern and secure (provided the pre-shared keys have high entropy)
 * - very low record overhead with CCM-8
 * - optimized for low RAM usage
 *
 * See README.txt for usage instructions.
 */
#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

/* mbed TLS feature support */
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
#define MBEDTLS_SSL_PROTO_TLS1_2
#define MBEDTLS_SSL_PROTO_DTLS

/* mbed TLS modules */
#define MBEDTLS_AES_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_MD_C
#define MBEDTLS_NET_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SSL_CLI_C
#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_SSL_DTLS_HELLO_VERIFY

/* Store the AES tables in ROM. */
#define MBEDTLS_AES_ROM_TABLES 

/* Save some RAM by adjusting to your exact needs */
#define MBEDTLS_PSK_MAX_LEN    16 /* 128-bits keys are generally enough */

/*
 * You should adjust this to the exact number of sources you're using: default
 * is the "platform_entropy_poll" source, but you may want to add other ones
 * Minimum is 2 for the entropy test suite.
 */
#define MBEDTLS_ENTROPY_MAX_SOURCES 2

/*
 * Save RAM at the expense of interoperability: do this only if you control
 * both ends of the connection!  (See comments in "mbedtls/ssl.h".)
 * The optimal size here depends on the typical size of records.
 */
/*
  calc the MBEDTLS_SSL_MAX_CONTENT_LEN by follow rule:
  the MBEDTLS_SSL_BUFFER_LEN is 1152 (udp len) = 
                MBEDTLS_SSL_MAX_CONTENT_LEN(?) 
                + MBEDTLS_SSL_COMPRESSION_ADD(0,not support) 
                + [counter + header + IV](29) 
                + MBEDTLS_SSL_MAC_ADD(32, SHA-256) 
                + MBEDTLS_SSL_PADDING_ADD(256,CBC)
*/
#define MBEDTLS_SSL_MAX_CONTENT_LEN            1347
#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH


//CBC use
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_SSL_CIPHERSUITES    MBEDTLS_TLS_PSK_WITH_AES_128_CBC_SHA256
     

/* Enable support for a limit of records with bad MAC */
#define MBEDTLS_SSL_DTLS_ANTI_REPLAY

/* Enable sending of alert messages in case of encountered errors as per RFC. */
#define MBEDTLS_SSL_ALL_ALERT_MESSAGES

#define MBEDTLS_PLATFORM_C

#define MBEDTLS_PLATFORM_MEMORY
#define MBEDTLS_PLATFORM_FREE_MACRO
#define MBEDTLS_PLATFORM_CALLOC_MACRO

#define MBEDTLS_SSL_RENEGOTIATION
#define MBEDTLS_SSL_CACHE_C  

//only for test, need modify before TR4A
#define TEST_RAND
#define TMP_ENTROPY_SOURCES

#define MBEDTLS_SSL_DTLS_ANTI_REPLAY

/* Lack of optimal padding scheme:  CMS-Padding or ISO-Padding. */
#define MBEDTLS_CIPHER_PADDING_ZEROS_AND_LEN 

#define MBEDTLS_SHA256_SMALLER

#define MBEDTLS_PKCS5_C


#define MBEDTLS_SSL_SRV_C
#define MBEDTLS_SSL_COOKIE_C


#include "check_config.h"

#endif /* MBEDTLS_CONFIG_H */
