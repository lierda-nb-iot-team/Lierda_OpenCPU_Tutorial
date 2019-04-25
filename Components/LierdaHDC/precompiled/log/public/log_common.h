/******************************************************************************
 * @brief    common logging producer interface - need to change name of log.h in all the protocol core files
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LOG_COMMON_H_
#define LOG_COMMON_H_

/** @defgroup libNEUL_LOG Hi21XX Log Writer
 * Hi21XX Log Writer
 * @ingroup HI21XX_MODULES
 * @{
 * */

#include "neulfw.h"
#if defined BUILD_APPLICATION_NBIOT
#include "stack_message.h"
#endif
#include "panic.h"
#include "neul_error_types.h"
#include "neul_log_types.h"
#include "log_buffer_common.h"

void log_init( void );

void log_level_init( void );

void log_full_log_enabled_init( void );

void log_init_after_rtos( void );

/** Log the given log message
 * @param module module identifier
 * @param verbosity verbosity level
 * @param flags additional flags used to identify XLOG/ERRLOG events
 * @param id  log message id within module
 * @param len length of buffer
 * @param buffer payload to log, null if no payload
 */
void log_event(log_module_id_t module, log_verbosity_t verbosity, log_flags_t flags, log_message_id_t id, uint16 len, const uint8 *buffer );

/** Log the given log message
 * @param module module identifier
 * @param verbosity verbosity level
 * @param flags additional flags used to identify XLOG/ERRLOG events
 * @param id  log message id within module
 * @param str payload to log, null if no payload
 */
void log_event_string(log_module_id_t module,  log_verbosity_t verbosity, log_flags_t kv_flags,log_message_id_t id, const char *str, ...);

/**
 * Check if the log is enabled.
 * @return true if the log is enabled.
 */
bool log_is_enabled(void);

/**
 * Sets a verbosity level and enables logging if it was disabled.
 * Any log_event calls with a verbosity v < verbosity will be ignored.
 * @param verbosity new verbosity.
 */
void log_set_verbosity(log_verbosity_t verbosity);

/**
 * gets a verbosity level
 * @return verbosity level.
 */
log_verbosity_t log_get_verbosity(void);

/**
 * Disables logging. If called, any log_event calls will be ignored.
 */
void log_disable_logging( void );

/** Check if full log is enabled. 
 * @return true if output full log, false will restricte to output privacy persional data in log
 */
bool log_full_log_enabled(void);

/** Set local log level from system log level
 * @return true if log level was successfully set to the specified level
 */
NEUL_RET log_set_local_log_level(NEUL_LOG_LEVEL level);

/** Get current log level
 * @return current log level
 */
NEUL_LOG_LEVEL log_get_local_log_level (void);

/** @} end of group libNEUL_LOG */

#endif /* LOG_COMMON_H_ */
