/******************************************************************************
 * @brief    IPC Common interface.
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef SRC_LIB_DRIVERS_IPC_SHARED_IPC_H_
#define SRC_LIB_DRIVERS_IPC_SHARED_IPC_H_

#include "neulfw.h"
#include "platform_definitions.h"


// Include the various IPC message types (IPC_ACTIONS) and associated payload types (ipc_payload).
// Placed in a dedicated file to keep 'user' types separate from 'infrastructure' ones.
#include "ipc_actions.h"


/**
 * Enum to specify indexes into array of mailboxes. Each core has one INBOX and one OUTBOX.
 */
typedef enum
{
    IPC_OUTBOX = 0,                 //!< Index of OUTBOX within array of mailboxes.
    IPC_INBOX,                      //!< Index of INBOX within array of mailboxes.
    IPC_NUM_MAILBOX                 //!< Number of entries per core.
}
IPC_MAILBOX_INDEX;


/**
 * Enum specifying the relative priority of the IPC message, with 0 indicating the highest priority.
 * Using the incrementing values allows for easy loops
 *      for (IPC_PRIORITY p = IPC_PRIORITY_HIGHEST; p <= IPC_PRIORITY_LOWEST; p++)
 */
typedef enum
{
    IPC_PRIORITY_HIGHEST = 0,       //!< Highest priority (lowest numeric value).
    IPC_PRIORITY_LOWEST,            //!< Lowest priority (highest numeric value).
    IPC_PRIORITY_MAX_NUM            //!< Used to size arrays.
}
IPC_PRIORITY;


/**
 * Enum holding the various status codes that an IPC message can pass through during delivery. Note that this is different
 * to IPC_STATUS enum which documents the IPC mechanism error codes.
 */
typedef enum
{
    IPC_ACTION_STATUS_CLEAR = 0,    //!< Message available for use in the message pool.
    IPC_ACTION_STATUS_PROCESS,      //!< Message is 'en-route' and awaiting further processing.
    IPC_ACTION_STATUS_DONE          //!< Message has been processed and is awaiting a return to the message pool.
}
IPC_ACTION_STATUS;


/**
 * Enum holding the status codes returned by the IPC mechanism. Note that this is different to the IPC_ACTION_STATUS enum which
 * documents the IPC message status.
 */
typedef enum
{
    IPC_STATUS_OK,                  //!< Everything went OK. Default return code.

    IPC_STATUS_INVALID_ACTION,      //!< The requested operation referred to an unknown / invalid IPC_ACTION type.
    IPC_STATUS_INVALID_HANDLER,     //!< The requested operation failed due to an error with the provided callback.
    IPC_STATUS_INVALID_CORE,        //!< The requested core doesn't exist.
    IPC_STATUS_INVALID_PRIORITY,    //!< The requested priority doesn't exist.

    IPC_STATUS_ALREADY_REGISTERED,  //!< The requested operation failed as already have callback registered.
    IPC_STATUS_MAILBOX_BUSY         //!< Can't send a message as the oubox is in use.
}
IPC_STATUS;


/**
 * This structure defines the complete IPC message, and is the basic element passed around within the internal IPC mechanism.
 * Do NOT change the size of this structure, as all cores MUST use the same definition for the IPC mechanism to work!
 */
typedef struct
{
    uint32              id;             //!< Incrementing message id. Numbering is unique to sending core only.
    IPC_PRIORITY        priority;       //!< Priority to use when processing the message internally.

    CORES               src;            //!< Sending core.
    CORES               dst;            //!< Destination core.

    // User fields.
    IPC_ACTION          action;         //!< Type of IPC message being sent. Used to route message on the destination.
    ipc_payload         payload;        //!< Union of user data types. The action field determines which union member to use.

    bool                request_ack;    //!< Request that a delivery confirmation be sent to the sender. UNUSED!
    uint8               chksum;         //!< Simple integrity checksum. UNUSED!

    IPC_ACTION_STATUS   status;         //!< Internal 'state' of the message as it is processed. Must be the last element written to!
}
ipc_mailbox_entry;


/**
 * Typedef to hold the mailboxes. One inbox and one outbox per core.
 */
typedef ipc_mailbox_entry ipc_mailbox_array [IPC_NUM_MAILBOX];


/**
 * IPC ACTION Callback. Called whenever the registered IPC_ACTION message is received.
 * @param message The IPC_ACTION of the received message.
 * @param payload_p Data payload of the received mssage. Note that this is the uinion, not the individual memeber.
 * @param src Sending core.
 * @param id Internal message id. Can be used to detect duplicate delivery and for debug.
 * @return True if the incoming mailslot shluld be released or false if the message was not (fully) processed and should be redelivered.
 */
typedef bool (*ipc_action_handler)(IPC_ACTION message, const volatile ipc_payload * payload_p, CORES src, uint32 id);



/**
 * Initialise the IPC mechanism. Simply initialise internal data structures, remove registered callbacks and enable appropriate interrupts.
 * @return Nothing.
 */
void ipc_init (void);


/**
 * De-Initialise the IPC mechanism. Simply disable appropriate interrupts and reset internal timers.
 * @return Nothing.
 */
void ipc_deinit (void);


/**
 * Register a specific callback to handle a specific IPC_ACTION. The action must not already have a handler registered.
 * The callback should copy the payload data passed to it as the IPC system will mark the mailslot as 'free' if the callback
 * returns true. Should the message not be fully processed, the callback should return false, which will cause the entire
 * message to be redelivered a short time later.
 * @param action The IPC_ACTION to register the callback for.
 * @param handler The callback function to install as callback handler.
 * @return See definition of IPC_STATUS for details on returned error codes and their meaning.
 */
IPC_STATUS ipc_register_handler (IPC_ACTION action, ipc_action_handler handler);


/**
 * De-Register a specific callback for a specific IPC_ACTION.
 * @param action The IPC_ACTION to de-register the callback for.
 * @return See definition of IPC_STATUS for details on returned error codes and their meaning.
 */
IPC_STATUS ipc_unregister_handler (IPC_ACTION action);


/**
 * Send an IPC message containing the provided action and payload to the specified core. If the message can't be sent immediately
 * the call fails and IPC_STATUS_MAILBOX_BUSY is returned, it is up to the caller to retry. Expected usage is that the caller will
 * yield/busy-wait if the needed mailslot is not available.
 * Note that IPC messages between the APPS and PROTOCOL cores are sent via the security core, which also handles the priorities.
 * @param dst Destination core for the message.
 * @param action Type of message being sent.
 * @param payload_p Pointer to the payload to be sent to the remote core. Can be NULL if no payload is needed.
 * @param priority Priority with which the message should be sent (higher priority messages may overtake lower priority ones en-route).
 * @param request_ack Request that the IPC mechanism confirm delivery to the remote core.
 * @return See definition of IPC_STATUS for details on returned error codes and their meaning.
 */
IPC_STATUS ipc_send_message (CORES dst, IPC_ACTION action, const ipc_payload * payload_p, IPC_PRIORITY priority, bool request_ack);


/**
 * Callback from HAL low level IRQ handler to indirect the HW specific functionality which is core specific. This ends up calling
 * the registered callback, if any,  in an interrupt context.
 * @return None
 */
void ipc_receive_message (void);

/*
 * Check the core's outbox is clear up or not.
 */
bool ipc_check_outbox_free(void);


// During debug - enable message tracing from interrupt context!
//#define IPC_DEBUG
//#define IPC_DEBUG_INTERRUPTS

#ifdef TEST_SUITE
void ipc_inspect_mailboxes (void);
#endif

#endif
