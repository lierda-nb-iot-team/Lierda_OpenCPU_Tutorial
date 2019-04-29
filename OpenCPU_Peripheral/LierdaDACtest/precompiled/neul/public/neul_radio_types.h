/******************************************************************************
 * @brief    Basic Radio Management Types for Hi21XX
 * Copyright (c) 2016-2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LIB_NEUL_RADIO_TYPES_H_
#define LIB_NEUL_RADIO_TYPES_H_

#include "types.h"
#include "neulfw.h"
#include "neul_error_types.h"
#include "platform_definitions.h"   //needed fore CORES

/** @addtogroup libNEUL_RADIO
 * @{
 * */
/*
 * APN: <Network Identifier>[.<Operator Identifier>]
 * <Network Identifier>: upto 63 octets
 * <Operator Identifier> = mnc<MNC>.mcc<MCC>.gprs
 * <MNC> = 3 digits
 * <MCC> = 3 digits
 */
#define NEUL_MAX_APN_SIZE               101
#define NEUL_CGAUTH_MAX_USERNAME_LEN    60
#define NEUL_CGAUTH_MAX_PASSWORD_LEN    60

#define NEUL_MAX_CID                    10
#define NEUL_NSLPI_UNDEFINED            255
#define NEUL_MAX_PLMN_LIST_NUM          7
#define NEUL_CIPCA_WITHOUT_PDN_VALUE    0xFF
#define NEUL_DATA_SENT_DATA_SEQ_INVALID 0
#define NEUL_NQSOS_MAX_LIST_NUM         256
#define NEUL_NQSOS_SEQ_NUM              32
#define NEUL_MAX_SOCKET_NUM             7
#define NEUL_MIN_SOCKET_SEQ             0
#define MAX_DNS_SERVER_ADDR_NUM         6
#define NEUL_CPSMS_UNUSED_TIME_VALUE    0xFFFF
#define NEUL_EDRX_AND_PTW_INVALID_FALG  0xFF
#define NEUL_CGEQOS_INVALID_QCI         0xFF
#define INVALID_T3324_T3412_EXT_VALUE   0xFFFF

/* MTU sizes
 * This will be replaced by a call to get MTU sizes from the Protocol Core
 */

/* 24.301 6.6.4.2 The recommended maximum size for link MTU is 1358 octets to prevent fragmentation in the backbone network
 * (see 3GPP TS 23.060 [74]). Depending on the network configuration, setting link MTU size to a value larger than 1358 octets
 * could lead to inefficient core network implementation due to fragmentation.
 */
#define NEUL_IP_MTU_SIZE           1358
#define NEUL_NONIP_MTU_SIZE        1358

// Value set to indicate there are currently no power readings (e.g. because we're not on a cell).
#define UE_STATS_INVALID_POWER     MIN_INT16
#define UE_STATS_INVALID_UNIT32    MAX_UINT32
#define UE_STATS_INVALID_UNIT16    MAX_UINT16
#define UE_STATS_INVALID_UNIT8     MAX_UINT8

/**
 * @brief PDN Type: IPv4, IPv6 or Dual
 */
typedef enum
{
    PDN_TYPE_INVALID    = 0x0,
    PDN_TYPE_IPV4       = 0x1,
    PDN_TYPE_IPV6       = 0x2,
    PDN_TYPE_IPV4V6     = 0x3,
    PDN_UNUSED          = 0x4,  // shall be interpreted as "IPv6" if received by the network
    PDN_TYPE_NON_IP     = 0x5
} NEUL_PDN_TYPE;

typedef enum
{
    NEUL_PDP_AUTH_PROTO_NONE    = 0,   // NONE
    NEUL_PDP_AUTH_PROTO_PAP     = 1,   // PAP
    NEUL_PDP_AUTH_PROTO_CHAP    = 2,   // CHAP
} NEUL_PDP_AUTH_PROTO;


typedef enum
{
    NEUL_AUTOCONNECT_FUNCTION,
    NEUL_CR_0354_0338_SCRAMBLING_FUNCTION,
    NEUL_CR_0859_SI_AVOID_FUNCTION,
    NEUL_COMBINE_ATTACH,
    NEUL_CELL_RESELECTION,
    NEUL_ENABLE_BIP,
    NEUL_MULTITONE_FUNCTION, /* When writing, use user preference;
                                when reading, return true only if user allows MT and HW supports it for current band */
    NEUL_NAS_SIM_POWER_SAVING_ENABLE,
    NEUL_BARRING_RELEASE_DELAY,
    NEUL_RELEASE_VERSION,
    NEUL_RPM_FUNCTION,
    NEUL_SYNC_TIME_PERIOD,
    NEUL_IPV6_GET_PREFIX_TIME,
    NEUL_NB_CATEGORY,
    NEUL_ENABLE_RAI,
    NEUL_HEAD_COMPRESS,
    NEUL_RLF_UPDATE,
    NEUL_CONNECTION_REEST,
    NEUL_TWO_HARQ,
    NEUL_PCO_TYPE,
    NEUL_T3324_T3412_EXT_CHANGE_REPORT,
    NEUL_NON_IP_NO_SMS_ENABLE,
    NEUL_SUPPORT_SMS,

    NEUL_NCONFIG_FUNCTION_NUM,
} NEUL_NCONFIG_FUNCTION;

typedef struct
{
    uint8 plmn[3];
    uint8 plmn_state;
} plmn_info;

#define UE_CELL_INFO_VERSION 2
#define UE_MAX_CELL_INFO_NUM 10

typedef struct {
    uint8  version;
    bool   primary_cell:1;
    bool   valid:1;
    uint16 pci;
    uint32 earfcn;
    int16  rsrp;
    int16  rsrq;
    int16  rssi;
    int16  snr;
} ue_cell_info;

/* Make sure this is incremented for any change to structure */
#define PDP_CONTEXT_VERSION 2
typedef struct
{
    uint8           version;            // structure version
    uint8           cid;
    uint8           d_comp;
    uint8           h_comp;
    NEUL_PDN_TYPE   pdp_type;
    bool            emergency;          // Not Used
    uint8           addr_alloc;         // Not Used
    uint8           nslpi;
    uint8           secure_pco;
    uint8           *apn;
    uint8           apn_nw[NEUL_MAX_APN_SIZE];
    uint8           state;
} pdp_context;

/*
 * ue_stats structure.
 * This structure is versioned. The version number must be checked before use. The
 * structure is inly valid if the version and UE_STATS_VERSION match.
 */

/* Make sure this is incremented for any change to structure, and is in sync with ue_stats.c */
#define UE_STATS_VERSION 8

typedef struct  {
    uint16  version;             // structure version: will increment on any change.
    uint16  pci;                 // physical cell id
    int32   signal_power;        // Signal power: <signal power in centibels>
    int32   total_power;         // Total power: <total power in centibels>
    int32   tx_power;            // TX power: <current Tx power level in centibels>
    uint32  tx_time;             // TX time<total Tx time since last reboot in millisecond>
    uint32  rx_time;             // RX time: <total Rx time since last reboot in millisecond>
    uint32  cell_id;             // Cell ID:<last cell ID>
    uint8   dl_mcs;              // DL MCS: <last DL MCS value>
    uint8   ul_mcs;              // UL MCS: <last UL MCS value>
    uint8   dci_mcs;             // DCI_MCS: <last DCI MCS value>
    uint8   current_ecl;         // Current ECL: <Current Enhanced Coverage Level (0..2)>
    int32   snr;                 // snr
    uint32  earfcn;              // earfcn of serving cell
    int32   rsrq;               // rsrq
    int16   operation_mode;     // operator mode for SlB1
    uint8   current_band;       // band of serving cell
    uint32  rlc_ul_bler;        // RLC UL throughput bler
    uint32  rlc_dl_bler;        // RLC DL throughput bler
    uint32  mac_ul_bler;        // MAC UL throughput bler
    uint32  mac_dl_bler;        // MAC DL throughput bler
    uint32  ll1_transmitted_bytes;
    uint32  ll1_received_bytes;
    uint16  total_tb_tx;
    uint16  total_tb_rx;
    uint16  total_tb_retx;
    uint16  total_harq_nack_received;
    uint32  rlc_ul_data_rate;   // RLC UL throughput
    uint32  rlc_dl_data_rate;   // RLC DL throughput
    uint32  mac_ul_data_rate;   // MAC UL throughput
    uint32  mac_dl_data_rate;   // MAC DL throughput
} ue_stats;

typedef enum
{
    PLMN_MODE_AUTOMATIC = 0,
    PLMN_MODE_MANUAL,
    PLMN_MODE_DEREGISTER,
    PLMN_MODE_SET_FORMAT,
    PLMN_MODE_REGISTER_MANUAL_AUTO
} PLMN_MODE;

typedef enum
{
   EMM_CAUSE_INFO_IMSI_UNKNOWN_IN_HSS                              = 2,
   EMM_CAUSE_INFO_ILLEGAL_UE                                       = 3,
   EMM_CAUSE_INFO_IMEI_NOT_ACCEPTED                                = 5,
   EMM_CAUSE_INFO_ILLEGAL_ME                                       = 6,
   EMM_CAUSE_INFO_EPS_SERVICES_NOT_ALLOWED                         = 7,
   EMM_CAUSE_INFO_EPS_AND_NON_EPS_SERVICES_NOT_ALLOWED             = 8,
   EMM_CAUSE_INFO_UE_ID_NOT_DERIVED_BY_NETWORK                     = 9,
   EMM_CAUSE_INFO_IMPLICITLY_DETACHED                              = 10,
   EMM_CAUSE_INFO_PLMN_NOT_ALLOWED                                 = 11,
   EMM_CAUSE_INFO_TRACKING_AREA_NOT_ALLOWED                        = 12,
   EMM_CAUSE_INFO_ROAMING_NOT_ALLOWED_IN_THIS_TAI                  = 13,
   EMM_CAUSE_INFO_EPS_SERVICES_NOT_ALLOWED_IN_THIS_PLMN            = 14,
   EMM_CAUSE_INFO_NO_SUITABLE_CELLS_IN_TAI                         = 15,
   EMM_CAUSE_INFO_MSC_TEMPORARILY_NOT_ACCEPTABLE                   = 16,
   EMM_CAUSE_INFO_NETWORK_FAILURE                                  = 17,
   EMM_CAUSE_INFO_CS_DOMAIN_NOT_AVAILABLE                          = 18,
   EMM_CAUSE_INFO_ESM_FAILURE                                      = 19,
   EMM_CAUSE_INFO_MAC_FAILURE                                      = 20,
   EMM_CAUSE_INFO_SYNC_FAILURE                                     = 21,
   EMM_CAUSE_INFO_CONGESTION                                       = 22,
   EMM_CAUSE_INFO_UE_SECURITY_CAPABILITIES_MISMATCH                = 23,
   EMM_CAUSE_INFO_UE_SECURITY_MODE_REJECTED_UNSPECIFIED            = 24,
   EMM_CAUSE_INFO_NOT_AUTHORISED_FOR_THIS_CSG                      = 25,
   EMM_CAUSE_INFO_NON_EPS_AUTH_UNACCEPTABLE                        = 26,
   EMM_CAUSE_INFO_REQUESTED_SERVICE_NOT_AUTHORISED_IN_THIS_PLMN    = 35,
   EMM_CAUSE_INFO_CS_SERVICES_TEMPORARILY_NOT_AVAILABLE            = 39,
   EMM_CAUSE_INFO_NO_EPS_BEARER_CONTEXT_ACTIVATED                  = 40,
   EMM_CAUSE_INFO_SEVERE_NETWORK_FAILURE                           = 42,
   EMM_CAUSE_INFO_SEMANTICALLY_INCORRECT_MSG                       = 95,
   EMM_CAUSE_INFO_INVALID_MANDATORY_INFORMATION                    = 96,
   EMM_CAUSE_INFO_MSG_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED         = 97,
   EMM_CAUSE_INFO_MSG_TYPE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE      = 98,
   EMM_CAUSE_INFO_IE_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED          = 99,
   EMM_CAUSE_INFO_CONDITIONAL_IE_ERROR                             = 100,
   EMM_CAUSE_INFO_MSG_NOT_COMPATIBLE_WITH_PROTOCOL_STATE           = 101,
   EMM_CAUSE_INFO_UNSPECIFIED_PROTOCOL_ERROR                       = 102,
   EMM_CAUSE_INFO_PROTOCOL_ERROR_UNSPECIFIED                       = 111,
   EMM_CAUSE_INFO_UNKNOWN                                          = 255  /* this is not in spec */
} EMM_CAUSE_INFO;

typedef enum
{
    PIN_COMMAND_VERIFY = 0,
    PIN_COMMAND_CHANGE,
    PIN_COMMAND_ENABLE,
    PIN_COMMAND_DISABLE,
    PIN_COMMAND_UNBLOCK
} PIN_COMMAND;

typedef enum
{
    DNS_SERVER_IPV4_ADDR_REQUEST,
    DNS_SERVER_IPV6_ADDR_REQUEST,
    NUM_PDP_CONTEXT_DYNAMIC_PARAM
} PDP_CONTEXT_DYNAMIC_PARAM;

typedef enum
{
    NEUL_CPSMS_MODE_DISABLE,
    NEUL_CPSMS_MODE_ENABLE,
    NEUL_CPSMS_MODE_DISABLE_AND_RESET
}NEUL_CPSMS_MODE;

typedef enum
{
    NEUL_CEDRXS_PTW_MODE_DISABLE,
    NEUL_CEDRXS_PTW_MODE_ENABLE,
    NEUL_CEDRXS_PTW_MODE_ENABLE_UNSOLICITED,
    NEUL_CEDRXS_PTW_MODE_DISABLE_AND_RESET,
}NEUL_CEDRXS_PTW_MODE;

typedef enum
{
    CIOT_EPS_OPT_DISABLE_REPORTING = 0,
    CIOT_EPS_OPT_ENABLE_REPORTING,
    CIOT_EPS_OPT_DISABLE_REPORTING_AND_RESET = 3,
}CIOT_EPS_OPT_REPORTING;

typedef enum
{
    CIOT_EPS_OPT_NO_SUPPORT = 0,
    CIOT_EPS_OPT_SUPPORT_CP,
    CIOT_EPS_OPT_SUPPORT_UP,
    CIOT_EPS_OPT_SUPPORT_CP_UP,
    CIOT_EPS_OPT_SUPPORT_INVALID,
}CIOT_EPS_OPT_SUPPORT;

typedef enum
{
    CIOT_EPS_OPT_NO_PREFERENCE = 0,
    CIOT_EPS_OPT_PREFERENCE_CP,
    CIOT_EPS_OPT_PREFERENCE_UP,
    CIOT_EPS_OPT_PREFERENCE_INVALID,
}CIOT_EPS_OPT_PREFERENCE;

typedef struct  {
    bool            remote_addr_subnet_mask_present;
    bool            protnum_nexthead_present;
    bool            local_port_range_present;
    bool            remote_port_range_present;
    bool            spi_present;
    bool            service_type_present;
    bool            flow_label_present;
    bool            direction_present;

    uint16          cid;
    uint8           pfi;
    uint8           evaluation_precedence;
    uint8           addr_subnet_type;
    uint8           remote_addr[16];
    uint8           subnet_mask_addr[16];
    uint8           protnum_nexthead;
    uint16          local_port_range[2];
    uint16          remote_port_range[2];
    uint32          spi;
    uint8           service_type[2];
    uint32          flow_label;
    uint8           direction;
}tft_context;

typedef enum
{
    TIME_UPDATE_MODE_LOCAL,
    TIME_UPDATE_MODE_NETWORK,
} TIME_UPDATE_MODE;

typedef enum
{
    PDP_CONTEXT_REPORT_DEACTIVATE_RESULT,
    PDP_CONTEXT_REPORT_ACTIVATE_RESULT
}PDP_CONTEXT_REPORT_RESULT_STATE;

typedef enum
{
    PDP_CONTEXT_REPORT_RESULT_OK,
    PDP_CONTEXT_REPORT_RESULT_NO_CONTEXT_DEFINED,
    PDP_CONTEXT_REPORT_RESULT_CONTEXT_NOT_ACTIVE,
    PDP_CONTEXT_REPORT_RESULT_CONTEXT_ALREADY_ACTIVE,
    PDP_CONTEXT_REPORT_RESULT_RESOURCE_ERROR,
    PDP_CONTEXT_REPORT_RESULT_LOCAL_REJECT,
    PDP_CONTEXT_REPORT_RESULT_APN_ERROR,
    PDP_CONTEXT_REPORT_RESULT_APN_BACKOFF_RUNNING,
    PDP_CONTEXT_REPORT_RESULT_IPV4_ONLY,
    PDP_CONTEXT_REPORT_RESULT_IPV6_ONLY,
    PDP_CONTEXT_REPORT_RESULT_IP_ONLY,
    PDP_CONTEXT_REPORT_RESULT_NON_IP_ONLY,
    PDP_CONTEXT_REPORT_RESULT_SINGLE_IP_ONLY,
    PDP_CONTEXT_REPORT_RESULT_SERVICE_ERROR,
    PDP_CONTEXT_REPORT_RESULT_MAX_CONN_REACHED,
    PDP_CONTEXT_REPORT_RESULT_REACTIVATION_REQUESTED,
    PDP_CONTEXT_REPORT_RESULT_LAST_PDN_DISC_NOT_ALLOWED,
    PDP_CONTEXT_REPORT_RESULT_FAILED,
    PDP_CONTEXT_REPORT_RESULT_NSLPI_OVERRIDE_NOT_ALLOWED,
    PDP_CONTEXT_REPORT_RESULT_ATTACHING,
}PDP_CONTEXT_REPORT_RESULT;

typedef enum
{
    NEUL_UICC_FREE,
    NEUL_UICC_RESTART,
} NEUL_UICC_STATUS;

#define NEUL_MAX_PATH_SIZE        10        //5 levels file path * 2
#define NEUL_MAX_CRSM_DATA_SIZE   255
typedef struct
{
    bool            p1_p2_p3_valid;

    uint8           type;
    uint8           path_len;
    uint8           data_len;
    uint16          p1;
    uint16          p2;
    uint16          p3;
    uint16          file_id;
    uint8           path_id[NEUL_MAX_PATH_SIZE];
    uint8           data[NEUL_MAX_CRSM_DATA_SIZE];
} crsm_command;

typedef enum
{
    SOCKET_OR_CID_STATUS_AVAILABLE,
    SOCKET_OR_CID_STATUS_NOT_EXIST,
    SOCKET_OR_CID_STATUS_FLOW_CONTROL,
    SOCKET_OR_CID_STATUS_BACK_OFF,
}SOCKET_OR_CID_STATUS;

/** @} end of group libNEUL_RADIO */

#endif /* LIB_NEUL_RADIO_TYPES_H_ */
