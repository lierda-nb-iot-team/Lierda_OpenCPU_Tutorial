/******************************************************************************
 * @brief    Hi211X Common 3GPP AKA definitions 
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef AKA_TYPES_H_
#define AKA_TYPES_H_

/* length of Authentication fields in bytes */
#define AKA_AUTS_LEN            14
#define AKA_AUTN_LEN            16
#define AKA_RAND_LEN            16
#define AKA_MAX_RES_LEN         16
/* length of Key fields in bytes */
#define IK_LEN                  16
#define CK_LEN                  16


typedef enum 
{
    AKA_STATUS_AUTH_SUCCESS,
    AKA_STATUS_SYNC_ERROR,
    AKA_STATUS_MAC_ERROR,
    AKA_STATUS_AUTH_ERROR
} aka_status_t;


#endif /* AKA_TYPES_H_ */
