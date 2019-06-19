/******************************************************************************
 * @brief    Network Functions for Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_NETWORK_H_
#define LIB_NEUL_NETWORK_H_

#include "neul_ip_addr.h"
#include "neulfw.h"
#include "neul_error_types.h"

/** @defgroup libNEUL_NETWORK Hi21XX libNEUL Network Functions
 * Hi21XX libNeul Network API
 * @ingroup LIBNEUL
 * @{
 * */

 /*
 * Used to return a list of addresses & netmasks
 * Need to review if we want all fields.
 */

 
struct ifaddrs {
    struct ifaddrs *ifa_next;       /* Next item in list */
    char *ifa_name;                 /* Name of interface */
    int16 cid;                      /* context number of the interface - increased to int16 to allow for non-radio IPs (-1) */
    uint32 ifa_flags;               /* Flags from SIOCGIFFLAGS */
    ip_addr_t ifa_addr;             /* Address of interface */
    ip_addr_t ifa_netmask;          /* Netmask of interface */
};

struct dnsaddrs {
    struct    dnsaddrs *dnsa_next;  /* Next item in list */
    uint8     cid;                  /* context number of the interface - increased to int16 to allow for non-radio IPs (-1) */
    ip_addr_t dns_addr;             /* Address of interface */
};

/** 
 * @brief return a list of addresses & netmasks
 * @param ifap  pointer to ifaddrs linked list, one element for each IP address
 * @return      error code
 */
NEUL_RET getifaddrs(struct ifaddrs **ifap);

/** 
 * @brief return a list of DNS server addresses
 * @param dnsap  pointer to DNS server linked list, one element for each IP address
 * @return      error code
 */
NEUL_RET getdnsaddr(uint8 cid, struct dnsaddrs **dnsap);

/** @brief free data structure returned by
 * @param ifa    ifaddrs linked list
 */
void freeifaddrs(struct ifaddrs *ifa);

/** @brief free data structure returned by
 * @param dnsa    dns server address linked list
 */
void freednsaddrs(struct dnsaddrs *dnsa);

typedef void (*ip_changed_callback)(uint8 cid);

/**
 * Sets a callback that will be used to let us know of changes to the IP address
 * @param callback The callback function, which will return the cid of the changed interface
 */
NEUL_RET set_ipaddr_callback( void(*callback)(uint8) );

/**
 * Deregister a callback 
 * @param callback The callback function
 */
NEUL_RET deregister_ipaddr_callback(ip_changed_callback callback);

/** @brief callback to receive icmp echo response or timeout
 * @param remote_addr address of remote system
 * @param success true if ping succeeded, false if it failed.
 * @param retry number of retries before success
 * @param ttl ttl value in response packet
 * @param uint32 rtt round-trip time in msec
 */
typedef void (*icmp_ping_callback)(const ip_addr_t *remote_addr, bool success, uint8 ttl, uint32 rtt);

/** @brief send icmp ping packet, and register callback to receive response
 * @param remote_addr address of remote system
 * @param  p_size size in bytes of echo packet payload
 * @param timeout timeout to ping remote_addr, unit ms.
 * @param callback icmp_ping_callback callback to receive echo packet or report timeout failure
 * @return error code
 */
NEUL_RET icmp_ping_send(ip_addr_t *remote_addr, uint16 p_size, uint32 timeout, icmp_ping_callback callback);

/** @} end of group libNEUL_NETWORK */

#endif /* LIB_NEUL_NETWORK_H_ */
