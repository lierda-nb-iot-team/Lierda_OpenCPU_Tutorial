/*
 * @file ifaddrs.h
 * @brief simple ifaddrs.h
 * Copyright (c) 2016 NEUL LIMITED
 */
#ifndef NEUL_IFADDRS_H
#define NEUL_IFADDRS_H

#include "neul_ip_addr.h"

struct ipc_app_ifaddrs {
    uint32 ifa_flags;               /* Flags from SIOCGIFFLAGS */
    ip_addr_t ifa_addr;           /* Address of interface */
    ip_addr_t ifa_netmask;        /* Netmask of interface */
    uint16 ifa_name_size;           /* Length of interface name */
    uint16 ifa_name_offset;         /* Offset to Name of interface in the data block*/
    int16 cid;                      /* The LWIP layer cannot find this, so it gets set to -1 here, and matched to the CID later */
    uint16 pad;
};

#endif /* NEUL_IFADDRS_H */
