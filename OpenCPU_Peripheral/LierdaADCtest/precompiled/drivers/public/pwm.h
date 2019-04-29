/******************************************************************************
 * @brief    APPS PWM DRIVER Header File
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "hal_pwm_definitions.h"
#include "neulfw.h"
#include "platform.h"

/** @defgroup NONOS_DRIVERS_PWM Hi21XX non-OS PWM Driver
 * Hi21XX non-OS PWM Driver. After entering the low-power mode will no longer output PWM signal.
 * @ingroup NONOS_DRIVERS
 * @{
 * */

/** PWM configuration */
typedef struct
{
    /** Clock cycles spent in on phase */
    uint32 period_cycles;
    /** Duty cycle (parts per 1000) */
    uint16 duty_cycle;
} PWM_CYCLE_DATA ; //lint !e959

/** PWM configuration */
typedef struct
{
    uint32 period_us;
    /** Duty cycle (parts per 1000) */
    uint16 duty_cycle;
} PWM_US_DATA   ; //lint !e959

/** PWM configuration */
typedef struct
{
    uint32 period_ms;
    /** Duty cycle (parts per 1000) */
    uint16 duty_cycle;
} PWM_MS_DATA  ; //lint !e959


/** PWM configuration */
typedef struct
{
    /** PWM data length */
    uint32 length;
    /** PWM cycles (on and off) used for interrupts or stop */
    uint8 cycles;
    /** Flag to indicate the transmission should start again when finished */
    bool repeat;
} PWM_BASE_CONFIGURATION; //lint !e959

/**
 * Initialise the PWM module
 */
void pwm_init(void);

/**
 * De-initialise the PWM module
 */
void pwm_deinit(void);

/**
 * Open a PWM line and associate it with a PIN
 * @param pwm PWM Device to use
 * @param pin PIN to use for the PWM
 * @return true if the claim and configuration were successful
 */
bool pwm_open(PWM_NUMBER pwm, PIN pin);

/**
 * Start the PWM running.
 * @param pwm PWM data configuration
 * @param configuration PWM Configuration.
 * configuration.length is the length of that data.
 * configuration.cycles is the number of pwm cycles to run this configuration for.
 * configuration.repeat indicates if the transmission should be repeated when it has finished.
 * @param pwm_cycle_data pwm_cycle_data->period_cycles contains the data to be transmitted to the pwm device.
 * If configuration.length < configuration.cycles when reaching the last element in configuration.pwm_data the driver will wrap and
 * it will start again from the first element until it has sent uint8 configuration.cycles.
 * If the repeat flag is true the transmission will start from the fist element in the configuration.pwm_data again.
 * @note The driver does not copy the data therefore the data buffers have to be available during the transmission.
 */
void pwm_cycle_start(PWM_NUMBER pwm, PWM_BASE_CONFIGURATION configuration, PWM_CYCLE_DATA* pwm_cycle_data);

/**
 * Start the PWM running.
 * @param pwm PWM data configuration
 * @param configuration PWM Configuration.
 * @param pwm_us_data pwm_us_data->period_us is a cycle of time. ms values accepted: (1~5000).
 * If configuration.length < configuration.cycles when reaching the last element in configuration.pwm_data the driver will wrap and
 * it will start again from the first element until it has sent uint8 configuration.cycles.
 * If the repeat flag is true the transmission will start from the fist element in the configuration.pwm_data again.
 * @note The driver does not copy the data therefore the data buffers have to be available during the transmission.
 */
void pwm_us_start(PWM_NUMBER pwm, PWM_BASE_CONFIGURATION configuration, PWM_US_DATA* pwm_us_data);

/**
 * Start the PWM running.
 * @param pwm PWM data configuration
 * @param configuration PWM Configuration.
 * @param pwm_ms_data pwm_ms_data->period_ms is a cycle of time. ms values accepted: (1~300).
 * If configuration.length < configuration.cycles when reaching the last element in configuration.pwm_data the driver will wrap and
 * it will start again from the first element until it has sent uint8 configuration.cycles.
 * If the repeat flag is true the transmission will start from the fist element in the configuration.pwm_data again.
 * @note The driver does not copy the data therefore the data buffers have to be available during the transmission.
 */
void pwm_ms_start(PWM_NUMBER pwm, PWM_BASE_CONFIGURATION configuration, PWM_MS_DATA* pwm_ms_data);

/**
 * Stop a running PWM
 * @param pwm PWM Device
 */
void pwm_stop(PWM_NUMBER pwm);

/**
 * Close a previously opened PWM device
 * @param pwm PWM Device
 */
void pwm_close(PWM_NUMBER pwm);

/**
 * Register an interrupt callback
 * @param pwm PWM Device
 * @param callback callback to register
 */
void pwm_register_interrupt(PWM_NUMBER pwm, PWM_CALLBACK callback);

/**
 * Unregister an event interrupt
 * @param pwm PWM Device
 * @note If you have
 */
void pwm_unregister_interrupt(PWM_NUMBER pwm);

/** @} end of NONOS_DRIVERS_PWM */

#endif /* PWM_H_ */
