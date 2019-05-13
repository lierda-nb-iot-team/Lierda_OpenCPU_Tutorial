/******************************************************************************
 * @brief    BOUDICA AT UTILS FUNCTION INTERFACE
 * Copyright (c) 2016 NEUL LIMITED
******************************************************************************/
#ifndef APP_AT_UTILS_H
#define APP_AT_UTILS_H

#include <time.h>
#include "neulfw.h"
#include "neul_error_types.h"
#include "neul_ip_addr.h"
#include "app_at.h"

/** @defgroup libNEUL_APP_AT_MOD_API Hi21XX AT Command Processor Module API
 * Hi21XX AT Command Processor Module API
 * @ingroup libNEUL_APP_AT
 * @{
 * */

#define AT_PARSE_FIRST_PARAM_POS     0
#define AT_PARSE_SECOND_PARAM_POS    1
#define AT_PARSE_THIRD_PARAM_POS     2
#define AT_PARSE_FOURTH_PARAM_POS    3
#define AT_PARSE_FIFTH_PARAM_POS     4
#define AT_PARSE_SIXTH_PARAM_POS     5
#define AT_PARSE_SEVENTH_PARAM_POS   6
#define AT_PARSE_EIGHTH_PARAM_POS    7
#define AT_PARSE_NINTH_PARAM_POS     8
#define AT_PARSE_TENTH_PARAM_POS     9
#define AT_PARSE_ELEVENTH_PARAM_POS  10
#define AT_PARSE_TWELFTH_PARAM_POS   11


#define AT_UINT8_NO_VALUE          MAX_UINT8
#define AT_UINT16_NO_VALUE         MAX_UINT16
#define AT_INT16_NO_VALUE          MAX_INT16
#define AT_INT32_NO_VALUE          MAX_UINT32

/**
 * @brief Get the string lenth of a comand
 * @param p_str The address of the string
 * @return The lenth of p_str
 */
uint16 at_get_cmd_length(const uint8 *p_str);

/** Convert bufffer to hexadecimal format string use forward order
 * @param source_buf The buffer to convert
 * @param dest_buf_hex The buffer to save converted data
 * @param source_length The length of source buffer
 * @return true or false
 */
bool at_parse_buf_to_hex_forward_order(const uint8* source_buf, uint8* dest_buf_hex, uint16 source_length);

/** Convert bufffer to hexadecimal format string use reversed order
 * @param buffer The buffer to convert
 * @param length The length of the buffer, must be even number
 * @return true or false
 */
bool at_parse_buf_to_hex_reversed_order(uint8* buffer, uint16 length);

/** Parse string buffer, translate hexadecimal format string to uint8, the source_buf_hex and dest_buf can be same to save memory use.
 * @param source_buf_hex The hexadecimal format string buffer to parse.
 * @param dest_buf The buffer to store result
 * @param source_length The length of source_buf_hex, source_length must be even number. dest_length = source_length/2
 * @return pointer of at callback struture.
 */
bool at_parse_buf_hex_to_uint8(const uint8* source_buf_hex, uint8* dest_buf, uint16 source_length);

/** Parse string buffer, translate hexadecimal format string to uint16.
 * @param source_buf_hex The hexadecimal format string buffer to parse.
 * @param dest_value The buffer to store result
 * @param source_length The length of source_buf_hex
 * @return true or false
 */
bool at_parse_buf_hex_to_uint16(const uint8* source_buf_hex, uint16 *dest_value, uint16 source_length);

/** Parse string buffer, translate hexadecimal format string to uint64.
 * @param source_buf_hex The hexadecimal format string buffer to parse.
 * @param dest_value The buffer to store result
 * @param source_length The length of source_buf_hex
 * @return true or false
 */
bool at_parse_buf_hex_to_uint64(const uint8* source_buf_hex, uint64 *dest_value, uint16 source_length);

/** Output string buffer in hexadecimal sting format through at uart.
 * @param message The stored string to output in hexadecimal format string.
 * @param length The lenght of message
 * @return true or false.
 */
bool at_output_buf_in_hex(const uint8 *message, uint32 length);

/** Convert neul result to at result.
 * @param result The neul result.
 * @return AT_RET The at result.
 */
AT_RET at_parse_convert_neul_result(NEUL_RET result);

/** Convert at result to sms result.
 * @param result The at result.
 * @return AT_RET The sms result.
 */
AT_RET at_parse_convert_sms_result(AT_RET result);

/** Create at parameter array.
 * @param p_atparams_string The buffer to store at string
 * @param p_param_num The number of at parameters
 * @param param_minnum The min number of at parameters
 * @param param_maxnum The max number of at parameters 
 * @return AT_RET The result of create at parameter array.
 */
AT_RET at_create_param_array(uint8 *p_atparams_string, uint8 *p_param_num, uint8 param_minnum, uint8 param_maxnum);

/** Free at parameter array.
 * @return none
 */
void at_free_at_params(void);

/** Get uint16 parameter.
 * @param seqno The sequence number of at parameter
 * @param p_uint16 The address to store at parameter
 * @param mandatory The at parameter is mandatory or not
 * @return AT_RET The result of Get at parameter.
 */
AT_RET at_get_uint16_param(uint8 seqno, uint16 *p_uint16, bool mandatory);

/** Get uint8 parameter.
 * @param seqno The sequence number of at parameter
 * @param p_uint8 The address to store at parameter
 * @param mandatory The at parameter is mandatory or not
 * @return AT_RET The result of Get at parameter.
 */
AT_RET at_get_uint8_param(uint8 seqno, uint8 *p_uint8, bool mandatory);

/** Get int16 parameter.
 * @param seqno The sequence number of at parameter
 * @param p_int16 The table to store at parameter
 * @param mandatory The at parameter is mandatory or not
 * @return AT_RET The result of Get at parameter.
 */
AT_RET at_get_int16_param(uint8 seqno, int16 *p_int16, bool mandatory);

/** Get uint16 parameter from a one decimal place real number.
 * @param seqno The sequence number of at parameter
 * @param p_uint16 The address to store at parameter
 * @param mandatory The at parameter is mandatory or not
 * @return AT_RET The result of Get at parameter.
 */
AT_RET at_get_1dp_to_int16_param(uint8 seqno, int16 *p_int16, bool mandatory);

/** Get uint32 parameter.
 * @param seqno The sequence number of at parameter
 * @param p_uint32 The address to store at parameter
 * @param mandatory The at parameter is mandatory or not
 * @return AT_RET The result of Get at parameter.
 */
AT_RET at_get_uint32_param(uint8 seqno, uint32 *p_uint32, bool mandatory);

/** Check if string contain hex prefix 0x/0X or not.
 * @param p_string The string to the check
 * @param str_len The length  of at string
 * @return true or false.
 */
bool at_check_hex_string_prefix(const uint8 *p_string, uint16 str_len);

/** Get string parameter.
 * @param seqno The sequence number of at parameter
 * @param p_string The buffer to store string parameter
 * @param max_len The lenght of p_string
 * @param mandatory The at parameter is mandatory or not
 * @return AT_RET The result of Get at parameter.
 */
AT_RET at_get_string_param(uint8 seqno, uint8 *p_string, uint16 max_len, bool mandatory);

/** Get Hexadecimal format string parameter.
 * @param seqno The sequence number of at parameter
 * @param p_hexstring The buffer pointer of  Hexadecimal format string parameter
 * @param p_hexstring_len The lenght of p_hexstring
 * @param mandatory The at parameter is mandatory or not
 * @return AT_RET The result of Get at parameter.
 */
AT_RET at_get_hexstring_param(uint8 seqno, uint8 **p_hexstring, uint16 *p_hexstring_len, bool mandatory);

/** Get ip parameter.
 * @param seqno The sequence number of at parameter
 * @param p_ip The buffer to store ip parameter
 * @param max_len The lenght of p_ip
 * @param mandatory The at parameter is mandatory or not
 * @param server_addr store changed address
 * @return AT_RET The result of Get at parameter.
 */
AT_RET at_get_ip_param(uint8 seqno, uint8 *p_ip, uint16 max_len, bool mandatory, ip_addr_t *server_addr);

/** query param is in double quotes or not
 * @param position The param position
 * @return true or false.
 */
bool at_is_param_in_double_quotes(uint8 position);

/** Get at callback struture
 * @param p_atstring The buffer to store at string
 * @param len The length of at string
 * @return pointer of at callback struture.
 */
const AT_CMD_CB_s * at_get_atcmd_cb_from_atstring(uint8 *p_atstring, uint16 *len);

/** Calculate crc8
 * @param data data buffer
 * @param len  data length
 * @param crc  crc calculate result
 * @return AT_RET AT_RET_OK, AT_RET_SYNTAX_ERROR
 */
AT_RET at_parse_calculate_crc8(const uint8* data, uint16 len, uint8* crc);

/** parse nrdexec parmter
 * @param num_subcarrier Number of subcarriers
 * @param subcarrier_index Position of subcarrie
 * @return AT_RET AT_RET_OK, AT_RET_SYNTAX_ERROR
 */
AT_RET at_check_num_sc_for_sc_index(uint16 num_subcarrier, uint16 subcarrier_index);

/** check parse time string to time (yy/MM/dd,hh:mm:ss+zz)
 * @param time_str time string to parse
 * @param current_time current time in second
 * @param time_zone time zone
 * @return AT_RET
 */
AT_RET at_get_tm_param(uint8 seqno, struct tm *time_struct, int8 *time_zone, bool mandatory);

/** @} end of group libNEUL_APP_AT_MOD_API */

#endif
