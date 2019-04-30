/******************************************************************************
 * @brief     AT Internal Command Parser header
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef    _APP_AT_CMD_PARSE_H_
#define    _APP_AT_CMD_PARSE_H_
#include "neul_error_types.h"

/** @addtogroup libNEUL_APP_AT_INT
 * @{
 * */

/**
 * @Get internal at cmd table size, internal cmd table is const.
 * @return The size of internal at cmd table
 */
uint8 at_get_internal_cmd_table_size(void);

/**
 * @Get internal at cmd table address, internal cmd table is const.
 * @return The address of internal at cmd table
 */
const AT_CMD_CB_s * at_get_internal_cmd_table_address(void);

/** @} end of group libNEUL_APP_AT_INT */

#endif
