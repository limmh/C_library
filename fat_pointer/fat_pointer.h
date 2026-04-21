#ifndef FAT_POINTER_H
#define FAT_POINTER_H

#include <assert.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief opaque fat pointer */
typedef struct fat_pointer_type_
{
	size_t do_not_access_directly[4];
} fat_pointer_type_;

/** @brief For type annotation, 'element_type' is the type of each element being referenced */
#define fat_pointer_type(element_type) fat_pointer_type_

/** @brief Error codes */
typedef enum fat_pointer_error_type
{
	fat_pointer_error_none = 0,
	fat_pointer_error_null_pointer_exception,
	fat_pointer_error_no_pointer,
	fat_pointer_error_incorrect_capacity,
	fat_pointer_error_incorrect_element_size,
	fat_pointer_error_index_out_of_range,
	fat_pointer_error_element_size_mismatch,
	fat_pointer_error_addition_overflow_detected,
	fat_pointer_error_multiplication_overflow_detected,
	fat_pointer_error_no_source_elements,
	fat_pointer_error_no_enough_capacity,
	fat_pointer_error_too_many_elements_to_remove
} fat_pointer_error_type;

/** @brief Debug info */
typedef struct fat_pointer_debug_info_type
{
	const char *file_name;
	size_t info_1;
	size_t info_2;
	int line_number;
	fat_pointer_error_type error;
} fat_pointer_debug_info_type;

/** @brief Error reporting handler type */
typedef void (*fat_pointer_error_reporting_handler_type)(fat_pointer_debug_info_type);

/**
 * @brief Sets an error reporting handler. If no error reporting handler is set, the default report handler is used.
 * @param [in] error_reporting_handler Function pointer to a custom error reporting handler
 * @return fat_pointer_error_reporting_handler_type The previous error reporting handler
 */
fat_pointer_error_reporting_handler_type
fat_pointer_set_report_handler(fat_pointer_error_reporting_handler_type error_reporting_handler);

/** @brief Exception handler type */
typedef void (*fat_pointer_exception_handler_type)(fat_pointer_error_type);

/**
 * @brief Sets an exception handler. There is no exception handler by default.
 * @param [in] exception_handler Function pointer to a custom exception handler
 * @return fat_pointer_exception_handler_type The previous exception handler
*/
fat_pointer_exception_handler_type
fat_pointer_set_exception_handler(fat_pointer_exception_handler_type exception_handler);

/**
 * @brief Creates an opaque fat pointer from a non-owning pointer and other parameters.
 * @param [in] ptr The non-owning pointer (MUST NOT be NULL)
 * @param [in] capacity The maximum number of elements allowed (MUST NOT exceed the actual number of elements)
 * @param [in] initial_size The initial length (MUST NOT exceed the capacity)
 * @param [in] element_size The size of each element (MUST NOT be zero)
 * @param [in] file_name The name or path of the source file which calls the function, For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @return fat_pointer_type_ An opaque fat pointer of type fat_pointer_type_.
 */
fat_pointer_type_
fat_pointer_create_(void *ptr, size_t capacity, size_t initial_size, size_t element_size, const char *file_name, int line_number);

/**
 * @brief Macro to create an opaque fat pointer from a non-owning pointer and other parameters
 * @param [in] type Type of each element
 * @param [in] ptr The non-owning pointer (MUST NOT be NULL)
 * @param [in] capacity The maximum number of elements allowed (MUST NOT exceed the actual number of elements)
 * @param [in] initial_length The initial length (MUST NOT exceed the capacity)
 * @return fat_pointer_type_ An opaque fat pointer of type fat_pointer_type_.
 */
#define fat_pointer_create(type, ptr, capacity, initial_length) \
	( assert(sizeof(type) == sizeof(*(ptr))), fat_pointer_create_(ptr, capacity, initial_length, sizeof(type), __FILE__, __LINE__) )

/**
 * @brief Destroys a fat pointer without modifying the data it references.
 * @param [in, out] fatptr Opaque fat pointer (MUST NOT be NULL)
 * @param [in] file_name The name or path of the source file which calls the function, For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 */
void fat_pointer_destroy_(fat_pointer_type_ *fatptr, const char *file_name, int line_number);

/**
 * @brief Macro to destroy a fat pointer without modifying the data it references
 * @param [in, out] fatptr Opaque fat pointer instance
 */
#define fat_pointer_destroy(fatptr) fat_pointer_destroy_(&(fatptr), __FILE__, __LINE__)

/**
 * @brief Zeros all the valid elements referenced by a fat pointer
 * @param [in, out] fatptr Opaque fat pointer (MUST NOT be NULL)
 * @param [in] file_name The name or path of the source file which calls the function, For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 */
void fat_pointer_zero_(fat_pointer_type_ *fatptr, const char *file_name, int line_number);

/**
 * @brief Macro to zero all the valid elements referenced by a fat pointer
 * @param [in, out] fatptr Opaque fat pointer instance
 */
#define fat_pointer_zero(fatptr) fat_pointer_zero_(&(fatptr), __FILE__, __LINE__)

/**
 * @brief Returns the maximum number of elements referenced by an opaque fat pointer
 * @param [in, out] fatptr Opaque fat pointer (MUST NOT be NULL)
 * @param [in] file_name The name or path of the source file which calls the function, For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @return size_t Maximum number of elements allowed
 */
size_t fat_pointer_capacity_(const fat_pointer_type_ *fatptr, const char *file_name, int line_number);

/**
 * @brief Macro to determine the maximum number of elements referenced by an opaque fat pointer
 * @param [in, out] fatptr Opaque fat pointer instance
 * @return size_t Maximum number of elements allowed
 */
#define fat_pointer_capacity(fatptr) fat_pointer_capacity_(&(fatptr), __FILE__, __LINE__)

/**
 * @brief Returns the number of valid elements referenced by an opaque fat pointer
 *
 * May not be the same as the maximum mumber of elements
 *
 * @param [in, out] fatptr Opaque fat pointer (MUST NOT be NULL)
 * @param [in] file_name The name or path of the source file which calls the function, For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @return size_t The number of valid elements, i.e. elements in use
 */
size_t fat_pointer_size_(const fat_pointer_type_ *fatptr, const char *file_name, int line_number);

/**
 * @brief Macro to determine the number of valid elements referenced by an opaque fat pointer
 * @param [in, out] fatptr Opaque fat pointer instance
 * @return size_t The number of valid elements, i.e. elements in use
 */
#define fat_pointer_size(fatptr) fat_pointer_size_(&(fatptr), __FILE__, __LINE__)

/** @brief The same as fat_pointer_size */
#define fat_pointer_length(fatptr) fat_pointer_size(fatptr)

/**
 * @brief Returns the size of each element referenced by an opaque fat pointer
 * @param [in, out] fatptr Opaque fat pointer (MUST NOT be NULL)
 * @param [in] file_name The name or path of the source file which calls the function, For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @return size_t The size of each element
 */
size_t fat_pointer_element_size_(const fat_pointer_type_ *fatptr, const char *file_name, int line_number);

/**
 * @brief Macro to determine the size of each element referenced by an opaque fat pointer
 * @param [in, out] fatptr Opaque fat pointer instance
 * @return size_t The size of each element
 */
#define fat_pointer_element_size(fatptr) fat_pointer_element_size_(&(fatptr), __FILE__, __LINE__)

/**
 * @brief Returns the address of an element referenced by an opaque fat pointer
 * @param [in, out] fatptr Opaque fat pointer (MUST NOT be NULL)
 * @param [in] index The index of an element (MUST NOT exceed the number of valid elements (elements in use)
 * @param [in] element_size The size of each element (MUST match the element size specified when the fat pointer was first initialized)
 * @param [in] file_name The name or path of the source file which calls the function, For debugging purpose.
 * @param [in] line_number : The line number of the source file at which the function is called. For debugging purpose.
 * @return void * A void pointer referring to an element referenced by the fat pointer
 *
 * Note: DO NOT call the function directly but use the provided function macros for element access.
 */
void *fat_pointer_element_ptr_(
	const fat_pointer_type_ *fatptr,
	size_t index,
	size_t element_size,
	const char *file_name,
	int line_number
);

/**
 * @brief Macro to access an element via a pointer
 * @param [in] type Type of each element
 * @param [in] fatptr Opaque fat pointer instance
 * @param [in] index Index of the element
 * @return type * Pointer to the element
 */
#define fat_pointer_element_ptr(type, fatptr, index) \
	( (type*) fat_pointer_element_ptr_(&(fatptr), index, sizeof(type), __FILE__, __LINE__) )


/**
 * @brief Macro to access the element as an lvalue, so that the element can be modified
 * @param [in] type Type of each element
 * @param [in] fatptr Opaque fat pointer instance
 * @param [in] index Index of the element
 * @return type lvalue of the element
 */
#define fat_pointer_element(type, fatptr, index) \
	(*fat_pointer_element_ptr(type, fatptr, index))

/**
 * @brief Adds elements to the array referenced by an opaque fat pointer
 * @param [in, out] fatptr Opaque fat pointer (MUST NOT be NULL)
 * @param [in] index The index to insert elements. (index + number of elements to be inserted) must not exceed the actual capacity.
 * @param [in] ptr_to_first_element A pointer to the first element in the source buffer to be copied
 * @param [in] number_of_elements The number of elements to be copied from the source buffer.
 * @param [in] element_size The size of each element (MUST match the element size specified when the fat pointer was first initialized)
 * @param [in] file_name The name or path of the source file which calls the function, For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @return fat_pointer_error_type Error code
 *
 * Notes:
 * - DO NOT call the function directly but use the provided function macros.
 * - If there is an error, the insertion operation WILL NOT be performed.
 */
fat_pointer_error_type
fat_pointer_add_elements_at_index_(
	fat_pointer_type_ *fatptr,
	size_t index,
	const void *ptr_to_first_element,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	int line_number
);

/**
 * @brief Macro to add elements to the array referenced by an opaque fat pointer
 * @param [in] type Type of each element
 * @param [in, out] fatptr Opaque fat pointer instance
 * @param [in] index The index to insert elements
 * @param [in] elements A pointer to the first element in the source buffer to be copied
 * @param [in] element_count The number of elements to be copied from the source buffer
 * @return fat_pointer_error_type Error code
 */
#define fat_pointer_add_elements_at_index(type, fatptr, index, elements, element_count) \
	fat_pointer_add_elements_at_index_(&(fatptr), index, elements, element_count, sizeof((elements)[0]), __FILE__, __LINE__)

/**
 * @brief Macro to add an element to the array referenced by an opaque fat pointer
 * @param [in] type Type of each element
 * @param [in, out] fatptr Opaque fat pointer instance
 * @param [in] index The index to insert elements
 * @param [in] element An element instance
 * @return fat_pointer_error_type Error code
 */
#define fat_pointer_add_element_at_index(type, fatptr, index, element) \
	fat_pointer_add_elements_at_index_(&(fatptr), index, &(element), 1U, sizeof(element), __FILE__, __LINE__)

/**
 * @brief Macro to append elements to the array referenced by an opaque fat pointer
 * @param [in] type Type of each element
 * @param [in, out] fatptr Opaque fat pointer instance
 * @param [in] elements A pointer to the first element in the source buffer to be copied
 * @param [in] element_count The number of elements to be copied from the source buffer
 * @return fat_pointer_error_type Error code
 */
#define fat_pointer_append_elements(type, fatptr, elements, element_count) \
	fat_pointer_add_elements_at_index_(&(fatptr), fat_pointer_length(fatptr), elements, element_count, sizeof((elements)[0]), __FILE__, __LINE__)

/**
 * @brief Macro to append an element to the array referenced by an opaque fat pointer
 * @param [in] type Type of each element
 * @param [in, out] fatptr Opaque fat pointer instance
 * @param [in] element An element instance
 * @return fat_pointer_error_type Error code
 */
#define fat_pointer_append_element(type, fatptr, element) \
	fat_pointer_add_elements_at_index_(&(fatptr), fat_pointer_length(fatptr), &(element), 1U, sizeof(element), __FILE__, __LINE__)

/**
 * @brief The same as fat_pointer_append_element
 */
#define fat_pointer_push_back(type, fatptr, element)  fat_pointer_append_element(type, fatptr, element)

/**
 * @brief Removes elements from the array referenced by an opaque fat pointer
 * @param [in, out] fatptr Opaque fat pointer (MUST NOT be NULL)
 * @param [in] index The index of the first element to be removed (MUST NOT exceed the number of valid elements)
 * @param [out] output_buffer A pointer to the first element of the destination buffer (Optional, can be NULL)
 * @param [in] number_of_elements The number of elements to be removed
 *             (MUST NOT exceed the number of elements between index and the final element or the maximum number of elements of the output buffer)
 * @param [in] element_size The size of each element (MUST match the element size specified when the fat pointer was first initialized)
 * @param [in] file_name The name or path of the source file which calls the function, For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @return fat_pointer_error_type Error code
 *
 * Notes:
 * - DO NOT call the function directly but use the provided function macros.
 * - If there is an error, the removal operation WILL NOT be performed.
 */
fat_pointer_error_type
fat_pointer_remove_elements_starting_from_index_(
	fat_pointer_type_ *fatptr,
	size_t index,
	void *output_buffer,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	int line_number
);

/**
 * @brief Macro to remove elements from the array referenced by an opaque fat pointer
 * @param [in] type Type of each element
 * @param [in, out] fatptr Opaque fat pointer instance
 * @param [in] index The index of the first element to be removed
 * @param [in] number_of_elements The number of elements to be removed
 * @return fat_pointer_error_type Error code
 */
#define fat_pointer_remove_elements_starting_from_index(type, fatptr, index, number_of_elements) \
	fat_pointer_remove_elements_starting_from_index_(&(fatptr), index, NULL, number_of_elements, sizeof(type), __FILE__, __LINE__)

/**
 * @brief Macro to move elements from the array referenced by an opaque fat pointer to another buffer
 * @param [in] type Type of each element
 * @param [in, out] fatptr Opaque fat pointer instance
 * @param [in] index The index of the first element to be removed
 * @param [out] buffer A pointer to the first element of the destination buffer
 * @param [in] number_of_elements The number of elements to be removed
 * @return fat_pointer_error_type Error code
 */
#define fat_pointer_move_elements_starting_from_index_to_buffer(type, fatptr, index, buffer, number_of_elements) \
	fat_pointer_remove_elements_starting_from_index_(&(fatptr), index, buffer, number_of_elements, sizeof((buffer)[0]), __FILE__, __LINE__)

/**
 * @brief Macro to remove an element from the array referenced by an opaque fat pointer
 * @param [in] type Type of each element
 * @param [in, out] fatptr Opaque fat pointer instance
 * @param [in] index The index of the first element to be removed
 * @return fat_pointer_error_type Error code
 */
#define fat_pointer_remove_element_at_index(type, fatptr, index) \
	fat_pointer_remove_elements_starting_from_index_(&(fatptr), index, NULL, 1U, sizeof(type), __FILE__, __LINE__)

/**
 * @brief Macro to move the last element from the array referenced by an opaque fat pointer to a variable
 * @param [in] type Type of each element
 * @param [in, out] fatptr Opaque fat pointer instance
 * @return fat_pointer_error_type Error code
 */
#define fat_pointer_pop_back(type, fatptr, variable) \
	fat_pointer_remove_elements_starting_from_index_(&(fatptr), fat_pointer_length(fatptr) - 1U, &(variable), 1U, sizeof(variable), __FILE__, __LINE__)

/**
 * @brief Resizes the array referenced by an opaque fat pointer
 * @param [in, out] fatptr Opaque fat pointer (MUST NOT be NULL)
 * @param [in] new_size The new number of valid elements (elements in use) (MUST NOT exceed the maximum number of elements of the output buffer)
 * @param [in] file_name The name or path of the source file which calls the function, For debugging purpose.
 * @param [in] line_number : The line number of the source file at which the function is called. For debugging purpose.
 * @return fat_pointer_error_type Error code
 *
 * Notes:
 * - DO NOT call the function directly but use the provided function macro.
 * - If there is an error, the resize operation WILL NOT be performed.
 */
fat_pointer_error_type
fat_pointer_resize_(
	fat_pointer_type_ *fatptr,
	size_t new_size,
	const char *file_name,
	int line_number
);

/**
 * @brief Macro to resize the array referenced by an opaque fat pointer
 * @param [in, out] fatptr Opaque fat pointer instance
 * @param [in] new_size New number of elements
 * @return fat_pointer_error_type Error code
 */
#define fat_pointer_resize(fatptr, new_size) \
	fat_pointer_resize_(&(fatptr), new_size, __FILE__, __LINE__)

#ifdef __cplusplus
}
#endif

#endif
