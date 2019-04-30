/*******************************************************************************
 *
 * Copyright (c) 2013, 2014 Intel Corporation and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * The Eclipse Distribution License is available at
 *    http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    David Navarro, Intel Corporation - initial API and implementation
 *    Fabien Fleutot - Please refer to git log
 *    Toby Jaffey - Please refer to git log
 *    Bosch Software Innovations GmbH - Please refer to git log
 *    Pascal Rieux - Please refer to git log
 *
 *******************************************************************************/
/*
 Copyright (c) 2013, 2014 Intel Corporation

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
     * Neither the name of Intel Corporation nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 THE POSSIBILITY OF SUCH DAMAGE.

 David Navarro <david.navarro@intel.com>

*/

#ifndef _LWM2M_INTERNALS_H_
#define _LWM2M_INTERNALS_H_

#include "../../coap/public/neul_coap1.h"
#include "liblwm2m.h"
#include "coap_io.h"
#include "lwm2m_coap_io.h"
#include "pdu.h"
#include "block.h"
#include "ota.h"
#include "lwm2mclient.h"
#ifdef LWM2M_WITH_LOGS
#define LOG(...) fprintf(stderr, __VA_ARGS__)
#else
#define LOG(...)
#endif

#define LWM2M_DEFAULT_LIFETIME  86400

#define AF_UNSPEC       0
//#define AF_INET         2
//#define AF_INET6        10
//#else /* LWIP_IPV6 */
//#define AF_INET6        AF_UNSPEC
//#endif /* LWIP_IPV6 */


#ifdef LWM2M_SUPPORT_JSON
#define REG_LWM2M_RESOURCE_TYPE     ">;rt=\"oma.lwm2m\";ct=1543,"   // Temporary value
#define REG_LWM2M_RESOURCE_TYPE_LEN 25
#else
#define REG_LWM2M_RESOURCE_TYPE     ">;rt=\"oma.lwm2m\","
#define REG_LWM2M_RESOURCE_TYPE_LEN 17
#endif

#define REG_ALT_PATH_LINK           "<%s"REG_LWM2M_RESOURCE_TYPE
#define REG_OBJECT_PATH             "<%s/%hu>,"
#define REG_OBJECT_INSTANCE_PATH    "<%s/%hu/%hu>,"

#define LWM2M_SERVER_PACKGE_PATH             "t/r"
/* URI path T mean TUP */
#define APP_COAP_RESOURCE_URI_T             "t"
/* URI path R mean register */
#define APP_COAP_RESOURCE_URI_R             "r"


#define URI_REGISTRATION_SEGMENT        "rd"
#define URI_REGISTRATION_SEGMENT_LEN    2
#define URI_BOOTSTRAP_SEGMENT           "bs"
#define URI_BOOTSTRAP_SEGMENT_LEN       2

#define QUERY_TEMPLATE      "ep="
#define QUERY_LENGTH        3       // strlen("ep=")
#define QUERY_SMS           "sms="
#define QUERY_SMS_LEN       4
#define QUERY_LIFETIME      "lt="
#define QUERY_LIFETIME_LEN  3
#define QUERY_VERSION       "lwm2m="
#define QUERY_VERSION_LEN   6
#define QUERY_BINDING       "b="
#define QUERY_BINDING_LEN   2
#define QUERY_DELIMITER     "&"
#define QUERY_STARTER       "?"
#define QUERY_NAME          "ep="
#define QUERY_VERSION_FULL      "lwm2m=1.0"
#define QUERY_VERSION_FULL_LEN  9

#define ATTR_MIN_PERIOD_STR      "pmin="
#define ATTR_MIN_PERIOD_LEN      5
#define ATTR_MAX_PERIOD_STR      "pmax="
#define ATTR_MAX_PERIOD_LEN      5
#define ATTR_GREATER_THAN_STR    "gt="
#define ATTR_GREATER_THAN_LEN    3
#define ATTR_LESS_THAN_STR       "lt="
#define ATTR_LESS_THAN_LEN       3
#define ATTR_STEP_STR            "stp="
#define ATTR_STEP_LEN            4
#define ATTR_STEP_STR_OLD        "step="
#define ATTR_STEP_LEN_OLD        5



#define LWM2M_URI_FLAG_DM           (uint8_t)0x00
#define LWM2M_URI_FLAG_DELETE_ALL   (uint8_t)0x10
#define LWM2M_URI_FLAG_REGISTRATION (uint8_t)0x20
#define LWM2M_URI_FLAG_BOOTSTRAP    (uint8_t)0x40

#define LWM2M_URI_MASK_TYPE (uint8_t)0x70
#define LWM2M_URI_MASK_ID   (uint8_t)0x07

#define LWM2M_DETACH_STATE              0
#define LWM2M_ATTACH_STATE              1

typedef enum
{
    LWM2M_BS_SEQ_MSG,
    LWM2M_FW_DL_MSG,
    LWM2M_FW_NOTIFY_MSG,
    LWM2M_FW_UPDATE_MSG,
    LWM2M_FW_END_MSG,
    LWM2M_FW_TIMEOUT_MSG,
    LWM2M_REG_REBOOT_MSG,
	LWM2M_REG_UPDATE_MSG,
    LWM2M_DEL_REG_TRANSACTION_MSG,
	#ifdef DTLS
	LWM2M_SEND_NON_BACKGROUND_DATA_SUCC,
	LWM2M_SEND_NON_BACKGROUND_DATA_FAIL,
	LWM2M_DTLS_TO_SERVER_REQ_MSG,  //11
    LWM2M_DTLS_TO_SERVER_RSP_MSG,
    LWM2M_DTLS_TO_CLIENT_REQ_MSG,
	#endif
    LWM2M_REMOTE_CONFIGURE_MSG,
    LWM2M_DETACH_MSG,
    LWM2M_ATTACH_MSG,
    LWM2M_RETRANS_MSG,
    LWM2M_START_DOWNLOAD_FW_MSG,
    LWM2M_REG_TIMEOUT_MSG,
}LWM2M_MSG_TYPE;

typedef struct transaction_req_param
{
    int type;
    int method;
    char *altPath;
    lwm2m_uri_t * uriP;
    uint16_t mID;
    uint8_t token_len;
    uint8_t * token;
    lwm2m_endpoint_type_t peerType;
    void * peerP;
    int accept;
} transaction_req_param_t;



typedef struct _lwm2m_block_transfer_t
{
    transaction_req_param_t param;
    uint8_t * buffer;
    size_t buffer_len;
    size_t buffer_offset;
    size_t buffer_remain;
    int block_seq;
} lwm2m_block_transfer_t;

typedef struct
{
    lwm2m_uri_t uri;
    lwm2m_result_callback_t callback;
    void * userData;
    lwm2m_block_transfer_t * block;
    lwm2m_context_t * contextP;
} dm_data_t;

typedef enum
{
    URI_DEPTH_OBJECT,
    URI_DEPTH_OBJECT_INSTANCE,
    URI_DEPTH_RESOURCE,
    URI_DEPTH_RESOURCE_INSTANCE
}uri_depth_t;

typedef struct
{
    uint8_t state;
    uint8_t supported;
    uint8_t result;
} firmware_data_t;

typedef struct _obs_list_
{
    struct _obs_list_ * next;
    lwm2m_observed_t * item;
} obs_list_t;


unsigned int
coap_encode_var_bytes(unsigned char *buf, unsigned int val);
unsigned int
coap_opt_block_num(const coap_opt_t *block_opt);


// defined in uri.c
int lwm2m_get_number(char * uriString, size_t uriLength);
lwm2m_uri_t * lwm2m_decode_uri(char * altPath, lwm2m_coap_multi_option_t *uriPath);
size_t prv_intToText(int64_t data,
                            uint8_t * string,
                            size_t length);

int prv_get_number(uint8_t * uriString, size_t uriLength);
/*init request block num value*/
int16_t lwm2m_request_blocknum_init(int16_t* block_num);
/*set request block num*/
int16_t lwm2m_set_request_blocknum(int16_t block_num);
/*set request more value*/
uint8_t lwm2m_set_request_more(uint8_t more_flag);


// defined in objects.c
//int print_memroy(void);
lwm2m_object_t * prv_find_object(lwm2m_context_t * contextP, uint16_t Id);
uint8_t object_checkReadable(lwm2m_context_t * contextP, lwm2m_uri_t * uriP);
uint8_t object_checkNumeric(lwm2m_context_t * contextP, lwm2m_uri_t * uriP);
unsigned int object_readData(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, int * sizeP, lwm2m_data_t ** dataP);
unsigned int object_read(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, lwm2m_media_type_t * formatP, uint8_t ** bufferP, size_t * lengthP);
unsigned int object_write(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, lwm2m_media_type_t format, lwm2m_block_option_t * opt, uint8_t * buffer, size_t length);
unsigned int object_execute(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, uint8_t * buffer, size_t length);
unsigned int object_delete(lwm2m_context_t * contextP, lwm2m_uri_t * uriP);
//unsigned int object_attrib(lwm2m_context_t* contextP, lwm2m_uri_t* uriP, lwm2m_coap_multi_option_t* uri_query, void* fromSessionH) ;
//uint8_t lwm2m_validateAndSetAttribute(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, lwm2m_coap_multi_option_t * uri_query, lwm2m_object_t * objectP, lwm2m_server_t * serverP);

bool object_isInstanceNew(lwm2m_context_t * contextP, uint16_t objectId, uint16_t instanceId);
int prv_getRegisterPayload(lwm2m_context_t * contextP, char * buffer, size_t length);

//void lwm2m_observer_check(lwm2m_context_t * contextP);
//lwm2m_attribute_data_t * lwm2m_findAttributes(lwm2m_server_t * serverP, lwm2m_uri_t * uriP);
//uint8_t lwm2m_evalAttributes(lwm2m_attribute_data_t* attrData, const char* resValBuf, int bufLen, uint32 tv, bool*notifyResult);

bool check_app_data_obj_uri(lwm2m_uri_t * uriP);
bool check_app_fota_obj_uri(lwm2m_uri_t * uriP);


// defined in transaction.c
lwm2m_transaction_t * transaction_new( transaction_req_param_t * param);

int transaction_send(lwm2m_context_t * contextP, lwm2m_transaction_t * transacP);
void transaction_free(lwm2m_transaction_t * transacP);
void transaction_remove(lwm2m_context_t * contextP, lwm2m_transaction_t * transacP);
bool transaction_handle_response(lwm2m_context_t * contextP, void * fromSessionH, coap_pdu_t* pdu, coap_pdu_t* response);
//bool transaction_handle_block_response(lwm2m_context_t * contextP, void * fromSessionH, lwm2m_coap_message_t * message, lwm2m_coap_message_t * response);

int transaction_list_timeout(lwm2m_context_t * contextP, uint32 * timeoutP);
void transaction_step(lwm2m_context_t * contextP, time_t currentTime, time_t * timeoutP);


// defined in management.c
lwm2m_media_type_t prv_convertMediaType(int type);
unsigned int handle_dm_request(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, lwm2m_server_t * serverP, coap_pdu_t * pdu, coap_pdu_t * response_pdu, lwm2m_coap_payload_t * payload);
// defined in observe.c
//unsigned int handle_observe_request(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, lwm2m_server_t * serverP, lwm2m_coap_message_t * message, lwm2m_coap_message_t * response);
unsigned int observe_handleRequest(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, lwm2m_server_t * serverP, int size, lwm2m_data_t * dataP, coap_pdu_t * pdu, coap_pdu_t * response_pdu);
void observe_cancel(lwm2m_context_t * contextP, uint16_t mid, void * fromSessionH);
unsigned int observe_setParameters(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, lwm2m_server_t * serverP, lwm2m_attributes_t * attrP);
void observe_step(lwm2m_context_t * contextP, time_t currentTime, time_t * timeoutP);
//bool handle_observe_notify(lwm2m_context_t * contextP, void * fromSessionH, lwm2m_coap_message_t * message, lwm2m_coap_message_t * response);
// defined in bootstrap.c
//void handle_bootstrap_response(lwm2m_context_t * context, lwm2m_coap_message_t * message, void * fromSessionH);
// defined in packet.c
int coap_message_send
(
	lwm2m_context_t * contextP,
	coap_pdu_t * pdu,
	const coap_endpoint_t * local_interface,
	const coap_address_t * dst
);

int coap_message_connection_send
(
	lwm2m_context_t * contextP,
	coap_pdu_t * pdu,
	connection_t * conn
);
//uint8_t handle_bootstrap_request(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, void * fromSessionH, lwm2m_coap_message_t * message, lwm2m_coap_message_t * response);
// defined in registration.c
//unsigned int handle_registration_request(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, void * fromSessionH, coap_packet_t * message, lwm2m_coap_message_t * response);

void cancel_observe(lwm2m_context_t * contextP, uint16_t mid, void * fromSessionH);

void registration_deregister(lwm2m_context_t * contextP, lwm2m_server_t * serverP);
void prv_freeClient(lwm2m_client_t * clientP);
void registration_update(lwm2m_context_t * contextP, uint32 currentTime, uint32 * timeoutP);
void observation_remove(lwm2m_client_t * clientP, lwm2m_observation_t * observationP);
void bootstrap_failed(lwm2m_context_t * context);
void reset_bootstrap_timer(lwm2m_context_t * context);
void update_bootstrap_state(lwm2m_context_t * contextP, uint32_t currentTime, uint32 * timeoutP);
void registration_step(lwm2m_context_t * contextP, time_t currentTime, time_t * timeoutP);
void send_register_msg(void);
void send_deregister_msg(void);
void send_update_register_msg(void);
void lwm2m_reregister(void);
void prv_transaction_reset_status(lwm2m_transaction_t * transaction);

// defined in utils.c
lwm2m_binding_t lwm2m_stringToBinding(uint8_t * buffer, size_t length);
int prv_isAltPathValid(const char * altPath);

#ifdef LWM2M_BOOTSTRAP
//lwm2m_server_t * utils_findBootstrapServer(lwm2m_context_t * contextP, void * fromSessionH);
#endif

/*lwm2m get update result from secrity**/
void lwm2m_get_update_result_sec(uint8_t *result);
void reset_all_update_state(void);
/*app task get update state*/
REST_STATE lwm2m_get_update_state(void);
bool lwm2m_filter_send_data(void);
void lwm2m_start_wait_server_req_timer(void);
void lwm2m_stop_wait_server_req_timer(void);
void lwm2m_start_notify_state_retry_timer(void);
void lwm2m_stop_notify_state_retry_timer(void);
void lwm2m_get_upload_result(uint8_t *result);
bool lwm2m_set_upload_result(uint8_t *result);
void at_mcriticaldata_stop_fota_download_proc(void);
void prv_handleRegistrationReply(lwm2m_transaction_t * transacP, void * pdu);
void prv_handleRegistrationUpdateReply(lwm2m_transaction_t * transacP, void * pdu);
void prv_handleDeregistrationReply(lwm2m_transaction_t * transacP, void * pdu);

#endif
