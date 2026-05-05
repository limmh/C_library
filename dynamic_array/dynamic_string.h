#ifndef DYNAMIC_STRING_H
#define DYNAMIC_STRING_H

#include "dynamic_array_interface.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Opaque type for dynamic strings */
typedef struct dynamic_string_type
{
	size_t do_not_access_this[5];
} dynamic_string_type;

/**
 * @brief Creates a dynamic string
 * @param [in] string Source string
 * @param [in] byte_length Length of source string in number of bytes
 * @param [in] interface Dynamic array interface
 * @return dynamic_string_type A new instance of dynamic string
 */
dynamic_string_type
dynamic_string_create_(
	const char *string,
	size_t byte_length,
	const dynamic_array_interface_type *interface
);

/**
 * @brief Creates a dynamic string from a source string using the default dynamic array interface
 * @param [in] string Source string
 * @param [in] length Length of source string in number of bytes
 * @return dynamic_string_type A new instance of dynamic string
 */
#define dynamic_string_create(string, length) dynamic_string_create_(string, length, dynamic_array_default_interface())

/**
 * @brief Creates a dynamic string from a source string using a custom interface
 * @param [in] string Source string
 * @param [in] length Length of source string in number of bytes
 * @param [in] interface Dynamic array interface (instance, NOT pointer)
 * @return dynamic_string_type A new instance of dynamic string
 */
#define dynamic_string_create_with_interface(string, length, interface) \
	dynamic_string_create_(string, length, &(interface))

/**
 * @brief Destroys or deletes a dynamic string
 * @param [in, out] pdynstring Dynamic string
 */
void dynamic_string_delete_(dynamic_string_type *pdynstring);

/**
 * @brief Destroys or deletes a dynamic string
 * @param [in, out] dynstring Dynamic string instance (NOT pointer)
 */
#define dynamic_string_delete(dynstring) dynamic_string_delete_(&(dynstring))

/** @brief The same as dynamic_string_delete */
#define dynamic_string_destroy(dynstring) dynamic_string_delete(dynstring)

/**
 * @brief Returns the length of a dynamic string in number of bytes
 * @param [in] pdynstring Dynamic string
 * @return size_t Length in number of bytes
 */
size_t dynamic_string_byte_length_(const dynamic_string_type *pdynstring);

/**
* @brief Returns the length of a dynamic string in number of bytes
* @param [in] dynstring Dynamic string instance (NOT pointer)
* @return size_t Length in number of bytes
*/
#define dynamic_string_byte_length(dynstring) dynamic_string_byte_length_(&(dynstring))

/**
 * @brief Checks whether a dynamic string is empty
 * @param [in] dynstring Dynamic string instance (NOT pointer)
 * @return bool
 */
#define dynamic_string_is_empty(dynstring) (dynamic_string_byte_length(dynstring) == 0)

/**
 * @brief Obtains a pointer to a character of a dynamic string
 * @param [in] pdynstring Dynamic string
 * @param [in] char_index
 * @return char * A pointer to the mutable character 
 * The exception handler will be invoked if char_index is out of bounds.
 */
char *dynamic_string_ptr_(
	dynamic_string_type *pdynstring,
	size_t char_index
);

/**
 * @brief Obtains an lvalue of a character of a dynamic string
 * @param [in] dynstring Dynamic string instance (NOT pointer)
 * @param [in] index Index of the character
 * @return char An lvalue of the mutable character
 * The exception handler will be invoked if char_index is out of bounds.
 */
#define dynamic_string_char(dynstring, index) (*dynamic_string_ptr_(&(dynstring), index))

/**
* @brief Obtains a pointer to a const character of a dynamic string
* @param [in] pdynstring Dynamic string
* @param [in] char_index Index of the character
* @return const char * A pointer to the immutable character
* The exception handler will be invoked if char_index is out of bounds.
*/
const char *dynamic_string_const_ptr_(
	const dynamic_string_type *pdynstring,
	size_t char_index
);

/**
 * @brief Obtains an lvalue to a const character of a dynamic string
 * @param [in] dynstring Dynamic string instance (NOT pointer)
 * @param [in] index Index of the character
 * @return const char An lvalue of the immutable character
 * The exception handler will be invoked if char_index is out of bounds.
 */
#define dynamic_string_const_char(dynstring, index) (*dynamic_string_const_ptr_(&(dynstring), index))

/**
 * @brief Obtains the underlying C-style string
 * @param [in] pdynstring Dynamic string
 * @return const char * A pointer to the first character
 */
const char *dynamic_string_cstring_(
	const dynamic_string_type *pdynstring
);

/**
 * @brief Obtains the underlying C-style string
 * @param [in] dynstring Dynamic string instance (NOT pointer)
 * @return const char * A pointer to the first character
 */
#define dynamic_string_cstring(dynstring) dynamic_string_cstring_(&(dynstring))

/**
 * @brief Assigns a source string to a target dynamic string
 * @param [in, out] pdynstring Dynamic string
 * @param [in] source_string Source string
 * @param [in] byte_length Length of source string in number of bytes
 */
void dynamic_string_assign_(
	dynamic_string_type *pdynstring,
	const char *source_string,
	size_t byte_length
);

/**
 * @brief Assigns a source string to a target dynamic string
 * @param [in, out] dynstring Dynamic string instance (NOT pointer)
 * @param [in] string Source string
 * @param [in] length Length of source string in number of bytes
 */
#define dynamic_string_assign(dynstring, string, length) dynamic_string_assign_(&(dynstring), string, length) 

/**
 * @brief Inserts a source string to a target dynamic string at the specified index
 * @param [in, out] pdynstring Dynamic string
 * @param [in] index Index to insert the source string
 * @param [in] source_string Source string
 * @param [in] byte_length Length of source string in number of bytes
 * The exception handler will be invoked if the index is out of bounds.
 */
void dynamic_string_insert_(
	dynamic_string_type *pdynstring,
	size_t index,
	const char *source_string,
	size_t byte_length
);

/**
 * @brief Inserts a source string to a target dynamic string at the specified index
 * @param [in, out] dynstring Dynamic string instance (NOT pointer)
 * @param [in] index Index to insert the source string
 * @param [in] string Source string
 * @param [in] length Length of source string in number of bytes
 * The exception handler will be invoked if the index is out of bounds.
 */
#define dynamic_string_insert(dynstring, index, string, length) dynamic_string_insert_(&(dynstring), index, string, length)

/**
 * @brief Appends a source string to a target dynamic string
 * @param [in, out] pdynstring Dynamic string
 * @param [in] source_string Source string
 * @param [in] byte_length Length of source string in number of bytes
 */
void dynamic_string_append_(
	dynamic_string_type *pdynstring,
	const char *source_string,
	size_t byte_length
);

/**
 * @brief Appends a source string to a target dynamic string
 * @param [in, out] dynstring Dynamic string instance (NOT pointer)
 * @param [in] string Source string
 * @param [in] length Length of source string in number of bytes
 */
#define dynamic_string_append(dynstring, string, length) dynamic_string_append_(&(dynstring), string, length)

/**
 * @brief Removes a substring from a target dynamic string
 * @param [in, out] pdynstring Dynamic string
 * @param [in] index Index of the first character to be removed
 * @param [in] byte_length Number of bytes to be removed
 */
void dynamic_string_remove_substring_(
	dynamic_string_type *pdynstring,
	size_t index,
	size_t byte_length
);

/**
 * @brief Removes a substring from a target dynamic string
 * @param [in, out] dynstring Dynamic string instance (NOT pointer)
 * @param [in] index Index of the first character to be removed
 * @param [in] length Number of bytes to be removed
 */
#define dynamic_string_remove_substring(dynstring, index, length) dynamic_string_remove_substring_(&(dynstring), index, length)

/**
 * @brief Clears a target dynamic string
 * @param [in, out] pdynstring Dynamic string
 */
void dynamic_string_clear_(dynamic_string_type *pdynstring);

/**
 * @brief Clears a target dynamic string
 * @param [in, out] dynstring Dynamic string instance (NOT pointer)
 */
#define dynamic_string_clear(dynstring) dynamic_string_clear_(&(dynstring))

#ifdef __cplusplus
}
#endif

#endif
