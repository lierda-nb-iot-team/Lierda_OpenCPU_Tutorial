/******************************************************************************
 * @brief    Temperature monitor types
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
/*
 * temp_mon_types.h
 */

#ifndef SRC_DRIVERS_CMSIS_TEMP_MON_SHARED_TEMP_MON_TYPES_H_
#define SRC_DRIVERS_CMSIS_TEMP_MON_SHARED_TEMP_MON_TYPES_H_


/*!< TEMP_MON function return value */
typedef enum
{
    TEMP_MON_RET_OK,
    TEMP_MON_RET_ERROR,
} TEMP_MON_RET;

#define TEMPERATURE_COEFFICIENT_DEFAULT (11550)
#define TEMPERATURE_COEFFICIENT_MINIMUM (10300)
#define TEMPERATURE_COEFFICIENT_MAXIMUM (12800)

#define KELVIN_OFFSET                              (273)
#define TEMP_OFFSET_ADJUSTMENT                     (16)   //  temperature offset from 0K to give more accurate reading
#define PTAT_V0_TEMPERATURE_OFFSET                 (KELVIN_OFFSET - TEMP_OFFSET_ADJUSTMENT)
#define STD_TEMP                                   (25)   // Temperature at which rf->temp_refV is defined.

#endif /* SRC_DRIVERS_CMSIS_TEMP_MON_SHARED_TEMP_MON_TYPES_H_ */
