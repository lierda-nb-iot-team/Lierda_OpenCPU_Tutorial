/******************************************************************************
 * @brief    Application Core Initialize Interface Header for Reference
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef APP_OS_INIT_H
#define APP_OS_INIT_H

#include "app_at.h"

typedef struct Uart_Recv1
{
	uint8 received_start;
	uint8 received_finish;
	uint8 received_timeOut;
	uint16 received_dataLen;
	uint8 received_Buff[AT_MAX_MTU_SIZE];
}Uart_Recv;

extern Uart_Recv UserUart;


void fota_send_to_incoming_queue(void);
void app_send_to_incoming_queue_from_isr(void);

/** Main initialisation function for the apps os. Creates the appropriate queues and threads.
 *@param    None
 *@return   None.
 */
void app_os_init( void * unused1, unsigned int unused2 );

#endif
