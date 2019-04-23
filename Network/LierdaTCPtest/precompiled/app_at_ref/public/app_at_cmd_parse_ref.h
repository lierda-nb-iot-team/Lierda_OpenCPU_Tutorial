/******************************************************************************
 * @file app_at_module_lwm2m.c
 * @brief TUP module AT handling and interface
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/
#ifndef    _APP_AT_CMD_PARSE_REF_H_
#define    _APP_AT_CMD_PARSE_REF_H_
#include "platform_definitions.h"
#include "app_at.h"
#include "dns.h"

typedef enum {
    LWM2M_RET_OK = 0,
    LWM2M_RET_ERROR = 1,
    LWM2M_RET_NO_MESSAGES = 2,
    LWM2M_RET_FLOW_CONTROL = 3,
    LWM2M_RET_MISSING_CONFIG = 4,
    LWM2M_RET_NOT_REGISTERED = 5,
    LWM2M_RET_ERROR_MEMORY   = 6,
    LWM2M_RET_INIT_FAILED    = 7
}LWM2M_RET;

typedef enum{
    APP_AT_NNMI_MODE_NO_INDICATION = 0,
    APP_AT_NNMI_MODE_INDICATION_AND_MESSAGE,
    APP_AT_NNMI_MODE_INDICATION_ONLY,
}APP_AT_NNMI_MODE;

typedef enum{
    APP_AT_NSMI_MODE_NO_INDICATION = 0,
    APP_AT_NSMI_MODE_INDIACTION,
}APP_AT_NSMI_MODE;

LWM2M_RET lwm2m_get_config(char *addr, uint16 *port, uint8 *id_len, uint8 *id);
AT_RET at_handle_lwm2m_NCDP_cmd_read(void);
AT_RET at_handle_lwm2m_NCDP_cmd_set(uint8 *p_atparams_string);
AT_RET at_handle_MBOOTSTRAPHOLDOFF_cmd_set(uint8 * p_atparams_string);
AT_RET at_handle_MBOOTSTRAPHOLDOFF_cmd_read(void);
LWM2M_RET get_lwm2m_config(char *server_addr, uint16 *port);
LWM2M_RET get_bootstrap_config(char *addr, uint16 * port);
LWM2M_RET set_lwm2m_config(char *server_addr, uint16 *port);
LWM2M_RET set_bootstrap_config(char* addr, uint16 * port);
AT_RET at_handle_MBOOTSTRAPSERVERIP_cmd_set(uint8 * p_atparams_string);
AT_RET at_handle_MBOOTSTRAPSERVERIP_cmd_read(void);
AT_RET at_handle_MLWEPNS_cmd_set(uint8 * p_atparams_string);
AT_RET at_handle_MLWEPNS_cmd_read(void);
AT_RET at_handle_MLWSREGIND_cmd_set(uint8 * p_atparams_string);
AT_RET at_handle_MLWULDATA_cmd_set(uint8 * p_atparams_string);
AT_RET at_handle_MLWULDATAEX_cmd_set(uint8 * p_atparams_string);
AT_RET at_handle_MLWULDATASTATUS_cmd_read(void);
AT_RET at_handle_MLWFOTAIND_cmd_set(uint8 *p_atparams_string);
AT_RET at_handle_MLWFOTAIND_cmd_read(void);
AT_RET at_handle_MREGSWT_cmd_set(uint8 *p_atparams_string);
AT_RET at_handle_MREGSWT_cmd_read(void);
void app_at_cmd_ref_init(void);
void lwm2m_recv_appdata_callback_init(void);
bool check_if_NCDP_be_set(void);

#endif // _APP_AT_MODULE_LWM2M_H_
