/******************************************************************************
 * @brief   aio functions library
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef SRC_LIB_AIO_FUNCTIONS_PUBLIC_AIO_FUNCTIONS_H_
#define SRC_LIB_AIO_FUNCTIONS_PUBLIC_AIO_FUNCTIONS_H_

#include "neulfw.h"
#include "core.h"

/** @defgroup MODULES_AIO_FUNCTIONS Hi211X AIO Functions
 * Hi211X AIO Functions: Common AIO Functions
 * @ingroup MODULES
 * @{
 * */

typedef enum {
    AIO_FUNC_RET_OK,
    AIO_FUNC_RET_ERROR,
} AIO_FUNC_RET;

/**
 * @brief Measures comparator outputs with adc in cal mode (inputs shorted), and adjusts trim registers.
 * AIO peripherals muxbus0 and ADC and... TODO? must not be claimed when calling
 * @return AIO_FUNC_RET_OK for success else error
 */
AIO_FUNC_RET aio_func_trim_adc(void);

/**
 * @brief Calibrate the ADC and set the internal ADC calibration tables
 * AIO peripherals vref, muxbus0 and ADC must not be claimed when calling
 * @return AIO_FUNC_RET_OK for success, error if invalid gain
 */
AIO_FUNC_RET aio_func_calibrate_adc(void);

/**
 * @brief read the analogue voltage present on the AIO<0> or AIO<1> pins, displayed in mv
 * @param voltage reading in millivolts
 * @param AIO<n> pin number, 0 or 1
 * @return AIO_FUNC_RET_OK for success, error for any read failure reason
 */
AIO_FUNC_RET aio_func_read_aiopin(uint32 *voltage, uint8 aio_pin_number);

/**
 * @brief read the analogue voltage present on the AIO<0> or AIO<1> pins, displayed as a raw value. without calibration
 * @param reading value
 * @param AIO<n> pin number, 0 or 1
 * @return AIO_FUNC_RET_OK for success, error for any read failure reason
 */
AIO_FUNC_RET aio_func_read_aiopin_raw(uint32 *value, uint8 aio_pin_number);

/**
 * @brief Calibrate the DAC and set the internal DAC calibration tables
 * AIO peripherals vref, muxbus0, DAC and ADC must not be claimed when calling
 *
 * @return AIO_FUNC_RET_OK for success, error if invalid gain
 */
AIO_FUNC_RET aio_func_calibrate_dac(void);

/**
 * @brief Read the battery voltage in mV and temperature
 * AIO peripherals vbat, temp, muxus0 and ADC must not be claimed when calling
 * @param temperature in degrees deciCelsius
 * @param voltage in mV
 * @return AIO_FUNC_RET_OK for success, error if invalid gain
 */
AIO_FUNC_RET aio_func_read_temp_vbat_mv(int16 *temperature, uint32 *voltage);

/**
  * @brief Measure the output of the temperature sensor and compare with the user-provided temperature to calculate
  * an updated temperature coefficient
  * @param temperature in degrees deciCelsius.
  * @return AIO_FUNC_RET_OK for success, otherwise error (eg if called before LL1 has been activated and calibrated the ADC)
  */
AIO_FUNC_RET aio_func_calibrate_temperature_coefficient(int16 temperature_input, uint16* new_temperature_coefficient);

/**
 * @brief retrieve the default temperature coefficient and use that to set the temp_mon conversion factor
 * @return AIO_FUNC_RET_OK for success, error if invalid gain
 */
AIO_FUNC_RET aio_func_set_default_temperature_coefficient(void);

/**
 * A wrapper for aio_func_set_default_temperature_coefficient so it can be posted to the freeRTOS timer task
 * @param unused Unused
 */
void aio_func_set_default_temperature_coefficient_wrapper(uint32 unused);

/** @} end of group MODULES_AIO_FUNCTIONS */

#endif /* SRC_LIB_AIO_FUNCTIONS_PUBLIC_AIO_FUNCTIONS_H_ */
