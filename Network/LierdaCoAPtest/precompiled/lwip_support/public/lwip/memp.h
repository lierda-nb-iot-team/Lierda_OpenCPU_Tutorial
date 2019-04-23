/******************************************************************************
 * @brief    lwip memp compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LWIP_SUPPORT_MEMP_H
#define LWIP_SUPPORT_MEMP_H

#include "lwip/opt.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

typedef enum {
    MEMP_PBUF,
    MEMP_POOL,
    MEMP_MAX
} memp_t;

struct memp_desc {
    u16_t size;
};

#define MEMP_ALIGN_SIZE(x)  (LWIP_MEM_ALIGN_SIZE(x))

#define LWIP_MEMPOOL_PROTOTYPE(name) extern const struct memp_desc memp_ ## name

#define LWIP_MEMPOOL_DECLARE(name, num, size, desc) \
    const struct memp_desc memp_ ## name = { \
      LWIP_MEM_ALIGN_SIZE(size) \
};

#define LWIP_MEMPOOL_INIT(name)    memp_init_pool(&memp_ ## name)

#define LWIP_MEMPOOL_ALLOC(name)   memp_malloc_pool(&memp_ ## name)

#define LWIP_MEMPOOL_FREE(name, x) memp_free_pool(&memp_ ## name, (x))

/** initialise a memory pool
 * @param memory pool descriptor
 */
void memp_init_pool(const struct memp_desc *desc);

/** allocate a memory pool
 * @param memory pool descriptor
 */
void *memp_malloc_pool(const struct memp_desc *desc);

/** free a memory pool
 * @param memory pool descriptor
 * @param address to free
 */
void  memp_free_pool(const struct memp_desc* desc, void *mem);

/** memp malloc
 * @param size to alloc
 */
#define memp_malloc(size)     irzalloc((uint32) size)

/** memp free
 * @param type to free
 * @param address to free
 */
#define memp_free(type, mem)  irfree(mem)

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_MEMP_H */

