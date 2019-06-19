/******************************************************************************
 * @brief    Hi21XX Common, (non-)os independant, UART driver interface
 * Copyright (c) 2016 NEUL LIMITED
 ******************************************************************************/

#ifndef UART_COMMON_H
#define UART_COMMON_H

/** @addtogroup DRIVER_PLATFORM
 * @{
 * */

/**
 * UART line configuration
 */
typedef struct
{
    uint32 baud_rate;
    UART_DATA_BITS data_bits;
    UART_PARITY parity;
    UART_STOP_BITS stop_bits;
} UART_LINE_CONFIGURATION;


/**
 * Internal uart interrupt callbacks type
 */
typedef struct
{
    ISR_CALLBACK rx_isr;
    ISR_CALLBACK tx_isr;
    ISR_CALLBACK idle_isr;
    ISR_CALLBACK error_isr;
} uart_isr_callbacks;

/**
 * Return codes from uart_common_validate_pin_config()
 */
typedef enum
{
    UART_COMMON_VALIDATE_PINS_OK,                //!< Pin assignments are ok
    UART_COMMON_VALIDATE_PINS_INVALID_PARAMS,    //!< NULL pointer supplied or no TX or RX pins specified
    UART_COMMON_VALIDATE_PINS_INVALID_TX,        //!< TX pin out of range or matches another pin
    UART_COMMON_VALIDATE_PINS_INVALID_RX,        //!< RX pin out of range or matches another pin
    UART_COMMON_VALIDATE_PINS_INVALID_RTS,       //!< RTS pin out of range or matches another pin
    UART_COMMON_VALIDATE_PINS_INVALID_CTS,       //!< CTS pin out of range or matches another pin
} UART_COMMON_VALIDATE_PINS;

/**
 * Validate that the supplied pin configuration is sensible
 * @param claim_pins PINs to use for UART TX, RX, CTS and RTS
 * @return UART_COMMON_VALIDATE_PINS_OK if pin configuration is acceptable, an error code otherwise
 */
UART_COMMON_VALIDATE_PINS uart_common_validate_pin_config( const uart_pin_configuration * claim_pins );

/**
 * Attempts to claim a UART and PINs.  Claimed PINs will be assigned their appropriate FUNCtion.
 * @param claim_pins PINs to use for UART TX, RX, CTS and RTS
 * @return The UART_BUS number of the claimed UART if both UART and PINs are claimed successfully, will be UART_BUS_NONE otherwise
 */
UART_BUS uart_common_claim( const uart_pin_configuration * claim_pins );

/**
 * Determines if a UART peripheral is claimed
 * @param uart The UART to check
 * @return True if the UART has been claimed, false otherwise
 */
bool uart_common_is_claimed( UART_BUS uart );

/**
 * Releases a claimed UART and associated PINs
 * @param uart The UART to release
 * @param assigned_pins PINs to release from UART TX, RX, CTS and RTS
 */
void uart_common_release( UART_BUS uart, const uart_pin_configuration * assigned_pins );

/**
 * Configure UART RX interrupt handlers
 * @param uart The UART to assign the interrupt handlers to
 * @param interrupt_handlers List of interrupt handlers to register
 */
void uart_common_configure_rx_interrupts( UART_BUS uart, const uart_isr_callbacks * interrupt_handlers );

/**
 * Configure UART TX interrupt handlers
 * @param uart The UART to assign the interrupt handlers to
 * @param interrupt_handlers List of interrupt handlers to register
 */
void uart_common_configure_tx_interrupts( UART_BUS uart, const uart_isr_callbacks * interrupt_handlers );

/**
  * Configures the line settings for a UART
  * @param uart The UART to configure
  * @param line_config The line settings to configure
  */
void uart_common_configure_line_settings( UART_BUS uart, const UART_LINE_CONFIGURATION * line_config );

/**
 * Disables a UART
 * @param uart The UART to disable
 */
void uart_common_disable_uart( UART_BUS uart );

/**
 * Enables a UART
 * @param uart The UART to enable
 * @param uart_pin_config PINs assigned to UART TX, RX, CTS and RTS
 */
void uart_common_enable_uart( UART_BUS uart, const uart_pin_configuration *uart_pin_config );

/** @} end of group DRIVER_PLATFORM */

#endif  // UART_COMMON_H
