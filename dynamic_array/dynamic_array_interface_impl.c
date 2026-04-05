#include "dynamic_array_interface.h"
#include <stdio.h>
#include <stdlib.h>

void dynamic_array_default_exception_handler(dynamic_array_error_type error)
{
	exit(EXIT_FAILURE);
}

void dynamic_array_default_error_reporter(dynamic_array_debug_info_type debug_info)
{
	FILE *output = stdout;
	const char *file_name = (debug_info.file_name != NULL) ? debug_info.file_name : "Unknown file name";
	const char *library_file_name = (debug_info.library_file_name != NULL) ?
		debug_info.library_file_name : "Unknown library file name";
	const unsigned long info_1 = (unsigned long) debug_info.info_1;
	const unsigned long info_2 = (unsigned long) debug_info.info_2;

	if (debug_info.error != dynamic_array_error_none) {
		fprintf(output, "%s (line %lu): Please refer to the code here for more details.\n",
			file_name, (unsigned long) debug_info.line_number);
	}

	fprintf(output, "%s (line %lu): ", library_file_name, (unsigned long) debug_info.library_line_number);

	switch (debug_info.error) {
	case dynamic_array_error_none:
		fprintf(output, "No error.\n");
		break;
	case dynamic_array_error_null_pointer_exception:
		fprintf(output, "The pointer to the data structure is null.\n");
		break;
	case dynamic_array_error_struct_size_mismatch:
		fprintf(output, "The struct size (%lu) is not the same as the internal struct size (%lu).\n", info_1, info_2);
		break;
	case dynamic_array_error_no_buffer:
		fprintf(output, "There is no valid buffer for the internal array.\n");
		break;
	case dynamic_array_error_incorrect_capacity:
		fprintf(output, "The capacity of the array (%lu) is incorrect. Number of elements: %lu\n", info_1, info_2);
		break;
	case dynamic_array_error_incorrect_element_size:
		fprintf(output, "The element size of the array (%lu) is incorrect.\n", info_1);
		break;
	case dynamic_array_error_index_out_of_range:
		fprintf(output, "The index (%lu) is out of range (number of array elements = %lu).\n", info_1, info_2);
 		break;
	case dynamic_array_error_element_size_mismatch:
		fprintf(output, "The size of a source element (%lu) is not the same as that of an array element (%lu).\n", info_1, info_2);
		break;
	case dynamic_array_error_addition_overflow_detected:
		fprintf(output,  "Addition overflow detected: operand 1 = %lu, operand 2 = %lu\n", info_1, info_2);
		break;
	case dynamic_array_error_multiplication_overflow_detected:
		fprintf(output, "Multiplication overflow detected: operand 1 = %lu, operand 2 = %lu\n", info_1, info_2);
		break;
	case dynamic_array_error_no_interface:
		fprintf(output, "There is no dynamic array interface.\n");
		break;
	case dynamic_array_error_memory_allocation_failure:
		fprintf(output, "Memory allocation failed. Number of bytes requested: %lu\n", info_1);
		break;
	case dynamic_array_error_memory_reallocation_failure:
		fprintf(output, "Memory reallocation failed. Number of bytes requested: %lu\n", info_1);
		break;
	case dynamic_array_error_no_memory_allocation_function:
		fprintf(output, "The memory allocation function is not available.\n");
		break;
	case dynamic_array_error_no_memory_deallocation_function:
		fprintf(output, "The memory deallocation function is not available.\n");
		break;
	default:
		fprintf(output, "Unknown error (%d)\n", (int) debug_info.error);
		break;
	}
}

const dynamic_array_interface_type *dynamic_array_default_interface(void)
{
	static const dynamic_array_interface_type default_interface = {
		{&malloc, &realloc, &free},
		&dynamic_array_default_exception_handler,
		&dynamic_array_default_error_reporter
	};
	return &default_interface;
}
