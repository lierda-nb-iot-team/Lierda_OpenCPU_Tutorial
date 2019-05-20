/******************************************************************************
 * @file     neul_nonip_messaging.h
 * @brief    nonip_messaging interface
 * Portions copyright (c) 2017 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_NONIP_MESSAGING_H_
#define LIB_NEUL_NONIP_MESSAGING_H_

#include "neulfw.h"
#include "neul_error_types.h"
#include "irmalloc.h"
#include <string.h>

/** @defgroup libNEUL_NONIP Hi21XX libNEUL Non-IP Messaging
 * Hi21XX libNeul Non-IP Messaging API
 * @ingroup LIBNEUL
 * @{
 * */

/**
 * @brief crtdcp callback
 * @param result new nonip message result
 */
typedef void (*neul_nonip_received_callback)(uint8 cid ,uint16 length, const uint8 *message);

/**
 * @brief non-ip data sent status callback
 * @param data_seq data sequence number
     composition: 0 - 7 bit  : sequence number.
                  8 - 16 bit : index (0xFF means non-ip cp only data sent result,0xEF means non-ip data via cp or up sent result)
 * @param status boolean indicating success or failure
 */
typedef void (*non_ip_sent_notify)(uint16 data_seq, bool status);

/**
 * @brief Sets a callback that will be triggered when new NonIP message via cp arrives
 * @param callback The callback function
 */
void nonip_set_cp_only_message_received_callback(neul_nonip_received_callback callback);

/**
 * @brief Sets a callback that will be triggered when new NonIP message arrives
 * @param callback The callback function
 */
void nonip_set_message_received_callback(neul_nonip_received_callback callback);

/**
 * @brief Send NonIP messages
 * @param cid Contxt ID
 * @param message Message to send
 * @param length Message length
 * @param flags Socket type
 * @return error or success
 */
NEUL_RET nonip_sendto(uint8 cid, const void *message, uint16 length, uint32 flags);

/**
 * set callbacks for non ip data sent
 * @param non-ip sent_notify_callback non-ip data sent result callback
 */
void set_non_ip_sent_callback(non_ip_sent_notify non_ip_sent_notify_callback);

/** @} end of group libNEUL_NONIP */
#endif /* LIB_NEUL_NONIP_MESSAGING_H_*/
