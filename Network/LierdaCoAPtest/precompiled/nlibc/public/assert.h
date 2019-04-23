/*
 * This header has been extracted from PDPCLIB (Public Domain Project
 * C Library) - See http://pdos.sourceforge.net/.
 */

/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  assert.h - assert header file.                                   */
/*                                                                   */
/*********************************************************************/

#ifndef __ASSERT_INCLUDED
#define __ASSERT_INCLUDED

#include "panic.h"

/** @defgroup NLIBC nlibC
 * nlibC
 * @ingroup NLIBC
 * @{
 * */
/** @} end of group NLIBC */

/** @defgroup NLIBC_ASSERT nlibc Assert
 * nlibc Assert
 * @ingroup NLIBC
 * @{
 * */

// Note: Use 'our' assert as opposed to the one from tools/pclint/co-gcc.h

#ifdef _lint
extern void * __builtin_return_address(unsigned int level);
#endif


//lint -emacro({506}, assert)       Constant Boolean value  -- assert(false)
//lint -function( exit, __assert )  __assert doesn't return



int __assert(char *x, char *y, int z);

/**
 * A temporary assert to be called from memcpy.sx
 * @param lr where memcpy was called from
 */
void __asm_memcpy_assert(uint32 lr);


#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(x) (x) ? ((void)0) : panic(PANIC_ASSERT, (uint32)__builtin_return_address(0))
#endif

/** @} end of group NLIBC_ASSERT */

#endif
