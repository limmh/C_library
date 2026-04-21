#ifndef STRING_REFERENCE_H
#define STRING_REFERENCE_H

#include "Boolean_type.h"
#include "inline_or_static.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
String reference: a data structure that can reference part of a string or the whole string
The life time of the underlying string must be longer than the reference itself
*/

/** @brief String content is mutable */
typedef struct stringref_type
{
	char *string;
	size_t length;
} stringref_type;

/** @brief String content is not mutable */
typedef struct const_stringref_type
{
	const char *string;
	size_t length;
} const_stringref_type;

/**
 * @brief Converts mutable string reference to constant string reference
 * @param [in] stringref Mutable string reference
 * @return const_stringref_type Constant string reference
 */
INLINE_OR_STATIC
const_stringref_type
stringref_to_const_stringref(stringref_type stringref)
{
	const_stringref_type const_stringref = {NULL, 0U};
	const_stringref.string = stringref.string;
	const_stringref.length = stringref.length;
	return const_stringref;
}

/**
 * @brief Checks whether a mutable string reference is valid
 * @param [in] stringref Mutable string reference
 * @return bool true if valid, otherwise false
 */
INLINE_OR_STATIC
bool
stringref_is_valid(stringref_type stringref)
{
	return (stringref.string != NULL);
}

/**
 * @brief Checks whether a constant string reference is valid
 * @param [in] const_stringref Constant string reference
 * @return bool true if valid, otherwise false
 */
INLINE_OR_STATIC
bool
const_stringref_is_valid(const_stringref_type const_stringref)
{
	return (const_stringref.string != NULL);
}

/**
 * @brief Checks whether a mutable string reference refers to an empty string
 * @param [in] stringref Mutable string reference
 * @return bool true if the referenced string is empty, otherwise false
 */
INLINE_OR_STATIC
bool
stringref_string_is_empty(stringref_type stringref)
{
	return (stringref.string != NULL && stringref.length > 0U) ?
		(stringref.string[0] == '\0') : true;
}

/**
 * @brief Checks whether a constant string reference refers to an empty string
 * @param [in] const_stringref Constant string reference
 * @return bool true if the reference string is empty, otherwise false
 */
INLINE_OR_STATIC
bool
const_stringref_string_is_empty(const_stringref_type const_stringref)
{
	return (const_stringref.string != NULL && const_stringref.length > 0U) ?
		(const_stringref.string[0] == '\0') : true;
}

/**
 * @brief Creates a string reference from a mutable string or substring
 * @param [in] string String or substring
 * @param [in] length Number of bytes
 * @return stringref_type New instance of mutable string reference
 */
INLINE_OR_STATIC
stringref_type
string_to_stringref(char *string, size_t length)
{
	stringref_type stringref = {NULL, 0U};
	stringref.string = string;
	stringref.length = length;
	return stringref;
}

/**
 * @brief Creates a constant string reference from a mutable or read-only string or substring
 * @param [in] string String or substring
 * @param [in] length Number of bytes
 * @return const_stringref_type New instance of constant string reference
 */
INLINE_OR_STATIC
const_stringref_type
string_to_const_stringref(const char *string, size_t length)
{
	const_stringref_type stringref = {NULL, 0U};
	stringref.string = string;
	stringref.length = length;
	return stringref;
}

/**
 * @brief Determines the number of bytes before the first terminating null character
 * @param stringref Constant string reference
 * @return size_t Number of bytes before the first null character
 *
 * - ASCII string: The number of characters before the first '\0' found in the string being referenced.
 *                 If no '\0' is found, the result is the same as the length.
 * - UTF-8 string: The number of bytes before the first '\0' found in the string being referenced.
 *                 If no '\0' is found, the result is the same as the length.
 */
INLINE_OR_STATIC
size_t
const_stringref_string_length(const_stringref_type stringref)
{
	size_t length = 0U;
	if (stringref.string != NULL) {
		size_t index = 0U;
		for (; index < stringref.length; ++index) {
			if (stringref.string[index] == '\0') {
				break;
			}
		}
		length = index;
	}
	return length;
}

/**
 * @brief Determines the number of bytes before the first terminating null character
 * @param stringref Mutable string reference
 * @return size_t Number of bytes before the first null character
 */
INLINE_OR_STATIC
size_t
stringref_string_length(stringref_type stringref)
{
	const_stringref_type const_stringref = stringref_to_const_stringref(stringref);
	return const_stringref_string_length(const_stringref);
}

/**
 * @brief Checks whether the referenced string is null-terminated
 * @param [in] stringref Constant string reference
 * @return bool true if null-terminated, otherwise false
 */
INLINE_OR_STATIC
bool
const_stringref_string_is_null_terminated(const_stringref_type stringref)
{
	return const_stringref_string_length(stringref) < stringref.length;
}

/**
 * @brief Checks whether the referenced string is null-terminated
 * @param [in] stringref Mutable string reference
 * @return bool true if null-terminated, otherwise false
 */
INLINE_OR_STATIC
bool
stringref_string_is_null_terminated(stringref_type stringref)
{
	return stringref_string_length(stringref) < stringref.length;
}

/**
 * @brief Copies the referenced string to a buffer, limited by the size of the buffer
 * @param [in] stringref Constant string reference
 * @param [out] buffer Destination buffer to store the reference string
 * @param [in] buffer_size Number of bytes of the destination buffer
 */
INLINE_OR_STATIC
void
const_stringref_to_string(const_stringref_type stringref, char *buffer, size_t buffer_size)
{
	assert(stringref.string != NULL);
	assert(buffer != NULL);
	if ((stringref.string != NULL) && (buffer != NULL) && (buffer_size > 0U)) {
		const size_t number_of_bytes = buffer_size - 1U;
		const size_t number_of_bytes_to_copy = (stringref.length <= number_of_bytes) ? stringref.length : number_of_bytes;
		if (number_of_bytes_to_copy > 0U) {
			memcpy(buffer, stringref.string, number_of_bytes_to_copy);
		}
		buffer[number_of_bytes_to_copy] = '\0';
	}
}

/**
 * @brief Copies the referenced string to a buffer, limited by the size of the buffer
 * @param [in] stringref Mutable string reference
 * @param [out] buffer Destination buffer to store the reference string
 * @param [in] buffer_size Number of bytes of the destination buffer
 */
INLINE_OR_STATIC
void
stringref_to_string(stringref_type stringref, char *buffer, size_t buffer_size)
{
	const_stringref_type const_stringref = stringref_to_const_stringref(stringref);
	const_stringref_to_string(const_stringref, buffer, buffer_size);
}

/**
 * @brief Checks whether two referenced strings are identical up to their first null characters
 * @param [in] strref1 Constant string reference 1
 * @param [in] strref2 Constant string reference 2
 * @return bool
 */
INLINE_OR_STATIC
bool
const_stringref_strings_are_equal(const_stringref_type strref1, const_stringref_type strref2)
{
	bool result = false;
	if (const_stringref_is_valid(strref1)) {
		const size_t length1 = const_stringref_string_length(strref1);
		if (const_stringref_is_valid(strref2)) {
			const size_t length2 = const_stringref_string_length(strref2);
			result = (length1 == length2) ? (memcmp(strref1.string, strref2.string, length1) == 0) : false;
		} else {
			result = (length1 == 0U);
		}
	} else {
		if (const_stringref_is_valid(strref2)) {
			const size_t length2 = const_stringref_string_length(strref2);
			result = (length2 == 0U);
		} else {
			result = true;
		}
	}
	return result;
}

/**
 * @brief Checks whether two referenced strings are of the same length and are identical bitwise
 * @param [in] strref1 Constant string reference 1
 * @param [in] strref2 Constant string reference 2
 * @return bool
 */
INLINE_OR_STATIC
bool
const_stringref_contents_are_equal(const_stringref_type strref1, const_stringref_type strref2)
{
	bool result = false;
	if (const_stringref_is_valid(strref1)) {
		if (const_stringref_is_valid(strref2)) {
			result = (strref1.length == strref2.length) ? (memcmp(strref1.string, strref2.string, strref1.length) == 0) : false;
		} else {
			result = (strref1.length == 0U);
		}
	} else {
		if (const_stringref_is_valid(strref2)) {
			result = (strref2.length == 0U);
		} else {
			result = true;
		}
	}
	return result;
}

/**
 * @brief Reverses a mutable referenced string
 * @param [in, out] stringref Mutable string reference
 */
INLINE_OR_STATIC
void
stringref_reverse_string(stringref_type stringref)
{
	assert(stringref.string != NULL);
	if (stringref.string != NULL && stringref.length > 0U) {
		size_t left_index = 0U;
		size_t right_index = stringref.length - 1U;
		while (left_index < right_index) {
			const char tmp = stringref.string[left_index];
			stringref.string[left_index] = stringref.string[right_index];
			stringref.string[right_index] = tmp;
			++left_index;
			--right_index;
		}
	}
}

#ifdef __cplusplus
}
#endif

#endif
