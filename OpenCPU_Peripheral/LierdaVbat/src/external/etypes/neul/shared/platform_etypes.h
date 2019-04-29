/******************************************************************************
 * @brief    PLATFORM ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef ETYPES_SHARED_PLATFORM_ETYPES_H_
#define ETYPES_SHARED_PLATFORM_ETYPES_H_

/** @defgroup BASE_DEFS Hi21XX Base Definitions
 * Hi21XX Base Definitions
 * @ingroup Hi21XX_Base
 * @{
 * */
#include "neulfw.h"

/**
 * Hi2115 PIN numbers
 */
typedef enum ETYPES_ENUM_HOLDER_TYPE(U8)
{
    PIN_0  = 0,        //!< PIN 0
    PIN_1  = 1,        //!< PIN 1
    PIN_2  = 2,        //!< PIN 2
    PIN_3  = 3,        //!< PIN 3
    PIN_4  = 4,        //!< PIN 4
    PIN_5  = 5,        //!< PIN 5
    PIN_6  = 6,        //!< PIN 6
    PIN_7  = 7,        //!< PIN 7
    PIN_8  = 8,        //!< PIN 8
    PIN_9  = 9,        //!< PIN 9
    PIN_10 = 10,       //!< PIN 10
    PIN_11 = 11,       //!< PIN 11
    PIN_12 = 12,       //!< PIN 12
    PIN_13 = 13,       //!< PIN 13
    PIN_14 = 14,       //!< PIN 14
    PIN_15 = 15,       //!< PIN 15
    PIN_16 = 16,       //!< PIN 16
    PIN_17 = 17,       //!< PIN 17
    PIN_18 = 18,       //!< PIN 18
    PIN_19 = 19,       //!< PIN 19
    PIN_20 = 20,       //!< PIN 20
    PIN_21 = 21,       //!< PIN 21
    PIN_22 = 22,       //!< PIN 22
    PIN_23 = 23,       //!< PIN 23
    PIN_24 = 24,       //!< PIN 24
    PIN_25 = 25,       //!< PIN 25
    PIN_26 = 26,       //!< PIN 26
    PIN_27 = 27,       //!< PIN 27
    PIN_28 = 28,       //!< PIN 28
    PIN_29 = 29,       //!< PIN 29
    PIN_30 = 30,       //!< PIN 30
    PIN_31 = 31,       //!< PIN 31
    PIN_32 = 32,       //!< PIN 32
    PIN_33 = 33,       //!< PIN 33
    PIN_34 = 34,       //!< PIN 34
    PIN_35 = 35,       //!< PIN 35
    PIN_36 = 36,       //!< PIN 36
    PIN_37 = 37,       //!< PIN 37
    PIN_38 = 38,       //!< PIN 38
    PIN_39 = 39,       //!< PIN 39
    PIN_NONE = 40,    //!< value used as invalid/unused PIN number
} PIN;

#define  PIN_MAX_NUMBER  PIN_NONE    // value USED to iterate in arrays

/**
 * UART pin configuration
 */
typedef struct
{
    PIN tx_pin;     //!< Transmission PIN
    PIN rx_pin;     //!< Reception PIN
    PIN cts_pin;    //!< Clear to send PIN
    PIN rts_pin;    //!< Request to send PIN to use
} uart_pin_configuration;


/** @} end of group BASE_DEFS */

#endif /* ETYPES_SHARED_PLATFORM_ETYPES_H_ */
