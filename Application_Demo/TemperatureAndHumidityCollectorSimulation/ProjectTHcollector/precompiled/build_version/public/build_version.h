/******************************************************************************
 * @brief    BOUDICA BUILD VERSION INFORMATION API
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/
#ifndef BUILD_VERSION_H_
#define BUILD_VERSION_H_

#include "neulfw.h"

/** @defgroup libNEUL_BUILDVERSION Hi21XX Build Version
 * Hi21XX Build Version
 * @ingroup HI21XX_MODULES
 * @{
 * */

/* Change the matching definition in the build system, tools/Scons/VersionInfo.py, when changing this limit */
#define FIRMWARE_VERSION_STRING_MAX_LENGTH 48

#define FIRMWARE_GIT_HASH_LENGTH 20
#define BUILD_VERSION_INFO_VERSION 2
#define BUILD_VERSION_MAGIC_NUMBER 0x0DD0FECA

/* BUILD version identifier */
typedef struct
{
    const uint32 version;                      
    const uint32 build_version_info_magic;    // 32-bits to match rom version - could be 16-bits 
    const uint16 build_version_info_version;
    const uint16 pad;
    const uint32 epoch;
    const char string[FIRMWARE_VERSION_STRING_MAX_LENGTH];
    const char hash[FIRMWARE_GIT_HASH_LENGTH];
}
build_version_info;

/* BUILD version identifier used for rom */
typedef struct
{
    const uint32 version;
    const uint32 epoch;
    const char string[];
}
build_version_info_rom;

const build_version_info * build_version_get_info(void);

/** return a pointer to version string
 * @return pointer to version string 
 */
const char *get_version_string(void);

/** return a pointer to git hash
 * @return pointer to git hash or null if not defined
 */
const char *get_git_hash(void);

/** @} end of group libNEUL_BUILDVERSION */

#endif // BUILD_VERSION_H_
