/******************************************************************************
 * @brief    lwip pbuf compatible header file
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LWIP_SUPPORT_PBUF_H
#define LWIP_SUPPORT_PBUF_H

#include "lwip/opt.h"
#include "lwip/err.h"

/** @addtogroup LWIP_SUPPORT
 * @{
 * */

#if LWIP_IPV6
#define PBUF_IP_HLEN        40
#else
#define PBUF_IP_HLEN        20
#endif

typedef enum {
    PBUF_TRANSPORT,       /** space for transport layer header */
    PBUF_IP,              /** space for IP  header */
    PBUF_LINK,            /** space for link layer headers */
    PBUF_RAW_TX,
    PBUF_RAW
} pbuf_layer;

typedef enum {
    PBUF_RAM,             /** pbuf in ram for TX */
    PBUF_ROM,             /** pbuf in rom */
    PBUF_REF,             /** similar to pbuf_rom, but payload may change */
    PBUF_POOL             /** pool pbuf for RX */
} pbuf_type;


struct pbuf {
    struct pbuf *next;    /** next pbuf in singly linked pbuf chain */
    void *payload;        /** pointer to the actual data in the buffer */
    u16_t tot_len;        /** length of all pbufs in chain */
    u16_t len;            /** length of this buffer */
    u8_t  type;           /** pbuf_type*/
    u32_t flags;
    u16_t ref;            /** pbuf reference count */
};

/** Allocate a pbuf chain
 * @param layer flag to define header size
 * @param length size of the pbuf payload
 * @param type where to allocate PBUF (PBUF_RAM/PBUF_ROM/PBUF_REF/PBUF_POOL)
 * @return the allocated pbuf chain
 */
struct pbuf *pbuf_alloc(pbuf_layer layer, u16_t length, pbuf_type type);

/** change size (shrink) of pbuf chain
 * @param pbuf chain to change size of
 * @param new_len new length of chain
 */
void pbuf_realloc(struct pbuf *p, u16_t new_len);

/** dereference and, if ref=0, free a pbuf/pbuf chain
 * @param pbuf chain to be dereferenced.
 * @return the number of pbufs that were freed
 */
u8_t pbuf_free(struct pbuf *p);

/** Adjust pbuf payload pointer
 * @param pbuf to change the header size.
 * @param header_size_increment number of bytes to increase header by
 * @return 0 on success, else !0 on failure
 */
u8_t pbuf_header(struct pbuf *p, s16_t header_size_increment);

/** Concatenate two pbufs
 * @param head pbuf
 * @param tail pbuf
 */
void pbuf_cat(struct pbuf *head, struct pbuf *tail);

/** create a PBUF_RAM and copy in
 * @param p_to destination
 * @param p_from source
 * @return ERR_OK if copied successfully, else error
 */
err_t pbuf_copy(struct pbuf *p_to, const struct pbuf *p_from);

/** Increment pbuf reference count
 * @param pbuf to add reference
 *
 */
void pbuf_ref(struct pbuf *p);

/** Take a pbuf
 * @param pbuf to take
 * @param data buffer pointer
 * @paran len
 * @return 0 if successful, !0 if error
 */
err_t pbuf_take(struct pbuf *buf, const void *dataptr, u16_t len);

/** Chain two pbufs together
 * @param head pbuf
 * @param tail pbuf
 */
void pbuf_chain(struct pbuf *head, struct pbuf *tail);

/** Remove first pbug from chain
 * @param pbuf to remove from chain
 * @return remainder of the pbuf chain or NULL if chain had one item
 */
struct pbuf * pbuf_dechain(struct pbuf *p);

/** @} end of group LWIP_SUPPORT */

#endif /* LWIP_SUPPORT_PBUF_H */
