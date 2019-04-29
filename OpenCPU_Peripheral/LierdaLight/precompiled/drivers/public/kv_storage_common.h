/******************************************************************************
 * @brief    SECURITY KEY VALUE NON VOLATILE STORAGE MODULE INTERFACE
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef SRC_DRIVERS_NON_OS_KV_STORAGE_COMMON_H_
#define SRC_DRIVERS_NON_OS_KV_STORAGE_COMMON_H_

#include "neulfw.h"

#define  NEUL_KV_NO_DATA    0
#define  NEUL_KV_MAGIC 0xdeadcafe
#define  NEUL_KV_CLEAN true
#define  NEUL_KV_UNCLEAN   false

/** Key type */
typedef uint16 kv_storage_key;

/** KV store key header */
typedef struct
{
    uint8             crc;
    uint8             owner;
    uint16            length;
    uint8             type; // normal (0xFF) or permanent(0x00)
    uint8             unused;
    uint16            key;
} kv_storage_key_header; // make sizeof %4 ==0 a compile assert

/** Key type */
typedef uint16 neul_kv_key;

typedef enum
{
    KV_CACHE_A = 1,
    KV_CACHE_B = 2,
} KV_CACHE;

typedef enum
{
    KV_SECURITY_STATE_UNLOCKED = 0,
    KV_SECURITY_STATE_LOCKED =   1,
    KV_SECURITY_STATE_FLUSHED =  2,
    KV_SECURITY_STATE_ERROR   =  3,
} KV_SECURITY_STATE;

typedef struct cache_node
{
    struct cache_node   *next;
    uint8               *kvalue;
    neul_kv_key         key;
    uint16              kvalue_length;
    bool                erase;
    bool                permanent;
} kv_cache_node_t; //lint !e959: This is a private structure, the alignment of it is irrelevant.

typedef struct kv_cache_node_root_struct
{
    kv_cache_node_t *kv_cache;           // Pointer to a node in the cache
    uint32           kv_magic;           // set to NEUL_KV_MAGIC to indicate a KV cache
    volatile uint32  kv_security_locked; // Set by the security core if it is in the process of writing this cache - it is now read only!
    volatile bool    kv_clean;           // no operation in progress
} kv_cache_node_root;

typedef struct kv_cache_root_struct
{
    uint32                kv_magic;           // set to NEUL_KV_MAGIC to indicate a KV cache
    KV_CACHE              primary;           // Defines which caches is primary
    kv_cache_node_root    *kv_cache_a;        // Cache A
    kv_cache_node_root    *kv_cache_b;        // Cache B
} kv_cache_root;

#endif /* SRC_DRIVERS_NON_OS_KV_STORAGE_COMMON_H_ */
