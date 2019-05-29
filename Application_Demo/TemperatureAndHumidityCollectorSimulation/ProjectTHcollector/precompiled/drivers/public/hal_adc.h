/******************************************************************************
 * @brief    ADC HAL interface.
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef HAL_ADC_H_
#define HAL_ADC_H_

#include "core.h"

/** @defgroup DRIVER_HAL_ADC Hi211X HAL ADC Driver
 * HAL ADC Driver
 * @ingroup DRIVER_HAL
 * @{
 * */


/*!< ADC range */
typedef enum
{
    HAL_ADC_RANGE_1450 = 0x00,
    HAL_ADC_RANGE_2000 = 0x01,
    HAL_ADC_RANGE_2500 = 0x02,
    HAL_ADC_RANGE_3000 = 0x03,
    HAL_ADC_RANGE_3500 = 0x04,
    HAL_ADC_RANGE_4000 = 0x05,
} HAL_ADC_RANGE;  // Approximate input voltage range of the applications ADC(mV). Accurate values determined during calibration.

/**
 * @brief Sets the Input Voltage Range of the Applications ADC
 * ADC will convert the input voltage to 1024 steps between 0V and the Full Scale Voltage.(1.45V, 2.00V, 2.5V, 3.0V, 3.5V, 4.0V)
 * @param hal_adc_voltage, Full scale voltage.
 * @return None
 */
void hal_adc_set_range(HAL_ADC_RANGE hal_adc_range);

/**
 * @brief Get ADC Output Value(1 ~ 1023)
 * @param None.
 * @return data.
 */
uint32 hal_adc_get_data(void);

/**
 * @brief Get Averaged ADC Output Value(0 ~ 1023*num_samples)
 * @param number of samples to sum over.
 * @return data.
 */
uint32 hal_adc_get_data_sum(uint16 num_samples);

/** @} end of group DRIVER_HAL_ADC */


/**
 * @brief Selects ADC trim mode
 * @param cal, 0 for off, 1 for on.
 * @return None.
 */
void hal_adc_select_trim_mode(uint8 on);

/**
 * @brief Set ADC driver config
 * @param config, ADC config.
 * @return None.
 */
void hal_set_adc_config(uint32 config);

/**
* @brief ADC offset calibration trim
* @param trim, offset trim
* @return None.
*/
void hal_adc_set_offset_hi(uint8 trim);

/**
* @brief ADC offset calibration trim
* @param trim, offset trim
* @return None.
*/
void hal_adc_set_offset_msb_lo(uint8 trim);

/**
* @brief ADC offset calibration trim
* @param trim, offset trim
* @return None.
*/
void hal_adc_set_offset_lsb_lo(uint8 trim);

/**
* @brief ADC offset calibration control
* @param on, select comp0
* @return None.
*/
void hal_adc_set_comp_sel0(uint8 on);

/**
* @brief ADC offset calibration control
* @param on, select comp1
* @return None.
*/
void hal_adc_set_comp_sel1(uint8 on);

/**
* @brief ADC offset calibration control
* @param on, select CM level
 * @return None.
*/
void hal_adc_set_cm_sel(uint8 on);

#endif
