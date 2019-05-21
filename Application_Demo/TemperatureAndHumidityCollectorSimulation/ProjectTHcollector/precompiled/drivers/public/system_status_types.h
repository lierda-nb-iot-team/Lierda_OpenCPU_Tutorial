/******************************************************************************
 * @brief    SYSTEM STATUS TYPES
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_DRIVERS_NON_OS_SYSTEM_STATUS_SHARED_SYSTEM_STATUS_TYPES_H_
#define SRC_DRIVERS_NON_OS_SYSTEM_STATUS_SHARED_SYSTEM_STATUS_TYPES_H_

#include "neulfw.h"

/** @addtogroup NONOS_DRIVERS_SYSTEM_STATUS
 * @{
 * */

/**
 * System status information from the slave core to the security core
 */
typedef struct
{
    volatile uint32   lock_flag;
    volatile uint32   status_flags;
    volatile uint64   expected_wake_time;
} system_status_core;


/**
 * System status information from the security core to the slave core
 */
typedef struct
{
    volatile uint32   lock_flag;
    volatile uint32   status_flags;
    volatile uint32   reserved_1;
} system_status_security;

#define SYSTEM_STATUS_FLAG_VETO_FLASH_WRITES     (0x01ul)   //Flash writes are not allowed
#define SYSTEM_STATUS_FLAG_JLINK_CONNECTED       (0x02ul)   //Jlink is connected, so certain reboots should be ignored (not trigger a system reset)
#define SYSTEM_STATUS_FLAG_NEED_FLASH_ACCESS     (0x04ul)   //Request access to the flash, gets the security core to unlock flash asap
#define SYSTEM_STATUS_FLAG_REBOOT_MASK           (0x80000000ul)


//lint -esym(755, SECURITY_FLAG_WRITING_TO_FLASH)
#define SECURITY_FLAG_WRITING_TO_FLASH          (0x01ul)
#define SECURITY_FLAG_FLASH_LOCKED              (0x02ul)

/** @} end of NONOS_DRIVERS_SYSTEM_STATUS */

#endif /* SRC_DRIVERS_NON_OS_SYSTEM_STATUS_SHARED_SYSTEM_STATUS_TYPES_H_ */
