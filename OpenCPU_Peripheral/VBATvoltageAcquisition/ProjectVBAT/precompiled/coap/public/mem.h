/*
 * mem.h -- CoAP memory handling
 *
 * Copyright (C) 2010-2011,2014-2015 Olaf Bergmann <bergmann@tzi.org>
 *
 * This file is part of the CoAP library libcoap. Please see README for terms
 * of use.
 */

#ifndef _COAP_MEM_H_
#define _COAP_MEM_H_

#include <stdlib.h>

#ifndef WITH_LWIP
/**
 * Initializes libcoap's memory management.
 * This function must be called once before coap_malloc() can be used on
 * constrained devices.
 */
void coap_memory_init(void);
#endif /* WITH_LWIP */

/**
 * Type specifiers for coap_malloc_type(). Memory objects can be typed to
 * facilitate arrays of type objects to be used instead of dynamic memory
 * management on constrained devices.
 */
typedef enum {
  COAP_STRING,
  COAP_ATTRIBUTE_NAME,
  COAP_ATTRIBUTE_VALUE,
  COAP_PACKET,
  COAP_NODE,
  COAP_CONTEXT,
  COAP_ENDPOINT,
  COAP_PDU,
  COAP_PDU_BUF,
  COAP_RESOURCE,
  COAP_RESOURCEATTR
} coap_memory_tag_t;

#define MEMP_COAP_CONTEXT       sizeof(coap_context_t)
#define MEMP_COAP_ENDPOINT      sizeof(coap_endpoint_t)
#define MEMP_COAP_PACKET        sizeof(coap_packet_t)
#define MEMP_COAP_NODE          sizeof(coap_queue_t)
#define MEMP_COAP_PDU           sizeof(coap_pdu_t)
#define MEMP_COAP_subscription  sizeof(coap_subscription_t)
#define MEMP_COAP_RESOURCE      sizeof(coap_resource_t)
#define MEMP_COAP_RESOURCEATTR  sizeof(coap_attr_t)

typedef enum {
  LWM2M_STRING,
  LWM2M_ATTRIBUTE_NAME,
  LWM2M_CLIENT_CONTEXT,
  LWM2M_CLIENT,
  LWM2M_OBJECT,
  LWM2M_URI,
  LWM2M_CONTEXT,
  LWM2M_MEMSSAGE,
  LWM2M_MEMSSAGE_BUF,
  LWM2M_RESOURCEATTR
}lwm2m_memory_tag_t;
#define MEMP_LWM2M_CLIENT_CONTEXT       sizeof(lwm2m_client_context_t)
#define MEMP_LWM2M_CONTEXT              sizeof(lwm2m_context_t)
#define MEMP_LWM2M_CLIENT               sizeof(lwm2m_client_t)
#define MEMP_LWM2M_OBJECT               sizeof(lwm2m_object_t)
#define MEMP_LWM2M_URI                  sizeof(lwm2m_uri_t)
#define MEMP_LWM2M_MEMSSAGE             sizeof(lwm2m_coap_message_t)
#define MEMP_LWM2M_RESOURCEATTR         sizeof(lwm2m_attribute_data_t)
#ifndef WITH_LWIP

/**
 * Allocates a chunk of @p size bytes and returns a pointer to the newly
 * allocated memory. The @p type is used to select the appropriate storage
 * container on constrained devices. The storage allocated by coap_malloc_type()
 * must be released with coap_free_type().
 *
 * @param type The type of object to be stored.
 * @param size The number of bytes requested.
 * @return     A pointer to the allocated storage or @c NULL on error.
 */
void *coap_malloc_type(coap_memory_tag_t type, size_t size);

/**
 * Releases the memory that was allocated by coap_malloc_type(). The type tag @p
 * type must be the same that was used for allocating the object pointed to by
 * @p .
 *
 * @param type The type of the object to release.
 * @param p    A pointer to memory that was allocated by coap_malloc_type().
 */
void coap_free_type(coap_memory_tag_t type, void *p);

/**
 * Wrapper function to coap_malloc_type() for backwards compatibility.
 */
static inline void *coap_malloc(size_t size) {
  return coap_malloc_type(COAP_STRING, size);
}

/**
 * Wrapper function to coap_free_type() for backwards compatibility.
 */
static inline void coap_free(void *object) {
  coap_free_type(COAP_STRING, object);
}

#endif /* not WITH_LWIP */

#ifdef WITH_LWIP

#include <lwip/memp.h>
#include <lwip/debug.h>
/* no initialization needed with lwip (or, more precisely: lwip must be
 * completely initialized anyway by the time coap gets active)  */
static inline void coap_memory_init(void) {}

/* It would be nice to check that size equals the size given at the memp
 * declaration, but i currently don't see a standard way to check that without
 * sourcing the custom memp pools and becoming dependent of its syntax
 */
#define coap_malloc_type(type, size) memp_malloc(MEMP_ ## type)
#define coap_free_type(type, p) memp_free(MEMP_ ## type, p)

#define lwm2m_malloc_type(type, size) memp_malloc(MEMP_ ## type)
#define lwm2m_free_type(type, p) memp_free(MEMP_ ## type, (p))
/* Those are just here to make uri.c happy where string allocation has not been
 * made conditional.
 */
static inline void *coap_malloc(size_t size) {
  //LWIP_ASSERT("coap_malloc must not be used in lwIP", 0);
  return memp_malloc(size);
}

static inline void coap_free(void *pointer) {
  //LWIP_ASSERT("coap_free must not be used in lwIP", 0);
  memp_free(COAP_STRING, pointer);
}

#define lwm2m_malloc(size)  memp_malloc((size))
#define lwm2m_free(pointer) do { \
    memp_free(LWM2M_STRING, (pointer)); \
    pointer = NULL; \
}while(0)


static inline char* lwm2m_strdup(const char* str)
{
    size_t length = strlen(str);
    char* result = lwm2m_malloc(length +1);
    if(NULL == result)
    {
        return NULL;
    }
    memcpy(result, str, length);
    result[length] = 0;
    return result;
}
#endif /* WITH_LWIP */

#endif /* _COAP_MEM_H_ */
