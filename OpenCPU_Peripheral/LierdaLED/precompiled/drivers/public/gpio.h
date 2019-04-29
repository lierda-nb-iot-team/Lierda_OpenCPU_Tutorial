/******************************************************************************
 * @brief    BOUDICA GPIO DRIVER
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "neulfw.h"
#include "platform.h"
#include "gpio_definitions.h"

/** @defgroup NONOS_DRIVERS_GPIO Hi21XX non-OS GPIO Driver
 * Hi21XX non-OS GPIO Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

/**
 * Typedef for the GPIO Callback.
 * It returns the number of the PIN which originated the interrupt.
 * @note It is executed in interrupt context.
 * @param pin PIN that caused the interrupt.
 */
typedef void (*GPIO_CALLBACK)(PIN pin);

/**
 * Initialise the gpio driver module.
 * This function should be called before any other on in the module.
 */
void gpio_init(void);

/**
 * De-initialise the GPIO module.
 */
void gpio_deinit(void);

/**
 * Claim a GPIO for either output or input.
 * @param pin PIN to use
 * @param dir Input or output direction
 * @return True if PIO claimed as a GPIO, false otherwise
 * @note If the GPIO is claimed as output the default configuration for the pin is PIO_DRIVE_HIGH and PIO_PULL_NONE
 * and the initial value is GPIO_LOW.  After claiming it the configuration can be changed with the pio_output_config function.
 * @note If the GPIO is claimed as input default configuration is PIO_PULL_NONE. After claiming it the configuration can be changed with the pio_input_config function.
 */
bool gpio_claim(PIN pin, GPIO_DIRECTION dir);

/**
 * Release a GPIO previously claimed.
 * @param pin PIN to use
 */
void gpio_release(PIN pin);

/**
 * Set to HIGH the output of a GPIO previously claimed for output.
 * @param pin PIN to use
 */
void gpio_set(PIN pin);

/**
 * Set to LOW the output of a GPIO previously claimed for output.
 * @param pin PIN to use
 */
void gpio_clear(PIN pin);

/**
 * Toggle the value of a GPIO previously claimed for output.
 * @param pin PIN to use
 */
void gpio_toggle(PIN pin);

/**
 * Read the value in a GPIO previously claimed.
 * @param pin PIN to use
 * @return value on the GPIO input
 */
bool gpio_read(PIN pin);

/**
 * Sets the GPIO drive strength for the specified pin
 * @param pin PIN to use
 * @param drive GPIO drive strength to use
 */
void gpio_drive_strength( PIN pin, GPIO_DRIVE_STRENGTH drive );

/**
 * Register a callback for this PIN. The callback registered will when the trigger happens.
 * Callbacks are not cummulative, if a new callback is registered it will overwrite the other one
 * therefore just the most recent callback and trigger are taking into account.
 * @note As soon as the callback is registered the interrupts will be enabled.
 * @param pin PIN to use
 * @param trigger Trigger under which the callback will be invoked
 * @param callback Pointer to callback
 */
void gpio_register_callback(PIN pin, GPIO_INTERRUPT trigger, GPIO_CALLBACK callback);

/**
 * Unregister all callbacks previously register for this PIN
 * @param pin PIN to use
 * @return value on the GPIO input
 */
void gpio_unregister_callback(PIN pin);

/** @} end of group NONOS_DRIVERS_GPIO */

#endif /* GPIO_H_ */
