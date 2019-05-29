/******************************************************************************
 * @brief    Default memory configurations
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/
#ifndef MEMORY_CONFIG_H_
#define MEMORY_CONFIG_H_

/* Each core sees RAM starting at the same relative location */
#define HI21XX_PRIVATE_RAM_ORIGIN (0x01000000)

/* 64K for APPS core. */
#define AC_RAM_ORIGIN HI21XX_PRIVATE_RAM_ORIGIN
#define AC_RAM_LENGTH 0x10000

/*------------------------------------------------------------------------------------------------------------------------*/
#define FLASH_PAGE_SIZE 8192

/* Application Area Flash Defines */
/* Maximum Application Area allocatable FLASH space pages below minimum NV region*/
#define APPS_AREA_MAX_FLASH_PAGES (44)
/* Maximum Application Area allocatable FLASH space in bytes */
#define APPS_AREA_FLASH_LENGTH    (APPS_AREA_MAX_FLASH_PAGES * FLASH_PAGE_SIZE)

/* Apps core - can be reduced to give more space to KV, system etc */
#define APPS_A_FLASH_REGION_LENGTH     APPS_AREA_FLASH_LENGTH

#define MESSAGE_QUEUE_RESERVE_LENGTH (256)

#define AC_VECTORS_ORIGIN 0
#define VECTORS_LENGTH 192
#define VERSION_LENGTH  84

#define AC_VERSION_ORIGIN  ( AC_VECTORS_ORIGIN + VECTORS_LENGTH )
#define AC_PROGRAM_ORIGIN ( ( AC_VERSION_ORIGIN )      + ( VERSION_LENGTH ) )
#define AC_PROGRAM_MAX_LENGTH ( ( APPS_A_FLASH_REGION_LENGTH ) - ( VECTORS_LENGTH + VERSION_LENGTH) )

#define AC_IPC_MAILBOX_ORIGIN   (AC_RAM_ORIGIN + AC_RAM_LENGTH - MESSAGE_QUEUE_RESERVE_LENGTH)

/* Make the last alias region the logging one*/
#define LOG_REGION_MEMORY_START        0x03000000
#define LOG_REGION_MEMORY_LENGTH       0x04000
#define PROTOCOL_CORE_LOGGING_LENGTH   0x2800

/*
 * ******************* PERIPHERAL MANAGER *******************
 * The Peripheral Manager is a section of memory mapped registers that are addressable by all cores.
 * It provides means to claim and configure the various peripherals provided.
 * There are 40 PIOs provided by the Hi2115.  Each PIO can be mapped to a different function.
 * The register maps for each PIO are ordered consecutively in the address space, with each PIO allocated 16 32-bit words
 */
#define PM_BASE    (0x40001000)    // Base address of Peripheral Manager
#define PM_LENGTH  (40 * 64)       // 40 PIOs each with a 64 byte register map

/* Reserved for System Status. */

#define SYSTEM_STATUS_AREA_LENGTH (32)

#define AC_SYSTEM_STATUS_ORIGIN   (AC_RAM_ORIGIN + AC_RAM_LENGTH - MESSAGE_QUEUE_RESERVE_LENGTH - SYSTEM_STATUS_AREA_LENGTH)
#define AC_SYSTEM_STATUS_LENGTH   (SYSTEM_STATUS_AREA_LENGTH)

/* Used to load functions in RAM or not for ROM builds */
#define MEMORY_CONFIGURATION_FUNCTION_LOADABLE_IN_RAM  __attribute__((section(".ramtext"), long_call)) __attribute__((noinline))

#endif /* MEMORY_CONFIG_H_ */
