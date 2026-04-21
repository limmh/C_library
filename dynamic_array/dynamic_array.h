#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "dynamic_array_interface.h"
#include "static_assert.h"
#include <assert.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Generic container type for dynamic arrays */
typedef struct dynamic_array_type_
{
	size_t do_not_access_this[5];
} dynamic_array_type_;

/** @brief This macro is only for annotation. */
#define dynamic_array_type(element_type) dynamic_array_type_

/*
- Function declarations and macros
- Most functions will invoke the exception handler on error.
- If no exception handler is provided, the program will be terminated when an error is detected.
*/

/**
 * @brief Creates a dynamic array and returns a dynamic_array_type_ variable.
 * @param [in] source The source of data to be copied when the dynamic array is first created. 'source' points to the first element of the source array. [Optional, can be NULL]
 * @param [in] number_of_elements The number of elements that the dynamic array will contain when it is first created.
 *                           If source is not NULL, then number_of_elements shall not exceed the number of elements that the source array contains.
 * @param [in] element_size The number of bytes of each element in the array.
 * @param [in] interface A pointer to an interface. The interface must have a longer life time than the dynamic array. If it is a null pointer, the default interface will be used.
 * @param [in] file_name The name or path of the source file which calls the function. For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @param [in] struct_size The number of bytes of a dynamic_array_type_. For debugging purpose.
 * @return dynamic_array_type_ A new instance of dynamic array container, which shall be assigned to a variable of compatible dynamic_array_type_ to prevent a memory leak.
 *
 * Possible errors and reasons:
 * 1. dynamic_array_error_memory_allocation_failure: No memory block can be acquired.
 * 2. dynamic_array_error_multiplication_overflow_detected: (Element size times initial capacity) is greater than the maximum allowed number of bytes.
 * 3. dynamic_array_error_no_memory_allocation_function: A user allocator is provided, but the pointer to memory allocation function is NULL.
 * 4. dynamic_array_error_no_memory_deallocation_function: A user allocator is provided, but the pointer to memory deallocation function is NULL.
 *
 * Depending on the implementation, only the first error detected may be reported.
 */
dynamic_array_type_
dynamic_array_create_(
	const void *source,
	size_t number_of_elements,
	size_t element_size,
	const dynamic_array_interface_type *interface,
	const char *file_name,
	int line_number,
	size_t struct_size
);

/**
 * @brief Macro to create a dynamic array with an initial size
 * @param [in] element_type Type of each element
 * @param [in] initial_size Initial number of elements
 * @return dynamic_array_type_ A new instance of dynamic array container 
 */
#define dynamic_array_create(element_type, initial_size) \
	dynamic_array_create_(NULL, initial_size, sizeof(element_type), dynamic_array_default_interface(), __FILE__, __LINE__, sizeof(dynamic_array_type_))

/**
 * @brief Macro to create a dynamic array with an initial size and uses a custom interface
 * @param [in] element_type Type of each element
 * @param [in] initial_size Initial number of elements
 * @param [in] interface An instance of dynamic array interface (NOT a pointer)
 * @return dynamic_array_type_ A new instance of dynamic array container
 */
#define dynamic_array_create_with_interface(element_type, initial_size, interface) \
	dynamic_array_create_(NULL, initial_size, sizeof(element_type), &(interface), __FILE__, __LINE__, sizeof(dynamic_array_type_))

/**
 * @brief Macro to create a dynamic array from a source array
 * @param [in] element_type Type of each element
 * @param [in] source Source array
 * @param [in] source_size Size of source array
 * @return dynamic_array_type_ A new instance of dynamic array container 
 */
#define dynamic_array_create_from_source(element_type, source, source_size) \
	(assert(sizeof(element_type) == sizeof((source)[0])), \
	dynamic_array_create_(source, source_size, sizeof(element_type), dynamic_array_default_interface(), __FILE__, __LINE__, sizeof(dynamic_array_type_)))

/**
 * @brief Macro to create a dynamic array which uses a custom interface from a source array
 * @param [in] element_type Type of each element
 * @param [in] source Source array
 * @param [in] source_size Size of source array
 * @param [in] interface An instance of dynamic array interface (NOT a pointer)
 * @return dynamic_array_type_ A new instance of dynamic array container 
 */
#define dynamic_array_create_from_source_with_interface(element_type, source, source_size, interface) \
	(assert(sizeof(element_type) == sizeof((source)[0])), \
	dynamic_array_create_(source, source_size, sizeof(element_type), &(interface), __FILE__, __LINE__, sizeof(dynamic_array_type_)))

/**
 * @brief Macro to create an empty dynamic array
 * @param [in] element_type Type of each element
 * @return dynamic_array_type_ A new instance of dynamic array container 
 */
#define dynamic_array_create_empty(element_type) \
	dynamic_array_create_(NULL, 0U, sizeof(element_type), dynamic_array_default_interface(), __FILE__, __LINE__, sizeof(dynamic_array_type_))

/**
 * @brief Macro to create an empty dynamic array which uses a custom interface
 * @param [in] element_type Type of each element
 * @param [in] interface An instance of dynamic array interface (NOT a pointer)
 * @return dynamic_array_type_ A new instance of dynamic array container 
 */
#define dynamic_array_create_empty_with_interface(element_type, interface) \
	dynamic_array_create_(NULL, 0U, sizeof(element_type), &(interface), __FILE__, __LINE__, sizeof(dynamic_array_type_))

/**
 * @brief Performs cleanup and releases the memory occupied by the dynamic array.
 *
 * @param [in, out] dynamic_array A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
 * @param [in] file_name The name or path of the source file which calls the function. For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @param [in] struct_size The number of bytes of a dynamic_array_type_. For debugging purpose.
 */
void dynamic_array_delete_(
	dynamic_array_type_ *dynamic_array,
	const char *file_name,
	int line_number,
	size_t struct_size
);

/**
 * @brief Macro to delete the memory of dynamic array container
 * @param [in, out] array An instance of dynamic array container (NOT a pointer)
 */
#define dynamic_array_delete(array) \
	dynamic_array_delete_(&(array), __FILE__, __LINE__, sizeof(array))

/**
 * @brief Retrieves the interface
 *
 * @param [in] dynamic_array A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
 * @param [in] file_name The name of path of the source file which calls the function. For debugging purpose.
 * @param [in] line_number The line of the source file at which the function is called. For debugging purpose.
 * @param [in] struct_size The number of bytes of dynamic_array_type_. For debugging purpose.
 * @return const dynamic_array_interface_type * A pointer to the interface used by the dynamic array. DO NOT modify any member of the interface.
 */
const dynamic_array_interface_type*
dynamic_array_get_interface_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	int line_number,
	size_t struct_size
);

/**
 * @brief Macro to retrieve the interface used by a dynamic array container
 * @param [in] array An instance of dynamic array container (NOT a pointer)
 * @return const dynamic_array_interface_type * A pointer to the interface used by the dynamic array container
 */
#define dynamic_array_get_interface(array) \
	dynamic_array_get_interface_(&(array), __FILE__, __LINE__, sizeof(array))

/**
 * @brief Checks the dynamic array for any error. The returned debug information is for the first error detected.
 * @param [in] dynamic_array A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
 * @param [in] file_name The name of path of the source file which calls the function. For debugging purpose.
 * @param [in] line_number The line of the source file at which the function is called. For debugging purpose.
 * @param [in] struct_size  : The number of bytes of dynamic_array_type_. For debugging purpose.
 * @return dynamic_array_debug_info_type The debug information for the first error detected.
 */
dynamic_array_debug_info_type
dynamic_array_check_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	int line_number,
	size_t struct_size
);

/**
 * @brief Macro to check a dynamic array container for any error
 * @param [in] array An instance of dynamic array container (NOT a pointer)
 * @return dynamic_array_debug_info_type The debug information for the first error found
 */
#define dynamic_array_check(array) \
	dynamic_array_check_(&(array), __FILE__, __LINE__, sizeof(array))

/**
 * @brief Returns the number of elements that can be stored without reallocation
 * @param [in, out] dynamic_array A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
 * @param [in] file_name The name of path of the source file which calls the function. For debugging purpose.
 * @param [in] line_number The line of the source file at which the function is called. For debugging purpose.
 * @param [in] struct_size The number of bytes of dynamic_array_type_. For debugging purpose.
 * @return [in] size_t The number of elements that can be stored without reallocation
 */
size_t dynamic_array_capacity_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	int line_number,
	size_t struct_size
);

/**
 * @brief Macro to find out the capacity of a dynamic array container
 * @param [in] array An instance of dynamic array container (NOT a pointer)
 * @return size_t Number of elements that can be stored without reallocation
 */
#define dynamic_array_capacity(array) \
	dynamic_array_capacity_(&(array), __FILE__, __LINE__, sizeof(array))

/**
 * @brief Returns the actual number of elements of the dynamic array
 * @param [in] dynamic_array A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
 * @param [in] file_name The name of path of the source file which calls the function. For debugging purpose.
 * @param [in] line_number The line of the source file at which the function is called. For debugging purpose.
 * @param [in] struct_size The number of bytes of dynamic_array_type_. For debugging purpose.
 * @return size_t The number of elements of the dynamic array
 */
size_t dynamic_array_size_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	int line_number,
	size_t struct_size
);

/**
 * @brief Macro to find out the number of elements of a dynamic array
 * @param [in] array An instance of dynamic array container (NOT a pointer)
 * @return size_t Number of elements
 */
#define dynamic_array_size(array) dynamic_array_size_(&(array), __FILE__, __LINE__, sizeof(array))

/**
 * @brief The same macro as dynamic_array_size
 */
#define dynamic_array_length(array) dynamic_array_size(array)

/**
 * @brief Macro to find out whether a dynamic array is empty
 * @param [in] array An instance of dynamic array container (NOT a pointer)
 * @return bool true if the array is empty, otherwise false
 */
#define dynamic_array_is_empty(array) (dynamic_array_size(array) == 0)

/**
 * @brief Returns a pointer to an element of the array based on the given index.
 *
 * The pointer is a void pointer and must be cast to the proper type of each element.
 *
 * NOTE: Do not call this function directly. Use the provided macro dynamic_array_element to access an array element.
 *
 * @param [in] dynamic_array A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
 * @param [in] index An array index which should be less than the number of array elements.
 * @param [in] element_size The number of bytes of each element. The value will be compared with the element size stored internally.
 * @param [in] file_name The name of path of the source file which calls the function. For debugging purpose.
 * @param [in] line_number The line of the source file at which the function is called. For debugging purpose.
 * @param [in] struct_size The number of bytes of dynamic_array_type_. For debugging purpose.
 * @return void * A pointer to an element in the internal buffer.
 */
void *dynamic_array_element_ptr_(
	const dynamic_array_type_ *dynamic_array,
	size_t index,
	size_t element_size,
	const char *file_name,
	int line_number,
	size_t struct_size
);

/**
 * @brief Macro that returns an lvalue corresponding to the element at the index specified
 * @param [in] element_type Type of each element
 * @param [in] array An instance of dynamic array container (NOT a pointer)
 * @param [in] index Index of element. Must be smaller than the number of elements
 * @return element_type An lvalue of the element at index
 */
#define dynamic_array_element(element_type, array, index) \
		(*((element_type*) dynamic_array_element_ptr_(&(array), index, sizeof(element_type), __FILE__, __LINE__, sizeof(array))))

/**
 * @brief Adds or inserts elements at an index
 *
 * Valid index values: from 0 to one past the last index, i.e. [0, array_size]
 *
 *The function will perform reallocation if there is no enough capacity.
 *
 * @param [in, out] dynamic_array A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
 * @param [in] index The index which corresponds to the position where the first new element is to be added.
 * @param [in] ptr_to_first_element A pointer to the first element to be added.
 * @param [in] number_of_elements The number of elements to be added.
 * @param [in] element_size The number of bytes of each element. The value will be compared with the element size stored internally.
 * @param [in] file_name The name or path of the source file which calls the function. For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @param [in] struct_size The number of bytes of a dynamic_array_type_. For debugging purpose.
 *
 * Possible errors and reasons:
 * 1. dynamic_array_error_memory_reallocation_failure: No enough memory for reallocation.
 * 2. Errors in the dynamic array data structure.
 */
void dynamic_array_add_elements_at_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	const void *ptr_to_first_element,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	int line_number,
	size_t struct_size
);

/**
 * @brief Macro to add an element at an index of a dynamic array
 * @param [in] element_type Type of each element
 * @param [in, out] array An instance of dynamic array container (NOT a pointer)
 * @param [in] index Index to insert the new element
 * @param [in] element New element
 */
#define dynamic_array_add_element_at_index(element_type, array, index, element) \
	do { \
		element_type tmp = element; \
		dynamic_array_add_elements_at_index_(&(array), index, &tmp, 1U, sizeof(tmp), \
			 __FILE__, __LINE__, sizeof(array)); \
	} while (0)

/**
 * @brief Macro to add elements at an index of a dynamic array
 * @param [in] element_type Type of each element
 * @param [in, out] array An instance of dynamic array container (NOT a pointer)
 * @param [in] index Index to insert the new elements
 * @param [in] elements New elements (MUST be from an array, a pointer to the first element)
 * @param [in] element_count Number of new elements
 */
#define dynamic_array_add_elements_at_index(element_type, array, index, elements, element_count) \
	do { \
		STATIC_ASSERT(sizeof(element_type) == sizeof((elements)[0]), "Mismatch between type size and element size."); \
		dynamic_array_add_elements_at_index_(&(array), index, elements, element_count, sizeof((elements)[0]), \
			__FILE__, __LINE__, sizeof(array)); \
	} while (0)

/**
 * @brief Macro to add an element at the end of a dynamic array
 * @param [in] element_type Type of each element
 * @param [in] array An instance of dynamic array container (NOT a pointer)
 * @param [in] element New element
 */
#define dynamic_array_append_element(element_type, array, element) \
	do { \
		element_type tmp = element; \
		dynamic_array_add_elements_at_index_(&(array), dynamic_array_size(array), &tmp, 1U, sizeof(tmp), \
			__FILE__, __LINE__, sizeof(array)); \
	} while (0)

/**
 * @brief The same as dynamic_array_append_element
 */
#define dynamic_array_push_back(element_type, array, element) dynamic_array_append_element(element_type, array, element)

/**
 * @brief Macro to add elements at the end of a dynamic array
 * @param [in] element_type Type of each element
 * @param [in, out] array An instance of dynamic array container (NOT a pointer)
 * @param [in] elements New elements (MUST be from an array, a pointer to the first element)
 * @param [in] element_count Number of new elements
 */
#define dynamic_array_append_elements(element_type, array, elements, element_count) \
	do { \
		STATIC_ASSERT(sizeof(element_type) == sizeof((elements)[0]), "Mismatch between type size and element size."); \
		dynamic_array_add_elements_at_index_(&(array), dynamic_array_size(array), elements, element_count, sizeof((elements)[0]), \
			__FILE__, __LINE__, sizeof(array)); \
	} while (0)

/**
 * @brief Macro to copy the elements of a source array to a dynamic array
 * @param [in] element_type Type of each element
 * @param [in, out] array An instance of dynamic array container (NOT a pointer)
 * @param [in] elements New elements (MUST be from an array, a pointer to the first element)
 * @param [in] element_count Number of new elements
 */
#define dynamic_array_assign(element_type, array, elements, element_count) \
	do { \
		STATIC_ASSERT(sizeof(element_type) == sizeof((elements)[0]), "Mismatch between type size and element size."); \
		dynamic_array_clear(array); \
		dynamic_array_add_elements_at_index_(&(array), 0U, elements, element_count, sizeof((elements)[0]), \
			__FILE__, __LINE__, sizeof(array)); \
	} while (0)

/**
 * @brief Removes elements start from the given index
 *
 * The specified number of elements to be removed can larger than the actual number of  elements that are available.
 *
 * Only the available elements will be removed. The function will not perform any reallocation.
 *
 * @param [in, out] dynamic_array A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
 * @param [in] index The index which corresponds to the position of the first element to be removed.
 * @param [out] output_buffer A pointer to the first element of an external buffer to store the removed elements.
 *                           Can be NULL if the removed elements need not be stored in any external buffer.
 * @param [in] number_of_elements The number of elements to be removed.
 * @param [in] element_size The number of bytes of each element. The value will be compared with the element size stored internally.
 * @param [in] file_name The name or path of the source file which calls the function. For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @param [in] struct_size The number of bytes of a dynamic_array_type_. For debugging purpose.
 */
void dynamic_array_remove_elements_starting_from_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	void *output_buffer,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	int line_number,
	size_t struct_size
);

/**
 * @brief Macro to remove the element at an index of a dynamic array
 * @param [in] element_type Type of each element
 * @param [in, out] array An instance of dynamic array container (NOT a pointer)
 * @param [in] index
 */
#define dynamic_array_remove_element_at_index(element_type, array, index) \
	dynamic_array_remove_elements_starting_from_index_(&(array), index, NULL, 1U, sizeof(element_type), \
		__FILE__, __LINE__, sizeof(array))

/**
 * @brief Macro to remove multiple elements starting from an index of a dynamic array
 * @param [in] element_type Type of each element
 * @param [in, out] array An instance of dynamic array container (NOT a pointer)
 * @param [in] index
 * @param [in] number_of_elements Number of elements to be removed
 */
#define dynamic_array_remove_elements_starting_from_index(element_type, array, index, number_of_elements) \
	dynamic_array_remove_elements_starting_from_index_(&(array), index, NULL, number_of_elements, sizeof(element_type), \
		__FILE__, __LINE__, sizeof(array))

/**
 * @brief Macro to move elements starting from an index to another array
 * @param [in] element_type Type of each element
 * @param [in, out] array An instance of dynamic array container (NOT a pointer)
 * @param [in] index Index of the first element to be removed
 * @param [in] number_of_elements Number of elements to be removed
 */
#define dynamic_array_move_elements_starting_from_index_to_buffer(element_type, array, index, buffer, number_of_elements) \
	do { \
		STATIC_ASSERT(sizeof(element_type) == sizeof((buffer)[0]), "Mismatch between type size and buffer element size."); \
		assert(buffer != NULL); \
		dynamic_array_remove_elements_starting_from_index_(&(array), index, buffer, number_of_elements, sizeof((buffer)[0]), \
			__FILE__, __LINE__, sizeof(array)); \
	} while (0)

/**
 * @brief Macro to remove the last element and copy its value to a variable of the same type
 * @param [in] element_type Type of each element
 * @param [in, out] array An instance of dynamic array container (NOT a pointer)
 * @param [out] variable A variable to store the value of the element removed. Must be an lvalue.
 */
#define dynamic_array_pop_back(element_type, array, variable) \
	do { \
		STATIC_ASSERT(sizeof(element_type) == sizeof(variable), "Mismatch between type size and variable size."); \
		size_t last_element_index = 0U, array_length = 0U; \
		array_length = dynamic_array_size(array); \
		assert(array_length >= 1U); \
		last_element_index = (array_length >= 1U) ? (array_length - 1U) : 0U; \
		dynamic_array_remove_elements_starting_from_index_(&(array), last_element_index, &(variable), 1U, sizeof(variable), \
			__FILE__, __LINE__, sizeof(array)); \
	} while (0)

/**
 * @brief Changes the size of the array.
 *
 * If the new size is larger than the old size, reallocation may be performed and all new elements are zero initialized.
 *
 * If the new size is smaller than the old size, there will be no reallocation. Old elements which are no longer valid will be zeroed.
 *
 * @param [in, out] dynamic_array A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
 * @param [in] new_size The new number of array elements.
 * @param [in] file_name The name or path of the source file which calls the function. For debugging purpose.
 * @param [in] line_number The line number of the source file at which the function is called. For debugging purpose.
 * @param [in] struct_size The number of bytes of a dynamic_array_type_. For debugging purpose.
 */
void dynamic_array_resize_(
	dynamic_array_type_ *dynamic_array,
	size_t new_size,
	const char *file_name,
	int line_number,
	size_t struct_size
);

/**
 * @brief Macro to resize a dynamic array
 * @param [in, out] array An instance of dynamic array container
 * @param [in] new_size New number of elements
 */
#define dynamic_array_resize(array, new_size) \
	dynamic_array_resize_(&(array), new_size, __FILE__, __LINE__, sizeof(array))

/**
 * @brief Macro to clear all elements of a dynamic array
 * @param [in, out] array An instance of dynamic array container (NOT a pointer)
 */
#define dynamic_array_clear(array) dynamic_array_resize(array, 0U);

#ifdef __cplusplus
}
#endif

#endif
