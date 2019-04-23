/******************************************************************************
 * @brief    NETWORK CONFIG Interface.
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LIB_NEUL_NETWORK_MANAGEMENT_H_
#define LIB_NEUL_NETWORK_MANAGEMENT_H_

#include "neulfw.h"
#include "neul_error_types.h"

/** @addtogroup libNEUL_SOCKET
 * @{
 * */

typedef enum {
    NETWORK_CONFIG_SILENT = 0
} NETWORK_CONFIG;

/**
 * NETWORK_CONFIG_SILENT status.
 */
typedef enum {
   NETWORK_CONFIG_SILENT_MODE_OFF = 0,
   NETWORK_CONFIG_SILENT_MODE_ON = 1
} NETWORK_CONFIG_SILENT_MODE;

/**
 * Get the NETWORK_CONFIG_SILENT status from kvalue, default value is NETWORK_CONFIG_SILENT_MODE_ON if get kvalue failed.
 * @return None
 */
void network_config_init(void);

/**
 * Set network config to protocol core
 * @param  config   network config option
 * @param  value    the value of network config to set
 * @return NEUL_RET_OK if success
           NEUL_RET_ERROR_RPC if the RPC busy
           NEUL_RET_ERROR_IN_PARAMETERS if the config illegal
 */
NEUL_RET set_network_config(uint16 config, uint16 value);

/** @} end of group libNEUL_SOCKET */

#endif /* LIB_NEUL_NETWORK_MANAGEMENT_H_ */
