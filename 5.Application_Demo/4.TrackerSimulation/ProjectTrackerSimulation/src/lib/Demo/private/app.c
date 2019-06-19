/******************************************************************************
 * @内容	用户任务函数
 * @设计	Lierda NB-IoT 软件设计团队@2018
******************************************************************************/
#include "app.h"
#include "lierda_network_dealwith.h"
#include "lierdaNNMIData.h"
#include "lierdaCloudConnected.h"
#include "stdio.h"

osThreadAttr_t App_task_attr = { "lierda_App_task"/*任务名称*/, 0, NULL, 0, NULL,
		(256) /*任务堆栈大小*/, 11/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * App_task_handle = NULL;

osThreadAttr_t server_task_attr = { "lierda_server_task"/*任务名称*/, 0, NULL, 0, NULL,
		(512) /*任务堆栈大小*/, 12/*任务优先级*/, 0, 0 };//任务属性结构体
uint32 * server_task_handle = NULL;


int16 Temper=0,Humidity=0;

static void local_para_init(void)
{
	NET_PARA_RET  cause;
  	struct NET_Local_Para  net_local_pa =
  	{
  	   1,
       8, //第一轮离散加网因子 (>=1)
  	   30, //第二轮离散加网因子 (>=1)
	   0,
	   0,
	   3,
       2,
	   {"180.101.147.115,5683"},
  	};

  	cause = lierda_net_local_config_init(&net_local_pa);
  	if (cause != 0)
  	{
  		lierdaLog("lierda_net_local_config_init,fail,%d\r\n",cause);
  	}
}

static void TitlePrint( char *name);
/******************************************************************************
* @函数名	app任务线程
* @参数	    param : 空参数，无效
* @返回值  无
******************************************************************************/
void lierda_App_task(void *param)
{
	UNUSED(param);


	osDelay(500);//等待模组初始化完成
	TitlePrint("温湿度HDC1000例程");
	I2C_init();//I2c总线初始化
	if(HDC1000_Init())  //HDC1000初始化
		lierdaLog("HDC1000 Init Success");
	else
		lierdaLog("HDC1000 Init Fail");

	local_para_init();

	lierda_network_dealwith_task_enable();

	for (;;)
	{
		HDC1000_UpdateInfo(&Temper,&Humidity);  //温湿度采集
		lierdaLog("Temper:%d  Humidity:%d",Temper/100,Humidity);  //温湿度通过AT口打印
		osDelay(5000);//每5秒采集一次温度湿度
	}
}

void lierda_server_task(void *param)
{
	UNUSED(param);

	uint8 recvBuffer[128] = {0};//下行数据
	uint16 recvBufferLenth;//下行数据接收长度
	CLOUD_RET ret = CLOUD_RET_OK;
	uint8 sendBuffer[100] = {0};

	lierdaNNMIDataInit();

	for(;;)
	{
		lierdaNNMIDataReceived(recvBuffer, &recvBufferLenth, 0xFFFFFFFF);

		if(recvBuffer[0] == 0xff && recvBuffer[1] == 0xaa)
		{
			memset(sendBuffer,0,sizeof(100));

			sprintf((char *)sendBuffer,"FFAAD0D0%d%d",Temper/100,Humidity);


			ret = lierdaSendMsgToPlatform(sendBuffer, strlen((const char *)sendBuffer), MSG_NON_WITH_SENDBACKRAI, 0,0);

			if(ret == 0)
			{
				lierdaLog("update info is ok");
			}
			else
			{
				lierdaLog("update info is failed");
			}


		}
	}

}




/******************************************************************************
* @函数名 创建用户线程
* @参数	param : 空参数
* @返回值  无
******************************************************************************/
void lierda_App_main(void)
{
	App_task_handle = osThreadNew(lierda_App_task, NULL, &App_task_attr); //创建测试任务
	if (App_task_handle == NULL)
	{
		lierdaLog("	lierda_App_task任务创建失败");
	}

	server_task_handle = osThreadNew(lierda_server_task, NULL, &server_task_attr); //创建测试任务
		if (App_task_handle == NULL)
		{
			lierdaLog("	lierda_App_task任务创建失败");
		}
}

/******************************************************************************
* @函数名 系统信息打印
* @参数	 *name : 例程名
* @返回值  无
******************************************************************************/
static void TitlePrint( char *name)
{

 lierdaLog("******************************************************************************");
 lierdaLog("                       NB86 EVK开发板例程----%s                                    \r\n",name);
 lierdaLog(" 利尔达科技集团<www.lierda.com>");
 lierdaLog(" LSD Science&Technology Co.,Ltd");
 lierdaLog(" 杭州市余杭区文一西路1326号利尔达科技园");
 lierdaLog(" 物联网开发者社区<http://bbs.lierda.com>");
 lierdaLog("******************************************************************************\r\n");
}
