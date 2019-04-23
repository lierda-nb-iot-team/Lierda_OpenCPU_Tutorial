/******************************************************************************
 * @brief    NEUL ADC header.
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef DRIVERS_CMSIS_ADC_ADC_COMMON_H_
#define DRIVERS_CMSIS_ADC_ADC_COMMON_H_

/** @addtogroup  DRIVER_CMSIS_ADC
 * @{
 * */

#include "neulfw.h"
#include "adc_common.h"

/**
 * @brief Set the time to wait for the ADC to be read from protocol core
 * @param read_within_time_us number of us to wait. Minimum and maximum times apply
 * @return ADC_RET_OK for success else error
 */
ADC_RET adc_set_read_within_time(uint32 read_within_time_us);

/** @} end of group DRIVER_CMSIS_ADC */

#endif // DRIVERS_CMSIS_ADC_ADC_COMMON_H_
