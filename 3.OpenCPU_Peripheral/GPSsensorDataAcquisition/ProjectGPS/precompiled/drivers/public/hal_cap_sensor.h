/******************************************************************************
 * @brief    BOUDICA CAPACITOR SENSOR HAL
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef HAL_CAP_SENSOR_H_
#define HAL_CAP_SENSOR_H_

/** @defgroup DRIVER_HAL_CAP_SENSOR Hi211X HAL Cap Sensor Driver
 * HAL Cap Sensor Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/**
 * Register a callback for the Capacitor Sensor Interrupt
 * @param func callback to register
 */
void hal_cap_sensor_set_callback(ISR_CALLBACK func);

/**
 * Enables the Capacitor Sensor clock
 */
void hal_cap_sensor_enable(void);

/**
 * Enables the capacitor sensor interrupts
 */
void hal_cap_sensor_enable_interrupts(void);

/**
 * Disables the capacitor sensor interrupt, unregister any interrupt and disables the interrupts
 */
void hal_cap_sensor_disable(void);

/** @} end of group DRIVER_CMSIS_CAP_SENSOR */

#endif /* HAL_CAP_SENSOR_H_ */
