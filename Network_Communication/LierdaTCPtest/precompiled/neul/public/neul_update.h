/******************************************************************************
 * @brief    Update Functions for Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_UPDATE_H_
#define LIB_NEUL_UPDATE_H_

#include "neul_error_types.h"
#include "reboot.h" 
#include "neul_update_types.h"

/** @defgroup libNEUL_UPDATE Hi21XX libNEUL Update API
 * Hi21XX libNeul Update API
 * @ingroup LIBNEUL
 * @{
 * */

/** Flash erase Callback Function
 * @param result flash erased result which true indicating succeeded or false indicating failed
 * @return none
 */
typedef void (*NEUL_UPDATE_FLASH_ERASE_DONE)(bool result);

typedef void (*NEUL_UPDATE_PACKAGE_PARSE_CNF)(uint8 status);

typedef void (*NEUL_UPDATE_PACKAGE_PROCESS_CNF)(uint8 status);

typedef void (*NEUL_UPDATE_GET_PACKAGE_NAME)(uint16 pkgname_length, uint8 *pkgname);

typedef void (*NEUL_UPDATE_GET_PACKAGE_VERSION)(uint16 version_length, uint8 *version);

/** Flash write Callback Function
 * @param result flash written result which 0 indicating succeeded or indicating failed otherwise
 * @return none
 */
typedef void (*NEUL_UPDATE_FLASH_WRITE_DONE)(uint8 result);

/** Return UE update status
 * @param update_status status of update
 * @return success or error
 */
NEUL_RET neul_update_get_update_status(NEUL_UPDATE_OTA_PACKAGE_STATUS *update_status);

/** Return UE update result
 * @param update_result update result
 * @return success or error
 */
NEUL_RET neul_update_get_update_result(NEUL_UPDATE_STAGE *update_result);

/** Reset UE update result
 * @return success or error
 */
NEUL_RET neul_update_reset_update_result(void);

/** Request the UE initiates an update
 * @param status status
 * @return success or error
 */
NEUL_RET neul_update_firmware_upgrade_req(NEUL_UPDATE_RET *status);

/** Request to parse the package
 * @return success or error
 */
NEUL_RET neul_update_package_parse_req(void);

/** Request to process the package
 * @return success or error
 */
NEUL_RET neul_update_package_process_req(void);

/** Get package name from FOTA package
 * @return success or error
 */
NEUL_RET neul_update_package_get_package_name_req(void);

/** Get version number from FOTA package
 * @return success or error
 */
NEUL_RET neul_update_package_get_package_version_req(void);

/** Write fota package data to flash
 * @param buffer_length
 * @param buffer
 * @param offset
 * @param buffered
 * @return success or error
 */
NEUL_RET neul_update_package_flash_write(uint32 buffer_length, uint32 buffer, uint32 offset, bool *buffered);

/** Reset UE update result
 * @param queued if erase request queued
 * @return success or error
 */
NEUL_RET neul_update_package_flash_erase(bool *buffered);

/** Get available space size for FOTA storage
 * @param pointer to flash space available
 * @return success or error
 */
NEUL_RET neul_update_package_get_available_flash(uint32 *available_size);

/** Request a region of flash for FOTA package
 * @param expected allocated flash size for udpate package
 * @param allocated return true if space allocated succeeded, and false otherwise
 * @return success or error
 */
NEUL_RET neul_update_package_allocate_flash(uint32 update_package_size, bool *allocated);

/** Register callback
 * @param callback to register
 * @return success or error
 */
NEUL_RET neul_update_register_flash_erase_done_callback(NEUL_UPDATE_FLASH_ERASE_DONE callback);

/** Register package parse callback
 * @param callback to register
 * @return success or error
 */
NEUL_RET neul_update_register_package_parse_cnf_callback(NEUL_UPDATE_PACKAGE_PARSE_CNF callback);

/** Register callback
 * @param callback to register
 * @return success or error
 */
NEUL_RET neul_update_register_package_process_cnf_callback(NEUL_UPDATE_PACKAGE_PROCESS_CNF callback);

/** Register callback
 * @param callback to register
 * @return success or error
 */
NEUL_RET neul_update_register_package_get_package_name_cnf_callback(NEUL_UPDATE_GET_PACKAGE_NAME callback);

/** Register callback
 * @param callback to register
 * @return success or error
 */
NEUL_RET neul_update_register_package_get_package_version_cnf_callback(NEUL_UPDATE_GET_PACKAGE_VERSION callback);

/** Register callback
 * @param callback to register
 * @return success or error
 */
NEUL_RET neul_update_register_flash_write_done_callback(NEUL_UPDATE_FLASH_WRITE_DONE callback);

/** @} end of group libNEUL_UPDATE */

#endif /* LIB_NEUL_UPDATE_H_ */
