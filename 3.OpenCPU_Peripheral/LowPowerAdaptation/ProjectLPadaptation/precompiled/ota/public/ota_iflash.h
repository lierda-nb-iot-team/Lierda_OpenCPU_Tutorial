/******************************************************************************
 * @brief    ota iflash interface
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef    _OTA_IFLASH_H_
#define    _OTA_IFLASH_H_

#include "neulfw.h"
#include "ota.h"

/**
 * @file 
 * This file contains operation for accesing Cleopatra internal flash storage for the FOTA update package.
 * Writing to internal flash of Cleopatra is not a trivial matter: all cores need to tell the Security core
 * that it is safe to write to internal flash. Therefore, the Apps core has to request the flash write, and the 
 * Security core will perform it when it decides it is safe to do so.
 * 
 * There are facilities here for:
 *      - Erasing FOTA flash space
 *      - Querying FOTA flash space capacity.
 *      - Querying whether FOTA flash space is erased.
 *      - Writing to FOTA flash space.
 *
 * The write operation is asynchronous; when Security core is done with the flash write, it invokes an RPC 
 * call to the Apps core.
 *
 * Similarly, the erase operation is asynchronous; when Security core finishes, it invokes an RPC call to the Apps
 * core. Because the erase is a time-consuming operation, we prefer not do it if it's not absolutely necessary. A 
 * method to query whether the flash space is erased is provided as well.
 */

/**
 * Request to write data to internal flash, in the flash space dedicated
 * for the FOTA package. 
 * 
 * This is done in two steps. First, Security core buffers the write request, so
 * it can execute it when it is safe to acccess the internal flash. Once the buffered
 * request is executed, an RPC notification is sent to the Apps core, indicating the buffer
 * pointer passed by the corresponding remote_command_fota_write() request.
 *
 * @param buffer            Buffer with data to write.
 * @param offset            Offset, from the beginning of the FOTA flash space, where to write the buffer.
 * @param len               Buffer length.
 * @param done_callback     Callback to invoke when flash write is complete, given the function returned true.
 *
 * @return                  True, if the request was succesfully buffered. False, otherwise.
 */
bool ota_iflash_write(uint8* buffer, uint32 offset, uint16 length, OTA_FLASH_WRITE_DONE_CB done_callback);

/**
 * Erases the location in flash where FOTA package is stored.
 * Effectively, this wipes out the last FOTA package stored.
 * There will be an asynchronous confirmation when the operation is done.
 *
 * @param erase_callback    Callback to invoke when erase is done.
 * @return                  True, if the request was succesfully buffered. False, otherwise.
 */
bool ota_iflash_erase(OTA_FLASH_ERASE_DONE_CB erase_callback);

/**
 * Return capacity of FOTA flash space.
 *
 * @return  FOTA flash space capacity in bytes.
 */
uint32 ota_iflash_get_capacity(void);

/**
 * Initialise the FOTA update process such as allocate the FOTA related flash regions.
 *
 * @param none.
 *
 * @return True if initialised success or false if failue.
 */
bool initialise_fota(void);

/**
 * * register callbacks
 */
void ota_iflash_register_callback(void);

#endif // _OTA_IFLASH_H_
