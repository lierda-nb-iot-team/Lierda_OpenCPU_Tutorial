/******************************************************************************
 * @brief    LOG BUFFER READER MODULE INTERFACE
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_LIB_LOG_PRIVATE_LOG_BUFFER_READER_H_
#define SRC_LIB_LOG_PRIVATE_LOG_BUFFER_READER_H_

#include "log_memory_definitions.h"

/** @addtogroup NONOS_DRIVERS_LOG
 * @{
 * */

typedef enum {
    LOG_READER_RET_OK,
    LOG_READER_RET_BUSY,
    LOG_READER_RET_ERROR,
    LOG_READER_RET_TIMEDOUT,
    LOG_READER_RET_ERROR_OVERFLOW_ON_DISCARDING,
    LOG_READER_RET_THERE_IS_NO_NEXT_MESSAGE,
    LOG_READER_RET_ERROR_IN_PARAMS,
    LOG_READER_RET_ERROR_TRYING_TO_DISCARD_WHEN_EMPTY,
    LOG_READER_RET_ERROR_CORRUPT_SHARED_MEMORY
} LOG_READER_RET;


/**
 * Initialize the log buffer reader module
 */
LOG_READER_RET log_buffer_reader_init( void );

/**
 * Lock the next message in the log buffer and returns its parameters.
 * @param lmsec log memory section of the region holding the next message
 * @param lb_header The log_buffer_header for the next log will be stored here
 * @return LOG_READER_RET_OK if the next message was locked, LOG_READER_RET_THERE_IS_NO_NEXT_MESSAGE if there is no
 * next message to lock, an error code otherwise.
 */
LOG_READER_RET log_buffer_reader_lock_next(LOG_MEMORY_REGION_SECTION * lmsec, log_buffer_header * lb_header);

/**
 * Claim the next message in the buffer.
 * @param lmsec log memory section
 * @param r1 (return value) a pointer to the first part of the message
 * @param len1 (return value) length of the first part of the message
 * @param r2 (return value) a pointer to the first part of the message ( in case is not in a contiguous memory block)
 * @param len2 (return value) length of the first part of the message  ( in case is not in a contiguous memory block)
 * @return LOG_READER_RET_OK or an error code
 */
LOG_READER_RET log_buffer_reader_claim_next(LOG_MEMORY_REGION_SECTION lmsec, uint8 ** r1, uint16 * len1, uint8 ** r2, uint16 * len2);

/**
 * Discard a previously claimed message
 * @param lmsec log memory section
 * @return LOG_READER_RET_OK or an error code
 */
LOG_READER_RET log_buffer_reader_discard (LOG_MEMORY_REGION_SECTION lmsec);


/**
 * Get the used space in a log memory section.
 * @param lmsec log memory section
 * @param used_space used space in bytes
 * @return LOG_READER_RET_OK or an error code
 */
LOG_READER_RET log_buffer_get_used_space(LOG_MEMORY_REGION_SECTION lmsec, uint16 * used_space);

/** @} end of NONOS_DRIVERS_LOG */

#endif /* SRC_LIB_LOG_PRIVATE_LOG_BUFFER_READER_H_ */
