/******************************************************************************
 * @brief    Non Os specific EXTERNAL FLASH driver module header file
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/
#ifndef DRIVERS_CMSIS_EFLASH_EFLASH_H_
#define DRIVERS_CMSIS_EFLASH_EFLASH_H_

#include "neulfw.h"

/** @defgroup DRIVER_CMSIS_EFLASH Hi211X CMSIS eFlash Driver
 * CMSIS eFlash Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */

/**
 * Definitions of the operation result
 */
typedef enum
{
    EFLASH_RET_OK,      //!< operation successful
    EFLASH_RET_BUSY,    //!< eflash in process
    EFLASH_RET_UNINIT,  //!< SSP Is Not Init
    EFLASH_RET_ERROR    //!< operation other fail
}EFLASH_RET;

#define EFLASH_CHIP_SIZE            (1 << 21)
#define EFLASH_SECTOR_SIZE          (1 << 12)
#define EFLASH_32KBLOCK_SIZE        (1 << 15)
#define EFLASH_64KBLOCK_SIZE        (1 << 16)

/**
 * Initialise external flash
 * If external flash has been already initialized it just returns
 * @return true if success
 */
bool eflash_init(void);

/**
 * De-Initialise external flash subsystem
 * If external flash is not initialized or has been already deinitialized it just returns
 * @return Nothing
 */
void eflash_deinit(void);

/**
 * Write data into external flash
 * @param addr the external flash write address
 * @param buff write data address
 * @param length write data length
 * @return write data count
 */
uint16 eflash_write_data(uint32 addr, uint8* buff, uint16 length);

/**
 * Read data from external flash
 * @param addr the external flash read address
 * @param buff read data address
 * @param length read data length
 * @return read data count
 */
uint16 eflash_read_data(uint32 addr, uint8* buff, uint16 length);

/**
 * Change external flash address to Sector ID
 * @param addr external flash address
 * @param id   external flash id
 * @return     EFLASH_OK    external flash address change to sector id succ
 *             EFLASH_ERROR external flash address is illegal
 */
EFLASH_RET eflash_get_sector_id(uint32 addr, uint16* id);

/**
 * Erase external flash in size of sector-4K
 * @param sector_id erase zone
 * @return  EFLASH_OK    Erase external flash in size of sector succ
 *          EFLASH_ERROR Erase external flash in size of sector fail
 */
EFLASH_RET eflash_sector_erase(uint16 sector_id);

/**
 * Change external flash address to 32KBlock ID
 * @param addr external flash address
 * @param id   external flash id
 * @return     EFLASH_OK    external flash address change to 32kblock id succ
 *             EFLASH_ERROR external flash address is illegal
 */
EFLASH_RET eflash_get_32kblock_id(uint32 addr, uint16* id);

/**
 * Erase external flash in size of 32KBlock-32K
 * @param sector_id erase zone
 * @return  EFLASH_OK    Erase external flash in size of 32KBlock succ
 *          EFLASH_ERROR Erase external flash in size of 32KBlock fail
 */
EFLASH_RET eflash_32kblock_erase(uint16 block_id);

/**
 * Change external flash address to 64KBlock ID
 * @param addr external flash address
 * @param id   external flash id
 * @return     EFLASH_OK    external flash address change to 64KBlock id succ
 *             EFLASH_ERROR external flash address is illegal
 */
EFLASH_RET eflash_get_64kblock_id(uint32 addr, uint16* id);

/**
 * Erase external flash in size of 64KBlock-64K
 * @param sector_id erase zone
 * @return  EFLASH_OK    Erase external flash in size of 64KBlock succ
 *          EFLASH_ERROR Erase external flash in size of 64KBlock fail
 */
EFLASH_RET eflash_64kblock_erase(uint16 block_id);

/**
 * Erase external flash ALL chip
 * @param None
 * @return  EFLASH_OK    Erase external flash all chip succ
 *          EFLASH_ERROR Erase external flash all chip fail
 */
EFLASH_RET eflash_chip_erase(void);

/**
 * Read external flash id
 * @param id  id pointer
 * @param len min buffer length, min value is 3
 * @return     EFLASH_OK    read external flash id succ
 *             EFLASH_ERROR read external flash id fail
 */
EFLASH_RET eflash_read_id(uint8* id, uint8 len);

/**
 * Check external flash is available
 * @param return true it is available, false it is not available
 */
bool eflash_is_available(void);

/** @} end of group DRIVER_CMSIS_EFLASH */

#endif // DRIVERS_CMSIS_EFLASH_EFLASH_H_
