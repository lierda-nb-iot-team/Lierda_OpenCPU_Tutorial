/******************************************************************************
 * @brief    BOUDICA NON OS Utils Header
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef NON_OS_H_
#define NON_OS_H_

#include "neulfw.h"
#include "core.h"

/** @defgroup NONOS_DRIVERS Hi21XX non-OS Drivers
 * Hi21XX non-OS Drivers
 * @ingroup NONOS_DRIVERS
 * */

#define THREAD_MODE_PRIORITY 4

typedef enum
{
    //Shared
    DRIVER_INIT_WATCHDOG = 0,
    DRIVER_INIT_RTC,
    DRIVER_INIT_TIMER,
    DRIVER_INIT_PIO,
    DRIVER_INIT_GPIO,
    DRIVER_INIT_IPC,
    DRIVER_INIT_SYS_STATUS,
    DRIVER_INIT_IPC_FLASH,
    DRIVER_INIT_UART,
    DRIVER_INIT_REBOOT,
    DRIVER_INIT_LPC,
    DRIVER_INIT_NEUL_KV,
    DRIVER_INIT_SPI,
    DRIVER_INIT_DMA,

    //Security Only
    DRIVER_INIT_IFLASH,
    DRIVER_INIT_IFLASH_CONFIG,
    DRIVER_INIT_MEMORY,
    DRIVER_INIT_OTP,
    DRIVER_INIT_IPC_SEC,
    DRIVER_INIT_IPC_FLASH_SECURITY,
    DRIVER_INIT_PMU,
    DRIVER_INIT_CLOCK,
    DRIVER_INIT_SWD_ACCESS_CONTROL,
    DRIVER_INIT_LOG_MEMORY,

    //Protocol Only
    DRIVER_INIT_UICC,
    //QUAD_SPI
    DRIVER_INIT_EFLASH,

    //APPS ONLY
    DRIVER_INIT_PWM,
    DRIVER_INIT_SSP0,
    DRIVER_INIT_SSP1,
    //I2C
    //SPI
    //CAPACTIVE TOUCH
    //Temperature
    //Comparator
    DRIVER_INIT_LPUART,
    DRIVER_INIT_MAX_VALUE
} DRIVER_INIT_BIT;


CASSERT( DRIVER_INIT_MAX_VALUE <= 32, NON_OS_H_);

/** @defgroup NONOS_DRIVERS_UTILS Hi21XX non-OS Utils and definitions.
 * Hi21XX non-OS Utils and definitions used by the NON-OS drivers.
 * @ingroup NONOS_DRIVERS
 * @{
 * */

/**
 * Enter in a critical section.
 */
//lint -sem( non_os_enter_critical, thread_protected )
//lint -sem( non_os_enter_critical, thread_lock )

void non_os_enter_critical(void);

/**
 * Enter in a critical section.
 */
//lint -sem( non_os_exit_critical, thread_unlock )
//lint -sem( non_os_exit_critical, thread_protected )
void non_os_exit_critical(void);

/**
 * Checks if the system is running on a critical section.
 * @return true if the system is running in a critical section.
 */
bool non_os_is_in_critical_section(void );


/**
 * Ensures interrupts are enabled and the interrupt nested counter is reset.
 */
void non_os_critical_section_init(void);


/**
 * Gets the value of the drivers flag bit, then converts into a bool
 * @param driver The driver that you wish to check is initialised
 * @return True if it has
 */
bool non_os_is_driver_initialised(DRIVER_INIT_BIT driver);

/**
 * Sets the value of the specified bit
 * @param driver The driver whose bit you wish to set
 * @param value The value to set the bit to
 */
void non_os_set_driver_initalised(DRIVER_INIT_BIT driver, bool value);

/**
 * Checks if we are currently in interrupt context
 * @return If we are in interrupt context this will return true, false otherwise
 */
bool non_os_is_this_interrupt_context(void);

/**
 * Gets the current IRQ that we are in
 * @return The IRQn_Type
 */
IRQn_Type non_os_get_current_irqn(void);

/**
 * Gets the current Priority level, although the M0 has the priority levels
 * 0,64,128,192 these get converted down to 0,1,2,3 where 0 is the highest priority
 * @return The current priority level
 */
uint32 non_os_get_current_priority(void);

/**
 * Gets the priority of the given IRQ< this will not check if that IRQ is enabled.
 * As with the non_os_get_current_priority, the returned values are either 0,1,2,3
 * Where 0 is the highest priority
 * @param context The IRQ that you want to check
 * @return the priority of that IRQ line
 */
uint32 non_os_get_irq_priority(IRQn_Type context);

/**
 * Claims a permanent timer (either timer or RTC)
 * The function does Nothing, this is intended!
 * It can be safely used until a timer reserve function is written
 */
void non_os_claim_permanent_timer( void );

/** @} end of NONOS_DRIVERS_UTILS*/

#endif /* NON_OS_H_ */
