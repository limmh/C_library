#ifndef SAFER_INTEGER_UTIL_H
#define SAFER_INTEGER_UTIL_H

#include "inline_or_static.h"
#include "macro_stringify.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/**
 * @brief Asserts without crashing the application (provided the input arguments are valid) and prints an error message to a file
 * (defined by its file pointer) if the Boolean condition is false
 * @param [in, out] file File pointer (MUST NOT be NULL)
 * @param [in] Boolean_condition Boolean expression which evaluates to true or false
 * @param [in] file_name Name of the source file where this function is called (MUST NOT be NULL)
 * @param [in] line_number Line where this function is called
 * @param [in] message Message to be displayed (MUST NOT be NULL)
 */
INLINE_OR_STATIC void safer_integer_assert(FILE *file, int Boolean_condition, const char *file_name, int line_number, const char *message)
{
	assert(file != NULL);
	assert(file_name != NULL);
	assert(message != NULL);
	if (!Boolean_condition) {
		fprintf(file, "File: %s\nAssertion failure at line %d: %s\n", file_name, line_number, message);
	}
}

#ifndef SAFER_INTEGER_ASSERT
/** @brief Macro for safer integer assertion (can be overridden by your own custom version) */
#define SAFER_INTEGER_ASSERT(condition) safer_integer_assert(stderr, condition, __FILE__, __LINE__, STRINGIFY(condition))
#endif

/*
Macros which check whether an integer is within a range [inclusively or exclusively].
Make sure all the macro arguments have the same signedness, i.e. all signed or all unsigned.
Make sure the minimum value [or lower bound value] is smaller than the maximum value [or upper bound value].
*/

/**
 * @brief Macro to check whether an integer is between the minimum and maximum values
 *
 * Avoid introducing expressions with side effects for each macro argument
 *
 * @param [in] integer Integer
 * @param [in] minimum Lowest integer value
 * @param [in] maximum Highest integer value
 * @return bool
 */
#define INTEGER_IS_WITHIN_RANGE(integer, minimum, maximum) ((integer) >= (minimum) && (integer) <= (maximum))

/**
 * @brief Macro to check whether an integer is between the lower and upper bounds
 *
 * Avoid introducing expressions with side effects for each macro argument
 *
 * @param [in] integer Integer
 * @param [in] lower_bound Integer value which is before the minimum allowed value
 * @param [in] upper_bound Integer value which is after the maximum allowed value 
 * @return bool
 */
#define INTEGER_IS_WITHIN_RANGE_EXCLUSIVE(integer, lower_bound, upper_bound) \
	((integer) > (lower_bound) && (integer) < (upper_bound))

#endif
