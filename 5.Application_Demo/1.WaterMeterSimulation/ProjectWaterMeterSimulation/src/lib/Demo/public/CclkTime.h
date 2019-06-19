/*
 * CclkTime.h
 *
 *  Created on: 2019Äê5ÔÂ5ÈÕ
 *      Author: Administrator
 */

#ifndef SRC_LIB_DEMO_PUBLIC_CCLKTIME_H_
#define SRC_LIB_DEMO_PUBLIC_CCLKTIME_H_
#include "neulfw.h"
#include "cmsis_os2.h"
#include "string.h"
#include <assert.h>
#include "lierda_app_main.h"
#include "rtc.h"
#include "time.h"

typedef unsigned long time_clk;
struct time
{
    uint8 time_sec;
    uint8 time_min;
    uint8 time_hour;
    uint8 time_day;
    uint8 time_mon;
    uint8 time_year;
};

uint8 cclktimeget(struct time *Datetime);
void UTCToBeijing(struct time *Datetime);
#endif /* SRC_LIB_DEMO_PUBLIC_CCLKTIME_H_ */
