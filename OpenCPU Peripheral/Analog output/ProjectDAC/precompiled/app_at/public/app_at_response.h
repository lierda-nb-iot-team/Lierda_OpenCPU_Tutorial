/******************************************************************************
 * @brief    AT response 
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef APP_AT_RESPONSE_H_
#define APP_AT_RESPONSE_H_

#define APP_AT_RESPONSE_MAX_LEN 30

/** @addtogroup libNEUL_APP_AT_INT
 * @{
 * */

typedef enum
{
    CMEE_NONE = 0,
    CMEE_NUMERIC,
} CMEE_ERROR_TYPE;

/**
 * @brief Get the error response behaviour.
 * @return value CMEE_ERROR_TYPE.
 */
CMEE_ERROR_TYPE get_cmee_error_type(void);

/**
 * @brief Set the error response behaviour.
 * @param error The error type to set.
 */
void set_cmee_error_type(CMEE_ERROR_TYPE error);

/**
 * @brief Print at response according CMEE_ERROR_TYPE.
 * @param err The AT_RET type to transform.
 */
void at_status_output(AT_RET err);

const char * get_ceer_register_reject_cause(uint8 cause);

/**
 * @brief process response from callback function.
 * @param err The AT_RET type to transform.
 */
void app_at_send_callback_response(AT_RET result);

/**
 * @brief process response from callback function
 * @param err The AT_RET type to transform
 */
void app_at_send_sms_callback_response(AT_SMS_RET result);

/**
 * @brief Print at response according CMEE_ERROR_TYPE.
 * @param err The AT_SMS_RET type to transform.
 */
void at_status_sms_output(AT_SMS_RET err);

/** @} end of group libNEUL_APP_AT_INT */

#endif
