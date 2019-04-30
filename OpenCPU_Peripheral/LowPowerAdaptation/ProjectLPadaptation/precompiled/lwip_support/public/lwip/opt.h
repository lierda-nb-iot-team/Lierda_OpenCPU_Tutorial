/******************************************************************************
 * @brief    lwip opt compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#if !defined LWIP_SUPPORT_OPT_H
#define LWIP_SUPPORT_OPT_H

/*
 * Include user defined options first. Anything not defined in these files
 * will be set to standard values. Override anything you don't like!
 */
#include "neulfw.h"
#include "lwipopts.h"
#include "lwip/debug.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#if !defined LWIP_PERF || defined __DOXYGEN__
#define LWIP_PERF                       0
#endif

#if !defined PBUF_LINK_ENCAPSULATION_HLEN || defined __DOXYGEN__
#define PBUF_LINK_ENCAPSULATION_HLEN    0u
#endif

#if !defined PBUF_POOL_BUFSIZE || defined __DOXYGEN__
#define PBUF_POOL_BUFSIZE               LWIP_MEM_ALIGN_SIZE(TCP_MSS+40+PBUF_LINK_ENCAPSULATION_HLEN+PBUF_LINK_HLEN)
#endif

#if !defined LWIP_TCP || defined __DOXYGEN__
#define LWIP_TCP                        1
#endif

#if !defined PBUF_DEBUG || defined __DOXYGEN__
#define PBUF_DEBUG                      LWIP_DBG_OFF
#endif

#if !defined LWIP_DBG_TYPES_ON || defined __DOXYGEN__
#define LWIP_DBG_TYPES_ON               LWIP_DBG_ON
#endif

#if !defined LWIP_DNS || defined __DOXYGEN__
#define LWIP_DNS                        0
#endif

#if !defined LWIP_DBG_MIN_LEVEL || defined __DOXYGEN__
#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_ALL
#endif

#if !defined LWIP_NETIF_HWADDRHINT || defined __DOXYGEN__
#define LWIP_NETIF_HWADDRHINT           0
#endif

#if !defined MEMCPY || defined __DOXYGEN__
#define MEMCPY(dst,src,len)             memcpy(dst,src,len)
#endif

#if !defined LWIP_TIMERS || defined __DOXYGEN__
#define LWIP_TIMERS                     1
#endif

#if !defined LWIP_TIMERS_CUSTOM || defined __DOXYGEN__
#define LWIP_TIMERS_CUSTOM              0
#endif

#if !defined NO_SYS || defined __DOXYGEN__
#define NO_SYS                          0
#endif

#if !defined SYS_DEBUG || defined __DOXYGEN__
#define SYS_DEBUG                       LWIP_DBG_OFF
#endif

#if !defined IP_DEFAULT_TTL || defined __DOXYGEN__
#define IP_DEFAULT_TTL                  255
#endif

#if !defined UDP_TTL || defined __DOXYGEN__
#define UDP_TTL                         (IP_DEFAULT_TTL)
#endif

#if !defined LWIP_MPU_COMPATIBLE || defined __DOXYGEN__
#define LWIP_MPU_COMPATIBLE             0
#endif

#if !defined IP_FORWARD || defined __DOXYGEN__
#define IP_FORWARD                      0
#endif

#if !defined LWIP_IPV6_FORWARD || defined __DOXYGEN__
#define LWIP_IPV6_FORWARD               0
#endif

#define LINK_STATS                      0

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_OPT_H */
