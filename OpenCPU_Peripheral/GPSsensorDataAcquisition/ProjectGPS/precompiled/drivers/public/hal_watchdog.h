/******************************************************************************
 * @brief    Hi2115 Watchdog HAL Header file for Watchdog driver
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef HAL_WATCHDOG_H
#define HAL_WATCHDOG_H

#include "core.h"

/** @defgroup DRIVER_HAL_WATCHDOG Hi211X HAL Watchdog Driver
 * HAL Watchdog Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

#if CORE == SECURITY
//Enable full chip reset with the extra 4
#define WATCHDOG_CTRL_ENABLE (0x4AB)
#else
#define WATCHDOG_CTRL_ENABLE (0xAB)
#endif

#define WATCHDOG_CTRL_KICK   (0xC7)
#define WATCHDOG_CTRL_STOP   (0x51)

#ifdef NO_TIMEOUT
#define hal_watchdog_kick()
#define hal_watchdog_set_interval(interval)       UNUSED(interval)
#define hal_watchdog_stop()
#define hal_watchdog_get_time()                   WDT_TIME

#define hal_watchdog_enable(monitor_arm_sleep_deep, nmi_first)\
    UNUSED(monitor_arm_sleep_deep);                           \
    UNUSED(nmi_first)
#else
#define hal_watchdog_kick()                       WDT_CTRL = ((WDT_CTRL) & 0xFF00) | WATCHDOG_CTRL_KICK
#define hal_watchdog_set_interval(interval)       WDT_INTERVAL = interval
#define hal_watchdog_stop()                       WDT_CTRL = WATCHDOG_CTRL_STOP
#define hal_watchdog_get_time()                   WDT_TIME

#define hal_watchdog_enable(monitor_arm_sleep_deep, nmi_first)\
    WDT_CTRL = (((WDT_CTRL) & 0xFC00) |                       \
               (monitor_arm_sleep_deep ? 0x100 : 0) |         \
               (nmi_first ? 0x200 : 0) |                      \
               WATCHDOG_CTRL_ENABLE)
#endif

/** @} end of group DRIVER_HAL_WATCHDOG */

#endif /* HAL_WATCHDOG_H */
