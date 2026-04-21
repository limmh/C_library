#ifndef INTEGER_TO_STRING_H
#define INTEGER_TO_STRING_H

#include "fixed_width_integer_types.h"
#include "inline_or_static.h"
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Options for integer-to-string conversion */
typedef enum int_to_string_option_type {
	int_to_string_option_default = 0,
	/*-------------------------------*/
	int_to_string_option_lowercase = 0, /* uses a to z for number bases greater than 10 */
	int_to_string_option_uppercase = 1, /* uses A to Z for number bases greater than 10 */
	/*-------------------------------*/
	int_to_string_option_add_prefix = 2, /* adds 0 in front of an octal integer, 0x in front of a hexadecimal integer, or 0b in front of a binary integer */
	/*-------------------------------*/
	int_to_string_option_add_plus_sign = 4 /* adds + in front of positive integers */
} int_to_string_option_type;

/** @brief string type representing int32_t */
typedef struct i32string_type {
	char content[(sizeof(int32_t) * CHAR_BIT) + 4U]; /* includes prefix (optional), plus (optional) or minus sign and NUL */
} i32string_type;

/** @brief string type representing uint32_t */
typedef struct u32string_type {
	char content[(sizeof(uint32_t) * CHAR_BIT) + 4U]; /* includes prefix (optional), plus sign (optional) and NUL */
} u32string_type;

/** @brief string type representing int64_t */
typedef struct i64string_type {
	char content[(sizeof(int64_t) * CHAR_BIT) + 4U]; /* includes prefix (optional), plus (optional) or minus sign and NUL */
} i64string_type;

/** @brief string type representing uint64_t */
typedef struct u64string_type {
	char content[(sizeof(uint64_t) * CHAR_BIT) + 4U]; /* includes prefix (optional), plus sign (optional) and NUL */
} u64string_type;

/* The string content returned by each conversion function is always null-terminated. */

/**
 * @brief Converts a 32-bit signed integer to string
 * @param [in] value Integer
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @param [in] options Conversion options
 * @return i32string_type
 */
i32string_type i32_to_i32string(int32_t value, int base, int_to_string_option_type options);

/**
 * @brief Converts a 32-bit unsigned integer to string
 * @param [in] value Integer
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @param [in] options Conversion options
 * @return u32string_type
 */
u32string_type u32_to_u32string(uint32_t value, int base, int_to_string_option_type options);

/**
 * @brief Converts a 64-bit signed integer to string
 * @param [in] value Integer
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @param [in] options Conversion options
 * @return i64string_type
 */
i64string_type i64_to_i64string(int64_t value, int base, int_to_string_option_type options);

/**
 * @brief Converts a 64-bit unsigned integer to string
 * @param [in] value Integer
 * @param [in] base Number base (minimum: 2, maximum: 36)
 * @param [in] options Conversion options
 * @return u64string_type
 */
u64string_type u64_to_u64string(uint64_t value, int base, int_to_string_option_type options);

/* i32_to_i32string variants for bases 2, 8, 10 and 16 */
/** @brief Converts a 32-bit signed integer to string in binary format */
INLINE_OR_STATIC i32string_type base2_i32_to_i32string(int32_t value) {
	return i32_to_i32string(value, 2, int_to_string_option_default);
}

/** @brief Converts a 32-bit signed integer to string in binary format with 0b prefix */
INLINE_OR_STATIC i32string_type base2_i32_to_i32string_with_prefix(int32_t value) {
	return i32_to_i32string(value, 2, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 32-bit signed integer to string in binary format with 0B prefix */
INLINE_OR_STATIC i32string_type base2_i32_to_i32string_with_prefix_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 2, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 32-bit signed integer to string in octal format */
INLINE_OR_STATIC i32string_type base8_i32_to_i32string(int32_t value) {
	return i32_to_i32string(value, 8, int_to_string_option_default);
}

/** @brief Converts a 32-bit signed integer to string in octal format with prefix (prefix: 0) */
INLINE_OR_STATIC i32string_type base8_i32_to_i32string_with_prefix(int32_t value) {
	return i32_to_i32string(value, 8, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 32-bit signed integer to string in decimal format */
INLINE_OR_STATIC i32string_type base10_i32_to_i32string(int32_t value) {
	return i32_to_i32string(value, 10, int_to_string_option_default);
}

/** @brief Converts a 32-bit signed integer to string in hexadecimal format */
INLINE_OR_STATIC i32string_type base16_i32_to_i32string(int32_t value) {
	return i32_to_i32string(value, 16, int_to_string_option_default);
}

/** @brief Converts a 32-bit signed integer to string in hexadecimal format with uppercase A to F */
INLINE_OR_STATIC i32string_type base16_i32_to_i32string_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 16, int_to_string_option_uppercase);
}

/** @brief Converts a 32-bit signed integer to string in hexadecimal format with 0x prefix */
INLINE_OR_STATIC i32string_type base16_i32_to_i32string_with_prefix(int32_t value) {
	return i32_to_i32string(value, 16, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 32-bit signed integer to string in hexadecimal format with 0X prefix and uppercase A to F */
INLINE_OR_STATIC i32string_type base16_i32_to_i32string_with_prefix_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 16, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

/* u32_to_u32string variants for bases 2, 8, 10 and 16 */
/** @brief Converts a 32-bit unsigned integer to string in binary format */
INLINE_OR_STATIC u32string_type base2_u32_to_u32string(uint32_t value) {
	return u32_to_u32string(value, 2, int_to_string_option_default);
}

/** @brief Converts a 32-bit unsigned integer to string in binary format with 0b prefix */
INLINE_OR_STATIC u32string_type base2_u32_to_u32string_with_prefix(uint32_t value) {
	return u32_to_u32string(value, 2, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 32-bit unsigned integer to string in binary format with 0B prefix */
INLINE_OR_STATIC u32string_type base2_u32_to_u32string_with_prefix_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 2, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 32-bit unsigned integer to string in octal format */
INLINE_OR_STATIC u32string_type base8_u32_to_u32string(uint32_t value) {
	return u32_to_u32string(value, 8, int_to_string_option_default);
}

/** @brief Converts a 32-bit unsigned integer to string in octal format with prefix (prefix: 0) */
INLINE_OR_STATIC u32string_type base8_u32_to_u32string_with_prefix(uint32_t value) {
	return u32_to_u32string(value, 8, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 32-bit unsigned integer to string in decimal format */
INLINE_OR_STATIC u32string_type base10_u32_to_u32string(uint32_t value) {
	return u32_to_u32string(value, 10, int_to_string_option_default);
}

/** @brief Converts a 32-bit unsigned integer to string in hexadecimal format */
INLINE_OR_STATIC u32string_type base16_u32_to_u32string(uint32_t value) {
	return u32_to_u32string(value, 16, int_to_string_option_default);
}

/** @brief Converts a 32-bit unsigned integer to string in hexadecimal format with uppercase A to F */
INLINE_OR_STATIC u32string_type base16_u32_to_u32string_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 16, int_to_string_option_uppercase);
}

/** @brief Converts a 32-bit unsigned integer to string in hexadecimal format with 0x prefix */
INLINE_OR_STATIC u32string_type base16_u32_to_u32string_with_prefix(uint32_t value) {
	return u32_to_u32string(value, 16, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 32-bit unsigned integer to string in hexadecimal format with 0X prefix an duppercase A to F */
INLINE_OR_STATIC u32string_type base16_u32_to_u32string_with_prefix_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 16, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

/* i64_to_i64string variants for bases 2, 8, 10 and 16 */
/** @brief Converts a 64-bit signed integer to string in binary format */
INLINE_OR_STATIC i64string_type base2_i64_to_i64string(int64_t value) {
	return i64_to_i64string(value, 2, int_to_string_option_default);
}

/** @brief Converts a 64-bit signed integer to string in binary format with 0b prefix */
INLINE_OR_STATIC i64string_type base2_i64_to_i64string_with_prefix(int64_t value) {
	return i64_to_i64string(value, 2, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 64-bit signed integer to string in binary format with 0B prefix */
INLINE_OR_STATIC i64string_type base2_i64_to_i64string_with_prefix_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 2, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 64-bit signed integer to string in octal format */
INLINE_OR_STATIC i64string_type base8_i64_to_i64string(int64_t value) {
	return i64_to_i64string(value, 8, int_to_string_option_default);
}

/** @brief Converts a 64-bit signed integer to string in octal format with prefix (prefix: 0) */
INLINE_OR_STATIC i64string_type base8_i64_to_i64string_with_prefix(int64_t value) {
	return i64_to_i64string(value, 8, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 64-bit signed integer to string in decimal format */
INLINE_OR_STATIC i64string_type base10_i64_to_i64string(int64_t value) {
	return i64_to_i64string(value, 10, int_to_string_option_default);
}

/** @brief Converts a 64-bit signed integer to string in hexadecimal format */
INLINE_OR_STATIC i64string_type base16_i64_to_i64string(int64_t value) {
	return i64_to_i64string(value, 16, int_to_string_option_default);
}

/** @brief Converts a 64-bit signed integer to string in hexadecimal format with uppercase A to F */
INLINE_OR_STATIC i64string_type base16_i64_to_i64string_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 16, int_to_string_option_uppercase);
}

/** @brief Converts a 64-bit signed integer to string in hexadecimal format with 0x prefix */
INLINE_OR_STATIC i64string_type base16_i64_to_i64string_with_prefix(int64_t value) {
	return i64_to_i64string(value, 16, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 64-bit signed integer to string in hexadecimal format with 0X prefix and uppercase A to F */
INLINE_OR_STATIC i64string_type base16_i64_to_i64string_with_prefix_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 16, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

/* u64_to_u64string variants for bases 2, 8, 10 and 16 */
/** @brief Converts a 64-bit unsigned integer to string in binary format */
INLINE_OR_STATIC u64string_type base2_u64_to_u64string(uint64_t value) {
	return u64_to_u64string(value, 2, int_to_string_option_default);
}

/** @brief Converts a 64-bit unsigned integer to string in binary format with 0b prefix */
INLINE_OR_STATIC u64string_type base2_u64_to_u64string_with_prefix(uint64_t value) {
	return u64_to_u64string(value, 2, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 64-bit unsigned integer to string in binary format with 0B prefix */
INLINE_OR_STATIC u64string_type base2_u64_to_u64string_with_prefix_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 2, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 64-bit unsigned integer to string in octal format */
INLINE_OR_STATIC u64string_type base8_u64_to_u64string(uint64_t value) {
	return u64_to_u64string(value, 8, int_to_string_option_default);
}

/** @brief Converts a 64-bit unsigned integer to string in octal format with prefix (prefix: 0) */
INLINE_OR_STATIC u64string_type base8_u64_to_u64string_with_prefix(uint64_t value) {
	return u64_to_u64string(value, 8, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 64-bit unsigned integer to string in decimal format */
INLINE_OR_STATIC u64string_type base10_u64_to_u64string(uint64_t value) {
	return u64_to_u64string(value, 10, int_to_string_option_default);
}

/** @brief Converts a 64-bit unsigned integer to string in hexadecimal format */
INLINE_OR_STATIC u64string_type base16_u64_to_u64string(uint64_t value) {
	return u64_to_u64string(value, 16, int_to_string_option_default);
}

/** @brief Converts a 64-bit unsigned integer to string in hexadecimal format with uppercase A to F */
INLINE_OR_STATIC u64string_type base16_u64_to_u64string_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 16, int_to_string_option_uppercase);
}

/** @brief Converts a 64-bit unsigned integer to string in hexadecimal format with 0x prefix */
INLINE_OR_STATIC u64string_type base16_u64_to_u64string_with_prefix(uint64_t value) {
	return u64_to_u64string(value, 16, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

/** @brief Converts a 64-bit unsigned integer to string in hexadecimal format with 0X prefix and uppercase A to F */
INLINE_OR_STATIC u64string_type base16_u64_to_u64string_with_prefix_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 16, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

#ifdef __cplusplus
}
#endif

#endif
