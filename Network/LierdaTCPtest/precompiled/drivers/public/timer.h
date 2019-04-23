/******************************************************************************
 * @brief    Timer interface
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/
#ifndef NEUL_TIMER_H
#define NEUL_TIMER_H

/** @defgroup NONOS_DRIVERS_TIMER Hi21XX non-OS Timer Driver
 * Hi21XX non-OS Timer Driver
 * @ingroup NONOS_DRIVERS
 * @{
 * */

/**
 * Timer types
 */
typedef enum
{
    TIMER_TYPE_NORMAL = 0,   //!< Once triggered, this type of timer becomes a freely available resource again
    TIMER_TYPE_PERMANENT,    //!< Until deleted, this type of timer remains as an allocated resource
    TIMER_MAX_TYPES
}TIMER_TYPE;

/**
 * Used to pass a timer handle around
 */
typedef void* timer_handle;

/**
 * Timer Driver API status indications
 */
typedef enum
{
    TIMER_STATUS_SUCCESS = 0,
    TIMER_STATUS_FAILURE
}TIMER_STATUS;

/**
 * The callback type for the timers
 */
typedef void (*timer_callback)(void);

/**
 * Initialises the timer, assumes that the core clock has already been set up
 * And that the clock speed will not get changed again
 */
void timer_init( void );

/**
 * Adds a new timer to the timer list, with a callback_delay specified in core clock ticks
 * Note :
 ******************************************************************
 *                                                                *
 *      timer need add sleep veto when anyone working, because    *
 *      it will stop count and can't wakeup system after enter    *
 *      deep-sleep. after all timer is unused, it will remove     *
 *      sleep veto allowing system enter deep-sleep               *
 *                                                                *
 ******************************************************************
 * @param callback_delay - how many core clock cycles to wait, with an upper limit of MAX_UINT32
 * @param callback_func the function to call once the wait is done
 * @param flag - the feature of timer
 * @return the handler to the timer - NULL = failed
 * @note It's recommended to not use delays less that ~1000 clock ticks (~20us).  If such time periods are required then it is better to use the Timer HAL directly.
 */
timer_handle timer_add(uint32 callback_delay, timer_callback callback_func, TIMER_TYPE timer_type);

/**
 * Adds a new timer to the timer list, with a callback_delay specified in microseconds
 * @param callback_delay how many microseconds to wait, with an upper limit of 80,000,000 microseconds
 * @param callback_func the function to call once the wait is done
 * @param flag the feature of timer
 * @return the handler to the timer - NULL = failed
 * @note It's recommended to not use delays less that ~20us.  If such time periods are required then it is better to use the Timer HAL directly.
 */
timer_handle timer_add_us(uint32 callback_delay, timer_callback callback_func, TIMER_TYPE timer_type);

/**
 * Adds a new timer to the timer list, with a callback_delay specified in milliseconds
 * Note :
 ******************************************************************
 *                                                                *
 *      timer need add sleep veto when anyone working, because    *
 *      it will stop count and can't wakeup system after enter    *
 *      deep-sleep. after all timer is unused, it will remove     *
 *      sleep veto allowing system enter deep-sleep               *
 *                                                                *
 ******************************************************************
 * @param callback_delay - how many milliseconds to wait, with an upper limit of 80,000 milliseconds.
 * @param callback_func the function to call once the wait is done
 * @param flag - the feature of timer
 * @return the handler to the timer - NULL = failed
 */
timer_handle timer_add_ms(uint32 callback_delay, timer_callback callback_func, TIMER_TYPE timer_type);

/**
 * Adds a new timer to the timer list, with a callback_delay specified in seconds
 * Note :
 ******************************************************************
 *                                                                *
 *      timer need add sleep veto when anyone working, because    *
 *      it will stop count and can't wakeup system after enter    *
 *      deep-sleep. after all timer is unused, it will remove     *
 *      sleep veto allowing system enter deep-sleep               *
 *                                                                *
 ******************************************************************
 * @param callback_delay - how many seconds to wait, with an upper limit of 80 seconds.
 * @param callback_func the function to call once the wait is done
 * @param flag - the feature of timer
 * @return the handler to the timer - NULL = failed
 */
timer_handle timer_add_s(uint32 callback_delay, timer_callback callback_func, TIMER_TYPE timer_type);

/**
 * stop the timer by timer_handle, only call by permanent timer
 * @param timer_id - timer_handle alloc in timer_add
 * @return Either TIMER_STATUS_SUCCESS or TIMER_STATUS_FAILURE - a failure indicates that the timer did not exist
 */
TIMER_STATUS timer_stop(const timer_handle timer_id);

/**
 * reset the timer by timer_handle, only call by permanent timer
 * @param timer_id - timer_handle alloc in timer_add
 * @param callback_delay - how many core clock ticks to wait, with an upper limit of MAX_UINT32
 * @param callback_func the function to call once the wait is done
 * @return Either TIMER_STATUS_SUCCESS or TIMER_STATUS_FAILURE - a failure indicates that the timer did not exist
 */
TIMER_STATUS timer_reset(const timer_handle timer_id, uint32 callback_delay, timer_callback callback_func);

/**
 * reset the timer by timer_handle, only call by permanent timer
 * @param timer_id - timer_handle alloc in timer_add
 * @param callback_delay - how many microseconds to wait, with an upper limit of 80,000,000 microseconds
 * @param callback_func the function to call once the wait is done
 * @return Either TIMER_STATUS_SUCCESS or TIMER_STATUS_FAILURE - a failure indicates that the timer did not exist
 */
TIMER_STATUS timer_reset_us(timer_handle timer_id, uint32 callback_delay, timer_callback callback_func);

/**
 * reset the timer by timer_handle, only call by permanent timer
 * @param timer_id - timer_handle alloc in timer_add
 * @param callback_delay - how many milliseconds to wait, with an upper limit of 80,000 milliseconds
 * @param callback_func the function to call once the wait is done
 * @return Either TIMER_STATUS_SUCCESS or TIMER_STATUS_FAILURE - a failure indicates that the timer did not exist
 */
TIMER_STATUS timer_reset_ms(timer_handle timer_id, uint32 callback_delay, timer_callback callback_func);

/**
 * reset the timer by timer_handle, only call by permanent timer
 * @param timer_id - timer_handle alloc in timer_add
 * @param callback_delay - how many seconds to wait, with an upper limit of 80 seconds
 * @param callback_func the function to call once the wait is done
 * @return Either TIMER_STATUS_SUCCESS or TIMER_STATUS_FAILURE - a failure indicates that the timer did not exist
 */
TIMER_STATUS timer_reset_s(timer_handle timer_id, uint32 callback_delay, timer_callback callback_func);

/**
 *
 * @param timer_id The timer id that you wish to delete
 * @return Either TIMER_STATUS_SUCCESS or TIMER_STATUS_FAILURE - a failure indicates that the timer did not exist
 */
TIMER_STATUS timer_delete(const timer_handle timer_id);


#if defined TIMER_DRIVER_DEBUG
timer_handle timer_debug_get_active( void );
timer_handle timer_debug_get_dormant( void );
timer_handle timer_debug_get_free( void );
timer_handle timer_debug_get_next( timer_handle current );
bool timer_debug_get_info( timer_handle timer, uint32 *callback_delta, timer_callback *callback_func, timer_handle *prev, timer_handle *next, uint8 *timer_flag );
#endif

/** @} end of NONOS_DRIVERS_TIMER */

#endif
