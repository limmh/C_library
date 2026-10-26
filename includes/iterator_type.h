#ifndef ITERATOR_TYPE_H
#define ITERATOR_TYPE_H

#include "Boolean_type.h"
#include "inline_or_static.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

/*
Usage example:
#include "iterator_type.h"
#include <stdio.h>

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
	for ((iterator) = (assert((first_iterator) <= (one_past_last_iterator)), one_past_last_iterator); \
		((iterator) != (first_iterator)) && ((iterator) = iterator_decrement(iterator, 1)) != (one_past_last_iterator); \
		)

/* These functions are inspired by the C++ STL algorithms (for_each, find, count, all_of, any_of, none_of, reverse, etc.),
but they are intentionally limited to contiguous pointer ranges over arrays. They do not provide a full generic
iterator abstraction for arbitrary container types. */

/** @brief for_each_value function template */
#define ITERATOR_TYPE_DEFINE_FOR_EACH_VALUE_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC void prefix##_for_each_value( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		void (*func)(element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			func(iterator_deref(iter)); \
		} \
	}

/** @brief for_each function template */
#define ITERATOR_TYPE_DEFINE_FOR_EACH_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC void prefix##_for_each( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		void (*func)(element_type *) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			func(iter); \
		} \
	}

/** @brief bitwise_compare_equal function template */
#define ITERATOR_TYPE_DEFINE_BITWISE_COMPARE_EQUAL_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC bool prefix##_bitwise_compare_equal(element_type *ptr_a, element_type *ptr_b) { \
		return memcmp(ptr_a, ptr_b, sizeof(*ptr_a)) == 0; \
	}

/** @brief find function template */
#define ITERATOR_TYPE_DEFINE_FIND_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC iterator_type(element_type) prefix##_find( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		element_type value \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (prefix##_bitwise_compare_equal(iter, &value)) break; \
		} \
		return iter; \
	}

/** @brief find_with function template */
#define ITERATOR_TYPE_DEFINE_FIND_WITH_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC iterator_type(element_type) prefix##_find_with( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		element_type rhs_value, \
		bool (*compare)(element_type, element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		assert(compare != NULL); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (compare(iterator_deref(iter), rhs_value)) break; \
		} \
		return iter; \
	}

/** @brief find_if function template */
#define ITERATOR_TYPE_DEFINE_FIND_IF_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC iterator_type(element_type) prefix##_find_if( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		bool (*predicate)(element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (predicate(iterator_deref(iter))) break; \
		} \
		return iter; \
	}

/** @brief find_if_not function template */
#define ITERATOR_TYPE_DEFINE_FIND_IF_NOT_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC iterator_type(element_type) prefix##_find_if_not( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		bool (*predicate)(element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (!predicate(iterator_deref(iter))) break; \
		} \
		return iter; \
	}

/** @brief reverse_find function template */
#define ITERATOR_TYPE_DEFINE_REVERSE_FIND_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC iterator_type(element_type) prefix##_reverse_find( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		element_type value \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator_in_reverse(iter, iter_first, iter_one_past_last) { \
			if (prefix##_bitwise_compare_equal(iter, &value)) return iter; \
		} \
		return iter_one_past_last; \
	}

/** @brief reverse_find_with function template */
#define ITERATOR_TYPE_DEFINE_REVERSE_FIND_WITH_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC iterator_type(element_type) prefix##_reverse_find_with( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		element_type rhs_value, \
		bool (*compare)(element_type, element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		assert(compare != NULL); \
		foreach_iterator_in_reverse(iter, iter_first, iter_one_past_last) { \
			if (compare(iterator_deref(iter), rhs_value)) return iter; \
		} \
		return iter_one_past_last; \
	}

/** @brief reverse_find_if function template */
#define ITERATOR_TYPE_DEFINE_REVERSE_FIND_IF_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC iterator_type(element_type) prefix##_reverse_find_if( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		bool (*predicate)(element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator_in_reverse(iter, iter_first, iter_one_past_last) { \
			if (predicate(iterator_deref(iter))) return iter; \
		} \
		return iter_one_past_last; \
	}

/** @brief reverse_find_if_not function template */
#define ITERATOR_TYPE_DEFINE_REVERSE_FIND_IF_NOT_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC iterator_type(element_type) prefix##_reverse_find_if_not( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		bool (*predicate)(element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator_in_reverse(iter, iter_first, iter_one_past_last) { \
			if (!predicate(iterator_deref(iter))) return iter; \
		} \
		return iter_one_past_last; \
	}

/** @brief count function template */
#define ITERATOR_TYPE_DEFINE_COUNT_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC size_t prefix##_count( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		element_type value \
	) { \
		size_t count = 0U; \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (prefix##_bitwise_compare_equal(iter, &value)) ++count; \
		} \
		return count; \
	}

/** @brief count_with function template */
#define ITERATOR_TYPE_DEFINE_COUNT_WITH_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC size_t prefix##_count_with( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		element_type rhs_value, \
		bool (*compare)(element_type, element_type) \
	) { \
		size_t count = 0U; \
		iterator_type(element_type) iter = iterator_init(); \
		assert(compare != NULL); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (compare(iterator_deref(iter), rhs_value)) ++count; \
		} \
		return count; \
	}

/** @brief count_if function template */
#define ITERATOR_TYPE_DEFINE_COUNT_IF_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC size_t prefix##_count_if( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		bool (*predicate)(element_type) \
	) { \
		size_t count = 0U; \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (predicate(iterator_deref(iter))) ++count; \
		} \
		return count; \
	}

/** @brief count_if_not function template */
#define ITERATOR_TYPE_DEFINE_COUNT_IF_NOT_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC size_t prefix##_count_if_not( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		bool (*predicate)(element_type) \
	) { \
		size_t count = 0U; \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (!predicate(iterator_deref(iter))) ++count; \
		} \
		return count; \
	}

/** @brief all_of function template */
#define ITERATOR_TYPE_DEFINE_ALL_OF_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC bool prefix##_all_of( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		bool (*predicate)(element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (!predicate(iterator_deref(iter))) break; \
		} \
		return (iter == iter_one_past_last); \
	}

/** @brief any_of function template */
#define ITERATOR_TYPE_DEFINE_ANY_OF_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC bool prefix##_any_of( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		bool (*predicate)(element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (predicate(iterator_deref(iter))) break; \
		} \
		return (iter != iter_one_past_last); \
	}

/** @brief none_of function template */
#define ITERATOR_TYPE_DEFINE_NONE_OF_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC bool prefix##_none_of( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		bool (*predicate)(element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first, iter_one_past_last) { \
			if (predicate(iterator_deref(iter))) break; \
		} \
		return (iter == iter_one_past_last); \
	}

/** @brief sum function template */
#define ITERATOR_TYPE_DEFINE_SUM_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC element_type prefix##_sum( \
		const iterator_type(element_type) iter_first, \
		const iterator_type(element_type) iter_one_past_last \
	) { \
		element_type sum = (element_type) 0; \
		const iterator_type(element_type) iter = iterator_init(); \
		foreach_iterator(iter, iter_first,  iter_one_past_last) { \
			sum += iterator_deref(iter); \
		} \
		return sum; \
	}

/** @brief reverse function template */
#define ITERATOR_TYPE_DEFINE_REVERSE_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC void prefix##_reverse( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last \
	) { \
		iterator_type(element_type) iter_front = iterator_init(); \
		iterator_type(element_type) iter_back = iter_one_past_last; \
		foreach_iterator(iter_front, iter_first, iter_back) { \
			iter_back = iterator_decrement(iter_back, 1); \
			if (iter_back != iter_front) { \
				element_type tmp = iterator_deref(iter_front); \
				iterator_deref(iter_front) = iterator_deref(iter_back); \
				iterator_deref(iter_back) = tmp; \
			} else { \
				break; \
			} \
		} \
	}

/** @brief sort function template (compare returns true: no swapping of two adjacent elements, otherwise swapping takes place) */
#define ITERATOR_TYPE_DEFINE_SORT_FUNCTION(element_type, prefix) \
	INLINE_OR_STATIC void prefix##_sort( \
		iterator_type(element_type) iter_first, \
		iterator_type(element_type) iter_one_past_last, \
		bool (*compare)(element_type, element_type) \
	) { \
		iterator_type(element_type) iter = iterator_init(); \
		size_t count = 0U; \
		size_t distance = (size_t) (iter_one_past_last - iter_first); \
		assert(compare != NULL); \
		for (count = 1U; count < distance; ++count) { \
			bool swap_performed = false; \
			iterator_type(element_type) iter_end = iterator_decrement(iter_one_past_last, count); \
			foreach_iterator(iter, iter_first, iter_end) { \
				iterator_type(element_type) iter_next = iterator_increment(iter, 1); \
				if (!compare(iterator_deref(iter), iterator_deref(iter_next))) { \
					element_type tmp = iterator_deref(iter); \
					iterator_deref(iter) = iterator_deref(iter_next); \
					iterator_deref(iter_next) = tmp; \
					swap_performed = true; \
				} \
			} \
			if (!swap_performed) break; \
		} \
	}

#define ITERATOR_TYPE_DEFINE_COMMON_FUNCTIONS(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_FOR_EACH_VALUE_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_FOR_EACH_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_BITWISE_COMPARE_EQUAL_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_FIND_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_FIND_WITH_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_FIND_IF_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_FIND_IF_NOT_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_REVERSE_FIND_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_REVERSE_FIND_WITH_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_REVERSE_FIND_IF_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_REVERSE_FIND_IF_NOT_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_COUNT_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_COUNT_WITH_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_COUNT_IF_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_COUNT_IF_NOT_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_ALL_OF_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_ANY_OF_FUNCTION(element_type, prefix) \
	ITERATOR_TYPE_DEFINE_NONE_OF_FUNCTION(element_type, prefix)

#define FOR_EACH_VALUE(prefix) prefix##_for_each_value
#define FOR_EACH(prefix) prefix##_for_each
#define FIND(prefix) prefix##_find
#define FIND_WITH(prefix) prefix##_find_with
#define FIND_IF(prefix) prefix##_find_if
#define FIND_IF_NOT(prefix) prefix##_find_if_not
#define REVERSE_FIND(prefix) prefix##_reverse_find
#define REVERSE_FIND_WITH(prefix) prefix##_reverse_find_with
#define REVERSE_FIND_IF(prefix) prefix##_reverse_find_if
#define REVERSE_FIND_IF_NOT(prefix) prefix##_reverse_find_if_not
#define COUNT(prefix) prefix##_count
#define COUNT_WITH(prefix) prefix##_count_with
#define COUNT_IF(prefix) prefix##_count_if
#define COUNT_IF_NOT(prefix) prefix##_count_if_not
#define ALL_OF(prefix) prefix##_all_of
#define ANY_OF(prefix) prefix##_any_of
#define NONE_OF(prefix) prefix##_none_of
#define SUM(prefix) prefix##_sum
#define REVERSE(prefix) prefix##_reverse
#define SORT(prefix) prefix##_sort

#ifdef ITERATOR_TYPE_SUPPORTS_LOWERCASE_FUNCTION_MACROS
#define for_each_value(prefix) FOR_EACH_VALUE(prefix)
#define for_each(prefix) FOR_EACH(prefix)
#define find(prefix) FIND(prefix)
#define find_with(prefix) FIND_WITH(prefix)
#define find_if(prefix) FIND_IF(prefix)
#define find_if_not(prefix) FIND_IF_NOT(prefix)
#define reverse_find(prefix) REVERSE_FIND(prefix)
#define reverse_find_with(prefix) REVERSE_FIND_WITH(prefix)
#define reverse_find_if(prefix) REVERSE_FIND_IF(prefix)
#define reverse_find_if_not(prefix) REVERSE_FIND_IF_NOT(prefix)
#define count(prefix) COUNT(prefix)
#define count_with(prefix) COUNT_WITH(prefix)
#define count_if(prefix) COUNT_IF(prefix)
#define count_if_not(prefix) COUNT_IF_NOT(prefix)
#define all_of(prefix) ALL_OF(prefix)
#define any_of(prefix) ANY_OF(prefix)
#define none_of(prefix) NONE_OF(prefix)
#define sum(prefix) SUM(prefix)
#define reverse(prefix) REVERSE(prefix)
#define sort(prefix) SORT(prefix)
#endif

#endif
