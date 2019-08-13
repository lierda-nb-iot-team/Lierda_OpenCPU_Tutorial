/*
 * lierda_network_dealwith.h
 *
 *  Created on: 2019年4月12日
 *      Author:
 */
#ifndef _LIERDA_NETWORK_DEALWITH_H_
#define _LIERDA_NETWORK_DEALWITH_H_

#include "neulfw.h"

// 此枚举类型为初始化设置参数时返回的错误类型
typedef enum
{
	NET_PARA_OK = 0x00,  // 参数初始化正确
	NET_FIRST_PARA_ERROR = 0x01,   // 第一轮离散加网因子时间 (>=1) ，参数错误
	NET_SECOND_PARA_ERROR = 0x02,  // 第一次搜网失败后，第二轮离散加网因子时间 (>=1) ，参数错误
	NET_POWER_MODE_ERROR = 0x03,   // 模组3种功耗模式 DRX， eDRX， PSM ，参数错误
	NET_CYCLIC_NUMBER_ERROR = 0x04,  // 重复执行搜网的次数， 参数错误
	NET_QUERY_CGATT_TIME_ERROR = 0x05, // 每次收网持续时间，循环查询CGATT时间， 参数错误
	NET_NCDP_VALUE_ERROR = 0x06  // NCDP参数，IP,port，  参数错误
}NET_PARA_RET;

typedef enum
{
	DRX = 0x00,
	eDRX = 0x01,
	PSM = 0x02
}POWER_DISSIPATION_MODE;

typedef enum
{
    IOTSTATE_LWM2M_APP_DATA_ENABLED = 0,  // 调换位置   与SDK源码的LWM2M状态的枚举类型，调换位置
    IOTSTATE_LWM2M_MISSING_CONFIG,
    IOTSTATE_LWM2M_INIITIALISING,
    IOTSTATE_LWM2M_INIITIALISED,
    IOTSTATE_LWM2M_INIT_FAILED,
    IOTSTATE_LWM2M_REGISTERING,
    IOTSTATE_LWM2M_REGISTERED,
    IOTSTATE_LWM2M_DEREGISTERED,
	IOTSTATE_LWM2M_UNINITIALISED,     // 8， 调换位置
    IOTSTATE_LWM2M_NO_UE_IP,
    IOTSTATE_LWM2M_REJECTED_BY_SERVER,
    IOTSTATE_LWM2M_TIMEOUT_AND_RETRYING,
    IOTSTATE_LWM2M_REG_FAILED,
    IOTSTATE_LWM2M_DEREG_FAILED,
	UNKNOWN_REG_NET,
	UNKNOWN_ERROR
}LWM2M_CLIENT_IOTSTATE;

extern LWM2M_CLIENT_IOTSTATE  lierda_lwm2m_status;

typedef enum
{
	NETSTATE_CONNECT_OK = 0,   // 1 registered, home network
	NETSTATE_NOT_REGISTERED,   // 0 not registered, MT is not currently searching for an operator to register to
	NETSTATE_NOT_REGISTERED_BUT_MT_TRYING,  // 2 not registered, but MT is currently trying to attach or searching for an operator to register to
    NETSTATE_REGISTRATION_DENIED,  // 3 registration denied
	NETSTATE_UNKNOWN,    // 4 unknown (e.g. out of E-UTRAN coverage), 其他返回状态类型值 >4  统一表示
    NOT_SIM              // 无SIM卡
}NET_CONNECT_STATE;

//此结构体是需要保存到KV区的参数数据
struct NET_Local_Para{
	uint8  first_disperse_factor;  // 上电初始，第一轮离散加网因子时间 (>=1)
	uint8  second_disperse_factor; // 第一次搜网失败后，第二轮离散加网因子时间 (>=1)
	POWER_DISSIPATION_MODE  power_mode;  // 模组3种功耗模式 DRX， eDRX， PSM
	uint8  net_cyclic_number;      // 重复执行搜网的次数
	uint8  query_cgatt_time;       // 单位 s, 每次收网持续时间，循环查询CGATT时间
    char   ncdp_value[25];         // NCDP参数，IP,port
}__attribute__((packed));

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
 *返回值: 0:连接上IOT平台, 非0:未连接上
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

/********************************************************
 *函数: lierda_NET_connect_state
 *入口: None
 *出口: None
 *返回值: 0:连接上网络, 非0:未连接上
 *概述: NB模组是否连接上网络
 ********************************************************/
extern uint8 lierda_NET_connect_state(void);

#endif /* _LIERDA_NETWORK_DEALWITH_H_ */

