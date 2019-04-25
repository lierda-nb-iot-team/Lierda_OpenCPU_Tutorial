/******************************************************************************
 * @brief    lwip ip6 compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef LWIP_SUPPORT_IP6_H_
#define LWIP_SUPPORT_IP6_H_

#include "lwip/pbuf.h"
#include "lwip/netif.h"
#include "lwip/err.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

err_t ip6_input(struct pbuf *p, struct netif *inp);

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_IP6_H_ */

