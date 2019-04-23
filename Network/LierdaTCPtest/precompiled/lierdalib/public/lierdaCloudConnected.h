/*
 * lierdaCloudConected.h
 *
 *  Created on: 2019年3月11日
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDALIB_PUBLIC_LIERDACLOUDCONNECTED_H_
#define SRC_LIB_LIERDALIB_PUBLIC_LIERDACLOUDCONNECTED_H_


#include "lierda_app_main.h"

#define AT_MLWULDATAEX_STRING_LEN 40

typedef enum
{
	CLOUD_RET_OK 				= 0,
	CLOUD_RET_PARAM_INVALID		= 1,
	CLOUD_RET_MEMORY_ERROR		= 4,
	CLOUD_RET_PROGRESS_ERROR    = 6,
	CLOUD_RET_ERROR				= 22
}CLOUD_RET;

typedef enum
{
    MSG_NON_NORAI = 0x0000,
    MSG_NON_WITHRAI = 0x0001,
    MSG_NON_WITH_SENDBACKRAI = 0x0010,
    MSG_CON_NORAI = 0x0100,
    MSG_CON_WITHRAI = 0x0101
}MSG_MODE;


/******************************************************************************
 * @函数名:lierdaSendMsgToPlatform，用于向IoT平台发送CON或NON数据
 * @参数:uint8 *data：需要传送的数据
 * 		uint16 data_len：数据长度
 * 		MSG_MODE mode：0x0000: Send NON message;0x0001: Send Non message and carry RELEASE RAI;0x0010: Send NON message and carry RELEASE_AFTER_REPLY RAI.x0100: Send CON message; 0x0101: Send CON message and carry RELEASE_AFTER_REPLY RAI
 * 		uint8 seq_num：0~255，根据AT指令手册一般填0
 * 		uint8 isHEX:0表示传入的为字符串，1表示传的是hex
 * @返回值:若成功，返回CLOUD_RET_OK
 * 		 若失败，返回相应错误原因CLOUD_RET
 * @重要修改记录:190311，Def创建函数
******************************************************************************/
CLOUD_RET lierdaSendMsgToPlatform(uint8 *data, uint16 data_len, MSG_MODE mode, uint8 seq_num,uint8 isHEX);


#endif /* SRC_LIB_LIERDALIB_PUBLIC_LIERDACLOUDCONNECTED_H_ */
