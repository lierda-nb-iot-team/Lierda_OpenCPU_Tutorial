/******************************************************************************
 * @brief    RPC Interface Header
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_LIB_RPC_INTERFACE_PUBLIC_RPC_INTERFACE_H
#define SRC_LIB_RPC_INTERFACE_PUBLIC_RPC_INTERFACE_H

#include "platform_definitions.h"    //CORES
#include "core.h"

/**
 * There are some limits to use rpc, or would dead loop.
 * In security core, can't trigger another rpc to another core while security core process the incoming commands.
 * In security core, while it wait for the rpc response, rpc_interface_poll need called to process incoming commands.
 * In protocol core, can't trigger another rpc to application core while protocol core process the incoming commands.
 */
 
typedef enum
{
    RPC_INTERFACE_RETURNS_SUCCESS,
    RPC_INTERFACE_RETURNS_BUFFER_FULL,
    RPC_INTERFACE_RETURNS_INCORRECT_HANDLER,
    RPC_INTERFACE_RETURNS_BAD_PARAMS,
    RPC_INTERFACE_RETURNS_IPC_FAILED,
    RPC_INTERFACE_RETURNS_IPC_INVALID_STATE,
    RPC_INTERFACE_RETURNS_INCOMPLETE_TRANSFER,
    RPC_INTERFACE_RETURNS_AWAITING_RESPONSE,
}RPC_INTERFACE_RETURNS;

typedef void (*rpc_auto_generated_release_func)(void * free_addr);

/**
 * Function pointer to a function that will block until a mailbox gets some data
 */
typedef void (*rpc_mailbox_incoming_function)(void);

/**
 * Function pointer to a function that will send data to a mailbox
 */
typedef void (*rpc_mailbox_outgoing_function)(CORES core);

/**
 * Function pointer to a function that yield task
 */
typedef void (*rpc_task_yield_function)(void);

/**
 * Function pointer to a function that will provide semaphore functionality
 */
typedef bool (*rpc_mailbox_semaphore)(CORES core);

/**
 * Function pointer to a function that will provide semaphore functionality
 */
typedef bool (*rpc_sent_data_semaphore)(void);

typedef struct
{
    rpc_mailbox_incoming_function incoming_command_recieve;
    rpc_mailbox_incoming_function incoming_command_send_from_isr;

    rpc_mailbox_outgoing_function outgoing_command_recieve;
    rpc_mailbox_outgoing_function outgoing_command_send_from_isr;

    rpc_mailbox_semaphore rpc_mailbox_semaphore_take;
    rpc_mailbox_semaphore rpc_mailbox_semaphore_give;

    rpc_sent_data_semaphore rpc_sent_semaphore_take;
    rpc_sent_data_semaphore rpc_sent_semaphore_give;

    rpc_task_yield_function rpc_task_yield;
} rpc_interface_mailboxes;

/**
 * The version we are currently running, this should be updated whenever a new command is added
 */
#define LOCAL_RPC_VERSION     (0x01)

/**
 * The version that we support from the other cores - if we have added a new command that we can call
 * on another call then out local_rpc_version would increase, but as long as we have not changed any
 * of the commands that another core calls on us then there is no need to increase this number
 */
#define SUPPORTED_RPC_VERSION (0x01)

/**
 * Polls the rpc to see if a new command/response has come in
 */
void rpc_interface_poll(void);

/**
 * Used for freeRTOS, at the moment it just puts a thread into a
 * rpc_interface_poll loop with a mailbox
 * @param unused Not used
 */
void rpc_thread_main(void);

/**
 * Inits the rpc interface
 * @param mailboxes if the mailboxes are not being used then this pointer should be null
 */
void rpc_interface_init( const rpc_interface_mailboxes *mailboxes );

/**
 * Deinits the rpc interface
 */
void rpc_interface_deinit( void );

/**
 * Gets the maximum amount of data that can be sent over the RPC.
 */
uint16 rpc_interface_get_max_message_size( void );

/**
 * Gets the maximum amount of data that can be returned over the RPC.
 */
uint16 rpc_interface_get_max_response_size( void );

/**
 * Allow external checking of buffer size
 * @param size of message to pass over RPC
 */
bool rpc_message_size_check(uint16 len);

#endif
