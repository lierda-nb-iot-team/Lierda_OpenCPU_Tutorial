/******************************************************************************
 * @brief    IP addr Types for Hi21XX
 * Copyright (c) 2017 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LIB_NEUL_NETWORK_DEFS_H_
#define LIB_NEUL_NETWORK_DEFS_H_

/** @addtogroup libNEUL_NETWORK
 * @{
 * */

#define htonl(x) ( (((uint32)(x))>>24) | (((x)&0xFF0000)>>8) \
                               | (((x)&0xFF00)<<8) | (((x)&0xFF)<<24) )

#define ntohs(x)  ((((x) & 0x00FFUL) << 8) | (((x) & 0xFF00UL) >> 8))

#define htons(x)  ((((x) & 0x00FFUL) << 8) | (((x) & 0xFF00UL) >> 8))

/** @} end of group libNEUL_NETWORK */

#endif /* LIB_NEUL_NETWORK_DEFS_H_ */
