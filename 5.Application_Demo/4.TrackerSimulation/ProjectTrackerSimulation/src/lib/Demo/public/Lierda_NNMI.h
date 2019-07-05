/******************************************************************************
* @内容	NNMI头文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#ifndef SRC_LIB_OPENMCU_PUBLIC_LIERDA_NNMI_H_
#define SRC_LIB_OPENMCU_PUBLIC_LIERDA_NNMI_H_
#include "neulfw.h"
#include "led.h"
#define NNMI_BUFFSIZE 256
extern uint8 nnmi_buff[NNMI_BUFFSIZE];
extern uint16 nnmi_datalen;
void lierda_MMNI_task(void *unused);
int lierdaLog_NNMI(const char *pcFormat, ...);


#endif /* SRC_LIB_OPENMCU_PUBLIC_LIERDA_NNMI_H_ */
