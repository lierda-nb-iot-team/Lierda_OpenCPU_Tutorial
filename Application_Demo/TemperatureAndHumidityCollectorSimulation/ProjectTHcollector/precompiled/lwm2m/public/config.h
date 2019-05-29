/* config.h. generated from config.h.in by configure.*/
/* config.h.in. Generated from configure.in by autoheader. */

/* Define when building universal (internal helper macro) */
/* Undefine AC_APPLE_UNIVERSAL_BUILD */

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the <assert.h> header file. */
#define HAVE_ASSERT_H 1

/* Define to 1 if you have the 'getaddrinfo' function. */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 when you have the 'coap' library (-lcoap). */
/*  HAVE_LIBCOAP */

/* Define to 1 if you have the <limmits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the 'MEMSET_S' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 0

/* Define to 1 if you have the 'select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the 'socket' function. */
#define HAVE_SOCKET 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the 'strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strnlen' function. */
#define HAVE_STRNLEN 1

/* Define to 1 if you have the 'strrchr' function. */
#define HAVE_STRRCHR 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/unistd.h> header file. */
//#define HAVE_SYS_UNISTD_H 1

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define to 1 if you have the <unistd.h> header file. */
//#define HAVE_UNISTD_H 1

/* Define to the address where bug reports for this package should be sent */
//#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package */
//#define PACKAGE_NAME "libcoap"

/* Define to the full name and version of this package */
//#define PACKAGE_STRING "VPP2.0 V100R001C00B020"

/* Define to the one symbol short name of this package */
#define PACKAGE_TARNAME "libcoap"

/* Define to the home page of this package */
//#define PACKAGE_URL ""

/* Define to the version of this package */
//#define PACKAGE_VERSION "4.0.3"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you have the UIO header files. */
#define HAVE_SYS_UIO_H 1



/* Define WORDS_BIGENDIAN to 1 when your processor stores words with the most
   significant byte first like Motorola and SPARC, unlike Intel. */
#if defined AC_APPLE_UNIVERSAL_BUILD
#if defined __BIG_ENDIAN__
#define WORDS_BIGENDIAN 1
#endif
#else
#ifndef WORDS_BIGENDIAN
/* #    undef WORDS_BIGENDIAN */
#endif
#endif

//#define COAP_MAX_PDU_SIZE 900

/* enable dtls */
// coap_WITH_DTLS 0

/* enable observe s*/
#define ENABLE_OBSERVE 1

#define COAP_CONF_MAX_OPT 1023

/* Define to 'unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to 'int' if <sys/types.h> does not define. */
/* #undef ssize_t */

/* enable dtls */
//#define COAP_WITH_DYLS 1
