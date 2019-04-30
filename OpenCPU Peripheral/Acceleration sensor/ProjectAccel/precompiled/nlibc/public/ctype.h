/* 
 * This header has been extracted from NEWLIB
 */

//lint -emacro(866, toupper)
//lint -emacro(866, tolower)
//lint -emacro(834, toupper) Operator '-' followed by operator '+' is confusing
//lint -emacro(834, tolower) Operator '-' followed by operator '+' is confusing

#ifndef _CTYPE_H_
#define _CTYPE_H_

/** @defgroup NLIBC_CTYPE nlibc Ctype
 * nlibc Ctype
 * @ingroup NLIBC
 * @{
 * */

int isalnum(int __c);
int isalpha(int __c);
int iscntrl(int __c);
int isdigit(int __c);
int isgraph(int __c);
int islower(int __c);
int isprint(int __c);
int ispunct(int __c);
int isspace(int __c);
int isupper(int __c);
int isxdigit(int __c);
int tolower(int __c);
int toupper(int __c);

#ifndef __STRICT_ANSI__
int isblank(int __c);
#endif

#ifndef __STRICT_ANSI__
int isascii(int __c);
int toascii(int __c);
#define _tolower(__c) ((unsigned char)(__c) - 'A' + 'a')
#define _toupper(__c) ((unsigned char)(__c) - 'a' + 'A')
#endif

#define    _U    01
#define    _L    02
#define    _N    04
#define    _S    010
#define _P    020
#define _C    040
#define _X    0100
#define    _B    0200

extern const char *__ctype_ptr__;

/* These macros are intentionally written in a manner that will trigger
   a gcc -Wall warning if the user mistakenly passes a 'char' instead
   of an int containing an 'unsigned char'.  Note that the sizeof will
   always be 1, which is what we want for mapping EOF to __ctype_ptr__[0];
   the use of a raw index inside the sizeof triggers the gcc warning if
   __c was of type char, and sizeof masks side effects of the extra __c.
   Meanwhile, the real index to __ctype_ptr__+1 must be cast to int,
   since isalpha(0x100000001LL) must equal isalpha(1), rather than being
   an out-of-bounds reference on a 64-bit machine.  */
#define __ctype_lookup(__c) ((__ctype_ptr__+sizeof(""[__c]))[(int)(__c)])

#define    isalpha(__c)    (__ctype_lookup(__c)&(_U|_L))
#define    isupper(__c)    ((__ctype_lookup(__c)&(_U|_L))==_U)
#define    islower(__c)    ((__ctype_lookup(__c)&(_U|_L))==_L)
#define    isdigit(__c)    (__ctype_lookup(__c)&_N)
#define    isxdigit(__c)    (__ctype_lookup(__c)&(_X|_N))
#define    isspace(__c)    (__ctype_lookup(__c)&_S)
#define ispunct(__c)    (__ctype_lookup(__c)&_P)
#define isalnum(__c)    (__ctype_lookup(__c)&(_U|_L|_N))
#define isprint(__c)    (__ctype_lookup(__c)&(_P|_U|_L|_N|_B))
#define    isgraph(__c)    (__ctype_lookup(__c)&(_P|_U|_L|_N))
#define iscntrl(__c)    (__ctype_lookup(__c)&_C)

#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#define isblank(__c) \
  __extension__ ({ __typeof__ (__c) __x = (__c);        \
        (__ctype_lookup(__x)&_B) || (int) (__x) == '\t';})
#endif


/* Non-gcc versions will get the library versions, and will be
   slightly slower.  These macros are not NLS-aware so they are
   disabled if the system supports the extended character sets. */
#if defined(__GNUC__)
#   define toupper(__c) \
  __extension__ ({ __typeof__ (__c) __x = (__c);    \
      islower (__x) ? (int) __x - 'a' + 'A' : (int) __x;})
#   define tolower(__c) \
  __extension__ ({ __typeof__ (__c) __x = (__c);    \
      isupper (__x) ? (int) __x - 'A' + 'a' : (int) __x;})
#endif /* __GNUC__ */

#ifndef __STRICT_ANSI__
#define isascii(__c)    ((unsigned)(__c)<=0177)
#define toascii(__c)    ((__c)&0177)
#endif

/* For C++ backward-compatibility only.  */
extern const char _ctype_[];

/** @} end of group NLIBC_CTYPE */

#endif /* _CTYPE_H_ */
