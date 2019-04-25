/******************************************************************************
 * @brief    FILTER SEND DATA INTERFACE
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef    _APP_AT_FILTER_H_
#define    _APP_AT_FILTER_H_

#include "neulfw.h"

typedef bool (*at_filter_send_callback)(void);

/** Set filter send data callback
 * @param callback filter func. NULL means no callback
 */
void at_set_filter_send_callback(at_filter_send_callback callback);

/** Filter send data
 * @return true can not send data, false can send
 */
bool at_trigger_filter_send(void);

#endif
