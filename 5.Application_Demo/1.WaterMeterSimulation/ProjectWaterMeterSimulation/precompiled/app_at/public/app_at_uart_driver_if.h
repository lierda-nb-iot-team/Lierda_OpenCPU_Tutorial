/******************************************************************************
 * @brief    APP AT UART Driver public interface
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef  APP_AT_UART_DRIVER_IF_H_
#define  APP_AT_UART_DRIVER_IF_H_

/**
 * Create the message queue needed by at_uart_recv_process()
 *@param    None.
 *@return   None.
 */
void at_uart_create_queue( void );

/**
 * AT UART received data processing thread
 *@param    args. Unused but needed for OS compatibility.
 *@return   None.
 */
void at_uart_recv_process( void *args );

#endif
