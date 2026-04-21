#ifndef STRING_TO_INTEGER_H
#define STRING_TO_INTEGER_H

#include "integer_to_string.h"

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

/** @brief string to 32-bit signed integer result */
typedef struct string_to_i32_result_type {
	int32_t value;
	string_to_int_error_type error;
} string_to_i32_result_type;

/** @brief string to 32-bit unsigned integer result */
typedef struct string_to_u32_result_type {
	uint32_t value;
	string_to_int_error_type error;
} string_to_u32_result_type;

/** @brief string to 64-bit signed integer result */
typedef struct string_to_i64_result_type {
	int64_t value;
	string_to_int_error_type error;
} string_to_i64_result_type;

/** @brief string to 64-bit unsigned integer result */
typedef struct string_to_u64_result_type {
	uint64_t value;
	string_to_int_error_type error;
} string_to_u64_result_type;

/**
 * @brief Converts an error code to an error message
 * @param [in] error Error code
 * @return const char * Read-only error message
 */
const char *string_to_int_error_message(string_to_int_error_type error);

/**
 * @brief Converts a string to a 32-bit signed integer
 * @param [in] string Pointer to the first character
 * @param [in] length Number of characters
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_i32_result_type
 */
string_to_i32_result_type string_to_i32(const char *string, size_t length, int base);

/**
 * @brief Converts an i32string to a 32-bit signed integer
 * @param [in] p_i32string Pointer to an instance of i32string_type (MUST NOT be NULL)
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_i32_result_type
 */
string_to_i32_result_type i32string_to_i32_(const i32string_type *p_i32string, int base);

/**
 * @brief Macro to convert an i32string to a 32-bit signed integer
 * @param [in] i32string An instance of i32string_type (NOT a pointer)
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_i32_result_type
 */
#define i32string_to_i32(i32string, base) i32string_to_i32_(&(i32string), base)

/**
 * @brief Converts a string to a 32-bit unsigned integer
 * @param [in] string Pointer to the first character
 * @param [in] length Number of characters
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_u32_result_type
 */
string_to_u32_result_type string_to_u32(const char *string, size_t length, int base);

/**
 * @brief Converts a u32string to a 32-bit unsigned integer
 * @param [in] p_u32string Pointer to an instance of u32string_type (MUST NOT be NULL)
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_u32_result_type
 */
string_to_u32_result_type u32string_to_u32_(const u32string_type *p_u32string, int base);

/**
 * @brief Macro to convert a u32string to a 32-bit unsigned integer
 * @param [in] u32string An instance of u32string_type (NOT a pointer)
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_u32_result_type
 */
#define u32string_to_u32(u32string, base) u32string_to_u32_(&(u32string), base)

/**
 * @brief Converts a string to a 64-bit signed integer
 * @param [in] string Pointer to the first character
 * @param [in] length Number of characters
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_i64_result_type
 */
string_to_i64_result_type string_to_i64(const char *string, size_t length, int base);

/**
 * @brief Converts an i64string to a 64-bit signed integer
 * @param [in] p_i64string Pointer to an instance of i64string_type (MUST NOT be NULL)
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_i64_result_type
 */
string_to_i64_result_type i64string_to_i64_(const i64string_type *p_i64string, int base);

/**
 * @brief Macro to convert an i64string to a 64-bit signed integer
 * @param [in] i64string An instance of i64string_type (NOT a pointer)
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_i64_result_type
 */
#define i64string_to_i64(i64string, base) i64string_to_i64_(&(i64string), base)

/**
 * @brief Converts a string to a 64-bit unsigned integer
 * @param [in] string Pointer to the first character
 * @param [in] length Number of characters
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_u64_result_type
 */
string_to_u64_result_type string_to_u64(const char *string, size_t length, int base);

/**
 * @brief Converts a u64string to a 64-bit unsigned integer
 * @param [in] p_u64string Pointer to an instance of u64string_type (MUST NOT be NULL)
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_i64_result_type
 */
string_to_u64_result_type u64string_to_u64_(const u64string_type *p_u64string, int base);

/**
 * @brief Macro to convert a u64string to a 64-bit unsigned integer
 * @param [in] u64string An instance of u64string_type (NOT a pointer)
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @return string_to_i64_result_type
 */
#define u64string_to_u64(u64string, base) u64string_to_u64_(&(u64string), base)

#ifdef __cplusplus
}
#endif

#endif
