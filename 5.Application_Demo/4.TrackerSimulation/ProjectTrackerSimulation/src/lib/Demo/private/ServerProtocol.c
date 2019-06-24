/*
 * ServerProtocol.c
 *
 *  Created on: 2019年5月21日
 *      Author: Administrator
 */
#include "ServerProtocol.h"
struct RegProtocolFrame1 RegProtocolFrame;
uint8  Server_SendBuff[SERVER_BUFF_MAXLEN];
uint8 GpsDtaBuff[300]={0};
struct NOtifyFormat1 SendDataNOtify;

static struct RegProtocolFrame1* RegMsgFilling(void);
static struct NOtifyFormat1* SendDataFilling(void);
static void Tracker_DataFilling(uint8 *FillingBuff);
static void lierda_RegMsgSend(void);
static void Lierda_Server_Protocol_Analysis(uint8 * databuff);


static struct RegProtocolFrame1* RegMsgFilling(void)
{
	uint16 dataLen = 0;

	RegProtocolFrame.PackHead = PACK_HEAD;

	RegProtocolFrame.CmdWord = SERVER_CMD_REG;

	RegProtocolFrame.Pritocol_Ver = PRITOCOL_VERSION;

	dataLen = sizeof(struct RegProtocolFrame1) -1;	//减掉最后的校验位
	//因为编译器为小端模式，协议要求为大端模式 所以把一些数据高低位交换了一下
	RegProtocolFrame.PackDataLen = (dataLen << 8);

	RegProtocolFrame.RegData.IMEI_Len = IMEI_LEN;
	strncpy(RegProtocolFrame.RegData.ModuleIMEI, Lierda_SysValue.Module_IMEI, IMEI_LEN);

	RegProtocolFrame.RegData.IMSI_Len = IMSI_LEN;
	strncpy(RegProtocolFrame.RegData.ModuleIMSI, Lierda_SysValue.Module_IMSI, IMSI_LEN);

	RegProtocolFrame.RegData.ICCID_Len = ICCID_LEN;
	strncpy(RegProtocolFrame.RegData.ModuleICCID, Lierda_SysValue.Module_ICCID, ICCID_LEN);

	//包头不参与校验和计算
	RegProtocolFrame.Crc = DataAccumulateSumCRC(&RegProtocolFrame.CmdWord, dataLen-2);

	return &RegProtocolFrame;
}
uint8 DataAccumulateSumCRC(void *DataBuff, uint16 DataLen)
{
	uint16 crc=0;
	uint16 i;
	uint8 *Ptr = (uint8*)DataBuff;

    for(i=0; i < DataLen; i++)
    {
    	crc += *Ptr++;
    }
	return (uint8)(crc&0xff);  // 取低位字节
}

static void lierda_RegMsgSend(void)
{
	struct RegProtocolFrame1  *RegProtocol=NULL;

	RegProtocol = RegMsgFilling();
	if(RegProtocol!=NULL)
	{
		 memcpy(Server_SendBuff,(uint8 *)RegProtocol,sizeof(struct RegProtocolFrame1));
		lierdaSendMsg(Server_SendBuff, sizeof(struct RegProtocolFrame1));
	}
}

void lierdaSendMsg(uint8* databuff,uint16 datalen)
{
	uint16 len=0;
	lierdaLog_NNMI("\r\n\r\n");
	lierdaLog_NNMI("len=%d  databuff:\r\n",datalen);
	for(len=0;len<datalen;len++)
	{
		lierdaLog_NNMI("%02x",databuff[len]);
	}
	lierdaLog_NNMI("\r\n\r\n");
	 lierdaSendMsgToPlatform(databuff, datalen, MSG_NON_NORAI,0,1);
	 SendDataled();
	 Lierda_SysValue.SendDataNum++;
	 //发送数据闪灯
}
void Lierda_ServerReg(void)
{
	Lierda_SysValue.DeviceSta=Device_Reg;
	do
	{

		lierda_module_status_read();
		if(strstr(module_status.charNMSTATUS,"MO_DATA_ENABLED")==NULL)
		{
			lierdaLog("OC 平台未注册");
			osDelay(1000);
		}
	}while(strstr(module_status.charNMSTATUS,"MO_DATA_ENABLED")==NULL);
	lierdaLog("OC 平台注册成功");
	lierda_RegMsgSend();
}

void RegMsgProtocolAnalysis(uint8 *ProtocolData)
{
	struct RegProtocoRSPFrame1 *RegProtocoRSP=NULL;
	RegProtocoRSP = (struct RegProtocoRSPFrame1 *)ProtocolData;
	if(RegProtocoRSP->PackHead == PACK_HEAD)
	{
		if(RegProtocoRSP->CmdWord == SERVER_CMD_REG_RSP)
		{
			if(RegProtocoRSP->Pritocol_Ver == PRITOCOL_VERSION)
			{
				if(strncmp(Lierda_SysValue.Module_IMEI, RegProtocoRSP->RegRSPData.ModuleIMEI, IMEI_LEN)==0)
				{
					if(RegProtocoRSP->RegRSPData.RegVlaue == 0)
					{

						lierdaLog("Reg Success\r\n");
						Lierda_SysValue.DeviceSta=Reg_Complete;
						 Lierda_SysValue.AckDataNum++;
						 Lierda_ServerSendData();
					}
					else
					{
						lierdaLog("Reg fail ErrorCode=0x%x\r\n",RegProtocoRSP->RegRSPData.RegVlaue);
					}
				}
			}
		}
	}
}

void Lierda_ServerSendData(void)
{
	struct NOtifyFormat1 *NOtifyFormat=NULL;
	uint16 PackLen=0;
	memset(Server_SendBuff,0,SERVER_BUFF_MAXLEN);
	NOtifyFormat=SendDataFilling();
	memcpy(Server_SendBuff,NOtifyFormat,sizeof(struct NOtifyFormat1));
	Tracker_DataFilling(Server_SendBuff+sizeof(struct NOtifyFormat1));
	if(Lierda_SysValue.GpsDataNumFullFlag==1)
		PackLen=sizeof(struct NOtifyFormat1)+10*GPSDATAPACK_LEN+TRACKER_LEN;
	else
		PackLen=sizeof(struct NOtifyFormat1)+Lierda_SysValue.GpsDataNum*GPSDATAPACK_LEN+TRACKER_LEN;
	Server_SendBuff[PackLen] = DataAccumulateSumCRC(Server_SendBuff+2, PackLen-2);
	PackLen = PackLen+1;
	lierdaSendMsg(Server_SendBuff, PackLen);
	Lierda_SysValue.GpsDataNumFullFlag=0;
	Lierda_SysValue.GpsDataNum=0;
	memset(GpsDtaBuff,0,300);
}

static void Tracker_DataFilling(uint8 *FillingBuff)
{
	struct Tracker_Pack teacker_pack={0};
	//场景
	teacker_pack.Scenes=TRACHER;
	teacker_pack.mode=Lierda_SysValue.SysMode;
	teacker_pack.InitInfo=0x01;
	teacker_pack.AutoTrigger=0x00;
	teacker_pack.BatteryInfo=100;
	teacker_pack.AvailableTime=100;
	teacker_pack.DistanceSensor=0x00;
	if(Lierda_SysValue.GpsDataNumFullFlag==1)
	{
		teacker_pack.GpsDataLen=BigtoLittle16((GPSDATAPACK_LEN*10)+1);
		teacker_pack.GpsDataNum=10;
		memcpy(FillingBuff, &teacker_pack, sizeof(struct Tracker_Pack));
		memcpy(FillingBuff+sizeof(struct Tracker_Pack),GpsDtaBuff,10*GPSDATAPACK_LEN);
		lierdaLog("定位标志：%d\r\n数据包数：%d",Lierda_SysValue.GpsPositSuc,10);
	}
	else
	{
		teacker_pack.GpsDataLen=BigtoLittle16((GPSDATAPACK_LEN*Lierda_SysValue.GpsDataNum)+1);
		teacker_pack.GpsDataNum=Lierda_SysValue.GpsDataNum;
		memcpy(FillingBuff, &teacker_pack, sizeof(struct Tracker_Pack));
		memcpy(FillingBuff+sizeof(struct Tracker_Pack),GpsDtaBuff,Lierda_SysValue.GpsDataNum*GPSDATAPACK_LEN);
		lierdaLog("定位标志：%d\r\n数据包数：%d",Lierda_SysValue.GpsPositSuc,Lierda_SysValue.GpsDataNum);
	}
	lierdaLog("Tracker data Filling\r\n");

}

static struct NOtifyFormat1* SendDataFilling(void)
{
	uint16 dataLen = 0;uint64 current_time=0;NueStats ModuleState = {0};
	//固定包头
	SendDataNOtify.PackHead = PACK_HEAD;		//因为编译器为小端模式，协议要求为大端模式 所以把一些数据高低位交换了一下
	//命令字
	SendDataNOtify.CmdWord = TIMIN_NOTIFY;
	//协议版本
	SendDataNOtify.Pritocol_Ver = PRITOCOL_VERSION;
	if(Lierda_SysValue.GpsDataNumFullFlag==1)
		{
			dataLen = sizeof(struct NOtifyFormat1)+TRACKER_LEN+10*GPSDATAPACK_LEN;
			//填充数据长度
			SendDataNOtify.FillingDataLen = BigtoLittle16(TRACKER_LEN+10*GPSDATAPACK_LEN);
		}
	else
	{
			dataLen = sizeof(struct NOtifyFormat1)+TRACKER_LEN+(Lierda_SysValue.GpsDataNum)*GPSDATAPACK_LEN;
			//填充数据长度
			SendDataNOtify.FillingDataLen = BigtoLittle16(TRACKER_LEN+(Lierda_SysValue.GpsDataNum)*GPSDATAPACK_LEN);
	}
	lierdaLog("dataLen=%d", dataLen);
//	lierdaLog("FillingDataLen=%d", dataLen);
	SendDataNOtify.PackDataLen = BigtoLittle16(dataLen);
	//IMEI
	SendDataNOtify.IMEI_Len = IMEI_LEN;
	strncpy(SendDataNOtify.ModuleIMEI, Lierda_SysValue.Module_IMEI, IMEI_LEN);
	//上报周期
	SendDataNOtify.NotifyCycle = BigtoLittle32(Lierda_SysValue.ReportCycle);
	//发送的消息包序号
	SendDataNOtify.Send_PackNum = BigtoLittle32(Lierda_SysValue.AckDataNum);
	//发送成功包数
	SendDataNOtify.ACK_PackNum =	BigtoLittle32(Lierda_SysValue.SendDataNum);

	//utc时间戳
	current_time = get_current_time();
	SendDataNOtify.Timestamp = BigtoLittle64(current_time);

	//模组网络状态
	GetNUESTATS_DelaWith(&ModuleState);
	SendDataNOtify.Rsrp = BigtoLittle16(ModuleState.Rsrp);
	SendDataNOtify.Snr = BigtoLittle16(ModuleState.Snr);
	SendDataNOtify.Coverage_level = ModuleState.Coverage_level;
	SendDataNOtify.Rsrq = BigtoLittle16(ModuleState.Rsrq);
	SendDataNOtify.Cell_ID = BigtoLittle32(ModuleState.Cell_ID);

	//功耗模式
	SendDataNOtify.Power_mode = PSM_MODE;
	//上次重发次数
	SendDataNOtify.ResendNum = 0;
	//标志位
	SendDataNOtify.flag = 0;
	return &SendDataNOtify;
}


void GetNUESTATS_DelaWith(NueStats *ModuleState)
{
	char *recvbuff=NULL;
	char *Ptr=NULL;

	recvbuff = lierdaATCall(LIERDA_NUESTATS,3000);
	if(recvbuff != NULL)
	{
		Ptr = strstr(recvbuff, SIGNAL_POWR);
		if(Ptr!=NULL)
		{
			ModuleState->Rsrp = atoi(Ptr+strlen(SIGNAL_POWR));
			lierdaLog("Rsrp=%d\r\n", ModuleState->Rsrp);
		}

		Ptr = NULL;
		Ptr = strstr(recvbuff, SNR);
		if(Ptr!=NULL)
		{
			ModuleState->Snr = atoi(Ptr+strlen(SNR));
			lierdaLog("Snr=%d\r\n", ModuleState->Snr);
		}

		Ptr = NULL;
		Ptr = strstr(recvbuff, ECL);
		if(Ptr!=NULL)
		{
			ModuleState->Coverage_level = atoi(Ptr+strlen(ECL));
			lierdaLog("Coverage_level=%d\r\n", ModuleState->Coverage_level);
		}

		Ptr = NULL;
		Ptr = strstr(recvbuff, RSRQ);
		if(Ptr!=NULL)
		{
			ModuleState->Rsrq = atoi(Ptr+strlen(RSRQ));
			lierdaLog("Rsrq=%d\r\n", ModuleState->Rsrq);
		}

		Ptr = NULL;
		Ptr = strstr(recvbuff, CELL_ID);
		if(Ptr!=NULL)
		{
			ModuleState->Cell_ID = atoi(Ptr+strlen(CELL_ID));
			lierdaLog("Cell_ID=%d\r\n", ModuleState->Cell_ID);
		}
	}
}
static void Lierda_Server_Protocol_Analysis(uint8 * databuff)
{
	uint8 temp=Stachange_data;
	if((databuff[32]==0xc1)&&(databuff[33]==0x6))
	{

		Lierda_SysValue.SysMode=databuff[40];//系统默认定位模式
		Lierda_SysValue.ReportCycle= databuff[41];//默认上报周期
		Lierda_SysValue.ReportCycle=(Lierda_SysValue.ReportCycle<<8)|databuff[42];
		Lierda_SysValue.ReportCycle=Lierda_SysValue.ReportCycle*60;
		Lierda_SysValue.CollCycle=databuff[43];//默认搜星周期
		Lierda_SysValue.CollCycle=(Lierda_SysValue.CollCycle<<8)|databuff[44];
		Lierda_SysValue.CollCycle=Lierda_SysValue.CollCycle*60;
		Lierda_SysValue.MaxSearchTimer=databuff[45];//最大搜星时间
		Lierda_SysValue.GpsHoldTimer=SEARHOLDTIME;
		DeviceParameterSave();
		if(databuff[39]==0x1)
			lierdaLog("Device OFF");
		else
			lierdaLog("Device ON");
		lierdaLog("mode=%#x", Lierda_SysValue.SysMode);
		if(Lierda_SysValue.SysMode==0x1)
		{
				lierdaLog("Tracker Mode");
				Deviceswitch();
		}
		else
		{
			lierdaLog("Standard Mode");
			Deviceswitch();
		}

		lierdaLog("Reporting cycle=%d", Lierda_SysValue.ReportCycle);
		lierdaLog("The sampling period=%d", Lierda_SysValue.CollCycle);
		lierdaLog("seach gps max time=%d", Lierda_SysValue.MaxSearchTimer);
		lierdaLog("GpsHold Timer=%d", Lierda_SysValue.GpsHoldTimer);
		QueueSendDataFun(&temp);
	}


}

void lierda_RegMsgRecv(uint8* databuff)
{
	 Lierda_Server_Protocol_Analysis(databuff);
}
