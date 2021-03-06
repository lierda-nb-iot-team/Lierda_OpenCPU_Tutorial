/******************************************************************************
 * @brief    UART Module PANIC Causes
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef UART_PANIC_H_
#define UART_PANIC_H_

/** @addtogroup DRIVER_CMSIS_UART
 * @{
 * */

typedef enum PANIC_ID_UART
{
    PANIC_UART_ERROR_IN_THE_PARAMETERS_SENT_TO_OPEN_UART,
    PANIC_UART_UNABLE_TO_ALLOCATE_MEMORY_FOR_UART,
    PANIC_UART_UNABLE_TO_CREATE_MUTEX,
    PANIC_UART_INVALID_TRANSMISSION_PIN,
    PANIC_UART_INVALID_RECEPTION_PIN,
    PANIC_UART_INVALID_READY_TO_SEND_PIN,
    PANIC_UART_INVALID_CLEAR_TO_SEND_PIN,
    PANIC_UART_COULD_NOT_SET_TX_PIN,
    PANIC_UART_COULD_NOT_SET_RX_PIN,
    PANIC_UART_COULD_NOT_SET_RTS_PIN,
    PANIC_UART_COULD_NOT_SET_CTS_PIN,
    PANIC_UART_ILLEGAL_ATTEMPT_TO_OPEN_AN_ALREADY_OPENED_UART,
    PANIC_UART_UNABLE_TO_TAKE_SEMAPHORE,
    PANIC_UART_UNABLE_TO_GIVE_SEMAPHORE,
    PANIC_UART_UNABLE_TO_ENQUEUE_SLEEP_TIMER_COMMAND,
    PANIC_UART_UNABLE_TO_CREATE_SLEEP_TIMER,
    PANIC_UART_UNABLE_TO_DELETE_SLEEP_TIMER,
} PANIC_ID_UART;

/** @} end of group DRIVER_CMSIS_UART */

#endif /* UART_PANIC_H_ */
