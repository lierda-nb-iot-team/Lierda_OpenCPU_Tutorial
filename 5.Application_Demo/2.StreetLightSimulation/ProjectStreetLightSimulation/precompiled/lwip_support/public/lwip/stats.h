/******************************************************************************
 * @brief    lwip stats compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_STATS_H
#define LWIP_SUPPORT_STATS_H

#include "lwip/opt.h"
#include "lwip/memp.h"  // lwip pppapi.c doesn't include this directly

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#define LINK_STATS_INC(x)

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_STATS_H */
