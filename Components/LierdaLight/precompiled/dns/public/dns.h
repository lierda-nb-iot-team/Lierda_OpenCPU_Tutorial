#ifndef _DNS_H_
#define _DNS_H_

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "neul_ip_addr.h"
#include "neul_socket_types.h"
#include "types.h"
#include "apps_dns_keys.h"

#define DNS_MAX_NAME_LENGTH      (256)
#define DNS_MAX_SERVERS          (6)
#define DNS_WAIT_RSP_TIMEOUT_S   (100)  //second
#define DNS_RETRY_TIMES          (3)
#define DNS_TABLE_SIZE           (6)


#define DNS_PORT                 (53)
#define EAI_OK                   (0)
#define EAI_NONAME      (200)
#define EAI_SERVICE     (201)
#define EAI_FAIL        (202)
#define EAI_MEMORY      (203)
#define EAI_AGAIN       (204)
#define EAI_BADFLAGS    (205)
#define EAI_PARSE      (206)

/* Used for netconn_gethostbyname_addrtype(), these should match the DNS_ADDRTYPE defines in dns.h */
#define NETCONN_DNS_DEFAULT   NETCONN_DNS_IPV4_IPV6
#define NETCONN_DNS_IPV4      0
#define NETCONN_DNS_IPV6      1
#define NETCONN_DNS_IPV4_IPV6 2 /* try to resolve IPv4 first, try IPv6 if IPv4 fails only */
#define NETCONN_DNS_IPV6_IPV4 3 /* try to resolve IPv6 first, try IPv4 if IPv6 fails only */

#define DNS_MAIN_MSG_QUEUE_LEN        (2)
#define DNS_MAIN_QUEUE_ITEM_SIZE (sizeof(uint32_t))

#define AT_MAX_MDNS_RSP_LEN               72

#define DNS_RCV_QUEUE_LEN (1)
#define DNS_RCV_QUEUE_ITEM_SIZE (sizeof(uint32_t))

#define ip4_addr_set_loopback(ipaddr) ((ipaddr)->addr = htonl(IPADDR_LOOPBACK))

#define ip6_addr_set_loopback(ip6addr) do{(ip6addr)->addr[0] = 0; \
                                          (ip6addr)->addr[1] = 0; \
                                          (ip6addr)->addr[2] = 0; \
                                          (ip6addr)->addr[3] = htonl(0x00000001UL);}while(0)

#define ip_addr_set_loopback(is_ipv6, ipaddr) do{if(is_ipv6){ \
  ip6_addr_set_loopback(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V6); }else{ \
  ip4_addr_set_loopback(ip_2_ip4(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V4); }}while(0)

#define inet_addr_from_ip4addr(target_inaddr, source_ipaddr) ((target_inaddr)->s_addr = ip4_addr_get_u32(source_ipaddr))

#if 0 //( ipconfigBYTE_ORDER == FREERTOS_LITTLE_ENDIAN )
#define dnsOUTGOING_FLAGS               0x0001 /* Standard query. */
#define dnsTYPE_IPV4                    0x0100 /* A record (host address. */
#define dnsCLASS                        0x0100 /* IN */
#define dnsDNS_PORT                     0x3500
#define dnsONE_QUESTION                 0x0100
#define dnsRX_FLAGS_MASK                0x0f80 /* The bits of interest in the flags field of incoming DNS messages. */
#define dnsEXPECTED_RX_FLAGS            0x0080 /* Should be a response, without any errors. */
#define dnsTYPE_IPV6                    0x1C00
#else
#define dnsDNS_PORT                     0x35
#define dnsONE_QUESTION                 0x01
#define dnsFLAG_QUERY_RESPONSE_BIT      0x8000
#define dnsFLAG_OPERATION_CODE_BITS     0x7800
#define dnsFLAG_TRUNCATION_BIT          0x0200
#define dnsFLAG_RESPONSE_CODE_BITS      0x000f
#define dnsOUTGOING_FLAGS               0x0100 /* Standard query. */
#define dnsTYPE_IPV4                    0x0001 /* A record (host address. */
#define dnsCLASS                        0x0001 /* IN */
#define dnsRX_FLAGS_MASK                0x800f /* The bits of interest in the flags field of incoming DNS messages. */
#define dnsEXPECTED_RX_FLAGS            0x8000 /* Should be a response, without any errors. */
#define dnsTYPE_IPV6                    0x001C
#endif /* ipconfigBYTE_ORDER */

#define dnsNAME_IS_OFFSET               ( ( uint8_t ) 0xc0 )

#define AI_PASSIVE      0x01
#define AI_CANONNAME    0x02
#define AI_NUMERICHOST  0x04
#define AI_NUMERICSERV  0x08
#define AI_V4MAPPED     0x10
#define AI_ALL          0x20
#define AI_ADDRCONFIG   0x40

#define AT_MAX_CID              10

#define MAX_DOMAIN_LEN 255
#define MAX_CHARACTER_NUM_PER_LABEL  63

typedef enum {
    DNS_STATE_UNUSED,
    DNS_STATE_INITED,
    DNS_STATE_ASKING,
}DNS_STATE;

typedef enum{
    DNS_ADDR_HOSTNAME,
    DNS_ADDR_IPADDR,
}DNS_ADDR_TYPE;

typedef enum
{
    DNS_IDLE,
    DNS_BUSY,
}DNS_PROCING_FLAG;

typedef struct dns_table_entry { 
   time_t       timeout;  //unit:s
   ip_addr_t   ipaddr1;
   ip_addr_t   ipaddr2;
   char*       hostname;
   struct dns_table_entry* next;
}dns_table_entry_t;

typedef struct dns_info_entry {
   time_t       timeout;  //unit:s
   ip_addr_t   ipaddr1;
   ip_addr_t   ipaddr2;
}dns_info_entry_t;

typedef struct dns_attempts_cfg {
    uint8   max_attempts;
    uint32  wait_timeout;
}dns_attempts_cfg_t;

typedef struct xDNSMessage
{
    uint16 usIdentifier;
    uint16 usFlags;
    uint16 usQuestions;
    uint16 usAnswers;
    uint16 usAuthorityRRs;
    uint16 usAdditionalRRs;
}xDNSMessage_t;

struct addrinfo {
    int               ai_flags;      /* Input flags. */
    int               ai_family;     /* Address family of socket. */
    int               ai_socktype;   /* Socket type. */
    int               ai_protocol;   /* Protocol of socket. */
    socklen_t         ai_addrlen;    /* Length of socket address. */
    struct sockaddr  *ai_addr;       /* Socket address of socket. */
    char             *ai_canonname;  /* Canonical name of service location. */
    struct addrinfo  *ai_next;       /* Pointer to next in list. */
};

typedef uint8 sa_family_t;
typedef uint16 in_port_t;

struct sockaddr_in_ipv4 {
  uint8           sin_len;
  sa_family_t     sin_family;
  in_port_t       sin_port;
  struct in_addr  sin_addr;
#define SIN_ZERO_LEN 8
  char            sin_zero[SIN_ZERO_LEN];
};

#define NETDB_ELEM_SIZE           (sizeof(struct addrinfo) + sizeof(struct sockaddr_storage) + DNS_MAX_NAME_LENGTH + 1)

typedef struct ip_addr_dns
{
   ip_addr_t  ip_addr;
   time_t     timeout;
   struct ip_addr_dns* ip_next;
}ip_addr_dns_t;

typedef enum
{
    DNS_QUEUE_COAP_DATA_MSG = 0,
    DNS_QUEUE_AT_MSG,
}DNS_QUEUE_MSG_TYPE;

typedef struct dns_at_msg_t
{
    char* hostname;
    uint8 dns_flag;
}dns_at_msg;

typedef struct
{
    uint8 *buffer;
    uint16  length;
    uint16  mode;
    uint8   seq_num;
    uint8   valid_flag;
}lwm2m_app_data_st;

void dns_init(void);
uint16 dns_proc(const char* hostname, dns_attempts_cfg_t* dns_attempt, struct sockaddr_in* sock_addr);
void dns_table_delete(char* addr);
void dns_send_to_incoming_queue(uint32 state);
uint8 dns_set_KV(const char* addr, dns_info_entry_t* dns_info);
void dns_erase_timeout_node_KV(char *addr);
uint8 dns_table_lookup(const char* addr, ip_addr_t* ip_addr);
uint8 dns_table_update(const char* addr, dns_info_entry_t* dns_info);
size_t prvCreateDNSMessage( uint8 *pucUDPPayloadBuffer, const char *pcHostName, uint16 usIdentifier );
void dns_create_queue(void);
void dns_main( void *unused );
void get_dns_serverip(void);
bool dns_check_hostname_timeout(char* hostname);
void dns_table_print(void);
void dns_info(char* domain, uint16 domain_len);
bool dns_check_uri(const char *uri);

unsigned char iccid_dns_get_ip(char *addr_str, ip4_addr_t *dns_IP);
#endif

