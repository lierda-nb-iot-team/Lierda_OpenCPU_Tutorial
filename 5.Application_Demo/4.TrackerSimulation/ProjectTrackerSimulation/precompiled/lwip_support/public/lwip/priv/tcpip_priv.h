/******************************************************************************
 * @brief    lwip snmp compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_PRIV_TCPIP_PRIV_H
#define LWIP_SUPPORT_PRIV_TCPIP_PRIV_H

#include "lwip/opt.h"
#include "lwip/tcpip.h"
#include "lwip/sys.h"
#include "lwip/timeouts.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#define API_VAR_REF(name)                               name
#define API_VAR_DECLARE(type, name)                     type name
#define API_VAR_ALLOC(type, pool, name, errorval)
#define API_VAR_ALLOC_POOL(type, pool, name, errorval)
#define API_VAR_FREE(pool, name)
#define API_VAR_FREE_POOL(pool, name)
#define API_EXPR_REF(expr)                              expr
#define API_MSG_M_DEF(m)                                *m
#define API_MSG_M_DEF_C(t, m)                           const t * m

struct tcpip_api_call_data
{
  u8_t tmp;
};

/** tcp api function
 * @param data to pass
 * return err_t ERR_OK is successful
 */
typedef err_t (*tcpip_api_call_fn)(struct tcpip_api_call_data* call);

/** tcp api call
 * @param fn function to call
 * @param data to pass
 * return err_t ERR_OK is successful
 */
err_t tcpip_api_call(tcpip_api_call_fn fn, struct tcpip_api_call_data *call);

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_PRIV_TCPIP_PRIV_H */
