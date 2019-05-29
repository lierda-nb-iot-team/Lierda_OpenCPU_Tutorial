/**
 * @file neul_string.h
 * @brief Exported Neul string functions
 */


#ifndef NEUL_STRING_H_
#define NEUL_STRING_H_

#include "neulfw.h"

/** @defgroup libNEUL_STRING Hi21XX libNEUL Utilities
 * Hi21XX libNeul Utilities
 * @ingroup LIBNEUL
 * @{
 * */

/**Initialise the neul_string module*/
void neul_string_init(void);

/**De-initialise the neul_string module*/
void neul_string_deinit(void);

/**Get a hex character from a nibble
 * @param nibble is the 0 to 15 number to be converted into a hex character
 * @param upper is true if an upper case characetr is wanted, otherwise a lower case character is created
 * @return the hex character
 */
char neul_string_nibble_to_hex_digit(uint8 nibble, bool upper);

/**Make sure the provided character is in upper case
 * @param next_char is the character to change into upper case
 * @return the uppercase character or the same as the input if there is no uppercase version of this character
 */
char neul_string_to_upper(const char next_char);

/**Determine if the provided character is a letter
 * @param next_char is the character to examine
 * @return true if next_char is a-z or A-Z
 */
bool neul_string_is_letter(const char next_char);

/**Determine if the provided character is a decimal digit
 * @param next_char is the character to examine
 * @return true if next_char is 0-9
 */
bool neul_string_is_decimal_digit(const char next_char);

/**Get the value of a decimal digit
 * @param next_char is the character to examine
 * @return the value 0-9
 * @note The provided character must have already been determined to be a decimal digit
 */
uint8 neul_string_get_decimal_digit_value(const char next_char);

/**Determine if the provided character is a hex digit
 * @param next_char is the character to examine
 * @return true if next_char is 0-9, a-f or A-F
 */
bool neul_string_is_hex_digit(const char next_char);

/**Get the value of a hex digit
 * @param next_char is the character to examine
 * @return the value 0-15
 * @note The provided character must have already been determined to be a hex digit
 */
uint8 neul_string_get_hex_digit_value(const char next_char);

/**Get the text length of a uint32 value
 * @param value is the value whose text length is desired
 * @return the number of text characters required
 */
uint8 neul_string_get_decimal_length_uint32(uint32 value);

/**Write a decimal uint32 value into a character buffer
 * @param buff is the buffer to write into
 * @param value is the uint32 value
 * @param max_chars is the maximum number of chars that can be written into the buffer
 * @return the number of characters written (or zero if insufficient characters)
 */
uint8 neul_string_write_decimal_uint32(char *buff, uint32 value, uint8 max_chars);

/**Write a decimal int32 value into a character buffer, including the minus sign
 * @param buff is the buffer to write into
 * @param value is the int32 value
 * @param max_chars is the maximum number of chars that can be written into the buffer
 * @return the number of characters written (or zero if insufficient characters)
 */
uint8 neul_string_write_decimal_int32(char *buff, int32 value, uint8 max_chars);

/**Write a hex value into a character buffer with a
 * @param buff is the buffer to write into
 * @param value is the uint32 value
 * @param chars is the specified number of hex chars (zero padded) to be written into the buffer; maximum of 8
 * @return the number of characters written (or zero if too many chars are specified)
 */
uint8 neul_string_write_hex_uint32(char *buff, uint32 value, uint8 chars, bool upper);

/**
 * Convert packed BCD to a string
 * @param out pointer to output buffer at least (b_len + 1) long. The returned buffer is a null terminated string.
 * @param in input array in BCD format
 * @param b_len number of bytes to convert (maximum length of in array * 2
 * @return number of binary characters converted.
 */
int neul_string_convert_BCD_to_str(char *out, const uint8 *in, uint16 b_len);

/**
 * Convert a string to packed BCD
 * tell it number of binary data items expected, convert string and get that number of bytes back
 * will zero fill trailing nibble if needed.
 * @param bin_data pointer to output buffer at least (bin_len + 1)/2 long
 * @param str_data the input buffer containing ascii decimal digits
 * @param bin_len  the number of characters in the input buffer
 * @return number of binary characters converted.
 */
int neul_string_convert_str_to_BCD(uint8 *bin_data, const char *str_data, uint16 bin_len);

/**
 * Covert a uint8 array to uint32 value
 * @param array pointer to the uint8 array which the lowest address is the highest bits of converted value
 * @param len the length of uint8 array
 * @param result the coverted uint32 value
 * @return true if all the arguments are OK or false otherwise
 */
bool neul_string_convert_uint8_array_to_uint32(const uint8* array, uint32 len, uint32 *result);

/** @} end of group libNEUL_STRING */



#endif //NEUL_STRING_H_
