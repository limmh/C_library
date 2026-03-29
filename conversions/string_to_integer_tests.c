#include "string_to_integer.h"
#include "static_assert.h"
#include "unit_testing.h"
#include <string.h>

STATIC_ASSERT(INT32_MAX == 0x7FFFFFFF, "The assumption about the value of INT32_MAX is not valid.");
STATIC_ASSERT(INT32_MIN == -INT32_MAX - 1, "The assumption about the value of INT32_MIN is not valid.");
STATIC_ASSERT(UINT32_MAX == 0xFFFFFFFFU, "The assumption about the value of UINT32_MAX is not valid.");
STATIC_ASSERT(INT64_MAX == 0x7FFFFFFFFFFFFFFFLL, "The assumption about the value of INT64_MAX is not valid.");
STATIC_ASSERT(INT64_MIN == -INT64_MAX - 1LL, "The assumption about the value of INT64_MIN is not valid.");
STATIC_ASSERT(UINT64_MAX == 0xFFFFFFFFFFFFFFFFU, "The assumption about the value of UINT64_MAX is not valid.");

/* ============================================================================
 * Tests for string_to_i32: Base 10 (Decimal)
 * ============================================================================ */

TEST(string_to_i32_base10_positive_zero, "Parse '0' in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("0", 1, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0);
}

TEST(string_to_i32_base10_positive_one, "Parse '1' in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("1", 1, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 1);
}

TEST(string_to_i32_base10_positive_small, "Parse '42' in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("42", 2, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 42);
}

TEST(string_to_i32_base10_positive_large, "Parse '123456789' in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("123456789", 9, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 123456789);
}

TEST(string_to_i32_base10_positive_int32_max, "Parse '2147483647' (INT32_MAX) in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("2147483647", 10, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
}

TEST(string_to_i32_base10_negative_one, "Parse '-1' in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("-1", 2, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, -1);
}

TEST(string_to_i32_base10_negative_small, "Parse '-42' in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("-42", 3, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, -42);
}

TEST(string_to_i32_base10_negative_large, "Parse '-123456789' in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("-123456789", 10, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, -123456789);
}

TEST(string_to_i32_base10_negative_int32_min, "Parse '-2147483648' (INT32_MIN) in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("-2147483648", 11, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, INT32_MIN);
}

TEST(string_to_i32_base10_plus_sign, "Parse '+42' with plus sign in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("+42", 3, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 42);
}

TEST(string_to_i32_base10_leading_whitespace, "Parse '  123' with leading whitespace in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("  123", 5, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 123);
}

TEST(string_to_i32_base10_trailing_whitespace, "Parse '123  ' with trailing whitespace in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("123  ", 5, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 123);
}

TEST(string_to_i32_base10_leading_and_trailing_whitespace, "Parse '  456  ' with whitespace in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("  456  ", 7, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 456);
}

TEST(string_to_i32_base10_tab_whitespace, "Parse '\\t789\\t' with tab characters in base 10 to int32")
{
	string_to_i32_result_type result = string_to_i32("\t789\t", 5, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 789);
}

TEST(string_to_i32_base10_overflow_positive, "Parse '2147483648' (INT32_MAX + 1) should overflow in base 10")
{
	string_to_i32_result_type result = string_to_i32("2147483648", 10, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_value_greater_than_maximum_signed_value);
}

TEST(string_to_i32_base10_overflow_negative, "Parse '-2147483649' (INT32_MIN - 1) should overflow in base 10")
{
	string_to_i32_result_type result = string_to_i32("-2147483649", 11, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_value_smaller_than_minimum_signed_value);
}

/* ============================================================================
 * Tests for string_to_i32: Base 16 (Hexadecimal)
 * ============================================================================ */

TEST(string_to_i32_base16_zero, "Parse '0' in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("0", 1, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0);
}

TEST(string_to_i32_base16_single_digit, "Parse 'f' in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("f", 1, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 15);
}

TEST(string_to_i32_base16_lowercase, "Parse '1a2b' in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("1a2b", 4, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0x1a2b);
}

TEST(string_to_i32_base16_uppercase, "Parse '1A2B' in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("1A2B", 4, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0x1A2B);
}

TEST(string_to_i32_base16_mixed_case, "Parse '1a2B' with mixed case in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("1a2B", 4, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0x1a2B);
}

TEST(string_to_i32_base16_with_prefix_lowercase, "Parse '0xff' with lowercase prefix in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("0xff", 4, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0xff);
}

TEST(string_to_i32_base16_with_prefix_uppercase, "Parse '0XFF' with uppercase prefix in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("0XFF", 4, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0xFF);
}

TEST(string_to_i32_base16_negative, "Parse '-ff' negative in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("-ff", 3, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, -255);
}

TEST(string_to_i32_base16_negative_with_prefix, "Parse '-0x1a2b' negative with prefix in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("-0x1a2b", 7, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, -0x1a2b);
}

TEST(string_to_i32_base16_int32_max, "Parse '7fffffff' (INT32_MAX) in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("7fffffff", 8, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
}

TEST(string_to_i32_base16_int32_min, "Parse '-80000000' (INT32_MIN) in base 16 to int32")
{
	string_to_i32_result_type result = string_to_i32("-80000000", 9, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, INT32_MIN);
}

/* ============================================================================
 * Tests for string_to_i32: Base 8 (Octal)
 * ============================================================================ */

TEST(string_to_i32_base8_zero, "Parse '0' in base 8 to int32")
{
	string_to_i32_result_type result = string_to_i32("0", 1, 8);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0);
}

TEST(string_to_i32_base8_single_digit, "Parse '7' in base 8 to int32")
{
	string_to_i32_result_type result = string_to_i32("7", 1, 8);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 7);
}

TEST(string_to_i32_base8_multiple_digits, "Parse '1234' in base 8 to int32")
{
	string_to_i32_result_type result = string_to_i32("1234", 4, 8);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 01234);
}

TEST(string_to_i32_base8_with_prefix, "Parse '0123' with leading zero in base 8 to int32")
{
	string_to_i32_result_type result = string_to_i32("0123", 4, 8);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0123);
}

TEST(string_to_i32_base8_negative, "Parse '-1234' negative in base 8 to int32")
{
	string_to_i32_result_type result = string_to_i32("-1234", 5, 8);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, -01234);
}

TEST(string_to_i32_base8_int32_max, "Parse '17777777777' (INT32_MAX) in base 8 to int32")
{
	string_to_i32_result_type result = string_to_i32("17777777777", 11, 8);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
}

/* ============================================================================
 * Tests for string_to_i32: Base 2 (Binary)
 * ============================================================================ */

TEST(string_to_i32_base2_zero, "Parse '0' in base 2 to int32")
{
	string_to_i32_result_type result = string_to_i32("0", 1, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0);
}

TEST(string_to_i32_base2_one, "Parse '1' in base 2 to int32")
{
	string_to_i32_result_type result = string_to_i32("1", 1, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 1);
}

TEST(string_to_i32_base2_multiple_bits, "Parse '10101' in base 2 to int32")
{
	string_to_i32_result_type result = string_to_i32("10101", 5, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 21);
}

TEST(string_to_i32_base2_with_prefix_lowercase, "Parse '0b1010' with lowercase prefix in base 2 to int32")
{
	string_to_i32_result_type result = string_to_i32("0b1010", 6, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 10);
}

TEST(string_to_i32_base2_with_prefix_uppercase, "Parse '0B1010' with uppercase prefix in base 2 to int32")
{
	string_to_i32_result_type result = string_to_i32("0B1010", 6, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 10);
}

TEST(string_to_i32_base2_negative, "Parse '-1010' negative in base 2 to int32")
{
	string_to_i32_result_type result = string_to_i32("-1010", 5, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, -10);
}

TEST(string_to_i32_base2_int32_max, "Parse '1111111111111111111111111111111' (INT32_MAX) in base 2 to int32")
{
	string_to_i32_result_type result = string_to_i32("1111111111111111111111111111111", 31, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
}

/* ============================================================================
 * Tests for string_to_i32: Error Cases
 * ============================================================================ */

TEST(string_to_i32_error_null_string, "Parse NULL string should return error_null_string")
{
	string_to_i32_result_type result = string_to_i32(NULL, 0, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_null_string);
}

TEST(string_to_i32_error_zero_length, "Parse with zero length should return error_zero_length")
{
	string_to_i32_result_type result = string_to_i32("123", 0, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_zero_length);
}

TEST(string_to_i32_error_empty_string, "Parse empty string should return error_empty_string")
{
	const char *empty = "";
	string_to_i32_result_type result = string_to_i32(empty, 1, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_empty_string);
}

TEST(string_to_i32_error_invalid_base_low, "Parse with base 1 should return error_invalid_base")
{
	string_to_i32_result_type result = string_to_i32("10", 2, 1);
	ASSERT_EQUAL(result.error, string_to_int_error_invalid_base);
}

TEST(string_to_i32_error_invalid_base_high, "Parse with base 37 should return error_unsupported_base")
{
	string_to_i32_result_type result = string_to_i32("10", 2, 37);
	ASSERT_EQUAL(result.error, string_to_int_error_unsupported_base);
}

TEST(string_to_i32_error_only_whitespaces, "Parse only whitespaces should return error_only_whitespaces")
{
	string_to_i32_result_type result = string_to_i32("   ", 3, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_only_whitespaces);
}

TEST(string_to_i32_error_invalid_character, "Parse '12a34' with invalid character in base 10 should error")
{
	string_to_i32_result_type result = string_to_i32("`1234", 5, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_invalid_character);
}

TEST(string_to_i32_error_digit_not_supported, "Parse '129' in base 8 should error (9 not in base 8)")
{
	string_to_i32_result_type result = string_to_i32("129", 3, 8);
	ASSERT_EQUAL(result.error, string_to_int_error_digit_not_supported_by_base);
}

TEST(string_to_i32_error_whitespace_after_sign, "Parse '- 123' with space after sign should error")
{
	string_to_i32_result_type result = string_to_i32("- 123", 5, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_whitespace_after_sign);
}

TEST(string_to_i32_error_incomplete_string_sign_only, "Parse '-' sign only should error")
{
	string_to_i32_result_type result = string_to_i32("-", 1, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_incomplete_string);
}

TEST(string_to_i32_error_incomplete_string_prefix_only, "Parse '0x' prefix only should error")
{
	string_to_i32_result_type result = string_to_i32("0x", 2, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_incomplete_string);
}

TEST(string_to_i32_error_invalid_trailing_character, "Parse '123abc' with trailing invalid characters")
{
	string_to_i32_result_type result = string_to_i32("123 abc", 6, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_invalid_trailing_character);
}

TEST(string_to_i32_error_invalid_prefix, "Parse '0q123' with invalid prefix in base 16")
{
	string_to_i32_result_type result = string_to_i32("0q123", 5, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_invalid_prefix);
}

/* ============================================================================
 * Tests for string_to_u32: Base 10 (Decimal)
 * ============================================================================ */

TEST(string_to_u32_base10_zero, "Parse '0' in base 10 to uint32")
{
	string_to_u32_result_type result = string_to_u32("0", 1, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 0U);
}

TEST(string_to_u32_base10_small, "Parse '42' in base 10 to uint32")
{
	string_to_u32_result_type result = string_to_u32("42", 2, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 42U);
}

TEST(string_to_u32_base10_large, "Parse '3000000000' in base 10 to uint32")
{
	string_to_u32_result_type result = string_to_u32("3000000000", 10, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 3000000000U);
}

TEST(string_to_u32_base10_uint32_max, "Parse '4294967295' (UINT32_MAX) in base 10 to uint32")
{
	string_to_u32_result_type result = string_to_u32("4294967295", 10, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
}

TEST(string_to_u32_base10_with_plus_sign, "Parse '+42' with plus sign in base 10 to uint32")
{
	string_to_u32_result_type result = string_to_u32("+42", 3, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 42U);
}

TEST(string_to_u32_base10_with_whitespace, "Parse '  789  ' with whitespace in base 10 to uint32")
{
	string_to_u32_result_type result = string_to_u32("  789  ", 7, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 789U);
}

TEST(string_to_u32_base10_overflow, "Parse '4294967296' (UINT32_MAX + 1) should overflow")
{
	string_to_u32_result_type result = string_to_u32("4294967296", 10, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_value_greater_than_maximum_unsigned_value);
}

TEST(string_to_u32_base10_negative, "Parse '-1' should error (negative for unsigned)")
{
	string_to_u32_result_type result = string_to_u32("-1", 2, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_value_smaller_than_minimum_unsigned_value);
}

/* ============================================================================
 * Tests for string_to_u32: Base 16 (Hexadecimal)
 * ============================================================================ */

TEST(string_to_u32_base16_lowercase, "Parse 'deadbeef' in base 16 to uint32")
{
	string_to_u32_result_type result = string_to_u32("deadbeef", 8, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 0xdeadbeefU);
}

TEST(string_to_u32_base16_uppercase, "Parse 'DEADBEEF' in base 16 to uint32")
{
	string_to_u32_result_type result = string_to_u32("DEADBEEF", 8, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 0xDEADBEEFU);
}

TEST(string_to_u32_base16_with_prefix, "Parse '0xffffffff' with prefix in base 16 to uint32")
{
	string_to_u32_result_type result = string_to_u32("0xffffffff", 10, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
}

TEST(string_to_u32_base16_uint32_max, "Parse 'ffffffff' (UINT32_MAX) in base 16 to uint32")
{
	string_to_u32_result_type result = string_to_u32("ffffffff", 8, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
}

/* ============================================================================
 * Tests for string_to_u32: Base 2 (Binary)
 * ============================================================================ */

TEST(string_to_u32_base2_zero, "Parse '0' in base 2 to uint32")
{
	string_to_u32_result_type result = string_to_u32("0", 1, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 0U);
}

TEST(string_to_u32_base2_small, "Parse '1010' in base 2 to uint32")
{
	string_to_u32_result_type result = string_to_u32("1010", 4, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 10U);
}

TEST(string_to_u32_base2_with_prefix, "Parse '0b11111111' with prefix in base 2 to uint32")
{
	string_to_u32_result_type result = string_to_u32("0b11111111", 10, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 255U);
}

/* ============================================================================
 * Tests for string_to_i64: Base 10 (Decimal)
 * ============================================================================ */

TEST(string_to_i64_base10_zero, "Parse '0' in base 10 to int64")
{
	string_to_i64_result_type result = string_to_i64("0", 1, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, 0LL);
}

TEST(string_to_i64_base10_small, "Parse '42' in base 10 to int64")
{
	string_to_i64_result_type result = string_to_i64("42", 2, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, 42LL);
}

TEST(string_to_i64_base10_large, "Parse '9223372036854775807' (INT64_MAX) in base 10 to int64")
{
	string_to_i64_result_type result = string_to_i64("9223372036854775807", 19, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, INT64_MAX);
}

TEST(string_to_i64_base10_negative_int64_min, "Parse '-9223372036854775808' (INT64_MIN) in base 10 to int64")
{
	string_to_i64_result_type result = string_to_i64("-9223372036854775808", 20, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, INT64_MIN);
}

TEST(string_to_i64_base10_overflow_positive, "Parse '9223372036854775808' (INT64_MAX + 1) should overflow")
{
	string_to_i64_result_type result = string_to_i64("9223372036854775808", 19, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_value_greater_than_maximum_signed_value);
}

TEST(string_to_i64_base10_overflow_negative, "Parse '-9223372036854775809' (INT64_MIN - 1) should overflow")
{
	string_to_i64_result_type result = string_to_i64("-9223372036854775809", 20, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_value_smaller_than_minimum_signed_value);
}

/* ============================================================================
 * Tests for string_to_i64: Base 16 (Hexadecimal)
 * ============================================================================ */

TEST(string_to_i64_base16_lowercase, "Parse '0123456789abcdef' in base 16 to int64")
{
	string_to_i64_result_type result = string_to_i64("0123456789abcdef", 16, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, 0x0123456789abcdefLL);
}

TEST(string_to_i64_base16_uppercase, "Parse '0123456789ABCDEF' in base 16 to int64")
{
	string_to_i64_result_type result = string_to_i64("0123456789ABCDEF", 16, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, 0x0123456789ABCDEFLL);
}

TEST(string_to_i64_base16_int64_max, "Parse '7fffffffffffffff' (INT64_MAX) in base 16 to int64")
{
	string_to_i64_result_type result = string_to_i64("7fffffffffffffff", 16, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, INT64_MAX);
}

TEST(string_to_i64_base16_negative, "Parse '-123' negative in base 16 to int64")
{
	string_to_i64_result_type result = string_to_i64("-123", 4, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, -0x123LL);
}

/* ============================================================================
 * Tests for string_to_i64: Base 8 (Octal)
 * ============================================================================ */

TEST(string_to_i64_base8_small, "Parse '1234' in base 8 to int64")
{
	string_to_i64_result_type result = string_to_i64("1234", 4, 8);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, 01234LL);
}

TEST(string_to_i64_base8_with_prefix, "Parse '0777' with prefix in base 8 to int64")
{
	string_to_i64_result_type result = string_to_i64("0777", 4, 8);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, 0777LL);
}

/* ============================================================================
 * Tests for string_to_i64: Base 2 (Binary)
 * ============================================================================ */

TEST(string_to_i64_base2_small, "Parse '10101010' in base 2 to int64")
{
	string_to_i64_result_type result = string_to_i64("10101010", 8, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, 170LL);
}

TEST(string_to_i64_base2_with_prefix, "Parse '0b11110000' with prefix in base 2 to int64")
{
	string_to_i64_result_type result = string_to_i64("0b11110000", 10, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, 240LL);
}

/* ============================================================================
 * Tests for string_to_u64: Base 10 (Decimal)
 * ============================================================================ */

TEST(string_to_u64_base10_zero, "Parse '0' in base 10 to uint64")
{
	string_to_u64_result_type result = string_to_u64("0", 1, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT64_EQUAL(result.value, 0ULL);
}

TEST(string_to_u64_base10_small, "Parse '42' in base 10 to uint64")
{
	string_to_u64_result_type result = string_to_u64("42", 2, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT64_EQUAL(result.value, 42ULL);
}

TEST(string_to_u64_base10_large, "Parse '18446744073709551615' (UINT64_MAX) in base 10 to uint64")
{
	string_to_u64_result_type result = string_to_u64("18446744073709551615", 20, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT64_EQUAL(result.value, UINT64_MAX);
}

TEST(string_to_u64_base10_with_plus_sign, "Parse '+999' with plus sign in base 10 to uint64")
{
	string_to_u64_result_type result = string_to_u64("+999", 4, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT64_EQUAL(result.value, 999ULL);
}

TEST(string_to_u64_base10_overflow, "Parse '18446744073709551616' (UINT64_MAX + 1) should overflow")
{
	string_to_u64_result_type result = string_to_u64("18446744073709551616", 20, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_value_greater_than_maximum_unsigned_value);
}

TEST(string_to_u64_base10_negative, "Parse '-1' should error (negative for unsigned)")
{
	string_to_u64_result_type result = string_to_u64("-1", 2, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_value_smaller_than_minimum_unsigned_value);
}

/* ============================================================================
 * Tests for string_to_u64: Base 16 (Hexadecimal)
 * ============================================================================ */

TEST(string_to_u64_base16_lowercase, "Parse 'ffffffffffffffff' in base 16 to uint64")
{
	string_to_u64_result_type result = string_to_u64("ffffffffffffffff", 16, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT64_EQUAL(result.value, UINT64_MAX);
}

TEST(string_to_u64_base16_with_prefix, "Parse '0xffffffffffffffff' with prefix in base 16 to uint64")
{
	string_to_u64_result_type result = string_to_u64("0xffffffffffffffff", 18, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT64_EQUAL(result.value, UINT64_MAX);
}

/* ============================================================================
 * Tests for i32string_to_i32 macro (roundtrip from i32string type)
 * ============================================================================ */

TEST(i32string_to_i32_roundtrip_base10, "Roundtrip: convert 12345 to string then parse back from i32string in base 10")
{
	i32string_type str = base10_i32_to_i32string(12345);
	string_to_i32_result_type result = i32string_to_i32(str, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 12345);
}

TEST(i32string_to_i32_roundtrip_base16, "Roundtrip: convert 0x1a2b to string then parse back from i32string in base 16")
{
	i32string_type str = base16_i32_to_i32string(0x1a2b);
	string_to_i32_result_type result = i32string_to_i32(str, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 0x1a2b);
}

TEST(i32string_to_i32_roundtrip_base2, "Roundtrip: convert 255 to string then parse back from i32string in base 2")
{
	i32string_type str = base2_i32_to_i32string(255);
	string_to_i32_result_type result = i32string_to_i32(str, 2);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 255);
}

TEST(i32string_to_i32_roundtrip_negative, "Roundtrip: convert -999 to string then parse back from i32string")
{
	i32string_type str = base10_i32_to_i32string(-999);
	string_to_i32_result_type result = i32string_to_i32(str, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, -999);
}

/* ============================================================================
 * Tests for u32string_to_u32 macro (roundtrip from u32string type)
 * ============================================================================ */

TEST(u32string_to_u32_roundtrip_base10, "Roundtrip: convert 99999 to string then parse back from u32string in base 10")
{
	u32string_type str = base10_u32_to_u32string(99999U);
	string_to_u32_result_type result = u32string_to_u32(str, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 99999U);
}

TEST(u32string_to_u32_roundtrip_base16, "Roundtrip: convert 0xdeadbeef to string then parse back from u32string in base 16")
{
	u32string_type str = base16_u32_to_u32string(0xdeadbeefU);
	string_to_u32_result_type result = u32string_to_u32(str, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT32_EQUAL(result.value, 0xdeadbeefU);
}

/* ============================================================================
 * Tests for i64string_to_i64 macro (roundtrip from i64string type)
 * ============================================================================ */

TEST(i64string_to_i64_roundtrip_base10, "Roundtrip: convert 123456789012 to string then parse back from i64string in base 10")
{
	i64string_type str = base10_i64_to_i64string(123456789012LL);
	string_to_i64_result_type result = i64string_to_i64(str, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, 123456789012LL);
}

TEST(i64string_to_i64_roundtrip_base16, "Roundtrip: convert 0x123456789abcdef to string then parse back from i64string in base 16")
{
	i64string_type str = base16_i64_to_i64string(0x123456789abcdefLL);
	string_to_i64_result_type result = i64string_to_i64(str, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT64_EQUAL(result.value, 0x123456789abcdefLL);
}

/* ============================================================================
 * Tests for u64string_to_u64 macro (roundtrip from u64string type)
 * ============================================================================ */

TEST(u64string_to_u64_roundtrip_base10, "Roundtrip: convert 9999999999999 to string then parse back from u64string in base 10")
{
	u64string_type str = base10_u64_to_u64string(9999999999999ULL);
	string_to_u64_result_type result = u64string_to_u64(str, 10);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT64_EQUAL(result.value, 9999999999999ULL);
}

TEST(u64string_to_u64_roundtrip_base16, "Roundtrip: convert 0xfedcba9876543210 to string then parse back from u64string in base 16")
{
	u64string_type str = base16_u64_to_u64string(0xfedcba9876543210ULL);
	string_to_u64_result_type result = u64string_to_u64(str, 16);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_UINT64_EQUAL(result.value, 0xfedcba9876543210ULL);
}

/* ============================================================================
 * Tests for various bases (3, 5, 12, 35, 36)
 * ============================================================================ */

TEST(string_to_i32_base3, "Parse '1201' in base 3 to int32 (1*27 + 2*9 + 0*3 + 1 = 46)")
{
	string_to_i32_result_type result = string_to_i32("1201", 4, 3);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 46);
}

TEST(string_to_i32_base5, "Parse '1234' in base 5 to int32 (1*125 + 2*25 + 3*5 + 4 = 194)")
{
	string_to_i32_result_type result = string_to_i32("1234", 4, 5);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 194);
}

TEST(string_to_i32_base12, "Parse 'ab8' in base 12 to int32 (10*144 + 11*12 + 8 = 1580)")
{
	string_to_i32_result_type result = string_to_i32("ab8", 3, 12);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 1580);
}

TEST(string_to_i32_base35, "Parse 'xy' in base 35 to int32 (33*35 + 34 = 1225)")
{
	string_to_i32_result_type result = string_to_i32("xy", 2, 35);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 1189);
}

TEST(string_to_i32_base36, "Parse 'zz' in base 36 to int32 (35*36 + 35 = 1295)")
{
	string_to_i32_result_type result = string_to_i32("zz", 2, 36);
	ASSERT_EQUAL(result.error, string_to_int_error_none);
	ASSERT_INT32_EQUAL(result.value, 1295);
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(list_of_tests) {
		/* string_to_i32: Base 10 tests */
		string_to_i32_base10_positive_zero,
		string_to_i32_base10_positive_one,
		string_to_i32_base10_positive_small,
		string_to_i32_base10_positive_large,
		string_to_i32_base10_positive_int32_max,
		string_to_i32_base10_negative_one,
		string_to_i32_base10_negative_small,
		string_to_i32_base10_negative_large,
		string_to_i32_base10_negative_int32_min,
		string_to_i32_base10_plus_sign,
		string_to_i32_base10_leading_whitespace,
		string_to_i32_base10_trailing_whitespace,
		string_to_i32_base10_leading_and_trailing_whitespace,
		string_to_i32_base10_tab_whitespace,
		string_to_i32_base10_overflow_positive,
		string_to_i32_base10_overflow_negative,

		/* string_to_i32: Base 16 tests */
		string_to_i32_base16_zero,
		string_to_i32_base16_single_digit,
		string_to_i32_base16_lowercase,
		string_to_i32_base16_uppercase,
		string_to_i32_base16_mixed_case,
		string_to_i32_base16_with_prefix_lowercase,
		string_to_i32_base16_with_prefix_uppercase,
		string_to_i32_base16_negative,
		string_to_i32_base16_negative_with_prefix,
		string_to_i32_base16_int32_max,
		string_to_i32_base16_int32_min,

		/* string_to_i32: Base 8 tests */
		string_to_i32_base8_zero,
		string_to_i32_base8_single_digit,
		string_to_i32_base8_multiple_digits,
		string_to_i32_base8_with_prefix,
		string_to_i32_base8_negative,
		string_to_i32_base8_int32_max,

		/* string_to_i32: Base 2 tests */
		string_to_i32_base2_zero,
		string_to_i32_base2_one,
		string_to_i32_base2_multiple_bits,
		string_to_i32_base2_with_prefix_lowercase,
		string_to_i32_base2_with_prefix_uppercase,
		string_to_i32_base2_negative,
		string_to_i32_base2_int32_max,

		/* string_to_i32: Error cases */
		string_to_i32_error_null_string,
		string_to_i32_error_zero_length,
		string_to_i32_error_empty_string,
		string_to_i32_error_invalid_base_low,
		string_to_i32_error_invalid_base_high,
		string_to_i32_error_only_whitespaces,
		string_to_i32_error_invalid_character,
		string_to_i32_error_digit_not_supported,
		string_to_i32_error_whitespace_after_sign,
		string_to_i32_error_incomplete_string_sign_only,
		string_to_i32_error_incomplete_string_prefix_only,
		string_to_i32_error_invalid_trailing_character,
		string_to_i32_error_invalid_prefix,

		/* string_to_u32: Base 10 tests */
		string_to_u32_base10_zero,
		string_to_u32_base10_small,
		string_to_u32_base10_large,
		string_to_u32_base10_uint32_max,
		string_to_u32_base10_with_plus_sign,
		string_to_u32_base10_with_whitespace,
		string_to_u32_base10_overflow,
		string_to_u32_base10_negative,

		/* string_to_u32: Base 16 tests */
		string_to_u32_base16_lowercase,
		string_to_u32_base16_uppercase,
		string_to_u32_base16_with_prefix,
		string_to_u32_base16_uint32_max,

		/* string_to_u32: Base 2 tests */
		string_to_u32_base2_zero,
		string_to_u32_base2_small,
		string_to_u32_base2_with_prefix,

		/* string_to_i64: Base 10 tests */
		string_to_i64_base10_zero,
		string_to_i64_base10_small,
		string_to_i64_base10_large,
		string_to_i64_base10_negative_int64_min,
		string_to_i64_base10_overflow_positive,
		string_to_i64_base10_overflow_negative,

		/* string_to_i64: Base 16 tests */
		string_to_i64_base16_lowercase,
		string_to_i64_base16_uppercase,
		string_to_i64_base16_int64_max,
		string_to_i64_base16_negative,

		/* string_to_i64: Base 8 tests */
		string_to_i64_base8_small,
		string_to_i64_base8_with_prefix,

		/* string_to_i64: Base 2 tests */
		string_to_i64_base2_small,
		string_to_i64_base2_with_prefix,

		/* string_to_u64: Base 10 tests */
		string_to_u64_base10_zero,
		string_to_u64_base10_small,
		string_to_u64_base10_large,
		string_to_u64_base10_with_plus_sign,
		string_to_u64_base10_overflow,
		string_to_u64_base10_negative,

		/* string_to_u64: Base 16 tests */
		string_to_u64_base16_lowercase,
		string_to_u64_base16_with_prefix,

		/* Roundtrip tests: i32string */
		i32string_to_i32_roundtrip_base10,
		i32string_to_i32_roundtrip_base16,
		i32string_to_i32_roundtrip_base2,
		i32string_to_i32_roundtrip_negative,

		/* Roundtrip tests: u32string */
		u32string_to_u32_roundtrip_base10,
		u32string_to_u32_roundtrip_base16,

		/* Roundtrip tests: i64string */
		i64string_to_i64_roundtrip_base10,
		i64string_to_i64_roundtrip_base16,

		/* Roundtrip tests: u64string */
		u64string_to_u64_roundtrip_base10,
		u64string_to_u64_roundtrip_base16,

		/* Various base tests */
		string_to_i32_base3,
		string_to_i32_base5,
		string_to_i32_base12,
		string_to_i32_base35,
		string_to_i32_base36
	};

	PRINT_FILE_NAME();
	RUN_TESTS(list_of_tests);
	PRINT_TEST_STATISTICS(list_of_tests);
	return 0;
}
