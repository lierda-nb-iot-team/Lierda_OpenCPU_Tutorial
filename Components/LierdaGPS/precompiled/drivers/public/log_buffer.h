/******************************************************************************
 * @brief    LOG BUFFER INTERFACE
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_DRIVERS_LOG_BUFFER_H_
#define SRC_DRIVERS_LOG_BUFFER_H_

#include "log_buffer_common.h"
#include "log_memory_section.h"

//lint -esym(759, log_buffer_reader_claim_next)

/** @defgroup NONOS_DRIVERS_LOG Hi21XX non-OS Log Driver
 * Hi21XX non-OS Log Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

typedef enum {
    LOG_RET_OK,
    LOG_RET_ERROR_IN_PARAMETERS,
    LOG_RET_ERROR_NOT_ENOUGH_SPACE,
    LOG_RET_ERROR_CORRUPT_SHARED_MEMORY
} LOG_RET;

/**
 * Initialize the log buffer module to log in the given log memory region section.
 * @return LOG_RET_OK or an error value
 */
void log_buffer_init(LOG_MEMORY_REGION_SECTION logsec);

/**
 * Write a log message to the log buffer
 * @param log_msg log message header
 * @param buffer log buffer
 * @param time_us time when the log was generated
 * @param was_empty if a pointer != NULL is given it will store a boolean indicating the buffer was empty(true) or not(false) when the write was done.
 * @return LOG_RET_OK or an error value
 */
LOG_RET log_buffer_message(const log_message_header_t *log_msg, const uint8 *buffer, uint32 time_us, bool * was_empty);

/**
 * Get the available space for the next message
 * @param av available space will be stored here
 * @return LOG_RET_OK or an error code
 */
LOG_RET log_buffer_get_available_for_next_message(uint16 * av);

/** @} end of NONOS_DRIVERS_LOG */

#endif /* SRC_DRIVERS_LOG_BUFFER_H_ */
