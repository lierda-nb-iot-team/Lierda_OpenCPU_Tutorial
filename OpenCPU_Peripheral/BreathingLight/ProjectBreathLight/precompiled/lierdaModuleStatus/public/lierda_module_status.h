
#ifndef SRC_LIB_LIERDAMODULESTATUS_LIERDA_MODULE_STATUS_H_
#define SRC_LIB_LIERDAMODULESTATUS_LIERDA_MODULE_STATUS_H_

#include "neulfw.h"

#define AT_MAX_STRING_LEN  15
#define AT_PLUS_MAX_STRING_LEN  48

extern char SocketNum[7];

typedef struct
{
	char   charCGATT[AT_MAX_STRING_LEN];
	char   charCSCON[AT_MAX_STRING_LEN];
	char   charCEREG[AT_MAX_STRING_LEN];
	char   charCPSMS[AT_MAX_STRING_LEN];
	char   charNPSMR[AT_MAX_STRING_LEN];
	char   charNMSTATUS[AT_PLUS_MAX_STRING_LEN];
	char   charFOTASTATUS[AT_PLUS_MAX_STRING_LEN];
	char   charSockNum[AT_PLUS_MAX_STRING_LEN];
}lierdaModStatus;



typedef enum
{
	FOTA_NON=0,//无FOTA状态
	FOTA_DOWNLOADING,//FOTA下载中
	FOTA_DOWNLOAD_FAILED,//FOTA下载失败
	FOTA_DOWNLOADED,//FOTA下载结束
	FOTA_UPDATING,//FOTA加载中
	FOTA_UPDATE_SUCCESS,//FOTA升级成功
	FOTA_UPDATE_FAILED,//FOTA升级失败
	FOTA_UPDATE_OVER,//FOTA升级结束
}lierda_fotaSta;

typedef enum{
	LierdaFota_DataEnable,
	LierdaFota_DataDisable,
}lierdaFota;

extern lierdaModStatus  module_status;

/******************************************************************************
* @函数名 用于事件更新
* @参数	param : 空参数
* @返回值  无
******************************************************************************/
void lierda_module_status_read(void);


/******************************************************************************
* @函数名 FOTA状态查询
* @参数	param : 空参数
* @返回值  FOTA状态，枚举变量
******************************************************************************/
lierda_fotaSta lierda_FotaStatus(void);


/******************************************************************************
* @函数名    用于判断FOTA过程中能不能做业务,建议发数据前调用此函数
* @参数	param : 空参数
* @返回值  LierdaFota_DataEnable：可以做发数据做业务  LierdaFota_DataDisable：不可以发数据做业务
******************************************************************************/
lierdaFota lierda_FotaEnableData(void);
#endif


