/******************************************************************************
 * @brief    Hi21XX Watchdog Driver Header File
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include "neulfw.h"

/** @defgroup NONOS_DRIVERS_WATCHDOG Hi21XX non-OS Watchdog Driver
 * Hi21XX non-OS Watchdog Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

/**
 * @brief Inits the watchdog, ready to be enabled
 * @param interval Number of clock cycles per watchdog interval
 * @param monitor_arm_sleep_deep If true then the watchdog timer will monitor the ARMs sleepdeep bit and will automatically\
 *        pause whenever this is asserted, even if another core stops the deep sleep.
 * @param nmi_on_first_fire If true, the watchdog will cause a NMI on the first fire, then a reboot on the second\
 *        this state is reset if watchdog_disable or watchdog_deinit is called after the first fire.
 */
void watchdog_init(uint32 interval, bool monitor_arm_sleep_deep, bool nmi_on_first_fire);

/**
 * Converts the given time in ms to 'core clock cycles', then calls watchdog_init
 * @param interval_ms The interval time for the watchdog in ms, to avoid risk of overflows this shouldn't be larger than 82000
 * @param monitor_arm_sleep_deep
 * @param nmi_on_first_fire
 */
void watchdog_init_ms(uint32 interval_ms, bool monitor_arm_sleep_deep, bool nmi_on_first_fire);

/**
 * @brief Enable/Start the watchdog with the settings passed into watchdog_init
 * If watchdog_init has not been called this function does nothing
 */
void watchdog_enable(void);

/**
 * @brief Kick the watchdog
 */
void watchdog_kick(void);

/**
 * @brief Stops the watchdog
 */
void watchdog_disable(void);

/**
 * Stops the watchdog and disables the driver (resets state)
 * Calling init then enable is required to restart the watchdog
 */
void watchdog_deinit(void);

/**
 * @brief Returns the time left
 * @return time left in number of clock cycles
 */
uint32 watchdog_get_time(void);

/** @} end of NONOS_DRIVERS_WATCHDOG */

#endif /* WATCHDOG_H_ */
