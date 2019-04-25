/******************************************************************************
 * @brief    HAL UTILS INTERFACE
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef HAL_H_
#define HAL_H_

#include "hal_gpio.h"
#include "hal_ipc.h"
#include "hal_pio.h"
#include "hal_reboot.h"
#include "hal_rtc.h"
#include "hal_sectors.h"
#include "hal_timer.h"
#include "hal_uart.h"
#include "hal_watchdog.h"

/** @defgroup DRIVER_HAL Hi211X HAL Driver
 * HAL Driver
 * @ingroup DRIVER_HAL
 * */

/** @defgroup DRIVER_HAL_BASE Hi211X HAL Base Driver
 * HAL Base Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/** Initialise the CPU Specifics and reboots if in interrupt context to ensure a known start state.
 * @return None
 */
void hal_cpu_init(void);

/** Initialise HAL
 * @return None
 */
void hal_init(void);

/** De-Initialise HAL
 * @return None
 */
void hal_deinit(void);

/**
 * Structure which is pushed onto the stack by the Cortex-M0 during
 * exception processing - stack frame.
 */
typedef struct STACK_FRAME
{
    unsigned long stacked_r0;
    unsigned long stacked_r1;
    unsigned long stacked_r2;
    unsigned long stacked_r3;
    unsigned long stacked_r12;
    unsigned long stacked_lr;
    unsigned long stacked_pc;
    unsigned long stacked_psr;
} exception_stack_frame_t;

typedef enum
{
    EXCEPTION_TYPE_NONE,
    EXCEPTION_TYPE_HARD_FAULT,
    EXCEPTION_TYPE_NMI,
} exception_type_t;

/** Get the last exception stack frame and reset it so subsequent calls will return false.
 *
 * @return  The type of the last exception.
 * @param last The last exception stack frame is written here if the return value was not EXCEPTION_TYPE_NONE.
 */
exception_type_t hal_get_and_reset_last_exception(exception_stack_frame_t *last);

/** Prototype for the assembly language hard-fault handler. This will setup the stack and attempt to
 * generate a stack trace to aid debug.
 * @return None.
 */
void HardFault_Handler(void);

/** @} end of group DRIVER_HAL_BASE */

#endif
