/******************************************************************************
 * @brief    BOUDICA hal RTC header file
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/
#ifndef RTC_H_
#define RTC_H_

#include "neulfw.h"
#include "core.h"
#include "memory_config.h"

/** @defgroup DRIVER_HAL_RTC Hi211X HAL RTC Driver
 * HAL RTC Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

typedef void (*hal_rtc_callback)(void);

/**
 * Number of RTC ticks that occur each second
 */
#define HAL_RTC_TICKS_PER_SEC 32768

/**
 * Maximum possible number of RTC ticks.  RTC is a 48-bit counter.
 */
#define HAL_RTC_MAX_TICKS ((1ULL << 48) - 1)

/*
 * Converts the given time period, in microseconds, to the number of RTC ticks which are guaranteed
 * to cover that time period.  Takes into account that the request can occur anywhere within
 * the current RTC timer tick.
 * Calculation is tailored to a 32768Hz tick rate of the RTC.  If that ever changes then this calculation
 * will also need to change.
 */
#define HAL_RTC_TIME_TO_TICKS(microsecs) ((((uint64)(microsecs) << 9) / 15625) + 1)

/**
 * Largest possible period of time
 * Based on the fact that any period of time will need multiplying by the number of RTC
 * ticks per second (currently 32768) at some point
 */
#define HAL_RTC_MAX_TIME_PERIOD ((1ULL << (64-15)) - 1)


/**Read the RTC IRQ time in a safe way
 * @return the current RTC IRQ time (64bit)
 */
uint64 hal_rtc_get_next_interrupt_time(void);

/**
 * Read lower 32 bits of RTC
 * @return lower 32 bits of RTC
 */
uint32 hal_rtc_get_time_lsbs( void );

/**Read the RTC timer in a safe way
 * @return the current RTC time
 */
uint64 hal_rtc_get_time(void) MEMORY_CONFIGURATION_FUNCTION_LOADABLE_IN_RAM;

/**Set the RTC IRQ time, and it should be called just from critical sections.
 * @param time is the IRQ time to set
 */
void hal_rtc_set_irq_time(uint64 time);

/**
 * Sets the RTC to trigger a interrupt after a delay
 * @param delay_in_ms The delay in ms
 */
void hal_rtc_setup( uint32 delay_in_ms );

/**
 * Sets the callback to be used by the RTC
 * @param func the callback function to use
 */
void hal_rtc_set_callback( hal_rtc_callback func );

/**
 * Clears any pending interrupts
 */
#define RTC_CLEAR_INTERRUPTS() \
    RTC_IRQ_CLR = 0xffffffff

/**
 * Disables the timer interrupt
 */
#define DISABLE_RTC_IRQ() \
    NVIC_DisableIRQ(RTC_IRQn)

/**
 * Enables the timer interrupt
 */
#define ENABLE_RTC_IRQ() \
    NVIC_EnableIRQ(RTC_IRQn)

/**
 * Gets the current RTC time in us
 * @return the RTC time in us
 */
uint64 hal_rtc_get_time_us(void);

/**
 * Gets the current RTC time in ms
 * @return the RTC time in ms
 */
uint64 hal_rtc_get_time_ms(void);

/**
 * Gets the current RTC time in whole seconds
 * @return the RTC time in whole seconds
 */
uint32 hal_rtc_get_time_s(void);

/**
 * Converts the given time period, in microseconds, to the number of RTC ticks which are guaranteed
 * to cover that time period.  Takes into account that the request can occur anywhere within
 * the current RTC timer tick.
 * @param time_period_in_us The time period, in microseconds, to convert into RTC ticks
 * @return The number of RTC ticks required to cover the specified timer period
 */
uint64 hal_rtc_convert_time_to_ticks( uint64 time_period_in_us );

/**
 * Obtains the RTC clock tick for some specified time in the future
 * @param time_period_in_ticks How long into the future to obtain an RTC time
 * @return The future RTC time, in ticks
 */
uint64 hal_rtc_get_future_time( uint64 time_period_in_ticks );

/** @} end of group DRIVER_HAL_RTC */

#endif
