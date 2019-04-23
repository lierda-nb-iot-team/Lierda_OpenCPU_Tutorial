/******************************************************************************
 * @brief    lwip mem compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LWIP_SUPPORT_MEM_H
#define LWIP_SUPPORT_MEM_H

#include "lwip/opt.h"
#include "lwip/arch.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#define mem_free   irfree
#define mem_malloc irzalloc

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_MEM_H */
