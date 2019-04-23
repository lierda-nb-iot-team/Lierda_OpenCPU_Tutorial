/******************************************************************************
 * @brief    voltage reference driver
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef DRIVERS_CMSIS_VREF_H_
#define DRIVERS_CMSIS_VREF_H_

/** @defgroup DRIVER_CMSIS_VREF Hi211X CMSIS VREF Driver
 * CMSIS VREF Driver: Voltage Reference Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */

/*!< VREF voltage */
typedef enum
{
    VREF_VOLTAGE_600,
    VREF_VOLTAGE_1200,
    VREF_VOLTAGE_MAX = VREF_VOLTAGE_1200
} VREF_VOLTAGE;


/*!< VREF function return value */
typedef enum
{
    VREF_RET_OK,
    VREF_RET_ERROR,
} VREF_RET;

/**
 * @brief Initialises the vref driver
 */
void vref_init(void);

/**
 * @brief Deinitialises the vref driver
 */
void vref_deinit(void);

/**
 * @brief Set VREF voltage
 * @param voltage in mV
 */
VREF_RET vref_set(VREF_VOLTAGE voltage);

/** @} end of group DRIVER_CMSIS_VREF */

#endif // DRIVERS_CMSIS_VREF_H_
