/******************************************************************************
 * @brief    Basic Production Management Functions for Hi21XX
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/

#ifndef LIB_NEUL_PRODUCTION_H_
#define LIB_NEUL_PRODUCTION_H_

#include "neulfw.h"
#include "neul_error_types.h"
#include "platform_definitions.h"   //needed for CORES
#include "neul_radio_types.h"
#include "neul_production_types.h"


/** @defgroup libNEUL_PRODUCTION Hi21XX libNEUL Production
 * Hi21XX libNeul Production API
 * @ingroup LIBNEUL
 * @{
 * */

/** Radio Test Interface Structure Definitions  */
typedef enum
{
    RADIO_TEST_RET_OK,
    RADIO_TEST_RET_UNKNOWN_COMMAND,
    RADIO_TEST_RET_MODE_ALREADY_ENABLED,
    RADIO_TEST_RET_INVALID_STATE,
    RADIO_TEST_RET_NOT_COMPLETE,
    RADIO_TEST_RET_TEST_MALLOC_FAIL
} RADIO_TEST_RET;

/**
 * @brief radio test callback
 * @param len radio test result lenth
 * @param retdata radio test result
 */
typedef void (*radio_test_callback)(uint8 retcode, uint16 len, const uint8* retdata);

/**
 * @brief Execute a binary encoded radio test command
 * It should only be used as instructed by Neul.
 * @param length The length of test data
 * @param test_data radiotest command
 * @param callback radio test result callback
 * @return error or success
 */
NEUL_RET production_execute_radiotest(uint16 length, uint8 *test_data, radio_test_callback callback);

/**
 * @brief read radio calibration
 * @param frequency frequency of the carrier to receive (Hz)
 * @param gain_index index of the gain to use for the measurment outputs
 * @param rssi Gain of the receiver in centibels at the input of the DSP
 * @param snr Signal to noise ratio in dB
 * @param port corresponding to the RX port
 */
NEUL_RET production_radio_config_meas_rssi(uint32 frequency, uint8 gain_index, int16 *rssi, int16 *snr, uint8 port);

/**
 * @brief read radio mipi word
 * @param slave_addr mipi slave address
 * @param data_addr  mipi slave register data address
 * @param data       mipi slave register data to read/write
 * @return success or failure
 */
NEUL_RET production_radio_config_read_mipi_word(uint8 slave_addr, uint8 data_addr, uint8* data);

/**
 * @brief write radio mipi word
 * @param slave_addr mipi slave address
 * @param data_addr  mipi slave register data address
 * @param data       mipi slave register data to read/write
 * @return success or failure
 */
NEUL_RET production_radio_config_write_mipi_word(uint8 slave_addr, uint8 data_addr, uint8 data);

/**
 * @brief read radio calibration
 * @param frequency Frequency of the carrier to transmit (Hz)
 * @param level RF level (units TBD)
 * @return success or failure.
 */
NEUL_RET production_radio_config_tx_tone(uint32 frequency);

/**
 * @brief set gain levels for RF TX configuration
 * @param tx_drive_level Tx DAC drive level, 0:1023
 * @param tx_coarse_gain Coarse Analog Tx gain, 0:3
 * @param rf_gain RF gain setting, 0:63
 * @param ext_pa_gain configure voltage level used
 *  to control an external SMPS for external Power Amplifier, 0:123
 */
NEUL_RET production_radio_config_set_tx_gains(uint16 tx_drive_level, uint8 tx_coarse_gain, uint8 rf_gain, uint16 ext_pa_gain);

/**
 * @brief get current RF TX configuration of gain levels
 * @param max_size_tx_gains max buffer size
 * @param tx_gains gain levels for RF TX configuration to get
 */
NEUL_RET production_radio_config_get_tx_gains(uint16 *tx_drive_level, uint8 *tx_coarse_gain, uint8 *rf_gain, uint16 *ext_pa_gain);

/**
 * @brief set up radio AIO for calibration tests
 * @param aio which aio needs to be used to set the voltage
 * @param voltage in mv
 */
NEUL_RET production_radio_config_set_rio_v(uint8 rio, uint16 mv);

/**
 * @brief set up GPIO for calibration tests
 * @param pio bitmask of which GPIO pins to set. only valid pins will be checked
 * @return success or failure
 */
NEUL_RET production_radio_config_set_gpio(uint64 pio);

/**
 * @brief get GPIO setup for calibration tests
 * @param pio bitmask of which GPIO pins are set.
 * @return success or failure
 */
NEUL_RET production_radio_config_get_gpio(uint64 *pio);

/**
 * @brief verify their Tx design calibration and compensation tables
 * @param tx_power Tx power level in dBm
 * @param tx_frequency Tx frequency in Hz
 * @param tx_duration Duration of transmission in reference clock cycles
 * @param tx_band EUTRA band number
 * @param temperature temperature that should be used as a lookup value in the temperature gain compensation table
 * @param voltage voltage that should be used as a lookup value in the voltage gain compensation table
 * @param num_subcarrier Number of subcarriers
 * @param subcarrier_index Position of subcarrier
 */
NEUL_RET production_radio_config_tx_verify(int8 tx_power, uint32 tx_frequency, uint32 tx_duration, uint8 tx_band, int16 temperature, int16 voltage, uint8 num_subcarrier, uint8 subcarrier_index);

/**
 * @brief tx list mode calibration
 * @param start_frequency Frequency of starting calibration
 * @param step_frequency Stepping of the calibration frequency
 * @param stop_frequency Calibrated maximum frequency
 * @param start_power Starting calibration power
 * @param step_power Calibrated power step
 * @param stop_power Maximum calibration power
 * @param num_subcarrier Number of subcarriers
 * @param subcarrier_index Position of subcarrier
 * @return success or failure
 */
NEUL_RET production_radio_config_tx_calist(uint32 start_frequency, uint32 step_frequency, uint32 stop_frequency, int8 start_power, int8 step_power, int8 stop_power, uint8 num_subcarrier, uint8 subcarrier_index);

/**
 * @brief rx list mode calibration
 * @param start_frequency Frequency of starting calibration
 * @param step_frequency Stepping of the calibration frequency
 * @param stop_frequency Calibrated maximum frequency
 * @param start_agc_index The starting value of the calibrated AGC
 * @param step_agc_index Calibrated AGC step
 * @param stop_agc_index The last AGC value of the calibration
 * @param up_power Expected uplink power
 * @param up_freq Expected uplink frequency
 * @param rssi_meas_duration Rssi measurement interval
 * @param sweep_band Measured band
 * @param nrdexec_rxlist_callback Rx calibration callback function
 * @return success or failure
 */
NEUL_RET production_radio_config_rx_calist(uint32 start_frequency, uint32 step_frequency, uint32 stop_frequency, uint8 start_agc_index, uint8 step_agc_index, uint8 stop_agc_index, int16 ul_power, uint32 ul_freq, uint32 rssi_meas_duration, uint8 sweep_band, radio_test_callback nrdexec_rxlist_callback);

/**
 * @brief verify Rx design calibration and compensation tables
 * @param frequency frequency of the carrier to receive (Hz)
 * @param gain_index index of the gain to use for the measurement
 * @param tx_band EUTRA band number
 * @param temperature temperature that should be used as a lookup value in the temperature gain compensation table
 * @param voltage voltage that should be used as a lookup value in the voltage gain compensation table
 * @param rssi Gain of the receiver in centibels at the input of the DSP to get
 * @param snr Signal to noise ratio in fixed point (Q7.8) dB to get
 * @param cbm received signal level in cBm to get
 * @return success or failure
 */
NEUL_RET production_radio_config_rx_verify(uint32 frequency, uint8 gain_index, uint8 band, int16 temperature, int16 voltage, int16 *rssi, int16* snr, int16* cbm);

/**
 * @brief rf config control command
 * @param cmd control command
 * @return success or failure
 */
NEUL_RET production_radio_config_ctrl(RF_CONFIG_CTRL_CMD cmd);

/**
 * @brief txtest Transmit a continuous test signal, either a tone or an NB-IOT signal using the specified subcarrier(s).
 * @param frequency frequency of the carrier to receive (Hz)
 * @param tx_band EUTRA band number
 * @param num_subcarrier Number of subcarriers
 * @param subcarrier_index Position of subcarrier
 */
NEUL_RET production_radio_config_tx_test(uint32 frequency, uint8 band, uint8 num_subcarrier, uint8 subcarrier_index);

/**
 * @brief calibrate_temperature.
 * @param temperature  current temperature in degrees Celsius
 * @return success or failure
 */
NEUL_RET production_calibrate_temperature(int16 temperature);

/** @} end of group libNEUL_PRODUCTION */

#endif /* LIB_NEUL_RADIO_H_ */
