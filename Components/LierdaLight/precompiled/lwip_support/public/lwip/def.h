/******************************************************************************
 * @brief    lwip defs compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_DEF_H
#define LWIP_SUPPORT_DEF_H

#include "neul_network_defs.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#define LWIP_MAX(x , y)     (((x) > (y)) ? (x) : (y))
#define LWIP_MIN(x , y)     (((x) < (y)) ? (x) : (y))

#define PP_HTONS(x)         htons(x)
#define PP_NTOHS(x)         PP_HTONS(x)
#define PP_HTONL(x)         htonl(x)
#define PP_NTOHL(x)         PP_HTONL(x)

#define lwip_htons(x)       PP_HTONS(x)
#define lwip_ntohl(x)       lwip_htonl(x)
#define lwip_ntohs(x)       lwip_htons(x)
#define lwip_htonl(x)       htonl(x)

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_DEF_H */
