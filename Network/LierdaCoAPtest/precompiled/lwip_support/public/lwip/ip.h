/******************************************************************************
 * @brief    lwip ip compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_IP_H_
#define LWIP_SUPPORT_IP_H_

#include "lwip/opt.h"

#include "lwip/def.h"
#include "lwip/pbuf.h"
#include "lwip/ip_addr.h"
#include "lwip/err.h"
#include "lwip/netif.h"
#include "lwip/ip4.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#define IP_PROTO_TCP     6

#define IP_PCB_ADDRHINT

#define IP_PCB \
    ip_addr_t local_ip;    \
    ip_addr_t remote_ip;   \
    u8_t so_options;       \
    u8_t tos;              \
    u8_t ttl               \
    IP_PCB_ADDRHINT

struct ip_pcb {
  IP_PCB;
};

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_IP_H_ */


