/******************************************************************************
 * @brief    BOUDICA LP UART Driver Header.
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/
#ifndef LP_UART_H_
#define LP_UART_H_

#include "pio.h"

/** @defgroup NONOS_DRIVERS_LPUART Hi21XX non-OS LPUART Driver
 * Hi21XX non-OS LPUART Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

typedef enum
{
    LP_UART_INTERRUPT_NONE = 0,
    LP_UART_INTERRUPT_PARITY_ERROR,
    LP_UART_INTERRUPT_FRAME_ERROR,
    LP_UART_INTERRUPT_SUCCESSFUL_WORD,
    LP_UART_INTERRUPT_START_BIT,
    LP_UART_INTERRUPT_THRESHOLD_AMMOUNT,
    LP_UART_MAX_INTERRUPTS
}
LP_UART_INTERRUPT; // Stop bit Enable for LPUART

typedef enum
{
    LPUART_WORDLENGTH_5BIT,
    LPUART_WORDLENGTH_6BIT,
    LPUART_WORDLENGTH_7BIT,
    LPUART_WORDLENGTH_8BIT
}
LPUART_WORDLENGTH; // Wordlengths for LPUART

/**
 * LP UART pin configuration
 */
typedef struct
{
    PIN rx_pin;     //!< Reception PIN
    PIN rts_pin;    //!< Request to send PIN to use
} lpuart_pin_configuration;

typedef void (*lp_uart_callback)(bool error);

typedef void (*LP_UART_SOFTWARE_FLOW_CONTROL_CALLBACK)( bool flow_control_asserted );

/**
 * init the lp_uart module
 */
bool lp_uart_init(const lpuart_pin_configuration *pin_config, uint32 baudrate, uint8 sync_mode, uint8 parity);

/**
 * de-init the lp_uart module
 */
void lp_uart_deinit(void);

/**
 * Enables software flow control in LP UART
 * @param rx_callback The callback function used to trigger sending of an XOFF/XON
 * @param tx_callback The callback function used to suspend/resume our own TX
 */
void lp_uart_enable_software_flow_control( LP_UART_SOFTWARE_FLOW_CONTROL_CALLBACK rx_callback, LP_UART_SOFTWARE_FLOW_CONTROL_CALLBACK tx_callback );

/**
 * Disables software flow control in LP UART
 */
void lp_uart_disable_software_flow_control( void );

/**
 * Set the trigger levels to cause software flow control to be actioned
 * XOFF will be transmitted if RX buffer exceeds the water margin level
 * XON will be transmitted if the RX buffer falls back to the water margin level
 * @param lower_water_margin The RX buffer level at which software flow control is de-asserted
 * @param upper_water_margin The RX buffer level at which software flow control is asserted
 */
void lp_uart_set_software_flow_control_water_margin( uint8 lower_water_margin, uint8 upper_water_margin );

/**
 * Sets the rx receive threshold level before the LP_UART_INTERRUPT_THRESHOLD_AMMOUNT is called
 * @param threshold_level the level in bytes before a interrupt is triggered
 */
void lp_uart_set_rx_threshold(uint8 threshold_level);

/**
 * Set the number of stop bits to use
 * @param word_length the word length to use - 5, 6, 7 or 8
 */
void lp_uart_set_word_length(LPUART_WORDLENGTH word_length);

/**
 * Enable/Disable the use of the LP_UART stop bit
 * @param use_stop_bit true/false!
 */
void lp_uart_enable_stop_bit(bool use_stop_bit);

/**
 * Flushes all data held in the LP UART driver receive buffer
 * @return Number of bytes flushed from receive buffer
 */
uint16 lp_uart_flush_data( void );

/**
 * Gets the data out of the low power UART,
 * @param buffer
 * @param max_amount the max amount to read in this pass
 * @param uart_errors Flags indicating any UART errors that occurred while receiving the data
 * @return The number of bytes read into the buffer
 */
uint16 lp_uart_get_data(uint8 *buffer, uint16 max_amount, UART_ERROR *uart_errors);

/**
 * Gets the current FIFO level
 * @return the Fifo level
 */
uint8 lp_uart_get_fifo_level(void);

/**
 * Gets the number of parity errors
 * @return the number of parity errors
 */
uint8 lp_uart_get_parity_errors(void);

/**
 * Gets the number of frame errors
 * @return The number of frame errors
 */
uint8 lp_uart_get_frame_errors(void);

/**
 * Enables the given IRQ line
 * @param irq
 */
void lp_uart_enable_irq(LP_UART_INTERRUPT irq);

/**
 * Disables the given IRQ line
 * @param irq
 */
void lp_uart_disable_irq(LP_UART_INTERRUPT irq);

/**
 * Registers a callback for the given irq
 * @param irq the IRQ to interrupt on
 * @param callback the function to call on that irq
 */
void lp_uart_set_callback(LP_UART_INTERRUPT irq, lp_uart_callback callback);

/**
 * De-Registers a callback for the given irq
 * @param irq the IRQ to not have a callback for
 */
void lp_uart_unset_callback(LP_UART_INTERRUPT irq);

/** @} end of NONOS_DRIVERS_LPUART */

#endif
