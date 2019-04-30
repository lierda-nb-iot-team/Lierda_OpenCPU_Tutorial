/******************************************************************************
 * @brief    lwip ip4 compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_IP4_H_
#define LWIP_SUPPORT_IP4_H_
// required for build inclusion references

#include "lwip/pbuf.h"
#include "lwip/netif.h"
#include "lwip/err.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

struct ip4_addr_packed {
  u32_t addr;
} PACK_STRUCT_STRUCT;

typedef struct ip4_addr_packed ip4_addr_p_t;

#define IP_OFFMASK  0x1fffU

struct ip_hdr {
  u8_t          _v_hl;
  u8_t          _tos;
  u16_t         _len;
  u16_t         _id;
  u16_t         _offset;
  u8_t          _ttl;
  u8_t          _proto;
  u16_t         _chksum;
  ip4_addr_p_t  src;
  ip4_addr_p_t   dest;
} PACK_STRUCT_STRUCT;

#define IPH_HL(hdr) ((hdr)->_v_hl & 0x0f)
#define IPH_LEN(hdr) ((hdr)->_len)
#define IPH_ID(hdr) ((hdr)->_id)
#define IPH_OFFSET(hdr) ((hdr)->_offset)
#define IPH_PROTO(hdr) ((hdr)->_proto)
#define IPH_CHKSUM(hdr) ((hdr)->_chksum)

#define IPH_LEN_SET(hdr, len) (hdr)->_len = (len)
#define IPH_ID_SET(hdr, id) (hdr)->_id = (id)
#define IPH_PROTO_SET(hdr, proto) (hdr)->_proto = (u8_t)(proto)
#define IPH_CHKSUM_SET(hdr, chksum) (hdr)->_chksum = (chksum)

err_t ip4_input(struct pbuf *p, struct netif *inp);

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_IP4_H_ */
