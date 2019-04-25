/******************************************************************************
 * @brief    LOG MEMORY REGION DEFINITIONS
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_DRIVERS_NON_OS_LOG_SHARED_LOG_MEMORY_DEFINITIONS_H_
#define SRC_DRIVERS_NON_OS_LOG_SHARED_LOG_MEMORY_DEFINITIONS_H_

#include "memory_config.h"

/** @addtogroup NONOS_DRIVERS_LOG
 * @{
 * */

/**
 * LOG MEMORY REGIONS
 */
typedef enum {
    LOG_MEMORY_REGION_SECTION_0 =0,//!< LOG_MEMORY_REGION_SECTION_0
    LOG_MEMORY_REGION_SECTION_1,   //!< LOG_MEMORY_REGION_SECTION_1
    LOG_MEMORY_REGION_SECTION_2,   //!< LOG_MEMORY_REGION_SECTION_2
    LOG_MEMORY_REGION_MAX_NUMBER,  //!< LOG_MEMORY_REGION_MAX_NUMBER
} LOG_MEMORY_REGION_SECTION;

/**
 * Log memory control structure for every section
 */
typedef struct
{
    // reader controlled
    volatile uint16 read;
    volatile uint8 reserved_0;
    volatile uint8 reserved_1;

    // writer controlled
    volatile uint16 write;
    volatile uint8 reserved_2;
    volatile uint8 reserved_3;

} log_memory_section_control;

/**
 * Log memory area control structure
 */
typedef struct
{
    uint16 offset[LOG_MEMORY_REGION_MAX_NUMBER];
    uint16 length;
    log_memory_section_control section_control[LOG_MEMORY_REGION_MAX_NUMBER];
} log_memory_region_control;

/** Macro to get the pointer to the log memory control block */
#define LOG_MEMORY_REGION_CONTROL_BLOCK_POINTER ((const log_memory_region_control *) LOG_REGION_MEMORY_START)

/** @} end of NONOS_DRIVERS_LOG */

#endif /* SRC_DRIVERS_NON_OS_LOG_SHARED_LOG_MEMORY_DEFINITIONS_H_ */
