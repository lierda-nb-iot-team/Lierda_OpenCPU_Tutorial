/******************************************************************************
* @内容	NNMI下行数据处理文件
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "irmalloc.h"
#include "Lierda_NNMI.h"
#include "string.h"
#include "stdio.h"
#include "stdarg.h"
#include "lierdaNNMIData.h"
#include "cmsis_os2.h"
#include "lierda_app_main.h"
#include "app.h"
#include "app_at_send_data.h"

uint8 nnmi_buff[NNMI_BUFFSIZE];
uint16 nnmi_datalen;


void lierda_MMNI_task(void *unused)
{
	UNUSED(unused);uint16 len=0;
	osDelay(500);
	lierdaNNMIDataInit();//下行任务接收初始化
	memset(nnmi_buff,0,NNMI_BUFFSIZE);
	nnmi_datalen=0;
	for(;;)
	{
		lierdaNNMIDataReceived(nnmi_buff,&nnmi_datalen,0xFFFFFFFF);//数据接收
		if(nnmi_datalen>0)
		{
			lierdaLog_NNMI("\r\n");
			lierdaLog_NNMI("len:%d	nnmi_buff:",nnmi_datalen);
			for(len=0;len<nnmi_datalen;len++)
			{
				lierdaLog_NNMI("%02x",nnmi_buff[len]);
			}
			lierdaLog_NNMI("\r\n");
			if(Lierda_SysValue.DeviceSta==Device_Reg)
			{
				RegMsgProtocolAnalysis(nnmi_buff);//注册下行数据解析
			}
			else if(Lierda_SysValue.DeviceSta==Reg_Complete)
			{
				lierda_RegMsgRecv(nnmi_buff);//下行命令数据解析
			}
			ReceiveDataled();//收到数据闪灯
		}

		memset(nnmi_buff,0,NNMI_BUFFSIZE);
		nnmi_datalen=0;
		osDelay(10);
	}
}

/******************************************************************************
 * @函数名:lierdaLog
 * @参数:同库函数"printf"用法，没有自动增加回车换行
 * @返回值:执行成功返回0，不成功返回-1
 * @重要修改记录:180830，Def更改函数名
******************************************************************************/
int lierdaLog_NNMI(const char *pcFormat, ...)
{
    int iRet = 0;
    char *pcBuff, *pcTemp;
    int iSize = 512;
    va_list list;
    pcBuff = (char*)irzalloc(iSize);
    if(pcBuff == NULL)
    {
        return -1;
    }

    while(1)
    {
        va_start(list,pcFormat);
        iRet = vsnprintf(pcBuff,iSize,pcFormat,list);
        va_end(list);
        if(iRet > -1 && iRet < iSize)
        {
            break;
        }
        else
        {
            //iSize*=2;
            //if((pcTemp=realloc(pcBuff,iSize))==NULL)
            {
                iRet = -1;
                break;
            }
            //else
            {
                pcBuff=pcTemp;
            }

        }
    }
    app_at_send_at_rsp_string(pcBuff,true,AT_FLAG_LOGABLE);
    irfree(pcBuff);
    return iRet;
}

