/******************************************************************************
 * @brief    NEUL KEY VALUE STORAGE INTERFACE
 * Copyright (c) 2018 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_KV_STORAGE_H_
#define LIB_NEUL_KV_STORAGE_H_

#include "neulfw.h"
#include "neul_error_types.h"
#include "kv_storage_common.h"
#include "core.h"
#if (CORE == SECURITY)
#include "kv_storage.h"
#endif

/** @defgroup libNEUL_PERSISTENT Hi21XX libNEUL Persistent Storage
 * Hi21XX libNeul Persistent Storage API
 * @ingroup LIBNEUL
 * @{
 * */


/**
 * Store a key value pair
 * @param key key to associate kvalue to
 * @param kvalue value to store
 * @param kvalue_length length in bytes of kvalue
 * @return NEUL_RET_OK or an error code
 * @note This key could be deleted by using neul_kv_erase_key, for permanent keys use neul_kv_set_permanent
 */
NEUL_RET neul_kv_set(neul_kv_key key, const uint8 *kvalue, uint16 kvalue_length);

#if CORE == SECURITY
/**
 * Store an asset store key value pair
 * @param key key to associate kvalue to
 * @param kvalue value to store
 * @param kvalue_length length in bytes of kvalue
 * @return NEUL_RET_OK or an error code
 * @note This key could be deleted by using neul_kv_erase_key, for permanent keys use neul_kv_set_permanent
 */
NEUL_RET neul_kv_asset_set(neul_kv_key key, const uint8 *kvalue, uint16 kvalue_length);
#endif /* CORE == SECURITY*/

/**
 * Store a key value pair
 * @param key key to associate kvalue to
 * @param kvalue value to store
 * @param kvalue_length length in bytes of kvalue
 * @param permanent flag
 * @return NEUL_RET_OK or an error code
 * @note This key could be deleted by using neul_kv_erase_key
 */
NEUL_RET neul_kv_set_with_attributes(neul_kv_key key, const uint8 *kvalue, uint16 kvalue_length, bool permanent);

/**
 * Migrate a key value pair to permanent flash storage
 * @param key key to associate make permanent
 * @return NEUL_RET_OK or an error code
 * @note This key can not then be deleted or overwitten, and there is no mechanism to undo this
 */
NEUL_RET neul_kv_set_permanent(neul_kv_key key);

/**
 * Get a value associated with a specific key
 * @param key key of the value to get
 * @param kvalue_max_length maximum length (in bytes) allowed to copy in the kvalue buffer if the key is found
 * @param kvalue_length length of kvalue in bytes
 * @param kvalue value associated with the provided key and group
 * @return NEUL_RET_OK or an error code
 */
NEUL_RET neul_kv_get(neul_kv_key key, uint16 kvalue_max_length, uint16 *kvalue_length, uint8 *kvalue);

/**
 * Check if a vlaue has been stored
 * @param key key of the value to check
 * @param kvalue_length length of kvalue in bytes
 * @param kvalue value associated with the provided key and group
 * @return NEUL_RET_OK or an error code
 */
NEUL_RET neul_kv_stored(neul_kv_key key, uint16 kvalue_length, const uint8 *kvalue);

/**
 * Erase an stored value given its key and group
 * @param key key of the key to erase
 * @return NEUL_RET_OK or an error code
 */
NEUL_RET neul_kv_erase_key(neul_kv_key key);

/**
 * Erase all keys stored.
 * @return NEUL_RET_OK or an error code
 * @note This function deletes all keys stored by using neul_kv_set. keys stored by using neul_kv_set_permanent can not be deleted.
 */
NEUL_RET neul_kv_erase_all(void);

/**
 * Protect writing cache from multiple threads with semaphore.
 */
void neul_kv_init(void);

/**
 * register cache to allow flusing on reboot
 */
void neul_kv_cache_register(void);


/** @} end of group libNEUL_PERSISTENT */

#endif /* LIB_NEUL_KV_STORAGE_H_ */
