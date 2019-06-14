/******************************************************************************
 * @brief    temperature monitor driver
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef DRIVERS_CMSIS_TEMP_MON_H_
#define DRIVERS_CMSIS_TEMP_MON_H_

/** @defgroup DRIVER_CMSIS_TEMP_MON Hi211X CMSIS Temperature Monitor Driver
 * CMSIS TEMP_MON Driver: Temperature Monitor Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */

#include "temp_mon_types.h"

/**
 * @brief Initialises the temp_mon driver
 */
void temp_mon_init(void);

/**
 * @brief Deinitialises the temp_mon driver
 */
void temp_mon_deinit(void);

/**
 * @brief Allow temperature coefficient to be set
 * @param temperature coefficient within valid range (1030-1280)
 * @return TEMP_MON_RET_ERROR if coefficient is invalid, else TEMP_MON_RET_OK
 */
TEMP_MON_RET temp_mon_set_coefficient(uint16 temperature_coefficient);

/**
 * @brief Convert voltage to temperature
 * @param voltage read from temp_mon
 * @return temperature in degrees deci-celcius
 */
int16 temp_mon_convert_uv_to_dcelsius(uint32 voltage);

/**
 * @brief Convert voltage to temperature with extra precision.
 * @param voltage read from temp_mon in uV
 * @return temperature in millidegrees celsius
 */
int32 temp_mon_convert_uv_to_mcelsius(uint32 voltage);

/**
 * @brief Calculate a new temperature coefficient based on measured and specified temperatures.
 * @param Temperature measured using the PTAT, in mC
 * @param Temperature specified, in C
 * @param New temperature coefficient, if calculation succeeded
 * @return TEMP_MON_RET_ERROR if calculated value is implausible, else TEMP_MON_RET_OK
 */
TEMP_MON_RET temp_mon_calculate_temperature_coefficient(int32 temperature_measured_mC, int16 temperature_input, uint16* new_temperature_coefficient);


/** @} end of group DRIVER_CMSIS_TEMP_MON */

#endif // DRIVERS_CMSIS_TEMP_MON_H_
