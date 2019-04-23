/******************************************************************************
 * @brief    Neul RPC CMSIS header
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/

#ifndef NEUL_CMSIS_RPC_H_
#define NEUL_CMSIS_RPC_H_

/**
 * Creates the mailboxes needed for the RPC when used with RTOS
 */
void rpc_interface_create_queue(void);

/**
 * Set Mailboxes up before any tasks are started.
 * This allows the tasks to be started in any order rather than blocking
 * waiting for RPC thread to start, which can't as a higher priority
 * taks is left waiting.
 *
 * @param Void
 */
void rpc_init (void);

/**
 * Entry point for the CMSIS thread for the RPC
 * @param unused Unused
 */
void rpc_main( void *unused );

#endif
