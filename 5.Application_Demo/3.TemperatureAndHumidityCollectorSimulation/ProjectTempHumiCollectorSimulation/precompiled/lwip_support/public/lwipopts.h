/******************************************************************************
 * @brief    lwip options
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIPOPTS_H_
#define LWIPOPTS_H_

/** @defgroup LWIP_SUPPORT Hi21XX libNEUL LWIP Compatibility
 * Hi21XX LWIP Compatibility
 * @ingroup LIBNEUL
 * @{
 * */

/** See LWIP 2.0.3 lwipopts.h file for details.
 * This file contains the define required to build specific LWIP modules and Third-Party code that is dependent on LWIP
 */

// Defines explicitly set
#define LWIP_IPV4                       1

#define LWIP_IPV6                       0

#define LWIP_NETIF_API                  0

#define LWIP_TIMERS 1

#define LWIP_TIMERS_CUSTOM 0

#define LWIP_DEBUG

#define LWIP_TIMERS 1

#define LWIP_TIMERS_CUSTOM 0

#define LWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS 1



// defines required but unchanged from LWIP defaults
#define MEMP_NUM_NETCONN                20

#define LWIP_RAW                        0

#define LWIP_NETIF_HOSTNAME             1

#define SYS_LIGHTWEIGHT_PROT            1

#define ETH_PAD_SIZE                    0

#define PBUF_LINK_HLEN                  (0 + ETH_PAD_SIZE)

#define LWIP_DHCP                       0

#define LWIP_AUTOIP                     0

#define LWIP_DHCP_AUTOIP_COOP           0

#define LWIP_DHCP_AUTOIP_COOP_TRIES     2

#define MEM_ALIGNMENT                   4

#define LWIP_IGMP                       0

#define LWIP_NETBUF_RECVINFO            1

#define TCPIP_THREAD_NAME              "TCPIP Stack"

#define TCPIP_THREAD_STACKSIZE          1000

#define TCPIP_THREAD_PRIO               2

#define TCPIP_MBOX_SIZE                 20

#define DEFAULT_UDP_RECVMBOX_SIZE       10

#define DEFAULT_TCP_RECVMBOX_SIZE       20

#define DEFAULT_ACCEPTMBOX_SIZE         10

#define TCP_MSS                         1460

#define TCP_SND_BUF                     (16 * TCP_MSS)

#define TCP_WND                         (16 * TCP_MSS)

#define LWIP_NETIF_STATUS_CALLBACK      1

#define LWIP_NETIF_LINK_CALLBACK        1

#define MEMP_NUM_TCP_SEG                64

#define MEM_LIBC_MALLOC                 1

#define MEMP_MEM_MALLOC                 1

#define LWIP_COMPAT_SOCKETS             0

#define LWIP_POSIX_SOCKETS_IO_NAMES     0

#define LWIP_SO_RCVTIMEO                1

#define LWIP_TCP_KEEPALIVE              1

#define IP_SOF_BROADCAST                1

#define IP_SOF_BROADCAST_RECV           1

#define LWIP_STATS                      0

#define LWIP_STATS_LARGE                0

#define LWIP_DHCP_BOOTP_FILE            0

#define DHCP_OPTIONS_LEN                (DHCP_MIN_OPTIONS_LEN + 63)

/** @} end of group LWIP_SUPPORT */

#endif /* LWIPOPTS_H_ */
