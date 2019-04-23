/******************************************************************************
 * @brief    BOUDICA  AT UART DRIVER DEFINITIONS
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef  APP_AT_UART_DRIVER_H_
#define  APP_AT_UART_DRIVER_H_

#include "hal_uart_definitions.h"
#include "neulfw.h"
#include "hal_lpuart.h"
#include "app_at_main.h"
#include "app_at_uart_etypes.h"

/** @defgroup libNEUL_APP_AT_INT Hi21XX AT Command Processor Internal
 * Hi21XX AT Command Processor API
 * @ingroup libNEUL_APP_AT
 * @{
 * */

#define AT_UART_DEFAULT_TIMEOUT          3
#define AT_UART_MAX_TIMEOUT              30
#define AT_UART_STORE_ENABLE             1
#define AT_UART_DEFAULT_SYNC_MODE        HAL_LPUART_SYNCMODE_EARLIER
#define AT_UART_MAX_SYNC_MODE            3
#define AT_UART_DEFAULT_BAUD_RATE        AT_UART_BAUD_RATE_9600
#define AT_UART_STOPBITS_1               1
#define AT_UART_STOPBITS_2               2
#define AT_UART_DEFAULT_STOPBITS         AT_UART_STOPBITS_1
#define AT_UART_DEFAULT_PARITY           UART_PARITY_NONE
#define AT_UART_DEFAULT_SW_FLOW_CONTROL  AT_UART_FLOW_CONTROL_DISABLED

typedef enum
{
    AT_UART_FLOW_CONTROL_DISABLED = 0,
    AT_UART_FLOW_CONTROL_ENABLED  = 1
} AT_UART_FLOW_CONTROL;

typedef enum
{
    AT_UART_STATUS_FREE = 0,
    AT_UART_STATUS_IN_PROCESS = 1,
}AT_UART_STATUS;

typedef enum
{
    AT_UART_BAUD_RATE_2400   = 2400,
    AT_UART_BAUD_RATE_4800   = 4800,
    AT_UART_BAUD_RATE_9600   = 9600,
    AT_UART_BAUD_RATE_57600  = 57600,
    AT_UART_BAUD_RATE_115200 = 115200,
    AT_UART_BAUD_RATE_230400 = 230400,
    AT_UART_BAUD_RATE_460800 = 460800,
    AT_UART_BAUD_RATE_921600 = 921600,
}AT_UART_BAUD_RATE;

/** AT UART received at command notification callback.
 * @param callback to received at command notifications. NULL means no callback
 */
void at_uart_set_received_at_notify_callback (at_uart_received_at_notify callback);

/**
 * Mark the AT UART need to change baud.
 *@param   at_uart_config the config to change.
 *@param   store store config if true.
 *@param   timeout indicating the time to wait for communication before switching back to the original speed, uint second.
 *@return  true if success.
 */
bool at_uart_mark_need_change_config(at_uart_config uart_config, bool store, uint32 timeout);

/**
 * Mark that the AT UART needs to change to a PPP UART
 * @return true if this is possible, false otherwise
 */
bool at_uart_mark_need_change_to_ppp(void);

/**
 * Mark that the AT UART needs to re-take control of the UART
 */
void at_uart_mark_need_change_to_at(void);

/**
 * Switch the AT UART to new config.
 * This should be called after delayed_async_output_list.
 *@param   None.
 *@return   None.
 */
void at_uart_switch_to_new_config(void);

/**
 * Ensure switch the AT UART to new config.
 *@param   None.
 *@return   None.
 */
void at_uart_mark_ensure_change_config(void);

/**
 * Store the AT UART's new config.
 *@param   None.
 *@return  true if success.
 */
bool at_uart_store_new_config(void);

/**
 * Checks if we should switch to ppp, and does it if we should
 * @return
 */
void at_uart_switch_to_ppp(void);

/**
 * Initialises the AT UART when RTOS functions are available.
 * This should be called before the RTOS scheduler starts, but when we can create mutexes.
 *@param    None.
 *@return   None.
 */
void at_uart_init( void );

/**
 * Deinits the AT UART
 */
void at_uart_deinit( void );

/** Claim at uart before output at format data.
 *@param    None.
 *@return   None.
 */
void at_uart_claim( void );

/** Release at uart after output at format data.
 *@param    None.
 *@return   None.
 */
void at_uart_release( void );

/** The at uart write function .
 *@param    buffer. the pointer of write data buffer;
 *@param    length. the data length of write data.
 *@return   None.
 */
void at_uart_write(const uint8 * buffer, uint32 length );

/** The  function for print log.
 *@param  str format to print.
  *@return   None.
 */
void at_uart_log_string (const char *str, ...);

/** Get at status.
 *@return   0,  free status no AT cmd to deal with. 1, busy status is dealing with input AT cmd.
 */
AT_UART_STATUS at_uart_get_status(void);

/** Get at status.
 *@return   pointer of at uart receive buffer.
 */
uint8* at_uart_get_receive_buffer(void);

/** Get at parity error status.
 *@return   at_uart_buffer_parity_err_flag.
 */
bool at_uart_get_parity_error_status(void);


/** Get at frame error status.
 *@return   at_uart_buffer_frame_err_flag.
 */
bool at_uart_get_frame_error_status(void);


/** Get at buffer error status.
 *@return   at_uart_buffer_err_flag.
 */
bool at_uart_get_buffer_error_status(void);

/** Set at parity error status.
 *@param  status to set.
 *@return None.
 */
void at_uart_set_parity_error_status(bool status);

/** Set at frame error status.
 *@param  status to set.
 *@return None.
 */
void at_uart_set_frame_error_status(bool status);

/** Set at buffer error status.
 *@param  status to set.
 *@return None.
 */
void at_uart_set_buffer_error_status(bool status);

/** Mark at uart can receive, after process at cmd.
 */
void at_uart_mark_can_receive(void);

/**
 * Re-take the UART and reinitialise if necessary
 * @return True if we reinitialised
 */
bool at_uart_should_restart_at(void);

/** Check baud_rate is valid or not.
 *@param  baud_rate baud_rate to check.
 *@param  high_speed baud_rate is high speed or not.
 *@return true if valid.
 */
bool at_uart_baud_rate_valid_check(uint32 baud_rate, bool* high_speed);

/** read uart current config.
 *@param  at_uart_config the pointer of uart config.
 *@return true if at_uart_config get valid config data.
 */
bool at_uart_read_current_config(at_uart_config* uart_config);

/** @} end of group libNEUL_APP_AT_INT */

#endif
