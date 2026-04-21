#include "iterator_type.h"
#include "unit_testing.h"
#include "sizeof_array.h"

#include <stddef.h>
#include <stdio.h>

TEST(iterator_test_1, "Modifying an array and accessing its elements")
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
		ASSERT_EQUAL(iterator_deref(iter), count);
		ASSERT_EQUAL(iterator_deref(iter), array[index]);
		printf("Index %d: %d\n", (int) index, iterator_deref(iter));
		++count;
		++index;
	}
}

TEST(iterator_test_2, "Accessing the elements of a constant array in forward direction")
{
	size_t index = 0U;
	const int array[5] = {1, 2, 3, 4, 5};
	iterator_type(const int) iter = iterator_init();
	iterator_type(const int) const begin = iterator_begin(array);
	iterator_type(const int) const end = iterator_end(array, sizeof_array(array));

	foreach_iterator(iter, begin, end) {
		ASSERT_EQUAL(iterator_deref(iter), array[index]);
		printf("Index %d: %d\n", (int) index, iterator_deref(iter));
		++index;
	}
}

TEST(iterator_test_3, "Modifying an array and accessing its elements in reverse")
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
		ASSERT_EQUAL(iterator_deref(iter), array[index]);
		printf("Index %d: %d\n", (int) index, iterator_deref(iter));
	}
}

TEST(iterator_test_4, "Accessing the elements of a constant array in reverse")
{
	size_t index = 0U;
	const int array[5] = {1, 2, 3, 4, 5};
	iterator_type(const int) iter = iterator_init();
	iterator_type(const int) const begin = iterator_begin(array);
	iterator_type(const int) const end = iterator_end(array, sizeof_array(array));

	index = sizeof_array(array);
	foreach_iterator_in_reverse(iter, begin, end) {
		--index;
		ASSERT_EQUAL(iterator_deref(iter), array[index]);
		printf("Index %d: %d\n", (int) index, iterator_deref(iter));
	}
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		iterator_test_1,
		iterator_test_2,
		iterator_test_3,
		iterator_test_4
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
