/*
 * LierdaDACtest.c
 *
 *  Created on: 2019年4月23日
 *      Author: Def_Lin
 */
#include "LierdaDACtest.h"


void Lierda_DAC_Init(void)
{
	lierdaDACInit(); //DAC初始化

	lierdaDACSetRange(3);//设置DAC输出电压范围

	lierdaDACConnect(LIERDA_AIO1);//用于建立DAC连接AIO引脚
}


