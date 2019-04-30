/*
 * lierdaUART.h
 *
 *  Created on: 2018楠烇拷9閺堬拷24閺冿拷
 *      Author: lindi
 */

#ifndef SRC_LIB_LIERDAUART_PUBLIC_LIERDAUART_H_
#define SRC_LIB_LIERDAUART_PUBLIC_LIERDAUART_H_

#include "hal_uart_definitions.h"
#include "neulfw.h"
#include "hal_lpuart.h"
#include "lp_uart.h"
#include "neul_utils.h"
#include "app_at_main.h"
#include "uart.h"

#ifndef bool
typedef int bool;
#endif

typedef void (*lierda_uart_received_data_notify)(void);

typedef struct
{
	uint32 			baudrate;
	UART_DATA_BITS 	data_bits;
	UART_STOP_BITS  stopbits;
	UART_PARITY  	parity;
	PIN				tx_pin;
	PIN				rx_pin;

}UART_HandleTypeDef;

UART_HandleTypeDef lierdaUARTHandle;


extern void lierdaUARTInit(UART_HandleTypeDef *huart);
extern uint16 lierdaUARTReceive(UART_HandleTypeDef *huart,uint8 *UserDataPtr, uint16 *UserDataLen, uint32 WaitTimeOut);
extern void lierda_uart_main_normal_uart_callback(void * buffer, uint16 length, UART_RELEASE_FUNCTION release_func);
extern void lierdaUARTSend(UART_HandleTypeDef *huart,const uint8 *buffer, uint32 length);

/******************************************************************************
 * @鍑芥暟鍚�:lierdaUARTClose锛岀敤浜庡叧闂覆鍙�
 * @鍙傛暟:None
 * @杩斿洖鍊�:None
 * @閲嶈淇敼璁板綍:190108锛孌ef鍒涘缓鍑芥暟
******************************************************************************/
void lierdaUARTClose(void);


#endif /* SRC_LIB_LIERDAUART_PUBLIC_LIERDAUART_H_ */
