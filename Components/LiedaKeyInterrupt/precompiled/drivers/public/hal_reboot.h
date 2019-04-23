/******************************************************************************
 * @brief    HAL Reboot functionality header file
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef HAL_REBOOT_H_
#define HAL_REBOOT_H_

#include "neulfw.h"

/** @defgroup DRIVER_HAL_REBOOT Hi211X HAL Reboot Driver
 * HAL Reboot Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/** Initialise the reboot subsystem */
void hal_reboot_init(void);

/**
 * After the a previous security image has run it should have passed us our reset reason, we need to use it
 * @param reboot_cause The original reason we rebooted
 */
void hal_reboot_init_with_value( uint16 reboot_cause );

/** De-initialise the reboot subsystem */
void hal_reboot_deinit(void);


/** Perform a software reboot (of this core only). */
void hal_reboot_core(void);

/** Values returned by hal_reboot_get_reset_reason().
 * No Bits, either the SEC_RESET_CORE register, or Power
 * Bit 0 = SYSRESETREQ.
 * Bit 1 = watchdog.
 * Bit 2 = Broken, always set
 * Bit 3 = alternative boot (security core only)
 *
 */
#define HAL_REBOOT_POWER_OR_RESET_CORE  (0x0000)
#define HAL_REBOOT_SYSRESETREQ          (0x0001)
#define HAL_REBOOT_WATCHDOG             (0x0002)
#define HAL_REBOOT_SECURITY             (0x0004)
#define HAL_REBOOT_ALTBOOT              (0x0008)
#define HAL_REBOOT_RESET_REG_0          (0x0010)
#define HAL_REBOOT_RESET_REG_3          (0x0020)
#define HAL_REBOOT_SEC_CHIP_WATCHDOG    (0x0040)
#define HAL_REBOOT_SCAN_MODE_ENTER_EXIT (0x0080)
#define HAL_REBOOT_PMU_POR              (0x0100)
#define HAL_REBOOT_RESET_PIN            (0x0200)

/**
 * This mask can be used to ignore reset reasons coming from the Apps or Protocol core
 * Since these reasons would reset the security as well, so it would already know about it
 */
#define HAL_REBOOT_ENTIRE_CHIP_MASK      (HAL_REBOOT_ALTBOOT | HAL_REBOOT_RESET_REG_0 | HAL_REBOOT_RESET_REG_3 | \
                                         HAL_REBOOT_SEC_CHIP_WATCHDOG | HAL_REBOOT_SCAN_MODE_ENTER_EXIT | \
                                         HAL_REBOOT_PMU_POR | HAL_REBOOT_RESET_PIN )

/** Return reset code showing why this core was rebooted
 *  @return the reset cause bitfield
 * */
uint16 hal_reboot_get_reset_reason(void);

/** @} end of group DRIVER_HAL_REBOOT */

#endif //HAL_REBOOT_H_
