/******************************************************************************
* @brief   Logical channel Management Functions library
* Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/

#ifndef LIB_LOGICAL_CHANNEL_H_
#define LIB_LOGICAL_CHANNEL_H_

#include "neulfw.h"
#include "neul_error_types.h"
#include "neul_radio_types.h"
#include "platform_definitions.h"   //needed for CORES


#define FIRST_CHANNEL_NB        0       /** basic channel number */
#define LAST_CHANNEL_NB         3       /** highest channel number */
#define APP_ID_MIN_LENGTH       1       /** min length of the application ID, in bytes */
#define APP_ID_MAX_LENGTH       16      /** maximal length of the application ID, in bytes */
#define MAX_SEND_DATA_LEN       261
#define MAX_RECV_DATA_LEN       258
#define COMMAND_CLA             0

/**
 * @brief Open a uicc logical channel to the card and
 * activate the specified application.
 * @param app_id ID of the application to select; must point to app_id_len bytes;
 * should not be NULL
 * @param app_id_len length of the application ID, in bytes
 * @param channel_num IN: address where to store the returned channel number
 * OUT: the channel used to communicate with the card
 * if a card is available; NULL otherwise
 * @return success or error
 */
NEUL_RET open_logical_channel(uint8 *app_id, uint16 app_id_len, uint8 *channel_num);

/**
 * @brief Close the logical channel and terminate the linked application.
 * @param channel_num uicc logical channel number
 * @return success or error
 */
NEUL_RET close_logical_channel(uint8 channel_num);

/**
 * @brief Send data to a T=0 card. When processing such a command,
 * the UICC driver is in charge of handling T=0 procedure bytes.
 * @param channel_num uicc logical channel number
 * @param cmd command send to the card
 * @param cmd_len command data length
 * @param rsp response data received from the card
 * @param rsp_len response data length
 * @return success or error
 */
NEUL_RET generic_uicc_logical_channel_access(uint8 channel_num,  uint8 *cmd, uint16 cmd_len, uint8 *rsp, uint16 *rsp_len);

/**
 * @brief control uicc status, power on/off
 * @param status uicc power on/off
 * @return success or error
 */
NEUL_RET uicc_status_control(NEUL_UICC_STATUS status);

/**
 * @brief restricted_sim_access
 * @param cmd command send to the card
 * @param rsp response data received from the card
 * @param rsp_len response data length
 * @return ret
 */
NEUL_RET restricted_sim_access(crsm_command *cmd, uint8 *rsp, uint16 *rsp_len);
#endif /* LIB_LOGICAL_CHANNEL_H_ */
