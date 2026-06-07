#include "char_utils.h"
#include "string_info_type.h"
#include "inline_or_static.h"
#include <assert.h>
#include <iso646.h>

INLINE_OR_STATIC size_t index_of_first_non_whitespace_character(const char *string, size_t length)
{
	size_t index = 0U;
	assert(string != NULL);
	assert(length > 0U);
	for (; index < length; ++index) {
		const char ch = string[index];
		if (character_is_whitespace(ch)) {
			continue;
		}
		break;
	}
	assert(index <= length);
	return index;
}

/* internal state */
typedef enum string_parsing_state_type {
	string_parsing_state_start = 0,
	string_parsing_state_leading_whitespaces,
	string_parsing_state_sign,
	string_parsing_state_whitespace_after_sign,
	string_parsing_state_prefix,
	string_parsing_state_invalid_prefix,
	string_parsing_state_digits,
	string_parsing_state_digit_not_supported_by_base,
	string_parsing_state_trailing_whitespaces,
	string_parsing_state_invalid_character,
	string_parsing_state_trailing_invalid_character
} string_parsing_state_type;

int_string_info_type string_to_int_get_string_info(const char *string, size_t length, int base)
{
	int_string_info_type info = {0};
	size_t index = 0U;
	string_parsing_state_type state = string_parsing_state_start;
	bool should_terminate_early = false;
	bool is_leading_zero = true;
	info.string = string;
	info.length = length;
	info.base = base;
	info.start_index = 0U;
	info.end_index = info.start_index;
	info.error = string_to_int_error_none;
	info.contains_valid_integer = false;
	info.integer_is_negative = false;

	if (string == NULL) {
		info.error = string_to_int_error_null_string;
	} else if (length == 0U) {
		info.error = string_to_int_error_zero_length;
	} else if (string[0] == '\0') {
		info.error = string_to_int_error_empty_string;
	} else if (base < 2) {
		info.error = string_to_int_error_invalid_base;
	} else if (base > 36) {
		info.error = string_to_int_error_unsupported_base;
	} else {
		index = index_of_first_non_whitespace_character(string, length);
		if (index >= length or string[index] == '\0') {
			info.error = string_to_int_error_only_whitespaces;
		}
		info.start_index = index;
		info.end_index = info.start_index;
		state = string_parsing_state_leading_whitespaces;
	}

	if (info.error != string_to_int_error_none) {
		return info;
	}

	for (; index < length; ++index) {
		const char ch = string[index];
		switch (state) {
		case string_parsing_state_start:
		case string_parsing_state_leading_whitespaces: /* fall through intended */
			assert(ch != '\0');
			if (ch == '-' or ch == '+') {
				state = string_parsing_state_sign;
				info.integer_is_negative = ch == '-';
			} else if (ch == '0' and index + 1U < length) {
				state = string_parsing_state_prefix;
			} else if (not character_is_valid_digit(ch)) {
				state = string_parsing_state_invalid_character;
				info.error = string_to_int_error_invalid_character;
			} else if (digit_is_supported_by_base(ch, base)) {
				state = string_parsing_state_digits;
				is_leading_zero = (ch == '0');
				info.contains_valid_integer = true;
				info.end_index = info.start_index = index;
			} else {
				state = string_parsing_state_digit_not_supported_by_base;
				info.error = string_to_int_error_digit_not_supported_by_base;
			}
			break;
		case string_parsing_state_sign:
			if (ch == '\0') {
				should_terminate_early = true;
				info.error = string_to_int_error_incomplete_string;
			} else if (ch == '0' and index + 1U < length) {
				state = string_parsing_state_prefix;
			} else if (character_is_whitespace(ch)) {
				state = string_parsing_state_whitespace_after_sign;
				info.error = string_to_int_error_whitespace_after_sign;
			} else if (not character_is_valid_digit(ch)) {
				state = string_parsing_state_invalid_character;
				info.error = string_to_int_error_invalid_character;
			} else if (digit_is_supported_by_base(ch, base)) {
				state = string_parsing_state_digits;
				if (is_leading_zero and ch != '0') {
					is_leading_zero = false;
				}
				info.contains_valid_integer = true;
				info.end_index = info.start_index = index;
			} else {
				state = string_parsing_state_digit_not_supported_by_base;
				info.error = string_to_int_error_digit_not_supported_by_base;
			}
			break;
		case string_parsing_state_prefix:
			assert(index > 0U);
			if (ch == '\0') {
				should_terminate_early = true;
				info.error = string_to_int_error_incomplete_string;
			} else if (base == 2) {
				if (character_is_binary_digit(ch)) {
					state = string_parsing_state_digits;
					is_leading_zero = (ch == '0');
					info.contains_valid_integer = true;
					info.end_index = info.start_index = index;
				} else if (ch == 'B' or ch == 'b') {
					state = string_parsing_state_digits;
					info.contains_valid_integer = (index + 1U < length) and digit_is_supported_by_base(string[index + 1U], base);
					info.start_index = (index + 1U < length) ? (index + 1U) : index;
					info.end_index = info.start_index;
				} else {
					state = string_parsing_state_invalid_prefix;
					info.error = string_to_int_error_invalid_prefix;
				}
			} else if (base == 16) {
				if (character_is_hexadecimal_digit(ch)) {
					state = string_parsing_state_digits;
					is_leading_zero = (ch == '0');
					info.contains_valid_integer = true;
					info.end_index = info.start_index = index;
				} else if (ch == 'X' or ch == 'x') {
					state = string_parsing_state_digits;
					info.contains_valid_integer = (index + 1U < length) and digit_is_supported_by_base(string[index + 1U], base);
					info.start_index = (index + 1U < length) ? (index + 1U) : index;
					info.end_index = info.start_index;
				} else {
					state = string_parsing_state_invalid_prefix;
					info.error = string_to_int_error_invalid_prefix;
				}
			} else if (not character_is_valid_digit(ch)) {
				state = string_parsing_state_invalid_character;
				info.error = string_to_int_error_invalid_character;
			} else if (digit_is_supported_by_base(ch, base)) {
				state = string_parsing_state_digits;
				is_leading_zero = (ch == '0');
				info.contains_valid_integer = true;
				info.end_index = info.start_index = index;
			} else {
				state = string_parsing_state_digit_not_supported_by_base;
				info.error = string_to_int_error_digit_not_supported_by_base;
			}
			break;
		case string_parsing_state_digits:
			if (ch == '\0') {
				should_terminate_early = true;
			} else if (character_is_whitespace(ch)) {
				state = string_parsing_state_trailing_whitespaces;
			} else if (not character_is_valid_digit(ch)) {
				state = string_parsing_state_trailing_invalid_character;
				info.error = string_to_int_error_invalid_trailing_character;
			} else if (digit_is_supported_by_base(ch, base)) {
				state = string_parsing_state_digits;
				if (is_leading_zero) {
					is_leading_zero = (ch == '0');
					info.start_index = index;
				}
				info.end_index = index;
			} else {
				state = string_parsing_state_digit_not_supported_by_base;
				info.error = string_to_int_error_digit_not_supported_by_base;
			}
			break;
		case string_parsing_state_trailing_whitespaces:
			if (ch == '\0') {
				should_terminate_early = true;
			} else if (not character_is_whitespace(ch)) {
				state = string_parsing_state_trailing_invalid_character;
				info.error = string_to_int_error_invalid_trailing_character;
			}
			break;
		default:
			break;
		}

		if (should_terminate_early or info.error != string_to_int_error_none) {
			break;
		}
	}

	assert(info.string == string);
	assert(info.length == length);
	assert(info.base == base);
	assert(info.start_index <= info.end_index);
	assert(info.end_index < length);
	return info;
}
