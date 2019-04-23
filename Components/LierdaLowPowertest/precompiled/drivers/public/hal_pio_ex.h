/******************************************************************************
 * @brief    Hi2115 Specific PIO Multiplexor HAL Header.
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef HAL_PIO_EX_H_
#define HAL_PIO_EX_H_

#include "hal_pio.h"

/** @addtogroup DRIVER_HAL_PIO
 * @{
 * */

/**
 * HAL PIO GPIO Input/Output Direction
 */
typedef enum
{
    HAL_PIO_GPIO_DIR_IN,    //!< GPIO is an input
    HAL_PIO_GPIO_DIR_OUT,   //!< GPIO is an output
} HAL_PIO_GPIO_DIR;

/**
 * HAL PIO GPIO Input/Output Level
 */
typedef enum
{
    HAL_PIO_GPIO_LVL_LOW,       //!< GPIO is at a low logic level   (used for input/output)
    HAL_PIO_GPIO_LVL_HIGH,      //!< GPIO is at a high logic level  (used for input/output)
    HAL_PIO_GPIO_LVL_TOGGLE,    //!< GPIO logic level to be toggled (used for output only)
} HAL_PIO_GPIO_LVL;

/**
 * HAL PIO Analogue Multiplexer Routing
 */
typedef enum
{
    HAL_PIO_ROUTE_NONE,     //!< Don't route any multiplexer
    HAL_PIO_ROUTE_MUX_0,    //!< Route analogue multiplexer 0
    HAL_PIO_ROUTE_MUX_1,    //!< Route analogue multiplexer 1
} HAL_PIO_ROUTE;

/**
 * HAL PIO Interrupt Trigger Types
 */
typedef enum
{
    HAL_PIO_INTERRUPT_RISING,   //!< Interrupt triggered on a PIO rising edge
    HAL_PIO_INTERRUPT_FALLING,  //!< Interrupt triggered on a PIO falling edge
    HAL_PIO_INTERRUPT_HIGH,     //!< Interrupt triggered at a PIO high level
    HAL_PIO_INTERRUPT_LOW,      //!< Interrupt triggered at a PIO low level
} HAL_PIO_INTERRUPT;


/**
 * Set GPIO input/output direction
 * @param pin PIN number
 * @param dir Input/output
 */
void hal_pio_set_gpio_direction( PIN pin, HAL_PIO_GPIO_DIR dir );

/**
 * Set output level for a GPIO
 * @param pin PIN number
 * @param level GPIO output level
 */
void hal_pio_set_gpio_output( PIN pin, HAL_PIO_GPIO_LVL level );

/**
 * Set low output level for a GPIO
 * @param pin PIN number
 * @note Direct access function for speed.  No checks are made that pin is configured as a GPIO output.
 */
void hal_pio_clear_gpio( PIN pin );

/**
 * Set high output level for a GPIO
 * @param pin PIN number
 * @note Direct access function for speed.  No checks are made that pin is configured as a GPIO output.
 */
void hal_pio_set_gpio( PIN pin );

/**
 * Toggle output level for a GPIO
 * @param pin PIN number
 * @note Direct access function for speed.  No checks are made that pin is configured as a GPIO output.
 */
void hal_pio_toggle_gpio( PIN pin );

/**
 * Gets the input level for a GPIO
 * @param pin PIN number
 * @return Input level of the GPIO
 */
HAL_PIO_GPIO_LVL hal_pio_get_gpio_input( PIN pin );

/**
 * Route an analogue multiplexer to a pio
 * @param pin PIN number
 * @param multiplexer Analogue multiplexer to route
 */
void hal_pio_route_analogue( PIN pin, HAL_PIO_ROUTE multiplexer );

/**
 * Obtains current IRQ status for a PIO
 * @param pin PIN number
 * @return True if IRQ asserted, false otherwise
 */
bool hal_pio_is_interrupt_asserted( PIN pin );

/**
 * Clears the IRQ status for a PIO
 * @param pin PIN number
 */
void hal_pio_clear_interrupt( PIN pin );

/**
 * Configure an interrupt trigger type for a pio
 * @param pin PIN number
 * @param interrupt Interrupt type to configure
 * @param state Enabled/disabled
 */
void hal_pio_set_interrupt( PIN pin, HAL_PIO_INTERRUPT interrupt_trigger_type, INTERRUPT_STATE state);

/** @} end of group DRIVER_HAL_PIO */

#endif // HAL_PIO_EX_H_
