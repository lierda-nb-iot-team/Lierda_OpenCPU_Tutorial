/*
 * lierda_network_dealwith.h
 *
 *  Created on: 2019��4��12��
 *      Author:
 */
#ifndef _LIERDA_NETWORK_DEALWITH_H_
#define _LIERDA_NETWORK_DEALWITH_H_

#include "neulfw.h"

// ��ö������Ϊ��ʼ�����ò���ʱ���صĴ�������
typedef enum
{
	NET_PARA_OK = 0x00,  // ������ʼ����ȷ
	NET_FIRST_PARA_ERROR = 0x01,   // ��һ����ɢ��������ʱ�� (>=1) ����������
	NET_SECOND_PARA_ERROR = 0x02,  // ��һ������ʧ�ܺ󣬵ڶ�����ɢ��������ʱ�� (>=1) ����������
	NET_POWER_MODE_ERROR = 0x03,   // ģ��3�ֹ���ģʽ DRX�� eDRX�� PSM ����������
	NET_CYCLIC_NUMBER_ERROR = 0x04,  // �ظ�ִ�������Ĵ����� ��������
	NET_QUERY_CGATT_TIME_ERROR = 0x05, // ÿ����������ʱ�䣬ѭ����ѯCGATTʱ�䣬 ��������
	NET_NCDP_VALUE_ERROR = 0x06  // NCDP������IP,port��  ��������
}NET_PARA_RET;

typedef enum
{
	DRX = 0x00,
	eDRX = 0x01,
	PSM = 0x02
}POWER_DISSIPATION_MODE;

typedef enum
{
    IOTSTATE_LWM2M_APP_DATA_ENABLED = 0,  // ����λ��   ��SDKԴ���LWM2M״̬��ö�����ͣ�����λ��
    IOTSTATE_LWM2M_MISSING_CONFIG,
    IOTSTATE_LWM2M_INIITIALISING,
    IOTSTATE_LWM2M_INIITIALISED,
    IOTSTATE_LWM2M_INIT_FAILED,
    IOTSTATE_LWM2M_REGISTERING,
    IOTSTATE_LWM2M_REGISTERED,
    IOTSTATE_LWM2M_DEREGISTERED,
	IOTSTATE_LWM2M_UNINITIALISED,     // 8�� ����λ��
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
	NETSTATE_UNKNOWN,    // 4 unknown (e.g. out of E-UTRAN coverage), ��������״̬����ֵ >4  ͳһ��ʾ
    NOT_SIM              // ��SIM��
}NET_CONNECT_STATE;

//�˽ṹ������Ҫ���浽KV���Ĳ�������
struct NET_Local_Para{
	uint8  first_disperse_factor;  // �ϵ��ʼ����һ����ɢ��������ʱ�� (>=1)
	uint8  second_disperse_factor; // ��һ������ʧ�ܺ󣬵ڶ�����ɢ��������ʱ�� (>=1)
	POWER_DISSIPATION_MODE  power_mode;  // ģ��3�ֹ���ģʽ DRX�� eDRX�� PSM
	uint8  net_cyclic_number;      // �ظ�ִ�������Ĵ���
	uint8  query_cgatt_time;       // ��λ s, ÿ����������ʱ�䣬ѭ����ѯCGATTʱ��
    char   ncdp_value[25];         // NCDP������IP,port
}__attribute__((packed));

/********************************************************
 *����: lierda_net_local_config_init
 *���: None
 *����: None
 *����ֵ:
 *����: ��ʼ�����ò���
 ********************************************************/
extern NET_PARA_RET lierda_net_local_config_init(struct NET_Local_Para *p_local_para);

/********************************************************
 *����: lierda_network_dealwith_task_enable
 *���: None
 *����: None
 *����ֵ:
 *����: ����������NB����ע�������߳�
 ********************************************************/
extern void lierda_network_dealwith_task_enable(void);

/********************************************************
 *����: lierda_IOT_connect_state
 *���: None
 *����: None
 *����ֵ: 0:������IOTƽ̨, ��0:δ������
 *����: NBģ���Ƿ����IOTƽ̨
 ********************************************************/
extern uint8 lierda_IOT_connect_state(void);

/********************************************************
 *����: lierda_CGATT_state
 *���: None
 *����: None
 *����ֵ: 1:����������, 0:δ����
 *����: NBģ���Ƿ���������
 ********************************************************/
extern uint8 lierda_CGATT_state(void);

/********************************************************
 *����: lierda_NET_connect_state
 *���: None
 *����: None
 *����ֵ: 0:����������, ��0:δ������
 *����: NBģ���Ƿ�����������
 ********************************************************/
extern uint8 lierda_NET_connect_state(void);

#endif /* _LIERDA_NETWORK_DEALWITH_H_ */

