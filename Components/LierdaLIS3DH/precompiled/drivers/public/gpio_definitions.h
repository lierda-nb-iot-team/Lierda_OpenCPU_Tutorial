/******************************************************************************
 * @brief    BOUDICA GPIO Definitions
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef GPIO_DEFINITIONS_H_
#define GPIO_DEFINITIONS_H_

/** GPIO Interrupt triggers */
typedef enum {
    /** Interrupt on rising edge of signal */
    GPIO_INTERRUPT_RISING_EDGE,
    /** Interrupt on falling edge of signal */
    GPIO_INTERRUPT_FALLING_EDGE,
    /** Interrupt on rising or falling edge of signal */
    GPIO_INTERRUPT_ANY_EDGE,
    /** Interrupt when logic zero */
    GPIO_INTERRUPT_LOW,
    /** Interrupt when logic one */
    GPIO_INTERRUPT_HIGH
} GPIO_INTERRUPT;

/** GPIO DIRECTIONS  */
typedef enum {
    GPIO_DIRECTION_INPUT  = 0, /** !< GPIO_DIRECTION_INPUT  */
    GPIO_DIRECTION_OUTPUT = 1,/** !< GPIO_DIRECTION_OUTPUT */
} GPIO_DIRECTION;

/**
 *  GPIO Drive Strength
 */
typedef enum
{
    GPIO_DRIVE_STRENGTH_LOW,     //!< Low drive strength for GPIO configured as an output
    GPIO_DRIVE_STRENGTH_HIGH,    //!< High drive strength for GPIO configured as an output
} GPIO_DRIVE_STRENGTH;

#endif /* GPIO_DEFINITIONS_H_ */
