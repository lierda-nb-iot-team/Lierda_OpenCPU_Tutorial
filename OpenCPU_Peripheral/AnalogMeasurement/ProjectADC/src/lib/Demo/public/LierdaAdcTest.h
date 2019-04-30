/*
 * LierdaAdcTest.h
 *
 *  Created on: 2019Äê4ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef SRC_LIB_DEMO_PUBLIC_LIERDAADCTEST_H_
#define SRC_LIB_DEMO_PUBLIC_LIERDAADCTEST_H_
#include "neulfw.h"
#include "cmsis_os2.h"
#include "string.h"
#include <assert.h>
#include "lierda_app_main.h"
#include "lierdaADC.h"

#define AIO0 0
#define AIO1 1

void AdcSampTest(void);
void AdcSampInit(void);

#endif /* SRC_LIB_DEMO_PUBLIC_LIERDAADCTEST_H_ */
