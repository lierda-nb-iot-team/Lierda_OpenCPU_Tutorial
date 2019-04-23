/******************************************************************************
 * @brief    AT send format data through at uart.
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef APP_AT_SEND_DATA_H_
#define APP_AT_SEND_DATA_H_

#include "app_at.h"

/** @addtogroup libNEUL_APP_AT_MOD_API
 * @{
 * */

/**
 * @brief send at string through at uart.
 * @param at_string The at string to send out through at uart.
 * @param claim With Claim at uart before send and release at uart after send or not. 
 * @param log_flag flag for log print.
 */
void app_at_send_at_rsp_string(const char *at_string, bool claim, AT_FLAG log_flag);

/**
 * @brief send at string through at uart and with "\r\n" string before, after at string.
 * @param at_string The at string to send out through at uart.
 * @param claim With Claim at uart before send and release at uart after send or not.
 * @param log_flag flag for log print.
 */
void app_at_send_at_rsp_string_lines(const char *at_string, bool claim, AT_FLAG log_flag);

/**
 * @brief send at string through at uart and with "\r\n" string before, after at string.
 * @With Claim at uart before send and release at uart after send. With log output after send.
 * @param at_string The at string to send out through at uart.
 */
void app_at_send_at_rsp_string_lines_with_claim_and_log(const char *at_string);

/**
 * @brief send at string through at uart and with "\r\n" string before, after at string.
 *  restricted output log include private persional data when user need to restracted it.
 * @With Claim at uart before send and release at uart after send. With log output after send.
 * @param at_string The at string to send out through at uart.
 */
void app_at_send_at_rsp_string_lines_with_claim_and_log_restricted(const char *at_string);

/**
 * @brief send at string through at uart and "\r\n" string after at string. Without claim at uart and release at uart. With log.
 * @param at_string The at string to send out through at uart.
 * @param log_flag flag for log print.
 */
void app_at_send_at_rsp_string_rn_no_claim(const char *at_string, AT_FLAG log_flag);

/**
 * @brief send at hexstring through at uart with "\r\n" string before, after at hexstring. Without claim at uart and release at uart. Without log.
 * @param at_string The at hexstring to send out through at uart.
 * @param offset_to_convert The position need to convert to hexstring.
 * @param length_to_convert The length need to convert to hexstring.
 */
void app_at_send_convert_hexstring_no_claim(const char *at_string, uint16 offset_to_convert, uint16 length_to_convert);

/**
 * @brief send string through uart without modification
 * @param at_string The string to output
 */
void app_at_send_at_string_no_claim(const char *at_string);

/**
 * @brief queue a string that can be output after any current output being printed has completed
 * @param at_string The message string to print later.
 * @param log_flag The attribute of message.
 * @param offset_to_convert The start offset in message should be convert to hexstring.
 * @param length_to_convert The length in message should be convert to hexstring.
 */
void app_at_send_at_string_delayed_async(const char *at_string, AT_FLAG log_flag, uint16 offset_to_convert, uint16 length_to_convert);

/**
 * @brief claim the uart. Allows _no_claim output to be grouped without unsolicited messages being inserted
 */
void app_at_send_claim(void);

/**
 * @brief release the uart. Allows _no_claim output to be grouped without unsolicited messages being inserted
 */
void app_at_send_release(void);

/** @} end of group libNEUL_APP_AT_MOD_API */

#endif
