/*
 * lierdaKVStorage.h
 *
 *  Created on: 2018年10月26日
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDAKVSTORAGE_PUBLIC_LIERDAKVSTORAGE_H_
#define SRC_LIB_LIERDAKVSTORAGE_PUBLIC_LIERDAKVSTORAGE_H_


#include "neul_kv_storage.h"
#include "neul_kv_storage_types.h"
#include "irmalloc.h"
#if defined USE_CMSIS_OS
#include "cmsis_os2.h"
#endif
#include <assert.h>
#include <string.h>
#include "core.h"

#if (CORE == SECURITY)
#include "non_os.h"
#include "kv_storage_caches.h"
#include "neul_sec_kv_storage.h"
#else
#include "rpc_auto_generated.h"
#include "rpc_interface.h"
#endif // (CORE == SECURITY)

typedef enum
{
	LIERDA_RET_OK = 0,
	LIERDA_RET_ERROR,

} LIERDA_RET;

typedef uint16 lierda_kv_key;

/******************************************************************************
 * @函数名:lierdaKVSet，用于设定kv值
 * @参数:neul_kv_key key：写入的kv映射ID（范围在0到26880）
 * 		uint8 *kvalue：要写入的值
 * 		kvalue_length：写入的数值长度
 * @返回值:若成功，返回NEUL_RET_OK（0）
 * 		 若失败，返回NEUL_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
extern LIERDA_RET lierdaKVSet(lierda_kv_key key, const uint8 *kvalue, uint16 kvalue_length);


/******************************************************************************
 * @函数名:lierdaKVGet，用于获取kv值
 * @参数:neul_kv_key key：读取的kv映射ID（范围在0到26880）
 * 		uint16 kvalue_max_length：kv的ID长度
 * 		kvalue_length：读取的数值长度
 * 		uint8 *kvalue：读取的数值
 * @返回值:若成功，返回NEUL_RET_OK（0）
 * 		若失败，返回NEUL_RET_ERROR
 * @重要修改记录:180830，Def创建函数
******************************************************************************/
extern LIERDA_RET lierdaKVGet(lierda_kv_key key, uint16 kvalue_max_length, uint16 *kvalue_length, uint8 *kvalue);

#endif /* SRC_LIB_LIERDAKVSTORAGE_PUBLIC_LIERDAKVSTORAGE_H_ */
