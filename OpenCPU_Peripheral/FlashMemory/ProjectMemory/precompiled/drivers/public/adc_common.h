/******************************************************************************
 * @brief    NEUL Common ADC header.
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef DRIVERS_CMSIS_ADC_ADC_H_
#define DRIVERS_CMSIS_ADC_ADC_H_

/** @defgroup DRIVER_CMSIS_ADC Hi211X CMSIS ADC Driver
 * CMSIS ADC Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */

#include "vref.h"

//These are nominal maximum voltages for each range; the actual maximum voltage is determined during calibration.
/*!< ADC gain */
typedef enum
{
    ADC_RANGE_AUTO,
    ADC_RANGE_1450,
    ADC_RANGE_2000,
    ADC_RANGE_2500,
    ADC_RANGE_3000,
    ADC_RANGE_3500,
    ADC_RANGE_4000,
    ADC_RANGE_DEFAULT = ADC_RANGE_4000,
    ADC_RANGE_MAX = ADC_RANGE_4000,
    ADC_RANGE_MIN = ADC_RANGE_1450
} ADC_RANGE;


/*!< ADC function return value */
typedef enum
{
    ADC_RET_OK,
    ADC_RET_ERROR,
    ADC_RET_OUT_OF_RANGE,
    ADC_RET_INVALID_GAIN,
    ADC_RET_NOT_CALIBRATED,
    ADC_RET_NOT_TRIMMED,
    ADC_RET_TIMEOUT,
    ADC_RET_DSP_BUSY /* Only applicable on Protocol Core */
} ADC_RET;

/* For apps core reads, the maximum time to wait for a reading can be
 * within certain limits, plus there is a default
 */
#define ADC_MAX_READ_READ_WITHIN_TIME       1000000  // maximum of 1 second
#define ADC_MIN_READ_READ_WITHIN_TIME           500  // minimum of 0.5 ms
#define ADC_DEFAULT_READ_READ_WITHIN_TIME    100000  // default of 0.1 s

/**
 * @brief Initialises the adc driver
 */
void adc_init(void);

/**
 * @brief Deinitialises the adc driver
 */
void adc_deinit(void);

/**
 * @brief Get the voltage corresponding to the max value returned using specified range
 * @param range to query
 * @param max voltage
 * @return ADC_RET_OK on success, else error
 */
ADC_RET adc_get_calibrated_max_voltage_mv(ADC_RANGE range, uint32 *voltage);

/**
 * @brief Read ADC in mV
 * @param number of samples to average over (0 uses default)
 * @param voltage returned
 * @return ADC_RET_OK on success, else error
 */
ADC_RET adc_read_mv(uint16 samples_to_average_over, uint32 *voltage);

/**
 * @brief Read ADC in uV
 * @param number of samples to average over (0 uses default)
 * @param voltage returned
 * @return ADC_RET_OK on success, else error
 */
ADC_RET adc_read_uv(uint16 samples_to_average_over, uint32 *voltage);

/**
 * @brief Read raw adc value
 * @param  raw ADC reading
 * @return ADC_RET_OK on success, else error
 */
 ADC_RET adc_read_raw(uint32 *reading);

/**
 * @brief Set range for raw read
 * @param range
 * @return None.
 */
void adc_set_range(ADC_RANGE range);

/**
 * @brief Generate calibration data for specified vref voltage. Must be connected to vref.
 * @param reference voltage applied
 * @return ADC_RET_OK for success else error
 */
ADC_RET adc_calibrate_for_voltage(VREF_VOLTAGE vref_voltage);

/**
 * @brief Generate calibration table from calibration voltages. Requires 2 sets of data at 2 vref values
 * @return ADC_RET_OK for success, else error
 */
ADC_RET adc_calibrate_calculate(void);

/**
 * @brief Measures comparator outputs with adc in cal mode (inputs shorted), and adjusts trim registers.
 * Routine exits leaving adc trims calibrated, and stores them for later reapplication.
 * @return ADC_RET_OK for success else error
 */
ADC_RET adc_find_trim_values(void);

/** @} end of group DRIVER_CMSIS_ADC */

#endif // DRIVERS_CMSIS_ADC_ADC_H_
