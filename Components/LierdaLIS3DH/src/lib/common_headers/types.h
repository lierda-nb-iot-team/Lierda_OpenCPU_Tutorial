/****************************************************************************
FILE
    types.h  -  common typedefs for the machine

DESCRIPTION
    This should be #included by every C source file for the target.
    This file holds machine-specific #defines.

    This file should be changed only infrequently and with great care.

    This file should contain the minimum necessary to get the job done.
 * Copyright (c) 2015 NEUL LIMITED
*/


#ifndef __TYPES_H
#define __TYPES_H

#ifndef NEULFW_H
#error "Please include types.h via neulfw.h"
#endif

/** @addtogroup COMMON_TYPES
 * @{
 * */

/* Get bool, true and false.
 * If using GCC then get stdbool, otherwise create definitions here,
 */
#if defined(__GNUC__) || defined(C99)
#include <stdbool.h>
/* Make true and false actual booleans, not ints, to avoid Lint moaning. GCC defines them as ints. */
#ifdef true
#undef true
#endif
#ifdef false
#undef false
#endif
#define true ((bool) 1)
#define false ((bool) 0)
#elif defined(__cplusplus)
/* bool is already defined in C++ */
#else
#define true 1
#define false 0
typedef int bool;
#endif
// Use meaningful names when bool used for success/failure, e.g. for function returns.
#define SUCCESS true
#define FAILURE false

typedef signed char             int8;
typedef short                   int16;
typedef long                    int32;
typedef long long               int64;

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned long           uint32;
typedef unsigned long long      uint64;

#define MAX_UINT8  0xFF
#define MAX_UINT16 0xFFFF
#define MAX_UINT32 0xFFFFFFFF
#define MAX_UINT64 0xFFFFFFFFFFFFFFFFULL
#define MIN_INT16  (-0x8000)
#define MAX_INT16  (0x7FFF)

/** Integer type big enough to hold a data pointer. */
typedef unsigned int            uintptr;


typedef void (*CONST_VOID_PTR__UINT16__ACTION)(const void *, uint16);

/** @} end of group COMMON_TYPES */



/** @addtogroup ETYPES MACROS
 * @{
 * */

#define ETYPES_ENUM_HOLDER_TYPE(y)

#define ETYPES_ASCII          char

/** @} end of group COMMON_TYPES */

#endif
