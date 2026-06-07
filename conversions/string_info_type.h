#ifndef STRING_INFO_TYPE_H
#define STRING_INFO_TYPE_H

#include "string_to_integer_error_codes.h"
#include "Boolean_type.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief String info type */
typedef struct int_string_info_type {
	const char *string;
	size_t length;
	size_t start_index; /* index of first digit */
	size_t end_index;   /* index of final digit */
	int base;
	string_to_int_error_type error;
	bool contains_valid_integer;
	bool integer_is_negative;
} int_string_info_type;

/**
 * @brief The function return information about the first integer in a string
 * @param [in] string Pointer to the first character
 * @param [in] length Number of bytes to be read by the function
 * @param [in] base Number base (between 2 and 36 inclusive)
 * @return int_string_info_type
 */
int_string_info_type string_to_int_get_string_info(const char *string, size_t length, int base);

#ifdef __cplusplus
}
#endif

#endif
