/******************************************************************************
 * @brief    Hi211X Activity Indication Function Interface
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LIB_ACTIVITY_INDICATION_H
#define LIB_ACTIVITY_INDICATION_H

/** @defgroup libNEUL_ACTIVITY_INDICATION Hi21XX Activity Indication
 * Hi21XX Activity Indication
 * @ingroup HI21XX_MODULES
 * @{
 * */

/**
* This is an activity indication pin. The pin signalling when an external
 * MCU might want to wake so it can interact with the UE.
 * activity_indication_init()  function will initialize the pin.The pin and
 * delay microseconds are set by key value pairs.
 * activity_indication_output()  function controls the pin drive high and delay
 * or drive low.It must be drive low after the control pin drive high.
 */
 typedef enum
 {
     ACTIVITY_INDICATION_RET_OK,
     ACTIVITY_INDICATION_RET_ERROR,
 }ACTIVITY_INDICATION_RET;


/**
 * Activity indication init
 * @return None
 */
void activity_indication_init(void);

/**
 * Activity indication deinit
 * @return None
 */
void activity_indication_deinit(void);

/**
 * Set the activity indication pin to drive high and delay or drive low
 * @param  Set true ,pin drive high and delay;set false,pin drive low
 * @return None
 */
ACTIVITY_INDICATION_RET activity_indication_output(bool active_pin);

/** @} end of group libNEUL_ACTIVITY_INDICATION */

#endif  /* LIB_ACTIVITY_INDICATION_H */
