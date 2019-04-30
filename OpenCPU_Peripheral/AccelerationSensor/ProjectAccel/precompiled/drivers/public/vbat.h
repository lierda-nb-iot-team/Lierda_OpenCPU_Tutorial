/******************************************************************************
 * @brief    battery voltage driver
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef DRIVERS_CMSIS_VBAT_H_
#define DRIVERS_CMSIS_VBAT_H_

/** @defgroup DRIVER_CMSIS_VBAT Hi211X CMSIS VBAT Driver
 * CMSIS VBAT Driver: Battery Voltage Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */

/**
 * @brief Initialises the vbat driver
 */
void vbat_init(void);

/**
 * @brief Deinitialises the vbat driver
 */
void vbat_deinit(void);

/** @} end of group DRIVER_CMSIS_VBAT */

#endif // DRIVERS_CMSIS_VBAT_H_
