/******************************************************************************
 * @brief    Hi21XX GPIO HAL INTERFACE
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "core.h"
#include "platform.h"
#include "gpio_definitions.h"


/** @defgroup DRIVER_HAL_GPIO Hi211X HAL GPIO Driver
 * HAL GPIO Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/**
 * Configure the direction of the GPIO
 * @param pin PIN to use
 * @param dir Direction
 */
void hal_gpio_config_dir(PIN pin, GPIO_DIRECTION dir);

/**
 * Set high the output of a GPIO.
 * @param pin PIN to use
 * @note assumes PIN configured as GPIO and as Output
 */
void hal_gpio_set(PIN pin);

/**
 * Set low the output for a GPIO.
 * @param pin PIN to use
 * @note assumes PIN configured as GPIO and as Output
 */
void hal_gpio_clear(PIN pin);

/**
 * Toggle the output of pin
 * @param pin PIN to use
 * @note assumes PIN configured as GPIO and as Output
 */
void hal_gpio_toggle(PIN pin);

/**
 * Read the input of pin
 * @param pin PIN to use
 * @note assumes PIN configured as GPIO and as Input
 */
bool hal_gpio_read(PIN pin);

/**
 * Sets the GPIO drive strength for the specified pin
 * @param pin PIN to use
 * @param drive GPIO drive strength to use
 * @note assumes PIN configured as GPIO and as Output
 */
void hal_gpio_drive_strength( PIN pin, GPIO_DRIVE_STRENGTH drive );

/**
 * Set a specific interrupt as enabled or disabled.
 * @param pin PIN to use
 * @param gpio_interrupt Interrupt type
 * @param state State to set the interrupt to
 */
void hal_gpio_set_interrupt(PIN pin, GPIO_INTERRUPT gpio_interrupt, INTERRUPT_STATE state);

/**
 * Disable all interrupts for an specific PIN
 * @param pin PIN to use
 */
void hal_gpio_disable_all_interrupts(PIN pin);

/**
 * Clear the interrupt for a pin configured as GPIO input.
 * @param pin PIN to use
 * @note assumes PIN configured as GPIO and as Input
 */
void hal_gpio_clear_interrupt(PIN pin);

/**
 * Returns the state of the interrupt.
 * @param pin PIN in use
 * @return true if the interrupt is asserted.
 */
bool hal_gpio_is_interrupt_asserted(PIN pin);

/** @} end of group DRIVER_HAL_GPIO */

#endif /* HAL_GPIO */
