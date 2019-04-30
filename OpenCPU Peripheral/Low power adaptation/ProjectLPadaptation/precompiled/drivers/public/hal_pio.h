/******************************************************************************
 * @brief    Hi21XX PIO Multiplexor HAL Header.
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef HAL_PIO_H_
#define HAL_PIO_H_

#include "core.h"
#include "platform.h"

/** @defgroup DRIVER_HAL_PIO Hi211X HAL PIO Driver
 * HAL PIO Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/**
 * Mask that can be applied to values of type HAL_PIO_OWNER
 */
#define HAL_PIO_OWNER_MASK (0x3)

/**
 * HAL PIO OWNER
 */
typedef enum
{
    HAL_PIO_OWNER_NONE     = 0,     //!<  This PIO is not claimed
    HAL_PIO_OWNER_SECURITY = 1,     //!<  SECURITY CORE
    HAL_PIO_OWNER_PROTOCOL = 2,     //!<  PROTOCOL CORE
    HAL_PIO_OWNER_APPS     = 3      //!<  APPLICATION CORE
} HAL_PIO_OWNER;

/**
 * PIO Drive Strength (only for outputs)
 */
typedef enum
{
    HAL_PIO_DRIVE_LOW,    //!< Low Drive Strength
    HAL_PIO_DRIVE_HIGH    //!< High Drive Strength
} HAL_PIO_DRIVE;

/**
 * PIO pull resistor (only for inputs)
 */
typedef enum
{
    HAL_PIO_PULL_NONE,  //!< No pull down or pull up enabled
    HAL_PIO_PULL_DOWN,  //!< Pull down enabled for this pin
    HAL_PIO_PULL_UP     //!< Pull up enabled for this pin
} HAL_PIO_PULL;

/**
 * Initialisation function for the hal_pio
 */
void hal_pio_init( void );

/**
 * Release the claims to every pio.
 */
void hal_pio_release_all( void );

/**
 * Release a specific pio.
 * @param pin PIN number
 */
void hal_pio_release( PIN pin );

/**
 * Claim a PIN (possibly silently removing a lesser core's claim) and assign a specific function to a PIN.
 * @param pin PIN number
 * @param function function to be set
 * @return True if PIO function set, false otherwise
 */
bool hal_pio_set_function_force( PIN pin, FUNC function );


/**
 * Claim a PIN (if it is unclaimed) and assign a specific function to it.
 * @param pin PIN number
 * @param function function to be set
 * @return True if PIO function set, false otherwise
 */
bool hal_pio_set_function( PIN pin, FUNC function );

/**
 * Return the current functions assigned to the PIN pio.
 * @param pin PIN number.
 * @return current functions assigned to the PIN pio. If the pio
 * has not been claimed by this core it will return FUNC_UNCLAIMED.
 */
FUNC hal_pio_get_function( PIN pin );

/**
 * Set the drive type for the pin.
 * @param pin PIN number
 * @param drive High or low drive
 */
void hal_pio_config_drive( PIN pin, HAL_PIO_DRIVE drive );

/**
 * Set a pull down or not for the pio.
 * @param pin PIN number
 * @param pull_type Internal pull resistor configuration
 */
void hal_pio_config_pull( PIN pin, HAL_PIO_PULL pull_type );

/**
 * Return the current owner for this pio.
 * @param pin PIN number
 * @return current owner for that PIN or HAL_PIO_OWNER_NONE if it has not been claimed.
 */
CORES hal_pio_get_owner( PIN pin );

/** @} end of group DRIVER_HAL_PIO */

#endif /* HAL_PIO_H_ */
