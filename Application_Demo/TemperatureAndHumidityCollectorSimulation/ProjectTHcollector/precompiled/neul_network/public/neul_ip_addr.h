/******************************************************************************
 * @brief    IP addr Types for Hi21XX
 * Parts Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
/*
 * Parts Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef LIB_NEUL_IP_ADDR_H_
#define LIB_NEUL_IP_ADDR_H_

#include "neulfw.h"
#include "neul_network_defs.h"
#include "neul_ip_addr_ip4.h"
#include "neul_ip_addr_ip6.h"
#include "neul_ip_addr_etypes.h"

/** @defgroup libNEUL_IPNETWORK Hi21XX libNEUL Network IP Functions
 * Hi21XX libNeulNetwork IP functions
 * @ingroup LIBNEUL
 * @{
 * */

/** These are the values for ip_addr_t.type */
#define IPADDR_TYPE_V4                0U
#define IPADDR_TYPE_V6                6U
#define IPADDR_TYPE_ANY               46U

#define IP_SET_TYPE_VAL(ipaddr, iptype) do { (ipaddr).type = (iptype); }while(0)
/*lint -emacro(506, IP_SET_TYPE)*/
#define IP_SET_TYPE(ipaddr, iptype)     do { if((ipaddr) != NULL) { IP_SET_TYPE_VAL(*(ipaddr), iptype); }}while(0)
#define IP_GET_TYPE(ipaddr)           ((ipaddr)->type)
#define IP_IS_V4_VAL(ipaddr)          (IP_GET_TYPE(&ipaddr) == IPADDR_TYPE_V4)
#define IP_IS_V6_VAL(ipaddr)          (IP_GET_TYPE(&ipaddr) == IPADDR_TYPE_V6)
#define IP_IS_V4(ipaddr)              (((ipaddr) == NULL) || IP_IS_V4_VAL(*(ipaddr)))
#define IP_IS_V6(ipaddr)              (((ipaddr) != NULL) && IP_IS_V6_VAL(*(ipaddr)))


/* Convert generic ip address to specific protocol version */
#define ip_2_ip6(ipaddr)   (&((ipaddr)->u_addr.ip6))
#define ip_2_ip4(ipaddr)   (&((ipaddr)->u_addr.ip4))

#define ipaddr_ntoa(addr)   (((addr) == NULL) ? "NULL" : \
  ((IP_IS_V6(addr)) ? ip6addr_ntoa(ip_2_ip6(addr)) : ip4addr_ntoa(ip_2_ip4(addr))))

#define ip_addr_set_any(is_ipv6, ipaddr)      do{if(is_ipv6){ \
  ip6_addr_set_any(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V6); }else{ \
  ip4_addr_set_any(ip_2_ip4(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V4); }}while(0) //lint !e774

#define ip_addr_copy(dest, src)      do{ IP_SET_TYPE_VAL(dest, IP_GET_TYPE(&src)); if(IP_IS_V6_VAL(src)){ \
  ip6_addr_copy(*ip_2_ip6(&(dest)), *ip_2_ip6(&(src))); }else{ \
  ip4_addr_copy(*ip_2_ip4(&(dest)), *ip_2_ip4(&(src))); }}while(0)

/*lint -emacro(506, ip_addr_set_any)*/
#define ip_addr_set_any(is_ipv6, ipaddr)      do{if(is_ipv6){ \
  ip6_addr_set_any(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V6); }else{ \
  ip4_addr_set_any(ip_2_ip4(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V4); }}while(0)

#define ip_addr_cmp(addr1, addr2)    ((IP_GET_TYPE(addr1) != IP_GET_TYPE(addr2)) ? 0 : (IP_IS_V6_VAL(*(addr1)) ? \
  ip6_addr_cmp(ip_2_ip6(addr1), ip_2_ip6(addr2)) : \
  ip4_addr_cmp(ip_2_ip4(addr1), ip_2_ip4(addr2))))

#define ip_addr_isany(ipaddr)        ((IP_IS_V6(ipaddr)) ? \
  ip6_addr_isany(ip_2_ip6(ipaddr)) : \
  ip4_addr_isany(ip_2_ip4(ipaddr)))

#define ip_addr_ismulticast(ipaddr)  ((IP_IS_V6(ipaddr)) ? \
  ip6_addr_ismulticast(ip_2_ip6(ipaddr)) : \
  ip4_addr_ismulticast(ip_2_ip4(ipaddr)))

#define ip_addr_set_ip4_u32(ipaddr, val)  do{if(ipaddr){ip4_addr_set_u32(ip_2_ip4(ipaddr), val); \
  IP_SET_TYPE(ipaddr, IPADDR_TYPE_V4); }}while(0)

#define ip_addr_get_ip4_u32(ipaddr)  (((ipaddr) && IP_IS_V4(ipaddr)) ? \
  ip4_addr_get_u32(ip_2_ip4(ipaddr)) : 0)

#define ip_addr_set_zero(ipaddr)     do{ \
  ip6_addr_set_zero(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, 0); }while(0)
#define ip_addr_set_zero_ip4(ipaddr)     do{ \
  ip6_addr_set_zero(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V4); }while(0)
#define ip_addr_set_zero_ip6(ipaddr)     do{ \
  ip6_addr_set_zero(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V6); }while(0)

int ipaddr_aton(const char *cp, ip_addr_t *addr);



extern const ip_addr_t ip_addr_any;
extern const ip_addr_t ip_addr_broadcast;

/**
 * @ingroup ip4addr
 * Can be used as a fixed/const ip_addr_t
 * for the IP wildcard.
 * Defined to @ref IP4_ADDR_ANY when IPv4 is enabled.
 * Defined to @ref IP6_ADDR_ANY in IPv6 only systems.
 * Use this if you can handle IPv4 _AND_ IPv6 addresses.
 * Use @ref IP4_ADDR_ANY or @ref IP6_ADDR_ANY when the IP
 * type matters.
 */
#define IP_ADDR_ANY         IP4_ADDR_ANY

/**
 * @ingroup ip4addr
 * Can be used as a fixed/const ip4_addr_t
 * for the wildcard and the broadcast address
 */
#define IP4_ADDR_ANY4       (ip_2_ip4(&ip_addr_any))

/** @ingroup ip4addr */
#define IP_ADDR_BROADCAST   (&ip_addr_broadcast)

/** @ingroup ip4addr */
#define IP4_ADDR_BROADCAST  (ip_2_ip4(&ip_addr_broadcast))

/** Copy IP address - faster than ip4_addr_set: no NULL check */
#define ip4_addr_copy(dest, src) ((dest).addr = (src).addr)

/** @} end of group libNEUL_IPNETWORK */

#endif /* LIB_NEUL_IP_ADDR_H_ */
