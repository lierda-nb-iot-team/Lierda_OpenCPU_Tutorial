/******************************************************************************
 * @brief    NEUL DAC header.
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef DRIVERS_CMSIS_DAC_DAC_H_
#define DRIVERS_CMSIS_DAC_DAC_H_

/** @defgroup DRIVER_CMSIS_DAC Hi211X CMSIS DAC Driver
 * CMSIS DAC Driver: The interfaces for handling aio, adc & dac will be replaced in an upcoming release and will not be backwards compatible.
 * @ingroup DRIVER_CMSIS
 * @{
 * */

/*!< DAC gain */
typedef enum
{
    DAC_VOLTAGE_RANGE_1200,
    DAC_VOLTAGE_RANGE_2000,
    DAC_VOLTAGE_RANGE_2800,
    DAC_VOLTAGE_RANGE_3600,
    DAC_VOLTAGE_RANGE_MAX,
} DAC_VOLTAGE_RANGE;

// VBAT is the maximum, which is 3.6V
#define DAC_VOLTAGE_1200 1200
#define DAC_VOLTAGE_2000 2000
#define DAC_VOLTAGE_2800 2800
#define DAC_VOLTAGE_3600 3600

/*!< DAC select static output enable or disable*/
typedef enum
{
    DAC_SEL_STATIC_DISABLE,
    DAC_SEL_STATIC_ENABLE,
    DAC_SEL_STATIC_NONE,
} DAC_SEL_STATIC;


/*!< DAC latch data enable or disable*/
typedef enum
{
    DAC_LATCH_DATA_DISABLE,
    DAC_LATCH_DATA_ENABLE,
    DAC_LATCH_DATA_NONE,
} DAC_LATCH_DATA;

/*!< DAC configuration */
typedef struct
{
    DAC_VOLTAGE_RANGE   dac_voltage_range;
    DAC_SEL_STATIC      dac_sel_static;
    DAC_LATCH_DATA      dac_latch_data;
} DAC_CONFIGURATION;

/*!< DAC function return value */
typedef enum
{
    DAC_RET_OK,
    DAC_RET_ERROR,
    DAC_RET_OUT_OF_RANGE,
    DAC_RET_INVALID_RANGE,
    DAC_RET_NOT_CALIBRATED
} DAC_RET;

/*!< DAC feedback setting */
typedef enum
{
    DAC_FEEDBACK_DISABLED,
    DAC_FEEDBACK_ENABLED,
} DAC_FEEDBACK;

/**
 * @brief Initialise DAC driver
 */
void dac_init(void);

/**
 * @brief De-initialise DAC driver
 */
void dac_deinit(void);

// Standard interface
/**
 * @brief  output voltage in mv. DAC must be calibrated
 * @param voltage to output in mv
 * @return  DAC_RET_OK on success, else error
 */
DAC_RET dac_write_mv(uint32 voltage_mv);

/**
 * @brief set feedback
 * @param feedback setting
 * @return  DAC_RET_OK on success, else error
 */
DAC_RET dac_set_feedback(DAC_FEEDBACK feedback);

//Raw interface
/**
 * @brief output value to DAC.
 * @param output value (0-1023)
 * @return  DAC_RET_OK on success, else error
 */
DAC_RET dac_raw_write(uint32 value);
/**
 * @brief  set output voltage range
 * @param  voltage range. maximum output value will be aligned to top of range voltage
 * @return  DAC_RET_OK on success, else error
 */
DAC_RET dac_set_range(DAC_VOLTAGE_RANGE range);

/** @} end of group DRIVER_CMSIS_DAC */

#endif // DRIVERS_CMSIS_DAC_DAC_H_
