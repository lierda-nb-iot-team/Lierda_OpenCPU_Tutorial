/*
 * @file app_at_ue_stats.h
 * @brief Declarations for ue_stats printing 
 * Copyright (c) 2016 NEUL LIMITED
 */
 
#ifndef    _APP_AT_UE_STATS_H_
#define    _APP_AT_UE_STATS_H_
#include "platform_definitions.h"
#include "neul_radio.h"

/** @addtogroup libNEUL_APP_AT_INT
 * @{
 * */

/*
 * These declarations must be kept in sync with struct ue_stats in neul/public/ipc_radio.h and ue_stats/public/ue_stats.h
 */
  
/*
 * Format sepcifiers for ue_stats values
 */ 
const char * const ue_stats_labels[] = {
        "Version:%u",
        "Signal power:%d",
        "Total power:%d",
        "TX power:%d",
        "TX time:%u",
        "RX time:%u",
        "Cell ID:%u",
        "ECL:%u",
        "SNR:%d",
        "EARFCN:%u",
        "PCI:%u",
        "RSRQ:%d",
        "OPERATOR MODE:%d",
        "CURRENT BAND:%d"
};

const char * const ue_stats_bler_labels[] = {
    NULL,
    "RLC UL BLER,%u",
    "RLC DL BLER,%u",
    "MAC UL BLER,%u",
    "MAC DL BLER,%u",
    "Total TX bytes,%u",
    "Total RX bytes,%u",
    "Total TX blocks,%u",
    "Total RX blocks,%u",
    "Total RTX blocks,%u",
    "Total ACK/NACK RX,%u",
};
/*
 * enumerator for ue_stats values
 */
enum ue_stats_labels_index {
    UE_STATS_VERSION_FIELD = 0,
    UE_STATS_SIGNAL_POWER,
    UE_STATS_TOTAL_POWER,
    UE_STATS_TX_POWER,
    UE_STATS_TX_TIME,
    UE_STATS_RX_TIME,
    UE_STATS_CELL_ID,
    UE_STATS_LAST_ECL,
    UE_STATS_SINR,
    UE_STATS_EARFCN,
    UE_STATS_PCI,
    UE_STATS_RSRQ,
    UE_STATS_OPERATION_MODE,
    UE_STATS_CURRENT_BAND,
    UE_STATS_LAST_LABEL
};

typedef enum ue_stats_bler_labels_index {
    UE_STATS_BLER_FIRST_LABEL = 0,
    UE_STATS_BLER_RLC_UL,
    UE_STATS_BLER_RLC_DL,
    UE_STATS_BLER_MAC_UL,
    UE_STATS_BLER_MAC_DL,
    UE_STATS_BLER_TX_BYTES,
    UE_STATS_BLER_RX_BYTES,
    UE_STATS_BLER_TX_BLOCKS,
    UE_STATS_BLER_RX_BLOCKS,
    UE_STATS_BLER_RTX_BLOCKS,
    UE_STATS_BLER_ACK_NACK_BLOCKS,
    UE_STATS_BLER_LAST_LABEL
}UE_STATS_BLER_INDEX_e;

/** @} end of group libNEUL_APP_AT_INT */

#endif // _APP_AT_UE_STATS_H_
