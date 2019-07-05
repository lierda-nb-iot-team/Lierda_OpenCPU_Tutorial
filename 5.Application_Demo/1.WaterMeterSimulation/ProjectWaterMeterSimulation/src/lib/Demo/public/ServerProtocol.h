/*
 * ServerProtocol.h
 *
 *  Created on: 2019年5月21日
 *      Author: Administrator
 */

#ifndef SRC_LIB_DEMO_PUBLIC_SERVERPROTOCOL_H_
#define SRC_LIB_DEMO_PUBLIC_SERVERPROTOCOL_H_
#include "app.h"
#include "neulfw.h"
#include "cmsis_os2.h"
#include "string.h"
#include <assert.h>
#include "led.h"
#include "CclkTime.h"
#include "lierda_app_main.h"
#include "lierdaCloudConnected.h"
#include "lierda_module_status.h"
#include "Lierda_NNMI.h"
#include "rtc.h"
#include "Lierda_Hdgps.h"



#define BigtoLittle16(A)   (( ((uint16)(A) & 0xff00) >> 8)    |  (( (uint16)(A) & 0x00ff) << 8))

#define BigtoLittle32(A)   ((( (uint32)(A) & 0xff000000) >> 24) | \
                                       (( (uint32)(A) & 0x00ff0000) >> 8)   | \
                                         (( (uint32)(A) & 0x0000ff00) << 8)   | \
                                       (( (uint32)(A) & 0x000000ff) << 24))

#define BigtoLittle64(A)              ((( (uint64)(A) & 0xff00000000000000) >> 56) | \
                                       (( (uint64)(A) & 0x00ff000000000000) >> 40)   | \
                                       (( (uint64)(A) & 0x0000ff0000000000) >> 24)   | \
                                       (( (uint64)(A) & 0x000000ff00000000) >> 8) |  \
                                       (( (uint64)(A) & 0x00000000ff000000) << 8)  |           \
                                       (( (uint64)(A) & 0x0000000000ff0000) << 24)   |         \
                                       (( (uint64)(A) & 0x000000000000ff00) << 40)   |         \
                                       (( (uint64)(A) & 0x00000000000000ff) << 56))
//因为编译器为小端模式，协议要求为大端模式 所以把一些数据高低位交换了一下
#define PACK_HEAD_POS		0xFFAA
#define	TIMIN_NOTIFY		0xD0D0
#define	NOTIFY_ACK			0xD1D1
#define PACK_HEAD           0xAAFF
#define SERVER_CMD_REG      0xD1D3
#define SERVER_CMD_REG_RSP	0xD2D3
#define PRITOCOL_VERSION	0x00

#define	NOTIFY_PACK_HEAD	60
#define NOTIFY_ACK_PACK_LEN	32
#define UE_REPLY_PACK_HEAD	24

#define	EVK_PACK_LEN		24
#define	SIMULATE_WATER_LEN	79
#define	SIMULATE_LIGHT_LEN	17

//服务器下发的的读取、控制命令
#define READ_VERSION		0xC001
#define READ_SCENES_NUM		0xC002
#define	SET_NOTIFY_MODE		0xC101
#define	SWITCH_UE_SCENES	0xC102
#define	CTR_UE_PERIPHERAL	0xC103
#define EVK_SIMULATE_WATER	0xC104
#define	EVK_SIMULATE_LIGHT	0xC105

#define IMEI_LEN			15
#define IMSI_LEN			15
#define ICCID_LEN			20
#define	SERVER_BUFF_MAXLEN	512

#define LIERDA_LWM2M_STAT           "AT+NMSTATUS?"
#define LIERDA_SET_EDRX_OFF         "AT+CEDRXS=0,5,0101"
#define LIERDA_SET_PSM_OFF       	"AT+CPSMS=0"
#define LIERDA_SET_PSM_ON       	"AT+CPSMS=1"
#define LIERDA_SET_NCDP       		"AT+NCDP=180.101.147.115,5683"
#define LIERDA_NRB                  "AT+NRB"
#define LIERDA_NNMI					"AT+NNMI=1"
#define LIERDA_NMGS                 "AT+NMGS="
#define LIERDA_GET_IMEI				"AT+CGSN=1"
#define LIERDA_GET_IMSI				"AT+CIMI"
#define LIERDA_GET_ICCID			"AT+NCCID"
#define LIERDA_GET_CGATT			"AT+CGATT?"
#define LIERDA_MLWULDATAEX			"AT+MLWULDATAEX="
#define LIERDA_NMGR					"AT+NMGR"
#define LIERDA_CCLK					"AT+CCLK?"
#define LIERDA_NUESTATS				"AT+NUESTATS"

#define READ_CCLK					"+CCLK:"
#define SIGNAL_POWR					"Signal power:"
#define SNR							"SNR:"
#define ECL							"ECL:"
#define RSRQ						"RSRQ:"
#define CELL_ID						"Cell ID:"

#define	UNKNOWN						0
#define	PSM_MODE					1
#define	DRX_MODE					2
#define	EDRX_MODE					3

#define	EVK					2
#define SCENES_WATER		5
#define SCENES_LIGHT		6



//电池电量 百分比
#define BATTER				100
//电池阈值
#define BATTER_THRESHOLD    20

typedef struct NUESTATS{
	short 	Rsrp;
	short 	Snr;
	uint8 	Coverage_level;
	short   Rsrq;
	uint32	Cell_ID;

}NueStats;
//注册消息 数据段帧格式
struct RegDataFormat1{

				uint8 	IMEI_Len;
				char 	ModuleIMEI[IMEI_LEN];
				uint8   IMSI_Len;
				char    ModuleIMSI[IMSI_LEN];
				uint8   ICCID_Len;
				char    ModuleICCID[ICCID_LEN];

}__attribute__((packed));
//注册消息帧格式
struct RegProtocolFrame1{

				uint16 					PackHead;    		//包头 固定0xFFAA
				uint16 					CmdWord;			//命令字
				uint8  					Pritocol_Ver;		//协议版本
				uint16 					PackDataLen;		//从起始位到校验位总长度、不包括校验位
				struct RegDataFormat1 	RegData;			//注册协议数据
				uint8  					Crc;				//校验位

}__attribute__((packed));


//注册应答消息 数据段帧格式
struct RegRSPDataFormat1{

				uint8 	IMEI_Len;
				char 	ModuleIMEI[IMEI_LEN];
				uint8 	RegVlaueLen;
				uint8   RegVlaue;

}__attribute__((packed));

//注册消息应答帧格式
struct RegProtocoRSPFrame1{

				uint16 						PackHead;    		//包头 固定0xFFAA
				uint16 						CmdWord;			//命令字
				uint8  						Pritocol_Ver;		//协议版本
				uint16 						PackDataLen;		//从起始位到校验位总长度、不包括校验位
				struct RegRSPDataFormat1 	RegRSPData;			//注册应答数据
				uint8  						Crc;				//校验位

}__attribute__((packed));

struct NOtifyFormat1{

			uint16 		PackHead;    		//包头 固定0xFFAA
			uint16 		CmdWord;			//命令字
			uint8  		Pritocol_Ver;		//协议版本
			uint16 		PackDataLen;		//从起始位到校验位总长度、不包括校验位
			uint8 		IMEI_Len;
			char 		ModuleIMEI[IMEI_LEN];
			uint32		NotifyCycle;
			uint32		Send_PackNum;
			uint32 		ACK_PackNum;
			uint64		Timestamp;
			short 		Rsrp;
			short		Snr;
			uint8 		Coverage_level;
			short 		Rsrq;
			uint32		Cell_ID;
			uint8 		Power_mode;
			uint16 		ResendNum;
			uint8 		flag;
			uint16		FillingDataLen;

}__attribute__((packed));

struct GPS_INFO{

			uint8 		Position;
			uint32		longitude;
			uint32		latitude;

}__attribute__((packed));

struct Water_Pack{

	uint8 		Scenes;
	uint32		BillingReading;
	uint32		CurrReading;
	char		AcquisitionTime[16];
	int16		InternalTemper;
	uint32		Day_CumulativeFlow;
	uint32		Day_CumulativeReverseFlow;
	uint32		Day_MaxFlow;
	char		Timestamp[16];
	uint16		IntervalFlow;
	uint16		WaterPressure;
	int16		WaterTemper;
	uint16		AcousticVibration;
	uint32		AlarmInfo;
	uint8		battery;
	uint8		BatteryThreshold;
	uint8		ValveState;
	struct GPS_INFO	GpsInfo;

}__attribute__((packed));

void Lierda_ServerSendData(void);
void lierdaSendMsg(uint8* databuff,uint16 datalen);
void Lierda_ServerReg(void);
void lierda_RegMsgRecv(uint8* databuff);
uint8 DataAccumulateSumCRC(void *DataBuff, uint16 DataLen);
void RegMsgProtocolAnalysis(uint8 *ProtocolData);
void GetNUESTATS_DelaWith(NueStats *ModuleState);
#endif /* SRC_LIB_DEMO_PUBLIC_SERVERPROTOCOL_H_ */
