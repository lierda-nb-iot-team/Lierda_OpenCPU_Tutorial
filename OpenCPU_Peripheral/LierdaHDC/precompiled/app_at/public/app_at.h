/******************************************************************************
 * @brief    AT Command structures
 * Portions copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef    _APP_AT_H_
#define    _APP_AT_H_

#include "irmalloc.h"
#include "neul_radio_types.h"

#define AT_MAX_MTU_SIZE    NEUL_IP_MTU_SIZE

/** @addtogroup libNEUL_APP_AT_MOD_API
 * @{
 * */

#define at_alloc(_size) irzalloc(_size)
#define at_free(ptr) \
{\
    irfree((ptr));\
    (ptr) = NULL;\
}

#define at_strlen(ptr)                  strlen((char *)ptr)
#define at_strncmp(ptr1,ptr2,len)       strncmp((char *)ptr1, (char *)ptr2, len)
#define at_strcmp(ptr1,ptr2)            strcmp((char *)ptr1, (char *)ptr2)
#define at_strcpy(ptr1,ptr2)            strcpy((char *)ptr1, (char *)ptr2)
#define at_strncpy(ptr1,ptr2,len)       strncpy((char *)ptr1, (char *)ptr2, len)

#define MAX_IP_LEN                 60
#define APP_AT_STR_RN                "\r\n"

#define MB

#ifdef MB
#define  LPNM_CMD_BUF  "MB86" //"NB08-01" //"NB05-01T",    MB86-B5
#define  ICCID_MODELSMS   "LED-MB86 B5"

#define CGMM_CMD_BUF "LSD4NBN-150H02" //LSD4LBN0724-02D0
#define CGMI_RSP_BUF  "Lierda"
#define LGMR_CMD_BUF "B300R3Lierda1501707T"  //LSD4NBN-LB05000004
#else



#define  LPNM_CMD_BUF  "NB86-G" //"NB08-01" //"NB05-01T",    MB86-B5
#define  ICCID_MODELSMS   "LED-NB86 G"

#define CGMM_CMD_BUF "LSD4NBN-150H01" //LSD4LBN0724-02D0
#define CGMI_RSP_BUF  "Lierda"
#define LGMR_CMD_BUF "B500R0Lierda1501013"  //LSD4NBN-LB05000004
#endif
#define ICCID_IP_ADDR  0x0F02632A
#define ICCID_IP_ADDR_LT 0x69ee5d2f
#define ICCID_RETURN_OK   0
#define LCTRGE_USED       1
#define AT_MAIN_START_UP     "\r\nLierda \r\nOK\r\n"
typedef enum
{
    AT_RET_OK                           = 0x00,
    AT_RET_SYNTAX_ERROR                 = 0x01,
    AT_RET_NOT_NUMERIC                  = 0x02,
    AT_RET_PARAM_MISSING                = 0x03,
    AT_RET_MEMORY_ERROR                 = 0x04,
    AT_RET_CMD_IN_PROGRESS              = 0x05,
    AT_RET_PROGRESS_ERROR               = 0x06,
    AT_RET_FLOW_CONTROL                 = 0x07,
    AT_RET_PARAM_UNCONFIG               = 0x08,
    AT_RET_CMD_IN_PROGRESS_BLOCK        = 0x09,
    AT_RET_NOT_REGISTERED               = 0x0A,
    AT_RET_NO_NETWORK_SERVICE           = 0x0B,
    AT_RET_CMD_NOT_SUPPORTED            = 0x0C,
    AT_RET_INTERNAL_ERROR               = 0x0D,
    AT_RET_COMMAND_DISABLED             = 0x0E,
    AT_RET_CID_ACTIVE_ERROR             = 0x0F,
    AT_RET_RADIOTEST_STATE_ERROR        = 0x10,
    AT_RET_CID_INVALID                  = 0x11,
    AT_RET_CID_NOT_ACTIVE               = 0x12,
    AT_RET_FOTA_UPDATING                = 0x13,
    AT_RET_CMD_WAIT_RESPONSE            = 0x14,
    AT_RET_SIM_PIN_REQUIRED             = 0x15,
#ifdef LIBMBEDTLS
    AT_RET_SECURITY_ERROR               = 0X16,
#endif
    AT_RET_DEACTIVE_LAST_ACTIVE_CID     = 0x17,
    AT_RET_CID_NOT_DEFINED              = 0x18,
    AT_RET_UART_PARITY_ERROR            = 0x19,
    AT_RET_CMD_ABORT_BY_USER            = 0x1A,
    AT_RET_UART_FRAME_ERROR             = 0x1B,
    AT_RET_NOT_POWER_ON                 = 0x1C,
    AT_RET_DATA_SEQUENCE_REPEAT_ERROR   = 0x1D,
    AT_RET_CMD_ABORT_ERROR              = 0x1E,
    AT_RET_COMMAND_INTERRUPTED          = 0x1F,
    AT_RET_CONFIGURATION_CONFLICTS      = 0x20,
    AT_RET_SMS_OPERATION_NOT_ALLOWED    = 0x21,
    AT_RET_SMS_OPERATION_NOT_SUPPORTED  = 0x22,
    AT_RET_SMS_MEMORY_ERROR             = 0x23,
    AT_RET_SMS_RESP_SENT                = 0x24,
    AT_RET_INVALID_SOCKET               = 0x25,
    AT_RET_VALUE_OVERFLOW               = 0x26,
    AT_RET_SMS_NO_CNMA_ACKNOWLEDGEMENT_EXPECTED = 0x27,
    AT_RET_SIM_NOT_INSERTED             = 0x28,
    AT_RET_INCORRECT_PASSWORD           = 0x29,
    AT_RET_SIM_PUK_REQUIRED             = 0x2A,
    AT_RET_SIM_PIN_BLOCKED              = 0x2B,
    AT_RET_SIM_PUK_BLOCKED              = 0x2C,
    AT_RET_UNSUPPORTED_QCI_VAULE        = 0x2D,
    AT_RET_NOT_MIPI_MODULE              = 0x2E,
    AT_RET_FILE_NOT_FOUND                   = 0x2F,
    AT_RET_CONDITIONS_OF_USE_NOT_SATISFIED  = 0x30,
    AT_RET_UART_BUFFER_ERROR            = 0x31,
    AT_RET_BACK_OFF                     = 0X32,
} AT_RET;

typedef enum
{
    SMS_RESPONSE_OK = 0,
    SMS_RESPONSE_ERROR = 1

} AT_SMS_RET;

typedef enum
{
    AT_FLAG_UNVISIABLE              = (1),
    AT_FLAG_VISIABLE                = (1 << 1),
    AT_FLAG_UNLOGABLE               = (1 << 2),
    AT_FLAG_LOGABLE                 = (1 << 3),
    AT_FLAG_CONVERT_2_HEX           = (1 << 4),
    AT_FLAG_LOG_RESTRICTED          = (1 << 5),
    AT_FLAG_ABORTABLE               = (1 << 6),
    AT_FLAG_APPLICATION_ONLY_CMD    = (1 << 7),
    AT_FLAG_SMS_CMD                 = (1 << 8),
} AT_FLAG;

//lint -e655 visiable and logable are the same enum
#define AT_IS_VISIABLE(flag)                ((flag) & AT_FLAG_VISIABLE)
#define AT_IS_LOGABLE(flag)                 ((flag) & AT_FLAG_LOGABLE)
#define AT_IS_HEXSTRING(flag)               ((flag) & AT_FLAG_CONVERT_2_HEX)
#define AT_IS_LOG_RESTRICTED(flag)          ((flag) & AT_FLAG_LOG_RESTRICTED)
#define AT_IS_ABORTABLE(flag)               ((flag) & AT_FLAG_ABORTABLE)
#define AT_IS_APPLICATION_ONLY_CMD(flag)    ((flag) & AT_FLAG_APPLICATION_ONLY_CMD)
#define AT_IS_SMS_CMD(flag)                 ((flag) & AT_FLAG_SMS_CMD)


typedef enum
{
    AT_SMS_MESSAGE_NULL = 0,
    AT_SMS_MESSAGE_CNMA,
    AT_SMS_MESSAGE_CMGS,
    AT_SMS_MESSAGE_CMGC
}AT_SMS_MESSAGE;

typedef struct
{
    bool        is_in_double_quotes;
    uint8      *str;
    uint16      str_len;
}AT_PARAM_s;

typedef struct
{
    uint8        param_count;
    AT_PARAM_s   *params_array;
}AT_PARAM_TABLE_s;

/** At command set callback
 * @param at_string The at string parameter to parse
 * @return result or at command
 */
typedef AT_RET ( *at_cmd_set) (uint8 *at_string);

/** At command read callback
 * @return result or at command
 */
typedef AT_RET ( *at_cmd_read) (void);

/** At command test callback
 * @return result or at command
 */
typedef AT_RET ( *at_cmd_test) (void);

/** At command execute callback
 * @return result or at command
 */

typedef AT_RET ( *at_cmd_exec) (void);

typedef struct
{
    AT_FLAG flag;
    char *cmd_str;  //command string

    at_cmd_set at_set_handler;
    at_cmd_read at_read_handler;
    at_cmd_test at_test_handler;
    at_cmd_exec at_exec_handler;
}AT_CMD_CB_s;

typedef struct
{
    AT_RET cause;
    uint16 errno;
}at_ret_errno_map_t; //lint !e959 at_ret_errno_map_t

static const at_ret_errno_map_t g_cmee_errno_table[] =
{
    // General Errors
    {AT_RET_COMMAND_DISABLED, 3}, //operation not allowed
    {AT_RET_PROGRESS_ERROR, 4},   //operation not supported
    {AT_RET_SIM_NOT_INSERTED, 10}, //SIM not inserted.
    {AT_RET_SIM_PIN_REQUIRED, 11}, //Need to enter PIN.
    {AT_RET_SIM_PUK_REQUIRED, 12}, //SIM PUK required.
    {AT_RET_INCORRECT_PASSWORD, 16}, //incorrect password.
    {AT_RET_MEMORY_ERROR, 23},    //memory failure
    {AT_RET_NO_NETWORK_SERVICE, 30}, //no network servise
    {AT_RET_NOT_NUMERIC, 50},     //Incorrect parameters
    {AT_RET_PARAM_MISSING, 50},   //Incorrect parameters
    {AT_RET_SYNTAX_ERROR, 50},    //Incorrect parameters
    {AT_RET_CMD_IN_PROGRESS, 51}, //command implemented but currently disabled
    {AT_RET_CMD_ABORT_BY_USER, 52},//command aborted by user
    {AT_RET_FLOW_CONTROL, 159},   //Uplink Busy
    {AT_RET_UNSUPPORTED_QCI_VAULE, 181},    //unsupported QCI value
    {AT_RET_PARAM_UNCONFIG, 512}, //Required Parameter Not Configured
    {AT_RET_NOT_REGISTERED, 513}, //TUP  Not Registered.
    {AT_RET_INTERNAL_ERROR, 514}, //AT Cmd Internal Error.
    {AT_RET_CID_ACTIVE_ERROR,515}, // cid is active.
    {AT_RET_RADIOTEST_STATE_ERROR,516},  //radio test state error
    {AT_RET_CID_INVALID,517},      //cid is invalid.
    {AT_RET_CID_NOT_ACTIVE,518},      //cid is not active.

#ifdef LIBMBEDTLS
    {AT_RET_SECURITY_ERROR,519},    //link security error.
#endif
    {AT_RET_DEACTIVE_LAST_ACTIVE_CID, 520},     //deactive last active cid
    {AT_RET_CID_NOT_DEFINED,521},               //cid is not defined.
    {AT_RET_UART_PARITY_ERROR, 522},            //at uart parity error.
    {AT_RET_UART_FRAME_ERROR, 523},             //at uart frame error.
    {AT_RET_NOT_POWER_ON, 524},                 //ue not power on
    {AT_RET_DATA_SEQUENCE_REPEAT_ERROR, 525},   //sent data sequence repeat error
    {AT_RET_CMD_ABORT_ERROR, 526},              //at command abort error
    {AT_RET_COMMAND_INTERRUPTED, 527},          //command interrupted
    {AT_RET_CONFIGURATION_CONFLICTS, 528},      //configuration conflicts
    {AT_RET_FOTA_UPDATING, 529},                //FOTA is updating
    {AT_RET_INVALID_SOCKET, 530},               //not the at allocated socket
    {AT_RET_SIM_PIN_BLOCKED, 531},              //SIM PIN is blocked
    {AT_RET_SIM_PUK_BLOCKED, 532},              //SIM PUK is blocked
    {AT_RET_NOT_MIPI_MODULE, 533},              //Not mipi module
    {AT_RET_FILE_NOT_FOUND, 534},               //file not found
    {AT_RET_CONDITIONS_OF_USE_NOT_SATISFIED, 535}, //conditions of use not satisfied
    {AT_RET_UART_BUFFER_ERROR, 536},            //at uart buffer error.
    {AT_RET_BACK_OFF, 537},                     //Back off timer is running
};
/** @} end of group libNEUL_APP_AT_MOD_API */

static const at_ret_errno_map_t g_cms_errno_table[] =
{
    // SMS Errors
    {AT_RET_SMS_OPERATION_NOT_ALLOWED, 302},            // operation not allowed
    {AT_RET_SMS_OPERATION_NOT_SUPPORTED, 303},          // operation not supported
    {AT_RET_SMS_MEMORY_ERROR, 320},                     // memory failure
    {AT_RET_SMS_NO_CNMA_ACKNOWLEDGEMENT_EXPECTED, 340}, //no +CNMA acknowledgement expected
};

#endif
