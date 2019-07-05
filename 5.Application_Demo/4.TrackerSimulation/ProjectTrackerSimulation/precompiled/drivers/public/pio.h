/******************************************************************************
 * @brief    PIO Multiplexor Driver Header.
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef PIO_H_
#define PIO_H_

#include "platform.h"
#include "neulfw.h"

/** @defgroup NONOS_DRIVERS_PIO Hi21XX non-OS PIO Driver
 * Hi21XX non-OS PIO Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

/** PIO Drive Strength (only for outputs) */
typedef enum {
    PIO_DRIVE_LOW, /**!<  Low Drive Strength   */
    PIO_DRIVE_HIGH /**!<  High Drive Strength  */
} PIO_DRIVE;

/** PIO Drive PULL Resistor options */
typedef enum {
    PIO_PULL_NONE,  /**!<  No pull down or pull up enabled  */
    PIO_PULL_DOWN,  /**!<  Pull down enabled for this pin   */
    PIO_PULL_UP,    /**!<  Pull up enabled for this pin     */
} PIO_PULL;

/** PIO output configuration */
typedef struct
{
    PIO_DRIVE drive; /*!< PIO Drive configuration          */
    PIO_PULL pull;   /*!< PIO Pull resistor configuration  */
} pio_out_config;

/** PIO input configuration */
typedef struct
{
    PIO_PULL pull;   /*!< PIO Pull resistor configuration  */
} pio_in_config;

/**
 * Initialise the PIO module.
 */
void pio_init(void);

/**
 * Release a PIN. Returns true if it was successfully released
 * @param pin PIN number
 * @return true if the release was successful
 */
bool pio_release(PIN pin);

/**
 * Claim a PIN (possibly silently removing a lesser core's claim) and assign a specific function to a PIN.
 * @param pin PIN number
 * @param function Function to set.
 * @return Returns true if successful.
 */
bool pio_set_function_force(PIN pin, FUNC function);

/**
 * Claim a PIN (if it is unclaimed) and assign a specific function to it.
 * @param pin PIN number
 * @param function Function to set.
 * @return Returns true if successful.
 */
bool pio_set_function(PIN pin, FUNC function);

/**
 * Obtains the current function for a PIN.
 * @param pin PIN number
 * @return The current function.
 */
FUNC pio_get_function( PIN pin );

/**
 * Configure the pull resistor and drive strength for an output PIO.
 * @param pin PIN number
 * @param config output configuration pointer
 */
void pio_output_config(PIN pin, const pio_out_config * config);

/**
 * Configure the pull resistor for an input PIN.
 * @param pin PIN number
 * @param config input configuration pointer
 */
void pio_input_config(PIN pin, const pio_in_config * config);

/** @} end of NONOS_DRIVERS_PIO */

#endif /* PIO_H_ */
