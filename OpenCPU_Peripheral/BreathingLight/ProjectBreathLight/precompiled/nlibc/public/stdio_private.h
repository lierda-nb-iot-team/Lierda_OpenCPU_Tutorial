#ifndef _STDIO_PRIVATE_H_
#define _STDIO_PRIVATE_H_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

#define __PDPCLIB_API__ 

#define STDIO_STRING_UNLIMITED              ((size_t)0xffffffff)

extern int vvprintf(const char *format, va_list arg, char *s, size_t maxlen);
extern int vvscanf(const char *format, va_list arg, const char *s);

#ifndef min
#define min(a, b) (a)<(b)?(a):(b)
#endif

#endif