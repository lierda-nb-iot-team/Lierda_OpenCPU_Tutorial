/******************************************************************************
 * @brief    HI21XX UART DEFINITIONS
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef HAL_UART_DEFINITIONS_H_
#define HAL_UART_DEFINITIONS_H_

/** @addtogroup DRIVER_HAL_UART
 * @{
 * */

/** Uart data bits available */
typedef enum
{
    UART_DATA_BITS_MIN_BITS = 0, /*!< Used for checking, the min value it can take */
    UART_DATA_BITS_5         = 0, /*!< 5 Data bits */
    UART_DATA_BITS_6         = 1, /*!< 6 Data bits */
    UART_DATA_BITS_7         = 2, /*!< 7 Data bits */
    UART_DATA_BITS_8         = 3, /*!< 8 Data bits */
    UART_DATA_BITS_MAX_BITS = 3, /*!< Used for checking, the max value it can take*/
} UART_DATA_BITS;

/** Uart parity modes available */
typedef enum
{
    UART_PARITY_NONE, /*!< No parity enabled */
    UART_PARITY_ODD,  /*!< Odd parity        */
    UART_PARITY_EVEN, /*!< Even parity       */
} UART_PARITY;

/** Uart stop bits modes available */
typedef enum
{
    UART_STOP_BITS_1 = 0, /*!< 1 Stop bit*/
    UART_STOP_BITS_2 = 1, /*!< 2 Stop bits */
} UART_STOP_BITS;

/** @} end of group DRIVER_HAL_UART */

#endif /* HAL_UART_DEFINITIONS_H_ */
