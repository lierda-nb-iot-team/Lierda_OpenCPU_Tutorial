/******************************************************************************
 * @brief    RPC auto generated header
 * Copyright (c) 2018 NEUL LIMITED
 ******************************************************************************/

#ifndef SRC_LIB_RPC_INTERFACE_PRIVATE_RPC_GENERATED_H
#define SRC_LIB_RPC_INTERFACE_PRIVATE_RPC_GENERATED_H

#include "platform_definitions.h"	//needed for CORES
#include "core.h"
#include "neulfw.h"
#include "rpc_interface.h"

typedef enum {
    RPC_APPLICATION_TO_SECURITY_GET_DIEID,
    RPC_APPLICATION_TO_SECURITY_GET_SECURITY_RPC_VERSION,
    RPC_APPLICATION_TO_SECURITY_SET_VDD_IO_LEVEL,
    RPC_APPLICATION_TO_SECURITY_SET_SECURITY_LOG_LEVEL,
    RPC_APPLICATION_TO_SECURITY_GET_SECURITY_LOG_LEVEL,
    RPC_APPLICATION_TO_SECURITY_KV_GET,
    RPC_APPLICATION_TO_SECURITY_KV_ERASE_ALL,
    RPC_APPLICATION_TO_SECURITY_SET_ID,
    RPC_APPLICATION_TO_SECURITY_SET_ID_PERMANENCE,
    RPC_APPLICATION_TO_SECURITY_SYSTEM_REBOOT,
    RPC_APPLICATION_TO_SECURITY_GET_ID,
    RPC_APPLICATION_TO_SECURITY_UPDATE_PACKAGE_PARSE_REQ,
    RPC_APPLICATION_TO_SECURITY_UPDATE_PACKAGE_PROCESS_REQ,
    RPC_APPLICATION_TO_SECURITY_UPDATE_PACKAGE_GET_PACKAGE_VERSION_REQ,
    RPC_APPLICATION_TO_SECURITY_UPDATE_PACKAGE_GET_PACKAGE_NAME_REQ,
    RPC_APPLICATION_TO_SECURITY_FIRMWARE_UPGRADE_REQ,
    RPC_APPLICATION_TO_SECURITY_UPDATE_PACKAGE_DISCARD,
    RPC_APPLICATION_TO_SECURITY_IMAGE_LOADER_READY_IND,
    RPC_APPLICATION_TO_SECURITY_UPDATE_PACKAGE_DATA_CNF,
    RPC_APPLICATION_TO_SECURITY_UPDATE_PACKAGE_FLASH_ERASE,
    RPC_APPLICATION_TO_SECURITY_UPDATE_PACKAGE_FLASH_WRITE,
    RPC_APPLICATION_TO_SECURITY_GET_FIRMWARE_VERSION,
    RPC_APPLICATION_TO_SECURITY_GET_SSB_VERSION,
    RPC_APPLICATION_TO_SECURITY_GET_RFCONFIG_VERSION,
    RPC_APPLICATION_TO_SECURITY_GET_TEMP_COEFFICIENT,
    RPC_APPLICATION_TO_SECURITY_REGISTER_KVCACHE,
    RPC_APPLICATION_TO_SECURITY_KV_QUEUE_CACHE_FOR_WRITE,
    RPC_APPLICATION_TO_SECURITY_GET_RANDOM,
    RPC_APPLICATION_TO_SECURITY_GET_UPDATE_RESULT,
    RPC_APPLICATION_TO_SECURITY_GET_UPDATE_STATUS,
    RPC_APPLICATION_TO_SECURITY_RESET_UPDATE_RESULT,
    RPC_APPLICATION_TO_SECURITY_IFLOG_CACHE_REGISTER,
    RPC_APPLICATION_TO_SECURITY_IFLOG_IFLASH_WRITE,
    RPC_APPLICATION_TO_SECURITY_IFLOG_IFLASH_READ,
    RPC_APPLICATION_TO_SECURITY_UPDATE_PACKAGE_ALLOCATE_FLASH,
    RPC_APPLICATION_TO_SECURITY_UPDATE_PACKAGE_GET_AVAILABLE_FLASH,
    RPC_APPLICATION_TO_SECURITY_APP_FLASH_ALLOC,
    RPC_APPLICATION_TO_SECURITY_APP_FLASH_FREE,
    RPC_APPLICATION_TO_SECURITY_APP_FLASH_ERASE_PAGES,
    RPC_APPLICATION_TO_SECURITY_APP_FLASH_WRITE_REQUEST,
    RPC_APPLICATION_TO_SECURITY_APP_FLASH_AVAIL,
    RPC_APPLICATION_TO_SECURITY_APP_FLASH_READ,
    RPC_COMMANDS_APPLICATION_TO_SECURITY_MAX_COMMANDS
} RPC_APPLICATION_TO_SECURITY_COMMANDS;

typedef enum {
    RPC_APPLICATION_TO_PROTOCOL_GET_PROTOCOL_RPC_VERSION,
    RPC_APPLICATION_TO_PROTOCOL_SET_PROTOCOL_LOG_LEVEL,
    RPC_APPLICATION_TO_PROTOCOL_GET_PROTOCOL_LOG_LEVEL,
    RPC_APPLICATION_TO_PROTOCOL_GETIFADDR,
    RPC_APPLICATION_TO_PROTOCOL_SET_EARFCN_RANGE,
    RPC_APPLICATION_TO_PROTOCOL_CLEAR_STORED_EARFCN,
    RPC_APPLICATION_TO_PROTOCOL_SET_BAND,
    RPC_APPLICATION_TO_PROTOCOL_GET_BAND,
    RPC_APPLICATION_TO_PROTOCOL_GET_SUPPORTED_BANDS,
    RPC_APPLICATION_TO_PROTOCOL_EXECUTE_RADIOTEST,
    RPC_APPLICATION_TO_PROTOCOL_EXECUTE_PLMN_SELECT,
    RPC_APPLICATION_TO_PROTOCOL_GET_PLMN_STATUS,
    RPC_APPLICATION_TO_PROTOCOL_GET_AVAILABLE_PLMN,
    RPC_APPLICATION_TO_PROTOCOL_START_RACH,
    RPC_APPLICATION_TO_PROTOCOL_SET_ATTACH_STATE,
    RPC_APPLICATION_TO_PROTOCOL_GET_IMSI,
    RPC_APPLICATION_TO_PROTOCOL_GET_REGISTRATION_STATUS,
    RPC_APPLICATION_TO_PROTOCOL_GET_CONNECTION_STATUS,
    RPC_APPLICATION_TO_PROTOCOL_SET_PDP_CONTEXT,
    RPC_APPLICATION_TO_PROTOCOL_DELETE_PDP_CONTEXT,
    RPC_APPLICATION_TO_PROTOCOL_GET_PDP_CONTEXT,
    RPC_APPLICATION_TO_PROTOCOL_SET_PDP_CONTEXT_AUTH_PARAM,
    RPC_APPLICATION_TO_PROTOCOL_GET_PDP_CONTEXT_AUTH_PARAM,
    RPC_APPLICATION_TO_PROTOCOL_SET_NCONFIG,
    RPC_APPLICATION_TO_PROTOCOL_GET_NCONFIG,
    RPC_APPLICATION_TO_PROTOCOL_SET_NTEST,
    RPC_APPLICATION_TO_PROTOCOL_GET_NTEST,
    RPC_APPLICATION_TO_PROTOCOL_QUERY_UE_STATS,
    RPC_APPLICATION_TO_PROTOCOL_SET_UE_CFUN,
    RPC_APPLICATION_TO_PROTOCOL_READ_SERVICE_STATUS,
    RPC_APPLICATION_TO_PROTOCOL_READ_UE_CFUN,
    RPC_APPLICATION_TO_PROTOCOL_GET_DEFINED_CIDS,
    RPC_APPLICATION_TO_PROTOCOL_ALLOCATE_SOCKET,
    RPC_APPLICATION_TO_PROTOCOL_CLOSE_SOCKET,
    RPC_APPLICATION_TO_PROTOCOL_NEUL_BIND,
    RPC_APPLICATION_TO_PROTOCOL_SENDTO,
    RPC_APPLICATION_TO_PROTOCOL_GET_PENDING_DATA_SEQS,
    RPC_APPLICATION_TO_PROTOCOL_SOCKET_SEND,
    RPC_APPLICATION_TO_PROTOCOL_SOCKET_CONNECT,
    RPC_APPLICATION_TO_PROTOCOL_SET_PING,
    RPC_APPLICATION_TO_PROTOCOL_SET_SYSTEM_TIME_FROM_APPS,
    RPC_APPLICATION_TO_PROTOCOL_SET_TIME_UPDATE_MODE,
    RPC_APPLICATION_TO_PROTOCOL_GET_TIME_UPDATE_MODE,
    RPC_APPLICATION_TO_PROTOCOL_RF_CONFIG_CTRL,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_MEAS_RSSI,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_READ_MIPI_WORD,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_WRITE_MIPI_WORD,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_TX_TONE,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_SET_TX_GAINS,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_GET_TX_GAINS,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_SET_RIO_V,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_SET_GPIO,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_GET_GPIO,
    RPC_APPLICATION_TO_PROTOCOL_FLUSH_UL_QUEUE,
    RPC_APPLICATION_TO_PROTOCOL_PREPARE_FOR_POWERDOWN,
    RPC_APPLICATION_TO_PROTOCOL_PDP_ACTIVATE_REQ,
    RPC_APPLICATION_TO_PROTOCOL_PDP_DEACTIVATE_REQ,
    RPC_APPLICATION_TO_PROTOCOL_SMS_SET_SHORT_MESSAGE_SERVICE,
    RPC_APPLICATION_TO_PROTOCOL_SMS_READ_SHORT_MESSAGE_SERVICE,
    RPC_APPLICATION_TO_PROTOCOL_SMS_SET_MORE_MESSAGE_TO_SEND,
    RPC_APPLICATION_TO_PROTOCOL_SMS_READ_MORE_MESSAGE_TO_SEND,
    RPC_APPLICATION_TO_PROTOCOL_SMS_SET_SHORT_MESSAGE_SERVICE_ADDRESS,
    RPC_APPLICATION_TO_PROTOCOL_SMS_READ_SHORT_MESSAGE_SERVICE_ADDRESS,
    RPC_APPLICATION_TO_PROTOCOL_SMS_SEND_SHORT_MESSAGE,
    RPC_APPLICATION_TO_PROTOCOL_SMS_SEND_COMMAND,
    RPC_APPLICATION_TO_PROTOCOL_SMS_SET_NEW_MSG_ACK,
    RPC_APPLICATION_TO_PROTOCOL_GET_CNMA_ACKNOWLEDGEMENT_EXPECTED,
    RPC_APPLICATION_TO_PROTOCOL_GET_ICCID,
    RPC_APPLICATION_TO_PROTOCOL_SET_POWER_SAVING_MODE,
    RPC_APPLICATION_TO_PROTOCOL_GET_POWER_SAVING_MODE,
    RPC_APPLICATION_TO_PROTOCOL_SET_EDRXS_AND_PTW,
    RPC_APPLICATION_TO_PROTOCOL_GET_EDRXS_AND_PTW,
    RPC_APPLICATION_TO_PROTOCOL_GET_CELL_INFO,
    RPC_APPLICATION_TO_PROTOCOL_GET_EXTENDED_ERROR_CAUSE,
    RPC_APPLICATION_TO_PROTOCOL_GET_EDRXRDP,
    RPC_APPLICATION_TO_PROTOCOL_GET_CHIPINFO,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_TX_VERIFY,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_RX_VERIFY,
    RPC_APPLICATION_TO_PROTOCOL_NONIP_SENDTO,
    RPC_APPLICATION_TO_PROTOCOL_GET_MTU_SIZE,
    RPC_APPLICATION_TO_PROTOCOL_EXECUTE_PIN_COMMAND,
    RPC_APPLICATION_TO_PROTOCOL_GET_APN_RATE_CONTROL_CONTEXT,
    RPC_APPLICATION_TO_PROTOCOL_SET_POWER_BAND_CLASS,
    RPC_APPLICATION_TO_PROTOCOL_GET_POWER_BAND_CLASS,
    RPC_APPLICATION_TO_PROTOCOL_SET_INITIAL_PDP_CONTEXT,
    RPC_APPLICATION_TO_PROTOCOL_GET_INITIAL_PDP_CONTEXT,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_TX_TEST,
    RPC_APPLICATION_TO_PROTOCOL_ABORT_PROCESSING_COMMAND,
    RPC_APPLICATION_TO_PROTOCOL_AIO_MANAGER_CLAIM_RESOURCE,
    RPC_APPLICATION_TO_PROTOCOL_AIO_MANAGER_FREE_RESOURCE,
    RPC_APPLICATION_TO_PROTOCOL_SET_NETWORK_CONFIG,
    RPC_APPLICATION_TO_PROTOCOL_RAI_REQ,
    RPC_APPLICATION_TO_PROTOCOL_GET_DNS_SERVER_IP_ADDRESS,
    RPC_APPLICATION_TO_PROTOCOL_SET_PDP_CONTEXT_DYNAMIC_PARAM_REQUEST_STATE,
    RPC_APPLICATION_TO_PROTOCOL_GET_PDP_CONTEXT_DYNAMIC_PARAM_REQUEST_STATE,
    RPC_APPLICATION_TO_PROTOCOL_CALIBRATE_TEMPERATURE,
    RPC_APPLICATION_TO_PROTOCOL_OPEN_LOGICAL_CHANNEL,
    RPC_APPLICATION_TO_PROTOCOL_CLOSE_LOGICAL_CHANNEL,
    RPC_APPLICATION_TO_PROTOCOL_GENERIC_UICC_LOGICAL_CHANNEL_ACCESS,
    RPC_APPLICATION_TO_PROTOCOL_PDP_MODIFY_REQ,
    RPC_APPLICATION_TO_PROTOCOL_SET_CIOT_OPT,
    RPC_APPLICATION_TO_PROTOCOL_GET_CIOT_OPT,
    RPC_APPLICATION_TO_PROTOCOL_SET_QOS_REQ,
    RPC_APPLICATION_TO_PROTOCOL_GET_QOS,
    RPC_APPLICATION_TO_PROTOCOL_DELETE_QOS,
    RPC_APPLICATION_TO_PROTOCOL_DELETE_TFT_REQ,
    RPC_APPLICATION_TO_PROTOCOL_SET_TFT_REQ,
    RPC_APPLICATION_TO_PROTOCOL_GET_TFT_CONTEXT,
    RPC_APPLICATION_TO_PROTOCOL_DRIVER_ADC_INIT,
    RPC_APPLICATION_TO_PROTOCOL_DRIVER_ADC_DEINIT,
    RPC_APPLICATION_TO_PROTOCOL_DRIVER_ADC_GET_CALIBRATED_MAX_VOLTAGE_MV,
    RPC_APPLICATION_TO_PROTOCOL_DRIVER_ADC_READ_UV,
    RPC_APPLICATION_TO_PROTOCOL_DRIVER_ADC_READ_RAW,
    RPC_APPLICATION_TO_PROTOCOL_DRIVER_ADC_SET_RANGE,
    RPC_APPLICATION_TO_PROTOCOL_DRIVER_ADC_CALIBRATE_FOR_VOLTAGE,
    RPC_APPLICATION_TO_PROTOCOL_DRIVER_ADC_CALIBRATE_CALCULATE,
    RPC_APPLICATION_TO_PROTOCOL_DRIVER_ADC_FIND_TRIM_VALUES,
    RPC_APPLICATION_TO_PROTOCOL_DRIVER_ADC_SET_READ_WITHIN_TIME,
    RPC_APPLICATION_TO_PROTOCOL_GET_PIN_STATE,
    RPC_APPLICATION_TO_PROTOCOL_GET_PIN_REMAINING_RETRIES,
    RPC_APPLICATION_TO_PROTOCOL_UICC_STATUS_CONTROL,
    RPC_APPLICATION_TO_PROTOCOL_RESTRICTED_SIM_ACCESS,
    RPC_APPLICATION_TO_PROTOCOL_GET_CID_STATUS,
    RPC_APPLICATION_TO_PROTOCOL_GET_SOCKET_STATUS,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_TX_CALIST,
    RPC_APPLICATION_TO_PROTOCOL_RADIO_CONFIG_RX_CALIST,
    RPC_COMMANDS_APPLICATION_TO_PROTOCOL_MAX_COMMANDS
} RPC_APPLICATION_TO_PROTOCOL_COMMANDS;

typedef enum {
    RPC_SECURITY_TO_APPLICATION_GET_APPS_RPC_VERSION,
    RPC_SECURITY_TO_APPLICATION_UPDATE_PACKAGE_PARSE_CNF,
    RPC_SECURITY_TO_APPLICATION_UPDATE_PACKAGE_PROCESS_CNF,
    RPC_SECURITY_TO_APPLICATION_UPDATE_PACKAGE_GET_PACKAGE_VERSION_CNF,
    RPC_SECURITY_TO_APPLICATION_UPDATE_PACKAGE_GET_PACKAGE_NAME_CNF,
    RPC_SECURITY_TO_APPLICATION_UPDATE_PACKAGE_DATA_REQ,
    RPC_SECURITY_TO_APPLICATION_UPDATE_PACKAGE_FLASH_ERASE_DONE,
    RPC_SECURITY_TO_APPLICATION_UPDATE_PACKAGE_FLASH_WRITE_DONE,
    RPC_SECURITY_TO_APPLICATION_KV_APPS_CACHE_FLUSHED,
    RPC_SECURITY_TO_APPLICATION_APP_FLASH_ERASE_RESPONSE,
    RPC_SECURITY_TO_APPLICATION_APP_FLASH_WRITE_RESPONSE,
    RPC_COMMANDS_SECURITY_TO_APPLICATION_MAX_COMMANDS
} RPC_SECURITY_TO_APPLICATION_COMMANDS;

typedef enum {
    RPC_PROTOCOL_TO_APPLICATION_GET_APPS_RPC_VERSION,
    RPC_PROTOCOL_TO_APPLICATION_GET_PLMN_RESULTS_IND,
    RPC_PROTOCOL_TO_APPLICATION_ATTACH_STATUS_SET_RESULT_IND,
    RPC_PROTOCOL_TO_APPLICATION_PLMN_SELECT_RESULT_IND,
    RPC_PROTOCOL_TO_APPLICATION_REGISTRATION_STATUS_IND,
    RPC_PROTOCOL_TO_APPLICATION_CONNECTION_STATUS_IND,
    RPC_PROTOCOL_TO_APPLICATION_SOCKET_DATA_SENT,
    RPC_PROTOCOL_TO_APPLICATION_NON_IP_DATA_SENT,
    RPC_PROTOCOL_TO_APPLICATION_IP_ADDRESS_CHANGED,
    RPC_PROTOCOL_TO_APPLICATION_RECVFROM,
    RPC_PROTOCOL_TO_APPLICATION_SOCKET_RECV,
    RPC_PROTOCOL_TO_APPLICATION_SOCKET_NOTIFY,
    RPC_PROTOCOL_TO_APPLICATION_PING_IND,
    RPC_PROTOCOL_TO_APPLICATION_CFUN_RESULT_IND,
    RPC_PROTOCOL_TO_APPLICATION_SMS_MGS_RESULT_IND,
    RPC_PROTOCOL_TO_APPLICATION_SMS_CMD_RESULT_IND,
    RPC_PROTOCOL_TO_APPLICATION_CURRENT_TIME_IND,
    RPC_PROTOCOL_TO_APPLICATION_RF_CALIBRATION_RTC_IND,
    RPC_PROTOCOL_TO_APPLICATION_SERVICE_RECOVERY,
    RPC_PROTOCOL_TO_APPLICATION_PDP_ACT_OR_DEACT_RESULT_IND,
    RPC_PROTOCOL_TO_APPLICATION_EDRX_CHANGED_IND,
    RPC_PROTOCOL_TO_APPLICATION_RADIOTEST_RESPONSE,
    RPC_PROTOCOL_TO_APPLICATION_NONIP_RECVFROM,
    RPC_PROTOCOL_TO_APPLICATION_CRING_IND,
    RPC_PROTOCOL_TO_APPLICATION_PIN_RESULT_IND,
    RPC_PROTOCOL_TO_APPLICATION_PSM_STATUS_IND,
    RPC_PROTOCOL_TO_APPLICATION_SMS_CMT_PDU_IND,
    RPC_PROTOCOL_TO_APPLICATION_RADIO_COMMAND_ABORT_IND,
    RPC_PROTOCOL_TO_APPLICATION_IP_INFO,
    RPC_PROTOCOL_TO_APPLICATION_FLOWCONTROL_STATUS,
    RPC_PROTOCOL_TO_APPLICATION_CIOT_OPT_STATUS_IND,
    RPC_PROTOCOL_TO_APPLICATION_PDP_MODIFY_RESULT,
    RPC_PROTOCOL_TO_APPLICATION_DRIVER_ADC_READ_RESPONSE,
    RPC_PROTOCOL_TO_APPLICATION_DRIVER_ADC_ACTION_RESPONSE,
    RPC_PROTOCOL_TO_APPLICATION_PIN_STATUS_IND,
    RPC_PROTOCOL_TO_APPLICATION_T3324_T3412_EXT_VALUE_CHANGED_IND,
    RPC_PROTOCOL_TO_APPLICATION_RXCALIST_RESPONSE,
    RPC_COMMANDS_PROTOCOL_TO_APPLICATION_MAX_COMMANDS
} RPC_PROTOCOL_TO_APPLICATION_COMMANDS;

typedef enum {
    RPC_ERR_OK = 0,
    RPC_ERR_TAKE_SEMAPHORE_FAIL,
    RPC_ERR_GIVE_SEMAPHORE_FAIL,
    RPC_ERR_BUSY,
} RPC_ERR;

typedef void (*rpc_interface_internal_callback)(CORES core, uint16 commandID, uint8* data);

#define RPC_INTERFACE_MAX_COMMAND_ID RPC_COMMANDS_RPC_INTERFACE_MAX_COMMANDS

void internal_incomming_response_default_blocking_response(CORES core);

RPC_ERR command_get_dieid(uint8 *get_dieid_result, uint16 dieid_max_length, uint16 *dieid_length, uint8 *dieid);
RPC_ERR command_get_protocol_rpc_version(uint32 *local_rpc_version, uint32 *supported_rpc_version);
RPC_ERR command_get_security_rpc_version(uint32 *local_rpc_version, uint32 *supported_rpc_version);
RPC_ERR command_set_protocol_log_level(uint8 level, uint8 *ret_code);
RPC_ERR command_set_vdd_io_level(uint8 bank, uint8 level, uint8 *ret_code);
RPC_ERR command_set_security_log_level(uint8 level, uint8 *ret_code);
RPC_ERR command_get_protocol_log_level(uint8 *level);
RPC_ERR command_get_security_log_level(uint8 *level);
RPC_ERR command_kv_get(uint16 key, uint8 *kv_ret_code, uint16 kvalue_max_length, uint16 *kvalue_length, uint8 *kvalue, bool *permanent);
RPC_ERR command_kv_erase_all(uint8 *kv_ret_code);
RPC_ERR command_set_id(uint16 id_length, uint8 *id, uint8 id_type, uint8 *ret_code);
RPC_ERR command_set_id_permanence(uint8 id_type, uint8 set_dest, uint8 *ret_code);
RPC_ERR command_system_reboot(void);
RPC_ERR command_get_id(uint8 id_type, uint16 id_max_length, uint16 *id_length, uint8 *id, uint8 *neul_ret_code);
RPC_ERR command_getifaddr(uint8 cid, uint16 ifaddr_data_max_length, uint16 *ifaddr_data_length, uint8 *ifaddr_data, uint8 *err);
RPC_ERR command_set_earfcn_range(uint16 mode, uint32 earfcn_start, uint32 earfcn_end, uint16 pci, uint8 *plmn_search_result);
RPC_ERR command_clear_stored_earfcn(uint8 *result);
RPC_ERR command_set_band(uint16 band_length, uint8 *band, uint8 *band_result);
RPC_ERR command_get_band(uint8 *band_result, uint16 band_max_length, uint16 *band_length, uint8 *band);
RPC_ERR command_get_supported_bands(uint8 *band_result, uint16 band_max_length, uint16 *band_length, uint8 *band);
RPC_ERR command_execute_radiotest(uint16 test_data_length, uint8 *test_data, uint8 *test_result);
RPC_ERR command_execute_plmn_select(uint16 plmn_mode, uint8 plmn[3], uint8 *plmn_select_result);
RPC_ERR command_get_plmn_status(uint8 *current_mode, uint8 current_plmn[3]);
RPC_ERR command_get_available_plmn(uint8 *get_available_plmn_result);
RPC_ERR command_start_rach(void);
RPC_ERR command_set_attach_state(uint16 state, uint8 *set_result);
RPC_ERR command_get_imsi(uint16 imsi_max_length, uint16 *imsi_length, char *imsi, uint8 *result);
RPC_ERR command_get_registration_status(uint8 *state, uint16 *tac, uint32 *ci, bool *reject_flag, uint8 *reject_cause, uint16 *active_time, uint16 *periodic_tau);
RPC_ERR command_get_connection_status(uint8 *status);
RPC_ERR command_set_pdp_context(uint8 cid, uint8 pdp_type, uint16 p_apn_str_length, uint8 *p_apn_str, uint8 d_comp, uint8 h_comp, uint8 p_emergency, uint8 addr_alloc, uint8 nslpi, uint8 secure_pco, uint8 *result);
RPC_ERR command_delete_pdp_context(uint16 cid, uint8 *delete_pdp_context_result);
RPC_ERR command_get_pdp_context(uint8 cid_requested, uint8 *result, uint16 apn_max_length, uint16 *apn_length, uint8 *apn, uint16 context_max_length, uint16 *context_length, uint8 *context);
RPC_ERR command_set_pdp_context_auth_param(uint8 cid, uint8 auth_prot, uint16 login_str_length, uint8 *login_str, uint16 password_str_length, uint8 *password_str, uint8 *result);
RPC_ERR command_get_pdp_context_auth_param(uint8 cid, uint8 *result, uint8 *auth_prot, uint16 login_str_max_length, uint16 *login_str_length, uint8 *login_str, uint16 password_str_max_length, uint16 *password_str_length, uint8 *password_str);
RPC_ERR command_set_nconfig(uint8 function, uint16 value, uint8 *result);
RPC_ERR command_get_nconfig(uint8 function, uint8 *result, uint16 *value);
RPC_ERR command_set_ntest(uint8 function, uint32 value, uint8 *result);
RPC_ERR command_get_ntest(uint8 function, uint8 *result, uint32 *value);
RPC_ERR command_query_ue_stats(uint16 ue_status_max_length, uint16 *ue_status_length, uint8 *ue_status);
RPC_ERR command_set_ue_cfun(uint16 cfun, uint8 *cfun_set_result);
RPC_ERR command_read_service_status(uint8 *service_status);
RPC_ERR command_read_ue_cfun(uint8 *c_fun);
RPC_ERR command_get_defined_cids(uint16 cids_max_length, uint16 *cids_length, uint8 *cids);
RPC_ERR command_allocate_socket(uint8 domain, uint8 type, uint8 protocol, uint8 *ret, uint16 *socknum);
RPC_ERR command_close_socket(uint16 socket, uint8 *ret);
RPC_ERR command_neul_bind(uint16 socket, uint16 sock_address_length, uint8 *sock_address, uint8 *ret);
RPC_ERR command_sendto(uint16 socket, uint16 message_length, uint8 *message, uint8 seq_num, uint16 flags, uint16 sock_address_length, uint8 *sock_address, uint8 *ret);
RPC_ERR command_get_pending_data_seqs(uint8 socket_num, uint16 data_seqs_max_length, uint16 *data_seqs_length, uint8 *data_seqs);
RPC_ERR command_socket_send(uint16 socket, uint16 message_length, uint8 *message, uint16 flags, uint8 *ret);
RPC_ERR command_socket_connect(uint16 socket, uint16 sock_address_length, uint8 *sock_address, uint8 *ret);
RPC_ERR command_set_ping(uint16 remote_addr_length, uint8 *remote_addr, uint16 p_size, uint32 timeout, uint8 *result);
RPC_ERR command_set_system_time_from_apps(uint64 current_time, int8 time_zone, uint8 daylight_saving_time, uint8 updated_time_fields, uint8 *result);
RPC_ERR command_set_time_update_mode(uint8 time_update_mode);
RPC_ERR command_get_time_update_mode(uint8 *time_update_mode);
RPC_ERR command_update_package_parse_req(uint8 *result);
RPC_ERR command_update_package_process_req(uint8 *result);
RPC_ERR command_update_package_get_package_version_req(uint8 *result);
RPC_ERR command_update_package_get_package_name_req(uint8 *result);
RPC_ERR command_firmware_upgrade_req(uint8 *result, uint8 *status);
RPC_ERR command_update_package_discard(void);
RPC_ERR command_image_loader_ready_ind(void);
RPC_ERR command_update_package_data_cnf(uint32 offset, uint16 package_data_length, uint8 *package_data);
RPC_ERR command_update_package_flash_erase(bool *buffered);
RPC_ERR command_update_package_flash_write(uint32 buffer_length, uint32 buffer, uint32 offset, bool *buffered);
RPC_ERR command_rf_config_ctrl(uint8 ctrl_command, uint8 *result);
RPC_ERR command_radio_config_meas_rssi(uint32 frequency, uint8 gain_index, uint8 port, uint8 *result, int16 *rssi, int16 *snr);
RPC_ERR command_radio_config_read_mipi_word(uint8 slave_addr, uint8 data_addr, uint8 *result, uint8 *mipi_data);
RPC_ERR command_radio_config_write_mipi_word(uint8 slave_addr, uint8 data_addr, uint8 mipi_data, uint8 *result);
RPC_ERR command_radio_config_tx_tone(uint32 frequency, uint8 *result);
RPC_ERR command_radio_config_set_tx_gains(uint16 tx_drive_level, uint8 tx_coarse_gain, uint8 rf_gain, uint16 mv, uint8 *result);
RPC_ERR command_radio_config_get_tx_gains(uint8 *result, uint16 *tx_drive_level, uint8 *tx_coarse_gain, uint8 *rf_gain, uint16 *ext_pa_gain);
RPC_ERR command_radio_config_set_rio_v(uint8 rio, uint16 mv, uint8 *ret_value);
RPC_ERR command_radio_config_set_gpio(uint64 pio, uint8 *result);
RPC_ERR command_radio_config_get_gpio(uint8 *ret_value, uint64 *pio);
RPC_ERR command_flush_ul_queue(void);
RPC_ERR command_prepare_for_powerdown(void);
RPC_ERR command_pdp_activate_req(uint16 cid, uint8 *ret);
RPC_ERR command_pdp_deactivate_req(uint16 cid, uint8 *ret);
RPC_ERR command_sms_set_short_message_service(uint16 service, uint8 *state, uint8 *mt, uint8 *mo, uint8 *bm);
RPC_ERR command_sms_read_short_message_service(uint8 *state, uint8 *service, uint8 *mt, uint8 *mo, uint8 *bm);
RPC_ERR command_sms_set_more_message_to_send(uint8 mode, uint8 *state);
RPC_ERR command_sms_read_more_message_to_send(uint8 *state, uint8 *mode);
RPC_ERR command_sms_set_short_message_service_address(uint8 type, uint16 address_length, uint8 *address, uint8 *state);
RPC_ERR command_sms_read_short_message_service_address(uint8 *state, uint8 *type, uint16 address_max_length, uint16 *address_length, uint8 *address);
RPC_ERR command_sms_send_short_message(uint8 data_len, uint16 tpdu_length, uint8 *tpdu, uint8 *state);
RPC_ERR command_sms_send_command(uint8 data_len, uint16 tpdu_length, uint8 *tpdu, uint8 *state);
RPC_ERR command_sms_set_new_msg_ack(uint8 report_type, uint16 tpdu_length, uint8 *tpdu, uint8 *state);
RPC_ERR command_get_cnma_acknowledgement_expected(uint8 *result);
RPC_ERR command_get_iccid(uint16 iccid_max_length, uint16 *iccid_length, char *iccid, uint8 *result);
RPC_ERR command_set_power_saving_mode(uint8 mode, uint16 requested_periodic_tau, uint16 requested_active_time, uint8 *result);
RPC_ERR command_get_power_saving_mode(uint8 *ret_value, uint8 *mode, uint8 *requested_periodic_tau, uint8 *requested_active_time);
RPC_ERR command_set_edrxs_and_ptw(uint8 mode, uint8 type, uint8 edrx_value, uint8 paging_time_window, uint8 *result);
RPC_ERR command_get_edrxs_and_ptw(uint8 *result, uint8 *type, uint8 *edrx_value, uint8 *paging_time_window);
RPC_ERR command_get_cell_info(uint8 *result, uint16 cell_info_buffer_max_length, uint16 *cell_info_buffer_length, uint8 *cell_info_buffer, uint8 *vaild_cell_info_num);
RPC_ERR command_get_extended_error_cause(uint8 *reject_flag, uint8 *cause);
RPC_ERR command_get_edrxrdp(uint8 *result, uint8 *registered_state, uint8 *act_type, uint8 *edrx_info_valid, uint8 *request_edrx, uint8 *nw_provided_edrx, uint8 *paging_time);
RPC_ERR command_get_firmware_version(uint8 version_core, uint8 *result, uint16 *version_string_length, char version_string[48]);
RPC_ERR command_get_ssb_version(uint8 *result, uint16 *version_string_length, char version_string[48]);
RPC_ERR command_get_rfconfig_version(uint8 *result, char version_string[48]);
RPC_ERR command_get_temp_coefficient(uint16 *temp_coefficient);
RPC_ERR command_get_chipinfo(uint8 *result, uint16 chipinfo_max_length, uint16 *chipinfo_length, uint8 *chipinfo);
RPC_ERR command_radio_config_tx_verify(int8 tx_power, uint32 tx_frequency, uint32 tx_duration, uint8 tx_band, int16 temperature, int16 voltage, uint8 num_subcarrier, uint8 subcarrier_index, uint8 *result);
RPC_ERR command_radio_config_rx_verify(uint32 frequency, uint8 gain_index, uint8 band, int16 temperature, int16 voltage, uint8 *result, int16 *rssi, int16 *snr, int16 *cbm);
RPC_ERR command_nonip_sendto(uint8 cid, uint16 message_length, uint8 *message, uint32 flags, uint8 *ret);
RPC_ERR command_get_mtu_size(uint8 cid, uint8 *result, uint16 *ip_mtu, uint16 *non_ip_mtu);
RPC_ERR command_execute_pin_command(uint8 command, uint8 pin1[9], uint8 pin2[9], uint8 *ret);
RPC_ERR command_register_kvcache(uint32 kv_cache, uint8 *kv_ret_code);
RPC_ERR command_kv_queue_cache_for_write(uint8 *kv_ret_code);
RPC_ERR command_get_random(uint16 random_request_length, uint8 *result, uint16 random_max_length, uint16 *random_length, uint8 *random);
RPC_ERR command_get_apn_rate_control_context(uint8 cid, uint8 *result, uint8 *additional_exception_reports, uint8 *uplink_time_unit, uint32 *maximum_uplink_rate, uint8 *except_uplink_time_unit, uint32 *except_maximum_uplink_rate);
RPC_ERR command_set_power_band_class(uint8 band, uint8 power_class, uint8 *set_result);
RPC_ERR command_get_power_band_class(uint8 band, uint8 *get_result, uint8 *power_class);
RPC_ERR command_get_update_result(uint8 *result);
RPC_ERR command_get_update_status(uint8 *status);
RPC_ERR command_reset_update_result(void);
RPC_ERR command_set_initial_pdp_context(uint8 attach_without_pdn, uint8 *result);
RPC_ERR command_get_initial_pdp_context(uint8 *result, uint8 *attach_without_pdn);
RPC_ERR command_radio_config_tx_test(uint32 tx_frequency, uint8 tx_band, uint8 num_subcarrier, uint8 subcarrier_index, uint8 *result);
RPC_ERR command_iflog_cache_register(uint32 cache, uint8 *result);
RPC_ERR command_iflog_iflash_write(uint16 index, uint16 len, uint8 *result);
RPC_ERR command_iflog_iflash_read(uint32 buff, uint16 buff_size, uint8 *result, uint16 *len);
RPC_ERR command_update_package_allocate_flash(uint32 update_package_size, bool *allocated);
RPC_ERR command_update_package_get_available_flash(uint32 *available_size);
RPC_ERR command_abort_processing_command(uint8 *result);
RPC_ERR command_aio_manager_claim_resource(uint16 resource_list_length, uint8 *resource_list, uint8 *result);
RPC_ERR command_aio_manager_free_resource(uint16 resource_list_length, uint8 *resource_list, uint8 *result);
RPC_ERR command_set_network_config(uint16 config, uint16 value, uint8 *result);
RPC_ERR command_rai_req(void);
RPC_ERR command_get_dns_server_ip_address(uint8 cid, uint8 *result, uint16 dns_server_ip_address_value_max_length, uint16 *dns_server_ip_address_value_length, uint8 *dns_server_ip_address_value);
RPC_ERR command_set_pdp_context_dynamic_param_request_state(uint8 param_item, bool state, uint8 *result);
RPC_ERR command_get_pdp_context_dynamic_param_request_state(uint8 param_item, bool *state);
RPC_ERR command_calibrate_temperature(int16 temperature, uint8 *result);
RPC_ERR command_open_logical_channel(uint16 app_id_length, uint8 *app_id, uint8 *result, uint8 *channel_num);
RPC_ERR command_close_logical_channel(uint8 channel_num, uint8 *result);
RPC_ERR command_generic_uicc_logical_channel_access(uint8 channel_num, uint16 command_length, uint8 *command, uint8 *result, uint16 response_max_length, uint16 *response_length, uint8 *response);
RPC_ERR command_pdp_modify_req(uint16 cid, uint8 *ret);
RPC_ERR command_set_ciot_opt(uint8 supported_ue_opt, uint8 preferred_ue_opt, uint8 *result);
RPC_ERR command_get_ciot_opt(uint8 *result, uint8 *supported_ue_opt, uint8 *preferred_ue_opt);
RPC_ERR command_set_qos_req(uint16 cid, uint8 qci, uint8 *ret);
RPC_ERR command_get_qos(uint16 cid, uint8 *ret, uint8 *qci);
RPC_ERR command_delete_qos(uint16 cid, uint8 *ret);
RPC_ERR command_delete_tft_req(uint16 cid, uint8 *ret);
RPC_ERR command_set_tft_req(uint16 tft_length, uint8 *tft, uint8 *ret);
RPC_ERR command_get_tft_context(uint8 cid, uint8 packet_filter, uint16 tft_context_max_length, uint16 *tft_context_length, uint8 *tft_context, uint8 *num_of_packet_filters);
RPC_ERR command_driver_adc_init(void);
RPC_ERR command_driver_adc_deinit(void);
RPC_ERR command_driver_adc_get_calibrated_max_voltage_mv(uint8 range, uint8 *ret_value, uint32 *voltage);
RPC_ERR command_driver_adc_read_uv(uint16 samples_to_average_over, uint8 *ret_value);
RPC_ERR command_driver_adc_read_raw(uint8 *ret_value);
RPC_ERR command_driver_adc_set_range(uint8 range);
RPC_ERR command_driver_adc_calibrate_for_voltage(uint8 vref_voltage, uint8 *ret_value);
RPC_ERR command_driver_adc_calibrate_calculate(uint8 *ret_value);
RPC_ERR command_driver_adc_find_trim_values(uint8 *ret_value);
RPC_ERR command_driver_adc_set_read_within_time(uint32 read_within_time);
RPC_ERR command_app_flash_alloc(uint8 buffer_length, uint8 *ret_val);
RPC_ERR command_app_flash_free(uint8 *ret_val);
RPC_ERR command_app_flash_erase_pages(uint8 page_offset, uint8 pages, uint8 *ret_val);
RPC_ERR command_app_flash_write_request(uint32 buffer_length, uint32 buffer, uint32 offset, uint8 *ret_val);
RPC_ERR command_app_flash_avail(uint8 *ret_val, uint8 *pages);
RPC_ERR command_app_flash_read(uint32 offset, uint32 buffer_length, uint32 buffer, uint8 *ret_val);
RPC_ERR command_get_pin_state(uint8 *result, uint8 *state);
RPC_ERR command_get_pin_remaining_retries(uint8 code, uint8 *result, uint8 *retries, uint8 *default_retries);
RPC_ERR command_uicc_status_control(uint8 status, uint8 *result);
RPC_ERR command_restricted_sim_access(uint16 crsm_cmd_length, uint8 *crsm_cmd, uint8 *result, uint16 response_max_length, uint16 *response_length, uint8 *response);
RPC_ERR command_get_cid_status(uint8 cid, uint8 *ret, uint8 *status, uint16 *backoff);
RPC_ERR command_get_socket_status(uint8 socketid, uint8 *ret, uint8 *status, uint16 *backoff);
RPC_ERR command_radio_config_tx_calist(uint32 start_frequency, uint32 step_frequency, uint32 stop_frequency, int8 start_power, int8 step_power, int8 stop_power, uint8 num_subcarrier, uint8 subcarrier_index, uint8 *result);
RPC_ERR command_radio_config_rx_calist(uint32 start_frequency, uint32 step_frequency, uint32 stop_frequency, uint8 start_agc_index, uint8 step_agc_index, uint8 stop_agc_index, int16 ul_power, uint32 ul_freq, uint32 rssi_meas_duration, uint8 sweep_band, uint8 *result);

uint32 remote_command_get_apps_rpc_version(CORES core, uint32 *supported_rpc_version);
void remote_command_get_plmn_results_ind(CORES core, uint16 available_plmn_length, uint8 *available_plmn, uint8 result);
void remote_command_attach_status_set_result_ind(CORES core, uint8 attach_status_set_result);
void remote_command_plmn_select_result_ind(CORES core, uint8 plmn_select_result);
void remote_command_registration_status_ind(CORES core, uint8 registration_status);
void remote_command_connection_status_ind(CORES core, uint8 connection_status);
void remote_command_socket_data_sent(CORES core, uint16 data_seq, bool status);
void remote_command_non_ip_data_sent(CORES core, uint16 data_seq, bool status);
void remote_command_ip_address_changed(CORES core, uint8 cid);
void remote_command_recvfrom(CORES core, uint16 socket, uint16 buffer_length, uint8 *buffer, uint16 sock_address_length, uint8 *sock_address);
void remote_command_socket_recv(CORES core, uint16 socket, uint16 buffer_length, uint8 *buffer, uint16 sock_address_length, uint8 *sock_address, uint16 flags);
void remote_command_socket_notify(CORES core, uint16 socket, uint16 notify, int arg);
void remote_command_ping_ind(CORES core, uint16 remote_addr_length, uint8 *remote_addr, uint8 result, uint8 ttl, uint32 rtt);
void remote_command_cfun_result_ind(CORES core, uint8 cfun_result);
void remote_command_sms_mgs_result_ind(CORES core, uint8 sms_mgs_result, uint8 mr, uint16 ackpdu_length, uint8 *ackpdu);
void remote_command_sms_cmd_result_ind(CORES core, uint8 sms_cmd_result, uint8 mr, uint16 ackpdu_length, uint8 *ackpdu);
void remote_command_current_time_ind(CORES core, uint64 current_time, int8 time_zone, uint8 daylight_saving_time, uint8 updated_time_fields);
void remote_command_rf_calibration_rtc_ind(CORES core, uint32 rtc_freq_calibrated_by_rf);
void remote_command_update_package_parse_cnf(CORES core, uint8 status);
void remote_command_update_package_process_cnf(CORES core, uint8 status);
void remote_command_update_package_get_package_version_cnf(CORES core, uint16 version_length, uint8 *version);
void remote_command_update_package_get_package_name_cnf(CORES core, uint16 pkgname_length, uint8 *pkgname);
void remote_command_update_package_data_req(CORES core, uint32 offset, uint16 length);
void remote_command_update_package_flash_erase_done(CORES core, bool result);
void remote_command_update_package_flash_write_done(CORES core, uint8 result);
void remote_command_service_recovery(CORES core);
void remote_command_pdp_act_or_deact_result_ind(CORES core, uint8 cid, uint8 state, uint8 result);
void remote_command_edrx_changed_ind(CORES core, uint8 type, uint8 requested_edrx_value, uint8 nw_provided_edrx_value, uint8 paging_time_window, uint8 requested_paging_time_window);
void remote_command_radiotest_response(CORES core, uint8 retcode, uint16 retdata_length, uint8 *retdata);
void remote_command_nonip_recvfrom(CORES core, uint8 cid, uint16 message_length, uint8 *message, bool cplane_pdu);
void remote_command_cring_ind(CORES core);
void remote_command_pin_result_ind(CORES core, uint8 pin_result, uint8 retries_remaining);
void remote_command_kv_apps_cache_flushed(CORES core, uint32 kv_cache_start, uint32 kv_processed_end, uint16 kv_return_code);
void remote_command_psm_status_ind(CORES core, uint8 psm_status);
void remote_command_sms_cmt_pdu_ind(CORES core, uint8 alpha, uint16 pdu_length, uint8 *pdu);
void remote_command_radio_command_abort_ind(CORES core, uint8 result);
void remote_command_ip_info(CORES core, uint8 cid, uint8 current_ip_type, uint8 requested_ip_type, uint8 failure_cause);
void remote_command_flowcontrol_status(CORES core, uint8 status);
void remote_command_ciot_opt_status_ind(CORES core, bool cplane_opt_supported, bool uplane_opt_supported);
void remote_command_pdp_modify_result(CORES core, uint8 ret);
void remote_command_driver_adc_read_response(CORES core, uint32 reading, uint8 ret_value);
void remote_command_driver_adc_action_response(CORES core, uint8 ret_value);
void remote_command_app_flash_erase_response(CORES core, uint8 ret_val);
void remote_command_app_flash_write_response(CORES core, uint8 ret_val);
void remote_command_pin_status_ind(CORES core, uint8 pin_status);
void remote_command_t3324_t3412_ext_value_changed_ind(CORES core, uint16 t3324, uint16 t3412_ext);
void remote_command_rxcalist_response(CORES core, uint8 retcode, uint16 retdata_length, uint8 *retdata);

#endif

