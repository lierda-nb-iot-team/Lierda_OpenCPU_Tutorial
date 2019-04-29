/******************************************************************************
 * @brief    lwip udp compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LWIP_SUPPORT_UDP_H
#define LWIP_SUPPORT_UDP_H

/*
 * minimal interface as per src.include/lwip/udp.h 
 * sensitive to any change in lwip config
 */
#include "lwip/pbuf.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include "lwip/ip.h"
#include "lwip/ip6_addr.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

struct udp_pcb;

/** Function prototype for udp pcb receive callback functions
 * @param arg user supplied argument (udp_pcb.recv_arg)
 * @param pcb the udp_pcb which received data
 * @param p the packet buffer that was received
 * @param addr the remote IP address from which the packet was received
 * @param port the remote port from which the packet was received
 */
typedef void (*udp_recv_fn)(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

struct udp_pcb {
    IP_PCB;
    struct udp_pcb *next;
    u8_t flags;
    u16_t local_port;
    u16_t remote_port;
    udp_recv_fn recv;         /** receive callback function */
    void *recv_arg;           /** user-supplied argument for the recv callback */
    uint16 socket;            /** socket to map pcb onto */
};

/**
 * Create a UDP pcb for specified IP type.
 * @param type of IP address
 * @return pcb created, or null if failed
 */
struct udp_pcb *udp_new_ip_type(u8_t type);

/**
 * create a new udp endpoint
 * @return udp pcb or NULL if it could not be allocated
 */
struct udp_pcb *udp_new(void);

/**
 * Remove an udp pcb
 * @param pcb udp pcb to remove
 */
void   udp_remove(struct udp_pcb *pcb);

/**
 * Set a receive callback for a udp pcb
 * @param pcb udp pcb to receive callback on
 * @param recv function pointer of the callback function
 * @param recv_arg argument to pass to the callback function
 */
void   udp_recv(struct udp_pcb *pcb, udp_recv_fn recv, void *recv_arg);

/**
 * send datagram using specified pcb
 * @param pcb udp pcb to use
 * @param p pbuf chain to send
 * @param dst_ip destination IP address
 * @param dst_port destination port.
 *
 * @return error code, ERR_OK if successful
 */
err_t  udp_sendto(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *dst_ip, u16_t dst_port);

/**
 * bind to udp pcb
 * @param pcb Uudp pcb to bind to
 * @param ipaddr local address to bind to
 * @param port local port to bind to
 * @return error code, ERR_OK on success
 */
err_t  udp_bind(struct udp_pcb *pcb, const ip_addr_t *ipaddr, u16_t port);

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_UDP_H */
