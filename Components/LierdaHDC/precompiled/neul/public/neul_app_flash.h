/******************************************************************************
 * @brief    apps flash interface
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef SRC_LIB_NEUL_PUBLIC_NEUL_APP_FLASH_H_
#define SRC_LIB_NEUL_PUBLIC_NEUL_APP_FLASH_H_

#include "neul_app_flash_types.h"

/** @defgroup libNEUL_APPFLASH Hi21XX libNEUL Application Flash Interface
 * Hi21XX libNeul AppFlash API
 * @ingroup LIBNEUL
 * @{
 * */

/**
 * @brief app flash write callback
 * @param app flash write result
 */
typedef void (*neul_app_flash_write_callback)(APP_FLASH_RET result);

/**
 * @brief app flash erase callback
 * @param app flash erase result
 */
typedef void (*neul_app_flash_erase_callback)(APP_FLASH_RET result);

/** allocate a flash area for apps core use
 * @param size in pages
 * @return APP_FLASH_RET_OK on success or an error
 */
APP_FLASH_RET app_flash_alloc(uint8 buffer_pages);

/** free a flash area for apps core use
 * After calling app_flash_free() the erase request will operate in the background.
 * The flash pages can only be re-allocated once the background erase operation has completed.
 * Erasing pages requires both protocol and apps cores to:
 *  - not veto deep sleep
 *  - set the expected_wake_time that is long enough to allow pages to be erased
 * When the radio is operating, it may take some time before a long-enough window is
 * available to erase the requested pages.
 * @return APP_FLASH_RET_OK on success or an error
 */
APP_FLASH_RET app_flash_free(void);

/** erase 1 or more pages that were allocated
 * Erasing pages requires both protocol and apps cores to:
 *  - not veto deep sleep
 *  - set the expected_wake_time that is long enough to allow pages to be erased
 * @return APP_FLASH_RET_OK on success or an error
 */
APP_FLASH_RET app_flash_erase_pages(uint8 page_offset, uint8 pages);

/** write data to flash
 * Writes to flash require both protocol and apps cores to allow the write to happen when the system has time.
 * Writing data requires both protocol and apps cores to:
 *  - not veto deep sleep
 *  - set the expected_wake_time that is long enough to allow at least one word to be written
 * Rules for writing to flash:
 * o Writes must never write to the same byte twice without an erase operation in between
 * o Writes should never write to any 16-byte flash line (on a 16-byte boundary) more than 4 times before the page containing that line is erased
 * Failure to follow the above rules may result in corrupt flash data
 * @param buffer address of buffer to read from
 * @param length to write
 * @param offset to write to in flash
 * @return APP_FLASH_RET_OK on success or an error
 */
APP_FLASH_RET app_flash_write(uint32 buffer, uint32 length_to_write, uint32 offset);

/** read data from flash
 * @param offset to read from in flash
 * @param buffer address of buffer to write to
 * @param length to read
 * @return APP_FLASH_RET_OK on success or an error
 */
APP_FLASH_RET app_flash_read(uint32 offset, uint32 buffer, uint32 length_to_read);

/** pages of flash that the apps core can allocate
 * @param pages number of pages that could be allocated
 * @return APP_FLASH_RET_OK on success or an error
 */
APP_FLASH_RET app_flash_avail(uint8 *pages);

/** notification that security core has completed app flash operation
 * @param APP_FLASH_RET_OK on success or an error
 */
void app_flash_set_erase_callback(neul_app_flash_erase_callback callback);

/** notification that security core has completed app flash operation
 * @param APP_FLASH_RET_OK on success or an error
 */
void app_flash_set_write_callback(neul_app_flash_write_callback callback);

/** @} end of group libNEUL_APPFLASH */

#endif /* SRC_LIB_NEUL_PUBLIC_NEUL_APP_FLASH_H_ */
