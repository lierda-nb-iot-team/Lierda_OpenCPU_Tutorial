/******************************************************************************
 * @brief    DAC HAL interface.
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef HAL_DAC_H_
#define HAL_DAC_H_

#include "core.h"

/** @defgroup DRIVER_HAL_DAC Hi211X HAL DAC Driver
 * HAL DAC Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/*!< DAC gain */
typedef enum
{
    HAL_DAC_RANGE_1200 = 0x00,
    HAL_DAC_RANGE_2000 = 0x01,
    HAL_DAC_RANGE_2800 = 0x02,
    HAL_DAC_RANGE_3600 = 0x03,
} HAL_DAC_RANGE;  // output voltage range of the applications DAC (mV)

// maximum value that can be written
#define HAL_DAC_MAX_LSB (1023)

/*!< DAC select static output enable or disable*/
typedef enum
{
    HAL_DAC_SEL_STATIC_DISABLE,
    HAL_DAC_SEL_STATIC_ENABLE,
} HAL_DAC_SEL_STATIC;

/*!< DAC selects star connected feedback path to the relevant AIO*/
typedef enum
{
    HAL_DAC_SEL_EXT_FB_DISABLE,
    HAL_DAC_SEL_EXT_FB_ENABLE,
} HAL_DAC_SEL_EXT_FB;

/*!< DAC latch data enable or disable*/
typedef enum
{
    HAL_DAC_LATCH_DATA_DISABLE,
    HAL_DAC_LATCH_DATA_ENABLE,
} HAL_DAC_LATCH_DATA;

/**
 * @brief Reduces operating current of application DAC for static outputs
 * @param HAL_DAC_SEL_STATIC_DISABLE or HAL_DAC_SEL_STATIC_ENABLE
 * @return None
 */
void hal_dac_set_sel_static(HAL_DAC_SEL_STATIC hal_dac_sel_static);

/**
 * @brief Selects star connected feedback path to the relevant AIO
 * @param HAL_DAC_SEL_EXT_FB_DISABLE or HAL_DAC_SEL_EXT_FB_ENABLE
 * @return None
 */
void hal_dac_set_sel_ext_fb(HAL_DAC_SEL_EXT_FB hal_dac_sel_ext_fb);

/**
 * @brief Latches application DAC data can be used to improve transients
 * with dynamic outputs
 * @param HAL_DAC_LATCH_DATA_DISABLE or HAL_DAC_LATCH_DATA_ENABLE
 * @return None
 */
void hal_dac_set_latch_data(HAL_DAC_LATCH_DATA hal_dac_latch_data);

/**
 * @brief Sets the Output Voltage Range of the Applications DAC
 * DAC output will be in 512 steps between 0V and the Full Scale Voltage.(1.2V, 2.0V, 2.8V, 3.6V)
 * @param  HAL_DAC_VOLTAGE_1200  -- Full scale voltage 1.2V
 *         HAL_DAC_VOLTAGE_2000  -- Full scale voltage 2.0V
 *         HAL_DAC_VOLTAGE_2800  -- Full scale voltage 2.8V
 *         HAL_DAC_VOLTAGE_3600  -- Full scale voltage 3.6V
 * @return None
 */
void hal_dac_set_range(HAL_DAC_RANGE hal_dac_voltage);

/**
 * @brief Set DAC Output Value(1 ~ 511)
 * @param data Dac output Voltage(1 ~ 511)
 * @return None
 */
void hal_dac_set_data(uint16 val);

/** @} end of group DRIVER_HAL_DAC */

#endif

