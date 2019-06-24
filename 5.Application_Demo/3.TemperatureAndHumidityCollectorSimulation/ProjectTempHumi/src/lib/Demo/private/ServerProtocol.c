/*
 * ServerProtocol.c
 *
 *  Created on: 2019年5月21日
 *      Author: Administrator
 */
#include "ServerProtocol.h"
struct RegProtocolFrame1 RegProtocolFrame;
uint8  Server_SendBuff[SERVER_BUFF_MAXLEN];
struct NOtifyFormat1 SendDataNOtify;

static struct RegProtocolFrame1* RegMsgFilling(void);
static struct NOtifyFormat1* SendDataFilling(void);
static void TempHumi_DataFilling(uint8 *FillingBuff);
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
	TempHumi_DataFilling(Server_SendBuff+sizeof(struct NOtifyFormat1));
	PackLen=sizeof(struct NOtifyFormat1)+sizeof(struct TemperHumi_Pack);
	Server_SendBuff[PackLen] = DataAccumulateSumCRC(Server_SendBuff+2, PackLen-2);
	PackLen = PackLen+1;
	lierdaSendMsg(Server_SendBuff, PackLen);
}

static void TempHumi_DataFilling(uint8 *FillingBuff)
{
	struct TemperHumi_Pack temperhumi_pack={0};
	//场景
	temperhumi_pack.Scenes=TEMPERHUMI;
	temperhumi_pack.Devicetype=1;
	temperhumi_pack.FactoryCode=1;
	temperhumi_pack.Temperature=BigtoLittle16(Lierda_SysValue.Temperature);
	temperhumi_pack.humidity=Lierda_SysValue.humidity;
	temperhumi_pack.battery=100;
	temperhumi_pack.warning=Lierda_SysValue.warning;
	lierdaLog("warning:%#x\r\n",temperhumi_pack.warning);
	temperhumi_pack.ReportCycle=BigtoLittle32(Lierda_SysValue.ReportCycle);
	temperhumi_pack.HightTempThreshold=BigtoLittle16(Lierda_SysValue.HightTempThreshold);
	temperhumi_pack.LowTempThreshold=BigtoLittle16(Lierda_SysValue.LowTempThreshold);
	temperhumi_pack.TempDelayWarn=Lierda_SysValue.TempDelayWarn;
	temperhumi_pack.TempCorrect=BigtoLittle16(Lierda_SysValue.TempCorrect);
	temperhumi_pack.HightHumiThreshold=Lierda_SysValue.HightHumiThreshold;
	temperhumi_pack.LowHumiThreshold=Lierda_SysValue.LowHumiThreshold;
	temperhumi_pack.HumiDelayWarn=Lierda_SysValue.HumiDelayWarn;
	temperhumi_pack.BatteryThreshold=Lierda_SysValue.BatteryThreshold;
	memcpy(FillingBuff, &temperhumi_pack, sizeof(struct TemperHumi_Pack));
	lierdaLog("TemperHumi data Filling\r\n");
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

	dataLen = sizeof(struct NOtifyFormat1)+TEMPER_HUMI_LEN;
	//填充数据长度
	SendDataNOtify.FillingDataLen = BigtoLittle16(TEMPER_HUMI_LEN);

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
	if((databuff[32]==0xc1)&&(databuff[33]==0x7))
	{
		lierdaLog("cmd %x %x\r\n", databuff[32],databuff[33]);
		Lierda_SysValue.ReportCycle=databuff[39];
		Lierda_SysValue.ReportCycle=(Lierda_SysValue.ReportCycle<<8)|databuff[40];
		Lierda_SysValue.ReportCycle=(Lierda_SysValue.ReportCycle<<8)|databuff[41];
		Lierda_SysValue.ReportCycle=(Lierda_SysValue.ReportCycle<<8)|databuff[42];
		lierdaLog("ReportCycle=%d ", Lierda_SysValue.ReportCycle);
		Lierda_SysValue.HightTempThreshold=databuff[43];
		Lierda_SysValue.HightTempThreshold=(Lierda_SysValue.HightTempThreshold<<8)|databuff[44];
		lierdaLog("HightTempThreshold=%d ", Lierda_SysValue.HightTempThreshold);
		Lierda_SysValue.LowTempThreshold=databuff[45];
		Lierda_SysValue.LowTempThreshold=(Lierda_SysValue.LowTempThreshold<<8)|databuff[46];
		lierdaLog("LowTempThreshold=%d ", Lierda_SysValue.LowTempThreshold);
		Lierda_SysValue.TempDelayWarn=databuff[47];
		lierdaLog("TempDelayWarn=%d ", Lierda_SysValue.TempDelayWarn);
		Lierda_SysValue.TempCorrect=databuff[48];
		Lierda_SysValue.TempCorrect=(Lierda_SysValue.TempCorrect<<8)|databuff[49];
		lierdaLog("TempCorrect=%d ", Lierda_SysValue.TempCorrect);
		Lierda_SysValue.HightHumiThreshold=databuff[50];
		lierdaLog("HightHumiThreshold=%d ", Lierda_SysValue.HightHumiThreshold);
		Lierda_SysValue.LowHumiThreshold=databuff[51];
		lierdaLog("LowHumiThreshold=%d ", Lierda_SysValue.LowHumiThreshold);
		Lierda_SysValue.HumiDelayWarn=databuff[52];
		lierdaLog("HumiDelayWarn=%d ", Lierda_SysValue.HumiDelayWarn);
		Lierda_SysValue.BatteryThreshold=databuff[53];
		lierdaLog("BatteryThreshold=%d ", Lierda_SysValue.BatteryThreshold);
		DeviceParametersave();
		QueueSendDataFun(&temp);
	}

}

void lierda_RegMsgRecv(uint8* databuff)
{
	 Lierda_Server_Protocol_Analysis(databuff);
}
