/******************************************************************************
 * @brief    LOG MEMORY SECTION INTERFACE
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_LIB_LOG_PRIVATE_LOG_MEMORY_SECTION_H_
#define SRC_LIB_LOG_PRIVATE_LOG_MEMORY_SECTION_H_

#include "log_memory_definitions.h"

/** @addtogroup NONOS_DRIVERS_LOG
 * @{
 * */

/**
 * Log memory section parameters
 */
typedef struct
{
    uint8 * start;
    uint16 length;
} log_memory_section_params; //lint !e959

/**
 * get the section data for a given region
 * @param section log memory section
 * @param section_data pointer where the section data will be stored
 */
void log_memory_section_get(LOG_MEMORY_REGION_SECTION section, log_memory_section_params * section_data);

/**
 * Get a pointer to the section control for a given log memory section
 * @param section log memory section
 * @return pointer to the section control for log memory section
 */
log_memory_section_control *  log_memory_section_get_control( LOG_MEMORY_REGION_SECTION section );

/** Macro to check if a pointer is in the log memory region*/
#define POINTER_IN_LOG_MEMORY_REGION(x)  ( ( (uint32)(x) & ~(LOG_REGION_MEMORY_LENGTH -1) ) == ( (uint32) LOG_REGION_MEMORY_START) )

/** @} end of NONOS_DRIVERS_LOG */

#endif /* SRC_LIB_LOG_PRIVATE_LOG_MEMORY_SECTION_H_ */
