/******************************************************************************
 * @brief    nuel dtls  Functions for Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/
#ifndef _DTLS_H_
#define _DTLS_H_

#include "mbedtls/ssl.h"
#include "lwip/udp.h"
#include "neul_kv_storage.h"
#include "rtc.h"
#include "irmalloc.h"
#include "neul_system.h"
#include "los_typedef.h"
#include "app_os_init.h"
#include "cmsis_os2.h"
#include "apps_dtls_keys.h"


//////////////////////handshark define///////////////////
#ifdef Enable_LiteOS
#define DTLS_HANDSHAKE_QUEUE_LEN   (2)
#define DTLS_HANDSHAKE_ITEM_SIZE ( sizeof(UINT32) )
#else
#define DTLS_HANDSHAKE_QUEUE_LEN   (2)
#define DTLS_HANDSHAKE_ITEM_SIZE   (0)
#endif
//The re-handshake time is set to 40 seconds
#define DTLS_HANDSHAKE_CALLBACK_DELAY_FIRST_MO  (500)// (40) //unit s
#define DTLS_CALLBACK_DELAY_FIRST_MO   (40) //unit s

//建链结果返回到DTLS_callback的延时时长
#define DTLS_CALLBACK_DELAY_TIME  (50)  //unit ms
//DTLS链路建立时长
#define DTLS_HANDSHARK_MAX_TIME   ((250)*(1000))//unit ms
//DTLS重协商时长
#define DTLS_RENEGOTIATION_MAX_TIME   ((400)*(1000)) //unit ms
//APP任务前台等待时长
#define DTLS_HANDSHARK_MIN_TIME   (8)  //uint s
//握手及协商消息每个消息发送次数
#define DTLS_HS_MSG_WAIT_TIME_MAX_NUM (4)
#define DTLS_HS_MSG_RESEND_MAX_NUM ((DTLS_HS_MSG_WAIT_TIME_MAX_NUM)-(1))

//ms per min
#define MS_PER_MIN (1000)


//#define TIME_UPDATE_LINK 5
#define DTLS_HANDLESHAKE_MAX_FAIL_COUNT (2)
//365(day) *24(hour) *60(minute)
#define DTLS_MAX_RENEGOTIATE_TIME (525600)
#define DTLS_MIN_RENEGOTIATE_TIME  (1)
#define HANDLE_HANDSHAKE_TIME_OUT ((86400)*(30))
#define STANDARD_DTLS_RENEGOTIATE_TIME (30) //uint s

#define PSK_IS_CONFIGING_FLAG (0xEA)

#define TIME_PSK_CHANGE_REBOOT (60000)  //unit ms
#define TIME_PSK_CONFIGING_REBOOT (600000) //unit ms


//////////////////////dtls encrypt and decrypt///////////////////
#define HANDSHAKE_LEN (2)
#define NAT_LEN (2)
#define PSK_IV_LEN (16)
#define PSK_ID_LEN  (15)
#define PSK_VALUE_LEN  (16)
#define PASSWD_LEN (32)
#define SALT_LEN (8)
#define ROOT_KEY_LEN (16)
#define ITERATION_COUNT (1000)

//////////////////////dtls payload///////////////////
#define DTLS_PBUF_PAYLOAD_LEN  (200)
#define LOG_LEN    (40)

//////////////////////dtls config///////////////////
#define SECURE_LINK (1)
#define UNSECURE_LINK (0)

//for resemeID
#define STANDARD_DTLS (0)
#define OPTIMIZED_DTLS  (1)
#define NO_DTLS          (2)
#define DTLS_INIT_RESUMEID (0x8000000000000000)


//////////////////////other///////////////////
#define UINT8_DATA_LEN (1)
#define UINT16_DATA_LEN (2)
#define UINT32_DATA_LEN (4)
#define UINT64_DATA_LEN (8)


#define DTLS_SENDMSG_QUEUE_LEN    (2)
#define DTLS_INCOMING_QUEUE_LEN   (2)

#ifdef Enable_LiteOS
#define DTLS_SENDMSG_ITEM_SIZE ( sizeof(UINT32) )
#define DTLS_INCOMING_ITEM_SIZE ( sizeof(UINT32) )
#else
#define DTLS_SENDMSG_ITEM_SIZE   (0)
#define DTLS_INCOMING_ITEM_SIZE  (0)
#endif

#define DTLS_CLIENT_HELLO_WITHOUT_COOKIE_DATAGRAM_LEN 95

typedef enum
{ 
        NO_DTLS_TIME_INIT = 0,
        NO_DTLS_TIMEIGN,
        NO_DTLS_TIME_OUT
}NO_DTLS_TIME;

typedef enum
{ 
        DTLS_LOG_LEVEL_NONE = 0,
        DTLS_LOG_LEVEL_BUFF,            
        DTLS_LOG_LEVEL_VERBOSE,
        DTLS_LOG_LEVEL_NORMAL,
        DTLS_LOG_LEVEL_WARNING,
        DTLS_LOG_LEVEL_ERROR
}DTLS_LOG_LEVEL;

typedef enum
{
    DTLS_STATUS_INIT,
    DTLS_STATUS_INITED,
    DTLS_STATUS_HANDSHAKING,
    DTLS_STATUS_HANDSHAKE_SUCCESS,
    DTLS_STATUS_HANDSHAKE_FAIL,
    DTLS_STATUS_RENEGOTIATING,
    DTLS_STATUS_RENEGOTIATION_SUCCESS,
    DTLS_STATUS_RENEGOTIATION_FAIL,
    DTLS_STATUS_PEER_CLOSED,
    DTLS_STATUS_TIMEOUT_AND_FAILED
}DTLS_STATUS;

typedef enum
{
    DTLS_HANDSHAKE_SUCCESS,
    DTLS_INITED,
    DTLS_HANDSHAKING,
    DTLS_HANDSHAKE_FAIL,
}DTLS_STAT;

typedef enum
{
    DTLS_WITH_NAT,
    DTLS_NO_NAT,
}DTLS_NAT;

typedef enum 
{
    DTLS_RET_OK = 0,
    DTLS_RET_ERROR,
    DTLS_RET_CTR_DRBG_SEED_FAILED,
    DTLS_RET_CONFIG_DEFAULTS_FAILED,
    DTLS_RET_CONFIG_PSK_FAILED,
    DTLS_RET_SETUP_FAILED,
    DTLS_RET_SOCKET_FAILED,
    DTLS_RET_CONNECT_FAILED,
    DTLS_RET_HANDSHAKE_FAILED,
    DTLS_RET_WRITE_FAILED,
    DTLS_RET_INITIAL_FAILED,
    DTLS_RET_ALLOC_FAILED,
    DTLS_RET_CONNECTION_CLOSED,
    DTLS_SETUP_AND_RETRYING

}DTLS_RET;

typedef enum
{
    NSECMODE_SEC_PSK = 0,
    NSECMODE_SEC_RPK,
    NSECMODE_SEC_CERT,
    NSECMODE_SEC_DISABLE = 3,    
}NSECMODE_TYPE;

typedef enum
{
    DTLS_STANDARD_PROTOCOL = 0,
    DTLS_OPTIMIZE_PROTOCOL,
    DTLS_INVALID_PROTOCOL = 0xFF,
}DTLS_PROTOCOL_TYPE;

typedef enum
{
    DTLS_DISABLE = 0,
    DTLS_STANDARD,
    DTLS_OPTIMIZE,
    DTLS_HS_TYPE_MAX,
}DTLS_HS_TYPE;

typedef struct
{
    uint8 secmode;
    uint8 psk[PSK_VALUE_LEN];
    uint8 hs_type;
    uint8 psk_id[PSK_ID_LEN];
    uint32 renegotiate_time;
    
}DTLS_CFG;

typedef enum
{
    DTLS_SEND_MSG,
    DTLS_RESEND_MSG,
    DTLS_UPDATE_PSK_CONFIGING,
    DTLS_UPDATE_PSK_FINISH,
    DTLS_CHANGE_SESSION_RESPONSE,//4 //4
    DTLS_NOT_CHANGE_SESSION_RESPONSE,
    DTLS_SESSION_SWTICH_SUCC,
    DTLS_CHANGE_SESSION_REQUEST, 
}DTLS_MSG_TYPE; 

extern osTimerId_t g_renegotiation_timer;
extern osTimerId_t dtls_ostimer_handle;
extern int g_dtls_loglevel;

extern uint8 g_ucDtls_resumeIdCfg;
extern uint8 g_Dtls_link_type;
extern uint64 g_ullDtls_globe_resumeId;
extern uint8 g_dtls_hs_msg_wait_time[];
extern uint8 g_psk_config_flag;

extern void mbedtls_handshake_ssl_resend(void);

#define MAX_DTLS_DEBUG_PRINT_BUFF_LEN  150

#define DTLS_LOG_BUFF(s, buff, len)            do{ \
            dtls_log_print_buff(s, buff, len); \
    }while(0)
#define DTLS_LOG_VERBOSE(s, args...)            do{ \
            APP_COAP_INFO("+LOG[D]" s, ## args);   \
    }while(0)

#define DTLS_LOG_INFO(s, args...)           do{ \
            APP_COAP_INFO("+LOG[I]" s, ## args);   \
    }while(0)

#define DTLS_LOG_WARNING(s, args...)        do{ \
            APP_COAP_WARN("+LOG[W]" s, ## args);   \
    }while(0)

#define DTLS_LOG_ERROR(s, args...)            do{ \
            APP_COAP_ERROR("+LOG[E]" s, ## args);   \
    }while(0)

DTLS_STATUS dtls_get_dtls_status(void);
void dtls_set_dtls_status(DTLS_STATUS status);
bool dtls_is_handshake_suceess(void);
void dtls_send_to_handshake_queue_from_isr(void);
//dtls_pcb *dtls_new_dpcb(struct udp_pcb *upcb);
dtls_pcb *dtls_new_dpcb(uint8 endpoint,uint8 *psk,uint8 *psk_id);
DTLS_RET dtls_ssl_write(dtls_pcb *dpcb, struct pbuf *p);
DTLS_RET dtls_set_secmode(uint8 data);
DTLS_RET dtls_set_psk(uint8 * data, uint16 psk_type);
DTLS_RET dtls_read_secmode_config(void);
DTLS_RET dtls_get_secmode_config(uint8 *hs_type, uint8 *psk, uint8 *psk_id, uint8 *NAT_type);
DTLS_RET dtls_get_pskid(uint8 *data, uint16 pskid_type);
void dtls_reSetup_timed_out(void);
void dtls_ssl_recv(struct dtls_pcb *dpcb, udp_recv_fn recv, void *recv_arg);
void dtls_dpcb_free(dtls_pcb *dpcb);
void test_srand(unsigned long seed);
int dtls_random_poll(void *data, unsigned char *output, size_t len, size_t *olen);
int dtls_random( uint8 *output, uint8 len, uint16 *olen );
DTLS_RET dtls_read_new_secmode_config(void);

DTLS_RET dtls_get_sendto_result(void);
void dtls_ssl_free(mbedtls_ssl_context *ssl);
void dtls_log_print_buff(const char *text, const unsigned char *buf, size_t len);
void dtls_ssl_dispacth(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
DTLS_RET dtls_pbkdf2(unsigned char* password,size_t passwdlen,unsigned char* salt,size_t saltlen,unsigned char *output);
DTLS_RET dtls_get_rootkey(uint8 *data);
DTLS_RET dtls_get_psk(uint8 *psk, uint16 psk_type);
DTLS_RET dtls_set_handshake_type(uint8  data, uint16 hs_kv_type);
DTLS_HS_TYPE dtls_get_handshake_type(void);
DTLS_RET dtls_security_info_set(uint8 mode, uint8 hs_type, uint8 *psk, uint8* pskid, uint32 renegotiate_time);
DTLS_RET dtls_get_remote_sec_swt(uint8 *swt);
uint32 dtls_get_hdrlen(void);
DTLS_RET dtls_ModLocalCfg(void);
void dtls_renegotiation_timed_out(void);
uint8 dtls_read_nsecswt_config(uint16 hs_kv_type, uint16 nat_kv_type);
uint8 dtls_set_nsecswt_config(uint8 *p_atparams_string, uint16 hs_kv_type, uint16 nat_kv_type);
DTLS_RET dtls_handshake(dtls_pcb * dpcb);
void dtls_callback(void);
DTLS_RET dtls_ssl_send_proc(dtls_pcb *dpcb, struct pbuf *p);
DTLS_RET update_link(void);
DTLS_RET dtls_resetLink(void);
void dtls_set_status_fail(void);
bool dtls_create_mutex(void);
DTLS_RET dtls_take_mutex(void);
void dtls_give_mutex(void);
void dtls_main( void *unused );
void dtls_send_to_incoming_queue(uint32 state);
void dtls_send_to_incoming_queue_from_isr(uint32 state);
void dtls_create_queue(void);
DTLS_RET dtls_setup_link(dtls_pcb * dpcb);
DTLS_RET dtls_start_renegotation(dtls_pcb *dpcb);
bool dtls_get_renegotiation_timed_out(void);
uint8 dtls_set_nsetpsk_config(uint8 *p_atparams_string, uint16 psk_type, uint16 pskid_type);
uint8 dtls_read_nsetpsk_config(uint16 psk_type, uint16 pskid_type);
DTLS_RET dtls_start_timer(uint64_t time);
void dtls_wait_for_init(void);
DTLS_RET dtls_set_pskid(uint8 * data, uint16 pskid_type);
DTLS_RET dtls_set_NAT_type(uint8 data, uint16 nat_kv_type);
DTLS_RET dtls_get_NAT_type(uint8 *data, uint16 nat_kv_type);
DTLS_RET dtls_swt_check(uint8 swt);
DTLS_RET dtls_pskid_check(uint8 psk_len);
DTLS_RET dtls_psk_check(uint8 psk_len);
DTLS_RET dtls_protocol_type_check(uint8 swt,uint8 protocol_type);
uint8 dtls_swt_cfg_convert(uint8 swt,uint8 protocol_type);
DTLS_RET dtls_get_kv_handshake_type(uint8 *data, uint16 hs_kv_type);
DTLS_RET dtls_read_bs_secmode_config(void);
DTLS_RET dtls_get_bs_secmode_config(uint8 *hs_type, uint8 *psk, uint8 *psk_id, uint8 *NAT_type);









#endif

