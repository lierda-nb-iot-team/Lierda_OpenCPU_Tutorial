/******************************************************************************
 * @brief    BOUDICA RTC DRIVER INTERFACE
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/
#ifndef NEUL_RTC_H
#define NEUL_RTC_H

#include <time.h>

/** @defgroup NONOS_DRIVERS_RTC Hi21XX non-OS RTC Driver
 * Hi21XX non-OS RTC Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

#define RTC_CLOCK_SPEED     32768
#define RTC_ONE_SECOND      (RTC_CLOCK_SPEED)
#define MINIMUM_RTC_DELAY   4
#define RTC_MS_IN_SECOND    1000

/*
 * These defines are the magic numbers used to convert from MS to RTC
 */
#define RTC_MS_TIME_MULTIPLY        (RTC_CLOCK_SPEED >> 3)
#define RTC_MS_TIME_DIVIDE          (1000 >> 3)
#define RTC_MS_CONVERT_TO_RTC(x)    (((uint64)x * RTC_MS_TIME_MULTIPLY) / RTC_MS_TIME_DIVIDE)

/**
 * @brief Used to pass a timer handle around
 */
typedef void* rtc_handle;

typedef void (*rtc_timer_callback)(void);

typedef enum
{
    RTC_FAILURE,
    RTC_SUCCESS
} rtc_status;

typedef enum
{
    CURRENT_TIME_FIELD_UPDATED                = 0x01,
    CURRENT_TIME_ZONE_FIELD_UPDATED           = 0x02,
    CURRENT_TIME_SAVING_TIME_FIELD_UPDATED    = 0x04,
} UPDATED_TIME_FIELDS;

/**
 * RTC flag for boudica.
 */
typedef enum
{
    RTC_FLAG_NORMAL = 0,
    RTC_FLAG_PERMANENT,    //the flag to make sure there is enough resource for caller
}RTC_FLAG;

/**
 * @brief Initialises the timer, assumes that the core clock has already been set up
 * And that the clock speed will not get changed again
 */
void rtc_init( void );

/**
 * Unlike the bellow functions this will add a timer at the specified RTC time
 * @param rtc_time The time rtc time to fire this timer
 * @param callback_func the function to call once the wait is done
 * @param flag the feature of rtc
 * @return the handler to the timer - NULL = failed
 */
rtc_handle rtc_add_at(uint64 rtc_time, rtc_timer_callback callback_func, RTC_FLAG flag);

/**
 * @brief Adds a new timer to the timer list
 * @param callback_delay - how many clock cycles to wait
 * @param callback_func the function to call once the wait is done
 * @param flag - the feature of rtc
 * @return the handler to the timer - NULL = failed
 */
rtc_handle rtc_add(uint64 callback_delay, rtc_timer_callback callback_func, RTC_FLAG flag);

/**
 * @brief Adds a permanent timer to the timer list
 * @param timer_id The timer id that you wish to reset
 * @param callback_delay - how many clock cycles to wait
 * @param callback_func the function to call once the wait is done
 * @return 0 on success, -1 otherwise - a failure indicates that the timer did not exist
 */
rtc_status rtc_reset(rtc_handle timer_id, uint64 callback_delay, rtc_timer_callback callback_func);

/**
 * @brief Adds a permanent timer to the timer list
 * @param timer_id The timer id that you wish to reset
 * @param callback_delay - how many clock cycles to wait
 * @param callback_func the function to call once the wait is done
 * @return 0 on success, -1 otherwise - a failure indicates that the timer did not exist
 */
rtc_status rtc_reset_ms(rtc_handle timer_id, uint32 callback_delay, rtc_timer_callback callback_func);

/**
 * @brief Adds a permanent timer to the timer list
 * @param timer_id The timer id that you wish to reset
 * @param callback_delay - how many clock cycles to wait
 * @param callback_func the function to call once the wait is done
 * @return 0 on success, -1 otherwise - a failure indicates that the timer did not exist
 */
rtc_status rtc_reset_s(rtc_handle timer_id, uint32 callback_delay, rtc_timer_callback callback_func);

/**
 * @brief Adds a new timer to the timer list
 * @param callback_delay - how many ms to wait
 * @param callback_func the function to call once the wait is done
 * @param flag - the feature of rtc
 * @return the handler to the timer - NULL = failed
 */
rtc_handle rtc_add_ms(uint32 callback_delay, rtc_timer_callback callback_func, RTC_FLAG flag);

/**
 * @brief Adds a new timer to the timer list
 * @param callback_delay - how many seconds to wait
 * @param callback_func the function to call once the wait is done
 * @param flag - the feature of rtc
 * @return the handler to the timer - NULL = failed
 */
rtc_handle rtc_add_s(uint32 callback_delay, rtc_timer_callback callback_func, RTC_FLAG flag);

/**
 * @param timer_id The timer id that you wish to stop
 * @return 0 on success, -1 otherwise - a failure indicates that the timer did not exist
 */
rtc_status rtc_stop(rtc_handle timer_id);
/**
 * @param timer_id The timer id that you wish to delete
 * @return 0 on success, -1 otherwise - a failure indicates that the timer did not exist or was already stopped
 */
rtc_status rtc_delete(rtc_handle timer_id);

/**
 * Read lower 32 bits of RTC
 * @return lower 32 bits of RTC
 */
uint32 rtc_get_time_lsbs(void);

/**
 * Gets the current RTC time value
 * @return the RTC time
 */
uint64 rtc_get_time(void);

/**
 * Gets the current RTC time in us
 * @return the RTC time in us
 */
uint64 rtc_get_time_us(void);

/**
 * Gets the current RTC time in ms
 * @return the RTC time in ms
 */
uint64 rtc_get_time_ms(void);

/**
 * Gets the current RTC time in whole seconds
 * @return the RTC time in whole seconds
 */
uint32 rtc_get_time_s(void);

/**
 * Converts the given time period, in microseconds, to the number of RTC ticks which are guaranteed
 * to cover that time period.  Takes into account that the request can occur anywhere within
 * the current RTC timer tick.
 * @param time_period_in_us The time period, in microseconds, to convert into RTC ticks
 * @return The number of RTC ticks required to cover the specified timer period
 */
uint64 rtc_convert_time_to_ticks( uint64 time_period_in_us );

/**
 * Obtains the RTC clock tick for some specified time in the future
 * @param time_period_in_ticks How long into the future to obtain an RTC time
 * @return The future RTC time, in ticks
 */
uint64 rtc_get_future_time( uint64 time_period_in_ticks );

/**
 * Set current time
 * @param current_time current time to set
 * @param time_zone expressed in quarters of an hour, between the local time and GMT; range -96...+96
 * @param daylight_saving_time uint is 1 hour
 * @param updated_time_fields updated time field flag for current_time, time_zone, daylight_saving_time
 */
void rtc_set_current_time(uint64 current_time, int8 time_zone, uint8 daylight_saving_time, uint8 updated_time_fields);

/**
 * get current time
 * @return the current time
 */
time_t get_current_time(void);

/**
 * get current time in ms
 * @return the current time
 */
uint64 get_current_time_ms(void);

/**
 * get daylight saving time
 * @return daylight saving time
 */
uint8 rtc_get_daylight_saving_time(void);

/**
 * get time zone
 * @return current time zone
 */
int8 rtc_get_time_zone(void);

/**
 * calibration rtc by rf
 * @param rtc_freq_calibrated_by_rf (calibrated RTC frequency in Hz) << 16
 */
void rtc_rf_calibration_rtc(uint32 rtc_freq_calibrated_by_rf);

/** @} end of NONOS_DRIVERS_RTC */

#endif
