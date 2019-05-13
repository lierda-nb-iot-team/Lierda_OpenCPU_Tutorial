/******************************************************************************
 * @brief    NEUL UPDATE ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef ETYPES_SHARED_AS_CORE_NEUL_UPDATE_ETYPES_H_
#define ETYPES_SHARED_AS_CORE_NEUL_UPDATE_ETYPES_H_

#include "neulfw.h"


typedef enum ETYPES_ENUM_HOLDER_TYPE(U8)
{
    INSTALL_TYPE_UNKNOWN,
    INSTALL_TYPE_NOT_SET,
    INSTALL_TYPE_NEED_SHA256,
    INSTALL_TYPE_NEED_SIGNATURE
}INSTALL_TYPE;


typedef enum ETYPES_ENUM_HOLDER_TYPE(U8)
{
    NEUL_UPDATE_STAGE_UPGRADE_INIT  = 0,
    NEUL_UPDATE_STAGE_UPGRADE_SUCC  = 1,
    NEUL_UPDATE_STAGE_VALIDATE_FAIL = 5,
    NEUL_UPDATE_STAGE_UPGRADE_FAIL  = 8,
    NEUL_UPDATE_STAGE_MAX
} NEUL_UPDATE_STAGE;

/*
* update status of UE
*/
typedef enum ETYPES_ENUM_HOLDER_TYPE(U8)
{
    NEUL_UPDATE_OTA_PACKAGE_OK,                         //!< Package is good and can be applied.
    NEUL_UPDATE_OTA_PACKAGE_CORRUPT,                    //!< Failure to decode the package.
    NEUL_UPDATE_OTA_PACKAGE_NOT_PROCESSED,              //!< Package has not been decoded yet.
    NEUL_UPDATE_OTA_PACKAGE_VALIDATION_FAILURE,         //!< Signatures validation failure.
    NEUL_UPDATE_OTA_PACKAGE_UNSUPPORTED_OPTIONS,        //!< Unsupported option detected, in package format.
    NEUL_UPDATE_OTA_PACKAGE_VERSION_MISMATCHED,         //!< Old version in package mismatched.
    NEUL_UPDATE_OTA_PACKAGE_ELEMENT_TOO_LONG,           //!< Some element in package too long.
    NEUL_UPDATE_OTA_PACKAGE_REGION_LOST,                //!< Allocated update package region in flash has been lost.
    NEUL_UPDATE_OTA_PACKAGE_SIGNATURE_OR_HASH_LACKED,   //!< Package lacks the necessary signature/hash..
    NEUL_UPDATE_OTA_PACKAGE_NOT_DOWNLOADED,             //!< Package had NOT been downloaded.
} NEUL_UPDATE_OTA_PACKAGE_STATUS;

#endif /* ETYPES_SHARED_AS_CORE_NEUL_UPDATE_ETYPES_H_ */
