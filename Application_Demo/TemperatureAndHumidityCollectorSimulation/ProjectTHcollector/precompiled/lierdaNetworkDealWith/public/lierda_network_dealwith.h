/*
 * lierda_network_dealwith.h
 *
 *  Created on: 2019年4月12日
 *      Author:
 */
#ifndef _LIERDA_NETWORK_DEALWITH_H_
#define _LIERDA_NETWORK_DEALWITH_H_

#include "neulfw.h"

#define IMEI_LEN			15
#define IMSI_LEN			15
#define ICCID_LEN			20

//此结构体为系统用到的一些全局变量，为了统一管理放到一个结构体内，后续有其他变量建议都放到这里
typedef struct NET_AppSystem1{

	uint8 DiscreteCGATT_State;
	//上电初始化就读出来的模组基本信息IMEI, IMSI, ICCID
	char Module_IMEI  [IMEI_LEN+1];
	char Module_IMSI  [IMSI_LEN+1];
	char Module_ICCID [ICCID_LEN+1];

	char RandomSeed[9];		 // 计算离散加网延时因子的种子   IMEI后8位
	uint16 DiscreteFactor;   // 离散加网延时因子 单位：s
	uint8 CGATT_Status;      // 模组是否附着上网络?  1为附着上，0为未附着
	uint8  NetCyclicNumber;  // 加网循环次数

}NET_AppSystem;

extern NET_AppSystem  AppSysTem;

// 此枚举类型为初始化设置参数时返回的错误类型
typedef enum
{
	NET_PARA_OK = 0x00,
	NET_FIRST_PARA_ERROR = 0x01,
	NET_SECOND_PARA_ERROR = 0x02,
	NET_EDRX_ERROR = 0x03,
	NET_PSM_ERROR = 0x04,
	NET_CYCLIC_NUMBER_ERROR = 0x05,
	NET_QUERY_CGATT_TIME_ERROR = 0x06,
	NET_NCDP_VALUE_ERROR = 0x07,
}NET_PARA_RET;

//此结构体是需要保存到KV区的参数数据
struct NET_Local_Para{
	uint8  net_para_flag;
	uint8  first_disperse_factor;  // 第一轮离散加网因子 (>=1)
	uint8  second_disperse_factor; // 第二轮离散加网因子 (>=1)
	uint8  edrx_mode;              // 1为PSM模式，0相反
	uint8  psm_mode;               // 1为eDRX模式，0相反
	uint8  net_cyclic_number;      // 重复执行搜网的次数
	uint8  query_cgatt_time;       // 单位 min, 每次收网持续时间，循环查询CGATT时间
    char   ncdp_value[25];         // NCDP参数，IP,port
}__attribute__((packed));

struct NUESTATS{
	int16 	Rsrp;   // 有符号
	int16 	Snr;    // 有符号
	uint32	Cell_ID;
	uint8 	Coverage_level;
	uint16   PCI;
}__attribute__((packed));

extern struct NUESTATS ModuleState;
/********************************************************
 *函数: lierda_net_local_config_init
 *入口: None
 *出口: None
 *返回值:
 *概述: 初始化设置参数
 ********************************************************/
extern NET_PARA_RET lierda_net_local_config_init(struct NET_Local_Para *p_local_para);

/********************************************************
 *函数: lierda_network_dealwith_task_enable
 *入口: None
 *出口: None
 *返回值:
 *概述: 创建并启动NB网络注册任务线程
 ********************************************************/
extern void lierda_network_dealwith_task_enable(void);

/********************************************************
 *函数: lierda_IOT_connect_state
 *入口: None
 *出口: None
 *返回值: 1:连接上IOT平台, 0:未连上
 *概述: NB模组是否接上IOT平台
 ********************************************************/
extern uint8 lierda_IOT_connect_state(void);

/********************************************************
 *函数: lierda_CGATT_state
 *入口: None
 *出口: None
 *返回值: 1:附着上网络, 0:未附着
 *概述: NB模组是否附着上网络
 ********************************************************/
extern uint8 lierda_CGATT_state(void);

#endif /* _LIERDA_NETWORK_DEALWITH_H_ */

