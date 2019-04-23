/******************************************************************************
 * @brief    lwip netif compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LWIP_SUPPORT_NETIF_H
#define LWIP_SUPPORT_NETIF_H

#include "lwip/opt.h"
#include "lwip/err.h"
#include "lwip/ip_addr.h"
#include "lwip/def.h"
#include "lwip/pbuf.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

/** Whether the network interface is 'up'.
 */
#define NETIF_FLAG_UP           0x01U

struct netif;

/** Function prototype for netif init functions.
 * @param netif The netif to initialize
 */
typedef err_t (*netif_init_fn)(struct netif *netif);

/** Function prototype for netif->input functions.
 * @param p The received packet, copied into a pbuf
 * @param inp The netif which received the packet
 */
typedef err_t (*netif_input_fn)(struct pbuf *p, struct netif *inp);

/** Function prototype for netif->output functions.
 * @param netif The netif which shall send a packet
 * @param p The packet to send (p->payload points to IP header)
 * @param ipaddr The IP address to which the packet shall be sent
 */
typedef err_t (*netif_output_fn)(struct netif *netif, struct pbuf *p, const ip4_addr_t *ipaddr);

#if LWIP_IPV6
/** Function prototype for netif->output_ip6 functions.
 * @param netif The netif which shall send a packet
 * @param p The packet to send (p->payload points to IP header)
 * @param ipaddr The IPv6 address to which the packet shall be sent
 */
typedef err_t (*netif_output_ip6_fn)(struct netif *netif, struct pbuf *p, const ip6_addr_t *ipaddr);
#endif /* LWIP_IPV6 */

/** Function prototype for netif->linkoutput functions. */
typedef err_t (*netif_linkoutput_fn)(struct netif *netif, struct pbuf *p);

/** Function prototype for netif status- or link-callback functions. */
typedef void (*netif_status_callback_fn)(struct netif *netif);


/** LWIP network interface structure
 * Generic data structure used for all lwIP network interfaces.
 */
struct netif {
    struct netif *next; /** pointer to next in linked list */
    ip_addr_t ip_addr;
    ip_addr_t netmask;
    ip_addr_t gw;
#if LWIP_IPV6
    ip_addr_t ip6_addr[LWIP_IPV6_NUM_ADDRESSES];    /** Array of IPv6 addresses for this netif. */
    u8_t ip6_addr_state[LWIP_IPV6_NUM_ADDRESSES];   /** The state of each IPv6 address (Tentative, Preferred, etc) */
#endif /* LWIP_IPV6 */
    netif_input_fn input;                           /** Pass a packet up the IP stack. */
    netif_output_fn output;                         /** Send a packet on the interface. */
#if LWIP_IPV6
    netif_output_ip6_fn output_ip6;                 /** This function is called by the IPv6 module when it wants to send a packet on the interface. This function typically first resolves the hardware address, then sends the packet */
#endif /* LWIP_IPV6 */
    void *state;                                    /** driver specific state information */
    u16_t mtu;                                      /** MTU size */
    u8_t flags;                                     /** flags */
    char name[2];                                   /** interface ame */
    u8_t num;                                       /** interface number */
    int16 socket;                                   /** socket used for protocol core comms */
};

/** set default netif
 * @param netif to set default
 */
void netif_set_default(struct netif *netif);

/** remove netif
 * @param netif to remove
 */
void netif_remove(struct netif * netif);


/** Add a network interface
 *
 * @param netif a (pre-allocated) netif structure
 * @param ipaddr ip address for the new interface
 * @param netmask for the new interface
 * @param gw default gateway address for the new interface
 * @param state opaque data passed to the new interface
 * @param init callback function for interface init
 * @param input callback when a packet comes in
 * @return netif or NULL if failed.
 */
struct netif *netif_add(struct netif *netif, const ip4_addr_t *ipaddr, const ip4_addr_t *netmask, const ip4_addr_t *gw, void *state, netif_init_fn init, netif_input_fn input);

/** Change IP address, netmask and gateway for a network interface
 *
 * @param netif the network interface to change
 * @param ipaddr new ip address
 * @param netmask new netmask
 * @param gw new default gateway
 */
void netif_set_addr(struct netif *netif, const ip4_addr_t *ipaddr, const ip4_addr_t *netmask, const ip4_addr_t *gw);

/**
 * Called when a link goes up
 */
void netif_set_link_up(struct netif *netif);

/**
 * Called when a link goes down
 */
void netif_set_link_down(struct netif *netif );

/** handle a recevied ip4 packet
 * @param p received IP packet (p->payload points to IP header)
 * @param inp the netif on which the packet was received
 * @return ERR_OK if processed ok, else ERR_error
 */
err_t ip4_input(struct pbuf *p, struct netif *inp);


/** ip4 recv
 * @param netif to receive on
 * @return if a packet was received
 */
bool netif_ip4_socket_recv(struct netif *netif_in);

/** ip4 callback prototype
 */
typedef void (*netif_ip4_socket_callback)(void);

/** register ip4 recv callback
 * @param callback to register
 */
void netif_ip4_socket_recv_notify_register(netif_ip4_socket_callback callback);

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_NETIF_H */
