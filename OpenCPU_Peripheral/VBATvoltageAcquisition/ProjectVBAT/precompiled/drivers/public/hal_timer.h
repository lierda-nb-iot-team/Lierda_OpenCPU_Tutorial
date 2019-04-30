/******************************************************************************
 * @brief    hal_timer header file
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

#include "neulfw.h"
#include "core.h"

/** @defgroup DRIVER_HAL_TIMER Hi211X HAL Timer Driver
 * HAL Timer Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

/*
 * This should get moved into a common place
 */
typedef void (*IRQ_Callback)(void);

/**
 * Sets up the timer with a delay
 * @param delay_in_ms The time until the interrupt is generated
 */
void hal_timer_setup( uint32 delay_in_ms );

/**
 * Sets the callback that this layer will call when it gets an interrupt
 * @param func the callback to call
 */
void hal_timer_set_callback( IRQ_Callback func );

/**
 * Simply stops the timer
 */
void hal_timer_cancel(void);

/**
 * Gets the remaining time in core cycles until the next timer interrupt
 * @return the remaining time till the next timer interrupt
 */
#define HAL_TIMER_GET_REMAINING()  \
    TIMER0_TIME

/**
 * Gets the number of core cycles that have elapsed since the timer was started
 * @return the number of core cycles that have elapsed since the timer was started
 */
#define HAL_TIMER_GET_ELAPSED()  \
    (TIMER0_LOAD - TIMER0_TIME)

/**
 * Gets the number of core cycles that have elapsed since the timer was started
 * @return the number of core cycles that have elapsed since the timer was started
 */
#define HAL_TIMER_GET_IRQ_ELAPSED()  \
    (MAX_UINT32 - TIMER0_TIME)

/**
 * Sets the number of clock cycles until the next interrupt
 */
#define HAL_TIMER_SET(value)  \
    TIMER0_LOAD = (value)

/**
 * Enables the timer bit in the TIMER0_CTRL register
 */
#define HAL_TIMER_ENABLE() \
    TIMER0_CTRL = 0x01

/**
 * Enables the timer and auto-repeat bit in the TIMER0_CTRL register
 */
#define HAL_TIMER_ENABLE_REPEATING() \
    TIMER0_CTRL = 0x03

/**
 * Disables the timer bit in the TIMER0_CTRL register
 */
#define HAL_TIMER_DISABLE() \
    TIMER0_CTRL = 0x00

/**
 * Indicates if a timer interrupt is pending
 */
#define HAL_TIMER_IS_IRQ_PENDING() \
        NVIC_GetPendingIRQ(Timer_IRQn)

/**
 * Enables the timer interrupt
 */
#define HAL_TIMER_ENABLE_IRQ() \
    NVIC_EnableIRQ(Timer_IRQn)

/**
 * Enables the timer interrupt
 */
#define HAL_TIMER_DISABLE_IRQ() \
    NVIC_DisableIRQ(Timer_IRQn)

/** @} end of group DRIVER_HAL_Timer */

#endif /* HAL_TIMER_H_ */
