/*******************************************************************************
 *
 * Copyright (c) 2014 Bosch Software Innovations GmbH, Germany.
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
 *    Bosch Software Innovations GmbH - Please refer to git log
 *
 *******************************************************************************/
/*
 * lwm2mclient.h
 *
 *  General functions of lwm2m test client.
 *
 *  Created on: 22.01.2015
 *  Author: Achim Kraus
 *  Copyright (c) 2015 Bosch Software Innovations GmbH, Germany. All rights reserved.
 */

#ifndef LWM2MCLIENT_H_
#define LWM2MCLIENT_H_

#include "liblwm2m.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "apps_lwm2m_keys.h"
#include "app_at_cmd_parse_ref.h"
#include "cmsis_os2.h"
#ifdef DTLS
#include "dtls.h"
#endif

extern int g_reboot;

/******* device declarations ************/
//#define PRV_MANUFACTURER      "Open Mobile Alliance"
//#define PRV_MODEL_NUMBER      "Lightweight M2M Client"
//#define PRV_SERIAL_NUMBER     "345000123"
//#define PRV_FIRMWARE_VERSION  "1.0"

#define PRV_POWER_SOURCE_1    1
#define PRV_POWER_SOURCE_2    5
#define PRV_POWER_VOLTAGE_1   3800
#define PRV_POWER_VOLTAGE_2   5000
#define PRV_POWER_CURRENT_1   125
#define PRV_POWER_CURRENT_2   900
#define PRV_BATTERY_LEVEL     100
#define PRV_MEMORY_FREE       15
#define PRV_ERROR_CODE        0
#define PRV_TIME_ZONE         "Europe/Berlin"
#define PRV_BINDING_MODE      "U"

#define PRV_OFFSET_MAXLEN   7 //+HH:MM\0 at max
#define PRV_TLV_BUFFER_SIZE 128

// Resource Id's:
#define RES_O_MANUFACTURER          0
#define RES_O_MODEL_NUMBER          1
#define RES_O_SERIAL_NUMBER         2
#define RES_O_FIRMWARE_VERSION      3
#define RES_M_REBOOT                4
#define RES_O_FACTORY_RESET         5
#define RES_O_AVL_POWER_SOURCES     6
#define RES_O_POWER_SOURCE_VOLTAGE  7
#define RES_O_POWER_SOURCE_CURRENT  8
#define RES_O_BATTERY_LEVEL         9
#define RES_O_MEMORY_FREE           10
#define RES_M_ERROR_CODE            11
#define RES_O_RESET_ERROR_CODE      12
#define RES_O_CURRENT_TIME          13
#define RES_O_UTC_OFFSET            14
#define RES_O_TIMEZONE              15
#define RES_M_BINDING_MODES         16
// since TS 20141126-C:
#define RES_O_DEVICE_TYPE           17
#define RES_O_HARDWARE_VERSION      18
#define RES_O_SOFTWARE_VERSION      19
#define RES_O_BATTERY_STATUS        20
#define RES_O_MEMORY_TOTAL          21


#define NO_ERROR 0
#define LOW_BATTERY_POWER 1
#define EXTERNAL_POWER_SUPPLY_OFF 2
#define GPS_MODULE_FAILURE 3
#define LOW_RECIEVED_SIGNAL_STRENGTH 4
#define OUT_OF_MEMORY 5
#define SMS_FAILURE 6
#define IP_CONNECTIVTY_FAILURE 7
#define PERIPHERAL_MALFUNCTION 8

#define LWM2M_LWIP_TIMER 2000 /* millisecond */
#define UPDATING_MCU    999
#define UPDATE_MCU_SUCC    101
#define UPDATE_MCU_CHECK_FAIL    106
#define UPDATE_MCU_FAIL    108

#define LWM2M_REG_UPDATE_WAIT_MIN_TIME   (15*60) /* second */
#define DELAY_OTA_UPDATE_OVER_TIME (30*1000)//ms
#define DELAY_GET_DTLS_SEMAPHORE_TIME (15*1000)//ms

#define LWM2M_BLOCK_SIZE    512
#define LWM2M_DEFAULT_BLOCK_SIZE    1024
typedef void (*deviceReboot)(void);
typedef struct
{
    uint8_t battery_level;
    int16   src_vol;
    deviceReboot reBoot;
} device_data_t;
typedef void (*LWM2M_SOCKET_CB)(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

typedef struct _security_instance_
{
    struct _security_instance_ * next;        // matches lwm2m_list_t::next
    uint16_t                     instanceId;  // matches lwm2m_list_t::id
    char *                       uri;
    bool                         isBootstrap;
    char *                       public_key;
    char *                       secret_key;    
    uint8_t                      security_mode;
    uint16_t                     shortID;
    uint32_t                     clientHoldOffTime;
} security_instance_t;

/******* Server declarations ************/

typedef struct _server_instance_
{
    struct _server_instance_ * next;   // matches lwm2m_list_t::next
    uint16_t    instanceId;            // matches lwm2m_list_t::id
    uint32_t    lifetime;
    uint32_t    defaultMinPeriod;
    uint32_t    defaultMaxPeriod;
    bool        storing;
    char        binding[4];
} server_instance_t;

/**               Configuration       START              ***/


//#ifndef LWM2M_OBJ_COUNT
//#define LWM2M_OBJ_COUNT 3
//#endif

//#define BOOTSTRAP_IP_ADDRESS 0xfe80,0x0,0x0,0x0,0x1012,0x12ff,0xfe12,0x1212

#define PRV_MANUFACTURER      "Open Mobile Alliance"

#define PRV_MODEL_NUMBER      "Lightweight M2M Client"

#define PRV_SERIAL_NUMBER     "345000123"

#define PRV_FIRMWARE_VERSION  "1.0"

/**               Configuration   END                  ***/


/* IP address*/
#define UIPINT16SZ 2
#define UIPIN6ADDRSZ 16
#define UIPINADDRSZ 4

typedef struct _lwm2m_client_context_t
{
  lwm2m_context_t *lwm2m_context;
  connection_t * connList;
  int addressFamily;
}lwm2m_client_context_t;

#define PRV_QUERY_BUFFER_LENGTH 150
#define PRV_PAYLOAD_BUFFER_LENGTH 256

#define REG_TYPE_REG          0
#define REG_TYPE_DE_REG       1
#define REG_TYPE_UPDATE_REG   2

#define BOOTSTRAP_START_NORMAL  0
#define BOOTSTRAP_START_LGU     1
#define DEFAULT_TIME_OUT 60

#define APP_MESSAGE_MAX_LENGTH  1024
#define DEFAULT_ClIENT_HOLD_OFF_TIME   (600)     

lwm2m_client_context_t g_lwm2m_client_context;
uint16 g_bootstrapstart;
extern uint32 g_clientholdofftimer;
extern uint8 g_bs_init_succ;

#define OTA_STATE_STR_DOWNLOADING       "FIRMWARE DOWNLOADING"
#define OTA_STATE_STR_DOWNLOAD_FAILED   "FIRMWARE DOWNLOAD FAILED"
#define OTA_STATE_STR_DOWNLOADED        "FIRMWARE DOWNLOADED"
#define OTA_STATE_STR_UPDATING          "FIRMWARE UPDATING"
#define OTA_STATE_STR_UPDATE_SUC        "FIRMWARE UPDATE SUCCESS"
#define OTA_STATE_STR_UPDATE_FAILED     "FIRMWARE UPDATE FAILED"
#define OTA_STATE_STR_UPDATE_OVER       "FIRMWARE UPDATE OVER"
typedef enum REG_FLAG
{
    LWM2M_REG_INIT = 0,
    LWM2M_AUTO_REG,
    LWM2M_USER_REG,
} REG_FLAG;
typedef enum RES_STATE
{
    STATE_IDLE,
    STATE_DOWNLOADING,
    STATE_DOWNLOADED,
    STATE_UPDATING,
    STATE_DOWNLOADING_WAIT_ACK,
    STATE_UPDATING_WAIT_ACK,
} REST_STATE;
typedef enum UPDATE_RESULT
{
    UPDATE_RESULT_INIT,
    UPDATE_RESULT_SUCC,                 //Success (Downloaded)
    UPDATE_RESULT_NOT_ENOUGH_STORAGE,   //Not enough storage for the new firmware package
    UPDATE_RESULT_OUT_OF_MEM,           //out of memory during downloading
    UPDATE_RESULT_LOST_CONNECT,         //connection lost during downloading
    UPDATE_RESULT_CRC_FAIL,             //check failure of new downloaded package
    UPDATE_RESULT_UNSUPPORTED_TYPE,     //Unsupported Package Type
    UPDATE_RESULT_INVALID_URI,          //Invalid URI
    UPDATE_RESULT_UPDATE_FAIL
} UPDATE_RESULT;

typedef enum
{
    LWM2M_TRY_TO_UPLOAD_RESULT,
    LWM2M_UPLOAD_RESULT_DEFAULT = 0xFF,
}LWM2M_UPLOAD_RESULT_STATE;

typedef enum
{
    LWM2M_STATE_DOWNLOADING,
    LWM2M_STATE_DOWNLOAD_FAILED,
    LWM2M_STATE_DOWNLOADED,
    LWM2M_STATE_UPDATING,
    LWM2M_STATE_UPDATE_SUC,
    LWM2M_STATE_UPDATE_FAILED,
    LWM2M_STATE_UPDATE_OVER
} LWM2M_STATE;

typedef enum
{
    LWM2M_REGISTRATION_COMPLETED, 
    LWM2M_DEREGISTRATION_COMPLETED,
    LWM2M_REGISTRATION_UPDATE_COMPLETED,
    LWM2M_1900_RESOURCE_OBSERVED,
    LWM2M_BOOTSTRAP_COMPLETED,
    FOTA_503_RESOURCE_OBSERVED,
    FOTA_DEVICE_RECEIVE_PUT_PACKAGE_URI,
    FOTA_DEVICE_RECEIVE_UPDATE,
	LWM2M_EVTIND_RESERVED,
    LWM2M_1900_RESOURCE_Cancel_OBSERVED,
	
	LWM2M_EVTIND_MAX,
} LWM2M_EVTIND;

typedef enum
{
    LWM2M_SERVER,
    BOOTSTRAP_SERVER,
}LWM2M_SERVER_TYPE;

typedef struct {
    unsigned int  length;    /* length of string */
    unsigned char data[8]; /* string data */
} str_token;
typedef struct
{
    uint8   state;
    uint8   result;
    str_token   token;
}fota_info_t;

typedef enum
{
    LWM2M_REMOTE_CONFIG_INIT = 0,
    LWM2M_REMOTE_NEW_CONFIG,
    LWM2M_REMOTE_OLD_CONFIG,
}LWM2M_REMOTE_CONFIG_TYPE;

bool ota_set_update_state(uint8_t *state);
bool ota_set_update_result(uint8_t *result);
bool ota_set_update_token(str_token *saveToken);
bool ota_get_update_state(uint8_t *state);
bool ota_get_update_result(uint8_t *result);

bool ota_get_update_token(str_token *update_token);

void lwm2m_wait_for_at_init(void);

/*lwm2m save udpate state*/
uint8_t lwm2m_update_state_write(uint8_t *state);

/*lwm2m save update result*/
uint8_t lwm2m_update_result_write(uint8_t *result);

/*lwm2m save token that observed*/
uint8_t lwm2m_update_token_write(str_token *saveToken);
/*


 * object_device.c
 */

//void lwm2m_client_single_init(uint16 bootstrapType); 
void client_lwm2m_main(coap_context_t * libcoap_context);
void lwm2m_main( void *unused_p );
void set_BootType(uint16 boot_type);
void set_reg_type(uint16 reg_type);
void start_boot_strap(uint16 start_type);
uint8_t lwm2m_update_state_write(uint8_t *state);
NEUL_RET lwm2m_get_bootstrap_clientofftimer(uint32 * clientholdofftime);
uint8 lwm2m_change_session(uint8 server_type, uint8 mode);
LWM2M_RET lwm2m_read_new_config(void);
LWM2M_RET lwm2m_read_bs_config(void);
LWM2M_RET lwm2m_set_new_remote_config_to_old_KV(void);
bool lwm2m_change_session_create_mutex(void);
LWM2M_RET lwm2m_change_session_take_mutex(void);
void lwm2m_change_session_give_mutex(void);
LWM2M_RET lwm2m_erase_new_remote_config(void);
LWM2M_RET lwm2m_set_remote_configing_flag(uint8 flag);
LWM2M_RET lwm2m_get_remote_configing_flag(uint8 *flag);
void lwm2m_remote_config_timeout(void);
#ifdef DTLS
void lwm2m_get_dtls_semaphore_timeout(void);
#endif

extern uint8 g_lwm2m_remote_config_flag;
#define LWM2M_REMOTE_CONFIGING_FLAG  (0xEA)
#define TIME_REMOTE_CONFIG_1_MIN (60000)  //unit ms
#define TIME_REMOTE_CONFIG_10_MIN (600000) //unit ms
#define TIME_WAIT_TO_EXECUTE_REMOTE_CONFIG (60000)
#define MAX_RETRY_TO_GET_MUTEX_TIMES (30)

typedef enum
{
    LWM2M_NEW_CONFIG = 0,
    LWM2M_OLD_CONFIG,
}LWM2M_CONFIG_TYPE;

typedef enum
{
    LWM2M_REG_TYPE_INIT = 0,
    LWM2M_SECURITY_REG_TYPE,
    LWM2M_NCDP_REG_TYPE,
}LWM2M_REG_TYPE;


/**
 * Creates the mailboxes needed for the app when used with freeRTOS
 */
void lwm2m_create_queue(void);

/**
 * Send the mailboxes to app queue from isr when used with freeRTOS
 */
void lwm2m_send_to_incoming_queue(uint32 state);
void lwm2m_get_server(lwm2m_client_context_t *userData, coap_address_t stRemoteAddr);
void lwm2m_close_connection(void * sessionH, void * userData);
void lwm2m_client_single_init(void);

void lwm2m_send_to_incoming_queue_from_ISR(uint32 state);


extern lwm2m_object_t * init_device_object( deviceReboot reBootPtr);
extern lwm2m_object_t * init_conn_monitor_object(void);
extern lwm2m_object_t * init_appdata_container_object(void);
extern lwm2m_object_t * init_appfota_object(void);
int add_security_object_instance(lwm2m_object_t * securityObj, uint16_t instanceId, int serverId, const char *serverUri, bool isBootstrap,uint32_t clientHoldOffTime);


extern uint8  lwm2m_get_update_result(uint32 *state);

int Set_ObjectDeviceCode_ErrorCode(int errorCode , lwm2m_object_t * objectP);

uint8_t device_change(lwm2m_data_t * dataArray, lwm2m_object_t * objectP);
//extern void display_device_object(lwm2m_object_t * objectP);
/*
 * object_firmware.c
 */
extern lwm2m_object_t * get_object_light_bulb(void);
extern lwm2m_object_t * init_firmware_object(void);

/*
 * object_location.c
 */
extern lwm2m_object_t * get_object_location(void);
extern void display_location_object(lwm2m_object_t * objectP);
/*
 * object_test.c
 */
#define TEST_OBJECT_ID 1024
extern lwm2m_object_t * get_test_object(void);
extern void display_test_object(lwm2m_object_t * objectP);
/*
 * object_server.c
 */
extern lwm2m_object_t * init_server_object(void);
extern void display_server_object(lwm2m_object_t * objectP);
extern void copy_server_object(lwm2m_object_t * objectDest, lwm2m_object_t * objectSrc);
int add_server_object_instance(lwm2m_object_t *serverObj, uint16_t instanceId, const char* binding,
                                   int lifetime, bool storing);

/*
 * object_connectivity_moni.c
 */
extern lwm2m_object_t * get_object_conn_m(void);
uint8_t connectivity_moni_change(lwm2m_data_t * dataArray, lwm2m_object_t * objectP);

/*
 * object_connectivity_stat.c
 */
extern lwm2m_object_t * get_object_conn_s(void);
extern void conn_s_updateTxStatistic(lwm2m_object_t * objectP, uint16_t txDataByte, bool smsBased);
extern void conn_s_updateRxStatistic(lwm2m_object_t * objectP, uint16_t rxDataByte, bool smsBased);

/*
 * object_access_control.c
 */
extern lwm2m_object_t* acc_ctrl_create_object(void);
extern bool  acc_ctrl_obj_add_inst (lwm2m_object_t* accCtrlObjP, uint16_t instId,
                 uint16_t acObjectId, uint16_t acObjInstId, uint16_t acOwner);
extern bool  acc_ctrl_oi_add_ac_val(lwm2m_object_t* accCtrlObjP, uint16_t instId,
                 uint16_t aclResId, uint16_t acValue);
/*
 * lwm2mclient.c
 */
extern void handle_value_changed(lwm2m_context_t* lwm2mH, lwm2m_uri_t* uri, const char * value, size_t valueLength);
/*
 * system_api.c
 */
extern void init_value_change(lwm2m_context_t * lwm2m);
extern void system_reboot(void);

/*
 * object_security.c
 */

extern char * get_server_uri(lwm2m_object_t * objectP, uint16_t secObjInstID);
extern char * get_public_key(lwm2m_object_t * objectP, uint16_t secObjInstID);
extern char * get_secret_key(lwm2m_object_t * objectP, uint16_t secObjInstID);
extern void lwm2m_getServerPara(lwm2m_object_t * objectP, lwm2m_server_t * server);
extern void display_security_object(lwm2m_object_t * objectP);
extern void copy_security_object(lwm2m_object_t * objectDest, lwm2m_object_t * objectSrc);
//extern int add_security_object_instance(lwm2m_object_t * securityObj, uint16_t instanceId, const char *serverUri, bool isBootstrap);

extern lwm2m_object_t * init_security_object(int serverId, const char *serverUri, bool isBootstrap, uint32_t clientHoldOffTime);


extern void lwm2m_set_server_from_nv(void);
extern LWM2M_RET bootstrap_start(lwm2m_context_t * contextP);
extern lwm2m_status_t bootstrap_getStatus(lwm2m_context_t * contextP);
extern unsigned int bootstrap_handleCommand(lwm2m_context_t * contextP, lwm2m_uri_t * uriP, lwm2m_server_t * serverP, coap_pdu_t * pdu, coap_pdu_t * response_pdu);
extern uint8_t registration_start(lwm2m_context_t * contextP);
extern lwm2m_status_t registration_getStatus(lwm2m_context_t * contextP);
extern int prv_updateRegistration(lwm2m_context_t * contextP, lwm2m_server_t * server, bool withObjects);
extern void prv_deregistertionSucc(lwm2m_server_t * targetP);
extern void lwm2m_add_reg_update_timer(void);

#ifdef LWM2M_BOOTSTRAP
extern int bootstrap_initiating_request(lwm2m_context_t * context, uint16_t type);
extern int handle_bootstrap_finish(lwm2m_context_t * context, void * fromSessionH);
#endif

uint8 lwm2m_notify_mcu_msg(LWM2M_STATE state);
void lwm2m_notify_evtind(LWM2M_EVTIND evtind);
void lwm2m_reset_state_and_timer(void);
void lwm2m_reset_before_reg(void);
bool lwm2m_check_server_and_reset(void);
void lwm2m_start_obappdata_timer(void);
void lwm2m_start_ob_appdata_timer_cb(void);
struct rcv_message_stats {
    uint32 buffered;       /* The number of datagram messages waiting to be read in the downstream buffer */
    uint32 received;       /* The total number of datagram messages received by the terminal since terminal boot  */
    uint32 dropped;        /* The number of datagram messages dropped by the terminal since terminal boot */
};

struct send_message_stats {
    uint32 pending;        /* The number of datagram messages waiting to be sent in the upstream buffer, if a registered and activated Layer 3 connection is not available. */
    uint32 sent;           /* The total number of uplink messages sent into the NB-IoT stack since terminal boot   */
    uint32 error;          /* The number of datagram messages that could not be sent by the terminal due to an error since terminal boot */
};

typedef struct{
    struct rcv_message_stats rcv_message_stats;
    struct send_message_stats send_message_stats;
}LWM2M_BUF_STATUS;

typedef enum
{
    LWM2M_GET_APPDATA_OK = 0,
    LWM2M_NO_MESSAGES,
}LWM2M_GET_APPDATA_RET;

typedef enum
{
    LWM2M_DATA_TYPE_NONE = 0,
    LWM2M_DATA_TYPE_NON,
    LWM2M_DATA_TYPE_CON,
} LWM2M_DATA_TYPE;

#define APP_AT_STR_NSMI                "+NSMI"
#define APP_AT_NSMI_MAX_LEN            16

#define APP_CONFIRMABLE_DATA_LEN  32
#define LWM2M_MAX_SENT_DATA_RSP_LEN 40

#define AT_CMD_DISABLE_LWM2M            0
#define AT_CMD_ENABLE_LWM2M             1

#define AT_CMD_DISABLE_LIFETIME            0
#define AT_CMD_ENABLE_LIFETIME             1

typedef void (*lwm2m_received_callback)(void);
typedef void (*lwm2m_sent_callback)(LWM2M_DATA_SENT_RESULT_TO_AIRFACE status, uint8 seq_num);

extern LWM2M_GET_APPDATA_RET lwm2m_get_appdata_from_queue(uint16 *length, uint8 *message);
extern void lwm2m_query_receive_appdata_statistics(struct rcv_message_stats *rcv_message_stats);
void ota_delay_notify_mcu_update_over(osTimerId_t osTimer);

int inet_pton6_iot(const char *src, unsigned char *dst);

#define RET_INVALID_TLV_LENGTH(_length, _subTlvP) \
if(0 == _length)\
{\
    lwm2m_data_free(2, _subTlvP);\
    return COAP_500_INTERNAL_SERVER_ERROR;\
}\



#define RET_INVALID_CHECK_MEM_FREE(_devObj, _devObjInst) \
if(_devObjInst == NULL)\
{\
    lwm2m_free(_devObj);\
    return NULL; \
}\

#define RET_INVALID_CHECK_MEM_FREE_USEDATA(_devObj, _devObjUser) \
if(_devObjUser == NULL)\
{\
    lwm2m_free(_devObj->instanceList);\
    lwm2m_free(_devObj);\
    return NULL; \
}\


#define RET_INVALID_CHECK_MEM_FREE_VOID(_instanceDest,_instance) \
if(_instance== NULL)\
{\
    lwm2m_free(_instanceDest);\
    return; \
}\


#define RET_INVALID_CHECK_VOID(_uri) \
if(_uri == NULL)\
{\
    PRINTF(" NULL pointer so return ");\
    return; \
}\



#define RET_INVALID_CHECK_MEM_FREE_RET(_uri,_Ret) \
if(_uri == NULL)\
{\
    lwm2m_free(_uri);\
    return _Ret; \
}\


#define RET_INVALID_CHECK_MEM_FREE_RET_CHECK(_Obj,_Ret) \
if(_Ret)\
{\
    lwm2m_free(_Obj);\
    return NULL; \
}\

#define RET_INVALID_CHECK(_subTlvP,_ErrorCode) \
if (_subTlvP == NULL)\
{\
    return _ErrorCode;\
}\

#define RET_INVALID_RET_CHECK(_retVal,_ErrorCode) \
if (_retVal != 0)\
{\
    PRINTF("LwM2M configuration has failed %d",_retVal);\
    return _ErrorCode;\
}\



#define RET_LENGTH_CHECK(_AttrLength,_MaxLength,_ErrorCode)\
{\
    if((_AttrLength) >= (_MaxLength))\
    {\
        return _ErrorCode;\
    }\
}\

#endif /* LWM2MCLIENT_H_ */

