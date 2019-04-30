/******************************************************************************
 * @brief    nuel coap  Functions for Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef _NEUL_COAP_H_
#define _NEUL_COAP_H_

#include "neulfw.h"
#include "neul_ip_addr.h"

#include "log_common.h"

/* LOG MESSAGES */
#define APP_COAP_LOGGING_MODULE    2
#define APP_COAP_LOGGING_ID_STRING 0

#ifdef FOTA_DEBUG
#define APP_COAP_DBG(s, args...)            do{ \
        log_event_string(APP_COAP_LOGGING_MODULE, LOG_VERBOSITY_VERBOSE, LOG_FLAGS_NONE, APP_COAP_LOGGING_ID_STRING, s, ## args); \
    }while(0)
#else
#define APP_COAP_DBG(s, args...)
#endif

#define APP_COAP_INFO(s, args...)           do{ \
        log_event_string(APP_COAP_LOGGING_MODULE, LOG_VERBOSITY_NORMAL, LOG_FLAGS_NONE, APP_COAP_LOGGING_ID_STRING, s, ## args); \
    }while(0)

#define APP_COAP_WARN(s, args...)        do{ \
        log_event_string(APP_COAP_LOGGING_MODULE, LOG_VERBOSITY_WARNING, LOG_FLAGS_NONE, APP_COAP_LOGGING_ID_STRING, s, ## args); \
    }while(0)

#define APP_COAP_ERROR(s, args...)            do{ \
        log_event_string(APP_COAP_LOGGING_MODULE, LOG_VERBOSITY_ERROR, LOG_FLAGS_XLOG, APP_COAP_LOGGING_ID_STRING, s, ## args); \
    }while(0)

/**
 * NEUL CoAP result codes of functions
 */
typedef enum {
    NEUL_COAP_RET_OK = 0,
    NEUL_COAP_RET_ERROR,
    NEUL_COAP_RET_FLOW_CONTROL,
    NEUL_COAP_RET_SECURITY_ERROR,
    NEUL_COAP_RET_SET_BACKGROUND_ERROR,
}NEUL_COAP_RET;

/** Process coap received rst message callback
 * if it's called there is a rst message.
 */
typedef void (*neul_coap_rst_callback)(void);

/** Process coap received lwm2m message callback
 * if it's called there is a lwm2m message.
 */
typedef void (*neul_coap_lwm2m_callback)(unsigned short mid);

/** Mutex for Process coap received message callback
 */
typedef void (*neul_coap_mutex_callback)(void);

/**
 * Set CoAP rst message callback.
 * @param callback to process coap receive rst message. NULL means no callback
 */
void neul_coap_set_rst_callback(neul_coap_rst_callback callback);

/**
 * Trigger callback when CoAP received rst message.
 */
void neul_coap_trigger_rst_callback(void);

/**
 * Set CoAP lwm2m message callback.
 * @param callback to process coap receive lwm2m message. NULL means no callback
 */
void neul_coap_set_lwm2m_callback(neul_coap_lwm2m_callback callback);

/**
 * Trigger callback when CoAP sended a lwm2m message.
 */
void neul_coap_trigger_lwm2m_callback(unsigned short mid);

/**
 * Set CoAP mutex take callback.
 * @param callback to do mutex protect for process coap receive message. NULL means no callback
 */
void neul_coap_set_mutex_take_callback(neul_coap_mutex_callback callback);

/**
 * Set CoAP mutex give callback.
 * @param callback to do mutex protect for process coap receive message. NULL means no callback
 */
void neul_coap_set_mutex_give_callback(neul_coap_mutex_callback callback);

/**
 * Trigger mutex take callback when CoAP received message.
 */
void neul_coap_trigger_mutex_take_callback(void);

/**
 * Trigger mutex give callback when CoAP received message.
 */
void neul_coap_trigger_mutex_give_callback(void);

/**
 * Set CoAP port number.
 * @param port  the port number.
 */
void neul_coap_set_port(uint16 port);

/**
 * Read CoAP port number.
 * @return port number.
 */
uint16 neul_coap_read_port(void);

/**
 * Set ip of server
 * @param server_addr     The ip of  server that we get form application.
 * @return error or success
 */
NEUL_COAP_RET neul_coap_set_server_addr(ip_addr_t erver_addr);

/**
 * Read ip of server.
 * @param server_addr  The pointer to save server address.
 * @return error or success
 */
NEUL_COAP_RET neul_coap_read_server_addr(ip_addr_t *server_addr);

/**
 * Set the coap sendto result.
 * @param result the result will be set.
 */
void neul_coap_set_sendto_result(NEUL_COAP_RET result);

/**
 * Get the coap sendto result.
 * @return the result of coap sendto.
 */
NEUL_COAP_RET neul_coap_get_sendto_result(void);
#endif

