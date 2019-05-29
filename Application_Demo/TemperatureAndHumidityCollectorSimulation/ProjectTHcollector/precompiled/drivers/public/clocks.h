/******************************************************************************
 * @brief    BOUDICA CLOCKS DRIVER HEADER
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_DRIVERS_BOUDICA_NON_OS_CLOCKS_SHARED_CLOCKS_H_
#define SRC_DRIVERS_BOUDICA_NON_OS_CLOCKS_SHARED_CLOCKS_H_

/** @defgroup NONOS_DRIVERS_CLOCKS Hi21XX non-OS Clock Driver
 * Hi21XX non-OS Clock Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

/**
 * Verify if the core clock is stable.
 * @return true if the core clock is stable.
 */
bool clocks_clock_is_stable(void);

/**
 * Return the value of the core clock.
 * @return value of the core clock in Hz.
 * @note the value returned is the mid one between the maximum limit and lower not the instant one.
 */
uint32 clocks_get_core_clock(void);

/** @} end of NONOS_DRIVERS_CLOCKS */

#endif /* SRC_DRIVERS_BOUDICA_NON_OS_CLOCKS_SHARED_CLOCKS_H_ */
