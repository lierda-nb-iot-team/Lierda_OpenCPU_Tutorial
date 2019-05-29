/******************************************************************************
 * @内容	用户任务头文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_
//include
#include "neulfw.h"
#include "cmsis_os2.h"
#include "string.h"
#include <assert.h>
#include "HDC1000.h"
#include "lierda_app_main.h"


void lierda_App_main(void);
void lierda_App_task(void *param);
void lierda_server_task(void *param);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_APP_H_ */
