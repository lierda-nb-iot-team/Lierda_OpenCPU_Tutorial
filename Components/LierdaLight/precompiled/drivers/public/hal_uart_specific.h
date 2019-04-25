/******************************************************************************
 * @brief    Hi2115 Specific UART HAL Driver Interface
 * Copyright (c) 2016 NEUL LIMITED
 ******************************************************************************/

#ifndef HAL_UART_SPECIFIC_H_
#define HAL_UART_SPECIFIC_H_

/** @addtogroup DRIVER_HAL_UART
 * @{
 * */

/**
 * Get pointer to UART control structure
 * @param Uart index
 * @return Pointer to uart control structure
 */
volatile uart_ctrl_t * hal_uart_specific_get_uart( uint8 uart );

/**
 * Resets the uarts on the protocol and apps cores using the RESET_REG register
 * The security core does not have that register, this function does nothing on
 * the security core
 * @param Uart index
 */
void hal_uart_specific_reset_uart( uint8 uart );

/**
 * Enables a UART clock
 * @param Uart index
 * @return True if clock enabled, false otherwise
 */
bool hal_uart_specific_enable_clock( uint8 uart );

/**
 * Determines if a UART clock is enabled
 * @param Uart index
 * @return True if clock enabled, false otherwise
 */
bool hal_uart_specific_is_clock_enabled( uint8 uart );

/**
 * Disables a UART clock
 * @param Uart index
 */
void hal_uart_specific_disable_clock( uint8 uart );

/**
 * Enable IRQ associated with a UART
 * @param uart Uart index
 */
void hal_uart_specific_enable_irq( uint8 uart );

/**
 * Disable IRQ associated with a UART
 * @param uart Uart index
 */
void hal_uart_specific_disable_irq( uint8 uart );

/**
 * Set IRQ associated with a UART pending
 * @param uart Uart index
 */
void hal_uart_specific_set_pending_irq( uint8 uart );

/** @} end of group DRIVER_HAL_UART */

#endif   // HAL_UART_SPECIFIC_H_
