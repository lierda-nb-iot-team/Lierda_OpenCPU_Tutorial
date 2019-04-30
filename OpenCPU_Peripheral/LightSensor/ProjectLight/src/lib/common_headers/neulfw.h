/****************************************************************************
FILE
    neulfw.h  -  common header neul firmware

DESCRIPTION
    This should be #included by every C source file on neul radio dev board.

    This file should be changed only infrequently and with great care.

    This file should contain the minimum necessary to get the job done.
 * Copyright (c) 2015 NEUL LIMITED
*/

#ifndef NEULFW_H
#define NEULFW_H

/** @defgroup COMMON_TYPES Hi21XX Common Types
 * Hi21XX Common Types
 * @ingroup Hi21XX_Base
 * @{
 * */


#if defined(COMPILE_FOR_DSL)
#include "etypes.h"
#define CASSERT(predicate, file)
#else

/* Create a define specifying the version of C we are compiling against */
#if defined(__STDC__)
#define C89
#if defined(__STDC_VERSION__)
#define C90
#if (__STDC_VERSION__ >= 199409L)
#define C94
#endif // (__STDC_VERSION__ >= 199409L)
#if (__STDC_VERSION__ >= 199901L)
#define C99
#endif // (__STDC_VERSION__ >= 199901L)
#endif // defined(__STDC_VERSION__)
#endif // defined(__STDC__)


#include "commonc.h"
#include "types.h"

#endif // defined(COMPILE_FOR_DSL)

// ToDo: FIXME - CV
//#include "config.h"

/** @} end of group COMMON_TYPES */

#endif /* NEULFW_H */
