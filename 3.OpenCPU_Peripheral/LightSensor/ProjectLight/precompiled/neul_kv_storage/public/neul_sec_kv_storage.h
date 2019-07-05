/******************************************************************************
 * @brief    SECURITY CORE kv storage api
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef SRC_LIB_NEUL_SEC_KV_STORAGE_H_
#define SRC_LIB_NEUL_SEC_KV_STORAGE_H_

#include "neul_error_types.h"
#include "kv_storage.h"

/**
 * Used to allow the security core to add another cores cache to the iflash task
 * @param core The core
 * @return KV_STORAGE_RET_OK if the cache was added, a KV error otherwise
 */
uint8 neul_lib_kv_storage_queue_cache_for_write(CORES core);

NEUL_RET kv_storage_ret_to_neul_ret( KV_STORAGE_RET kv_ret);

#endif /* SRC_LIB_NEUL_SEC_KV_STORAGE_H_ */
