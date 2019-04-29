/******************************************************************************
 * @brief    lwip tcp_priv compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_PRIV_TCP_PRIV_H
#define LWIP_SUPPORT_PRIV_TCP_PRIV_H

#include "lwip/opt.h"
#include "lwip/arch.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

struct tcp_hdr {
  u16_t src;
  u16_t dest;
  u32_t seqno;
  u32_t ackno;
  u16_t _hdrlen_rsvd_flags;
  u16_t wnd;
  u16_t chksum;
  u16_t urgp;
} PACK_STRUCT_STRUCT;

/* TCP header flags  */
#define TCP_FIN 0x01U
#define TCP_SYN 0x02U
#define TCP_RST 0x04U
#define TCP_PSH 0x08U
#define TCP_ACK 0x10U
#define TCP_URG 0x20U

/* TCP header flag mask */
#define TCP_FLAGS 0x3fU

#define TCPH_HDRLEN(phdr)               ((u16_t)(lwip_ntohs((phdr)->_hdrlen_rsvd_flags) >> 12))
#define TCPH_FLAGS(phdr)                ((u16_t)(lwip_ntohs((phdr)->_hdrlen_rsvd_flags) & TCP_FLAGS))
#define TCPH_SET_FLAG(phdr, flags )     (phdr)->_hdrlen_rsvd_flags = ((phdr)->_hdrlen_rsvd_flags | lwip_htons(flags))
#define TCPH_UNSET_FLAG(phdr, flags)    (phdr)->_hdrlen_rsvd_flags = ((phdr)->_hdrlen_rsvd_flags & ~lwip_htons(flags))

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_PRIV_TCP_PRIV_H */
