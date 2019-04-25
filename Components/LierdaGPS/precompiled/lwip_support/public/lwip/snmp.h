/******************************************************************************
 * @brief    lwip snmp compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_SNMP_H
#define LWIP_SUPPORT_SNMP_H

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#define MIB2_INIT_NETIF(netif, type, speed)
#define MIB2_STATS_NETIF_INC(n, x)
#define MIB2_STATS_NETIF_ADD(n, x, val)

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_SNMP_H */
