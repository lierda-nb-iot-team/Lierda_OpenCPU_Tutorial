/******************************************************************************
 * @brief    lwip arch compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LWIP_SUPPORT_ARCH_H
#define LWIP_SUPPORT_ARCH_H

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#define LITTLE_ENDIAN 1234

#include "arch/cc.h"

/**
 *  Typedefs for the types used by lwip -
 *    u8_t, s8_t, u16_t, s16_t, u32_t, s32_t, mem_ptr_t
 */
typedef uint8           u8_t;
typedef uint16          u16_t;
typedef uint32          u32_t;
typedef int8            s8_t;
typedef int16           s16_t;
typedef int32           s32_t;
typedef unsigned long   mem_ptr_t;

/** LWIP memory alignment macros
 */
#define LWIP_MEM_ALIGN_BUFFER(size) (((size) + MEM_ALIGNMENT - 1U))
#define LWIP_MEM_ALIGN(addr)        ((void *)(((mem_ptr_t)(addr) + MEM_ALIGNMENT - 1) & ~(mem_ptr_t)(MEM_ALIGNMENT-1)))
#define LWIP_MEM_ALIGN_SIZE(size)   (((size) + MEM_ALIGNMENT - 1U) & ~(MEM_ALIGNMENT-1U))

/* LWIP useful Macros
 */
#define LWIP_UNUSED_ARG(x)          UNUSED(x)

#ifdef __DOXYGEN__
#define PACK_STRUCT_USE_INCLUDES
#endif

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_ARCH_H */
