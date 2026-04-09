#include "safer_integer_math.h"
#include "unit_testing.h"
#include <iso646.h>

/* ============================================================================
 * Tests for i32_is_even / i32_is_odd
 * ============================================================================
 */

TEST(i32_is_even_with_zero, "i32_is_even returns true for zero")
{
	ASSERT(i32_is_even(0));
}

TEST(i32_is_even_with_positive_even, "i32_is_even returns true for positive even numbers")
{
	ASSERT(i32_is_even(2));
	ASSERT(i32_is_even(4));
	ASSERT(i32_is_even(100));
	ASSERT(i32_is_even(1000000));
}

TEST(i32_is_even_with_negative_even, "i32_is_even returns true for negative even numbers")
{
	ASSERT(i32_is_even(-2));
	ASSERT(i32_is_even(-4));
	ASSERT(i32_is_even(-100));
	ASSERT(i32_is_even(-1000000));
}

TEST(i32_is_even_with_positive_odd, "i32_is_even returns false for positive odd numbers")
{
	ASSERT(not i32_is_even(1));
	ASSERT(not i32_is_even(3));
	ASSERT(not i32_is_even(99));
	ASSERT(not i32_is_even(999999));
}

TEST(i32_is_even_with_negative_odd, "i32_is_even returns false for negative odd numbers")
{
	ASSERT(not i32_is_even(-1));
	ASSERT(not i32_is_even(-3));
	ASSERT(not i32_is_even(-99));
	ASSERT(not i32_is_even(-999999));
}

TEST(i32_is_even_with_extreme_values, "i32_is_even works with extreme int32_t values")
{
	ASSERT(i32_is_even(INT32_MAX - 1));  /* INT32_MAX is odd, so MAX-1 is even */
	ASSERT(not i32_is_even(INT32_MAX));  /* INT32_MAX (2147483647) is odd */
	ASSERT(i32_is_even(INT32_MIN));      /* INT32_MIN (-2147483648) is even */
	ASSERT(not i32_is_even(INT32_MIN + 1));  /* INT32_MIN + 1 is odd */
}

TEST(i32_is_odd_with_zero, "i32_is_odd returns false for zero")
{
	ASSERT(not i32_is_odd(0));
}

TEST(i32_is_odd_with_positive_odd, "i32_is_odd returns true for positive odd numbers")
{
	ASSERT(i32_is_odd(1));
	ASSERT(i32_is_odd(3));
	ASSERT(i32_is_odd(99));
	ASSERT(i32_is_odd(999999));
}

TEST(i32_is_odd_with_negative_odd, "i32_is_odd returns true for negative odd numbers")
{
	ASSERT(i32_is_odd(-1));
	ASSERT(i32_is_odd(-3));
	ASSERT(i32_is_odd(-99));
	ASSERT(i32_is_odd(-999999));
}

TEST(i32_is_odd_with_positive_even, "i32_is_odd returns false for positive even numbers")
{
	ASSERT(not i32_is_odd(2));
	ASSERT(not i32_is_odd(4));
	ASSERT(not i32_is_odd(100));
	ASSERT(not i32_is_odd(1000000));
}

TEST(i32_is_odd_with_negative_even, "i32_is_odd returns false for negative even numbers")
{
	ASSERT(not i32_is_odd(-2));
	ASSERT(not i32_is_odd(-4));
	ASSERT(not i32_is_odd(-100));
	ASSERT(not i32_is_odd(-1000000));
}

/* ============================================================================
 * Tests for u32_is_even / u32_is_odd
 * ============================================================================
 */

TEST(u32_is_even_with_zero, "u32_is_even returns true for zero")
{
	ASSERT(u32_is_even(0U));
}

TEST(u32_is_even_with_positive_even, "u32_is_even returns true for positive even numbers")
{
	ASSERT(u32_is_even(2U));
	ASSERT(u32_is_even(4U));
	ASSERT(u32_is_even(100U));
	ASSERT(u32_is_even(1000000U));
}

TEST(u32_is_even_with_positive_odd, "u32_is_even returns false for positive odd numbers")
{
	ASSERT(not u32_is_even(1U));
	ASSERT(not u32_is_even(3U));
	ASSERT(not u32_is_even(99U));
	ASSERT(not u32_is_even(999999U));
}

TEST(u32_is_even_with_extreme_values, "u32_is_even works with extreme uint32_t values")
{
	ASSERT(u32_is_even(UINT32_MAX - 1U));  /* UINT32_MAX is odd, so MAX-1 is even */
	ASSERT(not u32_is_even(UINT32_MAX));   /* UINT32_MAX (4294967295) is odd */
}

TEST(u32_is_odd_with_zero, "u32_is_odd returns false for zero")
{
	ASSERT(not u32_is_odd(0U));
}

TEST(u32_is_odd_with_positive_odd, "u32_is_odd returns true for positive odd numbers")
{
	ASSERT(u32_is_odd(1U));
	ASSERT(u32_is_odd(3U));
	ASSERT(u32_is_odd(99U));
	ASSERT(u32_is_odd(999999U));
}

TEST(u32_is_odd_with_positive_even, "u32_is_odd returns false for positive even numbers")
{
	ASSERT(not u32_is_odd(2U));
	ASSERT(not u32_is_odd(4U));
	ASSERT(not u32_is_odd(100U));
	ASSERT(not u32_is_odd(1000000U));
}

/* ============================================================================
 * Tests for i32_is_divisible
 * ============================================================================
 */

TEST(i32_is_divisible_basic_cases, "i32_is_divisible works for basic cases")
{
	ASSERT(i32_is_divisible(10, 2));      /* 10 / 2 = 5 */
	ASSERT(i32_is_divisible(15, 3));      /* 15 / 3 = 5 */
	ASSERT(i32_is_divisible(100, 10));    /* 100 / 10 = 10 */
	ASSERT(not i32_is_divisible(10, 3));  /* 10 / 3 = 3 remainder 1 */
	ASSERT(not i32_is_divisible(15, 4));  /* 15 / 4 = 3 remainder 3 */
}

TEST(i32_is_divisible_with_zero_dividend, "i32_is_divisible with zero dividend")
{
	ASSERT(i32_is_divisible(0, 1));
	ASSERT(i32_is_divisible(0, 2));
	ASSERT(i32_is_divisible(0, 100));
	ASSERT(i32_is_divisible(0, -5));
}

TEST(i32_is_divisible_with_negative_numbers, "i32_is_divisible works with negative numbers")
{
	ASSERT(i32_is_divisible(-10, 2));     /* -10 / 2 = -5 */
	ASSERT(i32_is_divisible(10, -2));     /* 10 / -2 = -5 */
	ASSERT(i32_is_divisible(-10, -2));    /* -10 / -2 = 5 */
	ASSERT(i32_is_divisible(-15, 3));     /* -15 / 3 = -5 */
	ASSERT(not i32_is_divisible(-10, 3)); /* -10 / 3 has remainder */
}

TEST(i32_is_divisible_with_divisor_one, "i32_is_divisible with divisor of 1")
{
	ASSERT(i32_is_divisible(0, 1));
	ASSERT(i32_is_divisible(1, 1));
	ASSERT(i32_is_divisible(100, 1));
	ASSERT(i32_is_divisible(-50, 1));
}

TEST(i32_is_divisible_with_divisor_negative_one, "i32_is_divisible with divisor of -1")
{
	ASSERT(i32_is_divisible(0, -1));
	ASSERT(i32_is_divisible(1, -1));
	ASSERT(i32_is_divisible(100, -1));
	ASSERT(i32_is_divisible(-50, -1));
}

TEST(i32_is_divisible_with_equal_dividend_and_divisor, "i32_is_divisible when dividend and divisor have the same absolute value")
{
	ASSERT(i32_is_divisible(5, 5));
	ASSERT(i32_is_divisible(-7, -7));
	ASSERT(i32_is_divisible(5, -5));  /* Different signs */
}

TEST(i32_is_divisible_with_divisor_zero_returns_false, "i32_is_divisible returns false for divisor of zero")
{
	ASSERT(not i32_is_divisible(0, 0));
	ASSERT(not i32_is_divisible(10, 0));
	ASSERT(not i32_is_divisible(-5, 0));
}

TEST(i32_is_divisible_with_extreme_values, "i32_is_divisible works with extreme int32_t values")
{
	ASSERT(i32_is_divisible(INT32_MAX, 1));
	ASSERT(i32_is_divisible(INT32_MIN, 1));
	ASSERT(i32_is_divisible(INT32_MIN, -1));
}

/* ============================================================================
 * Tests for u32_is_divisible
 * ============================================================================
 */

TEST(u32_is_divisible_basic_cases, "u32_is_divisible works for basic cases")
{
	ASSERT(u32_is_divisible(10U, 2U));     /* 10 / 2 = 5 */
	ASSERT(u32_is_divisible(15U, 3U));     /* 15 / 3 = 5 */
	ASSERT(u32_is_divisible(100U, 10U));   /* 100 / 10 = 10 */
	ASSERT(not u32_is_divisible(10U, 3U)); /* 10 / 3 = 3 remainder 1 */
	ASSERT(not u32_is_divisible(15U, 4U)); /* 15 / 4 = 3 remainder 3 */
}

TEST(u32_is_divisible_with_zero_dividend, "u32_is_divisible with zero dividend")
{
	ASSERT(u32_is_divisible(0U, 1U));
	ASSERT(u32_is_divisible(0U, 2U));
	ASSERT(u32_is_divisible(0U, 100U));
}

TEST(u32_is_divisible_with_divisor_one, "u32_is_divisible with divisor of 1")
{
	ASSERT(u32_is_divisible(0U, 1U));
	ASSERT(u32_is_divisible(1U, 1U));
	ASSERT(u32_is_divisible(100U, 1U));
}

TEST(u32_is_divisible_with_extreme_values, "u32_is_divisible works with extreme uint32_t values")
{
	ASSERT(u32_is_divisible(UINT32_MAX, 1U));
	ASSERT(u32_is_divisible(UINT32_MAX, UINT32_MAX));
}

TEST(u32_is_divisible_with_divisor_zero_returns_false, "u32_is_divisible returns false for divisor of zero")
{
	ASSERT(not u32_is_divisible(0U, 0U));
	ASSERT(not u32_is_divisible(10U, 0U));
}

/* ============================================================================
 * Tests for i32_is_prime
 * ============================================================================
 */

TEST(i32_is_prime_with_negative_numbers, "i32_is_prime returns false for negative numbers")
{
	ASSERT(not i32_is_prime(-1));
	ASSERT(not i32_is_prime(-2));
	ASSERT(not i32_is_prime(-5));
	ASSERT(not i32_is_prime(-17));
	ASSERT(not i32_is_prime(INT32_MIN));
}

TEST(i32_is_prime_with_zero_and_one, "i32_is_prime returns false for 0 and 1")
{
	ASSERT(not i32_is_prime(0));
	ASSERT(not i32_is_prime(1));
}

TEST(i32_is_prime_with_small_primes, "i32_is_prime identifies small primes correctly")
{
	ASSERT(i32_is_prime(2));
	ASSERT(i32_is_prime(3));
	ASSERT(i32_is_prime(5));
	ASSERT(i32_is_prime(7));
	ASSERT(i32_is_prime(11));
	ASSERT(i32_is_prime(13));
	ASSERT(i32_is_prime(17));
	ASSERT(i32_is_prime(19));
	ASSERT(i32_is_prime(23));
	ASSERT(i32_is_prime(29));
}

TEST(i32_is_prime_with_small_composites, "i32_is_prime identifies small composites correctly")
{
	ASSERT(not i32_is_prime(4));
	ASSERT(not i32_is_prime(6));
	ASSERT(not i32_is_prime(8));
	ASSERT(not i32_is_prime(9));
	ASSERT(not i32_is_prime(10));
	ASSERT(not i32_is_prime(12));
	ASSERT(not i32_is_prime(14));
	ASSERT(not i32_is_prime(15));
	ASSERT(not i32_is_prime(16));
	ASSERT(not i32_is_prime(18));
	ASSERT(not i32_is_prime(20));
	ASSERT(not i32_is_prime(21));
	ASSERT(not i32_is_prime(22));
	ASSERT(not i32_is_prime(24));
	ASSERT(not i32_is_prime(25));
}

TEST(i32_is_prime_with_perfect_squares, "i32_is_prime correctly identifies perfect squares as composite")
{
	ASSERT(not i32_is_prime(4));       /* 2^2 */
	ASSERT(not i32_is_prime(9));       /* 3^2 */
	ASSERT(not i32_is_prime(25));      /* 5^2 */
	ASSERT(not i32_is_prime(49));      /* 7^2 */
	ASSERT(not i32_is_prime(121));     /* 11^2 */
	ASSERT(not i32_is_prime(169));     /* 13^2 */
	ASSERT(not i32_is_prime(289));     /* 17^2 */
	ASSERT(not i32_is_prime(361));     /* 19^2 */
}

TEST(i32_is_prime_with_medium_primes, "i32_is_prime identifies medium-sized primes")
{
	ASSERT(i32_is_prime(97));
	ASSERT(i32_is_prime(101));
	ASSERT(i32_is_prime(307));
	ASSERT(i32_is_prime(509));
	ASSERT(i32_is_prime(997));
}

TEST(i32_is_prime_with_medium_composites, "i32_is_prime identifies medium-sized composites")
{
	ASSERT(not i32_is_prime(100));
	ASSERT(not i32_is_prime(102));
	ASSERT(not i32_is_prime(308));
	ASSERT(not i32_is_prime(510));
	ASSERT(not i32_is_prime(998));
}

TEST(i32_is_prime_with_large_primes, "i32_is_prime identifies large primes")
{
	ASSERT(i32_is_prime(10007));
	ASSERT(i32_is_prime(100003));
	ASSERT(i32_is_prime(1000003));
}

TEST(i32_is_prime_with_large_composites, "i32_is_prime identifies large composites")
{
	ASSERT(not i32_is_prime(10000));   /* 10000 = 10^4 */
	ASSERT(not i32_is_prime(100000));  /* 100000 = 10^5 */
	ASSERT(not i32_is_prime(1000000)); /* 1000000 = 10^6 */
}

TEST(i32_is_prime_near_int32_max, "i32_is_prime works near INT32_MAX")
{
	ASSERT(i32_is_prime(INT32_MAX));        /* 2147483647 is prime */
	ASSERT(not i32_is_prime(INT32_MAX - 1)); /* 2147483646 is not prime */
	ASSERT(not i32_is_prime(INT32_MAX - 2)); /* 2147483645 is not prime */
}

/* ============================================================================
 * Tests for u32_is_prime
 * ============================================================================
 */

TEST(u32_is_prime_with_zero_and_one, "u32_is_prime returns false for 0 and 1")
{
	ASSERT(not u32_is_prime(0U));
	ASSERT(not u32_is_prime(1U));
}

TEST(u32_is_prime_with_small_primes, "u32_is_prime identifies small primes correctly")
{
	ASSERT(u32_is_prime(2U));
	ASSERT(u32_is_prime(3U));
	ASSERT(u32_is_prime(5U));
	ASSERT(u32_is_prime(7U));
	ASSERT(u32_is_prime(11U));
	ASSERT(u32_is_prime(13U));
	ASSERT(u32_is_prime(17U));
	ASSERT(u32_is_prime(19U));
	ASSERT(u32_is_prime(23U));
	ASSERT(u32_is_prime(29U));
}

TEST(u32_is_prime_with_small_composites, "u32_is_prime identifies small composites correctly")
{
	ASSERT(not u32_is_prime(4U));
	ASSERT(not u32_is_prime(6U));
	ASSERT(not u32_is_prime(8U));
	ASSERT(not u32_is_prime(9U));
	ASSERT(not u32_is_prime(10U));
	ASSERT(not u32_is_prime(12U));
	ASSERT(not u32_is_prime(14U));
	ASSERT(not u32_is_prime(15U));
	ASSERT(not u32_is_prime(16U));
	ASSERT(not u32_is_prime(18U));
	ASSERT(not u32_is_prime(20U));
}

TEST(u32_is_prime_with_perfect_squares, "u32_is_prime correctly identifies perfect squares")
{
	ASSERT(not u32_is_prime(4U));       /* 2^2 */
	ASSERT(not u32_is_prime(9U));       /* 3^2 */
	ASSERT(not u32_is_prime(25U));      /* 5^2 */
	ASSERT(not u32_is_prime(49U));      /* 7^2 */
	ASSERT(not u32_is_prime(121U));     /* 11^2 */
	ASSERT(not u32_is_prime(169U));     /* 13^2 */
	ASSERT(not u32_is_prime(289U));     /* 17^2 */
}

TEST(u32_is_prime_with_medium_primes, "u32_is_prime identifies medium-sized primes")
{
	ASSERT(u32_is_prime(97U));
	ASSERT(u32_is_prime(101U));
	ASSERT(u32_is_prime(307U));
	ASSERT(u32_is_prime(509U));
	ASSERT(u32_is_prime(997U));
}

TEST(u32_is_prime_with_large_primes, "u32_is_prime identifies large primes")
{
	ASSERT(u32_is_prime(10007U));
	ASSERT(u32_is_prime(100003U));
	ASSERT(u32_is_prime(1000003U));
}

TEST(u32_is_prime_with_large_composites, "u32_is_prime identifies large composites")
{
	ASSERT(not u32_is_prime(10000U));
	ASSERT(not u32_is_prime(100000U));
	ASSERT(not u32_is_prime(1000000U));
}

TEST(u32_is_prime_near_uint32_max, "u32_is_prime works near UINT32_MAX")
{
	ASSERT(not u32_is_prime(UINT32_MAX));         /* 4294967295 = 3 × 5 × 17 × 257 × 65537 */
	ASSERT(u32_is_prime(4294967291U));            /* 4294967291 is prime */
	ASSERT(not u32_is_prime(UINT32_MAX - 1));     /* Even, not prime */
}

/* ============================================================================
 * Conditional tests for 64-bit integer functions (if available)
 * ============================================================================
 */

#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)

TEST(i64_is_even_with_zero, "i64_is_even returns true for zero")
{
	ASSERT(i64_is_even(0LL));
}

TEST(i64_is_even_with_positive_even, "i64_is_even returns true for positive even numbers")
{
	ASSERT(i64_is_even(2LL));
	ASSERT(i64_is_even(100LL));
	ASSERT(i64_is_even(1000000000000LL));
}

TEST(i64_is_even_with_negative_even, "i64_is_even returns true for negative even numbers")
{
	ASSERT(i64_is_even(-2LL));
	ASSERT(i64_is_even(-100LL));
	ASSERT(i64_is_even(-1000000000000LL));
}

TEST(i64_is_even_with_positive_odd, "i64_is_even returns false for positive odd numbers")
{
	ASSERT(not i64_is_even(1LL));
	ASSERT(not i64_is_even(99LL));
	ASSERT(not i64_is_even(999999999999LL));
}

TEST(i64_is_odd_with_zero, "i64_is_odd returns false for zero")
{
	ASSERT(not i64_is_odd(0LL));
}

TEST(i64_is_odd_with_positive_odd, "i64_is_odd returns true for positive odd numbers")
{
	ASSERT(i64_is_odd(1LL));
	ASSERT(i64_is_odd(99LL));
	ASSERT(i64_is_odd(999999999999LL));
}

TEST(u64_is_even_with_zero, "u64_is_even returns true for zero")
{
	ASSERT(u64_is_even(0ULL));
}

TEST(u64_is_even_with_positive_even, "u64_is_even returns true for positive even numbers")
{
	ASSERT(u64_is_even(2ULL));
	ASSERT(u64_is_even(100ULL));
	ASSERT(u64_is_even(1000000000000ULL));
}

TEST(u64_is_odd_with_positive_odd, "u64_is_odd returns true for positive odd numbers")
{
	ASSERT(u64_is_odd(1ULL));
	ASSERT(u64_is_odd(99ULL));
	ASSERT(u64_is_odd(999999999999ULL));
}

TEST(i64_is_divisible_basic_cases, "i64_is_divisible works for basic cases")
{
	ASSERT(i64_is_divisible(10LL, 2LL));
	ASSERT(i64_is_divisible(1000000000000LL, 1000000LL));
	ASSERT(not i64_is_divisible(10LL, 3LL));
}

TEST(i64_is_divisible_with_divisor_zero, "i64_is_divisible returns false for divisor zero")
{
	ASSERT(not i64_is_divisible(10LL, 0LL));
	ASSERT(not i64_is_divisible(0LL, 0LL));
}

TEST(u64_is_divisible_basic_cases, "u64_is_divisible works for basic cases")
{
	ASSERT(u64_is_divisible(10ULL, 2ULL));
	ASSERT(u64_is_divisible(1000000000000ULL, 1000000ULL));
	ASSERT(not u64_is_divisible(10ULL, 3ULL));
}

TEST(u64_is_divisible_with_divisor_zero, "u64_is_divisible returns false for divisor zero")
{
	ASSERT(not u64_is_divisible(10ULL, 0ULL));
	ASSERT(not u64_is_divisible(0ULL, 0ULL));
}

TEST(i64_is_prime_with_small_primes, "i64_is_prime identifies small primes")
{
	ASSERT(i64_is_prime(2LL));
	ASSERT(i64_is_prime(3LL));
	ASSERT(i64_is_prime(5LL));
	ASSERT(i64_is_prime(7LL));
	ASSERT(i64_is_prime(11LL));
}

TEST(i64_is_prime_with_zero_and_one, "i64_is_prime returns false for 0 and 1")
{
	ASSERT(not i64_is_prime(0LL));
	ASSERT(not i64_is_prime(1LL));
}

TEST(i64_is_prime_with_large_primes, "i64_is_prime identifies large 64-bit primes")
{
	ASSERT(i64_is_prime(1000000007LL));
	ASSERT(i64_is_prime(1000000009LL));
}

TEST(u64_is_prime_with_small_primes, "u64_is_prime identifies small primes")
{
	ASSERT(u64_is_prime(2ULL));
	ASSERT(u64_is_prime(3ULL));
	ASSERT(u64_is_prime(5ULL));
	ASSERT(u64_is_prime(7ULL));
	ASSERT(u64_is_prime(11ULL));
}

TEST(u64_is_prime_with_zero_and_one, "u64_is_prime returns false for 0 and 1")
{
	ASSERT(not u64_is_prime(0ULL));
	ASSERT(not u64_is_prime(1ULL));
}

TEST(u64_is_prime_with_large_primes, "u64_is_prime identifies large 64-bit primes")
{
	ASSERT(u64_is_prime(1000000007ULL));
	ASSERT(u64_is_prime(1000000009ULL));
}

#endif /* INT64_MIN && INT64_MAX && UINT64_MAX */

/* ============================================================================
 * Main Test Runner
 * ============================================================================
 */

int main(void)
{
	DEFINE_LIST_OF_TESTS(list_of_tests) {
		/* i32_is_even tests */
		i32_is_even_with_zero,
		i32_is_even_with_positive_even,
		i32_is_even_with_negative_even,
		i32_is_even_with_positive_odd,
		i32_is_even_with_negative_odd,
		i32_is_even_with_extreme_values,

		/* i32_is_odd tests */
		i32_is_odd_with_zero,
		i32_is_odd_with_positive_odd,
		i32_is_odd_with_negative_odd,
		i32_is_odd_with_positive_even,
		i32_is_odd_with_negative_even,

		/* u32_is_even tests */
		u32_is_even_with_zero,
		u32_is_even_with_positive_even,
		u32_is_even_with_positive_odd,
		u32_is_even_with_extreme_values,

		/* u32_is_odd tests */
		u32_is_odd_with_zero,
		u32_is_odd_with_positive_odd,
		u32_is_odd_with_positive_even,

		/* i32_is_divisible tests */
		i32_is_divisible_basic_cases,
		i32_is_divisible_with_zero_dividend,
		i32_is_divisible_with_negative_numbers,
		i32_is_divisible_with_divisor_one,
		i32_is_divisible_with_divisor_negative_one,
		i32_is_divisible_with_equal_dividend_and_divisor,
		i32_is_divisible_with_divisor_zero_returns_false,
		i32_is_divisible_with_extreme_values,

		/* u32_is_divisible tests */
		u32_is_divisible_basic_cases,
		u32_is_divisible_with_zero_dividend,
		u32_is_divisible_with_divisor_one,
		u32_is_divisible_with_extreme_values,
		u32_is_divisible_with_divisor_zero_returns_false,

		/* i32_is_prime tests */
		i32_is_prime_with_negative_numbers,
		i32_is_prime_with_zero_and_one,
		i32_is_prime_with_small_primes,
		i32_is_prime_with_small_composites,
		i32_is_prime_with_perfect_squares,
		i32_is_prime_with_medium_primes,
		i32_is_prime_with_medium_composites,
		i32_is_prime_with_large_primes,
		i32_is_prime_with_large_composites,
		i32_is_prime_near_int32_max,

		/* u32_is_prime tests */
		u32_is_prime_with_zero_and_one,
		u32_is_prime_with_small_primes,
		u32_is_prime_with_small_composites,
		u32_is_prime_with_perfect_squares,
		u32_is_prime_with_medium_primes,
		u32_is_prime_with_large_primes,
		u32_is_prime_with_large_composites,
		u32_is_prime_near_uint32_max,

#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)
		/* i64_is_even tests */
		i64_is_even_with_zero,
		i64_is_even_with_positive_even,
		i64_is_even_with_negative_even,
		i64_is_even_with_positive_odd,

		/* i64_is_odd tests */
		i64_is_odd_with_zero,
		i64_is_odd_with_positive_odd,

		/* u64_is_even tests */
		u64_is_even_with_zero,
		u64_is_even_with_positive_even,

		/* u64_is_odd tests */
		u64_is_odd_with_positive_odd,

		/* i64_is_divisible tests */
		i64_is_divisible_basic_cases,
		i64_is_divisible_with_divisor_zero,

		/* u64_is_divisible tests */
		u64_is_divisible_basic_cases,
		u64_is_divisible_with_divisor_zero,

		/* i64_is_prime tests */
		i64_is_prime_with_small_primes,
		i64_is_prime_with_zero_and_one,
		i64_is_prime_with_large_primes,

		/* u64_is_prime tests */
		u64_is_prime_with_small_primes,
		u64_is_prime_with_zero_and_one,
		u64_is_prime_with_large_primes,
#endif
	};

	PRINT_FILE_NAME();
	RUN_TESTS(list_of_tests);
	PRINT_TEST_STATISTICS(list_of_tests);
	return 0;
}
