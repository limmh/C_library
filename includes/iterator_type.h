#ifndef ITERATOR_TYPE_H
#define ITERATOR_TYPE_H

#include <assert.h>
#include <stddef.h>

/*
Usage example:

int main(void)
{
	enum { array_size = 5 };
	int array[array_size] = {1, 2, 3, 4, 5};
	iterator_type(int) it = iterator_init();
	iterator_type(int) begin = iterator_begin(array);
	iterator_type(int) end = iterator_end(begin, array_size);
	printf("Printing the numbers\n");
	foreach_iterator(it, begin, end) {
		printf("%d\n", iterator_deref(it));
	}
	iterator_reset(it);
	printf("Printing the numbers in reverse order\n");
	foreach_iterator_in_reverse(it, begin, end) {
		printf("%d\n", iterator_deref(it));
	}
	return 0;
}
*/

/** @brief Macro to define an iterator type */
#define iterator_type(element_type) element_type *

/** @brief Macro to initialize an iterator */
#define iterator_init() NULL

/** @brief Macro to dereference an iterator */
#define iterator_deref(iterator) (*(iterator))

/** @brief Macro that returns an incremented iterator */
#define iterator_increment(iterator, offset) ((iterator) + (offset))

/** @brief Macro that returns a decremented iterator */
#define iterator_decrement(iterator, offset) ((iterator) - (offset))

/** @brief Macro that indicates the iterator is the starting iterator */
#define iterator_begin(first_iterator) (first_iterator)

/** @brief Macro that indicates the iterator is one past the end */
#define iterator_end(iterator, offset) iterator_increment(iterator, offset)

/** @brief Macro that resets an iterator */
#define iterator_reset(iterator) ((iterator) = iterator_init())

/** @brief foreach macro */
#define foreach_iterator(iterator, first_iterator, one_past_last_iterator) \
	for ((iterator) = (assert((first_iterator) <= (one_past_last_iterator)), (first_iterator)); \
		(iterator) != (one_past_last_iterator); \
		(iterator) = iterator_increment(iterator, 1))

/** @brief foreach macro in reverse */
#define foreach_iterator_in_reverse(iterator, first_iterator, one_past_last_iterator) \
	for ((iterator) = (assert((first_iterator) <= (one_past_last_iterator)), iterator_decrement(one_past_last_iterator, 1)); \
		(iterator) >= first_iterator; \
		(iterator) = iterator_decrement(iterator, 1))

#endif
