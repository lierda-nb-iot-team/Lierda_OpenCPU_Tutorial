/******************************************************************************
 * @brief    ID and identifier Functions for Hi21XX
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LIB_NEUL_IDENTITY_H_
#define LIB_NEUL_IDENTITY_H_

#include "neulfw.h"
#include "neul_error_types.h"
#include "platform_definitions.h"
#include "neul_kv_storage.h"
#include "neul_identity_etypes.h"

/** @defgroup libNEUL_IDENTITY Hi21XX libNEUL Identity
 * Hi21XX libNeul Identity API
 * @ingroup LIBNEUL
 * @{
 * */

typedef enum {
    ID_TYPE_SERIALNUMBER = 0,
    ID_TYPE_IMEI,
    ID_TYPE_SVN,
    ID_TYPE_MANMODEL,
    ID_TYPE_MANREV
} ID_TYPE;

typedef enum {
    ID_CONFIG_FLASH = 1,
    ID_CONFIG_OTP
} NTPERMID_TYPE;

#define MAX_IMSI_LEN                        16
#define IMEI_LEN                            15
#define IMEISV_LEN                          16
#define SVN_LEN                              2
#define SVN_PACKED_LENGTH                    1
#define CCID_PACKED_LENGTH                  20
#define MAX_VERSION_STRING                  48
#define MAX_MANUFACTURER_IDENTIFIER_LENGTH  64

/**
 * Save the IMEI in BCD format in the location pointed by imei.
 * IMEI is IMEI_PACKED_LENGTH bytes long.
 * @param imei pointer to the location where IMEI value will be copied
 * @return NEUL_RET_OK or error code
 */
NEUL_RET get_imei (uint8 *imei);

/**
 * Set the IMEI in BCD format.
 * @param imei pointer where the IMEI to set is stored. IMEI must be IMEI_PACKED_LENGTH bytes long.
 * @return NEUL_RET_OK or error value
 */
NEUL_RET set_imei (uint8 *imei);

/**
 * Returns the value of the SVN.
 * @param svn pointer to the location where the SVN will be stored.
 * @return NEUL_RET_OK or error value
 * @note svn is returned in BCD format.
 */
NEUL_RET get_svn (uint8 *svn);

/**
 * Sets the value of the SVN.
 * @param svn pointer to the location where the SVN to set is stored.
 * @return NEUL_RET_OK or error value
 * @note svn must be given BCD format.
 */
NEUL_RET set_svn (const uint8 *svn);

/**
 * Save the serial number in the location pointed by serial number.
 * @param serialnumber pointer to the location where the serial number value will be copied. It must be SERIALNUMBER_LENGTH bytes long.
 * @return NEUL_RET_OK or error code
 */
NEUL_RET get_serial_number (uint8 *serialnumber);

/**
 * Sets the value of the serial number.
 * @param serialnumber pointer where the serial number to set is stored. serialnumber must be SERIALNUMBER_LENGTH bytes long.
 * @return NEUL_RET_OK or error value
 */
NEUL_RET set_serial_number (uint8 *serialnumber);

/**
 * Get the manufacturer identifier
 * @param mident buffer where the manufacturer identifier will be stored as a string.
 * @param mident_max_len buffer length.
 * @param mident_len length of the manufacturer string copied.
 * @return NEUL_RET_OK or error value
 */
NEUL_RET get_man_identifier (char *mident, uint16 mident_max_len, uint16 *mident_len);

/**
 * Get the manufacturer model
 * @param mmodel buffer where the manufacturer model will be stored as a string.
 * @param mmodel_max_len buffer maximum length.
 * @param mmodel_len length of the manufacturer string copied.
 * @return NEUL_RET_OK or error value
 */
NEUL_RET get_man_model (char *mmodel, uint16 mmodel_max_len, uint16 *mmodel_len);

/* @brief get the ssb version.
 * @param version_string_length the length of the version_string (maximum size will be 48 bytes)
 * @param version_string 48-byte buffer to hold ssb version information
 * @param buff_length the length of version_string buff(minimum 48 bytes).
 * @return NEUL_RET_OK or error value.
 */
NEUL_RET get_ssb_version(uint16 *version_string_length, char *version_string, uint16 buff_length);

/**
 * @brief Get the firmware version.
 * @param cimage core image to get version string of.
 * @param version_string_length the length of the version_string (maximum size will be 48 bytes)
 * @param version_string SW version information(minimum size of 48 bytes).
 * @param buff_length the length of version_string buff(minimum 48 bytes).
 * @return NEUL_RET_OK or error value.
 */
NEUL_RET get_firmware_version(CORE_IMAGES cimage, uint16 *version_string_length, char *version_string, uint16 buff_length);

/**
 * @brief Get the firmware version.
 * @param version_string SW version information(must be 48 bytes).
 * @return NEUL_RET_OK or error value.
 */
NEUL_RET get_rfconfig_version(char *version_string);

/**
 * Sets the value of the IMEISV.
 * @param imeisv pointer to the location where the IMEISV will be copied.
 * @return NEUL_RET_OK or error value
 * @note imeisv is given BCD format.
 */
NEUL_RET get_imeisv (uint8 *imeisv);

/** Return the IMSI number of the installed SIM
 * @param imsi data buffer to use. Must be of lenght 16 or larger (max imsi length is 15 characters +  null)
 * @param imsi_len length of imsi returned.
 * @return NEUL_RET_OK or NEUL_RET_ERROR
 */
NEUL_RET get_imsi(char *imsi, uint16 *imsi_len);

/**
 * Migrate the imei to permanent flash or OTP from flash.
 * @param dest destination where imei set.
 * @return NEUL_RET_OK or error value
 */
NEUL_RET set_imei_permanence(NTPERMID_TYPE dest);

/**
 * Migrate the serial number to permanent flash or OTP from flash.
 * @param dest destination where serial number set.
 * @return NEUL_RET_OK or error value
 */
NEUL_RET set_serialnumber_permanence(NTPERMID_TYPE dest);

/**
 * @brief Return card identification of the installed SIM (+NCCID?/+NCCID)
 * @param iccid card identification to get, iccid len is CCID_PACKED_LENGTH
 * @param iccid_len iccid len
 */
NEUL_RET get_iccid( char *iccid , uint16 *iccid_len);

/**
 * @brief Get dieid
 * @param dieid_length length of dieid data items returned
 * @param dieid a pointer to the pointer of a buffer of dieid
 * @return error or success
 */
NEUL_RET get_dieid(uint16 *dieid_length, uint8 **dieid);

/**
 * @brief Free dieid buffer
 * @param dieid the pointer to a buffer of dieid
 * @return null
 */
void free_dieid(uint8 *dieid);
/** @} end of group libNEUL_IDENTITY */

#endif /* LIB_NEUL_IDENTITY_H_ */
