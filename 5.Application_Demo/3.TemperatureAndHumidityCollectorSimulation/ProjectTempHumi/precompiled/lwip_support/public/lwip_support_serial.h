/******************************************************************************
 * @brief    lwip ts serial header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
 ******************************************************************************/

#ifndef SRC_LIB_LWIP_PLATFORM_TEST_SUITE_INCLUDE_TS_SERIAL_H_
#define SRC_LIB_LWIP_PLATFORM_TEST_SUITE_INCLUDE_TS_SERIAL_H_
#include "neulfw.h"
#include "platform_definitions.h"
#include "sio.h"
#include "uart.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

typedef void (*serial_data_callback)(void *, uint16, UART_RELEASE_FUNCTION);

/**
 * Sets the pins for the uart to use
 * @param uart_rx
 * @param uart_tx
 * @param uart_rtx
 * @param uart_ctx
 */
void neul_lwip_serial_set_pins(PIN uart_tx, PIN uart_rx, PIN uart_rtx, PIN uart_ctx);

/**
 * Sets the baud rate of the uart
 * @param uart_baud
 */
void neul_lwip_serial_set_baud(uint32 uart_baud);

/**
 * Sets the callback to use when UART data is received
 * @param callback
 */
void neul_lwip_serial_set_rx_callback(serial_data_callback callback);

/**
 * Deinits the lwip serial connection
 * @param uart_handler
 */
void neul_lwip_serial_deinit(const sio_fd_t uart_handler);

/** @} end of group LWIP_SUPPORT */

#endif
