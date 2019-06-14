/******************************************************************************
 * @brief    DMA Driver Header.
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef DMA_H_
#define DMA_H_

/** @defgroup DRIVER_CMSIS_DMA CMSIS DMA Driver
 * CMSIS DMA Driver
 * @ingroup DRIVER_CMSIS
 * @{
 * */

#define DMA_CH_MAX_TRANSFER_NUM             (0x1UL << 10) /* 1024 */

/** DMA manipulation result
 */
typedef enum
{
    DMA_RET_OK                                = 0,  //!< DMA manipulating is OK
    DMA_RET_NOT_INITIALIZED                   = 1,  //!< DMA module is NOT initialized
    DMA_RET_NO_AVAIL_CONTROLLER               = 2,  //!< Having no available DMA controller
    DMA_RET_NO_AVAIL_CH                       = 3,  //!< Having no available DMA channel
    DMA_RET_UNSUPPORTED_PERIPHERAL            = 4,  //!< DMA module do NOT support the peripheral
    DMA_RET_NOT_SUPPORTED_CONFIG              = 5,  //!< The configuration is NOT supported
    DMA_RET_ERROR_CONFIG                      = 6,  //!< The configuration has error
    DMA_RET_INCOMPLETE_CONFIG                 = 7,  //!< Need to complete the configuration batch, used in the scatter-gather transfer mode
    DMA_RET_ONE_TIME_BATCHED_CONFIGS_EXCEEDED = 8,  //!< The batched configurations in one transferring is over the maxinum number
    DMA_RET_CONFIG_QUEUE_FULL                 = 9,  //!< The transfer configuration queue of a specific channel is full
    DMA_RET_INVALID_ARGS                      = 10, //!< Invalid argument(s) is passed to function
    DMA_RET_OUT_OF_MEMORY                     = 11, //!< System memory is inadequate
    DMA_RET_NO_AVAIL_FREE_CONFIG              = 12  //!< Current channel has no available free driver configuration
} DMA_RET;

/** DMA Channel ID
 */
typedef enum
{
    DMA_CHANNEL_0,
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3,
    DMA_CHANNEL_MAX_NUM,
    DMA_CHANNEL_NONE = DMA_CHANNEL_MAX_NUM
} DMA_CHANNEL;

typedef enum
{
    DMA_CH_PRIORITY_HIGHEST  = 0,
    DMA_CH_PRIORITY_HIGH_1   = 1,
    DMA_CH_PRIORITY_HIGH_2   = 2,
    DMA_CH_PRIORITY_HIGH_3   = 3,
    DMA_CH_PRIORITY_LOW_1    = 4,
    DMA_CH_PRIORITY_LOW_2    = 5,
    DMA_CH_PRIORITY_LOW_3    = 6,
    DMA_CH_PRIORITY_LOWEST   = 7,
    DMA_CH_PRIORITY_RESERVED = 0xFF
} DMA_CH_PRIORITY;

/** DMA Channel transfer type
 */
typedef enum
{
    DMA_CH_TRANSFER_TYPE_MEM_TO_MEM,
    DMA_CH_TRANSFER_TYPE_MEM_TO_PERIPHERAL,
    DMA_CH_TRANSFER_TYPE_PERIPHERAL_TO_MEM,
    DMA_CH_TRANSFER_TYPE_MAX
} DMA_CH_TRANSFER_TYPE;

/** The power of 2 indicating how many DMA transfers responding to one burst request
 * DMA transfer: The action of transferring a single byte, halfword, or word.
 */
typedef enum
{
    DMA_POWER_OF_BURST_0    = 0,   //!< Run each DMA transfer in one burst
    DMA_POWER_OF_BURST_1    = 1,   //!< Run 2 DMA transfers in one burst
    DMA_POWER_OF_BURST_2    = 2,   //!< Run 4 DMA transfers in one burst
    DMA_POWER_OF_BURST_3    = 3,   //!< Run 8 DMA transfers in one burst
    DMA_POWER_OF_BURST_4    = 4,   //!< Run 16 DMA transfers in one burst
    DMA_POWER_OF_BURST_5    = 5,   //!< Run 32 DMA transfers in one burst
    DMA_POWER_OF_BURST_6    = 6,   //!< Run 64 DMA transfers in one burst
    DMA_POWER_OF_BURST_7    = 7,   //!< Run 128 DMA transfers in one burst
    DMA_POWER_OF_BURST_8    = 8,   //!< Run 256 DMA transfers in one burst
    DMA_POWER_OF_BURST_9    = 9,   //!< Run 512 DMA transfers in one burst
    DMA_POWER_OF_BURST_10   = 10,  //!< Run 1024 DMA transfers in one burst
} DMA_POWER_OF_BURST;

/** DMA channel cycle type
 * DMA cycle: All the DMA transfers that the controller must perform,
 * to transfer the N data packets.
 * DMA cycle type: The operating mode of the DMA cycle.
 */
typedef enum
{
    DMA_CH_CYCLE_TYPE_SINGLE,        //!< Single DMA cycle of a continuous address scope
    DMA_CH_CYCLE_TYPE_BATCHED_PART,  //!< One of Batched DMA cycles preceding the end one
    //!< Batched DMA cycle as following:
    //!< We transfer multiple parts which each one identifes
    //!< one scope of addresses transferring and usually are 
    //!< incontinuous address scopes with each other.
    //!<
    //!< +------+   +------+   +------+   +------+
    //!< | Part |-->| Part |-->| Part |-->| End  |
    //!< +------+   +------+   +------+   +------+
    DMA_CH_CYCLE_TYPE_BATCHED_END,   //!< The end of Batched DMA cycles
    DMA_CH_CYCLE_TYPE_MAX
} DMA_CH_CYCLE_TYPE;

/** DMA Channel user configuration of memory-to-memory type
 */
typedef struct
{
    uint32            src;           //!< The source address of this transfer
    uint32            dst;           //!< The destination address of this transfer
    uint16            transfer_num;  //!< transfer number of the bytes/halfwords/words based on your minimum transfer unit
    DMA_CH_CYCLE_TYPE cycle_type;    //!< channel cycle type that user indicated
} dma_ch_user_memory_config;

/** DMA Channel user configuration other than memory-to-memory type,
 * i.e. memory-to-peripheral or peripheral-to-memory type
 */
typedef struct
{
    uint32               addr;          //!< The memory start address of this transfer which is the
                                        //!< source address if the type is memory-to-peripheral or
                                        //!< the destination address if the type is peripheral-to-memory
    uint16               transfer_num;  //!< transfer number of the bytes/halfwords/words based on your minimum transfer unit
    DMA_CH_TRANSFER_TYPE transfer_type; //!< Channel transfer type
    DMA_CH_CYCLE_TYPE    cycle_type;    //!< channel cycle type that user indicated
} dma_ch_user_peripheral_config;

/** DMA Interrupt type
 */
typedef enum
{
    DMA_INTERRUPT_DONE,
    DMA_INTERRUPT_ERR,
    DMA_INTERRUPT_MAX
} DMA_INTERRUPT;

/** DMA peripheral feature
 */
typedef struct
{
    DMA_POWER_OF_BURST      power_of_burst;     //!< Power of 2 for one time of burst transfers specific to the connected peripheral
    bool                    use_burst;          //!< The controller only responds to dma_req[C] requests and performs 2^POWER_OF_BURST transfers
    uint32                  periph_addr;        //!< Channel connected peripheral address
} dma_peripheral_feature;

/** DMAC channel transfer done/error callback function pointer type of user
 */
typedef void (*dma_transfer_callback)(DMA_INTERRUPT intr);

/** Prepare to transfer data through DMA channel based on the associated peripheral
 */
typedef void (*dma_transfer_peripheral_prepare_callback)(DMA_PERIPHERAL peripheral);

/** Finish to transfer data through DMA channel based on the associated peripheral
 */
typedef void (*dma_transfer_peripheral_finish_callback)(DMA_PERIPHERAL peripheral);

/** DMA peripheral configurations set supplied by the peripheral driver
 */
typedef struct
{
    DMA_PERIPHERAL                           peripheral;        //!< DMA peripheral ID
    dma_peripheral_feature                   feature;           //!< peripheral feature relevant to the DMA transfer such as power_of_burst, use_burst, etc.
    dma_transfer_peripheral_prepare_callback transfer_prepare;  //!< Transfer parepare callback function supplied by the peripheral driver
    dma_transfer_peripheral_finish_callback  transfer_finish;   //!< Transfer finish callback function supplied by the peripheral driver
} dma_peripheral_config;

/** Initialize the DMA module
 */
void dma_init(void);

/** Deinitialize the DMA module
 */
void dma_deinit(void);


/** Get a free previously claimed DMA Controller's channel for data transfer.
 * @param ch the DMAC channel ID
 * @param pri the minimum priority of the expected opened channel
 * @param cfg the DMA peripheral configurations set if not NULL, and indicates that
 *   the DMA channel is doing memory-to-memory transfers if the cfg is NULL
 * @return OK if the channle opened succeeded or corresponding error code otherwise
 */
DMA_RET dma_ch_open(DMA_CHANNEL *ch, DMA_CH_PRIORITY pri, const dma_peripheral_config *cfg);

/** Close the specific DMA Channel
 * @param ch the DMAC channel ID
 */
void dma_ch_close(DMA_CHANNEL ch);

/** Transfer bytes of type memory-to-memory through DMA channel
 * @param ch the DMAC channel ID
 * @param user_cfg DMAC channel transfer configuration of user
 * @param callback channel transfer done/error callback function
 * @return OK if the operation succeeded or corresponding error code otherwise
 */
DMA_RET dma_transfer_memory_bytes(DMA_CHANNEL ch, const dma_ch_user_memory_config *user_cfg, dma_transfer_callback callback);

/** Transfer halfwords of type memory-to-memory through DMA channel
 * @param ch the DMAC channel ID
 * @param user_cfg DMAC channel transfer configuration of user
 * @param callback channel transfer done/error callback function
 * @return OK if the operation succeeded or corresponding error code otherwise
 */
DMA_RET dma_transfer_memory_halfwords(DMA_CHANNEL ch, const dma_ch_user_memory_config *user_cfg, dma_transfer_callback callback);

/** Transfer words of type memory-to-memory through DMA channel
 * @param ch the DMAC channel ID
 * @param user_cfg DMAC channel transfer configuration of user
 * @param callback channel transfer done/error callback function
 * @return OK if the operation succeeded or corresponding error code otherwise
 */
DMA_RET dma_transfer_memory_words(DMA_CHANNEL ch, const dma_ch_user_memory_config *user_cfg, dma_transfer_callback callback);

/** Transfer bytes of type memory-to-peripheral or peripheral-to-memory through DMA channel
 * @param ch the DMAC channel ID
 * @param user_cfg DMAC channel transfer configuration of user
 * @param callback channel transfer done/error callback function
 * @return OK if the operation succeeded or corresponding error code otherwise
 */
DMA_RET dma_transfer_peripheral_bytes(DMA_CHANNEL ch, const dma_ch_user_peripheral_config *user_cfg, dma_transfer_callback callback);

/** Transfer halfwords of type memory-to-peripheral or peripheral-to-memory through DMA channel
 * @param ch the DMAC channel ID
 * @param user_cfg DMAC channel transfer configuration of user
 * @param callback channel transfer done/error callback function
 * @return OK if the operation succeeded or corresponding error code otherwise
 */
DMA_RET dma_transfer_peripheral_halfwords(DMA_CHANNEL ch, const dma_ch_user_peripheral_config *user_cfg, dma_transfer_callback callback);

/** Transfer words of type memory-to-peripheral or peripheral-to-memory through DMA channel
 * @param ch the DMAC channel ID
 * @param user_cfg DMAC channel transfer configuration of user
 * @param callback channel transfer done/error callback function
 * @return OK if the operation succeeded or corresponding error code otherwise
 */
DMA_RET dma_transfer_peripheral_words(DMA_CHANNEL ch, const dma_ch_user_peripheral_config *user_cfg, dma_transfer_callback callback);

/** @} end of group DRIVER_CMSIS_DMA */

#endif /* DMA_H_ */
