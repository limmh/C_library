#ifndef DYNAMIC_ARRAY_INTERFACE_H
#define DYNAMIC_ARRAY_INTERFACE_H

#include "allocator_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Dynamic array error enum type */
typedef enum dynamic_array_error_type
{
	dynamic_array_error_none = 0,
	dynamic_array_error_null_pointer_exception,
	dynamic_array_error_struct_size_mismatch,
	dynamic_array_error_no_buffer,
	dynamic_array_error_incorrect_capacity,
	dynamic_array_error_incorrect_element_size,
	dynamic_array_error_index_out_of_range,
	dynamic_array_error_element_size_mismatch,
	dynamic_array_error_addition_overflow_detected,
	dynamic_array_error_multiplication_overflow_detected,
	dynamic_array_error_no_interface,
	dynamic_array_error_memory_allocation_failure,
	dynamic_array_error_memory_reallocation_failure,
	dynamic_array_error_no_memory_allocation_function,
	dynamic_array_error_no_memory_deallocation_function
} dynamic_array_error_type;

/** @brief Dynamic array debug info type */
typedef struct dynamic_array_debug_info_type
{
	const char *file_name; /* application source file */
	const char *library_file_name; /* library source file */
	size_t info_1;
	size_t info_2;
	int line_number; /* application source file */
	int library_line_number; /* library source file */
	dynamic_array_error_type error;
	unsigned short struct_size;
	unsigned short internal_struct_size;
} dynamic_array_debug_info_type;

/** @brief Dynamic array interface type */
typedef struct dynamic_array_interface_type
{
	allocator_type allocator;
	void (*exception_handler)(dynamic_array_error_type);
	void (*error_reporter)(dynamic_array_debug_info_type);
} dynamic_array_interface_type;

/**
 * @brief The default exception handler
 * @param [in] error Error code
 */
void dynamic_array_default_exception_handler(dynamic_array_error_type error);

/**
 * @brief The default error reporting function
 * @param debug_info Debug information
 *
 * Errors and additional debug info:
 * 1.  dynamic_array_error_none: no additional info (info_1 == 0, info_2 == 0)
 * 2.  dynamic_array_error_null_pointer_exception: no additional info
 * 3.  dynamic_array_error_struct_size_mismatch: info_1 == size of external data structure, info_2 == size of internal data structure
 * 4.  dynamic_array_error_no_buffer: no additional info
 * 5.  dynamic_array_error_incorrect_capacity: info_1 == capacity, info_2 == number of array elements
 * 6.  dynamic_array_error_incorrect_element_size: info_1 == element size
 * 7.  dynamic_array_error_index_out_of_range: info_1 == index, info_2 == number of array elements
 * 8.  dynamic_array_error_element_size_mismatch: info_1 == external element size, info_2 == internal element size
 * 9.  dynamic_array_error_addition_overflow_detected: info_1 == operand 1, info_2 == operand 2
 * 10. dynamic_array_error_multiplication_overflow_detected: info_1 == operand 1, info_2 == operand 2
 * 11. dynamic_array_error_no_interface: no additional info
 * 12. dynamic_array_error_memory_allocation_failure: info_1 == number of bytes requested, info_2 == 0
 * 13. dynamic_array_error_memory_reallocation_failure: info_1 == number of bytes requested, info_2 == 0
 * 14. dynamic_array_error_no_memory_allocation_function: no additional info
 * 15. dynamic_array_error_no_memory_deallocation_function: no additional info
 */
void dynamic_array_default_error_reporter(dynamic_array_debug_info_type debug_info);

/**
 * @brief Returns the default dynamic array interface
 * @return const dynamic_array_interface_type * A pointer to the default dynamic array interface object.
 */
const dynamic_array_interface_type *dynamic_array_default_interface(void);

#ifdef __cplusplus
}
#endif

#endif
