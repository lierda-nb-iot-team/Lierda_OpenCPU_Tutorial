/******************************************************************************
 * @brief    BOUDICA UART Driver Header.
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "hal_uart_definitions.h"
#include "pio.h"
#include "uart_common.h"
#include "core.h"
#include "dma.h"

/** @defgroup DRIVER_CMSIS Hi211X CMSIS Drivers
 * CMSIS UART Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */
/** @} end of group DRIVER_CMSIS */

/** @defgroup DRIVER_CMSIS_UART Hi211X CMSIS UART Driver
 * CMSIS UART Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */

/**
 * Prototype for functions used to assert/de-assert RX/TX software flow control
 * For RX, the function would be used to request that the other side stopped/started sending data
 * For TX, the function would be used to suspend/resume our own transmissions
 */
typedef void (*UART_ASSERT_SOFTWARE_FLOW_CONTROL_FUNCTION)( bool flow_control_asserted );

/**
 * UART buffer configuration
 */
typedef struct
{
    uint16 rx_buffer_size;  //!< reception buffer size in bytes
} uart_buffer_configuration;

/**
 * UART configuration relevant to DMA:
 * 1. Whether UART TX/RX using DMA
 * 2. Priority of the DMA channel associated with UART TX/RX
 */
typedef struct
{
    bool            tx_use_dma;         //!< If the UART TX data through DMA
    bool            rx_use_dma;         //!< If the UART RX data through DMA
    DMA_CH_PRIORITY tx_dma_ch_priority; //!< The priority of the DMA channel that UART TX associated with while opening the channel
    DMA_CH_PRIORITY rx_dma_ch_priority; //!< The priority of the DMA channel that UART RX associated with while opening the channel
} UART_DMA_CONFIGURATION;

/**
 * DMA configuraion for UART writing via DMA
 */
typedef struct
{
    DMA_CH_CYCLE_TYPE     cycle_type;    //!< DMA Channel cycle type
    dma_transfer_callback done_callback; //!< DMA transferring done callback function
} UART_WRITE_DMA_CONFIGURATION;

#define UART_RX_CONDITION_MASK_IDLE             (1)
#define UART_RX_CONDITION_MASK_SUFFICIENT_DATA  (2)
#define UART_RX_CONDITION_MASK_FULL             (4)

/**
 * UART Condition under the RX Callback will be invoked
 */
typedef enum
{
    /**A call-back will be made if the RX data pauses or there is no more RX buffer space so data is no longer being accepted.
     * When registering this condition, a back-log of */
    UART_RX_CONDITION_FULL_OR_IDLE = (UART_RX_CONDITION_MASK_FULL | UART_RX_CONDITION_MASK_IDLE),                   //!< UART_RX_CONDITION_FULL_OR_IDLE
    /**A call-back will be made as soon as possible after the specified amount of data is received or there is no more RX buffer space so data is no longer being accepted.
     * More than the requested data may be provided to the call-back if there was a back-log of received data*/
    UART_RX_CONDITION_FULL_OR_SUFFICIENT_DATA = (UART_RX_CONDITION_MASK_FULL | UART_RX_CONDITION_MASK_SUFFICIENT_DATA),        //!< UART_RX_CONDITION_FULL_OR_SUFFICIENT_DATA
    /**A call-back will be made if the RX data buffer is full or the specified number of bytes has been received or there is a pause*/
    UART_RX_CONDITION_FULL_OR_SUFFICIENT_DATA_OR_IDLE = (UART_RX_CONDITION_MASK_FULL | UART_RX_CONDITION_MASK_SUFFICIENT_DATA | UART_RX_CONDITION_MASK_IDLE),//!< UART_RX_CONDITION_FULL_OR_SUFFICIENT_DATA_OR_IDLE
} UART_RX_CONDITION;

/**
 * Type of the release function passed to the UART_RX_CALLBACK registered.
 * The supplied finished function must be called with the provided buffer and length in order that they are supplied
 * @param buffer buffer passed to the release UART_RX_CALLBACK registered.
 * @param length length parameter received in the UART_RX_CALLBACK registered.
 */
typedef void (*UART_RELEASE_FUNCTION)(const void *buffer, uint16 length);

/**Release buffer function to call once a TX block or RX fragment is no longer needed
 * @param buffer is the TX block or RX fragment memory buffer that is no longer required
 * @param length is the length of the memory buffer
 * @param params is supplied when the TX fragment is supplied and returned here
 * This function must be called against the TX block in the order they were provided.
 * This is invoked against a TX block in an ISR context
 * The params quantity is present to allow customisable information passing between the 'writer' and the registered callback handler
 */
typedef void (*UART_TX_CALLBACK)(const void *buffer, uint16 length, void *params);

/**The UART RX data interrupt callback function
 * @param buffer is the RX fragment memory buffer containing data
 * @param length is the length of the memory buffer
 * @param finished_with_rx_fragment is the function to release the RX fragment memory once it is no longer required by the application
 * This callback function will always be called in an interrupt context
 * This may be called multiple times to return RX data in non-contiguous memory
 * The returned RX data will always be in the order that it was received
 * The supplied finished function must be called with the provided buffer and length in order that they are supplied
 */
typedef void (*UART_RX_CALLBACK)(void *buffer, uint16 length, UART_RELEASE_FUNCTION finished_with_rx_fragment);

/**
 * UART Transmission Callback type to call when the RX condition registered on
 * uart_register_parity_error_callback call or on error.
 * This callback is invoked in an interrupt context and the buffer will be freed after the call.
 * Errors registered are parity.
 */
typedef void (*UART_PARITY_ERROR_CALLBACK)(void);

/**
 * UART Transmission Callback type to call when the RX condition registered on
 * uart_register_frame_error_callback call or on error.
 * This callback is invoked in an interrupt context and the buffer will be freed after the call.
 * Errors registered are frame.
 */
typedef void (*UART_FRAME_ERROR_CALLBACK)(void);

/**
 * Initialise the UART Module.
 */
void uart_init( void );

/**
 * Unregister any reception callback previously registered.
 * @param uart handle to the UART in use.
 */
void uart_unregister_rx_callback( UART_BUS uart );

/**
 * De-initialise the UART Module.
 */
void uart_deinit( void );

/**
 * Attempts to claim ownership of an unused UART peripheral and PINs specified for TX, RX, RTS and CTS
 * A UART can be used in a bi-directional or uni-directional manner.  This is determined by declaring use of the TX and/or the RX pin
 * Use of the RTS and CTS pins, for flow control, is optional
 * @param claim_pins The PINs to use for UART TX, RX, RTS and CTS
 * @return The UART_BUS number if a UART peripheral and all PINs were successfully claimed, UART_BUS_NONE otherwise
 */
UART_BUS uart_claim( uart_pin_configuration * claim_pins );

/**
 * Releases ownership of the specified UART peripheral and associated PINs.  Will also perform a close of the UART.
 * @param uart The UART to release, given in uart_claim()
 */
void uart_release( UART_BUS uart );

/**
 * Opens a previously claimed UART for communication.
 * uart_line_config specify specific line configuration like the baud rate or parity.
 * @param uart The UART to open, given in uart_claim()
 * @param uart_line_config Specify specific line configuration like the baud rate or parity..
 * @param uart_buffer_config Specify a reception buffer.
 * @param uart_dma_config Specify dma configuration of this uart port if it will transmit/receive data via DMA.
 * @return True if UART opened successfully, false otherwise.
 */
bool uart_open( UART_BUS uart, UART_LINE_CONFIGURATION *uart_line_config, uart_buffer_configuration *uart_buffer_config, UART_DMA_CONFIGURATION *uart_dma_config );

/**
 * Writes a buffer to an opened uart and calls a finished_with_buffer_func call back when it finish.
 * @note callback will be called in an interrupt context.
 * @param uart The UART to write to, given in uart_claim()
 * @param buffer Pointer to the buffer to write through the uart.
 * @param length Length of the buffer to write.
 * @param params Parameter to pass to finished_with_buffer_func.
 * @param finished_with_buffer_func function to call when the buffer is fully transmitted. it will be called in
 * the way finished_with_buffer_func(buffer, length, params)
 * @return
 */
bool uart_write( UART_BUS uart, const void *buffer, uint16 length, void *params, UART_TX_CALLBACK finished_with_buffer_func );

/**
 * Close the specified UART.
 * Will leave the UART and associated PINs claimed so that they can't be claimed by another core.
 * @param uart The UART to close, given in uart_claim()
 */
void uart_close( UART_BUS uart );

/**
 * Returns true if there are pending transmissions.
 * It could be used to check that the UART can be closed and no transmissions in the queue are going to be interrupted.
 * @param uart The UART, given in uart_claim()
 * @return true if there are pending transmissions, false otherwise.
 */
bool uart_has_pending_transmissions(UART_BUS uart);

/**
 * Registers a receive callback that will be triggered depending on condition and size.
 * @note callback will be called in an interrupt context.
 * @param uart The UART, given in uart_claim()
 * @param condition Condition on which the callback will be triggered.
 * @param size If condition implies a size this will be used.
 * @param callback Receive callback to call.
 */
void uart_register_rx_callback(UART_BUS uart, UART_RX_CONDITION condition, uint16 size, UART_RX_CALLBACK callback);
/**
 * Registers a parity error callback that will be triggered.
 * @note callback will be called in an interrupt context.
 * @param uart The UART, given in uart_claim()
 * @param callback Receive callback to call.
 */
void uart_register_parity_error_callback( UART_BUS uart, UART_PARITY_ERROR_CALLBACK callback );

/**
 * Registers a frame error callback that will be triggered.
 * @note callback will be called in an interrupt context.
 * @param uart The UART, given in uart_claim()
 * @param callback Receive callback to call.
 */
void uart_register_frame_error_callback( UART_BUS uart, UART_PARITY_ERROR_CALLBACK callback );

#if defined (UART_DRIVER_CONFIG_USE_VETOS_IN_STEAD_OF_TIMERS)
/**
 * UART sleep and wakup status according to the uart tx state.
 */
bool uart_is_need_awake(void);
#endif

/**
 * |Put in for slip, writes a char to the uart, blocks until written
 * @param uart The UART, given in uart_claim()
 * @param c the char to write
 */
void uart_write_immediately_char(UART_BUS uart, char c);

/**
 * Used to enable or disable software flow control
 * @param uart The UART, given in uart_claim()
 * @param enable True if software flow control is to be enabled
 */
void uart_enable_software_flow_control( UART_BUS uart, bool enable );

/**
 * Set the trigger levels which to cause software flow control to be actioned
 * XOFF will be transmitted if RX buffer exceeds the water margin level
 * XON will be transmitted if the RX buffer falls back to the water margin level
 * @param uart The UART, given in uart_claim()
 * @param lower_water_margin The RX buffer level at which software flow control is de-asserted
 * @param upper_water_margin The RX buffer level at which software flow control is asserted
 * @return True if water margins for flow control are set, false otherwise
 */
bool uart_set_software_flow_control_water_margin( UART_BUS uart, uint16 lower_water_margin, uint16 upper_water_margin );

/**
 * Obtains a pointer to the function used to assert software rx flow control for a uart.
 * The function obtained is called to trigger the sending of XON or XOFF
 * @param uart The UART, given in uart_claim()
 */
UART_ASSERT_SOFTWARE_FLOW_CONTROL_FUNCTION uart_get_software_rx_flow_control_assert_function( UART_BUS uart );

/**
 * Obtains a pointer to the function used to assert software tx flow control for a uart.
 * The function obtained is called in response to receiving an XON or XOFF and is used to gate our own TX
 * @param uart The UART, given in uart_claim()
 */
UART_ASSERT_SOFTWARE_FLOW_CONTROL_FUNCTION uart_get_software_tx_flow_control_assert_function( UART_BUS uart );

/**
 * Flush all data held in the supplied UART's RX buffer
 * @param uart The UART, given in uart_claim()
 * @return Number of bytes flushed from UART's RX buffer
 */
uint16 uart_flush_data( UART_BUS uart );

/**
 * Retrieves any outstanding data received that has not been claimed by a client
 * Will copy data, up to dest_buffer_length bytes, into the supplied dest_buffer
 * Any data copied will be marked as consumed (sent) so there is no need to call a release function.
 * @param uart The UART, given in uart_claim()
 * @param dest_buffer Pointer to buffer to receive the data
 * @param dest_buffer_length Length of dest_buffer
 * @param errors Will be set to indicate what type of errors, if asny, occurred during reception of the data obtained
 */
uint16 uart_get_data( UART_BUS uart, uint8 *dest_buffer, uint16 dest_buffer_length, UART_ERROR *errors );

/** @} end of group DRIVER_CMSIS_UART */

#endif /* UART_H_ */
