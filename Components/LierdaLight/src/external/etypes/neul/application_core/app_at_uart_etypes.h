/******************************************************************************
 * @brief    APP AT UART ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef ETYPES_APPLICATION_CORE_APP_AT_UART_ETYPES_H_
#define ETYPES_APPLICATION_CORE_APP_AT_UART_ETYPES_H_

#include "neulfw.h"

/** @addtogroup libNEUL_APP_AT
 * @{
 * */

// Older implementation of at_uart_config
typedef struct
{
    uint32 baudrate;
    uint8  syncmode;
    uint8  stopbits;
    uint8  parity;
}at_uart_config_v1; //lint !e959: This is an internal structure, not shared on the wire.

// Current implementation
typedef struct
{
    uint32 baudrate;
    uint8  syncmode;
    uint8  stopbits;
    uint8  parity;
    uint8  sw_flow_control;
}at_uart_config; //lint !e959: This is an internal structure, not shared on the wire.

/** @} end of group libNEUL_APP_AT */

#endif /* ETYPES_APPLICATION_CORE_APP_AT_UART_ETYPES_H_ */
