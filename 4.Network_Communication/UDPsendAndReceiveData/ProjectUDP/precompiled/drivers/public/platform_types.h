/******************************************************************************
 * @brief    Hi2115 PLATFORM TYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef SRC_DRIVERS_PLATFORM_HI2115_SHARED_PLATFORM_TYPES_H_
#define SRC_DRIVERS_PLATFORM_HI2115_SHARED_PLATFORM_TYPES_H_


/** @defgroup BASE_DEFS Hi21XX Base Definitions
 * Hi21XX Base Definitions
 * @ingroup Hi21XX_Base
 * @{
 * */

#include "platform_etypes.h"

/**
 * Generic enum to specify the required core.
 * By using an enum, type safety can be enforced at compile time.
 */
typedef enum
{
    CORES_SECURITY_CORE             = 0,                               /*!< Security Core.                                              */
    CORES_PROTOCOL_CORE             = 1,                               /*!< Protocol Core.                                              */
    CORES_APPS_CORE                 = 2,                               /*!< Applications Core.                                          */
    CORES_MAX_NUMBER_PHYSICAL       = 3,                               /*!< Used to size/range arrays for physical cores where needed.  */
    CORES_NONE                      = CORES_MAX_NUMBER_PHYSICAL,       /*!< Used to return a NONE value where needed.                   */
    CORES_ASSET_CORE                = CORES_MAX_NUMBER_PHYSICAL,       /* used for asset store                                          */
    CORES_UNKNOWN                   = CORES_MAX_NUMBER_PHYSICAL + 1,   /*!< Used to return a unknown value.                             */
} CORES;

/**
 * Generic enum to specify the core image.
 * On master C20 the standard Security core is CORE_IMAGES_B_SECURITY
 * On production the standard Security core is CORE_IMAGES_A_SECURITY
 */
typedef enum
{
    CORE_IMAGES_A_SECURITY        = 0,  /*!< Security core image A. At the lowest loadable slot in Flash  */
    CORE_IMAGES_A_PROTOCOL        = 1,  /*!< Protocol core image A                                        */
    CORE_IMAGES_A_APPS            = 2,  /*!< Application core image A.                                    */
    CORE_IMAGES_B_SECURITY        = 3,  /*!< Security core image B.                                       */
    CORE_IMAGES_B_APPS            = 4,  /*!< Application core image B                                     */
    CORE_IMAGES_MAX_NUMBER        = 5,  /*!< Used to size/range arrays where needed.                      */
    CORE_IMAGES_UNKNOWN           = 6   /*!< Unknown core image                                           */
} CORE_IMAGES;

/**
 * Interrupt Service Routine Callback Type
 */
typedef void (*ISR_CALLBACK)(void);

/**
 *Interrupt State Type
 */
typedef enum
{
    INTERRUPT_STATE_DISABLED = 0, /*!< Interrupt Disabled */
    INTERRUPT_STATE_ENABLED = 1,  /*!< Interrupt Enabled  */
} INTERRUPT_STATE;

/**
 * UART error condition flags
 */
typedef enum
{
    UART_ERROR_NONE    = 0,
    UART_ERROR_FRAME   = 1,
    UART_ERROR_PARITY  = 2,
    UART_ERROR_BREAK   = 4,
    UART_ERROR_OVERRUN = 8
} UART_ERROR;



/** @} end of group BASE_DEFS */

#endif /* SRC_DRIVERS_PLATFORM_HI2115_SHARED_PLATFORM_TYPES_H_ */
