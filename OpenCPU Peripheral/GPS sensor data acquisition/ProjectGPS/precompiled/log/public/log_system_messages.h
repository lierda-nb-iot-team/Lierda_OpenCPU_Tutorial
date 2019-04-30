/******************************************************************************
 * @brief    system log messages
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LOG_SYSTEM_MESSAGES_H_
#define LOG_SYSTEM_MESSAGES_H_

#include "log_common.h"

/** @addtogroup libNEUL_LOG
 * @{
 * */

typedef struct
{
    uint32  counter; // !< Number of missed messages.
} log_system_missed_message_t;

typedef enum
{
    LOG_SYSTEM_MISSED_MESSAGE_BUFFER,   // missed messages due to shared memeory being full
} log_system_message_id_t;

typedef enum
{
    LOG_SYSTEM_MODULE_LOG,   // logging
} log_system_module_t;

/** @} end of group libNEUL_LOG */

#endif // LOG_SYSTEM_MESSAGES_H_
