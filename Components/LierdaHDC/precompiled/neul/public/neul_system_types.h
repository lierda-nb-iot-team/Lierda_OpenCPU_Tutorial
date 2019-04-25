/******************************************************************************
 * @brief    System Functions for Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_SYSTEM_TYPES_H_
#define LIB_NEUL_SYSTEM_TYPES_H_

#include "neul_error_types.h"

/** @addtogroup libNEUL_SYSTEM
 * @{
 * */
 
#define NEUL_CHIPINFO_VERSION 1
typedef struct  
{
    uint16 version; //!<  structure version
    int16 vbat;     //!<  chip supply voltage in mV
    int16 temp;     //!<  chip temperature in degrees deciCelsius
} ue_chipinfo_t;

/*
 * Temperature Co-efficient is the voltage returned by the temperature sensor at 25 deg C 
 * It will always be a positive value, and a value of 0 indicates it is not valid
 */
#define TEMP_COEFFICIENT_UNKNOWN 0

/** @} end of group libNEUL_SYSTEM */

#endif /* LIB_NEUL_SYSTEM_TYPES_H_ */
