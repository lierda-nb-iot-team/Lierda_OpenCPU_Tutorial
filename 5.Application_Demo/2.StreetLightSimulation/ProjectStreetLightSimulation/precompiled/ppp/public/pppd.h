/******************************************************************************
 * @brief    basic pppd interface to system
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef SRC_LIB_PPP_PRIVATE_PPPD_H_
#define SRC_LIB_PPP_PRIVATE_PPPD_H_

#include "platform_definitions.h"
#include "neulfw.h"
#include "neul_ip_addr.h"

/** @defgroup PPP Hi21XX LWIP PPP
 * Hi21XX LWIP PPP
 * @ingroup LIBNEUL
 * @{
 * */

typedef void (*ppp_exited_cb)(void);

/** set PPP uart config
 * @param tx_pin PIN to transmit on
 * @param rx_pin PIN to receive on
 * @param rts_pin PIN for RTS
 * @param cts_pin PIN for CTS
 * @param baud baud rate to use
 * @param xonxoff Enables software flow control
 * @return true is successfully set, false if any values are not allowed
 */
bool ppp_set_serial_config(PIN tx_pin, PIN rx_pin, PIN rts_pin, PIN cts_pin, uint32 baud, bool xonxoff);

/** set PPP exit callback
 * @param callback to call when PPP exits
 */
void ppp_set_ppp_exit_callback(ppp_exited_cb callback);

/** set address for PPP to use
 * @param ip_addr ip address to use
 */
void pppd_set_ip_address(const ip_addr_t *ip_addr);

/** start pppd
 * requires uart and address to have been set
 */
void  pppd_go(void);

/** @} end of group PPP */

#endif /* SRC_LIB_PPP_PRIVATE_PPPD_H_ */
