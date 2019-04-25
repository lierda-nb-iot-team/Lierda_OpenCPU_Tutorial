/******************************************************************************
 * @brief    BOUDICA Low Power controller HAL INTERFACE
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef HAL_LPC_H_
#define HAL_LPC_H_

#include "memory_config.h"  //Needed for the MEMORY_CONFIGURATION_FUNCTION_LOADABLE_IN_RAM define

/** @defgroup DRIVER_HAL_LPC Hi211X HAL LPC Driver
 * HAL LPC Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/** LPC_STATUS REGISTER MASKS  */
#define LPC_STATUS_MASK_APPS_SLEEP              (0x01 << 23)
#define LPC_STATUS_MASK_PROTOCOL_SLEEP          (0x01 << 24)
#define LPC_STATUS_MASK_APPS_DEEP_SLEEP         (0x01 << 26)
#define LPC_STATUS_MASK_PROTOCOL_DEEP_SLEEP     (0x01 << 27)

/** Apps core is in sleep */
#define APPS_ASSERTS_SLEEP()                    ((hal_lpc_get_status_register() & LPC_STATUS_MASK_APPS_SLEEP) != 0)

/** Protocol core is in sleep */
#define PROTOCOL_ASSERTS_SLEEP()                ((hal_lpc_get_status_register() & LPC_STATUS_MASK_PROTOCOL_SLEEP) != 0)

/** Apps core is in deep sleep */
#define APPS_ASSERTS_DEEP_SLEEP()               ((hal_lpc_get_status_register() & LPC_STATUS_MASK_APPS_DEEP_SLEEP) != 0)

/** Protocol core is in deep sleep */
#define PROTOCOL_ASSERTS_DEEP_SLEEP()           ((hal_lpc_get_status_register() & LPC_STATUS_MASK_PROTOCOL_DEEP_SLEEP) != 0)


/** Low Power Controller Sleep Modes */
typedef enum
{
    HAL_LPC_SLEEP_MODE_LIGHT,
    HAL_LPC_SLEEP_MODE_DEEP,
} HAL_LPC_SLEEP_MODE;

/**
 * Enter Wait for interrupt state
 */
void hal_lpc_enter_wfi(void) MEMORY_CONFIGURATION_FUNCTION_LOADABLE_IN_RAM;

/**
 * Set a type of sleep mode
 * @param mode Sleep Mode
 * @note It configures the appropriate values for LPC_CTRL and SCB->SCR registers
 */
void hal_lpc_set_sleep_mode(HAL_LPC_SLEEP_MODE mode);

/**
 * Set the sleep on exit
 * @param sleep_on_exit uses (true) sleep on exit or not (false)
 */
void hal_lpc_set_sleep_on_exit( bool sleep_on_exit );

/**
 * Gets the current value of the LPC status register
 * @return
 */
uint32 hal_lpc_get_status_register(void);

/**
 * Returns the current value of LPC_SLEEP_CNT
 * @return
 */
uint32 hal_lpc_get_deep_sleep_count( void );

/** @} end of group DRIVER_HAL_LPC */

#endif /* HAL_LPC_H_ */
