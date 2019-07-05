/******************************************************************************
 * @brief    APPS PWM HAL Header File
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef HAL_PWM_H_
#define HAL_PWM_H_

#include "hal_pwm_definitions.h"

/** @defgroup DRIVER_HAL_PWM Hi211X HAL PWM Driver
 * HAL PWM Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/** PWM Interrupt causes */
typedef enum
{
    /** Interrupt when all the cycles to run for in PWM_CONFIGURATION has passed */
    HAL_PWM_INTERRUPT_END_OF_CYCLES_TO_RUN,
    /** Interrupt triggered at the end of every cycle */
    HAL_PWM_INTERRUPT_EVERY_CYCLE,
} HAL_PWM_INTERRUPT;

/**
 * Register a callback asociated with a PWM interrupt cause
 * @param pwm PWM device
 * @param interrupt_cause interrupt cause
 * @param callback callback to register
 */
void hal_pwm_register_callback(PWM_NUMBER pwm, HAL_PWM_INTERRUPT interrupt_cause, PWM_CALLBACK callback);

/**
 * Unregister a previously registered callback for a PWM device
 * @param pwm PWM device
 * @param interrupt_cause interrupt cause
 */
void hal_pwm_unregister_callback(PWM_NUMBER pwm, HAL_PWM_INTERRUPT interrupt_cause);

/**
 * Enable a PWM interrupt
 * @param pwm PWM device
 * @param interrupt_cause interrupt cause
 */
void hal_pwm_enable_interrupt(PWM_NUMBER pwm, HAL_PWM_INTERRUPT interrupt_cause);

/**
 * Disable a PWM interrupt
 * @param pwm PWM device
 * @param interrupt_cause interrupt cause
 */
void hal_pwm_disable_interrupt(PWM_NUMBER pwm, HAL_PWM_INTERRUPT interrupt_cause);

/**
 * Enable pwm clock
 */
void hal_pwm_clock_enable(void);

/**
 * Disable pwm clock
 */
void hal_pwm_clock_disable(void);

/**
 * Start the PWM device
 * @param pwm PWM device
 */
void hal_pwm_start(PWM_NUMBER pwm);

/**
 * Stop the PWM device
 * @param pwm PWM device
 */
void hal_pwm_stop(PWM_NUMBER pwm);

/**
 * Set the PWM scale field
 * @param pwm PWM device
 * @param scale value to set the scale value to
 */
void hal_pwm_set_scale(PWM_NUMBER pwm, uint8 scale);

/**
 * Set the repeat times and continuous field values
 * @param pwm PWM device
 * @param repeat_times value to set the repeat_times field to
 * @param continuous value for the continuous field
 */
void hal_pwm_set_times(PWM_NUMBER pwm, uint8 repeat_times, bool continuous);

/**
 * Set the number of cycles for phase 1 and phase 2
 * @param pwm PWM device
 * @param phase1_cycles number of cycles to set the phase1 field to
 * @param phase2_cycles number of cycles to set the phase2 field to
 */
void hal_pwm_set_cycles(PWM_NUMBER pwm, uint32 phase1_cycles, uint32 phase2_cycles);

/** @} end of group DRIVER_PWM_I2C */

#endif /* HAL_PWM_H_ */
