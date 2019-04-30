/******************************************************************************
 * @brief    Header file for NON VOLATILE flash layout
 * Copyright (c) 2015 NEUL LIMITED
 ******************************************************************************/

#ifndef SRC_DRIVERS_BOUDICA_NON_OS_IFLASH_SHARED_IFLASH_SECTIONS_H_
#define SRC_DRIVERS_BOUDICA_NON_OS_IFLASH_SHARED_IFLASH_SECTIONS_H_

/** @defgroup NONOS_DRIVERS_IFLASH Hi21XX non-OS iFlash Driver
 * Hi21XX non-OS iFlash Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

/**
 * Holds the definition of the various sections within the flash.
 * 'Data' sections are effectively non-volatile byte arrays, that need to be managed by the 'user'.
 */
typedef enum
{
    // Executable code sections.
    FLASH_SECTION_SECURITY_CODE = 0,            //!< SECURITY core code. Used during development only, as security code will be in ROM.
    FLASH_SECTION_PROTOCOL_CODE = 1,            //!< PROTOCOL core code.
    FLASH_SECTION_APPS_CODE     = 2,            //!< APPS core code.

    // Non volatile 'data' sections.
    FLASH_SECTION_UNUSED,                       //!< Currently UNUSED

    FLASH_SECTION_SECURITY_DATA,                //!< Non volatile storage for use by the security core.
    FLASH_SECTION_PROTOCOL_DATA,                //!< Non volatile storage for use by the PROTOCOL core.
    FLASH_SECTION_APPS_DATA,                     //!< Non volatile storage for use by the APPS core.

    FLASH_SECTION_PROTOCOL_CONST_DATA_1,         //!< Non volatile storage for use by the calibration mechanism. Expected to be read-only
    FLASH_SECTION_PROTOCOL_CONST_DATA_2          //!< Since the calibration is larger than 4KB it gets 2 configs, these need to be kept next to each other
}
FLASH_SECTION_TYPE;

/**
 * Data structure used to hold information about a NV storage page in flash
 */
typedef struct
{
    FLASH_SECTION_TYPE  type;     //!< 'Type' of the non-volatile section.
    uint8               id;       //!< Unique identifier allocated by 'owner' of the page.
    uint32              offset;   //!< Offset in bytes from start of flash. Must be page (4K) aligned!
    uint32              length;   //!< Size in bytes of allocated page. No more than 1 page (4K) -- currently unused.
}
nv_section;

/** @} end of NONOS_DRIVERS_IFLASH */

#endif /* SRC_DRIVERS_BOUDICA_NON_OS_IFLASH_SHARED_IFLASH_SECTIONS_H_ */
