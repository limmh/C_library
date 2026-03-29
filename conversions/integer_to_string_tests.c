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

TEST(tests_for_int32_base_2_string_output, "Tests for 32-bit signed integer-to-string conversion with base 2 output")
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

TEST(tests_for_int32_base_8_string_output, "Tests for 32-bit signed integer-to-string conversion with base 8 output")
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

TEST(tests_for_int32_base_10_string_output, "Tests for 32-bit signed integer-to-string conversion with base 10 output")
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

TEST(tests_for_int32_base_16_string_output, "Tests for 32-bit signed integer-to-string conversion with base 16 output")
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

TEST(tests_for_uint32_base_2_string_output, "Tests for 32-bit unsigned integer-to-string conversion with base 2 output")
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

TEST(tests_for_uint32_base_8_string_output, "Tests for 32-bit unsigned integer-to-string conversion with base 8 output")
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

TEST(tests_for_uint32_base_10_string_output, "Tests for 32-bit unsigned integer-to-string conversion with base 10 output")
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

TEST(tests_for_uint32_base_16_string_output, "Tests for 32-bit unsigned integer-to-string conversion with base 16 output")
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
	u32string = u32_to_u32string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0xffffffff");

	options = int_to_string_option_add_plus_sign;
	u32string = u32_to_u32string(0U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = u32_to_u32string(1U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1");
	u32string = u32_to_u32string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+1869f");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+7fffffff");
	u32string = u32_to_u32string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+ffffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u32string = u32_to_u32string(0U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0x0");
	u32string = u32_to_u32string(1U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0x1");
	u32string = u32_to_u32string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0x1869f");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0x7fffffff");
	u32string = u32_to_u32string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0xffffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	u32string = u32_to_u32string(0U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "0X0");
	u32string = u32_to_u32string(1U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0X1");
	u32string = u32_to_u32string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0X1869F");
	u32string = u32_to_u32string((uint32_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0X7FFFFFFF");
	u32string = u32_to_u32string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u32string.content, "+0XFFFFFFFF");
}

TEST(tests_for_int64_base_2_string_output, "Tests for 64-bit signed integer-to-string conversion with base 2 output")
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

TEST(tests_for_int64_base_8_string_output, "Tests for 64-bit signed integer-to-string conversion with base 8 output")
{
	const int base8 = 8;
	int_to_string_option_type options = int_to_string_option_default;
	i64string_type i64string = {{0}};

	i64string = i64_to_i64string(INT64_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1000000000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "777777777777777777777");

	options = int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT64_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1000000000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "777777777777777777777");

	options = int_to_string_option_add_prefix;
	i64string = i64_to_i64string(INT64_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-01000000000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "0777777777777777777777");

	options = int_to_string_option_add_plus_sign;
	i64string = i64_to_i64string(INT64_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-1000000000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "+777777777777777777777");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	i64string = i64_to_i64string(INT64_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-01000000000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0777777777777777777777");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT64_MIN, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "-01000000000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0777777777777777777777");
}

TEST(tests_for_int64_base_10_string_output, "Tests for 64-bit signed integer-to-string conversion with base 10 output")
{
	const int base10 = 10;
	int_to_string_option_type options = int_to_string_option_default;
	i64string_type i64string = {{0}};

	i64string = i64_to_i64string(INT64_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-9223372036854775808");
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
	i64string = i64_to_i64string(INT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "9223372036854775807");

	options = int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT64_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-9223372036854775808");
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
	i64string = i64_to_i64string(INT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "9223372036854775807");

	options = int_to_string_option_add_prefix;
	i64string = i64_to_i64string(INT64_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-9223372036854775808");
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
	i64string = i64_to_i64string(INT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "9223372036854775807");

	options = int_to_string_option_add_plus_sign;
	i64string = i64_to_i64string(INT64_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-9223372036854775808");
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
	i64string = i64_to_i64string(INT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "+9223372036854775807");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	i64string = i64_to_i64string(INT64_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-9223372036854775808");
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
	i64string = i64_to_i64string(INT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "+9223372036854775807");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT64_MIN, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "-9223372036854775808");
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
	i64string = i64_to_i64string(INT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(i64string.content, "+9223372036854775807");
}

TEST(tests_for_int64_base_16_string_output, "Tests for 64-bit signed integer-to-string conversion with base 16 output")
{
	const int base16 = 16;
	int_to_string_option_type options = int_to_string_option_default;
	i64string_type i64string = {{0}};

	i64string = i64_to_i64string(INT64_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-8000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "7fffffffffffffff");

	options = int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT64_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-8000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "7FFFFFFFFFFFFFFF");

	options = int_to_string_option_add_prefix;
	i64string = i64_to_i64string(INT64_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0x8000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "0x7fffffffffffffff");

	options = int_to_string_option_add_plus_sign;
	i64string = i64_to_i64string(INT64_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-8000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+7fffffffffffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	i64string = i64_to_i64string(INT64_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0x8000000000000000");
	i64string = i64_to_i64string(INT32_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0x80000000");
	i64string = i64_to_i64string(-99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0x1869f");
	i64string = i64_to_i64string(-1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0x1");
	i64string = i64_to_i64string(0, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "0x0");
	i64string = i64_to_i64string(1, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0x1");
	i64string = i64_to_i64string(99999, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0x1869f");
	i64string = i64_to_i64string(INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0x7fffffff");
	i64string = i64_to_i64string(INT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0x7fffffffffffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i64string = i64_to_i64string(INT64_MIN, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "-0X8000000000000000");
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
	i64string = i64_to_i64string(INT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(i64string.content, "+0X7FFFFFFFFFFFFFFF");
}

TEST(tests_for_uint64_base_2_string_output, "Tests for 64-bit unsigned integer-to-string conversion with base 2 output")
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
	u64string = u64_to_u64string(UINT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "1111111111111111111111111111111111111111111111111111111111111111");

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
	u64string = u64_to_u64string(UINT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "1111111111111111111111111111111111111111111111111111111111111111");

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
	u64string = u64_to_u64string(UINT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0b1111111111111111111111111111111111111111111111111111111111111111");
	
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
	u64string = u64_to_u64string(UINT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1111111111111111111111111111111111111111111111111111111111111111");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u64string = u64_to_u64string(0U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "0b0");
	u64string = u64_to_u64string(1U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0b1");
	u64string = u64_to_u64string(99999U, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0b11000011010011111");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0b1111111111111111111111111111111");
	u64string = u64_to_u64string(UINT32_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0b11111111111111111111111111111111");
	u64string = u64_to_u64string(UINT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0b1111111111111111111111111111111111111111111111111111111111111111");

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
	u64string = u64_to_u64string(UINT64_MAX, base2, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0B1111111111111111111111111111111111111111111111111111111111111111");
}

TEST(tests_for_uint64_base_8_string_output, "Tests for 64-bit unsigned integer-to-string conversion with base 8 output")
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
	u64string = u64_to_u64string(UINT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "1777777777777777777777");

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
	u64string = u64_to_u64string(UINT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "1777777777777777777777");

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
	u64string = u64_to_u64string(UINT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "01777777777777777777777");

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
	u64string = u64_to_u64string(UINT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1777777777777777777777");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
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
	u64string = u64_to_u64string(UINT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+01777777777777777777777");

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
	u64string = u64_to_u64string(UINT64_MAX, base8, options);
	ASSERT_STRING_EQUAL(u64string.content, "+01777777777777777777777");
}

TEST(tests_for_uint64_base_10_string_output, "Tests for 64-bit unsigned integer-to-string conversion with base 10 output")
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
	u64string = u64_to_u64string(UINT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "18446744073709551615");

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
	u64string = u64_to_u64string(UINT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "18446744073709551615");

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
	u64string = u64_to_u64string(UINT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "18446744073709551615");

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
	u64string = u64_to_u64string(UINT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+18446744073709551615");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
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
	u64string = u64_to_u64string(UINT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+18446744073709551615");

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
	u64string = u64_to_u64string(UINT64_MAX, base10, options);
	ASSERT_STRING_EQUAL(u64string.content, "+18446744073709551615");
}

TEST(tests_for_uint64_base_16_string_output, "Tests for 64-bit unsigned integer-to-string conversion with base 16 output")
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
	u64string = u64_to_u64string(UINT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "ffffffffffffffff");

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
	u64string = u64_to_u64string(UINT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "FFFFFFFFFFFFFFFF");

	options = int_to_string_option_add_prefix;
	u64string = u64_to_u64string(0U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0x0");
	u64string = u64_to_u64string(1U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0x1");
	u64string = u64_to_u64string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0x1869f");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0x7fffffff");
	u64string = u64_to_u64string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0xffffffff");
	u64string = u64_to_u64string(UINT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0xffffffffffffffff");

	options = int_to_string_option_add_plus_sign;
	u64string = u64_to_u64string(0U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = u64_to_u64string(1U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1");
	u64string = u64_to_u64string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+1869f");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+7fffffff");
	u64string = u64_to_u64string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+ffffffff");
	u64string = u64_to_u64string(UINT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+ffffffffffffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_lowercase;
	u64string = u64_to_u64string(0U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0x0");
	u64string = u64_to_u64string(1U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0x1");
	u64string = u64_to_u64string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0x1869f");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0x7fffffff");
	u64string = u64_to_u64string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0xffffffff");
	u64string = u64_to_u64string(UINT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0xffffffffffffffff");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	u64string = u64_to_u64string(0U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "0X0");
	u64string = u64_to_u64string(1U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0X1");
	u64string = u64_to_u64string(99999U, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0X1869F");
	u64string = u64_to_u64string((uint64_t) INT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0X7FFFFFFF");
	u64string = u64_to_u64string(UINT32_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0XFFFFFFFF");
	u64string = u64_to_u64string(UINT64_MAX, base16, options);
	ASSERT_STRING_EQUAL(u64string.content, "+0XFFFFFFFFFFFFFFFF");
}

TEST(tests_for_int32_base_2_to_string_functions, "Tests for base 2 32-bit signed integer-to-string conversion functions")
{
	i32string_type i32string = {{0}};

	i32string = base2_i32_to_i32string(INT32_MIN);
	ASSERT_STRING_EQUAL(i32string.content, "-10000000000000000000000000000000");
	i32string = base2_i32_to_i32string(-99999);
	ASSERT_STRING_EQUAL(i32string.content, "-11000011010011111");
	i32string = base2_i32_to_i32string(-1);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = base2_i32_to_i32string(0);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = base2_i32_to_i32string(1);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = base2_i32_to_i32string(99999);
	ASSERT_STRING_EQUAL(i32string.content, "11000011010011111");
	i32string = base2_i32_to_i32string(INT32_MAX);
	ASSERT_STRING_EQUAL(i32string.content, "1111111111111111111111111111111");

	i32string = base2_i32_to_i32string_with_prefix(INT32_MIN);
	ASSERT_STRING_EQUAL(i32string.content, "-0b10000000000000000000000000000000");
	i32string = base2_i32_to_i32string_with_prefix(-99999);
	ASSERT_STRING_EQUAL(i32string.content, "-0b11000011010011111");
	i32string = base2_i32_to_i32string_with_prefix(-1);
	ASSERT_STRING_EQUAL(i32string.content, "-0b1");
	i32string = base2_i32_to_i32string_with_prefix(0);
	ASSERT_STRING_EQUAL(i32string.content, "0b0");
	i32string = base2_i32_to_i32string_with_prefix(1);
	ASSERT_STRING_EQUAL(i32string.content, "0b1");
	i32string = base2_i32_to_i32string_with_prefix(99999);
	ASSERT_STRING_EQUAL(i32string.content, "0b11000011010011111");
	i32string = base2_i32_to_i32string_with_prefix(INT32_MAX);
	ASSERT_STRING_EQUAL(i32string.content, "0b1111111111111111111111111111111");

	i32string = base2_i32_to_i32string_with_prefix_in_uppercase(INT32_MIN);
	ASSERT_STRING_EQUAL(i32string.content, "-0B10000000000000000000000000000000");
	i32string = base2_i32_to_i32string_with_prefix_in_uppercase(-99999);
	ASSERT_STRING_EQUAL(i32string.content, "-0B11000011010011111");
	i32string = base2_i32_to_i32string_with_prefix_in_uppercase(-1);
	ASSERT_STRING_EQUAL(i32string.content, "-0B1");
	i32string = base2_i32_to_i32string_with_prefix_in_uppercase(0);
	ASSERT_STRING_EQUAL(i32string.content, "0B0");
	i32string = base2_i32_to_i32string_with_prefix_in_uppercase(1);
	ASSERT_STRING_EQUAL(i32string.content, "0B1");
	i32string = base2_i32_to_i32string_with_prefix_in_uppercase(99999);
	ASSERT_STRING_EQUAL(i32string.content, "0B11000011010011111");
	i32string = base2_i32_to_i32string_with_prefix_in_uppercase(INT32_MAX);
	ASSERT_STRING_EQUAL(i32string.content, "0B1111111111111111111111111111111");
}

TEST(tests_for_uint32_base_2_to_string_functions, "Tests for base 2 32-bit unsigned integer-to-string conversion functions")
{
	u32string_type u32string = {{0}};

	u32string = base2_u32_to_u32string(0U);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = base2_u32_to_u32string(1U);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = base2_u32_to_u32string(99999U);
	ASSERT_STRING_EQUAL(u32string.content, "11000011010011111");
	u32string = base2_u32_to_u32string((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "1111111111111111111111111111111");
	u32string = base2_u32_to_u32string(UINT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "11111111111111111111111111111111");

	u32string = base2_u32_to_u32string_with_prefix(0U);
	ASSERT_STRING_EQUAL(u32string.content, "0b0");
	u32string = base2_u32_to_u32string_with_prefix(1U);
	ASSERT_STRING_EQUAL(u32string.content, "0b1");
	u32string = base2_u32_to_u32string_with_prefix(99999U);
	ASSERT_STRING_EQUAL(u32string.content, "0b11000011010011111");
	u32string = base2_u32_to_u32string_with_prefix((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "0b1111111111111111111111111111111");
	u32string = base2_u32_to_u32string_with_prefix(UINT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "0b11111111111111111111111111111111");

	u32string = base2_u32_to_u32string_with_prefix_in_uppercase(0U);
	ASSERT_STRING_EQUAL(u32string.content, "0B0");
	u32string = base2_u32_to_u32string_with_prefix_in_uppercase(1U);
	ASSERT_STRING_EQUAL(u32string.content, "0B1");
	u32string = base2_u32_to_u32string_with_prefix_in_uppercase(99999U);
	ASSERT_STRING_EQUAL(u32string.content, "0B11000011010011111");
	u32string = base2_u32_to_u32string_with_prefix_in_uppercase((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "0B1111111111111111111111111111111");
	u32string = base2_u32_to_u32string_with_prefix_in_uppercase(UINT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "0B11111111111111111111111111111111");
}

TEST(tests_for_int64_base_2_to_string_functions, "Tests for base 2 64-bit signed integer-to-string conversion functions")
{
	i64string_type i64string = {{0}};

	i64string = base2_i64_to_i64string(INT64_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-1000000000000000000000000000000000000000000000000000000000000000");
	i64string = base2_i64_to_i64string(INT32_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-10000000000000000000000000000000");
	i64string = base2_i64_to_i64string(-99999);
	ASSERT_STRING_EQUAL(i64string.content, "-11000011010011111");
	i64string = base2_i64_to_i64string(-1);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = base2_i64_to_i64string(0);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = base2_i64_to_i64string(1);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = base2_i64_to_i64string(99999);
	ASSERT_STRING_EQUAL(i64string.content, "11000011010011111");
	i64string = base2_i64_to_i64string(INT32_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "1111111111111111111111111111111");
	i64string = base2_i64_to_i64string(INT64_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "111111111111111111111111111111111111111111111111111111111111111");

	i64string = base2_i64_to_i64string_with_prefix(INT64_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-0b1000000000000000000000000000000000000000000000000000000000000000");
	i64string = base2_i64_to_i64string_with_prefix(INT32_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-0b10000000000000000000000000000000");
	i64string = base2_i64_to_i64string_with_prefix(-99999);
	ASSERT_STRING_EQUAL(i64string.content, "-0b11000011010011111");
	i64string = base2_i64_to_i64string_with_prefix(-1);
	ASSERT_STRING_EQUAL(i64string.content, "-0b1");
	i64string = base2_i64_to_i64string_with_prefix(0);
	ASSERT_STRING_EQUAL(i64string.content, "0b0");
	i64string = base2_i64_to_i64string_with_prefix(1);
	ASSERT_STRING_EQUAL(i64string.content, "0b1");
	i64string = base2_i64_to_i64string_with_prefix(99999);
	ASSERT_STRING_EQUAL(i64string.content, "0b11000011010011111");
	i64string = base2_i64_to_i64string_with_prefix(INT32_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "0b1111111111111111111111111111111");
	i64string = base2_i64_to_i64string_with_prefix(INT64_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "0b111111111111111111111111111111111111111111111111111111111111111");

	i64string = base2_i64_to_i64string_with_prefix_in_uppercase(INT64_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-0B1000000000000000000000000000000000000000000000000000000000000000");
	i64string = base2_i64_to_i64string_with_prefix_in_uppercase(INT32_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-0B10000000000000000000000000000000");
	i64string = base2_i64_to_i64string_with_prefix_in_uppercase(-99999);
	ASSERT_STRING_EQUAL(i64string.content, "-0B11000011010011111");
	i64string = base2_i64_to_i64string_with_prefix_in_uppercase(-1);
	ASSERT_STRING_EQUAL(i64string.content, "-0B1");
	i64string = base2_i64_to_i64string_with_prefix_in_uppercase(0);
	ASSERT_STRING_EQUAL(i64string.content, "0B0");
	i64string = base2_i64_to_i64string_with_prefix_in_uppercase(1);
	ASSERT_STRING_EQUAL(i64string.content, "0B1");
	i64string = base2_i64_to_i64string_with_prefix_in_uppercase(99999);
	ASSERT_STRING_EQUAL(i64string.content, "0B11000011010011111");
	i64string = base2_i64_to_i64string_with_prefix_in_uppercase(INT32_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "0B1111111111111111111111111111111");
	i64string = base2_i64_to_i64string_with_prefix_in_uppercase(INT64_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "0B111111111111111111111111111111111111111111111111111111111111111");
}

TEST(tests_for_uint64_base_2_to_string_functions, "Tests for base 2 64-bit unsigned integer-to-string conversion functions")
{
	u64string_type u64string = {{0}};

	u64string = base2_u64_to_u64string(0U);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = base2_u64_to_u64string(1U);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = base2_u64_to_u64string(99999U);
	ASSERT_STRING_EQUAL(u64string.content, "11000011010011111");
	u64string = base2_u64_to_u64string((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "1111111111111111111111111111111");
	u64string = base2_u64_to_u64string(UINT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "11111111111111111111111111111111");
	u64string = base2_u64_to_u64string(UINT64_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "1111111111111111111111111111111111111111111111111111111111111111");

	u64string = base2_u64_to_u64string_with_prefix(0U);
	ASSERT_STRING_EQUAL(u64string.content, "0b0");
	u64string = base2_u64_to_u64string_with_prefix(1U);
	ASSERT_STRING_EQUAL(u64string.content, "0b1");
	u64string = base2_u64_to_u64string_with_prefix(99999U);
	ASSERT_STRING_EQUAL(u64string.content, "0b11000011010011111");
	u64string = base2_u64_to_u64string_with_prefix((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0b1111111111111111111111111111111");
	u64string = base2_u64_to_u64string_with_prefix(UINT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0b11111111111111111111111111111111");
	u64string = base2_u64_to_u64string_with_prefix(UINT64_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0b1111111111111111111111111111111111111111111111111111111111111111");

	u64string = base2_u64_to_u64string_with_prefix_in_uppercase(0U);
	ASSERT_STRING_EQUAL(u64string.content, "0B0");
	u64string = base2_u64_to_u64string_with_prefix_in_uppercase(1U);
	ASSERT_STRING_EQUAL(u64string.content, "0B1");
	u64string = base2_u64_to_u64string_with_prefix_in_uppercase(99999U);
	ASSERT_STRING_EQUAL(u64string.content, "0B11000011010011111");
	u64string = base2_u64_to_u64string_with_prefix_in_uppercase((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0B1111111111111111111111111111111");
	u64string = base2_u64_to_u64string_with_prefix_in_uppercase(UINT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0B11111111111111111111111111111111");
	u64string = base2_u64_to_u64string_with_prefix_in_uppercase(UINT64_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0B1111111111111111111111111111111111111111111111111111111111111111");
}

TEST(tests_for_int32_base_8_to_string_functions, "Tests for base 8 32-bit signed integer-to-string conversion functions")
{
	i32string_type i32string = {{0}};

	i32string = base8_i32_to_i32string(INT32_MIN);
	ASSERT_STRING_EQUAL(i32string.content, "-20000000000");
	i32string = base8_i32_to_i32string(-99999);
	ASSERT_STRING_EQUAL(i32string.content, "-303237");
	i32string = base8_i32_to_i32string(-1);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = base8_i32_to_i32string(0);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = base8_i32_to_i32string(1);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = base8_i32_to_i32string(99999);
	ASSERT_STRING_EQUAL(i32string.content, "303237");
	i32string = base8_i32_to_i32string(INT32_MAX);
	ASSERT_STRING_EQUAL(i32string.content, "17777777777");

	i32string = base8_i32_to_i32string_with_prefix(INT32_MIN);
	ASSERT_STRING_EQUAL(i32string.content, "-020000000000");
	i32string = base8_i32_to_i32string_with_prefix(-99999);
	ASSERT_STRING_EQUAL(i32string.content, "-0303237");
	i32string = base8_i32_to_i32string_with_prefix(-1);
	ASSERT_STRING_EQUAL(i32string.content, "-01");
	i32string = base8_i32_to_i32string_with_prefix(0);
	ASSERT_STRING_EQUAL(i32string.content, "00");
	i32string = base8_i32_to_i32string_with_prefix(1);
	ASSERT_STRING_EQUAL(i32string.content, "01");
	i32string = base8_i32_to_i32string_with_prefix(99999);
	ASSERT_STRING_EQUAL(i32string.content, "0303237");
	i32string = base8_i32_to_i32string_with_prefix(INT32_MAX);
	ASSERT_STRING_EQUAL(i32string.content, "017777777777");
}

TEST(tests_for_uint32_base_8_to_string_functions, "Tests for base 8 32-bit unsigned integer-to-string conversion functions")
{
	u32string_type u32string = {{0}};

	u32string = base8_u32_to_u32string(0U);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = base8_u32_to_u32string(1U);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = base8_u32_to_u32string(99999U);
	ASSERT_STRING_EQUAL(u32string.content, "303237");
	u32string = base8_u32_to_u32string((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "17777777777");
	u32string = base8_u32_to_u32string(UINT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "37777777777");

	u32string = base8_u32_to_u32string_with_prefix(0U);
	ASSERT_STRING_EQUAL(u32string.content, "00");
	u32string = base8_u32_to_u32string_with_prefix(1U);
	ASSERT_STRING_EQUAL(u32string.content, "01");
	u32string = base8_u32_to_u32string_with_prefix(99999U);
	ASSERT_STRING_EQUAL(u32string.content, "0303237");
	u32string = base8_u32_to_u32string_with_prefix((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "017777777777");
	u32string = base8_u32_to_u32string_with_prefix(UINT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "037777777777");
}

TEST(tests_for_int64_base_8_to_string_functions, "Tests for base 8 64-bit signed integer-to-string conversion functions")
{
	i64string_type i64string = {{0}};

	i64string = base8_i64_to_i64string(INT64_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-1000000000000000000000");
	i64string = base8_i64_to_i64string(INT32_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-20000000000");
	i64string = base8_i64_to_i64string(-99999);
	ASSERT_STRING_EQUAL(i64string.content, "-303237");
	i64string = base8_i64_to_i64string(-1);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = base8_i64_to_i64string(0);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = base8_i64_to_i64string(1);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = base8_i64_to_i64string(99999);
	ASSERT_STRING_EQUAL(i64string.content, "303237");
	i64string = base8_i64_to_i64string(INT32_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "17777777777");
	i64string = base8_i64_to_i64string(INT64_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "777777777777777777777");

	i64string = base8_i64_to_i64string_with_prefix(INT64_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-01000000000000000000000");
	i64string = base8_i64_to_i64string_with_prefix(INT32_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-020000000000");
	i64string = base8_i64_to_i64string_with_prefix(-99999);
	ASSERT_STRING_EQUAL(i64string.content, "-0303237");
	i64string = base8_i64_to_i64string_with_prefix(-1);
	ASSERT_STRING_EQUAL(i64string.content, "-01");
	i64string = base8_i64_to_i64string_with_prefix(0);
	ASSERT_STRING_EQUAL(i64string.content, "00");
	i64string = base8_i64_to_i64string_with_prefix(1);
	ASSERT_STRING_EQUAL(i64string.content, "01");
	i64string = base8_i64_to_i64string_with_prefix(99999);
	ASSERT_STRING_EQUAL(i64string.content, "0303237");
	i64string = base8_i64_to_i64string_with_prefix(INT32_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "017777777777");
	i64string = base8_i64_to_i64string_with_prefix(INT64_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "0777777777777777777777");
}

TEST(tests_for_uint64_base_8_to_string_functions, "Tests for base 8 64-bit unsigned integer-to-string conversion functions")
{
	u64string_type u64string = {{0}};

	u64string = base8_u64_to_u64string(0U);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = base8_u64_to_u64string(1U);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = base8_u64_to_u64string(99999U);
	ASSERT_STRING_EQUAL(u64string.content, "303237");
	u64string = base8_u64_to_u64string((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "17777777777");
	u64string = base8_u64_to_u64string(UINT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "37777777777");
	u64string = base8_u64_to_u64string(UINT64_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "1777777777777777777777");

	u64string = base8_u64_to_u64string_with_prefix(0U);
	ASSERT_STRING_EQUAL(u64string.content, "00");
	u64string = base8_u64_to_u64string_with_prefix(1U);
	ASSERT_STRING_EQUAL(u64string.content, "01");
	u64string = base8_u64_to_u64string_with_prefix(99999U);
	ASSERT_STRING_EQUAL(u64string.content, "0303237");
	u64string = base8_u64_to_u64string_with_prefix((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "017777777777");
	u64string = base8_u64_to_u64string_with_prefix(UINT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "037777777777");
	u64string = base8_u64_to_u64string_with_prefix(UINT64_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "01777777777777777777777");
}

TEST(tests_for_int32_base_10_to_string_functions, "Tests for base 10 32-bit signed integer-to-string conversion functions")
{
	i32string_type i32string = {{0}};

	i32string = base10_i32_to_i32string(INT32_MIN);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = base10_i32_to_i32string(-99999);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = base10_i32_to_i32string(-1);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = base10_i32_to_i32string(0);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = base10_i32_to_i32string(1);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = base10_i32_to_i32string(99999);
	ASSERT_STRING_EQUAL(i32string.content, "99999");
	i32string = base10_i32_to_i32string(INT32_MAX);
	ASSERT_STRING_EQUAL(i32string.content, "2147483647");
}

TEST(tests_for_uint32_base_10_to_string_functions, "Tests for base 10 32-bit unsigned integer-to-string conversion functions")
{
	u32string_type u32string = {{0}};

	u32string = base10_u32_to_u32string(0U);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = base10_u32_to_u32string(1U);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = base10_u32_to_u32string(99999U);
	ASSERT_STRING_EQUAL(u32string.content, "99999");
	u32string = base10_u32_to_u32string((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "2147483647");
	u32string = base10_u32_to_u32string(UINT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "4294967295");
}

TEST(tests_for_int64_base_10_to_string_functions, "Tests for base 10 64-bit signed integer-to-string conversion functions")
{
	i64string_type i64string = {{0}};

	i64string = base10_i64_to_i64string(INT64_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-9223372036854775808");
	i64string = base10_i64_to_i64string(INT32_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-2147483648");
	i64string = base10_i64_to_i64string(-99999);
	ASSERT_STRING_EQUAL(i64string.content, "-99999");
	i64string = base10_i64_to_i64string(-1);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = base10_i64_to_i64string(0);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = base10_i64_to_i64string(1);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = base10_i64_to_i64string(99999);
	ASSERT_STRING_EQUAL(i64string.content, "99999");
	i64string = base10_i64_to_i64string(INT32_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "2147483647");
	i64string = base10_i64_to_i64string(INT64_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "9223372036854775807");
}

TEST(tests_for_uint64_base_10_to_string_functions, "Tests for base 10 64-bit unsigned integer-to-string conversion functions")
{
	u64string_type u64string = {{0}};

	u64string = base10_u64_to_u64string(0U);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = base10_u64_to_u64string(1U);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = base10_u64_to_u64string(99999U);
	ASSERT_STRING_EQUAL(u64string.content, "99999");
	u64string = base10_u64_to_u64string((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "2147483647");
	u64string = base10_u64_to_u64string(UINT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "4294967295");
	u64string = base10_u64_to_u64string(UINT64_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "18446744073709551615");
}

TEST(tests_for_int32_base_16_to_string_functions, "Tests for base 16 32-bit signed integer-to-string conversion functions")
{
	i32string_type i32string = {{0}};

	i32string = base16_i32_to_i32string(INT32_MIN);
	ASSERT_STRING_EQUAL(i32string.content, "-80000000");
	i32string = base16_i32_to_i32string(-99999);
	ASSERT_STRING_EQUAL(i32string.content, "-1869f");
	i32string = base16_i32_to_i32string(-1);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = base16_i32_to_i32string(0);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = base16_i32_to_i32string(1);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = base16_i32_to_i32string(99999);
	ASSERT_STRING_EQUAL(i32string.content, "1869f");
	i32string = base16_i32_to_i32string(INT32_MAX);
	ASSERT_STRING_EQUAL(i32string.content, "7fffffff");

	i32string = base16_i32_to_i32string_in_uppercase(INT32_MIN);
	ASSERT_STRING_EQUAL(i32string.content, "-80000000");
	i32string = base16_i32_to_i32string_in_uppercase(-99999);
	ASSERT_STRING_EQUAL(i32string.content, "-1869F");
	i32string = base16_i32_to_i32string_in_uppercase(-1);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = base16_i32_to_i32string_in_uppercase(0);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = base16_i32_to_i32string_in_uppercase(1);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = base16_i32_to_i32string_in_uppercase(99999);
	ASSERT_STRING_EQUAL(i32string.content, "1869F");
	i32string = base16_i32_to_i32string_in_uppercase(INT32_MAX);
	ASSERT_STRING_EQUAL(i32string.content, "7FFFFFFF");

	i32string = base16_i32_to_i32string_with_prefix(INT32_MIN);
	ASSERT_STRING_EQUAL(i32string.content, "-0x80000000");
	i32string = base16_i32_to_i32string_with_prefix(-99999);
	ASSERT_STRING_EQUAL(i32string.content, "-0x1869f");
	i32string = base16_i32_to_i32string_with_prefix(-1);
	ASSERT_STRING_EQUAL(i32string.content, "-0x1");
	i32string = base16_i32_to_i32string_with_prefix(0);
	ASSERT_STRING_EQUAL(i32string.content, "0x0");
	i32string = base16_i32_to_i32string_with_prefix(1);
	ASSERT_STRING_EQUAL(i32string.content, "0x1");
	i32string = base16_i32_to_i32string_with_prefix(99999);
	ASSERT_STRING_EQUAL(i32string.content, "0x1869f");
	i32string = base16_i32_to_i32string_with_prefix(INT32_MAX);
	ASSERT_STRING_EQUAL(i32string.content, "0x7fffffff");

	i32string = base16_i32_to_i32string_with_prefix_in_uppercase(INT32_MIN);
	ASSERT_STRING_EQUAL(i32string.content, "-0X80000000");
	i32string = base16_i32_to_i32string_with_prefix_in_uppercase(-99999);
	ASSERT_STRING_EQUAL(i32string.content, "-0X1869F");
	i32string = base16_i32_to_i32string_with_prefix_in_uppercase(-1);
	ASSERT_STRING_EQUAL(i32string.content, "-0X1");
	i32string = base16_i32_to_i32string_with_prefix_in_uppercase(0);
	ASSERT_STRING_EQUAL(i32string.content, "0X0");
	i32string = base16_i32_to_i32string_with_prefix_in_uppercase(1);
	ASSERT_STRING_EQUAL(i32string.content, "0X1");
	i32string = base16_i32_to_i32string_with_prefix_in_uppercase(99999);
	ASSERT_STRING_EQUAL(i32string.content, "0X1869F");
	i32string = base16_i32_to_i32string_with_prefix_in_uppercase(INT32_MAX);
	ASSERT_STRING_EQUAL(i32string.content, "0X7FFFFFFF");
}

TEST(tests_for_uint32_base_16_to_string_functions, "Tests for base 16 32-bit unsigned integer-to-string conversion functions")
{
	u32string_type u32string = {{0}};

	u32string = base16_u32_to_u32string(0U);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = base16_u32_to_u32string(1U);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = base16_u32_to_u32string(99999U);
	ASSERT_STRING_EQUAL(u32string.content, "1869f");
	u32string = base16_u32_to_u32string((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "7fffffff");
	u32string = base16_u32_to_u32string(UINT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "ffffffff");

	u32string = base16_u32_to_u32string_in_uppercase(0U);
	ASSERT_STRING_EQUAL(u32string.content, "0");
	u32string = base16_u32_to_u32string_in_uppercase(1U);
	ASSERT_STRING_EQUAL(u32string.content, "1");
	u32string = base16_u32_to_u32string_in_uppercase(99999U);
	ASSERT_STRING_EQUAL(u32string.content, "1869F");
	u32string = base16_u32_to_u32string_in_uppercase((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "7FFFFFFF");
	u32string = base16_u32_to_u32string_in_uppercase(UINT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "FFFFFFFF");

	u32string = base16_u32_to_u32string_with_prefix(0U);
	ASSERT_STRING_EQUAL(u32string.content, "0x0");
	u32string = base16_u32_to_u32string_with_prefix(1U);
	ASSERT_STRING_EQUAL(u32string.content, "0x1");
	u32string = base16_u32_to_u32string_with_prefix(99999U);
	ASSERT_STRING_EQUAL(u32string.content, "0x1869f");
	u32string = base16_u32_to_u32string_with_prefix((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "0x7fffffff");
	u32string = base16_u32_to_u32string_with_prefix(UINT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "0xffffffff");

	u32string = base16_u32_to_u32string_with_prefix_in_uppercase(0U);
	ASSERT_STRING_EQUAL(u32string.content, "0X0");
	u32string = base16_u32_to_u32string_with_prefix_in_uppercase(1U);
	ASSERT_STRING_EQUAL(u32string.content, "0X1");
	u32string = base16_u32_to_u32string_with_prefix_in_uppercase(99999U);
	ASSERT_STRING_EQUAL(u32string.content, "0X1869F");
	u32string = base16_u32_to_u32string_with_prefix_in_uppercase((uint32_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "0X7FFFFFFF");
	u32string = base16_u32_to_u32string_with_prefix_in_uppercase(UINT32_MAX);
	ASSERT_STRING_EQUAL(u32string.content, "0XFFFFFFFF");
}

TEST(tests_for_int64_base_16_to_string_functions, "Tests for base 16 64-bit signed integer-to-string conversion functions")
{
	i64string_type i64string = {{0}};

	i64string = base16_i64_to_i64string(INT64_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-8000000000000000");
	i64string = base16_i64_to_i64string(INT32_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-80000000");
	i64string = base16_i64_to_i64string(-99999);
	ASSERT_STRING_EQUAL(i64string.content, "-1869f");
	i64string = base16_i64_to_i64string(-1);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = base16_i64_to_i64string(0);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = base16_i64_to_i64string(1);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = base16_i64_to_i64string(99999);
	ASSERT_STRING_EQUAL(i64string.content, "1869f");
	i64string = base16_i64_to_i64string(INT32_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "7fffffff");
	i64string = base16_i64_to_i64string(INT64_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "7fffffffffffffff");

	i64string = base16_i64_to_i64string_in_uppercase(INT64_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-8000000000000000");
	i64string = base16_i64_to_i64string_in_uppercase(INT32_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-80000000");
	i64string = base16_i64_to_i64string_in_uppercase(-99999);
	ASSERT_STRING_EQUAL(i64string.content, "-1869F");
	i64string = base16_i64_to_i64string_in_uppercase(-1);
	ASSERT_STRING_EQUAL(i64string.content, "-1");
	i64string = base16_i64_to_i64string_in_uppercase(0);
	ASSERT_STRING_EQUAL(i64string.content, "0");
	i64string = base16_i64_to_i64string_in_uppercase(1);
	ASSERT_STRING_EQUAL(i64string.content, "1");
	i64string = base16_i64_to_i64string_in_uppercase(99999);
	ASSERT_STRING_EQUAL(i64string.content, "1869F");
	i64string = base16_i64_to_i64string_in_uppercase(INT32_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "7FFFFFFF");
	i64string = base16_i64_to_i64string_in_uppercase(INT64_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "7FFFFFFFFFFFFFFF");

	i64string = base16_i64_to_i64string_with_prefix(INT64_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-0x8000000000000000");
	i64string = base16_i64_to_i64string_with_prefix(INT32_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-0x80000000");
	i64string = base16_i64_to_i64string_with_prefix(-99999);
	ASSERT_STRING_EQUAL(i64string.content, "-0x1869f");
	i64string = base16_i64_to_i64string_with_prefix(-1);
	ASSERT_STRING_EQUAL(i64string.content, "-0x1");
	i64string = base16_i64_to_i64string_with_prefix(0);
	ASSERT_STRING_EQUAL(i64string.content, "0x0");
	i64string = base16_i64_to_i64string_with_prefix(1);
	ASSERT_STRING_EQUAL(i64string.content, "0x1");
	i64string = base16_i64_to_i64string_with_prefix(99999);
	ASSERT_STRING_EQUAL(i64string.content, "0x1869f");
	i64string = base16_i64_to_i64string_with_prefix(INT32_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "0x7fffffff");
	i64string = base16_i64_to_i64string_with_prefix(INT64_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "0x7fffffffffffffff");

	i64string = base16_i64_to_i64string_with_prefix_in_uppercase(INT64_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-0X8000000000000000");
	i64string = base16_i64_to_i64string_with_prefix_in_uppercase(INT32_MIN);
	ASSERT_STRING_EQUAL(i64string.content, "-0X80000000");
	i64string = base16_i64_to_i64string_with_prefix_in_uppercase(-99999);
	ASSERT_STRING_EQUAL(i64string.content, "-0X1869F");
	i64string = base16_i64_to_i64string_with_prefix_in_uppercase(-1);
	ASSERT_STRING_EQUAL(i64string.content, "-0X1");
	i64string = base16_i64_to_i64string_with_prefix_in_uppercase(0);
	ASSERT_STRING_EQUAL(i64string.content, "0X0");
	i64string = base16_i64_to_i64string_with_prefix_in_uppercase(1);
	ASSERT_STRING_EQUAL(i64string.content, "0X1");
	i64string = base16_i64_to_i64string_with_prefix_in_uppercase(99999);
	ASSERT_STRING_EQUAL(i64string.content, "0X1869F");
	i64string = base16_i64_to_i64string_with_prefix_in_uppercase(INT32_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "0X7FFFFFFF");
	i64string = base16_i64_to_i64string_with_prefix_in_uppercase(INT64_MAX);
	ASSERT_STRING_EQUAL(i64string.content, "0X7FFFFFFFFFFFFFFF");
}

TEST(tests_for_uint64_base_16_to_string_functions, "Tests for base 16 64-bit unsigned integer-to-string conversion functions")
{
	u64string_type u64string = {{0}};

	u64string = base16_u64_to_u64string(0U);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = base16_u64_to_u64string(1U);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = base16_u64_to_u64string(99999U);
	ASSERT_STRING_EQUAL(u64string.content, "1869f");
	u64string = base16_u64_to_u64string((uint64_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "7fffffff");
	u64string = base16_u64_to_u64string(UINT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "ffffffff");
	u64string = base16_u64_to_u64string(UINT64_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "ffffffffffffffff");

	u64string = base16_u64_to_u64string_in_uppercase(0U);
	ASSERT_STRING_EQUAL(u64string.content, "0");
	u64string = base16_u64_to_u64string_in_uppercase(1U);
	ASSERT_STRING_EQUAL(u64string.content, "1");
	u64string = base16_u64_to_u64string_in_uppercase(99999U);
	ASSERT_STRING_EQUAL(u64string.content, "1869F");
	u64string = base16_u64_to_u64string_in_uppercase((uint64_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "7FFFFFFF");
	u64string = base16_u64_to_u64string_in_uppercase(UINT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "FFFFFFFF");
	u64string = base16_u64_to_u64string_in_uppercase(UINT64_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "FFFFFFFFFFFFFFFF");

	u64string = base16_u64_to_u64string_with_prefix(0U);
	ASSERT_STRING_EQUAL(u64string.content, "0x0");
	u64string = base16_u64_to_u64string_with_prefix(1U);
	ASSERT_STRING_EQUAL(u64string.content, "0x1");
	u64string = base16_u64_to_u64string_with_prefix(99999U);
	ASSERT_STRING_EQUAL(u64string.content, "0x1869f");
	u64string = base16_u64_to_u64string_with_prefix((uint64_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0x7fffffff");
	u64string = base16_u64_to_u64string_with_prefix(UINT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0xffffffff");
	u64string = base16_u64_to_u64string_with_prefix(UINT64_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0xffffffffffffffff");

	u64string = base16_u64_to_u64string_with_prefix_in_uppercase(0U);
	ASSERT_STRING_EQUAL(u64string.content, "0X0");
	u64string = base16_u64_to_u64string_with_prefix_in_uppercase(1U);
	ASSERT_STRING_EQUAL(u64string.content, "0X1");
	u64string = base16_u64_to_u64string_with_prefix_in_uppercase(99999U);
	ASSERT_STRING_EQUAL(u64string.content, "0X1869F");
	u64string = base16_u64_to_u64string_with_prefix_in_uppercase((uint64_t) INT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0X7FFFFFFF");
	u64string = base16_u64_to_u64string_with_prefix_in_uppercase(UINT32_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0XFFFFFFFF");
	u64string = base16_u64_to_u64string_with_prefix_in_uppercase(UINT64_MAX);
	ASSERT_STRING_EQUAL(u64string.content, "0XFFFFFFFFFFFFFFFF");
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		tests_for_int32_base_2_string_output,
		tests_for_int32_base_8_string_output,
		tests_for_int32_base_10_string_output,
		tests_for_int32_base_16_string_output,
		tests_for_uint32_base_2_string_output,
		tests_for_uint32_base_8_string_output,
		tests_for_uint32_base_10_string_output,
		tests_for_uint32_base_16_string_output,
		tests_for_int64_base_2_string_output,
		tests_for_int64_base_8_string_output,
		tests_for_int64_base_10_string_output,
		tests_for_int64_base_16_string_output,
		tests_for_uint64_base_2_string_output,
		tests_for_uint64_base_8_string_output,
		tests_for_uint64_base_10_string_output,
		tests_for_uint64_base_16_string_output,
		tests_for_int32_base_2_to_string_functions,
		tests_for_uint32_base_2_to_string_functions,
		tests_for_int64_base_2_to_string_functions,
		tests_for_uint64_base_2_to_string_functions,
		tests_for_int32_base_8_to_string_functions,
		tests_for_uint32_base_8_to_string_functions,
		tests_for_int64_base_8_to_string_functions,
		tests_for_uint64_base_8_to_string_functions,
		tests_for_int32_base_10_to_string_functions,
		tests_for_uint32_base_10_to_string_functions,
		tests_for_int64_base_10_to_string_functions,
		tests_for_uint64_base_10_to_string_functions,
		tests_for_int32_base_16_to_string_functions,
		tests_for_uint32_base_16_to_string_functions,
		tests_for_int64_base_16_to_string_functions,
		tests_for_uint64_base_16_to_string_functions
	};

	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
