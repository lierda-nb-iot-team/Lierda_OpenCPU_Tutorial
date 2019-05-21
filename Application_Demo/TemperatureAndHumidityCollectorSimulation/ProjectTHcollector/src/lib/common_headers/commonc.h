/****************************************************************************
FILE
    commonc.h  -  system-wide common header file

DESCRIPTION
    This should be #included by every C source file neul protocol development
    board system(s).

    The file includes typedefs and #defines that are common to many
    C projects.

    This file should be changed only infrequently and with great care.

    This file should contain the minimum necessary to get the job done.

    This file must not become a dumping ground for stuff that has only
    limited scope.
 * Copyright (c) 2015 NEUL LIMITED
*/

#ifndef COMMONC_H
#define COMMONC_H

#include <stddef.h>

/** @addtogroup COMMON_TYPES
 * @{
 * */

/* If DO_NOT_PACK_STRUCS is defined then strucs are not packed
   Typically this makes sense only when building on a PC. */
#ifdef NEUL_DO_NOT_PACK_STRUCTS
#define NPACKED_STRUCT
#define VAR_ALIGN(x)
#define VAR_SEGMENT(x)
#endif // NEUL_DO_NOT_PACK_STRUCTS

/* If some of the defines we use for locating variable are not defined then we had better define them */
#ifndef NPACKED_STRUCT
#if (defined __GNUC__ )|| (defined PC_ST)
#define NPACKED_STRUCT __attribute((packed))
#else
#error "You need to define NPACKED_STRUCT for your compiler."
#endif // (defined __GNUC__ )|| (defined PC_ST)
#endif // NPACKED_STRUCT


#ifndef VAR_ALIGN
#if (defined __GNUC__ )|| (defined PC_ST)
#define VAR_ALIGN(x) __attribute__ ((aligned (x)))
#else
#error "You need to define VAR_ALIGN for your compiler."
#endif // (defined __GNUC__ )|| (defined PC_ST)
#endif // VAR_ALIGN


#ifndef VAR_SEGMENT
#if (defined __GNUC__ )
#define VAR_SEGMENT(seg) __attribute__ ((section (seg)))
#else
#if  (defined PC_ST)
#define VAR_SEGMENT(seg)
#else
#error "You need to define VAR_SEGMENT for your compiler."
#endif // (defined PC_ST)
#endif // (defined __GNUC__ )
#endif // VAR_SEGMENT


//lint -emacro({717},UNUSED)
#define UNUSED(var) do { (void)var; } while(0)

//lint -emacro({717},UNUSED_DEFINE)
#define UNUSED_DEFINE(var) do { int unused_##var=(int)var; (void)unused_##var;} while(0)

#ifndef CXXTEST_RUNNING
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#endif /* CXXTEST_RUNNING */

#undef  forever
#define forever         for(;;)

#define tobool(v)       ((v) ? true : false)

#define MAKEUINT32(lo, hi)  ((uint32)(((lo) & 0xffff) | (((hi) & 0xffff) << 16)))
#define MAKEUINT16(lo, hi)  ((uint16)(((lo) & 0xff) | (((hi) & 0xff) << 8)))
#define HIUINT16(val)       ((uint16)(((val) >> 16) & 0xffff))
#define LOUINT16(val)       ((uint16)(((val) >>  0) & 0xffff))
#define HIUINT8(val)        ((uint8)(((val) >> 8) & 0xff))
#define LOUINT8(val)        ((uint8)(((val) >> 0) & 0xff))


#define PREPROCESSOR_ARGUMENT_STRING(x)                 #x
#define PREPROCESSOR_ARGUMENT_EVALUATED_STRING(x)       PREPROCESSOR_ARGUMENT_STRING(x)

/** A compile time assertion check.
 *
 *  Validate at compile time that the predicate is true without
 *  generating code. This can be used at any point in a source file
 *  where typedef is legal.
 *
 *  On success, compilation proceeds normally.
 *
 *  On failure, attempts to typedef an array type of negative size. The
 *  offending line will look like
 *      typedef assertion_failed_file_h_42[-1]
 *  where file is the content of the second parameter which should
 *  typically be related in some obvious way to the containing file
 *  name, 42 is the line number in the file on which the assertion
 *  appears, and -1 is the result of a calculation based on the
 *  predicate failing.
 *
 *  \param predicate The predicate to test. It must evaluate to
 *  something that can be coerced to a normal C boolean.
 *
 *  \param file A sequence of legal identifier characters that should
 *  uniquely identify the source file in which this condition appears.
 */
#define CASSERT(predicate, file) _impl_CASSERT_LINE(predicate,__LINE__,file)

#define _impl_PASTE(a,b) a##b
#define _impl_CASSERT_LINE(predicate, line, file) \
    typedef char _impl_PASTE(assertion_failed_##file##_,line)[2*!!(predicate)-1]

#define BIT(x)        (1UL << (x))

// Macro to check at compile time certain expressions not supported by the preprocessor
#if ! defined _lint
#define CT_ASSERT(e) enum LENGTH_CHECK { ct_assert_value = 1/((!(!(e)))) };
#else
#define CT_ASSERT(e)
#endif

/** @} end of group COMMON_TYPES */

#endif  /* COMMONC_H */
