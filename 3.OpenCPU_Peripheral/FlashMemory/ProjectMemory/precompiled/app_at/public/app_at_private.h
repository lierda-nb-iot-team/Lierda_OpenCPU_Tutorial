/******************************************************************************
 * @brief    AT Command private functions.
 * Portions copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef    _APP_AT_PRIVATE_H_
#define    _APP_AT_PRIVATE_H_

#include "neul_error_types.h"
#include "neul_network.h"
#include "neul_sms_messaging.h"

/** @addtogroup libNEUL_APP_AT_INT
 * @{
 * */

typedef enum
{
    AT_COPS_MODE_AUTOMATIC = 0,
    AT_COPS_MODE_MANUAL,
    AT_COPS_MODE_DEREGISTER,
    AT_COPS_MODE_SET_FORMAT,
    AT_COPS_MODE_MANUAL_THEN_AUTOMATIC
}AT_COPS_MODE;

typedef enum
{
    AT_CFUN_MIN = 0,
    AT_CFUN_FULL = 1,
    AT_CFUN_DISABLE_TXRX = 4
}AT_CFUN;

#define AT_MAX_PDP_TYPE_SIZE    16
#define AT_MAX_PDP_ADDR_SIZE    33
#define AT_MAX_CID              10

typedef enum
{
    AT_HEADER_COMPRESSION_OFF = 0,          //off
    AT_HEADER_COMPRESSION_RFC1144,
    AT_HEADER_COMPRESSION_RFC2507,
    AT_HEADER_COMPRESSION_RFC3095
} AT_HEADER_COMPRESSION;

typedef enum
{
    AT_DATA_COMPRESSION_OFF = 0,    //off
    AT_DATA_COMPRESSION_V42BIS
}AT_DATA_COMPRESSION;

typedef enum
{
    AT_NON_IP_DATA_REPORT_MODE_DISABLE,
    AT_NON_IP_DATA_REPORT_MODE_ENABLE,
}AT_REPORT_NON_IP_DATA_MODE;

/**
 * Gets the IP address associated with a cid
 * @param cid The cid whoes IP addresses we want to find
 * @param ifa List of address
 * @param cgaddr_len The length of the multi-lined return string
 * @param cgaddr The buffer to hold the string
 * @return AT_SUCCESS if good, anything else for failure
 */
uint8 get_cgpaddr_cid(int16 cid, struct ifaddrs *ifa, uint32 *cgaddr_len, char *cgaddr, uint16 max_cgaddr_size);

/**
 * Gets a list of defined cids in the format "+CGPADDR:(cid_0,cid_1,...)"
 * @param cgaddr_len Length of the string cgaddr
 * @param cgaddr The string with the result
 */
void get_cgpaddr_cid_range(uint32 *cgaddr_len, char *cgaddr, uint8 max_cgaddr_size);

NEUL_RET plmn_select(uint16 plmn_mode, uint16 format, uint16 buffer_length, uint8 * buffer);

AT_RET at_pre_process_sms_data(uint8 * p_str);

AT_RET at_process_sms_data(const uint8 *p_str);

void set_at_sms_msg_type(AT_SMS_MESSAGE type);

void set_wait_for_sms_data(void);

void clear_wait_for_sms_data(void);

bool get_wait_for_sms_data(void);

void at_set_crtdcp_mode(AT_REPORT_NON_IP_DATA_MODE mode);

void at_query_crtdcp_mode(AT_REPORT_NON_IP_DATA_MODE *mode);

void at_set_non_ip_data_report_mode(AT_REPORT_NON_IP_DATA_MODE mode);

AT_REPORT_NON_IP_DATA_MODE at_get_non_ip_data_report_mode(void);

void set_sms_len(uint16 len);

void set_sms_uart_pdu_len(uint16 len);

uint16 get_sms_uart_pdu_len(void);

void set_report_type(NEUL_SMS_RECEIVE_PDU_RES_TYPE type);

void set_is_pdu(void);

void clear_is_pdu(void);

bool get_is_pdu(void);

bool get_at_cmd_in_progress(void);

bool get_at_processing_cmd_abortable(void);

bool get_at_blocking_at_command_protected(void);

AT_RET app_at_get_non_ip_mtu_size(uint16 *non_ip_mtu_size);
AT_RET app_at_min_ip_mtu_from_active_cids(uint16 *mtu);
void app_at_ip_mtu_init(void);
void psm_status_callback(uint8 psm_status);
AT_RET get_ip_addr(uint8 cid, NEUL_PDN_TYPE ip_type, char *addr, uint8 max_addr_size);

void at_non_ip_sent_callback(uint16 data_seq, bool data_status);

/** @} end of group libNEUL_APP_AT_INT */

#endif
