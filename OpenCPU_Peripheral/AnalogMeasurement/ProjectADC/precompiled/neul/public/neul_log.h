/******************************************************************************
 * @brief       NEUL LOG FOR THE Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_LOG_H_
#define LIB_NEUL_LOG_H_

#include "neul_error_types.h"
#include "platform_definitions.h"
#include "neul_log_types.h"

/** @defgroup libNEUL_LOGAPI Hi21XX libNEUL Logging
 * Hi21XX libNeul Logging API
 * @ingroup LIBNEUL
 * @{
 * */

/**
 * Set Log Level For Print
 * @param core  pointer to which core to set, security protocol ...
 * @param level pointer to which level to set
 * @return NEUL_RET_OK or error code
 */
NEUL_RET neul_log_set_log_level(CORES core, NEUL_LOG_LEVEL level);

/**
 * Get Log Level
 * @param core  set the core ,which can be security protocol ...
 * @param level get the level
 * @return NEUL_RET_OK or error code
 */
NEUL_RET neul_log_get_log_level(CORES core, NEUL_LOG_LEVEL* level);

/**
 * Get log behaviour, restricted or not.
 * @param log_behaviour_config save the log behaviour config
 * @return NEUL_RET_OK or error code
 */
NEUL_RET  neul_log_get_log_behaviour_restricted(NEUL_LOG_BEHAVIOUR_CONFIG* log_behaviour_config);
/** @} end of group libNEUL_LOGAPI */

#endif /* LIB_NEUL_LOG_H_ */
