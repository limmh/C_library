#include "integer_to_string.h"
#include "static_assert.h"
#include "unit_testing.h"
#include <string.h>

STATIC_ASSERT(INT32_MAX == 0x7FFFFFFF, "The assumption about the value of INT32_MAX is not valid.");
STATIC_ASSERT(INT32_MIN == -INT32_MAX - 1, "The assumption about the value of INT32_MIN is not valid.");
STATIC_ASSERT(UINT32_MAX == 0xFFFFFFFFU, "The assumption about the value of UINT32_MAX is not valid.");
STATIC_ASSERT(INT64_MAX == 0x7FFFFFFFFFFFFFFFLL, "The assumption about the value of INT64_MAX is not valid.");
STATIC_ASSERT(INT64_MIN == -INT64_MAX - 1LL, "The assumption about the value of INT64_MIN is not valid.");
STATIC_ASSERT(UINT64_MAX == 0xFFFFFFFFFFFFFFFFU, "The assumption about the value of UINT64_MAX is not valid.");

TEST(tests_for_int32_base_2_output, "Tests for 32-bit signed integer-to-string conversion with base 2 output")
{
	const int base2 = 2;
	int_to_string_option_type options = int_to_string_option_default;
	i32string_type i32string = {{0}};

	i32string = i32_to_i32string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-10000000000000000000000000000000");
	i32string = i32_to_i32string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-11000011010011111");
	i32string = i32_to_i32string(-1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "11000011010011111");
	i32string = i32_to_i32string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "1111111111111111111111111111111");

	options = int_to_string_option_uppercase;
	i32string = i32_to_i32string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-10000000000000000000000000000000");
	i32string = i32_to_i32string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-11000011010011111");
	i32string = i32_to_i32string(-1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "11000011010011111");
	i32string = i32_to_i32string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "1111111111111111111111111111111");

	options = int_to_string_option_add_prefix;
	i32string = i32_to_i32string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0b10000000000000000000000000000000");
	i32string = i32_to_i32string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0b11000011010011111");
	i32string = i32_to_i32string(-1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0b1");
	i32string = i32_to_i32string(0, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "0b0");
	i32string = i32_to_i32string(1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "0b1");
	i32string = i32_to_i32string(99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "0b11000011010011111");
	i32string = i32_to_i32string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "0b1111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign;
	i32string = i32_to_i32string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-10000000000000000000000000000000");
	i32string = i32_to_i32string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-11000011010011111");
	i32string = i32_to_i32string(-1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "+1");
	i32string = i32_to_i32string(99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "+11000011010011111");
	i32string = i32_to_i32string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "+1111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	i32string = i32_to_i32string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0b10000000000000000000000000000000");
	i32string = i32_to_i32string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0b11000011010011111");
	i32string = i32_to_i32string(-1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0b1");
	i32string = i32_to_i32string(0, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "0b0");
	i32string = i32_to_i32string(1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0b1");
	i32string = i32_to_i32string(99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0b11000011010011111");
	i32string = i32_to_i32string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0b1111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i32string = i32_to_i32string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0B10000000000000000000000000000000");
	i32string = i32_to_i32string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0B11000011010011111");
	i32string = i32_to_i32string(-1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0B1");
	i32string = i32_to_i32string(0, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "0B0");
	i32string = i32_to_i32string(1, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0B1");
	i32string = i32_to_i32string(99999, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0B11000011010011111");
	i32string = i32_to_i32string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0B1111111111111111111111111111111");
}

TEST(tests_for_int32_base_8_output, "Tests for 32-bit signed integer-to-string conversion with base 8 output")
{
	const int base8 = 8;
	int_to_string_option_type options = int_to_string_option_default;
	i32string_type i32string = {{0}};

	i32string = i32_to_i32string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-20000000000");
	i32string = i32_to_i32string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-303237");
	i32string = i32_to_i32string(-1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "303237");
	i32string = i32_to_i32string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "17777777777");

	options = int_to_string_option_uppercase;
	i32string = i32_to_i32string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-20000000000");
	i32string = i32_to_i32string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-303237");
	i32string = i32_to_i32string(-1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "303237");
	i32string = i32_to_i32string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "17777777777");

	options = int_to_string_option_add_prefix;
	i32string = i32_to_i32string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-020000000000");
	i32string = i32_to_i32string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0303237");
	i32string = i32_to_i32string(-1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-01");
	i32string = i32_to_i32string(0, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "00");
	i32string = i32_to_i32string(1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "01");
	i32string = i32_to_i32string(99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "0303237");
	i32string = i32_to_i32string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "017777777777");

	options = int_to_string_option_add_plus_sign;
	i32string = i32_to_i32string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-20000000000");
	i32string = i32_to_i32string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-303237");
	i32string = i32_to_i32string(-1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "+1");
	i32string = i32_to_i32string(99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "+303237");
	i32string = i32_to_i32string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "+17777777777");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	i32string = i32_to_i32string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-020000000000");
	i32string = i32_to_i32string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0303237");
	i32string = i32_to_i32string(-1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-01");
	i32string = i32_to_i32string(0, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "00");
	i32string = i32_to_i32string(1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "+01");
	i32string = i32_to_i32string(99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0303237");
	i32string = i32_to_i32string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "+017777777777");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i32string = i32_to_i32string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-020000000000");
	i32string = i32_to_i32string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0303237");
	i32string = i32_to_i32string(-1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "-01");
	i32string = i32_to_i32string(0, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "00");
	i32string = i32_to_i32string(1, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "+01");
	i32string = i32_to_i32string(99999, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0303237");
	i32string = i32_to_i32string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i32string.content, "+017777777777");
}

TEST(tests_for_int32_base_10_output, "Tests for 32-bit signed integer-to-string conversion with base 10 output")
{
	const int base10 = 10;
	int_to_string_option_type options = int_to_string_option_default;
	i32string_type i32string = {{0}};

	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "2147483647");

	options = int_to_string_option_uppercase;
	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "2147483647");

	options = int_to_string_option_add_prefix;
	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "2147483647");

	options = int_to_string_option_add_plus_sign;
	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+2147483647");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+2147483647");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+2147483647");
}

TEST(tests_for_int32_base_16_output, "Tests for 32-bit signed integer-to-string conversion with base 16 output")
{
	const int base16 = 16;
	int_to_string_option_type options = int_to_string_option_default;
	i32string_type i32string = {{0}};

	i32string = i32_to_i32string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-80000000");
	i32string = i32_to_i32string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1869f");
	i32string = i32_to_i32string(-1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "1869f");
	i32string = i32_to_i32string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "7fffffff");

	options = int_to_string_option_uppercase;
	i32string = i32_to_i32string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-80000000");
	i32string = i32_to_i32string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1869F");
	i32string = i32_to_i32string(-1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "1869F");
	i32string = i32_to_i32string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "7FFFFFFF");

	options = int_to_string_option_add_prefix;
	i32string = i32_to_i32string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0x80000000");
	i32string = i32_to_i32string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0x1869f");
	i32string = i32_to_i32string(-1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0x1");
	i32string = i32_to_i32string(0, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "0x0");
	i32string = i32_to_i32string(1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "0x1");
	i32string = i32_to_i32string(99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "0x1869f");
	i32string = i32_to_i32string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "0x7fffffff");

	options = int_to_string_option_add_plus_sign;
	i32string = i32_to_i32string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-80000000");
	i32string = i32_to_i32string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1869f");
	i32string = i32_to_i32string(-1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "+1");
	i32string = i32_to_i32string(99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "+1869f");
	i32string = i32_to_i32string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "+7fffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	i32string = i32_to_i32string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0x80000000");
	i32string = i32_to_i32string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0x1869f");
	i32string = i32_to_i32string(-1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0x1");
	i32string = i32_to_i32string(0, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "0x0");
	i32string = i32_to_i32string(1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0x1");
	i32string = i32_to_i32string(99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0x1869f");
	i32string = i32_to_i32string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0x7fffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i32string = i32_to_i32string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0X80000000");
	i32string = i32_to_i32string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0X1869F");
	i32string = i32_to_i32string(-1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "-0X1");
	i32string = i32_to_i32string(0, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "0X0");
	i32string = i32_to_i32string(1, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0X1");
	i32string = i32_to_i32string(99999, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0X1869F");
	i32string = i32_to_i32string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i32string.content, "+0X7FFFFFFF");
}

TEST(tests_for_uint32_base_2_output, "Tests for 32-bit unsigned integer-to-string conversion with base 2 output")
{
	const int base2 = 2;
	int_to_string_option_type options = int_to_string_option_default;
	u32string_type u32string = {{0}};

	u32string = u32_to_u32string(0U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = u32_to_u32string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "11000011010011111");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "1111111111111111111111111111111");
	u32string = u32_to_u32string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "11111111111111111111111111111111");

	options = int_to_string_option_uppercase;
	u32string = u32_to_u32string(0U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = u32_to_u32string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "11000011010011111");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "1111111111111111111111111111111");
	u32string = u32_to_u32string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "11111111111111111111111111111111");

	options = int_to_string_option_add_prefix;
	u32string = u32_to_u32string(0U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0b0");
	u32string = u32_to_u32string(1U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0b1");
	u32string = u32_to_u32string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0b11000011010011111");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0b1111111111111111111111111111111");
	u32string = u32_to_u32string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0b11111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign;
	u32string = u32_to_u32string(0U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1");
	u32string = u32_to_u32string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+11000011010011111");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1111111111111111111111111111111");
	u32string = u32_to_u32string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+11111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u32string = u32_to_u32string(0U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0b0");
	u32string = u32_to_u32string(1U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0b1");
	u32string = u32_to_u32string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0b11000011010011111");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0b1111111111111111111111111111111");
	u32string = u32_to_u32string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0b11111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u32string = u32_to_u32string(0U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0b0");
	u32string = u32_to_u32string(1U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0b1");
	u32string = u32_to_u32string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0b11000011010011111");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0b1111111111111111111111111111111");
	u32string = u32_to_u32string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0b11111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	u32string = u32_to_u32string(0U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "0B0");
	u32string = u32_to_u32string(1U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0B1");
	u32string = u32_to_u32string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0B11000011010011111");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0B1111111111111111111111111111111");
	u32string = u32_to_u32string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0B11111111111111111111111111111111");
}

TEST(tests_for_uint32_base_8_output, "Tests for 32-bit unsigned integer-to-string conversion with base 8 output")
{
	const int base8 = 8;
	int_to_string_option_type options = int_to_string_option_default;
	u32string_type u32string = {{0}};

	u32string = u32_to_u32string(0U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = u32_to_u32string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "303237");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "17777777777");
	u32string = u32_to_u32string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "37777777777");

	options = int_to_string_option_uppercase;
	u32string = u32_to_u32string(0U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = u32_to_u32string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "303237");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "17777777777");
	u32string = u32_to_u32string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "37777777777");

	options = int_to_string_option_add_prefix;
	u32string = u32_to_u32string(0U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "00");
	u32string = u32_to_u32string(1U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "01");
	u32string = u32_to_u32string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "0303237");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "017777777777");
	u32string = u32_to_u32string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "037777777777");

	options = int_to_string_option_add_plus_sign;
	u32string = u32_to_u32string(0U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1");
	u32string = u32_to_u32string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+303237");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+17777777777");
	u32string = u32_to_u32string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+37777777777");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u32string = u32_to_u32string(0U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "00");
	u32string = u32_to_u32string(1U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+01");
	u32string = u32_to_u32string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0303237");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+017777777777");
	u32string = u32_to_u32string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+037777777777");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u32string = u32_to_u32string(0U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "00");
	u32string = u32_to_u32string(1U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+01");
	u32string = u32_to_u32string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0303237");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+017777777777");
	u32string = u32_to_u32string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+037777777777");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	u32string = u32_to_u32string(0U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "00");
	u32string = u32_to_u32string(1U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+01");
	u32string = u32_to_u32string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0303237");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+017777777777");
	u32string = u32_to_u32string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u32string.content, "+037777777777");
}

TEST(tests_for_uint32_base_10_output, "Tests for 32-bit unsigned integer-to-string conversion with base 10 output")
{
	const int base10 = 10;
	int_to_string_option_type options = int_to_string_option_default;
	u32string_type u32string = {{0}};

	u32string = u32_to_u32string(0U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = u32_to_u32string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "99999");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "2147483647");
	u32string = u32_to_u32string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "4294967295");

	options = int_to_string_option_uppercase;
	u32string = u32_to_u32string(0U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = u32_to_u32string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "99999");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "2147483647");
	u32string = u32_to_u32string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "4294967295");

	options = int_to_string_option_add_prefix;
	u32string = u32_to_u32string(0U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = u32_to_u32string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "99999");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "2147483647");
	u32string = u32_to_u32string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "4294967295");

	options = int_to_string_option_add_plus_sign;
	u32string = u32_to_u32string(0U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1");
	u32string = u32_to_u32string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+99999");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+2147483647");
	u32string = u32_to_u32string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+4294967295");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u32string = u32_to_u32string(0U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1");
	u32string = u32_to_u32string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+99999");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+2147483647");
	u32string = u32_to_u32string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+4294967295");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u32string = u32_to_u32string(0U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1");
	u32string = u32_to_u32string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+99999");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+2147483647");
	u32string = u32_to_u32string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+4294967295");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	u32string = u32_to_u32string(0U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1");
	u32string = u32_to_u32string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+99999");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+2147483647");
	u32string = u32_to_u32string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u32string.content, "+4294967295");
}

TEST(tests_for_uint32_base_16_output, "Tests for 32-bit unsigned integer-to-string conversion with base 16 output")
{
	const int base16 = 16;
	int_to_string_option_type options = int_to_string_option_default;
	u32string_type u32string = {{0}};

	u32string = u32_to_u32string(0U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = u32_to_u32string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "1869f");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "7fffffff");
	u32string = u32_to_u32string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "ffffffff");

	options = int_to_string_option_uppercase;
	u32string = u32_to_u32string(0U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = u32_to_u32string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "1869F");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "7FFFFFFF");
	u32string = u32_to_u32string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "FFFFFFFF");

	options = int_to_string_option_add_prefix;
	u32string = u32_to_u32string(0U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0x0");
	u32string = u32_to_u32string(1U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0x1");
	u32string = u32_to_u32string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0x1869f");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0x7fffffff");

	options = int_to_string_option_add_plus_sign;
	u32string = u32_to_u32string(0U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1");
	u32string = u32_to_u32string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1869f");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+7fffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u32string = u32_to_u32string(0U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0x0");
	u32string = u32_to_u32string(1U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0x1");
	u32string = u32_to_u32string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0x1869f");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0x7fffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u32string = u32_to_u32string(0U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0x0");
	u32string = u32_to_u32string(1U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0x1");
	u32string = u32_to_u32string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0x1869f");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0x7fffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	u32string = u32_to_u32string(0U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0X0");
	u32string = u32_to_u32string(1U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0X1");
	u32string = u32_to_u32string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0X1869F");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0X7FFFFFFF");
}

TEST(tests_for_int64_base_2_output, "Tests for 64-bit signed integer-to-string conversion with base 2 output")
{
	const int base2 = 2;
	int_to_string_option_type options = int_to_string_option_default;
	i64string_type i64string = {{0}};

	i64string = i64_to_i64string(INT64_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1000000000000000000000000000000000000000000000000000000000000000");
	i64string = i64_to_i64string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-10000000000000000000000000000000");
	i64string = i64_to_i64string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-11000011010011111");
	i64string = i64_to_i64string(-1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = i64_to_i64string(99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "11000011010011111");
	i64string = i64_to_i64string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "1111111111111111111111111111111");
	i64string = i64_to_i64string(INT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "111111111111111111111111111111111111111111111111111111111111111");

	options = int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT64_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1000000000000000000000000000000000000000000000000000000000000000");
	i64string = i64_to_i64string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-10000000000000000000000000000000");
	i64string = i64_to_i64string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-11000011010011111");
	i64string = i64_to_i64string(-1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = i64_to_i64string(99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "11000011010011111");
	i64string = i64_to_i64string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "1111111111111111111111111111111");
	i64string = i64_to_i64string(INT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "111111111111111111111111111111111111111111111111111111111111111");

	options = int_to_string_option_add_prefix;
	i64string = i64_to_i64string(INT64_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0b1000000000000000000000000000000000000000000000000000000000000000");
	i64string = i64_to_i64string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0b10000000000000000000000000000000");
	i64string = i64_to_i64string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0b11000011010011111");
	i64string = i64_to_i64string(-1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0b1");
	i64string = i64_to_i64string(0, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "0b0");
	i64string = i64_to_i64string(1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "0b1");
	i64string = i64_to_i64string(99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "0b11000011010011111");
	i64string = i64_to_i64string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "0b1111111111111111111111111111111");
	i64string = i64_to_i64string(INT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "0b111111111111111111111111111111111111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign;
	i64string = i64_to_i64string(INT64_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1000000000000000000000000000000000000000000000000000000000000000");
	i64string = i64_to_i64string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-10000000000000000000000000000000");
	i64string = i64_to_i64string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-11000011010011111");
	i64string = i64_to_i64string(-1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+1");
	i64string = i64_to_i64string(99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+11000011010011111");
	i64string = i64_to_i64string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+1111111111111111111111111111111");
	i64string = i64_to_i64string(INT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+111111111111111111111111111111111111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	i64string = i64_to_i64string(INT64_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0b1000000000000000000000000000000000000000000000000000000000000000");
	i64string = i64_to_i64string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0b10000000000000000000000000000000");
	i64string = i64_to_i64string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0b11000011010011111");
	i64string = i64_to_i64string(-1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0b1");
	i64string = i64_to_i64string(0, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "0b0");
	i64string = i64_to_i64string(1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0b1");
	i64string = i64_to_i64string(99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0b11000011010011111");
	i64string = i64_to_i64string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0b1111111111111111111111111111111");
	i64string = i64_to_i64string(INT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0b111111111111111111111111111111111111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT64_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0B1000000000000000000000000000000000000000000000000000000000000000");
	i64string = i64_to_i64string(INT32_MIN, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0B10000000000000000000000000000000");
	i64string = i64_to_i64string(-99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0B11000011010011111");
	i64string = i64_to_i64string(-1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0B1");
	i64string = i64_to_i64string(0, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "0B0");
	i64string = i64_to_i64string(1, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0B1");
	i64string = i64_to_i64string(99999, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0B11000011010011111");
	i64string = i64_to_i64string(INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0B1111111111111111111111111111111");
	i64string = i64_to_i64string(INT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0B111111111111111111111111111111111111111111111111111111111111111");
}

TEST(tests_for_int64_base_8_output, "Tests for 64-bit signed integer-to-string conversion with base 8 output")
{
	const int base8 = 8;
	int_to_string_option_type options = int_to_string_option_default;
	i64string_type i64string = {{0}};

	i64string = i64_to_i64string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-20000000000");
	i64string = i64_to_i64string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-303237");
	i64string = i64_to_i64string(-1, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = i64_to_i64string(99999, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "303237");
	i64string = i64_to_i64string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "17777777777");

	options = int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-20000000000");
	i64string = i64_to_i64string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-303237");
	i64string = i64_to_i64string(-1, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = i64_to_i64string(99999, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "303237");
	i64string = i64_to_i64string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "17777777777");

	options = int_to_string_option_add_prefix;
	i64string = i64_to_i64string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-020000000000");
	i64string = i64_to_i64string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0303237");
	i64string = i64_to_i64string(-1, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-01");
	i64string = i64_to_i64string(0, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "00");
	i64string = i64_to_i64string(1, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "01");
	i64string = i64_to_i64string(99999, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "0303237");
	i64string = i64_to_i64string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "017777777777");

	options = int_to_string_option_add_plus_sign;
	i64string = i64_to_i64string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-20000000000");
	i64string = i64_to_i64string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-303237");
	i64string = i64_to_i64string(-1, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "+1");
	i64string = i64_to_i64string(99999, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "+303237");
	i64string = i64_to_i64string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "+17777777777");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT32_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-020000000000");
	i64string = i64_to_i64string(-99999, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0303237");
	i64string = i64_to_i64string(-1, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-01");
	i64string = i64_to_i64string(0, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "00");
	i64string = i64_to_i64string(1, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "+01");
	i64string = i64_to_i64string(99999, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0303237");
	i64string = i64_to_i64string(INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "+017777777777");
}

TEST(tests_for_int64_base_10_output, "Tests for 64-bit signed integer-to-string conversion with base 10 output")
{
	const int base10 = 10;
	int_to_string_option_type options = int_to_string_option_default;
	i64string_type i64string = {{0}};

	i64string = i64_to_i64string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-2147483648");
	i64string = i64_to_i64string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-99999");
	i64string = i64_to_i64string(-1, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = i64_to_i64string(99999, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "99999");
	i64string = i64_to_i64string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "2147483647");

	options = int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-2147483648");
	i64string = i64_to_i64string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-99999");
	i64string = i64_to_i64string(-1, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = i64_to_i64string(99999, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "99999");
	i64string = i64_to_i64string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "2147483647");

	options = int_to_string_option_add_prefix;
	i64string = i64_to_i64string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-2147483648");
	i64string = i64_to_i64string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-99999");
	i64string = i64_to_i64string(-1, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = i64_to_i64string(99999, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "99999");
	i64string = i64_to_i64string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "2147483647");

	options = int_to_string_option_add_plus_sign;
	i64string = i64_to_i64string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-2147483648");
	i64string = i64_to_i64string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-99999");
	i64string = i64_to_i64string(-1, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "+1");
	i64string = i64_to_i64string(99999, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "+99999");
	i64string = i64_to_i64string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "+2147483647");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-2147483648");
	i64string = i64_to_i64string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-99999");
	i64string = i64_to_i64string(-1, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "+1");
	i64string = i64_to_i64string(99999, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "+99999");
	i64string = i64_to_i64string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "+2147483647");
}

TEST(tests_for_int64_base_16_output, "Tests for 64-bit signed integer-to-string conversion with base 16 output")
{
	const int base16 = 16;
	int_to_string_option_type options = int_to_string_option_default;
	i64string_type i64string = {{0}};

	i64string = i64_to_i64string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-80000000");
	i64string = i64_to_i64string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1869f");
	i64string = i64_to_i64string(-1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = i64_to_i64string(99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "1869f");
	i64string = i64_to_i64string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "7fffffff");

	options = int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-80000000");
	i64string = i64_to_i64string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1869F");
	i64string = i64_to_i64string(-1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = i64_to_i64string(99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "1869F");
	i64string = i64_to_i64string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "7FFFFFFF");

	options = int_to_string_option_add_prefix;
	i64string = i64_to_i64string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0x80000000");
	i64string = i64_to_i64string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0x1869f");
	i64string = i64_to_i64string(-1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0x1");
	i64string = i64_to_i64string(0, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "0x0");
	i64string = i64_to_i64string(1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "0x1");
	i64string = i64_to_i64string(99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "0x1869f");
	i64string = i64_to_i64string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "0x7fffffff");

	options = int_to_string_option_add_plus_sign;
	i64string = i64_to_i64string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-80000000");
	i64string = i64_to_i64string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1869f");
	i64string = i64_to_i64string(-1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = i64_to_i64string(0, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = i64_to_i64string(1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+1");
	i64string = i64_to_i64string(99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+1869f");
	i64string = i64_to_i64string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+7fffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0X80000000");
	i64string = i64_to_i64string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0X1869F");
	i64string = i64_to_i64string(-1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0X1");
	i64string = i64_to_i64string(0, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "0X0");
	i64string = i64_to_i64string(1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0X1");
	i64string = i64_to_i64string(99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0X1869F");
	i64string = i64_to_i64string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0X7FFFFFFF");
}

TEST(tests_for_uint64_base_2_output, "Tests for 64-bit unsigned integer-to-string conversion with base 2 output")
{
	const int base2 = 2;
	int_to_string_option_type options = int_to_string_option_default;
	u64string_type u64string = {{0}};

	u64string = u64_to_u64string(0U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = u64_to_u64string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "11000011010011111");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "1111111111111111111111111111111");
	u64string = u64_to_u64string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "11111111111111111111111111111111");

	options = int_to_string_option_uppercase;
	u64string = u64_to_u64string(0U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = u64_to_u64string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "11000011010011111");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "1111111111111111111111111111111");
	u64string = u64_to_u64string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "11111111111111111111111111111111");

	options = int_to_string_option_add_prefix;
	u64string = u64_to_u64string(0U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0b0");
	u64string = u64_to_u64string(1U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0b1");
	u64string = u64_to_u64string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0b11000011010011111");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0b1111111111111111111111111111111");
	u64string = u64_to_u64string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0b11111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign;
	u64string = u64_to_u64string(0U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1");
	u64string = u64_to_u64string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+11000011010011111");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1111111111111111111111111111111");
	u64string = u64_to_u64string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+11111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	u64string = u64_to_u64string(0U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0B0");
	u64string = u64_to_u64string(1U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0B1");
	u64string = u64_to_u64string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0B11000011010011111");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0B1111111111111111111111111111111");
	u64string = u64_to_u64string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0B11111111111111111111111111111111");
}

TEST(tests_for_uint64_base_8_output, "Tests for 64-bit unsigned integer-to-string conversion with base 8 output")
{
	const int base8 = 8;
	int_to_string_option_type options = int_to_string_option_default;
	u64string_type u64string = {{0}};

	u64string = u64_to_u64string(0U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = u64_to_u64string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "303237");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "17777777777");
	u64string = u64_to_u64string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "37777777777");

	options = int_to_string_option_uppercase;
	u64string = u64_to_u64string(0U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = u64_to_u64string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "303237");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "17777777777");
	u64string = u64_to_u64string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "37777777777");

	options = int_to_string_option_add_prefix;
	u64string = u64_to_u64string(0U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "00");
	u64string = u64_to_u64string(1U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "01");
	u64string = u64_to_u64string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "0303237");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "017777777777");
	u64string = u64_to_u64string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "037777777777");

	options = int_to_string_option_add_plus_sign;
	u64string = u64_to_u64string(0U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1");
	u64string = u64_to_u64string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+303237");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+17777777777");
	u64string = u64_to_u64string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+37777777777");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	u64string = u64_to_u64string(0U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "00");
	u64string = u64_to_u64string(1U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+01");
	u64string = u64_to_u64string(99999U, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0303237");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+017777777777");
	u64string = u64_to_u64string(UINT32_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+037777777777");
}

TEST(tests_for_uint64_base_10_output, "Tests for 64-bit unsigned integer-to-string conversion with base 10 output")
{
	const int base10 = 10;
	int_to_string_option_type options = int_to_string_option_default;
	u64string_type u64string = {{0}};

	u64string = u64_to_u64string(0U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = u64_to_u64string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "99999");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "2147483647");
	u64string = u64_to_u64string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "4294967295");

	options = int_to_string_option_uppercase;
	u64string = u64_to_u64string(0U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = u64_to_u64string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "99999");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "2147483647");
	u64string = u64_to_u64string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "4294967295");

	options = int_to_string_option_add_prefix;
	u64string = u64_to_u64string(0U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = u64_to_u64string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "99999");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "2147483647");
	u64string = u64_to_u64string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "4294967295");

	options = int_to_string_option_add_plus_sign;
	u64string = u64_to_u64string(0U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1");
	u64string = u64_to_u64string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+99999");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+2147483647");
	u64string = u64_to_u64string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+4294967295");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	u64string = u64_to_u64string(0U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1");
	u64string = u64_to_u64string(99999U, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+99999");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+2147483647");
	u64string = u64_to_u64string(UINT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+4294967295");
}

TEST(tests_for_uint64_base_16_output, "Tests for 64-bit unsigned integer-to-string conversion with base 16 output")
{
	const int base16 = 16;
	int_to_string_option_type options = int_to_string_option_default;
	u64string_type u64string = {{0}};

	u64string = u64_to_u64string(0U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = u64_to_u64string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "1869f");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "7fffffff");
	u64string = u64_to_u64string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "ffffffff");

	options = int_to_string_option_uppercase;
	u64string = u64_to_u64string(0U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = u64_to_u64string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "1869F");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "7FFFFFFF");
	u64string = u64_to_u64string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "FFFFFFFF");

	options = int_to_string_option_add_prefix;
	u64string = u64_to_u64string(0U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0x0");
	u64string = u64_to_u64string(1U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0x1");
	u64string = u64_to_u64string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0x1869f");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0x7fffffff");

	options = int_to_string_option_add_plus_sign;
	u64string = u64_to_u64string(0U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1");
	u64string = u64_to_u64string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1869f");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+7fffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	u64string = u64_to_u64string(0U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0X0");
	u64string = u64_to_u64string(1U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0X1");
	u64string = u64_to_u64string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0X1869F");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0X7FFFFFFF");
}

/* TODO: Add more tests in the future */

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		tests_for_int32_base_2_output,
		tests_for_int32_base_8_output,
		tests_for_int32_base_10_output,
		tests_for_int32_base_16_output,
		tests_for_uint32_base_2_output,
		tests_for_uint32_base_8_output,
		tests_for_uint32_base_10_output,
		tests_for_uint32_base_16_output,
		tests_for_int64_base_2_output,
		tests_for_int64_base_8_output,
		tests_for_int64_base_10_output,
		tests_for_int64_base_16_output,
		tests_for_uint64_base_2_output,
		tests_for_uint64_base_8_output,
		tests_for_uint64_base_10_output,
		tests_for_uint64_base_16_output
	};

	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
