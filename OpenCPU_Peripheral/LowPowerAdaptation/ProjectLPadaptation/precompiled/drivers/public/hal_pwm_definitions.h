/******************************************************************************
 * @brief    BOUDICA APPS PWM DEFINITIONS
 * Copyright (c) 2015 NEUL LIMITED
******************************************************************************/

#ifndef HAL_PWM_DEFINITIONS_H_
#define HAL_PWM_DEFINITIONS_H_

/** @addtogroup DRIVER_HAL_PWM
 * @{
 * */

/** PWM DEVICES */
typedef enum
{
    /** PWM Peripheral 0 */
    PWM_NUMBER_0 = 0,
    /** PWM Peripheral 1 */
    PWM_NUMBER_1 = 1,
    /** Number of PWM Devices*/
    PWM_NUMBER_MAX =2,
} PWM_NUMBER;

/** PWM CALLBACK TYPE */
typedef void (*PWM_CALLBACK)(PWM_NUMBER pwm);

/** @} end of group DRIVER_HAL_PWM */

#endif /* HAL_PWM_DEFINITIONS_H_ */
