/******************************************************************************
 * @brief    Basic Radio Management Functions for Hi21XX
 * Copyright (c) 2016-2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LIB_NEUL_RADIO_H_
#define LIB_NEUL_RADIO_H_

#include "neulfw.h"
#include "neul_error_types.h"
#include "platform_definitions.h"   //needed for CORES
#include "neul_radio_types.h"

/** @defgroup libNEUL_RADIO Hi21XX libNEUL Radio
 * Hi21XX libNeul Radio API
 * @ingroup LIBNEUL
 * @{
 * */

/*
 * Value to indicate  apn rate control uplink_time_unit is unrestricted
*/
#define APN_RATE_CTRL_UNRESTRICTED 0

typedef enum
{
    RADIO_POWER_OFF = 0,
    RADIO_POWER_ON
}RADIO_POWER;

/**
 * @brief radio power state callback
 * @param result radio power state set result
 */
typedef void (*neul_radio_power_state_callback)(uint8 result);

/**
 * @brief registration callback
 * @param reg_state registration status
 */
typedef void (*neul_registration_status_callback)(uint8 reg_status);

/**
 * @brief t3324_t3412_ext_value_changed callback
 * @param t3324 t3412_ext value
 */
typedef void (*neul_t3324_t3412_ext_value_changed_callback)(uint16 t3324,uint16 t3412_ext);


/**
 * @brief connection callback
 * @param connect status
 */
typedef void (*neul_connection_status_callback)(uint8 connect_status);

/**
 * @brief psm status callback
 * @param psm status
 */
typedef void (*neul_psm_status_reporting_callback)(uint8 psm_status);

/**
 * @brief attach callback
 * @param result attach/detach result
 */
typedef void (*neul_attach_callback)(uint8 result);

/**
 * @brief plmn state callback
 * @param result set plmn state result
 */
typedef void (*neul_set_plmn_state_callback)(uint8 result);

/**
 * @brief PIN callback
 * @param result - PIN command result
 */
typedef void (*neul_pin_command_callback)(uint8 result, uint8 retries_remaining);

/**
 * @brief
 * @param
 */
typedef void (*neul_service_recovery_callback)(void);

/**
 * @brief
 * @param
 */
typedef void (*neul_pdp_act_result_callback)(uint8 result);


/**
 * @brief Indication of PDP context activate and deactivate result callback
 * @param cid particular PDP context definition
 * @param state indicates the state of PDP context activation
 * @param result PDP context activate or deactivate result
 */
typedef void (*neul_pdp_context_report_callback)(uint8 cid, PDP_CONTEXT_REPORT_RESULT_STATE state,  PDP_CONTEXT_REPORT_RESULT result);

/**
 * @brief
 * @param
 */
typedef void (*neul_set_edrx_changed_callback)(uint8 act_type, uint8 requested_edrx_value, uint8 nw_provided_edrx_value, uint8 paging_time_window);

/**
 * @brief
 * @param
 */
typedef void (*neul_set_ptwedrx_changed_callback)(uint8 act_type, uint8 requested_edrx_value, uint8 nw_provided_edrx_value, uint8 paging_time_window, uint8 requested_paging_time_window);

/**
 * @brief Indication of the supported CIoT EPS optimizations by the network callback
 * @param network opt support
 */
typedef void (*neul_set_ciot_opt_callback)(uint8 network_opt_support);

/**
 * @brief Indication of receiving MT short message callback
 * @param pdu_length -length of received MT short message
 * @param pdu - received MT short message
 */
typedef void (*neul_receive_short_message)(uint8 alpha, uint16 pdu_length, const uint8 *pdu);

/**
 * @brief Indication of incoming PAGE callback
 */
typedef void (*neul_cring_ind_callback)(void);

/** @brief callback to get available.
 *  @param available_plmn available plmn searched.
 *  @param plmn_num available plmn number searched.
 *  @param result get available plmn result.
 */
typedef void (*neul_get_available_plmn_callback)(plmn_info plmn_info[],uint8 plmn_num, uint8 result);

/**
 * @brief callback for radio command abort
 * @param result error or success
 */
typedef void (*neul_radio_cmd_abort_callback)(NEUL_RET result);

/**
 * @brief callback for IP info
 * @param
 */
 typedef void (*neul_ip_info_callback)(uint8 cid, NEUL_PDN_TYPE current_ip_type, NEUL_PDN_TYPE requested_ip_type, uint8 failure_cause);

/**
 * @brief pdp modify callback
 * @param result pdp modify result
 */
typedef void (*neul_pdp_modify_callback)(NEUL_RET result);

/**
 * @brief callback for radio command abort
 * @param result error or success
 */
typedef void (*neul_sim_pin_ind_callback)(uint8 result);

/**
 * @brief Specify a freq range and pci for plmn search. If start and end are the same they are specifying a point
 * @param search_mode search mode
 * @param start    start freq
 * @param end      end freq
 * @param pci physical cell ID
 * @return error or success
 */
NEUL_RET set_plmn_search_range(uint16 search_mode, uint32 earfcn_start, uint32 earfcn_end, uint16 pci);

/**
 * @brief clear stored earfcn from rrc nv
 * @return error or success
 */
NEUL_RET clear_stored_earfcn(void);

/**
 * @brief Start cell search procedure.
 * @param mode  cell search mode
 */
void start_cell_search(uint16 mode);

/**
 * @brief Specify a PLMN ID for plmn search
 * @param plmn_mode
 * @param plmn
 * @param callback:callback for set plmn state result
 * @return error or success
 */
NEUL_RET set_plmn_state(uint16 plmn_mode, uint8 plmn[3], neul_set_plmn_state_callback callback);

/**
 * @brief Enter PIN
 * @param pin length
 * @param pin
 * @param callback:callback for verify pin result
 * @return error or success
 */
NEUL_RET pin_command(uint8 mode, uint8 pin1[9], uint8 pin2[9], neul_pin_command_callback callback);

/**
 * @brief get SIM pin state
 * @param state ready,sim pin or sim puk
 * @return success or error
 */
NEUL_RET get_pin_state(uint8 *state);

/**
 * @brief get SIM pin or puk remaining retries
 * @param code sim pin or sim puk
 * @param retries pin or puk remaining retries
 * @param default_retries pin or puk default remaining retries
 * @return success or error
 */
NEUL_RET get_pin_remaining_retries(uint8 code, uint8 *retries, uint8 *default_retries);

/**
 * @brief Set band to search
 * @param num_bands number of bands to set(the max number is 4 now)
 * @param bands an array of band data containing num_bands bands
 * @return error or success
 */
NEUL_RET set_bands(uint8 num_bands, uint8 *bands);

/**
 * @brief Get list of bands to search
 * @param max_bands_size: size of bands buffer in bytes
 * @param num_bands number of band data items returned
 * @param bands a pointer to a buffer of max_bands_size bytes
 * @return error or success
 */
NEUL_RET get_bands(uint16 max_bands_size, uint16 *num_bands, uint8 *bands);

/**
 * @brief Get supported bands
 * @param max_supported_bands_size size of supported_bandin bytes
 * @param num_supported_bands number of supported band data items returned
 * @param supported_bands a pointer to a buffer of max_supported_bands_size bytes
 * @return error or success
 */
NEUL_RET get_support_bands(uint16 max_supported_bands_size, uint16 *num_supported_bands, uint8 *supported_bands);

/**
 * @brief Get PLMN status
 * @param current_mode
 * @param current_plmn, {0xff, 0xff, 0xff} means invalid plmn.
 * @return success or error
 */
NEUL_RET get_plmn_state(uint8 *current_mode, uint8 *current_plmn);

/** Get available plmn (+COPS=?)
 * @param callback The function to call with the available plmn search ind
 * @return NEUL_RET
 */
NEUL_RET get_available_plmn(neul_get_available_plmn_callback available_plmn_callback);

/**
 * @brief set service state
 * @param attach_state  1: attach, 0: detach
 * @param callback:callback for set service state result
 * @return NEUL_RET_OK or an error code
 */
NEUL_RET set_service_state(uint16 attach_state, neul_attach_callback callback);

/**
 * @brief get service state
 * @param creg_status state  1: attached, 0: detached
 */
NEUL_RET get_service_state(uint8 *creg_status);

/**
 * @brief Get signal strength indicator
 * @return csq signal strength in decimal of 0 to 31 or 99
 */
NEUL_RET get_csq(uint8 *csq);

/**
 * @brief Query camped cell information
 * @param state pointer to the eps registration state
 * @param tac pointer to tracking area code
 * @param ci pointer to cell id
 * @param reject_flag indicate whether reject_cause is valid
 * @param reject_cause reject cause of attach(if attach failed)
 * @param active_time Indicates the Active Time value (T3324) allocated to the UE in E-UTRAN,0xFFFF means invalid
 * @param periodic_tau the extended periodic TAU value (T3412),0xFFFF means invalid
 * @return success or fail
 */
NEUL_RET get_registration_status(uint8 *state, uint16* tac, uint32* ci, bool *reject_flag, EMM_CAUSE_INFO *reject_cause, uint16 *active_time, uint16 *periodic_tau);

/**
 * @brief gives details of the terminal perceived radio connection status
 * @param status 0: Idle, 1: Connected
 * @return success or error
 */
NEUL_RET get_connection_status(uint8 *status);

/**
 * @brief Set radio state function
 * @param fun radio power state 0: off 1: on
 * @param callback The function to call with the cfun result
 * @return NEUL_RET
 */
NEUL_RET set_cfun(uint16 fun, neul_radio_power_state_callback callback);

/**
 * @brief get radio state function
 * @param cfun radio power state 0: off 1: on
 * @return NEUL_RET_OK or an error code
 */
NEUL_RET get_cfun(uint16 *cfun);

/**
 * @brief This command fetches the most recent operational statistics.
 * @param  stats pointer to a struct ue_stats
 * @return error if command failed
 */
NEUL_RET get_ue_stats(ue_stats *stats);

 /**
 * @brief get service cell and adjacent cells measurements
 * @param max_cell_info_num max cell info num to get
 * @param cell_info_num the num of cell info
 * @param cell_info point of cell_info array
 */
NEUL_RET get_cell_info(uint8 max_cell_info_num, uint8 *cell_info_num, ue_cell_info *cell_info);

/**
 * @brief Configure UE Behaviour
 * @param function:function to set
 * @param value:function value to set
 * @return success or failure
 */
NEUL_RET set_nconfig(uint8 function, uint16 value);

/**
 * @brief Get nconfig value
 * @param value:function value to get
 * @return success or failure
 */
NEUL_RET get_nconfig(uint8 function, uint16 *value);

/**
 * @brief get list of defined cids
 * @param cids_max_length size of cids buffer in bytes
 * @param cids_num number of band data items returned
 * @param cids a pointer to a buffer of cids_max_length bytes
 */
NEUL_RET get_defined_cids(uint16 cids_max_length, uint16 *cids_num, uint8 *cids);

/**
* @brief get list of data seqs
* @param socket_num socket number
* @param seqs_max_length size of seqs buffer in bytes
* @param seqs_num number of pending data items returned
* @param seqs a pointer to a buffer of seqs_max_length bytes
*/
NEUL_RET get_pending_data_seqs(uint8 socket_num, uint16 seqs_max_length, uint16 *seqs_num, uint8 *data_seqs);

/**
 * @brief delete a pdp context
 * @param cid: The cid to activate
 * @return success or error
 */
NEUL_RET delete_pdp_context(uint16 cid);

/**
 * @brief Activates a pdp context
 * @param context The context to activate
 * @return success or error
 */
NEUL_RET activate_pdp_context(const pdp_context *context);

/**
 * @brief get a pdp context
 * @param cid context to get
 * @param context pointer to structure to contain context.
 * @return success or error
 */
NEUL_RET get_pdp_context(uint8 cid, pdp_context *context);

/**
 * @brief Define PDP context authentication parameters
 * @param cid
 * @param auth_prot  Authentication protocol used for this PDP context.
 * @param login_str User name for access to the IP network   max length is 60.
 * @param password_str Password for access to the IP network max length is 60.
 * @return success or error
 */
NEUL_RET set_pdp_context_auth_param(uint8 cid, uint8 auth_port, uint8 *login_str, uint8 *password_str);

/**
 * @brief Define PDP context authentication parameters
 * @param cid
 * @param auth_prot  Authentication protocol used for this PDP context.
 * @param login_str User name for access to the IP network max length is 60
 * @param password_str Password for access to the IP network max length is 60
 * @return success or error
 */
NEUL_RET get_pdp_context_auth_param(uint8 cid, uint8* auth_prot, uint8 *login_str, uint8 *password_str);

/**
 * @brief Sets a callback that will be triggered when we receive notifications about our connection status
 * @param callback The function to call with the connection status
 * @return indicate if call was successful. Will fail if a callback is already registered.
 */
NEUL_RET set_connection_status_callback( neul_connection_status_callback callback );

/**
 * Sets a callback that will be triggered when we receive psm status changed (+NPRSR)
 * @param callback The function to call with the psm status
 */
void set_psm_status_reporting_callback( neul_psm_status_reporting_callback callback);

/**
 * @brief Sets a callback that will be triggered when we change from being in/out of service
 * @param callback The function to call with service status
 */
NEUL_RET set_registration_status_callback( neul_registration_status_callback callback);

/**
 * @brief Sets a callback that will be triggered when we change t3324 and t3412_ext
 * @param callback The function to call with t3324 and t3412_ext changed
 */
NEUL_RET set_t3324_t3412_ext_value_changed_callback( neul_t3324_t3412_ext_value_changed_callback callback );

/**
 * @brief Sets a callback that will be triggered when receive MT short message
 * @param callback The function to call with pdu
 */
NEUL_RET set_sms_pdu_callback(neul_receive_short_message callback);

/**
 * @brief Set power saving mode
 * @param mode 0: disable the use of psm,1: enable, 2: Disable the use of PSM and discard all parameters for PSM.
 * @param requested_periodic_tau requested periodic tau value to set, 0xFFFF means not set
 * @param requested_active_time requested active time value to set, 0xFFFF means not set
 */
NEUL_RET set_power_saving_mode(uint8 mode, uint16 requested_periodic_tau, uint16 requested_active_time);

/**
 * @brief Get power saving mode
 * @param mode power saving mode to get
 * @param requested_periodic_tau requested periodic tau value to get
 * @param requested_active_time requested active time value to get
 */
NEUL_RET get_power_saving_mode(uint8 *mode, uint8 *requested_periodic_tau, uint8 *requested_active_time);

/**
 * @brief
 * @param
 * @return success or error
 */
NEUL_RET set_service_callback( void(*callback)(void) );

/**
 * @brief
 * @return success or error
 */
void flush_ul_queue(void);

/**
 * @brief activate pdp context
 * @param cid cid to active
 * @param callback callback for php context activate result
 * @return success or error
 */
NEUL_RET activate_pdp_req(uint16 cid, neul_pdp_act_result_callback callback);

/**
 * @brief deactivate pdp context
 * @param cid cid to deactivate
 * @return success or error
 */
NEUL_RET deactivate_pdp_req(uint16 cid);

/**
 * @brief
 * @param
 * @param
 * @return success or error
 */
NEUL_RET get_pdp_state(uint8 cid, uint8 *state);

/**
 * @brief set pdp context activate or deactivate result report callback
 * @param callback pdp context activate or deactivate result report callback
 */
void set_pdp_context_report_callback(neul_pdp_context_report_callback callback);

/**
 * @brief Set the UEs eDRX parameters
 * @param mode disable or enable the use of eDRX in the UE
 * @param type the type of access technology
 * @param edrx_value the value of eDRX
 * @return success or error
 */
NEUL_RET set_edrxs(uint8 mode, uint8 type, uint8 edrx_value, neul_set_edrx_changed_callback edrxcallback);

/**
 * @brief Set the UEs eDRX parameters
 * @param mode disable or enable the use of eDRX in the UE
 * @param type the type of access technology
 * @param edrx_value the value of eDRX
 * @param paging_time_window the value of paging_time_window
 * @return success or error
 */
NEUL_RET set_ptwedrxs(uint8 mode, uint8 type, uint8 edrx_value, uint8 paging_time_window, neul_set_ptwedrx_changed_callback ptwedrxcallback);


/**
 * @brief Get the UEs eDRX parameters
 * @param type the type of access technology
 * @param edrx_value the value of eDRX
 * @param paging_time_window the value of paging_time_window
 * @return success or error
 */
NEUL_RET get_edrxs_and_ptw (uint8 *type, uint8 *edrx_value, uint8 *paging_time_window);


/**
 * @brief Get the attach reject cause
 * @param attach_rejected flag to indicate attach reject
 * @param cause the cause of attach reject
 * @return success or error
 */
NEUL_RET get_extended_error_cause (uint8 *attach_rejected, EMM_CAUSE_INFO *cause);

/**
 * @brief Get the UEs eDRX parameters
 * @param registered_state the UE registered state
 * @param act_type the type of access technology
 * @param edrx_valid indicates if the information is valid or not
 * @param edrx_value the eDRX value of UE request(edrx_value is 4-bit value)
 * @param nw_provided_edrx the eDRX value of NW provide(nw_provided_edrx is 4-bit value)
 * @param paging_time the paging time window(paging_time is 4-bit value)
 * @return success or error
 */
NEUL_RET get_edrxedp (uint8 *registered_state, uint8 *act_type, uint8 *edrx_valid, uint8 *request_edrx, uint8 *nw_provided_edrx, uint8 *paging_time);

/**
 * @brief Get the MTU sizes for a specific CID
 * @param CID
 * @param ip-mtu in bytes
 * @param non-ip-mtu in bytes
 * @return success or error
 */
NEUL_RET get_mtu_size (uint8 cid, uint16 *ip_mtu_size, uint16 *non_ip_mtu_size);

/**
 * @brief Sets a callback that will be triggered when the UE is paged.
 * @param callback The function to call
 */
NEUL_RET set_ring_ind_callback( neul_cring_ind_callback callback);

/**
 * @brief get apn rate when cid is active.
 * @param cid
 * @additional_exception_reports indicates whether or not additional exception reports are allowed to be sent when the maximum uplink rate is reached
 * @uplink_time_unit specifies the time unit to be used for the maximum uplink rate
 * @maximum_uplink_rate specifies the maximum number of messages the UE is restricted to send per uplink time unit
 * @except_uplink_time_unit specifies the time unit to be used for the exception data maximum uplink rate
 * @except_maximum_uplink_rate specifies the maximum number of additional exception messages the UE is restricted to send once maximum_uplink_rate is reached, per uplink time unit
 */
NEUL_RET get_apn_rate_control_context(uint8 cid, uint8 *additional_exception_reports, uint8 *uplink_time_unit, uint32 *maximum_uplink_rate, uint8 *except_uplink_time_unit, uint32 *except_maximum_uplink_rate);

/**
 * @brief Set the power class of band
 * @param band band to set
 * @param power_class
 * @return success or error
 */
NEUL_RET set_power_band_class(uint8 band, uint8 power_class);

 /**
 * @brief read the map of band and power class
 * @param band_map_power_class_t the value of band and power class
 * @return success or error
 */
NEUL_RET get_power_band_class(uint8 band, uint8 *power_class);

/**
 * @brief set initial pdp context
 * @param attach_without_pdn EPS Attach with or without PDN connection
 * @return success or error
 */
NEUL_RET set_initial_pdp_context(uint8 attach_without_pdn);

/**
 * @brief get initial pdp context configuration parameters
 * @param attach_without_pdn EPS Attach with or without PDN connection
 * @return success or error
 */
NEUL_RET get_initial_pdp_context(uint8 *attach_without_pdn);

/**
 * @brief abort processing radio command
 * @return success or error
 */
NEUL_RET abort_radio_processing_command(void);

/**
 * @brief register radio command abort handler callback
 * @return success or error
 */
void neul_radio_register_abort_handler(neul_radio_cmd_abort_callback  callback);

/**
 * Sets a callback that will be triggered when we receive IP info changed (+NIPINFO)
 * @param callback The function to call with the IP info
 */
 NEUL_RET set_ip_info_callback( neul_ip_info_callback callback );

/**
 * @brief indicate no more PS data
 * @return success or error
 */
NEUL_RET rai_req(void);

/**
 * @brief set pdp context dynamic parameter item request state
 * @param param_item parameter item
 * @param state true or false enable/disable to get the pdp context dynamic parameter
 * @return success or error
 */
NEUL_RET set_pdp_context_dynamic_param_request_state(PDP_CONTEXT_DYNAMIC_PARAM param_item, bool state);

/**
 * @brief get pdp context dynamic parameter item request state
 * @param param_item parameter item
 * @param state true or false enable/disable to get the pdp context dynamic parameter
 * @return success or error
 */
NEUL_RET get_pdp_context_dynamic_param_request_state(PDP_CONTEXT_DYNAMIC_PARAM param_item, bool *state);

/**
 * @brief modify pdp context
 * @param cid cid to modify
 * @param callback pdp modify callback
 * @return NEUL_RET
 */
NEUL_RET modify_pdp_req(uint16 cid, neul_pdp_modify_callback callback);

/**
 * @brief set quality of service (QCI) for pdp context
 * @param cid cid to modify
 * @param qci requested QCI value
 * @return success or error
 */
NEUL_RET set_qos_req(uint16 cid, uint8 qci);

/**
 * @brief Get quality of service (QCI) for pdp context
 * @param cid cid to modify
 * @param qci requested QCI value
 * @return success or error
 */
NEUL_RET get_qos(uint16 cid, uint8 *qci);

/**
 * @brief delete quality of service (QCI) for pdp context
 * @param cid cid to delete
 * @return success or error
 */
NEUL_RET delete_qos(uint16 cid);

/**
 * @brief delete modified TFT packet filters for cid
 * @param cid cid
 * @return success or error
 */
NEUL_RET delete_tft_req(uint16 cid);

/**
 * @brief sets packet filter for TFT
 * @param tft The params of TFT
 * @return success or error
 */
NEUL_RET set_tft_req(tft_context *tft);

/**
 * @brief Get TFT packet filters for cid
 * @param cid cid
 * @param packet_filter designated packet filters for cid
 * @param tft The tft params for designated packet filters
 * @param num_of_packet_filters The number of packet filters for cid
 * @return success or error
 */
NEUL_RET get_tft_context(uint8 cid,uint8 packet_filter, tft_context *tft, uint8 *num_of_packet_filters);

/** @} end of group libNEUL_RADIO */

/**
 * @brief set_ciot_opt parameters
 * @param supported_ue_opt ue support opt
 * @param preferred_ue_opt ue preferred opt
 * @param set_ciot_opt_callback ciot opt callback
 * @return success or error
 */
NEUL_RET set_ciot_opt (uint8 supported_ue_opt, uint8 preferred_ue_opt, neul_set_ciot_opt_callback set_ciot_opt_callback);

/**
 * @brief get_ciot_opt
 * @param supported_ue_opt ue support opt
 * @param preferred_ue_opt ue preferred opt
 * @return success or error
 */
NEUL_RET get_ciot_opt(uint8* supported_ue_opt, uint8* preferred_ue_opt);


/**
 * @brief register radio command pin handler callback
 * @return
 */
void neul_radio_register_pin_handler(neul_sim_pin_ind_callback callback);

/**
 * @brief get cid status
 * @param cid pdp context id
 * @param status socket status
 * @param backoff remaining backoff time value, uint : s, valid only when status is SOCKET_OR_CID_STATUS_BACK_OFF
 * @return NUEL_RET
**/
NEUL_RET get_cid_status(uint8 cid, SOCKET_OR_CID_STATUS *status,uint16 *backoff);

/** @} end of group libNEUL_RADIO */


#endif /* LIB_NEUL_RADIO_H_ */
