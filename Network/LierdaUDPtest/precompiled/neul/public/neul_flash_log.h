/******************************************************************************
 * @brief       NEUL Flash LOG FOR THE Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_FLASH_LOG_H_
#define LIB_NEUL_FLASH_LOG_H_

#include "neul_error_types.h"
#include "platform_definitions.h"
#include "neul_log_types.h"

/** @addtogroup libNEUL_LOGAPI
 * @{
 * */

/**
 * Register flash logging buffer
 * @param log_address pointer to address of log header
 * @return NEUL_RET_OK or error code
 */
NEUL_RET flash_log_register(void *log_address);

/**
 * Initiate a write to flash logging buffer
 * @param index Start address to write from (word aligned)
 * @param length to write in bytes
 * @return NEUL_RET_OK or error code
 */
NEUL_RET flash_log_write(uint16 index, uint16 len);

/**
 * Read from flash logging buffer
 * @param buffer to read into
 * @param buffer_size size of buffer passed in
 * @param length amount of data returned
 * @return NEUL_RET_OK or error code
 */
NEUL_RET flash_log_read(uint32 buffer, uint16 buffer_size, uint16 *length);

/** @} end of group libNEUL_LOGAPI */

#endif /* LIB_NEUL_FLASH_LOG_H_ */
