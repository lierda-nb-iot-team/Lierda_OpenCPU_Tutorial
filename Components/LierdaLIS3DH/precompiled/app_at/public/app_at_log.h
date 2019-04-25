/******************************************************************************
 * @brief     AT Command Debug
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef _APP_AT_DEBUG_H_
#define _APP_AT_DEBUG_H_

#include "log_common.h"
#include "apps_system_sw_module_ids.h"

/** @addtogroup libNEUL_APP_AT_MOD_API
 * @{
 * */

#define APP_AT_VERBOSE(s, args...)            do{ \
        log_event_string(APPS_SW_MODULE_AT, LOG_VERBOSITY_VERBOSE, LOG_FLAGS_NONE, NEUL_LOG_TYPE_STRING, s, ## args); \
    }while(0)

#define APP_AT_NORMAL(s, args...)           do{ \
        log_event_string(APPS_SW_MODULE_AT, LOG_VERBOSITY_NORMAL,  LOG_FLAGS_NONE, NEUL_LOG_TYPE_STRING, s, ## args); \
    }while(0)

#define APP_AT_WARNING(s, args...)        do{ \
        log_event_string(APPS_SW_MODULE_AT, LOG_VERBOSITY_WARNING, LOG_FLAGS_NONE, NEUL_LOG_TYPE_STRING, s, ## args); \
    }while(0)

#define APP_AT_ERROR(s, args...)            do{ \
        log_event_string(APPS_SW_MODULE_AT, LOG_VERBOSITY_ERROR, LOG_FLAGS_XLOG, NEUL_LOG_TYPE_STRING, s, ## args); \
    }while(0)

/** @} end of group libNEUL_APP_AT_MOD_API */

#endif /*_APP_AT_DEBUG_H_ */
