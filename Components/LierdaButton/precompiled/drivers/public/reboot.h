/******************************************************************************
 * @brief    Reboot interface.
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef REBOOT_H_
#define REBOOT_H_

#include "platform_definitions.h"
/** @defgroup NONOS_DRIVERS_REBOOT Hi21XX non-OS Reboot Driver
 * Hi21XX non-OS Reboot Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

/**
 * This is a special enum, it is split into three sections
 * Only 16 bits are used.
 * Bits 13 to 15 are flags setting which core caused the reboot
 * Bit 8 sets if the reset reason is custom or fixed
 * Bits 0 to 7 contain the reason
 *
 * If Bit 8 is set then the reasons are Unknown (0), SysReset(1), Watchdog(2) for the apps and the protocol cores
 * The security core has two extra reasons - Self (4) and AltBoot(8)
 * It should not be possible to get reset reason 0 on the Apps or protocol cores. (0xX100)
 */
typedef enum
{
    REBOOT_CAUSE_UNKNOWN                          = 0x0000, //!< Used as a default for the reboot_reset_reason variable
    //Security core reset reasons
    REBOOT_CAUSE_SECURITY_RESET_UNKNOWN           = 0x8000, //!< Should never happen - unknown reset reason
    REBOOT_CAUSE_SECURITY_SYSRESETREQ             = 0x8001, //!< Only possible if the codeloader reboot command was sent, or on a codeloader change speed error
    REBOOT_CAUSE_SECURITY_WATCHDOG                = 0x8002, //!< The securities watchdog fired
    REBOOT_CAUSE_SECURITY_SECURITY                = 0x8003, //!< Security core did a soft reset with no other reason stored, apart from HW error, No known causes
    REBOOT_CAUSE_SECURITY_ALTBOOT                 = 0x8004, //!< ROM Failure, apart from HW error, not currently possible
    REBOOT_CAUSE_SECURITY_RESET_REG_0             = 0x8005, //!< Security core did a soft reset with no other reason stored, apart from HW error, No known causes
    REBOOT_CAUSE_SECURITY_RESET_REG_3             = 0x8006, //!< Security core did a soft reset with no other reason stored, apart from HW error, No known causes
    REBOOT_CAUSE_SECURITY_STANDARD_CHIP_WATCHDOG  = 0x8007, //!< Security core could not kick the watchdog in time - If seen, check that the apps->security interrupt line is not being over used
    REBOOT_CAUSE_SECURITY_SCAN_ENTER_EXIT         = 0x8008, //!< Only possible in non-standard test modes
    REBOOT_CAUSE_SECURITY_PMU_POR                 = 0x8009, //!< Power management unit start up - BlackOut/BrownOut/PowerOn
    REBOOT_CAUSE_SECURITY_RESET_PIN               = 0x800A, //!< Reset line was toggled

    REBOOT_CAUSE_SECURITY_MONITOR_REBOOT_REQ      = 0x8100, //!< Placeholder: Start of security custom reset reasons
    REBOOT_CAUSE_SECURITY_REGIONS_UPDATED,                  //!< The Security core updated its mapped in memory regions - No known causes
    REBOOT_CAUSE_SECURITY_FOTA_UPGRADE,                     //!< REBOOT_CAUSE_SECURITY_FOTA_UPGRADE
    REBOOT_CAUSE_SECURITY_UPDATER_CHIP_WATCHDOG,            //!< Updater core hit the NMI handler and waited for the watchdog

    //Protocol core reset reasons
    REBOOT_CAUSE_PROTOCOL_GLOBAL                  = 0x4000, //!< Start of the Protocol reboot reasons
    REBOOT_CAUSE_PROTOCOL_SYSRESETREQ             = 0x4001, //!< The Protocol core reset its self with the SYSRESETREQ internal line - No known causes
    REBOOT_CAUSE_PROTOCOL_WATCHDOG                = 0x4002, //!< The Protocol cores watchdog fired
    REBOOT_CAUSE_PROTOCOL_SECURITY                = 0x4003, //!< The Security core reset the Protocol core with no additional reason given - No known causes
    REBOOT_CAUSE_PROTOCOL_RESERVED_1              = 0x4004, //!< Not Possible, left in for enum compatibility with the security core
    REBOOT_CAUSE_PROTOCOL_RESET_REG_0             = 0x4005, //!< The Security core reset the Protocol core with no additional reason given - No known causes
    REBOOT_CAUSE_PROTOCOL_RESET_REG_3             = 0x4006, //!< The Security core reset the Protocol core with no additional reason given - No known causes

    REBOOT_CAUSE_PROTOCOL_MONITOR_REBOOT_REQ      = 0x4100, //!< Placeholder: Start of protocol custom reset reasons
    REBOOT_CAUSE_PROTOCOL_RPC_TIMEOUT,                      //!< A timeout on the RPC inter-core communication layer, another core failed to respond in time
    REBOOT_CAUSE_PROTOCOL_IMSI_UPDATE,                      //!< A new IMSI was received

    //Application core reset reasons
    REBOOT_CAUSE_APPLICATION_GLOBAL               = 0x2000, //!< Start of the Application reboot reasons
    REBOOT_CAUSE_APPLICATION_SYSRESETREQ          = 0x2001, //!< The Application core reset its self with the SYSRESETREQ internal line
    REBOOT_CAUSE_APPLICATION_WATCHDOG             = 0x2002, //!< The Application cores watchdog fired
    REBOOT_CAUSE_APPLICATION_SECURITY             = 0x2003, //!< The Security core reset the Application core with no additional reason given - No known causes
    REBOOT_CAUSE_APPLICATION_RESERVED_1           = 0x2004, //!< Not Possible, left in for enum compatibility with the security core
    REBOOT_CAUSE_APPLICATION_RESET_REG_0          = 0x2005, //!< The Security core reset the Application core with no additional reason given - No known causes
    REBOOT_CAUSE_APPLICATION_RESET_REG_3          = 0x2006, //!< The Security core reset the Application core with no additional reason given - No known causes

    REBOOT_CAUSE_APPLICATION_MONITOR_REBOOT_REQ   = 0x2100, //!< Placeholder: Start of Application custom reset reasons
    REBOOT_CAUSE_APPLICATION_AT,                            //!< The AT command processor requested a reboot
    REBOOT_CAUSE_APPLICATION_RPC_TIMEOUT,                   //!< A timeout on the RPC inter-core communication layer, another core failed to respond in time
} REBOOT_CAUSE;

typedef enum
{
    REBOOT_STATUS_IPC_SEND_MESSAGE_FAIL
} REBOOT_STATUS;


//REBOOT_CAUSE_SECURITY_MONITOR_REBOOT_REQ    = 0x8000,
/**
 * Initialise the reboot subsystem
 * @return None
 */
void reboot_init(void);

/**
 * De-initialise the reboot subsystem
 * @return None
 */
void reboot_deinit(void);


/**
 * Perform a software reboot of this core only.
 * @return None
 */
void reboot_core(void);

/**
 * Perform a software reboot of the entire system.
 * @param cause The reason we are asking for a chip reset, bits 8 to 15 are ignored as this command
 *              can only set a custom reboot for this core
 * @return None
 */
void reboot_system(REBOOT_CAUSE cause);

/**
 * Gets the reason of the last reset
 * @return The reason we last reset
 */
REBOOT_CAUSE reboot_get_reset_reason(void);

/**
 * Used by the security core to find out why this core rebooted. The reasons that cause a chip wide
 * reset are ignored, as the security core will already know about them
 * @param hal_reason The hal_layer reason passed to us from that core
 * @param core
 * @return REBOOT_CAUSE_..._GLOBAL if this reset was a chip wide reset, otherwise should be sysreq or watchdog
 */
REBOOT_CAUSE reboot_convert_hal_reason(uint16 hal_reason, CORES core);

/**
 * Gets the last reason that the security core rebooted
 * @return The reason, or REBOOT_CAUSE_UNKNOWN if there is more than 1 reason
 */
REBOOT_CAUSE reboot_get_security_reboot_reason(void);

/**
 * Notify security_core to reboot application_core
 * @return None
 */
void protocol_notify_security_reboot_apps(void);

/** @} end of NONOS_DRIVERS_REBOOT */

#endif
