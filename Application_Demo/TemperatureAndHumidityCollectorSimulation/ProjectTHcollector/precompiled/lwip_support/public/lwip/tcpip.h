/******************************************************************************
 * @brief    lwip tcp compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_TCPIP_H
#define LWIP_SUPPORT_TCPIP_H

#include "lwip/opt.h"
#include "lwip/err.h"
#include "lwip/timeouts.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

err_t  tcpip_inpkt(struct pbuf *p, struct netif *inp, netif_input_fn input_fn);

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_TCPIP_H */
