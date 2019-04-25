/******************************************************************************
 * @brief    PANIC module internal header
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef PANIC_PRIVATE_H
#define PANIC_PRIVATE_H

#include "panic.h"
#if defined USE_CMSIS_OS
#include "cmsis_os2.h"
#endif
#include "hal.h"
#include "preserve.h"
#include "rtc.h"
#if defined(LIBBACKTRACE)
#include "backtrace.h"
#endif



#endif  /* PANIC_PRIVATE_H */

