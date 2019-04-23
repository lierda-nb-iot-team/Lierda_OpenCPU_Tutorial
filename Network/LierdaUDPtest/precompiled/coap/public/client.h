#ifndef __CLIENT_H__
#define __CLIENT_H__



#define ZZHC_HOST_NAME  "zzhc.vnet.cn"

unsigned int iccid_coap_send(unsigned char *return_recv_data);
unsigned int iccid_1234(unsigned char *return_recv_data);
void client_log(char *log_output);
//int Report(const char *pcFormat, ...);
void watchdog_delay(uint32_t time_cnt);
//static void cmdline_uri(char *arg);
#endif
