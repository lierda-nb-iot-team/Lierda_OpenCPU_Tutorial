/******************************************************************************
 * @brief    BOUDICA IPC mechanism - Definition of supported messages and payload
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef SRC_LIB_DRIVERS_IPC_SHARED_IPC_ACTIONS_H_
#define SRC_LIB_DRIVERS_IPC_SHARED_IPC_ACTIONS_H_

#define IPC_SECURITY_VERSION_CURRENT          4
#define IPC_SECURITY_VERSION_LAST_SUPPORTED   4

#include "iflash_sections.h"

/**
 * This enum describes all the supported IPC messages. Each message needs to have an associated payload type defined
 * in the ipc_payload union.
 * Note: Gaps in numbering lead to wasted memory, as also used to iterate over an array of callbacks.
 */
typedef enum
{
    IPC_ACTION_CORE_STARTED,               //!< Sent to the security core if another core has started
    IPC_ACTION_PROTOCOL_REBOOT_APPS,       //!< Protocol Send Reboot Apps To security Implement
    IPC_ACTION_UNUSED_2,                   //!< UNUSED Action

    IPC_ACTION_UNUSED_3,                   //!<
    IPC_ACTION_FLASH_OP_CNF,               //!<
    IPC_ACTION_FLASH_OP_IND,               //!<

    IPC_ACTION_SYS_REBOOT_REQ,             //!< Request a complete system reboot.

    IPC_ACTION_LOG_INFO,                   //!< Inform there are logs available.

    IPC_ACTION_RPC_COMMAND,                   //!< Used to send rpc style commands between the cores

#if defined (TEST_SUITE)
    IPC_ACTION_TS_MESSAGE_REQ,             //!< Used by the test suite to send a command.
    IPC_ACTION_TS_MESSAGE_CNF,             //!< Used by the test suite to send the response to a previous command.
#endif

    IPC_ACTION_NUM_ACTIONS,                //!< Used to size arrays.

    IPC_ACTION_FORCE_SIZE = 0x7FFF            //!< Used to force enum to 2 bytes
}
IPC_ACTION;


/*
 * Placeholder for the various IPC_ACTION_ENCRYPT messages.
 */
typedef struct
{
    uint32 sourcePtr;
    uint32 destPtr;
    uint16 length;
}
ipc_payload_memory;

#if defined (TEST_SUITE)
// Length of the string buffer used to exchange commands and responses.
#define IPC_TEST_SUITE_STRING_LENTGH    60


/**
 * Defines the information passed around by the test suite. USed to send a command (text string from the uart) and to provide
 * response strings back for our output (to the uart).
 */
typedef struct
{
    uint16  status;                                 //!< Provides information regarding the latest command. Pass, fail, etc
    uint16  length;                                 //!< Length in bytes of the msg.
    char    msg [IPC_TEST_SUITE_STRING_LENTGH];     //!< Command or response string.
}
ipc_payload_test_suite_string;
#endif

typedef enum
{
    IPC_FLASH_CLAIM_SECTION,
    IPC_FLASH_FLUSH_SECTION,
    IPC_FLASH_ERASE_SECTION,
    IPC_FLASH_RELEASE_SECTION
}
ipc_flash_command;

typedef enum {
    IPC_MEMORY_TRANSFER_COMMAND_TRANSFER_BUFFER,
    IPC_MEMORY_TRANSFER_COMMAND_ALLOCATION_REQUEST,
    IPC_MEMORY_TRANSFER_IND_DONE_WITH_BUFFER
}
IPC_MEMORY_TRANSFER_COMMAND;


/**
 * Structure to hold FLASH requests.
 */
typedef struct
{
    // Always used.
    ipc_flash_command       command;            //!< The command sent to the flash.

    FLASH_SECTION_TYPE      type;               //!< Type of section to act on.
    uint8                   id;                 //!< ID of section to act on.

    // Usage depends on 'command'.
    uint32                  length;             //!< Length of the section. Used with IPC_FLASH_CLAIM_SECTION.
    uint32                  address;            //!< Address of buffer in local RAM. Used with IPC_FLASH_CLAIM_SECTION.
}
ipc_payload_flash_req;

/**
 * Structure to hold FLASH response.
 */
typedef struct
{
    ipc_flash_command       command;            //!< The command sent to the flash.

    FLASH_SECTION_TYPE      type;               //!< Type of section to act on.
    uint8                   id;                 //!< ID of section to act on.
}
ipc_payload_flash_cnf, ipc_payload_flash_ind;

/**
 * Structure to hold the ipc_reboot cause
 */
typedef struct
{
    uint32 reboot_cause;
} ipc_payload_core_started;

/**
 * Reasonable payload size for an RPC message.
 * All fixed sized messages should fit within this size.
 * Large variable sized messages will be fragmented but this tries to provide a reasonable trade-off.
 */
#define IPC_RPC_PAYLOAD_SIZE 64

/**
 * Defines a suitable RPC payload buffer, to help prevent excessive IPC message fragmentation
 */
typedef struct
{
    uint8 data[ IPC_RPC_PAYLOAD_SIZE ];
}
ipc_payload_rpc;

/**
 * A struct to hold why one core has asked the security core to reboot
 */
typedef struct
{
    uint16 requested_reboot_reason;
} ipc_payload_request_reboot;

/**
 * This union defines the IPC message payload, i.e. encapsulates the actual data transported by the IPC message.
 */
typedef union
{
    ipc_payload_memory              memory;         //!< Used to share memory between cores.

    // 'Remote' flash accesses.
    ipc_payload_flash_req           flash_req;      //!< Used to specify which flash operation to perform.
    ipc_payload_flash_cnf           flash_cnf;      //!< Used to pass a response to a previous request.
    ipc_payload_flash_ind           flash_ind;      //!< Used to pass 'asynchronous' data to a 'remote' client.

    ipc_payload_core_started        core_started;   //!< Used to signal to the security core that a core has rebooted

    ipc_payload_rpc                 rpc_payload;    //!< Not actually used.  Just to ensure ipc_payload union is a reasonable size.

    ipc_payload_request_reboot      request_reboot; //!< Used to request a reboot from the security core, the reason is then passed to the cores on startup

#if defined (TEST_SUITE)
    ipc_payload_test_suite_string   testsuite;      //!< Used by the test-suite to send/receive command/response strings.
#endif
}
ipc_payload;

#endif
