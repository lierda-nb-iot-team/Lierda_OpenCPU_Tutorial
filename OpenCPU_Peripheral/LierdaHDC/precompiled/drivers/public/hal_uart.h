/******************************************************************************
 * @brief    BOUDICA UART HAL Header.
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef HAL_UART_H_
#define HAL_UART_H_

#include "hal_uart_definitions.h"
#include "platform.h"

/** @defgroup DRIVER_HAL_UART Hi211X HAL UART Driver
 * HAL UART Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/**
 * Bitmasks used to configure which UART features to enable in
 */
#define HAL_UART_ENABLE_FLAG_NONE (0)
#define HAL_UART_ENABLE_FLAG_RX   (1 << 0)
#define HAL_UART_ENABLE_FLAG_TX   (1 << 1)
#define HAL_UART_ENABLE_FLAG_CTS  (1 << 2)
#define HAL_UART_ENABLE_FLAG_RTS  (1 << 3)

/**
 * UART Flag Register fields
 */
#define HAL_UARTFR_TXFE_FLAG      BIT(7)   // TX FIFO Empty flag
#define HAL_UARTFR_RXFF_FLAG      BIT(6)   // RX FIFO Full flag
#define HAL_UARTFR_TXFF_FLAG      BIT(5)   // TX FIFO Full flag
#define HAL_UARTFR_RXFE_FLAG      BIT(4)   // RX FIFO Empty flag
#define HAL_UARTFR_BUSY_FLAG      BIT(3)   // TX Busy flag

typedef uint8 HAL_UART_ENABLE_FLAGS;

/** FIFO Status */
typedef enum
{
    HAL_UART_FIFO_ENABLED,
    HAL_UART_FIFO_DISABLED,
} HAL_UART_FIFO;

/** Uart FIFO Level */
typedef enum
{
    HAL_UART_FIFO_INT_LEVEL_1_8,
    HAL_UART_FIFO_INT_LEVEL_1_4,
    HAL_UART_FIFO_INT_LEVEL_1_2,
    HAL_UART_FIFO_INT_LEVEL_3_4,
    HAL_UART_FIFO_INT_LEVEL_7_8,
} HAL_UART_FIFO_INT_LEVEL;

/** Uart interrupt types */
typedef enum
{
    HAL_UART_INTERRUPT_RX,
    HAL_UART_INTERRUPT_TX,
    HAL_UART_INTERRUPT_IDLE,
    HAL_UART_INTERRUPT_ERROR
} HAL_UART_INTERRUPT;

/**
 * Initialise the hal uart module.
 * Must be called before any other hal_uart function.
 */
void hal_uart_init( void );

/**
 * De-initialise the hal uart module.
 */
void hal_uart_deinit( void );

/**
 * Attempts to claim a UART
 * @param uart The uart to be claimed
 * @return True if claim is successful, false otherwise
 */
bool hal_uart_claim( UART_BUS uart );

/**
 * Determines if a UART is claimed
 * @param uart The uart to check
 * @return True if the uart has been claimed, false otherwise
 */
bool hal_uart_is_claimed( UART_BUS uart );

/**
 * Releases a claimed UART
 * @param uart The uart to be released
 */
void hal_uart_release( UART_BUS uart );

/**
 * Sets FIFO enabled or not.
 * @param uart Uart bus.
 * @param fifo FIFO state.
 */
void hal_uart_set_fifo( UART_BUS uart, HAL_UART_FIFO fifo );

/**
 * Sets the FIFO interrupt leves for receiving and transmitting.
 * @param uart Uart bus.
 * @param rx_level Level at which the receive interrupt interrupt will be triggered.
 * @param tx_level Level at which the transmit interrupt interrupt will be triggered.
 */
void hal_uart_set_fifo_int_levels( UART_BUS uart, HAL_UART_FIFO_INT_LEVEL rx_level, HAL_UART_FIFO_INT_LEVEL tx_level );

/**
 * Obtains the RX FIFO trigger level in bytes, as configured by hal_uart_set_fifo_int_levels
 * @param uart Uart bus.
 * @return The currently configured FIFO trigger level
 */
uint8 hal_uart_get_rx_fifo_level( UART_BUS uart );

/**
 * Returns a pointer to the data register to write or read from.
 * @param uart Uart bus.
 * @return data pointer.
 */
volatile uint32* hal_uart_get_data_register( UART_BUS uart );

/**
 * Returns a pointer to the error register to read from.
 * @param uart Uart bus.
 * @return error register value.
 */
volatile uint32* hal_uart_get_error_register( UART_BUS uart );

/**
 * Returns a pointer to the flag register to read from.
 * @param uart Uart bus.
 * @return error register value.
 */
volatile uint32* hal_uart_get_flag_register( UART_BUS uart );

/**
 * Sets the baud rate.
 * @param uart Uart bus.
 * @param baud Baud rate.
 */
void hal_uart_set_baud_rate( UART_BUS uart, uint32 baud );

/**
 * Reads the baud rate back from the registers
 * @param uart The Uart bus to read from
 * @return The current baud rate
 */
uint32 hal_uart_get_baud_rate(UART_BUS uart);

/**
 * Sets the data bits to use in the uart.
 * @param uart Uart bus.
 * @param bits Data bits.
 */
void hal_uart_set_data_bits( UART_BUS uart, UART_DATA_BITS bits );

/**
 * Sets the data bits to use in the uart.
 * @param uart Uart bus.
 * @param bits Data bits.
 */
void hal_uart_set_stop_bits( UART_BUS uart, UART_STOP_BITS bits );

/**
 * Sets the parity bits to use in the uart.
 * @param uart Uart bus.
 * @param parity Parity bits.
 */
void hal_uart_set_parity( UART_BUS uart, UART_PARITY parity );

/**
 * Enables the uart for transmission, reception and or cts.
 * @param uart Uart bus.
 * @param uart_enable_flags Bitmask of UART functions (RX, TX, CTS and RTS) to enable
 */
void hal_uart_set_enable_uart( UART_BUS uart, HAL_UART_ENABLE_FLAGS uart_enable_flags );

/**
 * Disables the uart.
 * @param uart Uart bus.
 */
void hal_uart_disable_uart( UART_BUS uart );

/**
 * Registers the interrupt callback associated with a interrupt type.
 * @param uart Uart bus.
 * @param interrupt_type Uart interrupt type
 * @param callback Calback function to register
 * @param initial_state Initial state of the interrupt, enabled or disabled.
 */
void hal_uart_configure_interrupt( UART_BUS uart, HAL_UART_INTERRUPT interrupt_type, ISR_CALLBACK callback, INTERRUPT_STATE initial_state );

/**
 * Enables the uart interrupt type specified
 * @param uart Uart bus.
 * @param interrupt_type Uart interrupt type
 */
void hal_uart_enable_interrupt( UART_BUS uart, HAL_UART_INTERRUPT interrupt_type );

/**
 * Disables the uart interrupt type specified
 * @param uart
 * @param interrupt_type
 */
void hal_uart_disable_interrupt( UART_BUS uart, HAL_UART_INTERRUPT interrupt_type );

/**
 * Clears the uart interrupt type specified.
 * @param uart Uart bus.
 * @param interrupt_type Uart interrupt type.
 */
void hal_uart_clear_interrupt( UART_BUS uart, HAL_UART_INTERRUPT interrupt_type );

/**
 * Returns true if the uart transmit fifo is empty.
 * @param uart Uart bus.
 * @return true if the uart transmit fifo is empty.
 */
bool hal_uart_is_tx_fifo_empty( UART_BUS uart );

/**
 * Returns true if the uart transmit fifo is full.
 * @param uart Uart bus.
 * @return true if the uart transmit fifo is full.
 */
bool hal_uart_is_tx_fifo_full( UART_BUS uart );

/**
 * Returns true if the uart receive fifo is empty.
 * @param uart Uart bus.
 * @return true if the uart receive fifo is empty.
 */
bool hal_uart_is_rx_fifo_empty( UART_BUS uart );

/**
 * Returns true if the uart receive fifo is full.
 * @param uart
 * @return true if the uart receive fifo is full.
 */
bool hal_uart_is_rx_fifo_full( UART_BUS uart );

/**
 * true if the uart transmit is busy, this is if there is something on the FIFO or the shift register
 * that has not been transmited yet.
 * @param uart Uart bus.
 * @return true if the uart transmit is busy
 */
bool hal_uart_is_busy( UART_BUS uart );

/**
 * Sends debug out a UART using a currently unused UART. It assumes the corresponding UART TX PIN has been configured.
 * @param uart UART_BUS to use
 * @param buffer is the data to transmit
 * @param data_length length is the the amount of data to transmit
 * @param baud_rate is the baud rate to use
 * @param data_bits data bits to use
 * @param stop_bits stop bits to use
 * @param parity parity mode to use
 * @note The specified UART must not be claimed for success
 */
void hal_uart_debug_send_using_unclaimed_uart( UART_BUS uart, const uint8* buffer, uint32 data_length, uint32 baud_rate, UART_DATA_BITS data_bits, UART_PARITY parity, UART_STOP_BITS stop_bits );

/**
 * Forces the pending excecution of the tx isr in an interrupt context.
 * @param uart Uart bus
 */
void hal_uart_force_tx_isr( UART_BUS uart );

/**
 * Forces the pending excecution of the idle isr in an interrupt context.
 * @param uart Uart bus
 */
void hal_uart_force_idle_isr( UART_BUS uart );

/**
 * Get the register to control the UART data transfer via DMAC.
 * @param uart Uart bus
 */
volatile uint32 *hal_uart_get_dmac_register( UART_BUS uart );

/**
 * Generic ISR for UARTs called from the specific handler.
 * @param uart Uart that triggered the interrupt
 */
void hal_uart_isr( UART_BUS uart );

/** @} end of group DRIVER_HAL_UART */

#endif /* HAL_UART_H_ */
