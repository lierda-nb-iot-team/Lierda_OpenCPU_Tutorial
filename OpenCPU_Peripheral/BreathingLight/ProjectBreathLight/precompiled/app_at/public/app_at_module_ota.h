/******************************************************************************
 * @brief OTA module AT handling and interface
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/
#ifndef    _APP_AT_MODULE_OTA_H_
#define    _APP_AT_MODULE_OTA_H_

/** @addtogroup libNEUL_APP_AT_INT
 * @{
 * */

typedef enum
{
    AT_OTA_CMD_ERASE               = 0x00, //!< erase flash for package
    AT_OTA_CMD_DOWNLOAD            = 0x01, //!< download package
    AT_OTA_CMD_VALIDITY_CHECK      = 0x02, //!< package validity check
    AT_OTA_CMD_GET_PACKAGE_NAME    = 0x03, //!< get package name
    AT_OTA_CMD_GET_PACKAGE_VERSION = 0x04, //!< get package version
    AT_OTA_CMD_UPGRADE             = 0x05, //!< start upgrade
    AT_OTA_CMD_MAX_NUM             = 0x06  //!< cmd max number
}AT_OTA_CMD;

/**
 * exec command
 *@param  buff   data buffer
 *@param  len    data length
 *@return AT_RET
 */
AT_RET at_ota_exec_cmd(AT_OTA_CMD cmd);

/**
 * download package
 *@param  sn     sequence number
 *@param  buff   data buffer
 *@param  length data length
 *@return AT_RET
 */
AT_RET at_ota_download_package(uint16 sn, uint16 length, const uint8* data, const uint8* crc);

/** @} end of group libNEUL_APP_AT_INT */

#endif
