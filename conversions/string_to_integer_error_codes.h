#ifndef STRING_TO_INTEGER_ERROR_CODES_H
#define STRING_TO_INTEGER_ERROR_CODES_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Error codes for string-to-integer conversion */
typedef enum string_to_int_error_type {
	string_to_int_error_unknown = -1,
	string_to_int_error_none = 0,
	string_to_int_error_null_string,
	string_to_int_error_zero_length,
	string_to_int_error_empty_string,
	string_to_int_error_invalid_base,
	string_to_int_error_unsupported_base,
	string_to_int_error_only_whitespaces,
	string_to_int_error_incomplete_string,
	string_to_int_error_invalid_character,
	string_to_int_error_invalid_prefix,
	string_to_int_error_whitespace_after_sign,
	string_to_int_error_digit_not_supported_by_base,
	string_to_int_error_invalid_trailing_character,
	string_to_int_error_value_smaller_than_minimum_signed_value,
	string_to_int_error_value_greater_than_maximum_signed_value,
	string_to_int_error_value_smaller_than_minimum_unsigned_value,
	string_to_int_error_value_greater_than_maximum_unsigned_value
} string_to_int_error_type;

#ifdef __cplusplus
}
#endif

#endif
