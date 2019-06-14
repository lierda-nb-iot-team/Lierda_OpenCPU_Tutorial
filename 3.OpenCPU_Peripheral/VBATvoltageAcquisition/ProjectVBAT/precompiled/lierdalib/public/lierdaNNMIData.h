/*
 * lierdaNNMIData.h
 *
 *  Created on: 2018Äê9ÔÂ28ÈÕ
 *      Author: Def_Lin
 */

#ifndef SRC_LIB_LIERDANNMIDATA_PUBLIC_LIERDANNMIDATA_H_
#define SRC_LIB_LIERDANNMIDATA_PUBLIC_LIERDANNMIDATA_H_

#include "neulfw.h"

#define LIERDA_NNMI_RECEIVE_BUFFER_SIZE    (1024)


void lierda_nnmi_trigger_received_data_notify_callback(void);
extern void lierdaNNMIDataReceived(uint8* nnmi_buff,uint16* nnmi_buff_len,uint32 timeout);
extern void lierdaNNMIDataInit(void);

extern void lierdaSocketAcquireSemaphore(void);

#endif /* SRC_LIB_LIERDANNMIDATA_PUBLIC_LIERDANNMIDATA_H_ */
