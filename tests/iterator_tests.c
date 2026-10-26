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

/* comparators */
INLINE_OR_STATIC bool int_equal(int lhs, int rhs) {
	return (lhs == rhs);
}

INLINE_OR_STATIC bool int_greater_than(int lhs, int rhs) {
	return (lhs > rhs);
}

INLINE_OR_STATIC bool int_greater_than_or_equal(int lhs, int rhs) {
	return (lhs >= rhs);
}

INLINE_OR_STATIC bool int_less_than_or_equal(int lhs, int rhs) {
	return (lhs <= rhs);
}

INLINE_OR_STATIC bool int_less_than(int lhs, int rhs) {
	return (lhs < rhs);
}

INLINE_OR_STATIC bool double_equal(double lhs, double rhs) {
	return (lhs == rhs);
}

INLINE_OR_STATIC bool double_greater_than(double lhs, double rhs) {
	return (lhs > rhs);
}

INLINE_OR_STATIC bool double_less_than(double lhs, double rhs) {
	return (lhs < rhs);
}

/* Instantiate algorithm functions for int */
ITERATOR_TYPE_DEFINE_COMMON_FUNCTIONS(int, int)
ITERATOR_TYPE_DEFINE_COMMON_FUNCTIONS(const int, const_int)
ITERATOR_TYPE_DEFINE_SUM_FUNCTION(int, int)
ITERATOR_TYPE_DEFINE_REVERSE_FUNCTION(int, int)
ITERATOR_TYPE_DEFINE_SORT_FUNCTION(int, int)
ITERATOR_TYPE_DEFINE_COMMON_FUNCTIONS(const double, const_double)

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

/* Test: find, find_with, find_if, find_if_not, count, count_with, count_if, count_if_not */
TEST(iterator_func_find_and_count, "find and count variants")
{
	int a[] = {1, 2, 3, 2, -1, 2};
	iterator_type(int) const first = iterator_begin(a);
	iterator_type(int) const one_past_last = iterator_end(a, sizeof_array(a));
	iterator_type(int) iter = iterator_init();

	/* find first 2 */
	iter = find(int)(first, one_past_last, 2);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 1);
	ASSERT_INT_EQUAL(iterator_deref(iter), 2);
	iter = find_with(int)(first, one_past_last, 2, int_equal);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 1);
	ASSERT_INT_EQUAL(iterator_deref(iter), 2);

	/* find last 2 */
	iter = reverse_find(int)(first, one_past_last, 2);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 5);
	ASSERT_INT_EQUAL(iterator_deref(iter), 2);
	iter = reverse_find_with(int)(first, one_past_last, 2, int_equal);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 5);
	ASSERT_INT_EQUAL(iterator_deref(iter), 2);

	/* find not present */
	iter = find(int)(first, one_past_last, 99);
	ASSERT(iter == one_past_last);
	iter = reverse_find(int)(first, one_past_last, 99);
	ASSERT(iter == one_past_last);

	/* first negative */
	iter = find_if(int)(first, one_past_last, int_is_negative);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 4);
	ASSERT_INT_LESS(iterator_deref(iter), 0);

	/* find last negative */
	iter = reverse_find_if(int)(first, one_past_last, int_is_negative);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 4);
	ASSERT_INT_LESS(iterator_deref(iter), 0);

	/* find first element not equal to 1 */
	iter = find_if_not(int)(first, one_past_last, int_is_one);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 1);
	ASSERT_INT_NOT_EQUAL(iterator_deref(iter), 1);

	/* find last element not equal to 1 */
	iter = reverse_find_if_not(int)(first, one_past_last, int_is_one);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 5);
	ASSERT_INT_NOT_EQUAL(iterator_deref(iter), 1);

	/* count of value 2 */
	ASSERT_SIZE_EQUAL(count(int)(first, one_past_last, 2), 3U);
	ASSERT_SIZE_EQUAL(count_with(int)(first, one_past_last, 2, int_equal), 3U);

	/* count of even values */
	ASSERT_SIZE_EQUAL(count_if(int)(first, one_past_last, int_is_even), 3U);

	/* count of non-negative values */
	ASSERT_SIZE_EQUAL(count_if_not(int)(first, one_past_last, int_is_negative), 5U);
}

/* Test: find_with and count with */
TEST(iterator_func_find_with_and_count_with, "find_with and count_with variants")
{
	const int integers[] = {-3, -2, -1, 0, 1, 2, 3};
	const double numbers[] = {1.0, -0.0, 0.0, 2.0};

	iterator_type(const int) int_iter = iterator_init();
	iterator_type(const int) const int_first = iterator_begin(integers);
	iterator_type(const int) const int_one_past_last = iterator_end(integers, sizeof_array(integers));
	iterator_type(const double) iter = iterator_init();
	iterator_type(const double) const first = iterator_begin(numbers);
	iterator_type(const double) const one_past_last = iterator_end(numbers, sizeof_array(numbers));

	int_iter = find_with(const_int)(int_first, int_one_past_last, 0, int_less_than);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(int_iter - int_first), 0);
	ASSERT_INT_LESS(iterator_deref(int_iter), 0);
	int_iter = find_with(const_int)(int_first, int_one_past_last, 0, int_equal);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(int_iter - int_first), 3);
	ASSERT_INT_EQUAL(iterator_deref(int_iter), 0);
	int_iter = find_with(const_int)(int_first, int_one_past_last, 0, int_greater_than);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(int_iter - int_first), 4);
	ASSERT_INT_GREATER(iterator_deref(int_iter), 0);

	ASSERT_SIZE_EQUAL(count_with(const_int)(int_first, int_one_past_last, 0, int_less_than), 3U);
	ASSERT_SIZE_EQUAL(count_with(const_int)(int_first, int_one_past_last, 0, int_equal), 1U);
	ASSERT_SIZE_EQUAL(count_with(const_int)(int_first, int_one_past_last, 0, int_greater_than), 3U);

	iter = find_with(const_double)(first, one_past_last, 0.0, double_less_than);
	ASSERT(iter == one_past_last);
	iter = find_with(const_double)(first, one_past_last, 0.0, double_equal);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 1);
	iter = find_with(const_double)(first, one_past_last, 0.0, double_greater_than);
	ASSERT_PTRDIFF_EQUAL((ptrdiff_t)(iter - first), 0);
	
	ASSERT_SIZE_EQUAL(count_with(const_double)(first, one_past_last, 0.0, double_less_than), 0U);
	ASSERT_SIZE_EQUAL(count_with(const_double)(first, one_past_last, 0.0, double_equal), 2U);
	ASSERT_SIZE_EQUAL(count_with(const_double)(first, one_past_last, 0.0, double_greater_than), 2U);
}

/* Test: reverse (odd/even lengths and round-trip) */
TEST(iterator_func_reverse, "reverse and double-reverse")
{
	const int a[4] = {1, 2, 3, 4};
	const int b[5]  = { 1, 2, 3, 4, 5};
	int a_copy[4] = {0};
	int b_copy[5] = {0};
	int single_element_array[] = {1};

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

	/* single element */
	reverse(int)(iterator_begin(single_element_array), iterator_end(single_element_array, sizeof_array(single_element_array)));
	ASSERT_INT_EQUAL(single_element_array[0], 1);
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

/* Test: sort */
TEST(iterator_func_sort, "sort")
{
	int dummy[] = {0};
	int single_element_array[] = {1};
	int a[] = {-3, -2, -1, 0, 1, 2, 3};
	int b[] = {-1, -2, 4, 5, 0};
	int c[] = {-1, -2, 4, 5, 0};
	int d[] = {1, 0};
	int e[] = {0, 1};

	sort(int)(iterator_begin(dummy), iterator_end(dummy, 0), int_less_than_or_equal);
	ASSERT_INT_EQUAL(dummy[0], 0);
	sort(int)(iterator_begin(dummy), iterator_end(dummy, 0), int_greater_than_or_equal);
	ASSERT_INT_EQUAL(dummy[0], 0);

	sort(int)(iterator_begin(single_element_array), iterator_end(single_element_array, sizeof_array(single_element_array)), int_less_than_or_equal);
	ASSERT_INT_EQUAL(single_element_array[0], 1);
	sort(int)(iterator_begin(single_element_array), iterator_end(single_element_array, sizeof_array(single_element_array)), int_greater_than_or_equal);
	ASSERT_INT_EQUAL(single_element_array[0], 1);

	sort(int)(iterator_begin(a), iterator_end(a, sizeof_array(a)), int_less_than_or_equal);
	ASSERT_INT_EQUAL(a[0], -3);
	ASSERT_INT_EQUAL(a[1], -2);
	ASSERT_INT_EQUAL(a[2], -1);
	ASSERT_INT_EQUAL(a[3],  0);
	ASSERT_INT_EQUAL(a[4],  1);
	ASSERT_INT_EQUAL(a[5],  2);
	ASSERT_INT_EQUAL(a[6],  3);

	sort(int)(iterator_begin(a), iterator_end(a, sizeof_array(a)), int_greater_than_or_equal);
	ASSERT_INT_EQUAL(a[0],  3);
	ASSERT_INT_EQUAL(a[1],  2);
	ASSERT_INT_EQUAL(a[2],  1);
	ASSERT_INT_EQUAL(a[3],  0);
	ASSERT_INT_EQUAL(a[4], -1);
	ASSERT_INT_EQUAL(a[5], -2);
	ASSERT_INT_EQUAL(a[6], -3);

	sort(int)(iterator_begin(b), iterator_end(b, sizeof_array(b)), int_less_than_or_equal);
	ASSERT_INT_EQUAL(b[0], -2);
	ASSERT_INT_EQUAL(b[1], -1);
	ASSERT_INT_EQUAL(b[2],  0);
	ASSERT_INT_EQUAL(b[3],  4);
	ASSERT_INT_EQUAL(b[4],  5);

	sort(int)(iterator_begin(c), iterator_end(c, sizeof_array(c)), int_greater_than_or_equal);
	ASSERT_INT_EQUAL(c[0],  5);
	ASSERT_INT_EQUAL(c[1],  4);
	ASSERT_INT_EQUAL(c[2],  0);
	ASSERT_INT_EQUAL(c[3], -1);
	ASSERT_INT_EQUAL(c[4], -2);

	sort(int)(iterator_begin(d), iterator_end(d, sizeof_array(d)), int_less_than_or_equal);
	ASSERT_INT_EQUAL(d[0], 0);
	ASSERT_INT_EQUAL(d[1], 1);

	sort(int)(iterator_begin(e), iterator_end(e, sizeof_array(e)), int_greater_than_or_equal);
	ASSERT_INT_EQUAL(e[0], 1);
	ASSERT_INT_EQUAL(e[1], 0);
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
		iterator_func_find_with_and_count_with,
		iterator_func_reverse,
		iterator_func_sum_and_predicates,
		iterator_func_sort
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return TEST_RESULT_ERROR_CODE;
}
