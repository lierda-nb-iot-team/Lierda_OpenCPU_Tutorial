/******************************************************************************
 * @brief    IPC HAL interface.
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef SRC_LIB_DRIVERS_IPC_SHARED_HAL_IPC_H_
#define SRC_LIB_DRIVERS_IPC_SHARED_HAL_IPC_H_

#include "core.h"
#include "platform_definitions.h"

/** @defgroup DRIVER_HAL_IPC Hi211X HAL IPC Driver
 * HAL IPC Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/*
 * Use macros for speed.
 */
#define hal_ipc_interrupt_security()            ARM_IRQ_REG = 0x01
#define hal_ipc_interrupt_protocol()               ARM_IRQ_REG = 0x02
#define hal_ipc_interrupt_apps()                ARM_IRQ_REG = 0x04


/**
 * Enable the appropriate interrupts for the IPC mechanism on this core (core specific).
 * @return None.
 */
void hal_ipc_init_interrupts (void);


/**
 * Disable interrupts used by the IPC mechanism on this core (core specific).
 * @return None.
 */
void hal_ipc_deinit_interrupts (void);


/**
 * Inform the core that an IPC operation is pending. For the APPS and PROTOCOL core this means a message has been places in their inbox,
 * while for the security core, this can have additional meaning as the security core is the man in the middle for all IPC message
 * between cores.
 * @return None
 */
void hal_ipc_interrupt_core (CORES core);


/**
 * Low level IRQ handler for IPC messages from security core.
 * @return None.
 */
void IRQ_SECURITY0_Handler (void);


/**
 * Low level IRQ handler for IPC messages from protocol core. Supported on security core only.
 * @return None.
 */
void IRQ_PROTOCOL0_Handler (void);


/**
 * Low level IRQ handler for IPC messages from apps core. Supported on security core only.
 * @return None.
 */
void IRQ_APPS0_Handler (void);

/** @} end of group DRIVER_HAL_IPC */

#endif
