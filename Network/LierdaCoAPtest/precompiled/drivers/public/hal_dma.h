/******************************************************************************
 * @brief    Hi21XX DMA HAL Header
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef HAL_DMA_H_
#define HAL_DMA_H_

#include "platform.h"

/* These following lint exceptions are for unreferenced defs.  Should be removed as and when they are used. */
//lint -esym(755,HAL_DMA_CH_REAL_PRIORITY_HIGHEST)
//lint -esym(755,HAL_DMA_CH_REAL_PRIORITY_LOWEST)
//lint -esym(755,HAL_DMA_CH_REAL_PRIORITY_LEVEL)
//lint -esym(755,HAL_DMA_CH_REAL_PRI_TO_CH_ID)

/** @defgroup DRIVER_HAL_DMA Hi211X HAL DMA Driver
 * HAL DMA Driver
 * @ingroup DRIVER_HAL
 * @{
 * */

#define HAL_DMA_CH_TRANSFER_QUEUE_MAX_SIZE              (10UL)

#define HAL_DMA_CH_MAX_TRANSFER_NUM                     (0x1UL << 10) /* 1024 */

/* Maximum Scatter-Gather mode configs number in a group of Scatter-Gather DMA configs
 * which starts with a Memory/Peripheral alternate Scatter-Gather config, ends with a
 * Basic config. 
 */
#define HAL_DMA_MAX_SUPPORTED_SCATTER_GATHER_CONFIGS    (9)

/** Compute the DMA transfers of arbitration occurs based on the r_power value */
#define HAL_DMA_R_POWER_TRANSFERS(r_power)              (1 << r_power)

/** DMA real priority recognised by the DMAC, the real priority value less, the priority higher,
 *  as follows(there are 4 channels in each DMAC):
 *  CH ID   |   PriorityLevelSetting   |    Real Priority
 *    0     |          High            |       Highest
 *    1     |          High            |          |
 *    2     |          High            |          |
 *    3     |          High            |          |Descending
 *    0     |          Default         |          |
 *    1     |          Default         |          |
 *    2     |          Default         |          V
 *    3     |          Default         |        Lowest
 */
#define HAL_DMA_CH_REAL_PRIORITY(ch_id, level)          ((level) * HAL_DMA_CHANNEL_MAX_NUM + (ch_id))
#define HAL_DMA_CH_REAL_PRIORITY_HIGHEST                HAL_DMA_CH_REAL_PRIORITY(HAL_DMA_CHANNEL_0, HAL_DMA_CH_PRIORITY_LEVEL_HIGH)
#define HAL_DMA_CH_REAL_PRIORITY_LOWEST                 HAL_DMA_CH_REAL_PRIORITY(HAL_DMA_CHANNEL_3, HAL_DMA_CH_PRIORITY_LEVEL_DEFAULT)
#define HAL_DMA_CH_REAL_PRIORITY_LEVEL(real_pri)        ((real_pri) / HAL_DMA_CHANNEL_MAX_NUM)
#define HAL_DMA_CH_REAL_PRI_TO_CH_ID(real_pri)          ((real_pri) % HAL_DMA_CHANNEL_MAX_NUM)

#define HAL_DMA_INTEGRATION_CONFIGURATION_BASE_OFFSET   (0xE00)
#define HAL_DMA_ERR_SET_TEST_BASE_OFFSET                (0xE48)

/** DMA Channel priority
 */
typedef enum
{
    HAL_DMA_CH_PRIORITY_LEVEL_HIGH,
    HAL_DMA_CH_PRIORITY_LEVEL_DEFAULT,
} HAL_DMA_CH_PRIORITY_LEVEL;

/** DMA transfer data width
 */
typedef enum
{
    HAL_DMA_DATA_WIDTH_BYTE     = 0x0,
    HAL_DMA_DATA_WIDTH_HALFWORD = 0x1,
    HAL_DMA_DATA_WIDTH_WORD     = 0x2,
    HAL_DMA_DATA_WIDTH_RESERVED = 0x3,
} HAL_DMA_DATA_WIDTH;

/** DMA src/dst address increment
 */
typedef enum
{
    HAL_DMA_ADDRESS_INC_BYTE        = 0x0,
    HAL_DMA_ADDRESS_INC_HALFWORD    = 0x1,
    HAL_DMA_ADDRESS_INC_WORD        = 0x2,
    HAL_DMA_ADDRESS_INC_NO_INC      = 0x3,
    HAL_DMA_ADDRESS_INC_TYPES
} HAL_DMA_ADDRESS_INC;

/** The power of 2 indicating how many DMA transfers before rearbitrating
 * DMA transfer: The action of transferring a single byte, halfword, or word.
 */
typedef enum
{
    HAL_DMA_R_POWER_0       = 0,   //!< Arbitrates after each DMA transfer
    HAL_DMA_R_POWER_1       = 1,   //!< Arbitrates after 2 DMA transfers
    HAL_DMA_R_POWER_2       = 2,   //!< Arbitrates after 4 DMA transfers
    HAL_DMA_R_POWER_3       = 3,   //!< Arbitrates after 8 DMA transfers
    HAL_DMA_R_POWER_4       = 4,   //!< Arbitrates after 16 DMA transfers
    HAL_DMA_R_POWER_5       = 5,   //!< Arbitrates after 32 DMA transfers
    HAL_DMA_R_POWER_6       = 6,   //!< Arbitrates after 64 DMA transfers
    HAL_DMA_R_POWER_7       = 7,   //!< Arbitrates after 128 DMA transfers
    HAL_DMA_R_POWER_8       = 8,   //!< Arbitrates after 256 DMA transfers
    HAL_DMA_R_POWER_9       = 9,   //!< Arbitrates after 512 DMA transfers
    HAL_DMA_R_POWER_10      = 10,  //!< Arbitrates after 1024 DMA transfers
    HAL_DMA_R_POWER_DEFAULT = HAL_DMA_R_POWER_0
} HAL_DMA_R_POWER;

/** Determine whether the remaining peripheral scatter-gather mode
 * DMA transfers use burst mode while completing a time of DMA
 * transfer that uses the alternate data structure
 */
typedef enum
{
    HAL_DMA_NEXT_USE_BURST_DISABLE, //!< Remaining DMA cycles both responding to burst transfers request and single transfer request
    HAL_DMA_NEXT_USE_BURST_ENABLE   //!< Remaining DMA cycles only responding to burst transfers request
} HAL_DMA_NEXT_USE_BURST;

/** DMA Channel cycle type
 * DMA cycle: All the DMA transfers that the controller must perform,
 * to transfer the N data packets.
 * DMA cycle type: The operating mode of the DMA cycle.
 */
typedef enum
{
    HAL_DMA_CH_CYCLE_TYPE_STOP,                          //!< Channel control data structure is invalid
    HAL_DMA_CH_CYCLE_TYPE_BASIC,                         //!< Basic DMA transfer
    HAL_DMA_CH_CYCLE_TYPE_AUTO_REQUEST,                  //!< Auto-request
    HAL_DMA_CH_CYCLE_TYPE_PING_PONG,                     //!< Ping-pong
    HAL_DMA_CH_CYCLE_TYPE_SCATTER_GATHER_MEM_PRI,        //!< Memory scatter-gather using the primary data structure
    HAL_DMA_CH_CYCLE_TYPE_SCATTER_GATHER_MEM_ALT,        //!< Memory scatter-gather using the alternate data structure
    HAL_DMA_CH_CYCLE_TYPE_SCATTER_GATHER_PERIPHERAL_PRI, //!< Peripheral scatter-gather using the primary data structure
    HAL_DMA_CH_CYCLE_TYPE_SCATTER_GATHER_PERIPHERAL_ALT, //!< Peripheral scatter-gather using the alternate data structure
} HAL_DMA_CH_CYCLE_TYPE;

#define HAL_DMA_CH_CYCLE_TYPE_SCATTER_GATHER_ALTERNATE_TO_PRIMARY(mode) (HAL_DMA_CH_CYCLE_TYPE)(mode - 1)

/** DMA Channel ID
 */
typedef enum
{
    HAL_DMA_CHANNEL_0,
    HAL_DMA_CHANNEL_1,
    HAL_DMA_CHANNEL_2,
    HAL_DMA_CHANNEL_3,
    HAL_DMA_CHANNEL_MAX_NUM,
    HAL_DMA_CHANNEL_NONE = HAL_DMA_CHANNEL_MAX_NUM
} HAL_DMA_CHANNEL;

typedef uint8 hal_dma_ch_real_pri_t;

/** DMA channel working state
 */
typedef enum
{
    HAL_DMA_CH_STATE_CLOSED,    //!< The DMA channel is closed
    HAL_DMA_CH_STATE_IDLE,      //!< The DMA channel has been opend but its logic configuration queue has no configurations to be sent
    HAL_DMA_CH_STATE_ACTIVE,    //!< The DMA channel is transferring data or has been done the data transferring
    HAL_DMA_CH_STATE_FINISHED,  //!< Useless now
    HAL_DMA_CH_STATE_ERROR      //!< The DMA channel has had error while transferring data
} HAL_DMA_CH_STATE;

/** DMA Interrupt type
 */
typedef enum
{
    HAL_DMA_INTERRUPT_DONE,
    HAL_DMA_INTERRUPT_ERR,
    HAL_DMA_INTERRUPT_MAX
} HAL_DMA_INTERRUPT;

/** DMA manipulation result
 */
typedef enum
{
    HAL_DMA_RET_OK                              = 0, //!< DMA manipulating is OK
    HAL_DMA_RET_NOT_INITIALIZED                 = 1, //!< DMA module is NOT initialized
    HAL_DMA_RET_INVALID_ARGS                    = 2  //!< Invalid argument(s) is passed to function
} HAL_DMA_RET;

typedef enum
{
    PANIC_HAL_DMA_MEMORY_ALLOCATION_FAILED = 0x80    //!< Distinguish with driver layer, start from 0x80
} PANIC_ID_HAL_DMA;

/** DMAC channel transfer done/error callback function pointer type of user
 */
typedef void (*hal_dma_transfer_callback)(HAL_DMA_INTERRUPT intr);

/** DMA Channel peripheral feature
 */
typedef struct
{
    bool use_burst;
} hal_dma_ch_periph_feature;

/** Prepare to transfer data through DMA channel based on the associated peripheral
 */
typedef void (*hal_dma_transfer_peripheral_prepare_callback)(DMA_PERIPHERAL peripheral);

/** DMA Channel configuration
 */
typedef struct hal_dma_ch_cfg
{
    uint32                    src;                    //!< Start address of source
    uint32                    dst;                    //!< Start address of destination
    HAL_DMA_DATA_WIDTH        data_width;             //!< src and dst data width
    HAL_DMA_ADDRESS_INC       src_inc;                //!< source address increment
    HAL_DMA_ADDRESS_INC       dst_inc;                //!< destination address increment
    HAL_DMA_NEXT_USE_BURST    next_use_burst;         //!< Whether the next transfer after this time transfer using 
                                                      //!< mode when using Peripheral Scatter-Gather transfer
    uint16                    transfer_num;           //!< Total DMA transfers of the configuraion in unit of data_width
    HAL_DMA_CH_CYCLE_TYPE     cycle_type;             //!< DMA cycle type
    HAL_DMA_R_POWER           r_power;                //!< Control how many DMA transfers can occur before the controller rearbitrates
    uint8                     scatter_gather_configs; //!< Configs num while in the scatter-gather mode transfer
    bool                      ready;                  //!< This configuration has been ready to be transferred
    uint8                     index;                  //!< The self index in the config buffer
    hal_dma_transfer_callback callback;               //!< Transfer done/error callback of user
} hal_dma_ch_configuration;

/** DMA Interrupt Service Routine Callback Type
 */
typedef void (*HAL_DMA_ISR_CALLBACK)(HAL_DMA_CHANNEL ch);

/**
 * Internal DMA interrupt callbacks type
 */
typedef struct
{
    HAL_DMA_ISR_CALLBACK done_isr;
    HAL_DMA_ISR_CALLBACK err_isr;
} hal_dma_isr_callbacks;

/** Initialize the DMA Controller
 */
void hal_dma_init(void);

/** Deinitialise the DMA controller
 */
void hal_dma_deinit(void);

/** Claim the DMA controller
 * @return OK if the controller claim succeeded or corresponding error code otherwise
 */
HAL_DMA_RET hal_dma_claim(void);

/** Check wheher the DMA controller had been claimed
 * @return true if the controller had been claimed or the error code otherwise
 */
bool hal_dma_is_claimed(void);

/** Release the DMA controller
 */
void hal_dma_release(void);

/** Register the transfer prepare callback of the driver for the peripheral
 * that the DMA channel associated with
 * @param ch DMAC channel ID
 * @param callback the transfer prepare callback of the peripheral driver
 */
void hal_dma_ch_register_peripheral_prepare_callback(HAL_DMA_CHANNEL ch, hal_dma_transfer_peripheral_prepare_callback callback);

/** Deregister the transfer prepare callback of the driver for the peripheral
 * that the DMA channel associated with
 * @param ch DMAC channel ID
 */
void hal_dma_ch_deregister_peripheral_prepare_callback(HAL_DMA_CHANNEL ch);

/** Get a free previously claimed DMA Controller's channel for data transfer.
 * @param ch the DMAC channel ID
 * @param pri the minnum priority of the expected opened channel
 * @param periph the peripheral ID that would associated with that channel
 * @return true if the channle opened succeeded or false otherwise
 */
bool hal_dma_ch_open(HAL_DMA_CHANNEL *ch, hal_dma_ch_real_pri_t pri, DMA_PERIPHERAL periph);

/** Disable the specific DMA Channel and set the channel's state to closed
 * @param ch the DMAC channel ID
 */
void hal_dma_ch_close(HAL_DMA_CHANNEL ch);

/** Check whether all the channels of DMA controller are closed
 * @return true if all the DMA channels are closed or false otherwise
 */
bool hal_dma_all_ch_are_closed(void);

/** Check whether the DMA channel is closed
 * @param ch DMA channel ID
 * @return true if the channel is closed or false otherwise
 */
bool hal_dma_ch_is_closed(HAL_DMA_CHANNEL ch);

/** Configure the DMA channel configuration feature related to the peripheral associated
 * @param ch DMA channel ID
 * @param feature DMA channel peripheral feature
 */
void hal_dma_ch_configure_peripheral_feature(HAL_DMA_CHANNEL ch, const hal_dma_ch_periph_feature *feature);

/** Get the DMA channel state
 * @param ch DMA channel ID
 * @return the conrresponding DMA channel state
 */
HAL_DMA_CH_STATE hal_dma_ch_state_get(HAL_DMA_CHANNEL ch);

/** Set the DMA channel state
 * @param ch DMA channel ID
 * @param state setting channel state
 */
void hal_dma_ch_state_set(HAL_DMA_CHANNEL ch, HAL_DMA_CH_STATE state);

/** Initialise the DMA channel configuration buffer
 * @param ch DMA channel ID
 */
void hal_dma_ch_config_buffer_init(HAL_DMA_CHANNEL ch);

/** De-initialise the DMA channel configuration buffer
 * @param ch DMA channel ID
 */
void hal_dma_ch_config_buffer_deinit(HAL_DMA_CHANNEL ch);

/** Get the N-th free config from the config buffer
 * @param ch DMA channel ID
 * @param index The index of the free configs in the config buffer which start
 *              from Index 0 for the first free one, Index 1 for the second free one, and so on
 * @return Pointer to the N-th free config in the config buffer
 */
hal_dma_ch_configuration *hal_dma_ch_config_buffer_get_free_config(HAL_DMA_CHANNEL ch, uint8 index);

/** Get the first used config in the config buffer
 * @param ch DMA channel ID
 * @return The pointer to the first used config in the config buffer
 */
hal_dma_ch_configuration *hal_dma_ch_config_buffer_get_first_used(HAL_DMA_CHANNEL ch);

/** Add a used(configured) config to the config buffer
 * @param ch The DMA channel ID
 */
void hal_dma_ch_config_buffer_add_config(HAL_DMA_CHANNEL ch);

/** Remove N used configs from the config buffer
 * @param ch The DMA channel ID
 * @param dropped_count The number of removed used configs
 */
void hal_dma_ch_config_buffer_remove_config(HAL_DMA_CHANNEL ch, uint8 dropped_count);

/** Check whether the DMA channel transfer configuration is OK
 * @param config DMAC channel transfer configuration
 * @return true if the configuration is OK or false otherwise
 */
bool hal_dma_check_ch_transfer_config(const hal_dma_ch_configuration *config);

/** The core function to start transfer the data through the DMA channel
 * @param ch DMA channel ID
 * @param cfg DMA channel transfer configuration
 * @return true if the transfer starting succeeded or false otherwise
 */
bool hal_dma_transfer(HAL_DMA_CHANNEL ch, hal_dma_ch_configuration *cfg);

/** Free the specific DMA channel's scatter_gather alternate configuration buffer in memory
 * @param ch DMA channel ID
 */
void hal_dma_ch_scatter_gather_alternate_config_buffer_free(HAL_DMA_CHANNEL ch);

/** Allocate the specific DMA channel's scatter_gather alternate configuration buffer in memory
 * @param ch DMA channel ID
 */
void hal_dma_ch_scatter_gather_alternate_config_buffer_alloc(HAL_DMA_CHANNEL ch);


/** Configure the DMA interrupt callback function and turn on/off the corresponding interrput based on the arguments
 * @param ch DAM channel ID
 * @param interrupt_type which type of interrupt to be configured
 * @param callback the configured callback function
 * @param initial_state determine to turn on or turn off the interrupt
 */
void hal_dma_configure_interrupt(HAL_DMA_CHANNEL ch, HAL_DMA_INTERRUPT interrupt_type, HAL_DMA_ISR_CALLBACK callback, INTERRUPT_STATE initial_state );

/** Enable a specific DMA channel interrupt
 * @param ch DMA channel ID
 * @param interrupt_type which type of interrupt to be enabled
 */
void hal_dma_enable_interrupt(HAL_DMA_CHANNEL ch, HAL_DMA_INTERRUPT interrupt_type);

/** Disable a specific DMA channel interrupt
 * @param ch DMA channel ID
 * @param interrupt_type which type of interrupt to be disabled
 */
void hal_dma_disable_interrupt(HAL_DMA_CHANNEL ch, HAL_DMA_INTERRUPT interrupt_type);

/** Clear the DMA channel interrupt status in the register
 * @param ch DMA channel ID
 * @param interrupt_type which type of interrupt to be cleared
 */
void hal_dma_clear_interrupt(HAL_DMA_CHANNEL ch, HAL_DMA_INTERRUPT interrupt_type);

/** Select the primary data structure for the corresponding DMA channel
 * @param ch DMA channel ID
 */
void hal_dma_ch_select_primary(HAL_DMA_CHANNEL ch);

/** Enable a specific DMA channel
 * @param ch DMA channel ID
 */
void hal_dma_enable_ch(HAL_DMA_CHANNEL ch);

/** Disable a specific DMA channel
 * @param ch DMA channel ID
 */
void hal_dma_disable_ch(HAL_DMA_CHANNEL ch);

/** Check whether a specific DMA channel is enabled
 * @param ch DMA channel ID
 * @return true if the DMA channel is enabled or false otherwise
 */
bool hal_dma_ch_is_enabled(HAL_DMA_CHANNEL ch);

/** Check whethe the specific DMA channel is busy
 * @param ch DMA channel ID
 * @return ture if the DMA channel is busy or false otherwise
 */
bool hal_dma_ch_is_busy(HAL_DMA_CHANNEL ch);

/** @} end of group DRIVER_HAL_DMA */

#endif /* HAL_DMA_H_ */
