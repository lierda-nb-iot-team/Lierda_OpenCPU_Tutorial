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
 *    Simon Bernard - Please refer to git log
 *    Toby Jaffey - Please refer to git log
 *    Julien Vermillard - Please refer to git log
 *    Bosch Software Innovations GmbH - Please refer to git log
 *    Pascal Rieux - Please refer to git log
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

#ifndef _LIBLWM2M_H_
#define _LIBLWM2M_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include <time.h>
#include <connection.h>
#include "app_at.h"
// for libcoap support
#include "pdu.h"
#include "net.h"
#include "lwm2m_coap_io.h"
#include "mem.h"
#include "reboot.h"
#include "app_at_send_data.h"
#include "cmsis_os2.h"

#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG
#include <stdio.h>

#ifndef PRINTF
#define PRINTF(...) printf(__VA_ARGS__)
#endif

#ifndef SNPRINTF
#define SNPRINTF(...) snprintf(__VA_ARGS__)
#endif

#ifndef PRINT6ADDR
#define PRINT6ADDR(addr) PRINTF("[%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x]", ((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15])
#endif

#ifndef PRINTLLADDR
#define PRINTLLADDR(lladdr) PRINTF("[%02x:%02x:%02x:%02x:%02x:%02x]", (lladdr)->addr[0], (lladdr)->addr[1], (lladdr)->addr[2], (lladdr)->addr[3], (lladdr)->addr[4], (lladdr)->addr[5])
#endif
#else

#ifndef PRINTF
#define PRINTF(...)
#endif

#ifndef SNPRINTF
#define SNPRINTF(...)
#endif

#ifndef PRINT6ADDR
#define PRINT6ADDR(addr)
#endif

#ifndef PRINTLLADDR
#define PRINTLLADDR(addr)
#endif

#endif

// This function must return the number of seconds elapsed since origin.
// The origin (Epoch, system boot, etc...) does not matter as this
// function is used only to determine the elapsed time since the last
// call to it.
// In case of error, this must return a negative value.
// Per POSIX specifications, time_t is a signed integer.
// An implementation for POSIX systems is provided in utils.c
uint32 lwm2m_gettime(void);

/*
 * Error code
 */

#define COAP_NO_ERROR                   (uint8_t)0x00
#define COAP_IGNORE                     (uint8_t)0x01

#define COAP_201_CREATED                (uint8_t)0x41
#define COAP_202_DELETED                (uint8_t)0x42
#define COAP_204_CHANGED                (uint8_t)0x44
#define COAP_205_CONTENT                (uint8_t)0x45
#define COAP_400_BAD_REQUEST            (uint8_t)0x80
#define COAP_401_UNAUTHORIZED           (uint8_t)0x81
#define COAP_402_BAD_OPTION             (uint8_t)0x82
#define COAP_404_NOT_FOUND              (uint8_t)0x84
#define COAP_405_METHOD_NOT_ALLOWED     (uint8_t)0x85
#define COAP_406_NOT_ACCEPTABLE         (uint8_t)0x86
#define COAP_500_INTERNAL_SERVER_ERROR  (uint8_t)0xA0
#define COAP_501_NOT_IMPLEMENTED        (uint8_t)0xA1
#define COAP_503_SERVICE_UNAVAILABLE    (uint8_t)0xA3

/*
 * Standard Object IDs
 */
#define LWM2M_SECURITY_OBJECT_ID            0
#define LWM2M_SERVER_OBJECT_ID              1
#define LWM2M_ACL_OBJECT_ID                 2
#define LWM2M_DEVICE_OBJECT_ID              3
#define LWM2M_CONN_MONITOR_OBJECT_ID        4
#define LWM2M_FIRMWARE_UPDATE_OBJECT_ID     5
#define LWM2M_LOCATION_OBJECT_ID            6
#define LWM2M_CONN_STATS_OBJECT_ID          7
#define LWM2M_LIGHT_CONTROL_OBJECT_ID       3311
#ifdef LWM2M_APPDATA_STD
#define LWM2M_APP_DATA_CONTAINER            19
#else
#define LWM2M_APP_DATA_CONTAINER            10250
#endif

#ifdef LWM2M_LOG_EVENT_STD
#define LWM2M_UPLOAD_LOG_OBJECT_ID          20
#else
#define LWM2M_UPLOAD_LOG_OBJECT_ID          10251
#endif

#define LWM2M_SECURITY_INSTANCE_ID            0

/*
 * Ressource IDs for the LWM2M Security Object
 */
#define LWM2M_SECURITY_URI_ID                 0
#define LWM2M_SECURITY_BOOTSTRAP_ID           1
#define LWM2M_SECURITY_SECURITY_ID            2
#define LWM2M_SECURITY_PUBLIC_KEY_ID          3
#define LWM2M_SECURITY_SERVER_PUBLIC_KEY_ID   4
#define LWM2M_SECURITY_SECRET_KEY_ID          5
#define LWM2M_SECURITY_SMS_SECURITY_ID        6
#define LWM2M_SECURITY_SMS_KEY_PARAM_ID       7
#define LWM2M_SECURITY_SMS_SECRET_KEY_ID      8
#define LWM2M_SECURITY_SMS_SERVER_NUMBER_ID   9
#define LWM2M_SECURITY_SHORT_SERVER_ID        10
#define LWM2M_SECURITY_HOLD_OFF_ID            11
#define LWM2M_SECURITY_PROTOCOL_TYPE          13

/*
 * Ressource IDs for the LWM2M Server Object
 */
#define LWM2M_SERVER_SHORT_ID_ID    0
#define LWM2M_SERVER_LIFETIME_ID    1
#define LWM2M_SERVER_MIN_PERIOD_ID  2
#define LWM2M_SERVER_MAX_PERIOD_ID  3
#define LWM2M_SERVER_DISABLE_ID     4
#define LWM2M_SERVER_TIMEOUT_ID     5
#define LWM2M_SERVER_STORING_ID     6
#define LWM2M_SERVER_BINDING_ID     7
#define LWM2M_SERVER_UPDATE_ID      8

#define LWM2M_SECURITY_MODE_PRE_SHARED_KEY  0
#define LWM2M_SECURITY_MODE_RAW_PUBLIC_KEY  1
#define LWM2M_SECURITY_MODE_CERTIFICATE     2
#define LWM2M_SECURITY_MODE_NONE            3

/*
* Ressource IDs for the LWM2M upload log Object
*/
#ifdef LWM2M_LOG_EVENT_STD
#define LWM2M_UPLOAD_LOG_RES_ID     4014
#else
#define LWM2M_UPLOAD_LOG_RES_ID     1
#endif


#define LWM2M_STRING_ID_MAX_LEN 8

#define SERVER_INSTANCE_ID    0

#define LWM2M_TIMER   86400 // 24 hours
#define LWM2M_REBOOT_DELAY_TIMER   60 // 1 min


/*
 * Utility functions for sorted linked list
 */

typedef struct _lwm2m_list_t
{
    struct _lwm2m_list_t * next;
    uint16_t    id;
} lwm2m_list_t;

// defined in list.c
// Add 'node' to the list 'head' and return the new list
lwm2m_list_t * lwm2m_list_add(lwm2m_list_t * head, lwm2m_list_t * node);
// Return the node with ID 'id' from the list 'head' or NULL if not found
lwm2m_list_t * lwm2m_list_find(lwm2m_list_t * head, uint16_t id);
// Remove the node with ID 'id' from the list 'head' and return the new list
lwm2m_list_t * lwm2m_list_remove(lwm2m_list_t * head, uint16_t id, lwm2m_list_t ** nodeP);
// Return the lowest unused ID in the list 'head'
uint16_t lwm2m_list_newId(lwm2m_list_t * head);
// Free a list. Do not use if nodes contain allocated pointers as it calls lwm2m_free on nodes only.
// If the nodes of the list need to do more than just "free()" their instances, don't use lwm2m_list_free().
void lwm2m_list_free(lwm2m_list_t * head);

#define LWM2M_LIST_ADD(H,N) lwm2m_list_add((lwm2m_list_t *)H, (lwm2m_list_t *)N);
#define LWM2M_LIST_RM(H,I,N) lwm2m_list_remove((lwm2m_list_t *)H, I, (lwm2m_list_t **)N);
#define LWM2M_LIST_FIND(H,I) lwm2m_list_find((lwm2m_list_t *)H, I)
#define LWM2M_LIST_FREE(H) lwm2m_list_free((lwm2m_list_t *)H)

/*
*   Resource values
*/

// defined in utils.c
int lwm2m_PlainTextToInt64(uint8_t * buffer, int length, int64_t * dataP);
int lwm2m_PlainTextToFloat64(uint8_t * buffer, int length, double * dataP);

/*
* These utility functions allocate a new buffer storing the plain text
* representation of data. They return the size in bytes of the buffer
* or 0 in case of error.
* There is no trailing '\0' character in the buffer.
*/

size_t lwm2m_int64ToPlainText(int64_t data, uint8_t ** bufferP);
size_t lwm2m_float64ToPlainText(double data, uint8_t ** bufferP);
size_t lwm2m_boolToPlainText(bool data, uint8_t ** bufferP);

/*
* TLV
*/

#define LWM2M_TLV_HEADER_MAX_LENGTH 6

/*
* Bitmask for the lwm2m_data_t::flag
* LWM2M_TLV_FIAG_STATIC_DATA specifies that lwm2m_data_t::value
* points to static memory and must no be freeed by the caller.
* LWM2M_TLV_FLAG_TEXT_FORMAT specifies that lwm2m_data_t::value
* is expressed or requested in plain text format.
*/
#define LWM2M_TLV_FLAG_STATIC_DATA   0x01
#define LWM2M_TLV_FLAG_TEXT_FORMAT   0x02

#ifdef LWM2M_BOOTSTRAP
#define LWM2M_TLV_FLAG_BOOTSTRAPPING 0x04
#endif

/*
* Bit 7 and 6 of assigned values for LWM2M_TYPE_RESOURCE,
* LWM2M_TYPE_MULTIPLE_RESOURCE, LWM2M_TYPE_RESOURCE_INSTANCE
* and LWM2M_TYPE_OBJECT_INSTANCE must match the ones defined
* in the TLV format LWM2M TS $6.3.3
*/
typedef enum
{
    LWM2M_TYPE_UNDEFINED = 0,
    LWM2M_TYPE_OBJECT,
    LWM2M_TYPE_OBJECT_INSTANCE,
    LWM2M_TYPE_MULTIPLE_RESOURCE,

    LWM2M_TYPE_STRING,
    LWM2M_TYPE_OPAQUE,
    LWM2M_TYPE_INTEGER,
    LWM2M_TYPE_FLOAT,
    LWM2M_TYPE_BOOLEAN,

    LWM2M_TYPE_OBJECT_LINK
} lwm2m_data_type_t;

typedef struct _lwm2m_data_t lwm2m_data_t;

struct _lwm2m_data_t
{
    //uint8_t flags;
    lwm2m_data_type_t type;
    uint16_t    id;
    union
    {
        bool        asBoolean;
        int64_t     asInteger;
        double      asFloat;
        struct
        {
            size_t    length;
            uint8_t * buffer;
        } asBuffer;
        struct
        {
            size_t         count;
            lwm2m_data_t * array;
        } asChildren;
        struct
        {
            uint16_t objectId;
            uint16_t objectInstanceId;
        } asObjLink;
    } value;
    //size_t    length;
    //uint8_t * value;
};

typedef struct
{
    uint8_t flag;       // indicates which segments are set
    uint16_t objectId;
    uint16_t instanceId;
    uint16_t resourceId;
} lwm2m_uri_t;

typedef enum
{
    LWM2M_CONTENT_TEXT      = 0,        // Also used as undefined
    LWM2M_CONTENT_LINK      = 40,
    LWM2M_CONTENT_OPAQUE    = 42,
    LWM2M_CONTENT_TLV       = 11542,     // Temporary value
    LWM2M_CONTENT_JSON      = 11543      // Temporary value
} lwm2m_media_type_t;

lwm2m_data_t * lwm2m_data_new(int size);
int lwm2m_data_parse(lwm2m_uri_t * uriP, uint8_t * buffer, size_t bufferLen, lwm2m_media_type_t format, lwm2m_data_t ** dataP);
int tlv_parse(uint8_t * buffer, size_t bufferLen, lwm2m_data_t ** dataP);
int lwm2m_serializeTLV(bool isResourceInstance, int size, lwm2m_data_t * dataP, uint8_t ** bufferP);
int lwm2m_data_serialize(lwm2m_uri_t * uriP, int size, lwm2m_data_t * dataP, lwm2m_media_type_t * formatP, uint8_t ** bufferP);
void lwm2m_data_free(int size, lwm2m_data_t * dataP);
int lwm2m_decode_TLV(const uint8_t * buffer, size_t buffer_len, lwm2m_data_type_t * oType, uint16_t * oID, size_t * oDataIndex, size_t * oDataLen);
void lwm2m_data_encode_int(int64_t value, lwm2m_data_t * dataP);
void lwm2m_data_encode_string(const char * string, lwm2m_data_t * dataP);
int lwm2m_data_decode_int(lwm2m_data_t * dataP, int64_t * valueP);
void lwm2m_data_encode_float(double value, lwm2m_data_t * dataP);
int lwm2m_data_decode_float(lwm2m_data_t * dataP, double * valueP);
void lwm2m_data_encode_bool(bool value, lwm2m_data_t * dataP);
int lwm2m_data_decode_bool(const lwm2m_data_t * dataP, bool * valueP);
void lwm2m_data_encode_opaque(uint8_t * buffer, size_t length, lwm2m_data_t * dataP);
void lwm2m_data_include(lwm2m_data_t * subDataP, size_t count, lwm2m_data_t * dataP);

/*
 * These utility functions fill the buffer with a TLV record containing
 * the data. They return the size in bytes of the Tlv record, 0 in case
 * of error.
*/
//int lwm2m_intToTLV(lwm2m_tlv_type_t type, int64_t data, uint16_t id, uint8_t * buffer, size_t buffer_len);
//int lwm2m_boolToTLV(lwm2m_tlv_type_t type, bool value, uint16_t id, uint8_t * buffer, size_t buffer_len);
//int lwm2m_opaqueToTLV(lwm2m_tlv_type_t type, uint8_t * dataP, size_t data_len, uint16_t id, uint8_t * buffer, size_t buffer_len);
//int lwm2m_decodeTLV(uint8_t * buffer, size_t buffer_len, lwm2m_tlv_type_t * oType, uint16_t * oID, size_t * oDataIndex, size_t * oDataLen);
int lwm2m_opaqueToInt(uint8_t * buffer, size_t buffer_len, int64_t * dataP);
int lwm2m_opaqueToFloat(uint8_t * buffer, size_t buffer_len, double * dataP);

/*
* URI
*
* objectId is always set
* if instanceId or resourceId is greater than LWM2M_URI_MAX_ID, it means it is not specified
*
*/
#define LWM2M_MAX_ID    ((uint16_t)0xFFFF)
#define LWM2M_URI_FLAG_OBJECT_ID    (uint8_t)0x04
#define LWM2M_URI_FLAG_INSTANCE_ID  (uint8_t)0x02
#define LWM2M_URI_FLAG_RESOURCE_ID  (uint8_t)0x01

#define LWM2M_URI_IS_SET_INSTANCE(uri) (((uri)->flag & LWM2M_URI_FLAG_INSTANCE_ID) != 0)
#define LWM2M_URI_IS_SET_RESOURCE(uri) (((uri)->flag & LWM2M_URI_FLAG_RESOURCE_ID) != 0)
#define LWM2M_URI_IS_SET_OBJECT(uri) (((uri)->flag & LWM2M_URI_FLAG_OBJECT_ID) != 0)


#define LWM2M_TOKEN_MAX_LEN 8

#define LWM2M_APPDATA_MAX_LEN  1024

// Parse an URI in LWM2M format and fill the lwm2m_uri_t.
// Return the number of characters read from buffer or 0 in case of error.
// Valid URIs: /1, /1/, /1/2,/1/2/, /1/2/3
// invalid URIs: /, //, //2, /1//, /1//3, /1/2/3, /1/2/3/4

typedef enum
{
    ATTRIBUTE_INVALID = 0,
    ATTRIBUTE_MIN_PERIOD = 1,
    ATTRIBUTE_MAX_PERIOD = 2,
    ATTRIBUTE_GREATER_THAN = 3,
    ATTRIBUTE_LESS_THAN = 4,
    ATTRIBUTE_STEP = 5,
    ATTRIBUTE_CANCEL = 6
} lwm2m_attribute_type_t;

typedef struct _lwm2m_block_option_t
{
    int block_num;
    int offset;
    uint16_t size;
    uint8_t more;
} lwm2m_block_option_t;

/*
 * LWM2M Objects
 *
 * For the read callback, if *numDataP is not zero, *dataArrayP is pre-allocated
 * and contains the list of resources to read.
 *
 */

typedef struct _lwm2m_object_t lwm2m_object_t;

typedef uint8_t (*lwm2m_read_callback_t) (uint16_t instanceId, int * numDataP, lwm2m_data_t ** dataArrayP, lwm2m_object_t * objectP);
typedef uint8_t (*lwm2m_discover_callback_t) (uint16_t instanceId, int * numDataP, char dataArrayP[], lwm2m_object_t * objectP);
typedef uint8_t (*lwm2m_write_callback_t) (uint16_t instanceId, int numData, lwm2m_data_t * dataArray, lwm2m_object_t * objectP, lwm2m_block_option_t * opt);
typedef uint8_t (*lwm2m_execute_callback_t) (uint16_t instanceId, uint16_t resourceId, uint8_t * buffer, int length, lwm2m_object_t * objectP);
typedef uint8_t (*lwm2m_create_callback_t) (uint16_t instanceId, int numData, lwm2m_data_t * dataArray, lwm2m_object_t * objectP);
typedef uint8_t (*lwm2m_delete_callback_t) (uint16_t instanceId, lwm2m_object_t * objectP);
typedef uint8_t (*lwm2m_get_datatype_t) (uint16_t resourceId, lwm2m_data_type_t * dataType);
typedef void (*lwm2m_close_callback_t) (lwm2m_object_t * objectP);

struct _lwm2m_object_t
{
    uint16_t       objID;
    lwm2m_list_t * instanceList;
    lwm2m_read_callback_t     readFunc;
    lwm2m_write_callback_t    writeFunc;
    lwm2m_execute_callback_t  executeFunc;
    lwm2m_create_callback_t   createFunc;
    lwm2m_delete_callback_t   deleteFunc;
    lwm2m_close_callback_t    closeFunc;
    lwm2m_discover_callback_t discoverFunc;
    lwm2m_get_datatype_t     datatypeFunc;
    void * userData;
};

/*
 * LWM2M Servers
 *
 * Since LWM2M Server Object instances are not accessible to LWM2M servers,
 * there is no need to store them as lwm2m_objects_t
 */

typedef enum
{
    STATE_DEREGISTERED = 0,   // not registered or boostrap not started
    STATE_REG_PENDING,        // registration pending
    STATE_REGISTERED,         // successfully registered
    STATE_REG_FAILED,         // last registration failed
    STATE_REG_UPDATE_PENDING, // registration update pending
    STATE_REG_UPDATE_NEEDED,  // registration update required
    STATE_DEREG_PENDING,      // deregistration pending
    STATE_BS_HOLD_OFF,        // bootstrap hold off time 7
    STATE_BS_INITIATED,       // bootstrap request sent
    STATE_BS_PENDING,         // boostrap on going
    STATE_BS_FINISHED,        // bootstrap done
    STATE_BS_FAILED,          // bootstrap failed
    STATE_DEREG_FAILED,       // deregistration failed
    STATE_BS_REQ,
    STATE_BS_WAITING_FINISH,
} lwm2m_status_t;


typedef enum
{
    BINDING_UNKNOWN = 0,
    BINDING_U,   // UDP
    BINDING_UQ,  // UDP queue mode
    BINDING_S,   // SMS
    BINDING_SQ,  // SMS queue mode
    BINDING_US,  // UDP plus SMS
    BINDING_UQS  // UDP queue mode plus SMS
} lwm2m_binding_t;

typedef enum
{
    AUTO_BS_REG_INGORE = 0,
    AUTO_BS, 
    AUTO_REG,
} lwm2m_auto_bs_reg_t;

typedef struct resource_value
{
    union
    {
        double floatValue;
        int64_t intValue;
    }val;
} lwm2m_resource_value_t;
lwm2m_resource_value_t lwm2m_set_decimal_value(double f);
lwm2m_resource_value_t lwm2m_set_numeric_value(int64_t ui);
#define LWM2M_URI_FLAG_OLD_VALUE    (uint8_t)0x20
#define LWM2M_URI_FLAG_STEP    (uint8_t)0x10
#define LWM2M_URI_FLAG_LESS_THAN    (uint8_t)0x08
#define LWM2M_URI_FLAG_GREATER_THAN    (uint8_t)0x04
#define LWM2M_URI_FLAG_MAX_PERIOD  (uint8_t)0x02
#define LWM2M_URI_FLAG_MIN_PERIOD  (uint8_t)0x01

#define ATTR_FLAG_NUMERIC (uint8_t)(LWM2M_URI_FLAG_LESS_THAN | LWM2M_URI_FLAG_GREATER_THAN | LWM2M_URI_FLAG_STEP)

#define LWM2M_URI_IS_SET_MIN_PERIOD(attr) ((attr->flag & LWM2M_URI_FLAG_MIN_PERIOD) != 0)
#define LWM2M_URI_IS_SET_MAX_PERIOD(attr) ((attr->flag & LWM2M_URI_FLAG_MAX_PERIOD) != 0)
#define LWM2M_URI_IS_SET_GREATER_THAN(attr) ((attr->flag & LWM2M_URI_FLAG_GREATER_THAN) != 0)
#define LWM2M_URI_IS_SET_LESS_THAN(attr) ((attr->flag & LWM2M_URI_FLAG_LESS_THAN) != 0)
#define LWM2M_URI_IS_SET_STEP(attr) ((attr->flag & LWM2M_URI_FLAG_STEP) != 0)
#define LWM2M_URI_IS_SET_OLD_VALUE(attr) ((attr->flag & LWM2M_URI_FLAG_OLD_VALUE) != 0)

#define LWM2M_URI_SET_MIN_PERIOD(attr) (attr->flag |= LWM2M_URI_FLAG_MIN_PERIOD)
#define LWM2M_URI_SET_MAX_PERIOD(attr) (attr->flag |= LWM2M_URI_FLAG_MAX_PERIOD)
#define LWM2M_URI_SET_GREATER_THAN(attr) (attr->flag |= LWM2M_URI_FLAG_GREATER_THAN)
#define LWM2M_URI_SET_LESS_THAN(attr) (attr->flag |= LWM2M_URI_FLAG_LESS_THAN)
#define LWM2M_URI_SET_STEP(attr) (attr->flag |= LWM2M_URI_FLAG_STEP)
#define LWM2M_URI_SET_OLD_VALUE(attr) (attr->flag |= LWM2M_URI_FLAG_OLD_VALUE)

/** holds the attributes for object, instance and resources */
#if 0
typedef struct _attribute_data_
{
    struct _attribute_data_ * next;     // next list a element
	uint8_t* optaque_value;
    uint16_t optaque_value_len;
    uint16_t shortID;
    uint32 lastTransmission;    /**< holds the time stamp of the last transmission of this object, instance or resource */
    uint32 nextTransmission;    /**< holds the time for the next scheduled transmission */
    lwm2m_uri_t uri;            /**< holds the URI of the object/instance/resource the attributes are valid for */
    uint32_t minPeriod;         /**< minimal update period in seconds, the object/instance/resource must not be sent more frequent */
    uint32_t maxPeriod;         /**< maximum update period, the object/instance/resource must be sent at keast after this period, even if no change happend */
    lwm2m_resource_value_t greaterThan;     /**< the resource has to be sent if this threshold is reached */
    lwm2m_resource_value_t lessThan;        /**< the resource has to be sent if this threshold is underrun */
    lwm2m_resource_value_t step;            /**< the resource has to be sent if it si changed by the given step */
    lwm2m_resource_value_t oldValue;        /**< holds the last sent value of the resource if the resource is a numerical resource */
    lwm2m_data_type_t resDataType;
    uint8_t flag;
} lwm2m_attribute_data_t;
#endif

typedef struct
{
    uint8_t     toSet;
    uint8_t     toClear;
    uint32_t    minPeriod;
    uint32_t    maxPeriod;
    double      greaterThan;
    double      lessThan;
    double      step;
} lwm2m_attributes_t;


typedef struct _lwm2m_server_
{
    //struct _lwm2m_server_ * next;   // matches lwm2m_list_t::next
    uint16_t          secObjInstID; // matches lwm2m_list_t::id
    uint16_t          shortID;      // servers short ID, may be 0 for bootstrap server
    uint32            lifetime;     // lifetime of the registration in sec or 0 if default value (86400 sec), also used as hold off time for bootstrap servers
    uint32            registration; // date of the last registration in sec
    lwm2m_binding_t   binding;      // client connection mode with this server
    void *            sessionH;
    lwm2m_status_t    status;
    char              location[64];
    //lwm2m_attribute_data_t * attributeData; /**< list of attributr data */
} lwm2m_server_t;


/*
 * LWM2M result callback
 *
 * When used with an observe, if 'data' is not nil, 'status' holds the observe counter.
 */
typedef void (*lwm2m_result_callback_t) (uint16_t clientID, lwm2m_uri_t * uriP, int status, int format, uint8_t * data, int dataLength, void * userData);

/*
 * LWM2M Observations
 *
 * Used to store observation of remote clients resources.
 * status STATE_REG_PENDING means the observe request was sent to the client but not yet answered.
 * status STATE_REGISTERED means the client acknowledged the observe request.
 * status STATE_DEREG_PENDING means the user canceled the request before the client answered it.
 */

typedef struct _lwm2m_observation_
{
    struct _lwm2m_observation_ * next;  // matches lwm2m_list_t::next
    uint16_t                     id;    // matches lwm2m_list_t::id
    struct _lwm2m_client_ * clientP;
    lwm2m_uri_t             uri;
    lwm2m_status_t          status;
    lwm2m_result_callback_t callback;
    void *                  userData;
} lwm2m_observation_t;

/*
 * LWM2M Clients
 *
 * Be careful not to mix lwm2m_client_object_t used to store list of objects of remote clients
 * and lwm2m_object_t describing objects exposed to remote servers.
 *
 */

typedef struct _lwm2m_client_object_
{
    struct _lwm2m_client_object_ * next; // matches lwm2m_list_t::next
    uint16_t                 id;         // matches lwm2m_list_t::id
    lwm2m_list_t *           instanceList;
} lwm2m_client_object_t;

typedef struct _lwm2m_client_
{
    struct _lwm2m_client_ * next;       // matches lwm2m_list_t::next
    uint16_t                internalID; // matches lwm2m_list_t::id
    char *                  name;
    lwm2m_binding_t         binding;
    char *                  msisdn;
    char *                  altPath;
    uint32_t                lifetime;
    uint32                  endOfLife;
    void *                  sessionH;
    lwm2m_client_object_t * objectList;
    lwm2m_observation_t *   observationList;
} lwm2m_client_t;


/*
 * LWM2M transaction
 *
 * Adaptation of Erbium's coap_transaction_t
 */

typedef enum
{
    ENDPOINT_UNKNOWN = 0,
    ENDPOINT_CLIENT,
    ENDPOINT_SERVER
} lwm2m_endpoint_type_t;

typedef struct _lwm2m_transaction_ lwm2m_transaction_t;

typedef void (*lwm2m_transaction_callback_t) (lwm2m_transaction_t * transacP, void * message);

struct _lwm2m_transaction_
{
    lwm2m_transaction_t * next;  // matches lwm2m_list_t::next
    uint16_t              mID;   // matches lwm2m_list_t::id
    lwm2m_endpoint_type_t peerType;
    void *                peerP;
    uint8_t               ack_received; // indicates, that the ACK was received
    uint32                response_timeout; // timeout to wait for response, if token is used. When 0, use calculated acknowledge timeout.
    uint8_t  retrans_counter;
    uint32   retrans_time;
    char objStringID[LWM2M_STRING_ID_MAX_LEN];
    char instanceStringID[LWM2M_STRING_ID_MAX_LEN];
    char resourceStringID[LWM2M_STRING_ID_MAX_LEN];
    void * pdu;
    uint16_t buffer_len;
    uint8_t * buffer;
    lwm2m_transaction_callback_t callback;
    void * userData;
};

/*
 * LWM2M observed resources
 */

typedef struct _lwm2m_watcher_
{
    struct _lwm2m_watcher_ * next;

    bool active;
    bool update;
    lwm2m_server_t * server;
    lwm2m_attributes_t * parameters;
    uint8_t token[8];
    size_t tokenLen;
    time_t lastTime;
    uint32_t counter;
    uint16_t lastMid;
    union
    {
        int64_t asInteger;
        double  asFloat;
    } lastValue;
} lwm2m_watcher_t;

typedef struct _lwm2m_observe_token_
{
    size_t tokenLen;
    uint8_t token[8];
}lwm2m_observe_token_t;

typedef struct _lwm2m_observed_
{
    struct _lwm2m_observed_ * next;

    lwm2m_uri_t uri;
    lwm2m_watcher_t * watcherList;
    unsigned short id;
} lwm2m_observed_t;

#ifdef LWM2M_BOOTSTRAP
typedef enum
{
    NOT_BOOTSTRAPPED = 0,
    BOOTSTRAP_REQUESTED,
    BOOTSTRAP_CLIENT_HOLD_OFF,
    BOOTSTRAP_INITIATED,
    BOOTSTRAP_PENDING,
    BOOTSTRAP_FINISHED,
    BOOTSTRAP_FAILED,
    BOOTSTRAPPED
} lwm2m_bootstrap_state_t;
#endif

typedef enum
{
    STATE_INITIAL = 0,
    STATE_BOOTSTRAP_REQUIRED,
    STATE_BOOTSTRAPPING,
    STATE_REGISTER_REQUIRED,
    STATE_REGISTERING,
    STATE_READY,
    STATE_BOOTSTRAP_HOLD_OFF,
} lwm2m_client_state_t;

typedef enum
{
    STATE_LWM2M_UNINITIALISED = 0,
    STATE_LWM2M_MISSING_CONFIG,
    STATE_LWM2M_INIITIALISING,
    STATE_LWM2M_INIITIALISED,
    STATE_LWM2M_INIT_FAILED,
    STATE_LWM2M_REGISTERING,
    STATE_LWM2M_REGISTERED,
    STATE_LWM2M_DEREGISTERED,
    STATE_LWM2M_APP_DATA_ENABLED,
    STATE_LWM2M_NO_UE_IP,
    STATE_LWM2M_REJECTED_BY_SERVER,
    STATE_LWM2M_TIMEOUT_AND_RETRYING,
    STATE_LWM2M_REG_FAILED,
    STATE_LWM2M_DEREG_FAILED,
}lwm2m_client_state_ex_t;

/*
 * LWM2M Context
 */

typedef struct lwm2m_context lwm2m_context_t;

// The session handle MUST uniquely identify a peer.
typedef void * (*lwm2m_connect_server_callback_t) (uint16_t secObjInstID, void * userData);
// The session handle MUST uniquely identify a peer.
//typedef uint8_t (*lwm2m_buffer_send_callback_t) (lwm2m_context_t * contextP, lwm2m_coap_message_t * message,
//                                        void * sessionH);

struct lwm2m_context
{
    lwm2m_client_state_t state;
    uint32               bsStart;
    char *               endpointName;
    char *               msisdn;
    char *               altPath;
#ifdef LWM2M_BOOTSTRAP
    lwm2m_server_t *     bootstrapServer;
#endif
    lwm2m_server_t *     server;
    lwm2m_object_t **    objectList;
    uint16_t             numObject;
    lwm2m_observed_t *   observedList;
    lwm2m_observed_t *   app_data_observed;
    lwm2m_observe_token_t *fw_state_tokenP;
    coap_context_t    * libcoap_context;
    uint16_t                nextMID;
    lwm2m_transaction_t *   transactionList;
    // communication layer callbacks
    lwm2m_connect_server_callback_t connectCallback;
    //lwm2m_buffer_send_callback_t    bufferSendCallback;
    void *                          userData;
    lwm2m_client_state_ex_t    state_ex;

};

typedef enum OTA_STATUS
{
    OTA_SUCCESS,                // Success (Downloaded)
    OTA_STORAGE_ERROR,          // Not enough storage for the new firmware package
    OTA_MEMORY_ERROR,           // Out of memory during downloading
    OTA_CONNECTION_ERROR,       // connection lost during downloading
    OTA_CRC_ERROR,              // check failure of new downloaded package
    OTA_INVALID_PACKAGE_TYPE,   // Unsupported Package Type
    OTA_INVALID_URI,            // Invalid URI
    OTA_INVALID_PACKAGE_HANDLE, // File not a package
    OTA_NO_SUCH_FILE,           // Server says no such file
    OTA_ACCESS_ERROR,           // Server says no
    OTA_IN_PROGRESS,             // Header exists but hasn't had the full download cycle
    OTA_TOKEN_ERROR,
    OTA_PDU_MSG_ERROR,
    OTA_BLOCK_NUM_ERROR,
    OTA_RES_CODE_OR_BLK_SIZE_ERROR, //Response ack  or block size error
    
} OTA_STATUS;
typedef enum
{
    COAP_MESSAGE_NON_NORAI      = 0x0000,
    COAP_MESSAGE_NON_WITH_RAI   = 0x0001,
    COAP_MESSAGE_NON_WITH_SENDBACKRAI   = 0x0010,
    COAP_MESSAGE_CON_NORAI      = 0x0100,
    COAP_MESSAGE_CON_WITH_RAI   = 0x0101,
    
} SOCK_MSG_MODE;
typedef enum
{
    NOT_SENT            = 0,
    SENT_WAIT_RESPONSE,  
    SENT_FAIL,   
    SENT_TIMEOUT,
    SENT_SUCCESS,
    SENT_GOT_RST,
    SEND_PENDING,
      
}CON_DATA_SEND_STATUS;

typedef struct _lwm2m_con_data_status_
{
    CON_DATA_SEND_STATUS send_status;
    uint8 seq_num;
}lwm2m_con_data_status;

typedef enum 
{
    DISCARDED,
    SENT,
    SENT_TO_AIR_INTERFACE,
}LWM2M_DATA_SENT_RESULT_TO_AIRFACE;

typedef enum
{
    NO_INIT = 0,
    SERVER_INIT, 
    CLIENT_INIT,
}lwm2m_bs_init_type;

// initialize a liblwm2m context.
lwm2m_context_t * lwm2m_init(coap_context_t *libcoap_context, lwm2m_connect_server_callback_t connectCallback, void * userData);
// dispatch received data to liblwm2m
void lwm2m_handle_packet(lwm2m_context_t * contextP, coap_pdu_t * pdu, void * fromSessionH, coap_pdu_t * response_pdu);
void lwm2m_handle_response(lwm2m_context_t * contextP, coap_pdu_t * pdu, void * fromSessionH, coap_pdu_t * response_pdu);
void lwm2m_handle_notify_packet(lwm2m_context_t * contextP, void * fromSessionH, coap_pdu_t * response_pdu,str * token);
void ota_package_init_callback(void);

// configure the client side with the Endpoint Name, binding, MSISDN (can be nil), alternative path
// for objects (can be nil) and a list of objects.
// LWM2M Security Object (ID 0) must be present with either a bootstrap server or a LWM2M server and
// its matching LWM2M Server Object (ID 1) instance
int lwm2m_configure(lwm2m_context_t * contextP, const char * endpointName, const char * msisdn, const char * altPath, uint16_t numObject, lwm2m_object_t ** objectList);
//void lwm2m_state_check(uint32 *state);
/*lwm2m start download update package
 *lwm2m will get request to server
*/
void start_download(void);
void lwm2m_request_package_callback(uint8 result);
void lwm2m_notify_fw_state(uint32 state, unsigned char coap_type);
uint8_t lwm2m_fw_dl_state_save( void );
void ota_validate_package_check_callback(uint8 status);
OTA_STATUS lwm2m_fw_pgk_save(lwm2m_context_t * contextP, coap_pdu_t* pdu);
void lwm2m_fw_pkg_dl(lwm2m_block_option_t *opt);
void lwm2m_fw_update(void);
void lwm2m_fw_timeout_proc(void);
uint16 get_fota_ind_value(void);
void lwm2m_state_change(uint16 state);
void lwm2m_conntection_failed(void);

void lwm2m_add_bs_reg_timer(void);
void lwm2m_stop_bs_reg_timer(void);
void lwm2m_reg_timeout_callback(void);
void lwm2m_bs_seq_or_register_retry(void);
void lwm2m_bs_reg_selfcure_callback(void);
void lwm2m_bs_reg_reboot(void);
void lwm2m_start_bs_clientholdoff_timer(void);
void lwm2m_stop_bs_clientholdoff_timer(void);
void lwm2m_bs_holdoff_timeout_cb(osTimerId_t xTimer);
void lwm2m_add_bs_client_timer(void);
void lwm2m_stop_bs_client_timer(void);
void lwm2m_bs_client_timeout_cb(void);
int lwm2m_step(lwm2m_context_t * contextP, time_t * timeoutP);
AT_RET lwm2m_appdata_notify(uint8_t *buffer, uint16 length, uint16 mode, uint8 seq_num);
void app_confirmable_data_cb(void *context, coap_pdu_t *pdu,  int flag);
void lwm2m_fw_state_notify(uint8_t state);
void lwm2m_stats_pending_update(int change);
void lwm2m_stats_error_update(uint32 change);
void lwm2m_stats_sent_update(uint32 change);
void lwm2m_trigger_appdata_sent_callback(LWM2M_DATA_SENT_RESULT_TO_AIRFACE status, uint8 seq_num);
#ifdef DTLS
void lwm2m_stop_dtls_semaphore_timer(void);
#endif
AT_RET lwm2m_check_appdata(uint8 seq_num);




void init_bootstrapserver(lwm2m_server_t ** BSserverP);
void init_server(lwm2m_server_t ** serverP);
unsigned short lwm2m_new_message_id(lwm2m_context_t *context);

extern int lwm2m_update_registration(lwm2m_context_t * contextP, uint16_t shortServerID);
void lwm2m_send_update_register_msg(void);
void lwm2m_reg_msg(void);
void lwm2m_get_module_current_ipaddr(void);
void lwm2m_detach_query_cb(osTimerId_t xTimer);
void lwm2m_query_detach_state(void);
void lwm2m_attach_query_cb(osTimerId_t xTimer);
void lwm2m_query_attach_state(void);
void coap_cancel_con_req_retrans_msg(coap_context_t *context, lwm2m_transaction_callback_t con_req_cb);

#if 1
void ByteToHexStr(uint8_t * source, char* dest, int sourceLen);
uint32 make_rspstring(uint8 type, lwm2m_data_t * dataP, uint8** str_at);

#else
uint32 make_rspstring(uint8 type, lwm2m_data_t * dataP, uint8** str_at);
#endif

#ifdef LWM2M_BOOTSTRAP
int GetBootStrapStatus(void);
extern void bootstrap_step(lwm2m_context_t * contextP, uint32_t currentTime, time_t* timeoutP);
extern unsigned int bootstrap_handleFinish(lwm2m_context_t * context, void * fromSessionH);
extern void prv_handleBootstrapReply(lwm2m_transaction_t * transaction, void * message);
extern void prv_bootstrapFailed(lwm2m_server_t * bootstrapServer);
#endif


#ifdef __cplusplus
}
#endif

#endif /* _LIBLWM2M_H_ */
