/******************************************************************************
 * @brief    LOG UART MODULE INTERFACE
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LOG_UART_H_
#define LOG_UART_H_

/** @defgroup libNEUL_LOGREADER Hi21XX Log Reader
 * Hi21XX Log Reader
 * @ingroup HI21XX_MODULES
 * @{
 * */

#if defined USE_CMSIS_OS

#include "log_common.h"
#include "unit_test.h"
#include "neul_error_types.h"
#include "log_memory_definitions.h"
#include "memory_config.h"

#define LOG_UART_PROTOCOL_LOG_WATERMARK_VALUE_ON_INIT  0
#define LOG_UART_PROTOCOL_LOG_WATERMARK_VALUE_HIGH     ( (PROTOCOL_CORE_LOGGING_LENGTH) * 8 / 10 )

typedef enum
{
    NXLOG_OPERATION_ENABLE = 0,
    NXLOG_OPERATION_DISABLE,
    NXLOG_OPERATION_DELETE,
    NXLOG_OPERATION_DUMP_TO_AT_UART,
    NXLOG_OPERATION_DUMP_TO_DEBUG_UART
}NXLOG_OPERATION;

/* Don't use strlen() for speed */
#define LOG_UART_PREFIX             "%DBG:"
#define LOG_UART_PREFIX_LENGTH      5

/**
 * Initialises the uart logger before RTOS functions are available.
 */
UNIT_TEST_WRAPPABLE void log_uart_init(void);

/**
 * @brief output response to at uart callback
 * @param at_string The at string to send out through at uart.
 */
typedef void (*log_uart_output_response_to_at_uart_callback)(const char *at_string, uint16 len);

/**
 * Initialises the UART logging when RTOS functions are available.
 * This should be called before the RTOS scheduler starts, but when we can create mutexes.
 * @param enable_at_start indicate if logging should start immediately
 */
void log_uart_init_after_rtos(bool enable_at_start);

/**
 * Enable log uart output. Only operates if log_uart_init_after_rtos(false) was used to initialise logging.
 * This is mainly for testing purposes, and in production logging should be started with log_uart_init_after_rtos(true);
 */
void log_uart_enable(void);

/**
 * Triggers the uart logger.
 * It can be called from program context or ISR.
 */
void log_uart_trigger(void);

/**
 * Execute XLOG AT CMD
 * @param  cmd               Xlog AT CMD
 * @param  output_callback   callback for output response to at uart callback
 * @return FLOG_RET_OK       AT CMD Success
 *         FLOG_RET_ERROR    AT CMD Error
 */
NEUL_RET log_uart_nxlog_ctrl(NXLOG_OPERATION cmd, log_uart_output_response_to_at_uart_callback output_callback);

/**
 * Check if the xlog is enabled.
 * @return 1 if the xlog is enabled.
 */
uint32 log_uart_get_nxlog_state(void);

/**
 * Main log uart task
 * @param unused_p unused parameter
 */
void log_main( void *unused_p );

/**
 * Update the watermark level for a given logging region.
 * @note Currently just LOG_MEMORY_REGION_SECTION_1 is supported.
 */
void log_uart_update_watermark_level(LOG_MEMORY_REGION_SECTION logmemregion, uint16 new_watermark_val);


#else
#error "log to uart not implemented in non-os version"
#endif // defined USE_CMSIS_OS

/** @} end of group libNEUL_LOGREADER */

#endif // LOG_UART_H_
