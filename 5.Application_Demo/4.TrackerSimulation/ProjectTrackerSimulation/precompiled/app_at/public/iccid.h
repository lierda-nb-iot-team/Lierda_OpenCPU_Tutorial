/*
 * iccid.h
 *
 *  Created on: 2017Äê8ÔÂ10ÈÕ
 *      Author: Administrator
 */

#ifndef __ICCID_H__
#define __ICCID_H__


//#include "app_at_log.h"

#define USER_ADDRESS   0x19D000
#define ICCID_ADDRESS  (USER_ADDRESS + 0X10)
#define MAX_APN_SIZE    200

#define PLMN_RESULT_CTNB   	0
#define PLMN_RESULT_NBIOT   1
#define PLMN_RESULT_CMNB   	2

#define CT_IOT_APN   "ctnb"
#define LT_IOT_APN   "nbiot"
#define YD_IOT_APN   "CMNBIOT"




#define ICCID_READ_KEY  (134*256+8)
#define ICCID_DATA_KEY  (134*256+9)

#define ICCID_CTRL_KEY  (134*256+10)

#define ICCID_CANLE_RUN  5


unsigned char get_apn_result(void);
void iccid_register(void *unused_p);
unsigned char check_iccid(char *iccid_sim_temp);
uint8 check_connect_state(void);
char * base64_encode( const unsigned char * bindata, char * base64, int binlength );
//void iccid_recv_data(void);
void cjson_create(char *send_data);
int8 iccid_data_write_eflash(uint32 iccid_addr, uint8* buffer_addr, uint16 buffer_len);
uint8 get_register_ip(void);
void ota_wait_for_iccid(void);
unsigned char iccid_result(void);
void set_iccid_result(unsigned char temp_num);
int Report(const char *pcFormat, ...);
void iccid_kv_set_zero(void);
unsigned char iccid_kv_result(void);
#endif /* SRC_APP_STANDARD_APPLICATION_CORE_ICCID_H_ */
