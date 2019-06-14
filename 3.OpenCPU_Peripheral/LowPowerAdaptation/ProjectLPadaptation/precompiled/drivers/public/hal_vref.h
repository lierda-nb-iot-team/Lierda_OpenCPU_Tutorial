/******************************************************************************
 * @brief    HAL VREF interface.
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef HAL_VREF_H_
#define HAL_VREF_H_

#include "core.h"

/** @defgroup DRIVER_HAL_VREF Hi211X HAL VREF Driver
 * HAL VREF Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/*!< ADC gain */
typedef enum
{
    HAL_VREF_600,
    HAL_VREF_1200,
} HAL_VREF_VOLTAGE;  // Reference voltage

/**
 * @brief Set VREF voltage
 * @param voltage  to set reference to
 * @return None
 */
void hal_vref_set_voltage(HAL_VREF_VOLTAGE voltage);

/** @} end of group DRIVER_HAL_VREF */

#endif //HAL_VREF_H_
