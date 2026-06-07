#include "string_to_integer.h"
#include "char_utils.h"
#include "string_info_type.h"
#include "safer_fixed_width_integers.h"
#include "string_reference.h"
#include "sizeof_array.h"
#include <assert.h>
#include <iso646.h>

static string_to_int_error_type integer_operation_error_to_string_to_int_error(integer_operation_error_type integer_op_error)
{
	string_to_int_error_type error = string_to_int_error_none;
	switch (integer_op_error) {
	case integer_operation_error_none:
		error = string_to_int_error_none;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		error = string_to_int_error_value_smaller_than_minimum_signed_value;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		error = string_to_int_error_value_greater_than_maximum_signed_value;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		error = string_to_int_error_value_greater_than_maximum_unsigned_value;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger:
		error = string_to_int_error_value_smaller_than_minimum_unsigned_value;
		break;
	default:
		error = string_to_int_error_unknown;
		break;
	}
	return error;
}

const char *string_to_int_error_message(string_to_int_error_type error)
{
	const char *message = NULL;
	switch (error) {
	case string_to_int_error_none:
		message = "No error.";
		break;
	case string_to_int_error_null_string:
		message = "The string is null.";
		break;
	case string_to_int_error_zero_length:
		message = "The string has zero length.";
		break;
	case string_to_int_error_empty_string:
		message = "The string is empty.";
		break;
	case string_to_int_error_invalid_base:
		message = "The number base is invalid.";
		break;
	case string_to_int_error_unsupported_base:
		message = "The number base is not supported.";
		break;
	case string_to_int_error_only_whitespaces:
		message = "The string contains only whitespaces.";
		break;
	case string_to_int_error_incomplete_string:
		message = "The string is incomplete.";
		break;
	case string_to_int_error_invalid_character:
		message = "An invalid character is found.";
		break;
	case string_to_int_error_invalid_prefix:
		message = "The prefix is invalid.";
		break;
	case string_to_int_error_whitespace_after_sign:
		message = "There is a whitespace after the sign.";
		break;
	case string_to_int_error_digit_not_supported_by_base:
		message = "A digit which is not supported by the number base is found.";
		break;
	case string_to_int_error_invalid_trailing_character:
		message = "An invalid trailing character is found.";
		break;
	case string_to_int_error_value_smaller_than_minimum_signed_value:
		message = "The integer value in the string is lower than the minimum of the signed integer.";
		break;
	case string_to_int_error_value_greater_than_maximum_signed_value:
		message = "The integer value in the string is higher than the maximum of the signed integer.";
		break;
	case string_to_int_error_value_smaller_than_minimum_unsigned_value:
		message = "The integer value in the string is lower than the minimum of the unsigned integer.";
		break;
	case string_to_int_error_value_greater_than_maximum_unsigned_value:
		message = "The integer value in the string is higher than the maximum of the unsigned integer.";
		break;
	default:
		message = "Unknown error.";
		break;
	}
	assert(message != NULL);
	return message;
}

string_to_i32_result_type string_to_i32(const char *string, size_t length, int base)
{
	string_to_i32_result_type result = {0};
	int_string_info_type info = string_to_int_get_string_info(string, length, base);

	if (info.error == string_to_int_error_none and not info.contains_valid_integer) {
		result.error = string_to_int_error_incomplete_string;
	} else {
		result.error = info.error;
	}

	if (info.contains_valid_integer) {
		size_t index = 0U;
		if (not info.integer_is_negative) {
			const int32_t limit = INT32_MAX / (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const int32_t digit_value = digit_to_integer(info.string[index]);
				if (result.value < limit) {
					result.value *= base;
				} else {
					const i32_result_type r = safer_i32_multiply(result.value, base);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (result.value < limit) {
					result.value += digit_value;
				} else {
					const i32_result_type r = safer_i32_add(result.value, digit_value);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		} else {
			const int32_t limit = INT32_MIN / (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const int32_t digit_value = digit_to_integer(info.string[index]);
				if (result.value > limit) {
					result.value *= base;
				} else {
					const i32_result_type r = safer_i32_multiply(result.value, base);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (result.value > limit) {
					result.value -= digit_value;
				} else {
					const i32_result_type r = safer_i32_minus(result.value, digit_value);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		}
	}

	return result;
}

string_to_i32_result_type i32string_to_i32_(const i32string_type *p_i32string, int base)
{
	size_t length = 0U;
	const_stringref_type conststrref = string_to_const_stringref(p_i32string->content, sizeof_array(p_i32string->content));
	length = const_stringref_string_length(conststrref);
	return string_to_i32(conststrref.string, length, base);
}


string_to_u32_result_type string_to_u32(const char *string, size_t length, int base)
{
	string_to_u32_result_type result = {0};
	int_string_info_type info = string_to_int_get_string_info(string, length, base);

	if (info.error == string_to_int_error_none and not info.contains_valid_integer) {
		result.error = string_to_int_error_incomplete_string;
	} else {
		result.error = info.error;
	}

	if (info.contains_valid_integer) {
		size_t index = 0U;
		if (not info.integer_is_negative) {
			const uint32_t limit = UINT32_MAX / (uint32_t) (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const uint32_t digit_value = (uint32_t) digit_to_integer(info.string[index]);
				if (result.value < limit) {
					result.value *= (uint32_t) base;
				} else {
					const u32_result_type r = safer_u32_multiply(result.value, (uint32_t) base);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (result.value < limit) {
					result.value += digit_value;
				} else {
					const u32_result_type r = safer_u32_add(result.value, digit_value);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		} else {
			result.value = 0U;
			result.error = string_to_int_error_value_smaller_than_minimum_unsigned_value;
		}
	}

	return result;
}

string_to_u32_result_type u32string_to_u32_(const u32string_type *p_u32string, int base)
{
	size_t length = 0U;
	const_stringref_type conststrref = string_to_const_stringref(p_u32string->content, sizeof_array(p_u32string->content));
	length = const_stringref_string_length(conststrref);
	return string_to_u32(conststrref.string, length, base);
}

string_to_i64_result_type string_to_i64(const char *string, size_t length, int base)
{
	string_to_i64_result_type result = {0};
	int_string_info_type info = string_to_int_get_string_info(string, length, base);

	if (info.error == string_to_int_error_none and not info.contains_valid_integer) {
		result.error = string_to_int_error_incomplete_string;
	} else {
		result.error = info.error;
	}

	if (info.contains_valid_integer) {
		size_t index = 0U;
		if (not info.integer_is_negative) {
			const int64_t limit = INT64_MAX / (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const int64_t digit_value = digit_to_integer(info.string[index]);
				if (result.value < limit) {
					result.value *= base;
				} else {
					const i64_result_type r = safer_i64_multiply(result.value, base);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (result.value < limit) {
					result.value += digit_value;
				} else {
					const i64_result_type r = safer_i64_add(result.value, digit_value);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		} else {
			const int64_t limit = INT64_MIN / (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const int64_t digit_value = digit_to_integer(info.string[index]);
				if (result.value > limit) {
					result.value *= base;
				} else {
					const i64_result_type r = safer_i64_multiply(result.value, base);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (result.value > limit) {
					result.value -= digit_value;
				} else {
					const i64_result_type r = safer_i64_minus(result.value, digit_value);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		}
	}

	return result;
}

string_to_i64_result_type i64string_to_i64_(const i64string_type *p_i64string, int base)
{
	size_t length = 0U;
	const_stringref_type conststrref = string_to_const_stringref(p_i64string->content, sizeof_array(p_i64string->content));
	length = const_stringref_string_length(conststrref);
	return string_to_i64(conststrref.string, length, base);
}

string_to_u64_result_type string_to_u64(const char *string, size_t length, int base)
{
	string_to_u64_result_type result = {0};
	int_string_info_type info = string_to_int_get_string_info(string, length, base);

	if (info.error == string_to_int_error_none and not info.contains_valid_integer) {
		result.error = string_to_int_error_incomplete_string;
	} else {
		result.error = info.error;
	}

	if (info.contains_valid_integer) {
		size_t index = 0U;
		if (not info.integer_is_negative) {
			const uint64_t limit = UINT64_MAX / (uint64_t) (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const uint64_t digit_value = (uint64_t) digit_to_integer(info.string[index]);
				if (result.value < limit) {
					result.value *= (uint64_t) base;
				} else {
					const u64_result_type r = safer_u64_multiply(result.value, (uint64_t) base);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (result.value < limit) {
					result.value += digit_value;
				} else {
					const u64_result_type r = safer_u64_add(result.value, digit_value);
					result.value = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		} else {
			result.value = 0U;
			result.error = string_to_int_error_value_smaller_than_minimum_unsigned_value;
		}
	}

	return result;
}

string_to_u64_result_type u64string_to_u64_(const u64string_type *p_u64string, int base)
{
	size_t length = 0U;
	const_stringref_type conststrref = string_to_const_stringref(p_u64string->content, sizeof_array(p_u64string->content));
	length = const_stringref_string_length(conststrref);
	return string_to_u64(conststrref.string, length, base);
}
