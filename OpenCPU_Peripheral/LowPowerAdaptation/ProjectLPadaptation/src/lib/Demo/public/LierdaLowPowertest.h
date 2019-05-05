/*
 * LierdaLowPowertest.h
 *
 *  Created on: 2019年4月23日
 *      Author: Def_Lin
 */

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_LIERDALOWPOWERTEST_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_LIERDALOWPOWERTEST_H_

#include "cmsis_os2.h"
#include "neulfw.h"
#include "app_at_log.h"
#include "string.h"
#include "assert.h"
#include "lierdaGPIO.h"

osMessageQueueId_t msg_QueueId; //队列ID

void createMsgQueue( void );

void TestKeyInit(PIN key_pin, GPIO_DIRECTION mode);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_LIERDALOWPOWERTEST_H_ */
