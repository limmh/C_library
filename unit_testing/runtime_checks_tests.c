#include "runtime_checks.h"
#include "unit_testing.h"

#include <iso646.h>
/*
#define NOT_NULLPTR(ptr) (ptr != NULL)
#define not_nullptr(ptr) NOT_NULLPTR(ptr)

#define IS_ARRAY(array_or_pointer) \
#define is_array(array_or_pointer) IS_ARRAY(array_or_pointer)
static bool int_subtraction_has_defined_behavior(int a, int b)
static bool int_multiplication_has_defined_behavior(int a, int b)
static bool int_division_has_defined_behavior(int dividend, int divisor)
static bool long_addition_has_defined_behavior(long a, long b)
static bool long_subtraction_has_defined_behavior(long a, long b)
static bool long_multiplication_has_defined_behavior(long a, long b)
static bool long_division_has_defined_behavior(long dividend, long divisor)
static bool long_long_addition_has_defined_behavior(long long a, long long b)
static bool long_long_subtraction_has_defined_behavior(long long a, long long b)
static bool long_long_multiplication_has_defined_behavior(long long a, long long b)
static bool long_long_division_has_defined_behavior(long long dividend, long long divisor)

static bool unsigned_int_addition_no_wraparound(unsigned int a, unsigned int b)
static bool unsigned_int_subtraction_no_wraparound(unsigned int a, unsigned int b)
static bool unsigned_int_multiplication_no_wraparound(unsigned int a, unsigned int b)
static bool unsigned_int_division_no_division_by_zero(unsigned int dividend, unsigned int divisor)
static bool unsigned_long_addition_no_wraparound(unsigned long a, unsigned long b)
static bool unsigned_long_subtraction_no_wraparound(unsigned long a, unsigned long b)
static bool unsigned_long_multiplication_no_wraparound(unsigned long a, unsigned long b)
static bool unsigned_long_division_no_division_by_zero(unsigned long dividend, unsigned long divisor)
static bool unsigned_long_long_addition_no_wraparound(unsigned long long a, unsigned long long b)
static bool unsigned_long_long_subtraction_no_wraparound(unsigned long long a, unsigned long long b)
static bool unsigned_long_long_multiplication_no_wraparound(unsigned long long a, unsigned long long b)
static bool unsigned_long_long_division_no_division_by_zero(unsigned long long dividend, unsigned long long divisor)
*/

TEST(int_addition_has_defined_behavior_test, "int addition operations which have defined behavior")
{
	ASSERT(int_addition_has_defined_behavior(0, 0));
	ASSERT(int_addition_has_defined_behavior(-1, 0));
	ASSERT(int_addition_has_defined_behavior(0, -1));
	ASSERT(int_addition_has_defined_behavior(INT_MIN, 0));
	ASSERT(int_addition_has_defined_behavior((INT_MIN + 1), -1));
	ASSERT(int_addition_has_defined_behavior(INT_MAX, 0));
	ASSERT(int_addition_has_defined_behavior((INT_MAX - 1), 1));
}

TEST(int_addition_has_undefined_behavior_test, "int addition operations which have undefined behavior")
{
	ASSERT(not int_addition_has_defined_behavior(INT_MIN, -1));
	ASSERT(not int_addition_has_defined_behavior(INT_MIN, INT_MIN));
	ASSERT(not int_addition_has_defined_behavior(INT_MAX, 1));
	ASSERT(not int_addition_has_defined_behavior(INT_MAX, INT_MAX));
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		int_addition_has_defined_behavior_test,
		int_addition_has_undefined_behavior_test
	};
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
