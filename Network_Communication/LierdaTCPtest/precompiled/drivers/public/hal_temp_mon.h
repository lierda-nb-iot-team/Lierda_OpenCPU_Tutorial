/******************************************************************************
 * @brief    HAL TEMP_MON interface.
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef HAL_TEMP_MON_H_
#define HAL_TEMP_MON_H_

#include "core.h"

/** @defgroup DRIVER_HAL_TEMP_MON Hi211X HAL TEMP_MON Driver
 * HAL TEMP_MON Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/**
 * @brief Set Temp Mon offset
 * @param offset to set
 */
void hal_temp_mon_set_voltage_offset(uint8 offset);

/** @} end of group DRIVER_HAL_TEMP_MON */

#endif //HAL_TEMP_MON_H_
