#ifndef ITERATOR_TYPE_SUPPORTS_LOWERCASE_FUNCTION_MACROS
#define ITERATOR_TYPE_SUPPORTS_LOWERCASE_FUNCTION_MACROS
#endif

#include "alternative_operators.h"
#include "inline_or_static.h"
#include "iterator_type.h"
#include "unit_testing.h"
#include "sizeof_array.h"

#include <stddef.h>
#include <stdio.h>

TEST(foreach_iterator_test_1, "Modifying an array and accessing its elements")
{
	size_t index = 0U;
	int count = 0;
	int array[5] = {0};
	iterator_type(int) iter = iterator_init();
	iterator_type(int) const begin = iterator_begin(array);
	iterator_type(int) const end = iterator_end(array, sizeof_array(array));

	foreach_iterator(iter, begin, end) {
		++count;
		iterator_deref(iter) = count;
	}

	count = 1;
	foreach_iterator(iter, begin, end) {
		ASSERT_INT_EQUAL(iterator_deref(iter), count);
		ASSERT_INT_EQUAL(iterator_deref(iter), array[index]);
		printf("Index %d: %d\n", (int) index, iterator_deref(iter));
		++count;
		++index;
	}
}

TEST(foreach_iterator_test_2, "Accessing the elements of a constant array in forward direction")
{
	size_t index = 0U;
	const int array[5] = {1, 2, 3, 4, 5};
	iterator_type(const int) iter = iterator_init();
	iterator_type(const int) const begin = iterator_begin(array);
	iterator_type(const int) const end = iterator_end(array, sizeof_array(array));

	foreach_iterator(iter, begin, end) {
		ASSERT_INT_EQUAL(iterator_deref(iter), array[index]);
		printf("Index %d: %d\n", (int) index, iterator_deref(iter));
		++index;
	}
}

TEST(foreach_iterator_in_reverse_test_1, "Modifying an array and accessing its elements in reverse")
{
	size_t index = 0U;
	int count = 0;
	int array[5] = {0};
	iterator_type(int) iter = iterator_init();
	iterator_type(int) const begin = iterator_begin(array);
	iterator_type(int) const end = iterator_end(array, sizeof_array(array));

	foreach_iterator(iter, begin, end) {
		++count;
		iterator_deref(iter) = count;
	}

	index = sizeof_array(array);
	foreach_iterator_in_reverse(iter, begin, end) {
		--index;
		ASSERT_INT_EQUAL(iterator_deref(iter), array[index]);
		printf("Index %d: %d\n", (int) index, iterator_deref(iter));
	}
}

TEST(foreach_iterator_in_reverse_test_2, "Accessing the elements of a constant array in reverse")
{
	size_t index = 0U;
	const int array[5] = {1, 2, 3, 4, 5};
	iterator_type(const int) iter = iterator_init();
	iterator_type(const int) const begin = iterator_begin(array);
	iterator_type(const int) const end = iterator_end(array, sizeof_array(array));

	index = sizeof_array(array);
	foreach_iterator_in_reverse(iter, begin, end) {
		--index;
		ASSERT_INT_EQUAL(iterator_deref(iter), array[index]);
		printf("Index %d: %d\n", (int) index, iterator_deref(iter));
	}
}

/* helper callbacks */
INLINE_OR_STATIC void int_inc_by_one(int *p_value) {
	++(*p_value); 
}

INLINE_OR_STATIC void int_local_copy_inc_by_one(int value) {
	++value;
}

INLINE_OR_STATIC void collect_value_to_array(int value) {
	(void) value;
}

/* predicate examples */
INLINE_OR_STATIC bool int_is_even(int value) {
	return (value % 2) == 0;
}

INLINE_OR_STATIC bool int_is_negative(int value) {
	return (value < 0);
}

INLINE_OR_STATIC bool int_is_one(int value) {
	return (value == 1);
}

INLINE_OR_STATIC bool int_greater_than_3(int v) {
	return (v > 3);
}

/* Instantiate algorithm functions for int */
ITERATOR_TYPE_DEFINE_COMMON_FUNCTIONS(int, int)
ITERATOR_TYPE_DEFINE_COMMON_FUNCTIONS(const int, const_int)
ITERATOR_TYPE_DEFINE_SUM_FUNCTION(int, int)
ITERATOR_TYPE_DEFINE_REVERSE_FUNCTION(int, int)

/* Test: empty range */
TEST(iterator_func_empty_range, "Algorithms handle empty ranges gracefully")
{
	int a[1] = {42};
	iterator_type(int) first = iterator_begin(a);
	iterator_type(int) one_past_last = iterator_end(a, 0); /* empty range */
	iterator_type(int) iter = iterator_init();

	/* for_each does nothing */
	for_each(int)(first, one_past_last, int_inc_by_one);
	ASSERT_INT_EQUAL(a[0], 42);

	/* find returns one past last */
	iter = find(int)(first, one_past_last, 42);
	ASSERT(iter == one_past_last);

	/* count is zero */
	ASSERT_SIZE_EQUAL(count(int)(first, one_past_last, 42), 0);

	/* sum is zero */
	ASSERT_INT_EQUAL(sum(int)(first, one_past_last), 0);
}

/* Test: for_each_value vs for_each pointer */
TEST(iterator_func_for_each, "for_each_value passes copies; for_each passes pointers")
{
	size_t index = 0;
	const int original[] = {1, 2, 3, 4};
	int a[sizeof_array(original)] = {0};
	memcpy(a, original, sizeof(original));

	/* for_each_value: callback receives copies, array remains unchanged */
	for_each_value(int)(iterator_begin(a), iterator_end(a, sizeof_array(a)), int_local_copy_inc_by_one);
	for (index = 0; index < sizeof_array(a); ++index) {
		ASSERT_INT_EQUAL(a[index], original[index]);
	}

	/* for_each (pointer): increment each element in-place */
	for_each(int)(iterator_begin(a), iterator_end(a, sizeof_array(a)), int_inc_by_one);
	for (index = 0; index < sizeof_array(a); ++index) {
		ASSERT_INT_EQUAL(a[index], original[index] + 1);
	}
}

/* Test: find, find_if, find_if_not, count, count_if, count_if_not */
TEST(iterator_func_find_and_count, "find and count variants")
{
	int a[] = {1, 2, 3, 2, -1, 2};
	iterator_type(int) first = iterator_begin(a);
	iterator_type(int) one_past_last = iterator_end(a, sizeof_array(a));
	iterator_type(int) iter = iterator_init();

	/* find first 2 */
	iter = find(int)(first, one_past_last, 2);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 1);
	ASSERT_INT_EQUAL(iterator_deref(iter), 2);

	/* find not present */
	iter = find(int)(first, one_past_last, 99);
	ASSERT(iter == one_past_last);

	/* find_if: first negative */
	iter = find_if(int)(first, one_past_last, int_is_negative);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 4);
	ASSERT_INT_LESS(iterator_deref(iter), 0);

	/* find_if_not: find first element not equal to 1 */
	iter = find_if_not(int)(first, one_past_last, int_is_one);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 1);
	ASSERT_INT_NOT_EQUAL(iterator_deref(iter), 1);

	/* count of value 2 */
	ASSERT_SIZE_EQUAL(count(int)(first, one_past_last, 2), 3U);

	/* count of even values */
	ASSERT_SIZE_EQUAL(count_if(int)(first, one_past_last, int_is_even), 3U);

	/* count of non-negative values */
	ASSERT_SIZE_EQUAL(count_if_not(int)(first, one_past_last, int_is_negative), 5U);
}

/* Test: reverse (odd/even lengths and round-trip) */
TEST(iterator_func_reverse, "reverse and double-reverse")
{
	const int a[4] = {1, 2, 3, 4};
	const int b[5]  = { 1, 2, 3, 4, 5};
	int a_copy[4] = {0};
	int b_copy[5] = {0};

	memcpy(a_copy, a, sizeof(a_copy));
	memcpy(b_copy, b, sizeof(b_copy));

	/* even length: reverse */
	reverse(int)(iterator_begin(a_copy), iterator_end(a_copy, sizeof_array(a_copy)));
	ASSERT_INT_EQUAL(a_copy[0], 4);
	ASSERT_INT_EQUAL(a_copy[1], 3);
	ASSERT_INT_EQUAL(a_copy[2], 2);
	ASSERT_INT_EQUAL(a_copy[3], 1);

	/* even length: reversing again restores */
	reverse(int)(iterator_begin(a_copy), iterator_end(a_copy, sizeof_array(a_copy)));
	ASSERT_INT_EQUAL(a_copy[0], 1);
	ASSERT_INT_EQUAL(a_copy[1], 2);
	ASSERT_INT_EQUAL(a_copy[2], 3);
	ASSERT_INT_EQUAL(a_copy[3], 4);

	/* odd length: reverse */
	reverse(int)(iterator_begin(b_copy), iterator_end(b_copy, sizeof_array(b_copy)));
	ASSERT_INT_EQUAL(b_copy[0], 5);
	ASSERT_INT_EQUAL(b_copy[1], 4);
	ASSERT_INT_EQUAL(b_copy[2], 3);
	ASSERT_INT_EQUAL(b_copy[3], 2);
	ASSERT_INT_EQUAL(b_copy[4], 1);

	/* odd length: reversing again restores */
	reverse(int)(iterator_begin(b_copy), iterator_end(b_copy, sizeof_array(b_copy)));
	ASSERT_INT_EQUAL(b_copy[0], 1);
	ASSERT_INT_EQUAL(b_copy[1], 2);
	ASSERT_INT_EQUAL(b_copy[2], 3);
	ASSERT_INT_EQUAL(b_copy[3], 4);
	ASSERT_INT_EQUAL(b_copy[4], 5);
}

/* Test: sum and all/any/none */
TEST(iterator_func_sum_and_predicates, "sum, all_of, any_of, none_of")
{
	const int a[5] = {1, 1, 1, 1, 1};
	const int b[4] = {1, 2, 3, 4};
	const int c[1] = {0};

	/* empty ranges */
	ASSERT_INT_EQUAL(sum(int)(iterator_begin(a), iterator_end(a, 0)), 0);
	ASSERT_INT_EQUAL(sum(int)(iterator_begin(b), iterator_end(b, 0)), 0);
	ASSERT_INT_EQUAL(sum(int)(iterator_begin(c), iterator_end(c, 0)), 0);
	ASSERT(all_of(const_int)(iterator_begin(a), iterator_end(a, 0), int_is_one));
	ASSERT(not any_of(const_int)(iterator_begin(b), iterator_end(b, 0), int_greater_than_3));
	ASSERT(none_of(const_int)(iterator_begin(c), iterator_end(c, 0), int_greater_than_3));
	
	/* full ranges */
	ASSERT_INT_EQUAL(sum(int)(iterator_begin(a), iterator_end(a, sizeof_array(a))), 5);
	ASSERT_INT_EQUAL(sum(int)(iterator_begin(b), iterator_end(b, sizeof_array(b))), 10);
	ASSERT_INT_EQUAL(sum(int)(iterator_begin(c), iterator_end(c, sizeof_array(c))), 0);
	ASSERT(all_of(const_int)(iterator_begin(a), iterator_end(a, sizeof_array(a)), int_is_one));
	ASSERT(any_of(const_int)(iterator_begin(b), iterator_end(b, sizeof_array(b)), int_greater_than_3));
	ASSERT(none_of(const_int)(iterator_begin(c), iterator_end(c, sizeof_array(c)), int_greater_than_3));
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		foreach_iterator_test_1,
		foreach_iterator_test_2,
		foreach_iterator_in_reverse_test_1,
		foreach_iterator_in_reverse_test_2,
		iterator_func_empty_range,
		iterator_func_for_each,
		iterator_func_find_and_count,
		iterator_func_reverse,
		iterator_func_sum_and_predicates
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return TEST_RESULT_ERROR_CODE;
}
