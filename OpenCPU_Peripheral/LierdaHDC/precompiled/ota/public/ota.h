/******************************************************************************
 * @brief OTA module handling interface
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/
#ifndef    _OTA_H_
#define    _OTA_H_

#include "neulfw.h"
#include "platform_definitions.h"
#include "neul_update.h"

/** @defgroup libNEUL_OTA Hi21XX OTA Upgrade
 * Hi21XX OTA Upgrade
 * @ingroup HI21XX_MODULES
 * @{
 * */

#define OTA_PACKAGE_BUFF_SIZE           (512)
#define MAX_PKGINFO_LENGTH              (100)

typedef enum
{
    OTA_UPDATE_METHOD_LWM2M, //!< Update through LwM2M
    OTA_UPDATE_METHOD_AT, //!< Update through AT
} OTA_UPDATE_METHOD;


typedef enum
{
    OTA_PACKAGE_INFO_NAME,
    OTA_PACKAGE_INFO_VERSION,
    OTA_PACKAGE_INFO_UNSUPPORTED
} OTA_PACKAGE_INFO;

/**
 * Callback for Flash write completion.
 * @param result flash written result which 0 indicating succeeded or indicating failed otherwise
 * @return none
 */
typedef void (*OTA_FLASH_WRITE_DONE_CB)(uint8 result);

/**
 * Callback for Flash erase completion.
 */
typedef void (*OTA_FLASH_ERASE_DONE_CB)(void);

typedef void (*OTA_UPGRADE_REQ_CB)(uint8 state);

typedef void (*OTA_PARSE_REQ_CB)(uint8 state);

typedef void (*OTA_PROCESS_REQ_CB)(uint8 state);

typedef void (*OTA_PACKAGE_INFO_REQ_CB)(void);

typedef uint8 *(*OTA_GET_PACKAGE_INFO_BUFF_CB)(uint16 len);

/**
 * Ota poll process
 */
void ota_poll(void);

/**
 * OTA module initializaton
 */
void ota_init(void);

/**
 * before erase package area, register erase callback
 */
NEUL_UPDATE_RET ota_package_init(OTA_FLASH_ERASE_DONE_CB callback);

/**
 * Check whether the update package relevant flash area erasing is OK.
 * @return true if erasing OK, false if erasing failed
 */
bool ota_check_flash_erased_result(void);

/**
 * Download package into storage medium
 * Use external flash as storage medium, it wil auto erase
 * Internal flash not support now
 *@param offset package offset
 *@param buff   data buffer
 *@param len    data length
 *@return NEUL_UPDATE
 */
NEUL_UPDATE_RET ota_package_download(uint32 offset, const uint8 * buff, uint16 len, OTA_FLASH_WRITE_DONE_CB callback);

/**
 * Upload package from storage medium
 * Use external flash as storage medium
 * Internal flash not support now
 *@param offset package offset
 *@param buff   data buffer
 *@param len    data length
 *@return NEUL_UPDATE
 */
NEUL_UPDATE_RET ota_package_read(uint32 offset, uint8* buff, uint16 len);

/**
 * Ota package parse request
 * @param callback package parse finished callback
 * @return OK if the parse request sending succeeded or ERROR otherwise
 */
NEUL_UPDATE_RET ota_package_parse_req(OTA_PARSE_REQ_CB callback);

/**
 * Ota package validity request
 */
NEUL_UPDATE_RET ota_package_process_req(OTA_PROCESS_REQ_CB callback);

/**
 * Ota package upgrade request
 */
NEUL_UPDATE_RET ota_package_upgrade_req(void);

/**
 * Ota package info getting request
 * @param callback callback function when package_info is confirmed
 * @param get_buff callback function when get the buffer to store the confirmed package_info
 * @param type     package_info gotten type
 * @return NEUL_UPDATE_RET_OK succ OTHERS fail
 */
NEUL_UPDATE_RET ota_get_package_info_req(OTA_PACKAGE_INFO_REQ_CB callback, OTA_GET_PACKAGE_INFO_BUFF_CB get_buff, OTA_PACKAGE_INFO type);

/**
 * Get update method
 * @param update_method OTA_UPDATE_METHOD_AT is AT method, OTA_UPDATE_METHOD_LWM2M is Lwm2m method
 * @return true succ false fail
 */
bool get_update_method(uint8 *update_method);

/**
 * Set update method
 * @param update_method OTA_UPDATE_METHOD_AT is AT method, OTA_UPDATE_METHOD_LWM2M is Lwm2m method
 * @return true succ false fail
 */
bool set_update_method(uint8 update_method);

/** @} end of group libNEUL_OTA */

#endif
