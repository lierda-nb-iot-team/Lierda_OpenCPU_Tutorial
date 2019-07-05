/******************************************************************************
 * @brief    Socket Types for Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_SOCKET_TYPES_H_
#define LIB_NEUL_SOCKET_TYPES_H_

/** @addtogroup libNEUL_SOCKET
 * @{
 * */

/* 
 * socket error codes 
 */
#define NEUL_SOCKET_RET_OK                           0
#define NEUL_SOCKET_RET_ERROR                       -1
#define NEUL_SOCKET_RET_FLOWCONTROL                 -2
#define NEUL_SOCKET_RET_DATA_SEQUENCE_REPEAT_ERROR  -3
#define NEUL_SOCKET_RET_NO_NETWORK_SERVICE          -4


/**
 * Maximum number of sockets supported
 */
#define NUM_SOCKETS 7

#define FLOWCONTROL_ENABLED 1
#define FLOWCONTROL_DISABLED 0

/**
 * Socket interfaces aligned to BSD sockets
 */
typedef int32 ssize_t;
 
/**
 * Protocol family. Will always be one of these two
 */
typedef enum {
    AF_INET = 2,
    AF_INET6 = 10
} PROTOCOL_FAMILY;

/**
 * Protocol. UDP/TCP supported.
 */
typedef enum {
    ICMP = 1,
    TCP = 6,
    UDP = 17,
    RAW = 255
} PROTOCOL_TYPE;

/**
 * Socket type.
 */
typedef enum {
    SOCK_NONE=0,
    SOCK_STREAM=1,
    SOCK_DGRAM=2,
    SOCK_RAW=3
} SOCKET_TYPE;

/**
 * Message Flags
 * Forced enumeration values to enable or of multiple flags.
 */
typedef enum {
    MSG_NORMAL      = 0,
    MSG_NEXCEPTION  = 0x100,
    MSG_NRELEASE    = 0x200,
    MSG_NRELEASE_AFTER_REPLY    = 0x400,
    MSG_NNO_DATA_STATUS = 0x800
} SOCK_MSG_FLAG;

/**
 * Socket status
 * Indicate the socket status updated
 */
typedef enum
{
    TCP_CONNECTED,
    TCP_SENT,
    TCP_RECV,
    TCP_ERR,
    TCP_CONNECTION_CLOSED,         // Close by protocol stack when server close the connection
    SOCKET_CLOSE_PASSIVE,          // Close by protocol stack when error happened
    SOCKET_CLOSE_PROACTIVE,        // Close by user
    SOCKET_DATA_DROPPED            // Apps cache full, DL data dropped
} SOCKET_STATUS;

/**
 * length of socket. IPv4 & IPv6 sockaddr have different lengths, so is always passed in as sizeof() the sockadd passed in.
 */
typedef uint8   socklen_t;

/**
 * standard sockaddr for casting
 */
struct sockaddr {
    PROTOCOL_TYPE    sa_family;         // address family, e.g. AF_INET, AF_INET6
    char             sa_data[14];       // sockadder specific data
};

/**
 * IPv4 AF_INET socket
 */
struct in_addr {
    uint32           s_addr;            // load with inet_aton() or inet_pton()
};

/**
 * IPv6 AF_INET6 socket 14 bytes + PROTOCOL_TYPE
 */
struct in6_addr {
    unsigned char    s6_addr[16];       // load with inet_pton()
};


/**
 * IPv4 sockaddr
 */
struct sockaddr_in {
    PROTOCOL_FAMILY   sin_family;       // e.g. AF_INET, AF_INET6
    uint16            sin_port;         // port, Network Byte Order
    ip_addr_t         sin_addr;              // struct in_addr,
};

/**
 * IPv6 sockaddr
 */
struct sockaddr_in6 {
    PROTOCOL_FAMILY  sin6_family;       // address family, e.g. AF_INET, AF_INET6
    uint16           sin6_port;         // port number, Network Byte Order
    uint32           sin6_flowinfo;     // IPv6 flow information
    struct in6_addr  sin6_addr;         // struct in6_addr
    uint32           sin6_scope_id;     // scope id
};

/**
 * sockaddr_storage - big enough for any sockaddr we support
 */
struct sockaddr_storage {
    PROTOCOL_FAMILY  ss_family;         // e.g. AF_INET, AF_INET6
    char             __ss_padding[sizeof(struct sockaddr_in6)-sizeof(PROTOCOL_TYPE)];
};

/** @} end of group libNEUL_SOCKET */

#endif /* LIB_NEUL_TYPES_H_ */
