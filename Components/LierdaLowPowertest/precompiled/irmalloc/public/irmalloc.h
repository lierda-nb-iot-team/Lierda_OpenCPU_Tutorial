/******************************************************************************
 * @brief    Internal RAM memory allocator interface
 * Copyright (c) 2011 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef IRMALLOC_H_
#define IRMALLOC_H_

#include "neulfw.h"

/** @defgroup libNEUL_MALLOC Hi21XX Memory Allocator
 * Hi21XX Memory Allocator
 * @ingroup HI21XX_MODULES
 * @{
 * */

#ifdef __cplusplus
extern "C" {
#endif


// Turning this on allocates an extra uint32 at the beginning of each malloc block and uses it to
// store the caller's address.
//
// There's a Python script, malloc_trace.py, which can analyse a dump of the malloc arena with
// this option on, and tell you where the memory went. ONLY do this when building NBIOT protocol stack.
#if defined (NBIOT_SCONS_DEFINE)
//#define DEBUG_MALLOC_TRACE_OWNER
#endif

/**Initialise the internal memory with the default pool passed in via the linker*/
extern void irmalloc_init_default(void);

/**
 * Initialise the internal memory with the given memory location
 * @param start Start of the pool
 * @param size Size of the pool
 */
extern void irmalloc_init(void *start, size_t size);

/**Add an additional memory pool to allocate from; the irmalloc implementation is not obliged to use this memory
 * @param start is the start memory address of the new pool
 * @param size is number of bytes in the new memory pool
 */
extern void irmalloc_new_pool(void *start, size_t size);

/**Allocate a block of memory from internal RAM
 * @param size size of the block to allocate
 * @return pointer to allocated memory, or NULL
 */
//lint -function(malloc,irmalloc)   irmalloc has the same semantics as malloc.
extern void *irmalloc(size_t size);

/**Allocate a block of memory from internal RAM or panic on failure
 * @param size size of the block to allocate
 * @return pointer to allocated memory
 */
//lint -function(malloc(0),irmalloc_panicking)   irmalloc_panicking has the same semantics as malloc, but doesn't return NULL.
//lint -function(malloc(1),irmalloc_panicking)   irmalloc_panicking has the same semantics as malloc, but doesn't return NULL.
extern void *irmalloc_panicking(size_t size);

/**Allocate a block of memory from internal RAM, without using memory recovery in case of allocation failure
 * @param size size of the block to allocate
 * @return pointer to allocated memory, or NULL
 */
//lint -function(malloc,irmalloc_singleshot)   irmalloc_singleshot has the same semantics as malloc.
void *irmalloc_singleshot(size_t size);

/**Allocate a block of memory and zero it.
 * @param size size of the block to allocate
 * @return pointer to allocated memory, or NULL
 */
//lint -function(malloc,irzalloc)   irzalloc has the same semantics as malloc.
extern void *irzalloc(size_t size);

/**Allocate a block of memory and zero it.
 * @param size size of each block to allocate
 * @param number number of blocks to allocate
 * @return pointer to allocated memory, or NULL
 */
#define ircalloc(size, number) irzalloc((size) * (number))

/**Free a block of memory
 * @param buf
 */
//lint -function(free,irfree)   irfree has the same semantics as free.
extern void irfree(void * buf);

/**Duplicate the contents of a block of memory into irmalloc.
 * @param orig pointer to memory to duplicate
 * @param size size of the block to duplicate
 * @return pointer to block contain
 */
extern void *irmalloc_dup(const void *orig, size_t size);

/**Reallocate a block of memory*/
//lint -function(realloc,irrealloc)  irrealloc has the same semantics as realloc.
extern void *irrealloc(void *buf, size_t size);

/**Reallocate a block of memory or panic on failure*/
//lint -function(realloc(0),irrealloc_panicking)   irrealloc_panicking has the same semantics as realloc, but doesn't return NULL.
//lint -function(realloc(1),irrealloc_panicking)   irrealloc_panicking has the same semantics as realloc, but doesn't return NULL.
//lint -function(realloc(2),irrealloc_panicking)   irrealloc_panicking has the same semantics as realloc, but doesn't return NULL.
extern void *irrealloc_panicking(void *buf, size_t size);

/**Get some human readable statistics on the memory management state
 * @return the irmalloc'ed memory buffer containing a NULL terminated ASCII string of the human readbale stats; this memory must be irfree'd by the calling code
 * note The stats format is variable and is not guaranteed to be parsable.  NULL is returned if no memory is irmallocable
 */
extern char* irmalloc_get_human_readable_stats(void);

/**Get some macine readable statistics on the memory management state
 * @param current_allocated pointer to memory to hold current allocated size
 * @param total_free pointer to memory to hold current free pool size
 * @param max_free pointer to memory to hold maximum free block size
 * @param num_allocs pointer to memory to hold accumulated number of mallocs
 * @param num_frees pointer to memory to hold accumulated number of frees
 */
void irmalloc_get_machine_readable_stats(uint32 *current_allocated, uint32 *total_free, uint32 *max_free, uint32 *num_allocs, uint32 *num_frees);

#ifdef __cplusplus
}
#endif

/** @} end of group libNEUL_MALLOC */

#endif /* IRMALLOC_H_ */
