/*
 * CclkTime.c
 *
 *  Created on: 2019年5月5日
 *      Author: Administrator
 */
#include "CclkTime.h"


uint8 cclktimeget(struct time *Datetime)
{
	 time_clk current_time; struct tm *FmtDatetime;
	 current_time = get_current_time();
	    if(current_time == 0)
	    {
	        return 1;
	    }
	    FmtDatetime = gmtime(&current_time);
	    if (FmtDatetime == NULL)
	    {
	        return 1;
	    }
	    Datetime->time_year=FmtDatetime->tm_year%100;
	    Datetime->time_mon=FmtDatetime->tm_mon+1;
	    Datetime->time_day=FmtDatetime->tm_mday;
	    Datetime->time_hour=FmtDatetime->tm_hour;
	    Datetime->time_min=FmtDatetime->tm_min;
	    Datetime->time_sec=FmtDatetime->tm_sec;
	    UTCToBeijing(Datetime);
	    return 0;
}

//UTC转换为北京时间  函数可直接调用
void UTCToBeijing(struct time *Datetime)
{
	int year=0,month=0,day=0,hour=0;
    int lastday = 0;// 月的最后一天日期
    int lastlastday = 0;//上月的最后一天日期
	  year=Datetime->time_year+2000;
		month=Datetime->time_mon;
	  day=Datetime->time_day;
	  hour=Datetime->time_hour+8;//UTC+8转换为北京时间

	  if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
		{
        lastday = 31;
        if(month == 3)
				{
            if((year%400 == 0)||(year%4 == 0 && year%100 != 0))//判断是否为闰年
                lastlastday = 29;//闰年的2月为29天，平年为28天
            else
                lastlastday = 28;
        }
        if(month == 8)
            lastlastday = 31;
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11)
		{
        lastday = 30;
        lastlastday = 31;
    }
    else
		{
        lastlastday = 31;
        if((year%400 == 0)||(year%4 == 0 && year%100 != 0))//闰年的2月为29天，平年为28天
            lastday = 29;
        else
            lastday = 28;
    }
		if(hour >= 24)//当算出的时大于或等于24：00时，应减去24：00，日期加一天
		{
				hour -= 24;
				day += 1;
				if(day > lastday)//当算出的日期大于该月最后一天时，应减去该月最后一天的日期，月份加上一个月
				{
						day -= lastday;
						month += 1;

						if(month > 12)//当算出的月份大于12，应减去12，年份加上1年
						{
								month -= 12;
								year += 1;
						}
				}
		}
		Datetime->time_year=year-2000;
		Datetime->time_mon=month;
		Datetime->time_day=day;
		Datetime->time_hour=hour;
}

