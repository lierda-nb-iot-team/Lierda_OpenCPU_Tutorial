/*
 * LierdaUDPtest.h
 *
 *  Created on: 2019Äê4ÔÂ23ÈÕ
 *      Author: Def_Lin
 */

#ifndef SRC_APP_REFERENCE_APPLICATION_CORE_LIERDAUDPTEST_H_
#define SRC_APP_REFERENCE_APPLICATION_CORE_LIERDAUDPTEST_H_

#include "cmsis_os2.h"
#include "neulfw.h"
#include "app_at_log.h"
#include "string.h"
#include "assert.h"
#include "lierdaNNMIData.h"
#include "lierda_module_status.h"



uint8 socketID;

void lierdaUDPsend(void);

#endif /* SRC_APP_REFERENCE_APPLICATION_CORE_LIERDAUDPTEST_H_ */
