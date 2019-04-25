/******************************************************************************
 * @brief    lwip debug compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_DEBUG_H
#define LWIP_SUPPORT_DEBUG_H

#include "neulfw.h"
#include "lwip/arch.h"
#include "lwip/opt.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#define LWIP_DBG_ON            0x80U
#define LWIP_DBG_OFF           0x00U

#define LWIP_DBG_LEVEL_ALL     0x00
#define LWIP_DBG_LEVEL_WARNING 0x01
#define LWIP_DBG_LEVEL_SERIOUS 0x02
#define LWIP_DBG_LEVEL_SEVERE  0x03

#define LWIP_DBG_TRACE         0x40U
#define LWIP_DBG_STATE         0x20U
#define LWIP_DBG_FRESH         0x10U
#define LWIP_DBG_HALT          0x08U

#define LWIP_DBG_MASK_LEVEL    0x03

#ifndef LWIP_NOASSERT
#include "assert.h"
#define LWIP_ASSERT(message, assertion) assert(assertion)
#else   /* LWIP_NOASSERT */
#define LWIP_ASSERT(message, assertion)
#endif  /* LWIP_NOASSERT */

#ifndef LWIP_NOASSERT
#define LWIP_PLATFORM_ERROR(message) LWIP_PLATFORM_ASSERT(message)
#elif defined LWIP_DEBUG
#define LWIP_PLATFORM_ERROR(message) LWIP_PLATFORM_DIAG((message))
#else
#define LWIP_PLATFORM_ERROR(message)
#endif

#define LWIP_ERROR(message, expression, handler) do { if (!(expression)) { \
    LWIP_PLATFORM_ERROR(message); handler;}} while(0)

#ifdef LWIP_DEBUG
#define LWIP_DEBUGF(debug, message) do { \
                               if ( \
                                   ((debug) & LWIP_DBG_ON) && \
                                   ((debug) & LWIP_DBG_TYPES_ON) && \
                                   ((s16_t)((debug) & LWIP_DBG_MASK_LEVEL) >= LWIP_DBG_MIN_LEVEL)) { \
                                 LWIP_PLATFORM_DIAG(message); \
                                 if ((debug) & LWIP_DBG_HALT) { \
                                   while(1); \
                                 } \
                               } \
                             } while(0)

#else
#define LWIP_DEBUGF(debug, message)
#endif  // LWIP_DEBUG

/** @} end of group LWIP_SUPPORT */

#endif // LWIP_SUPPORT_DEBUG_H
