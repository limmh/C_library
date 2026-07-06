#include "fixed_width_integer_types.h"
#include "unit_testing.h"

#include <iso646.h>

/* Exact-width signed types */
TEST(int8_type_tests, "int8_t has exactly 8 bits and the correct range")
{
	ASSERT_SIZE_EQUAL(sizeof(int8_t) * CHAR_BIT, 8U);
	ASSERT_INT8_EQUAL(INT8_MAX, 127);
	ASSERT_INT8_EQUAL(INT8_MIN, -128);
	ASSERT_INT8_EQUAL(INT8_C(0), 0);
	ASSERT_INT8_EQUAL(INT8_C(100), 100);
	ASSERT_INT8_EQUAL(INT8_C(-100), -100);
}

TEST(int16_type_tests, "int16_t has exactly 16 bits and the correct range")
{
	ASSERT_SIZE_EQUAL(sizeof(int16_t) * CHAR_BIT, 16U);
	ASSERT_INT16_EQUAL(INT16_MAX, 32767);
	ASSERT_INT16_EQUAL(INT16_MIN, -32768);
	ASSERT_INT16_EQUAL(INT16_C(0), 0);
	ASSERT_INT16_EQUAL(INT16_C(12345), 12345);
	ASSERT_INT16_EQUAL(INT16_C(-12345), -12345);
}

TEST(int32_type_tests, "int32_t has exactly 32 bits and the correct range")
{
	ASSERT_SIZE_EQUAL(sizeof(int32_t) * CHAR_BIT, 32U);
	ASSERT_INT32_EQUAL(INT32_MAX, INT32_C(2147483647));
	ASSERT_INT32_EQUAL(INT32_MIN, INT32_C(-2147483647) - INT32_C(1));
	ASSERT_INT32_EQUAL(INT32_C(0), 0);
	ASSERT_INT32_EQUAL(INT32_C(1000000), 1000000);
}

/* Exact-width unsigned types */
TEST(uint8_type_tests, "uint8_t has exactly 8 bits and the correct range")
{
	ASSERT_SIZE_EQUAL(sizeof(uint8_t) * CHAR_BIT, 8U);
	ASSERT_UINT8_EQUAL(UINT8_MAX, 255U);
	ASSERT_UINT8_EQUAL(UINT8_C(0), 0U);
	ASSERT_UINT8_EQUAL(UINT8_C(200), 200U);
}

TEST(uint16_type_tests, "uint16_t has exactly 16 bits and the correct range")
{
	ASSERT_SIZE_EQUAL(sizeof(uint16_t) * CHAR_BIT, 16U);
	ASSERT_UINT16_EQUAL(UINT16_MAX, 65535U);
	ASSERT_UINT16_EQUAL(UINT16_C(0), 0U);
	ASSERT_UINT16_EQUAL(UINT16_C(50000), 50000U);
}

TEST(uint32_type_tests, "uint32_t has exactly 32 bits and the correct range")
{
	ASSERT_SIZE_EQUAL(sizeof(uint32_t) * CHAR_BIT, 32U);
	ASSERT_UINT32_EQUAL(UINT32_MAX, UINT32_C(4294967295));
	ASSERT_UINT32_EQUAL(UINT32_C(0), 0U);
	ASSERT_UINT32_EQUAL(UINT32_C(3000000000), UINT32_C(3000000000));
}

/* Optional 64-bit types */

#if defined(INT64_MIN) and defined(INT64_MAX)
TEST(int64_type_tests, "int64_t has exactly 64 bits and the correct range")
{
	ASSERT_SIZE_EQUAL(sizeof(int64_t) * CHAR_BIT, 64U);
	ASSERT_INT64_EQUAL(INT64_MAX, INT64_C(9223372036854775807));
	ASSERT_INT64_EQUAL(INT64_MIN, INT64_C(-9223372036854775807) - INT64_C(1));
	ASSERT_INT64_EQUAL(INT64_MIN + INT64_MAX, INT64_C(-1)); /* Two's complement symmetry. */
	ASSERT_INT64_EQUAL(INT64_C(1000000000000), INT64_C(1000000000000));
}
#endif

#if defined(UINT64_MAX)
TEST(uint64_type_tests, "uint64_t has exactly 64 bits and the correct range")
{
	ASSERT_SIZE_EQUAL(sizeof(uint64_t) * CHAR_BIT, 64U);
	ASSERT_UINT64_EQUAL(UINT64_MAX, UINT64_C(18446744073709551615));
	ASSERT_UINT64_EQUAL(UINT64_MAX + UINT64_C(1), UINT64_C(0)); /* Wrap-around identity for an unsigned 64-bit type. */
	ASSERT_UINT64_EQUAL(UINT64_C(10000000000000000000), UINT64_C(10000000000000000000));
}
#endif

/* Minimum-width (least) types must be able to hold the nominal range */
TEST(least_signed_type_tests, "int_least*_t are at least as wide as the nominal width")
{
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(int_least8_t) * CHAR_BIT, 8U);
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(int_least16_t) * CHAR_BIT, 16U);
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(int_least32_t) * CHAR_BIT, 32U);

	/* Evaluated in each macro's own width to avoid forcing a truncating cast. */
	ASSERT(INT_LEAST8_MAX >= INT8_MAX);
	ASSERT(INT_LEAST8_MIN <= INT8_MIN);
	ASSERT(INT_LEAST16_MAX >= INT16_MAX);
	ASSERT(INT_LEAST16_MIN <= INT16_MIN);
	ASSERT(INT_LEAST32_MAX >= INT32_MAX);
	ASSERT(INT_LEAST32_MIN <= INT32_MIN);
}

TEST(least_unsigned_type_tests, "uint_least*_t are at least as wide as the nominal width")
{
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(uint_least8_t) * CHAR_BIT, 8U);
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(uint_least16_t) * CHAR_BIT, 16U);
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(uint_least32_t) * CHAR_BIT, 32U);

	/* Evaluated in each macro's own width to avoid forcing a truncating cast. */
	ASSERT(UINT_LEAST8_MAX >= UINT8_MAX);
	ASSERT(UINT_LEAST16_MAX >= UINT16_MAX);
	ASSERT(UINT_LEAST32_MAX >= UINT32_MAX);
}

/* Fastest-width (fast) types must be able to hold the nominal range */
TEST(fast_signed_type_tests, "int_fast*_t are at least as wide as the nominal width")
{
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(int_fast8_t) * CHAR_BIT, 8U);
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(int_fast16_t) * CHAR_BIT, 16U);
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(int_fast32_t) * CHAR_BIT, 32U);

	/* Evaluated in each macro's own width to avoid forcing a truncating cast. */
	ASSERT(INT_FAST8_MAX >= INT8_MAX);
	ASSERT(INT_FAST8_MIN <= INT8_MIN);
	ASSERT(INT_FAST16_MAX >= INT16_MAX);
	ASSERT(INT_FAST16_MIN <= INT16_MIN);
	ASSERT(INT_FAST32_MAX >= INT32_MAX);
	ASSERT(INT_FAST32_MIN <= INT32_MIN);
}

TEST(fast_unsigned_type_tests, "uint_fast*_t are at least as wide as the nominal width")
{
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(uint_fast8_t) * CHAR_BIT, 8U);
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(uint_fast16_t) * CHAR_BIT, 16U);
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(uint_fast32_t) * CHAR_BIT, 32U);

	/* Evaluated in each macro's own width to avoid forcing a truncating cast. */
	ASSERT(UINT_FAST8_MAX >= UINT8_MAX);
	ASSERT(UINT_FAST16_MAX >= UINT16_MAX);
	ASSERT(UINT_FAST32_MAX >= UINT32_MAX);
}

/* Greatest-width (max) types */
TEST(intmax_type_tests, "intmax_t and uintmax_t cover at least every other integer type")
{
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(intmax_t) * CHAR_BIT, sizeof(int32_t) * CHAR_BIT);
	ASSERT_SIZE_GREATER_OR_EQUAL(sizeof(uintmax_t) * CHAR_BIT, sizeof(uint32_t) * CHAR_BIT);

	ASSERT_SIZE_EQUAL(sizeof(intmax_t), sizeof(uintmax_t));
	/* Compared in intmax_t arithmetic to avoid truncating a 64-bit value to long. */
	ASSERT(INTMAX_MAX > 0);
	ASSERT(INTMAX_MIN < 0);
	ASSERT(UINTMAX_MAX > 0U);
}

/* Pointer-holding integer types */
TEST(pointer_integer_type_tests, "intptr_t and uintptr_t are the size of a pointer")
{
	ASSERT_SIZE_EQUAL(sizeof(intptr_t), sizeof(void *));
	ASSERT_SIZE_EQUAL(sizeof(uintptr_t), sizeof(void *));
	ASSERT_SIZE_EQUAL(sizeof(intptr_t), sizeof(uintptr_t));
}

/* Bit-width macros */
TEST(width_macro_tests, "The *_WIDTH macros match the actual type widths")
{
	ASSERT_UINT_EQUAL(INT8_WIDTH, 8U);
	ASSERT_UINT_EQUAL(INT16_WIDTH, 16U);
	ASSERT_UINT_EQUAL(INT32_WIDTH, 32U);
	ASSERT_UINT_EQUAL(UINT8_WIDTH, 8U);
	ASSERT_UINT_EQUAL(UINT16_WIDTH, 16U);
	ASSERT_UINT_EQUAL(UINT32_WIDTH, 32U);

	ASSERT_SIZE_EQUAL(INT8_WIDTH, sizeof(int8_t) * CHAR_BIT);
	ASSERT_SIZE_EQUAL(INT16_WIDTH, sizeof(int16_t) * CHAR_BIT);
	ASSERT_SIZE_EQUAL(INT32_WIDTH, sizeof(int32_t) * CHAR_BIT);

	ASSERT_UINT_GREATER_OR_EQUAL(INT_LEAST8_WIDTH, 8U);
	ASSERT_UINT_GREATER_OR_EQUAL(INT_LEAST16_WIDTH, 16U);
	ASSERT_UINT_GREATER_OR_EQUAL(INT_LEAST32_WIDTH, 32U);
	ASSERT_UINT_GREATER_OR_EQUAL(INT_FAST8_WIDTH, 8U);
	ASSERT_UINT_GREATER_OR_EQUAL(INT_FAST16_WIDTH, 16U);
	ASSERT_UINT_GREATER_OR_EQUAL(INT_FAST32_WIDTH, 32U);

#ifdef INT64_WIDTH
	ASSERT_UINT_EQUAL(INT64_WIDTH, 64U);
	ASSERT_SIZE_EQUAL(INT64_WIDTH, sizeof(int64_t) * CHAR_BIT);
#endif

#ifdef UINT64_WIDTH
	ASSERT_UINT_EQUAL(UINT64_WIDTH, 64U);
	ASSERT_SIZE_EQUAL(UINT64_WIDTH, sizeof(uint64_t) * CHAR_BIT);
#endif
}

TEST(pointer_width_macro_tests, "The pointer-related width macros match the pointer size")
{
#ifdef INTPTR_WIDTH
	ASSERT_SIZE_EQUAL(INTPTR_WIDTH, sizeof(intptr_t) * CHAR_BIT);
#endif

#ifdef UINTPTR_WIDTH
	ASSERT_SIZE_EQUAL(UINTPTR_WIDTH, sizeof(uintptr_t) * CHAR_BIT);
#endif

#ifdef PTRDIFF_WIDTH
	ASSERT_SIZE_EQUAL(PTRDIFF_WIDTH, sizeof(ptrdiff_t) * CHAR_BIT);
#endif

#ifdef SIZE_WIDTH
	ASSERT_SIZE_EQUAL(SIZE_WIDTH, sizeof(size_t) * CHAR_BIT);
#endif
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		int8_type_tests,
		int16_type_tests,
		int32_type_tests,
		uint8_type_tests,
		uint16_type_tests,
		uint32_type_tests,
#if defined(INT64_MIN) and defined(INT64_MAX)
		int64_type_tests,
#endif
#if defined(UINT64_MAX)
		uint64_type_tests,
#endif
		least_signed_type_tests,
		least_unsigned_type_tests,
		fast_signed_type_tests,
		fast_unsigned_type_tests,
		intmax_type_tests,
		pointer_integer_type_tests,
		width_macro_tests,
		pointer_width_macro_tests
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
