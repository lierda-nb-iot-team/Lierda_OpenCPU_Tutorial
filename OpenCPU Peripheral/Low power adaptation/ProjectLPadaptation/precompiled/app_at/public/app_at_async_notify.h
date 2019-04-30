/******************************************************************************
 * @brief    Async output at message with check of at status.
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef APP_AT_ASYNC_NOTIFY_H_
#define APP_AT_ASYNC_NOTIFY_H_
#include "app_at.h"

/** @addtogroup libNEUL_APP_AT_INT
 * @{
 * */

/**
 * @brief Adds a message string to a list. If not in AT process status, just output the message, or insert it to the tail of list.
 * @param message The message string to print later.
 * @param flag The attribute of message.
 * @param offset_to_convert The start offset in message should be convert to hexstring.
 * @param length_to_convert The length in message should be convert to hexstring.
 */
void delayed_async_print(const char *message, AT_FLAG flag, uint16 offset_to_convert, uint16 length_to_convert);

/**
 * @brief output all the message string in the list.
 * @param message The message string to print later.
 */
void delayed_async_output_list(void);

/**
 * @brief async notify init.
 */
void app_at_async_notify_init(void);

/** @} end of group libNEUL_APP_AT_INT */

#endif
