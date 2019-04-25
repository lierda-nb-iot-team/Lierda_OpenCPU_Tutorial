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

#ifndef LIB_NEUL_IP_ADDR_V4_H_
#define LIB_NEUL_IP_ADDR_V4_H_

#include "neulfw.h"
#include "neul_network_defs.h"
#include "neul_ip_addr_ip4_etypes.h"

/** @addtogroup libNEUL_IPNETWORK
 * @{
 * */

#define IP4ADDR_STRLEN_MAX  16
/** 255.255.255.255 */
#define IPADDR_NONE         ((uint32)0xffffffffUL)
/** 127.0.0.1 */
#define IPADDR_LOOPBACK     ((uint32)0x7f000001UL)
/** 0.0.0.0 */
#define IPADDR_ANY          ((uint32)0x00000000UL)
/** 255.255.255.255 */
#define IPADDR_BROADCAST    ((uint32)0xffffffffUL)

#define ip4_addr_get_u32(src_ipaddr) ((src_ipaddr)->addr)

#define ip4_addr_set_any(ipaddr)      ((ipaddr)->addr = IPADDR_ANY)

char *ip4addr_ntoa(const ip4_addr_t *addr);
char*ip4addr_ntoa_r(const ip4_addr_t *addr, char *buf, int buflen);

/** MEMCPY-like copying of IP addresses where addresses are known to be
 * 16-bit-aligned if the port is correctly configured (so a port could define
 * this to copying 2 u16_t's) - no NULL-pointer-checking needed. */
#ifndef IPADDR2_COPY
#define IPADDR2_COPY(dest, src) SMEMCPY(dest, src, sizeof(ip4_addr_t))
#endif

/** Copy IP address - faster than ip4_addr_set: no NULL check */
#define ip4_addr_copy(dest, src) ((dest).addr = (src).addr)
/** Safely copy one IP address to another (src may be NULL) */
#define ip4_addr_set(dest, src) ((dest)->addr = \
                                    ((src) == NULL ? 0 : \
                                    (src)->addr))

/** IPv4 only: set the IP address given as an uint32 */
#define ip4_addr_set_u32(dest_ipaddr, src_u32) ((dest_ipaddr)->addr = (src_u32))
/** IPv4 only: get the IP address as an uint32 */
#define ip4_addr_get_u32(src_ipaddr) ((src_ipaddr)->addr)

#define ip4_addr_cmp(addr1, addr2) ((addr1)->addr == (addr2)->addr)

#define ip4_addr_ismulticast(addr1) (((addr1)->addr & htonl(0xf0000000UL)) == htonl(0xe0000000UL))

#define ip4_addr_isany_val(addr1)   ((addr1).addr == IPADDR_ANY)
#define ip4_addr_isany(addr1) ((addr1) == NULL || ip4_addr_isany_val(*(addr1)))

int ip4addr_aton(const char *cp, ip4_addr_t *addr);

// added for PPP */
#define IP_CLASSA_NSHIFT    24
#define IP_LOOPBACKNET      127                 /* official! */

#define IP_CLASSD(a)        (((u32_t)(a) & 0xf0000000UL) == 0xe0000000UL)
#define IP_CLASSD_NET       0xf0000000          /* These ones aren't really */
#define IP_CLASSD_NSHIFT    28                  /*   net and host fields, but */
#define IP_CLASSD_HOST      0x0fffffff          /*   routing needn't know. */
#define IP_MULTICAST(a)     IP_CLASSD(a)

#define IP_BADCLASS(a)      (((u32_t)(a) & 0xf0000000UL) == 0xf0000000UL)


/** @} end of group libNEUL_IPNETWORK */

#endif /* LIB_NEUL_IP_ADDR_V4_H_ */
