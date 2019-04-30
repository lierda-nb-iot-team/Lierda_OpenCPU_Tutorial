/* coap_io.h -- Default network I/O functions for libcoap
 *
 * Copyright (C) 2012--2013 Olaf Bergmann <bergmann@tzi.cog>
 *
 * This file is part of the CoAP library libcoap. Please see
 * README for terms of use.
 */

#ifndef _LWM2M_COAP_IO_H_
#define _LWM2M_COAP_IO_H_

//#include "internals.h"
//#include "coap_sec.h"
#include "coap_io.h"

#ifdef  HAVE_ASSERT_H
#include <assert.h>
#else
#ifndef assert
#warning "assertions are disabled"
#define assert(x)
#endif
#endif

#ifdef HAVE_SYS_TYPES_H
//# include <sys/types.h>
#endif

#include "address.h"

#ifndef min
#define min(a,b) ((a) < (b)? (a) : (b))
#endif /* min */

/* Bitmap for set options */
enum { COAP_OPTION_MAP_SIZE = sizeof(unsigned char) * 8};

#define COAP_SET_OPTION(packet, opt) ((packet)->options[opt / COAP_OPTION_MAP_SIZE] |= 1 << (opt % COAP_OPTION_MAP_SIZE))

#define COAP_CHECK_OPTION(packet, opt) ((packet)->options[opt / COAP_OPTION_MAP_SIZE] & (1 << (opt % COAP_OPTION_MAP_SIZE)))

#ifndef COAP_REST_MAX_CHUNK_SIZE
#define COAP_REST_MAX_CHUNK_SIZE    1024
#endif


#ifndef COAP_UPLOAD_LOG_SIZE
#define COAP_UPLOAD_LOG_SIZE    256
#endif
/*
 * Conservative size limit, ad not all options have to be set at the same time.
 */
#ifndef COAP_MAX_HEADER_SIZE
/*                              Hdr CoT Age Tag         Obs ToK         Blo strings */
#define COAP_MAX_HEADER_SIZE (4 + 3 + 5 + 1 + COAP_MAX_ETAG_LEN + 3 + 1 + COAP_MAX_TOKEN_LEN + 4 + 30) /* 70 */
#endif /* COAP_MAX_HEADER_SIZE */

#define NO_ERROR 0

typedef struct _lwm2m_coap_multi_option_t
{
    struct _lwm2m_coap_multi_option_t * next;
    unsigned char len;
    unsigned char * data;
} lwm2m_coap_multi_option_t;

typedef struct
{
    unsigned short payload_len;
    unsigned char * payload;
} lwm2m_coap_payload_t;

void lwm2m_coap_add_multi_option(lwm2m_coap_multi_option_t ** dst, unsigned char * option, size_t option_len);
void lwm2m_coap_get_message_multi_option_as_string(char * output, lwm2m_coap_multi_option_t * option);
int lwm2m_coap_get_block_message(coap_opt_t *option,unsigned int *num, unsigned char *more, unsigned short *size, unsigned int *offset);
void lwm2m_coap_free_multi_option(lwm2m_coap_multi_option_t *dst);
int lwm2m_coap_set_block(coap_pdu_t* pdu, unsigned short type,unsigned int num, unsigned char more, unsigned short size);
int lwm2m_coap_set_multi_option(coap_pdu_t *pdu, unsigned short type, unsigned char *strInput);
void lwm2m_coap_get_multi_option(coap_pdu_t *pdu,unsigned short type,lwm2m_coap_multi_option_t **dst );
int lwm2m_coap_set_uri_path_segment(void *pdu, const char *segment);
void lwm2m_coap_pdu_init(coap_pdu_t * response_pdu, unsigned char type, unsigned char code, unsigned short mid);
#endif /* _LWM2M_COAP_IO_H_ */
