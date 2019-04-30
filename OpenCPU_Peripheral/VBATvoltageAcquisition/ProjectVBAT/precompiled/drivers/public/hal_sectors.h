/******************************************************************************
 * @brief    header file for the hal_sectors
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef HAL_SECTORS_H_
#define HAL_SECTORS_H_

#include "neulfw.h"

/** @defgroup DRIVER_HAL_SECTORS Hi211X HAL Sectors Driver
 * HAL Sectors Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

// HAL sectors API


/**he size of the RAM assigned to the heap in internal RAM (in octets)*/
extern const uint32 hal_sectors_ram_heap_size;

/**The pointer to the start of the external RAM assigned to the internal RAM heap*/
extern const void *hal_sectors_ram_heap_start;

/**The total size of the RAM (in octets)*/
extern const uint32 hal_sectors_ram_size;

/**The start address of RAM*/
extern const void* hal_sectors_ram_start;

#if defined(BUILD_APPLICATION_SSB)
/**The number of flash pages*/
extern const uint32 hal_sectors_flash_region_pages;

/**The end of the flash region */
extern const void * hal_sectors_flash_region_end;
#endif /* BUILD_APPLICATION_SSB */

/** @} end of group DRIVER_HAL_SECTORS */

#endif /* HAL_SECTORS_H_ */
