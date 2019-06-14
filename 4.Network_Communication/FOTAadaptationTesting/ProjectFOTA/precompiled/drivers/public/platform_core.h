/******************************************************************************
 * @brief    Hi2115 Application Core Platform Definitions
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef PLATFORM_CORE_H_
#define PLATFORM_CORE_H_

#include "platform_definitions.h"

/** @addtogroup DRIVER_PLATFORM
 * @{
 * */
/**
 * Maximum UART buses
 * Defined here rather than in the UART_BUS enum, due to needing to use it for conditional compilation
 */
#define UART_BUS_MAX_NUMBER 3            //!< Max number of UARTS available

/**
 * Maximum I2C buses
 * Defined here rather than in the I2C_BUS enum, due to needing to use it for conditional compilation
 */
#define I2C_BUS_MAX_NUMBER 2            //!< Max number of I2C available

/**
 * UART buses
 */
typedef enum
{
    UART_BUS_0 = 0,                      //!< UART 0
    UART_BUS_1 = 1,                      //!< UART 1
    UART_BUS_2 = 2,                      //!< UART 2
    UART_BUS_NONE = UART_BUS_MAX_NUMBER  //!< Value used as invalid/unused UART number
} UART_BUS;

/*!< I2C bus */
typedef enum
{
    I2C_BUS0,                            //!< I2C 0
    I2C_BUS1,                            //!< I2C 1
    I2C_BUS_NONE = I2C_BUS_MAX_NUMBER
}I2C_BUS;

/** @} end of group DRIVER_PLATFORM */

#endif /* PLATFORM_CORE_H_ */
