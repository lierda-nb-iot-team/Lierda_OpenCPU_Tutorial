/******************************************************************************
 * @brief    NEUL IP ADDR ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef ETYPES_SHARED_AP_NEUL_IP_ADDR_ETYPES_H_
#define ETYPES_SHARED_AP_NEUL_IP_ADDR_ETYPES_H_

#include "neul_ip_addr_ip4_etypes.h"
#include "neul_ip_addr_ip6_etypes.h"

/** @addtogroup libNEUL_IPNETWORK
 * @{
 * */


typedef union
{
    ip6_addr_t ip6;
    ip4_addr_t ip4;
}
u_addr_u;

typedef struct
{
    u_addr_u u_addr;
    uint8 type;
}
ip_addr_t;

/** @} end of group libNEUL_IPNETWORK */


#endif /* ETYPES_SHARED_AP_NEUL_IP_ADDR_ETYPES_H_ */
