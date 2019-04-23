/******************************************************************************
 * @brief    Hi21XX Specific LOW POWER UART HAL INTERFACE
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/
#ifndef HAL_LPUART_SPECIFIC_H
#define HAL_LPUART_SPECIFIC_H

#define HAL_LPUART_CTRL_NUM_DEN_MASK (0xFFFF)
#define HAL_LPUART_CTRL_SET_NUM_DEN(r,x) ( ((r) & ~HAL_LPUART_CTRL_NUM_DEN_MASK ) | ( (x) & HAL_LPUART_CTRL_NUM_DEN_MASK ) )

/** @addtogroup DRIVER_HAL_LPUART
 * @{
 * */

/**
 * Attempt to claim the LP UART
 * @return True if LP UART is claimed, false otherwise
 */
bool hal_lpuart_specific_claim( void );

/**
 *  Release claim over LP UART
 */
void hal_lpuart_specific_release( void );

/**
 *  Clear LP UART RX interrupt
 */
void hal_lpuart_specific_clear_irq( void );

/**
 * Sets the baudrate for the LPUART.
 * @param baudrate baudrate to set the lpuart to.
 * @return true if successful, false otherwise.
 */
bool hal_lpuart_specific_set_baud_rate(uint32 baudrate);

/** @} end of group DRIVER_HAL_LPUART */

#endif // HAL_LPUART_SPECIFIC_H
