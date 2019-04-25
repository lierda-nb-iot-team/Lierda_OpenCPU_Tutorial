/******************************************************************************
 * @brief    SYSTEM STATUS MODULE INTERFACE
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_DRIVERS_NON_OS_SYSTEM_STATUS_SHARED_SYSTEM_STATUS_H_
#define SRC_DRIVERS_NON_OS_SYSTEM_STATUS_SHARED_SYSTEM_STATUS_H_

#include "core.h"
#include "memory_config.h"
#if CORE != SECURITY

/** @defgroup NONOS_DRIVERS_SYSTEM_STATUS Hi21XX non-OS System Status Driver
 * Hi21XX non-OS System Status Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

#if defined TEST_SUITE
#define SYSTEM_STATUS_WAKE_DEBUG
#endif

#define SYSTEM_STATUS_WAKE_DEBUG  // Kept this debug macro on to capture max protocol core delay due to flash write/erase at the time of DSP lockup

#if defined SYSTEM_STATUS_WAKE_DEBUG
extern uint32 system_status_debug_longest_wake_delay;
#endif

/**
 * Initialise the system status module
 */
void system_status_init(void);

/**
 * Adds one veto to the flash writes, if the number of vetos added is > 0 the flash writes
 * will be blocked.
 */
void system_status_add_flash_write_veto(void);

/**
 * Removes one veto to the flash writes
 * If the number of vetos is 0 the flash writes will be allowed again.
 */
void system_status_remove_flash_write_veto(void);

/**
 * Read state of the veto
 * No critical section needed as the caller will subsequently instructs the
 * security core to attempt the flash write which will check the veto again.
 */
bool system_status_flash_write_vetoed(void);

/**
 * This is a special function that gets called before main has started.
 * It either returns because we have passed the locks, or we got ignored.
 * This should only happen if we were talking to a old security core image
 * @return A uint16 from the security core containing our reset reason
 */
uint16 system_status_system_starting( void );

/**
 * Sets the jlink connected bit
 * This will prevent the security core from restarting the whole system if the reset cause was SYSRESETREQ
 */
void system_status_jlink_connected( void ) __attribute__((section(".gdb_debug")));

/**
 * Unsets the jlink connected bit
 * This will cause the security core to reboot the whole chip if this reset from SYSRESETREQ
 */
void system_status_jlink_disconnected( void ) __attribute__((section(".gdb_debug")));

/**
* @param wake_time The expected wake-up time
*/
void system_status_set_expected_wake_time( uint64 wake_time );

/**
 * Sets the system status flags to let the security core know that we are fine for it to
 * write to flash until the time set by system_status_set_expected_wake_time
 * This function has to be in ram as the security core 'could' start a flash write as soon as the bits are set
 */
void system_status_signal_enter_wfi( void ) MEMORY_CONFIGURATION_FUNCTION_LOADABLE_IN_RAM;

/**
 * Sets the status flags asking the security core to allow us flash access, this function will
 * block until it is safe to go to flash
 */
void system_status_signal_exit_wfi( void ) MEMORY_CONFIGURATION_FUNCTION_LOADABLE_IN_RAM;

/** @} end of NONOS_DRIVERS_SYSTEM_STATUS */

#endif // CORE != SECURITY

#endif /* SRC_DRIVERS_NON_OS_SYSTEM_STATUS_SHARED_SYSTEM_STATUS_H_ */
