/******************************************************************************
 * @brief    SMS Messaging Functions for Hi21XX
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_SMS_MESSAGING_H_
#define LIB_NEUL_SMS_MESSAGING_H_

#include "neul_error_types.h"
#include <stdlib.h>
#include "irmalloc.h"
#include <string.h>
#include <stdio.h>
#include "platform_definitions.h"

#define NEUL_SMS_MAX_SMC_ADDRESS_LENGTH     20
#define NEUL_SMS_MIN_SMC_ADDRESS_LENGTH     1
#define NEUL_SMS_MAX_TPDU_LEN               232

/** @defgroup libNEUL_SMS Hi21XX libNEUL SMS Messaging
 * Hi21XX libNeul SMS Messaging API
 * @ingroup LIBNEUL
 * @{
 * */


typedef enum
{
    NEUL_SMS_DR_OK       = 0,  //!< Send RP-ACK  */
    NEUL_SMS_DR_ERROR    = 1   //!< Send RP-ERROR */
} NEUL_SMS_RECEIVE_PDU_RES_TYPE;


typedef enum
{
    NEUL_SMS_MORE_MESSAGE_DISABLE                = 0,
    NEUL_SMS_MORE_MESSAGE_ENABLE_UNTIL_TIMEOUT   = 1,
    NEUL_SMS_MORE_MESSAGE_ENABLE                 = 2
} NEUL_SMS_CMMS_TYPE;

/**
 * @brief Indication of receiving MT short message callback
 * @param pdu_length -length of received MT short message
 * @param pdu - received MT short message
 */
typedef void (*neul_receive_short_message)(uint8 alpha, uint16 pdu_length, const uint8 *pdu);

/**
 * @brief callback for CMGS result
 * @param
 */
typedef void (*neul_send_msg_reuslt_callback)(uint8 result, uint8 mr, uint16 ackpdu_len, uint8 * ackpdu);

/**
 * @brief callback for CMGC result
 * @param
 */
typedef void (*neul_send_cmd_result_callback)(uint8 result, uint8 mr, uint16 ackpdu_len, uint8 * ackpdu);

/**
 * @brief set short message service type
 * @param
 * @param
 * @param
 * @result error or sucess
 */
NEUL_RET set_short_message_service_type(uint16 service ,uint8 * mt, uint8 * mo, uint8 * bm);

/**
 * @brief read short message service type
 * @param
 * @param
 * @param
 * @result error or sucess
 */
NEUL_RET read_short_message_service_type(uint8 * service , uint8 * mt, uint8 * mo, uint8 * bm);

/**
 * @brief set CMMS mode
 * @param CMMS mode
 * @result error or sucess
 */
NEUL_RET set_more_message_to_send(uint8 mode);

/**
 * @brief read CMMS mode
 * @param CMMS mode
 * @result error or sucess
 */
NEUL_RET read_more_message_to_send(uint8 * mode);

/**
 * @brief set short message service address
 * @param
 * @param
 * @param
 * @result error or sucess
 */
 NEUL_RET set_short_message_service_address(uint8 type, uint8 len, uint8 *ser_addr);

/**
 * @brief send short message to protocol core
 * @param sms_len:the setting length
 * @param pdu_length: the length for pdu
 * @param pdu: message content
 * @param callback: the callback function
 * @result error or sucess
 */
NEUL_RET send_short_message(uint8 sms_len, uint16 pdu_length, uint8 *pdu, neul_send_msg_reuslt_callback callback);

/**
 * @brief send command to protocol core
 * @param sms_len:the setting length
 * @param pdu_length: the length for pdu
 * @param pdu: message content
 * @param callback: the callback function
 * @result error or sucess
 */
NEUL_RET send_command(uint8 sms_len, uint16 pdu_length, uint8 *pdu, neul_send_cmd_result_callback callback);

/**
 * @brief set new msg ack
 * @param
 * @param
 * @param
 * @result error or sucess
 */
 NEUL_RET set_new_msg_ack(NEUL_SMS_RECEIVE_PDU_RES_TYPE report_type, uint8 sms_len, uint8 *pdu);

/**
 * @brief get cnma acknowledgement expected
 * @param
 * @param
 * @param
 * @result error or sucess
 */
NEUL_RET get_cnma_acknowledgement_expected(void);


/**
 * @brief read short message service address
 * @param
 * @param
 * @param
 * @result error or sucess
 */
 NEUL_RET read_short_message_service_address(uint8 *type, uint16 max_length, uint16 *length, uint8 * ser_addr);

/**
 * @brief Sets a callback that will be triggered when receive MT short message
 * @param callback The function to call with pdu
 */
NEUL_RET set_sms_pdu_callback(neul_receive_short_message callback);

/** @} end of group libNEUL_SMS */

#endif /* LIB_NEUL_SMS_MESSAGING_H_ */
