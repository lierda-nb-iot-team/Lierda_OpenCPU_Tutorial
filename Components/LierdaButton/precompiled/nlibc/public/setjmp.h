/*********************************************************************/
/*                                                                   */
/*  This Program Written by Paul Edwards.                            */
/*  Released to the Public Domain                                    */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*  setjmp.h - setjmp header file.                                   */
/*                                                                   */
/*********************************************************************/

#ifndef __SETJMP_INCLUDED
#define __SETJMP_INCLUDED

/** @defgroup NLIBC_SETJMP nlibc Setjump/Longjmp
 * nlibc Setjump/Longjmp
 * @ingroup NLIBC
 * @{
 * */

#if ! defined(__ARM_ARCH_6M__)

/* Continue looking in compiler incldue path, for non embedded targets. */
#include_next <setjmp.h>

#else

/* Only provide local version for ARM Cortex M0. Other (windows) platforms use 'standard' version. */

#include "neulfw.h"

#define JMP_BUF_SIZE        12
#define JMP_BUF_RETURN_VAL    (JMP_BUF_SIZE - 1)
typedef uint32 jmp_buf[JMP_BUF_SIZE];

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);
#endif

/** @} end of group NLIBC_SETJMP */

#endif
