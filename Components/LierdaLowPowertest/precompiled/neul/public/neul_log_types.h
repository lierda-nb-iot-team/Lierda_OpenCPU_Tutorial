/******************************************************************************
 * @brief       NEUL LOG TYPES FOR THE Hi21XX
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
 ******************************************************************************/

#ifndef LIB_NEUL_LOG_TYPES_H_
#define LIB_NEUL_LOG_TYPES_H_

#include "neul_error_types.h"
#include "neul_log_etypes.h"

/** @addtogroup libNEUL_LOGAPI
 * @{
 * */


 typedef enum
{
    NEUL_LOG_BEHAVIOUR_CONFIG_UNRESTRICTED,
    NEUL_LOG_BEHAVIOUR_CONFIG_RESTRICTED,
    NEUL_LOG_BEHAVIOUR_CONFIG_MAX,
} NEUL_LOG_BEHAVIOUR_CONFIG;


/* string type for compatibility */
#define NEUL_LOG_TYPE_STRING    0

#endif /* LIB_NEUL_LOG_TYPES_H_ */
