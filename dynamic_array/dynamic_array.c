#include "dynamic_array.h"
#include "Boolean_type.h"
#include "inline_or_static.h"
#include "macro_alignof.h"
#include "safer_fixed_width_integers.h"
#include <iso646.h>
#include <string.h>

/* Notes:
- All runtime assertions (assert) can be disabled by defining NDEBUG when compiling the source file, e.g. gcc -DNDEBUG -c dynamic_array.c
- Code for runtime checks can be disabled by defining DYNAMIC_ARRAY_NO_RUNTIME_CHECKS when compiling the source file, e.g. gcc -DDYNAMIC_ARRAY_NO_RUNTIME_CHECKS -c dynamic_array.c
- Avoid changing size variables from size_t to a signed integer type
*/

#define UNUSED_PARAMETER(param) (void) param

typedef struct dynamic_array_internal_type
{
	size_t capacity;
	size_t number_of_elements;
	size_t element_size; /* number of bytes of each element */
	void *ptr; /* points to the first element */
	const dynamic_array_interface_type *interface; /* must have a longer lifetime than the dynamic array */
} dynamic_array_internal_type;

STATIC_ASSERT(sizeof(size_t) == sizeof(void*), "size_t and pointer type must have the same size.");
STATIC_ASSERT(sizeof(dynamic_array_type_) == sizeof(dynamic_array_internal_type), "The public data type and the internal data type must have the same size.");
STATIC_ASSERT(ALIGNOF(dynamic_array_type_) == ALIGNOF(dynamic_array_internal_type), "The public data type and the internal data type must have the same memory alignment.");

INLINE_OR_STATIC
void dynamic_array_report_error(void (*error_reporter)(dynamic_array_debug_info_type), dynamic_array_debug_info_type debug_info)
{
	if (error_reporter != NULL) {
		error_reporter(debug_info);
	}
}

INLINE_OR_STATIC
void dynamic_array_handle_exception(void (*exception_handler)(dynamic_array_error_type), dynamic_array_error_type error)
{
	if (exception_handler != NULL) {
		exception_handler(error);
	}
}

INLINE_OR_STATIC
Boolean_type dynamic_array_addition_overflow_detected(size_t a, size_t b)
{
	const size_result_type result = safer_size_add(a, b);
	return (result.error != integer_operation_error_none);
}

INLINE_OR_STATIC
Boolean_type dynamic_array_multiplication_overflow_detected(size_t a, size_t b)
{
	const size_result_type result = safer_size_multiply(a, b);
	return (result.error != integer_operation_error_none);
}

static void dynamic_array_check_error_internal(
	const dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type *pdebug_info
){
	assert(pdebug_info != NULL);
	if (dynamic_array != NULL) {
		const dynamic_array_internal_type *array = (const dynamic_array_internal_type*) dynamic_array;
		if (array->ptr == NULL) {
			pdebug_info->error = dynamic_array_error_no_buffer;
			pdebug_info->info_1 = 0U;
			pdebug_info->info_2 = 0U;
		} else if (pdebug_info->struct_size != sizeof(dynamic_array_internal_type)) {
			pdebug_info->error = dynamic_array_error_struct_size_mismatch;
			pdebug_info->info_1 = pdebug_info->struct_size;
			pdebug_info->info_2 = pdebug_info->internal_struct_size;
		} else if (array->capacity < array->number_of_elements) {
			pdebug_info->error = dynamic_array_error_incorrect_capacity;
			pdebug_info->info_1 = array->capacity;
			pdebug_info->info_2 = array->number_of_elements;
		} else if (array->element_size < 1) {
			pdebug_info->error = dynamic_array_error_incorrect_element_size;
			pdebug_info->info_1 = array->element_size;
			pdebug_info->info_2 = 0U;
		} else if (array->interface == NULL) {
			pdebug_info->error = dynamic_array_error_no_interface;
			pdebug_info->info_1 = 0U;
			pdebug_info->info_2 = 0U;
		} else if (array->interface->allocator.allocate == NULL) {
			pdebug_info->error = dynamic_array_error_no_memory_allocation_function;
			pdebug_info->info_1 = 0U;
			pdebug_info->info_2 = 0U;
		} else if (array->interface->allocator.deallocate == NULL) {
			pdebug_info->error = dynamic_array_error_no_memory_deallocation_function;
			pdebug_info->info_1 = 0U;
			pdebug_info->info_2 = 0U;
		} else {
			pdebug_info->error = dynamic_array_error_none;
			pdebug_info->info_1 = 0U;
			pdebug_info->info_2 = 0U;
		}
	} else {
		pdebug_info->error = dynamic_array_error_null_pointer_exception;
		pdebug_info->info_1 = 0U;
		pdebug_info->info_2 = 0U;
	}
}

static void dynamic_array_check_and_report_error(
	const dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type *pdebug_info
){
	const dynamic_array_internal_type *array = (const dynamic_array_internal_type*) dynamic_array;
	dynamic_array_check_error_internal(dynamic_array, pdebug_info);
	if (pdebug_info->error != dynamic_array_error_none) {
		if (array != NULL and array->interface != NULL) {
			dynamic_array_report_error(array->interface->error_reporter, *pdebug_info);
		}
	}
}

dynamic_array_debug_info_type
dynamic_array_check_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	int line_number,
	size_t struct_size
){
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = __LINE__;
	debug_info.struct_size = (unsigned short) struct_size;
	debug_info.internal_struct_size = (unsigned short) sizeof(dynamic_array_internal_type);
	dynamic_array_check_error_internal(dynamic_array, &debug_info);
	return debug_info;
}

dynamic_array_type_
dynamic_array_create_(
	const void *source,
	size_t number_of_elements,
	size_t element_size,
	const dynamic_array_interface_type *interface,
	const char *file_name,
	int line_number,
	size_t struct_size
){
	size_t initial_capacity = 1U;
	size_t initial_size = number_of_elements;
	size_t number_of_bytes = 0U;
	void *ptr = NULL;
	dynamic_array_internal_type array = {0U};
	dynamic_array_type_ dyn_array = {0U};
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	Boolean_type multiplication_overflow_detected = Boolean_false;
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.struct_size = (unsigned short) struct_size;
	debug_info.internal_struct_size = (unsigned short) sizeof(dynamic_array_internal_type);
#else
	UNUSED_PARAMETER(file_name);
	UNUSED_PARAMETER(line_number);
	UNUSED_PARAMETER(struct_size);
#endif

	if (interface != NULL) {
		assert(interface->allocator.allocate != NULL);
		assert(interface->allocator.deallocate != NULL);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		if (interface->allocator.allocate == NULL) {
			debug_info.error = dynamic_array_error_no_memory_allocation_function;
			debug_info.library_line_number = __LINE__;
			dynamic_array_report_error(interface->error_reporter, debug_info);
			dynamic_array_handle_exception(interface->exception_handler, debug_info.error);
			return dyn_array;
		}
		if (interface->allocator.deallocate == NULL) {
			debug_info.error = dynamic_array_error_no_memory_deallocation_function;
			debug_info.library_line_number = __LINE__;
			dynamic_array_report_error(interface->error_reporter, debug_info);
			dynamic_array_handle_exception(interface->exception_handler, debug_info.error);
			return dyn_array;
		}
#endif
	} else {
		interface = dynamic_array_default_interface();
	}

	assert(interface != NULL);
	assert(element_size > 0);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size < 1) {
		debug_info.error = dynamic_array_error_incorrect_element_size;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = element_size;
		dynamic_array_report_error(interface->error_reporter, debug_info);
		dynamic_array_handle_exception(interface->exception_handler, debug_info.error);
		return dyn_array;
	}
#endif

	if (initial_size == SIZE_MAX) {
		initial_capacity = initial_size;
	}

	while (initial_capacity < initial_size) {
		initial_capacity += initial_capacity;
	}

#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	multiplication_overflow_detected = dynamic_array_multiplication_overflow_detected(initial_capacity, element_size);
	if (multiplication_overflow_detected) {
		debug_info.error = dynamic_array_error_multiplication_overflow_detected;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = initial_capacity;
		debug_info.info_2 = element_size;
		dynamic_array_report_error(interface->error_reporter, debug_info);
		dynamic_array_handle_exception(interface->exception_handler, debug_info.error);
		return dyn_array;
	}
#endif

	number_of_bytes = initial_capacity * element_size;
	ptr = allocator_allocate(interface->allocator, number_of_bytes);
	if (ptr != NULL) {
		if (source != NULL) {
			const size_t number_of_bytes_to_copy = initial_size * element_size;
			const size_t number_of_bytes_to_zero = number_of_bytes - number_of_bytes_to_copy;
			unsigned char *dest = (unsigned char*) ptr;
			memcpy(dest, source, number_of_bytes_to_copy);
			if (number_of_bytes_to_zero > 0) {
				memset(&dest[number_of_bytes_to_copy], 0, number_of_bytes_to_zero);
			}
		} else {
			memset(ptr, 0, number_of_bytes);
		}
	} else {
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		debug_info.error = dynamic_array_error_memory_allocation_failure;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = number_of_bytes;
		dynamic_array_report_error(interface->error_reporter, debug_info);
		dynamic_array_handle_exception(interface->exception_handler, debug_info.error);
#endif
		initial_capacity = initial_size = 0U;
	}

	array.capacity = initial_capacity;
	array.number_of_elements = initial_size;
	array.element_size = element_size;
	array.ptr = ptr;
	array.interface = interface;
	memcpy(&dyn_array, &array, sizeof(array));
	return dyn_array;
}

void dynamic_array_delete_(
	dynamic_array_type_ *dynamic_array,
	const char *file_name,
	int line_number,
	size_t struct_size
){
	dynamic_array_internal_type *array = (dynamic_array_internal_type*) dynamic_array;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = __LINE__;
	debug_info.struct_size = (unsigned short) struct_size;
	debug_info.internal_struct_size = (unsigned short) sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none and debug_info.error != dynamic_array_error_no_buffer) {
		if (array != NULL and array->interface != NULL) {
			dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
			return;
		}
	}
#else
	UNUSED_PARAMETER(file_name);
	UNUSED_PARAMETER(line_number);
	UNUSED_PARAMETER(struct_size);
#endif
	assert(array != NULL);
	assert(array->interface != NULL);
	if (array != NULL) {
		if (array->interface != NULL) {
			allocator_deallocate(array->interface->allocator, array->ptr);
		}
		array->capacity = 0U;
		array->number_of_elements = 0U;
		array->element_size = 0U;
		array->ptr = NULL;
		array->interface = NULL;
	}
}

const dynamic_array_interface_type*
dynamic_array_get_interface_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	int line_number,
	size_t struct_size
){
	const dynamic_array_internal_type *array = (const dynamic_array_internal_type*) dynamic_array;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = __LINE__;
	debug_info.struct_size = (unsigned short) struct_size;
	debug_info.internal_struct_size = (unsigned short) sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		if (array != NULL and array->interface != NULL) {
			dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		}
		return NULL;
	}
#else
	UNUSED_PARAMETER(file_name);
	UNUSED_PARAMETER(line_number);
	UNUSED_PARAMETER(struct_size);
#endif
	assert(array != NULL);
	assert(array->interface != NULL);
	return array->interface;
}

size_t dynamic_array_capacity_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	int line_number,
	size_t struct_size
){
	const dynamic_array_internal_type *array = (const dynamic_array_internal_type*) dynamic_array;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = __LINE__;
	debug_info.struct_size = (unsigned short) struct_size;
	debug_info.internal_struct_size = (unsigned short) sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		if (array != NULL and array->interface != NULL) {
			dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		}
		return 0U;
	}
#else
	UNUSED_PARAMETER(file_name);
	UNUSED_PARAMETER(line_number);
	UNUSED_PARAMETER(struct_size);
#endif
	assert(array != NULL);
	return array->capacity;
}

size_t dynamic_array_size_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	int line_number,
	size_t struct_size
){
	const dynamic_array_internal_type *array = (const dynamic_array_internal_type*) dynamic_array;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = __LINE__;
	debug_info.struct_size = (unsigned short) struct_size;
	debug_info.internal_struct_size = (unsigned short) sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		if (array != NULL and array->interface != NULL) {
			dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		}
		return 0U;
	}
#else
	UNUSED_PARAMETER(file_name);
	UNUSED_PARAMETER(line_number);
	UNUSED_PARAMETER(struct_size);
#endif
	assert(array != NULL);
	return array->number_of_elements;
}

void *dynamic_array_element_ptr_(
	const dynamic_array_type_ *dynamic_array,
	size_t index,
	size_t element_size,
	const char *file_name,
	int line_number,
	size_t struct_size
){
	size_t offset = 0U;
	unsigned char *ptr = NULL;
	const dynamic_array_internal_type *array = (const dynamic_array_internal_type*) dynamic_array;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	Boolean_type multiplication_overflow_detected = Boolean_false;
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = __LINE__;
	debug_info.struct_size = (unsigned short) struct_size;
	debug_info.internal_struct_size = (unsigned short) sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		if (array != NULL and array->interface != NULL) {
			dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		}
		return NULL;
	}
#else
	UNUSED_PARAMETER(element_size);
	UNUSED_PARAMETER(file_name);
	UNUSED_PARAMETER(line_number);
	UNUSED_PARAMETER(struct_size);
#endif
	assert(array != NULL);
	assert(array->interface != NULL);
	assert(element_size == array->element_size);
	assert(index < array->number_of_elements);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size) {
		debug_info.error = dynamic_array_error_element_size_mismatch;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = element_size;
		debug_info.info_2 = array->element_size;
		dynamic_array_report_error(array->interface->error_reporter, debug_info);
		dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
	}

	if (index >= array->number_of_elements) {
		debug_info.error = dynamic_array_error_index_out_of_range;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = index;
		debug_info.info_2 = array->number_of_elements;
		dynamic_array_report_error(array->interface->error_reporter, debug_info);
		dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
	}

	multiplication_overflow_detected = dynamic_array_multiplication_overflow_detected(index, array->element_size);
	if (multiplication_overflow_detected) {
		debug_info.error = dynamic_array_error_multiplication_overflow_detected;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = index;
		debug_info.info_2 = array->element_size;
		dynamic_array_report_error(array->interface->error_reporter, debug_info);
		dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
	}
#endif
	offset = index * array->element_size;
	ptr = (unsigned char*) array->ptr;
	return &ptr[offset];
}

void dynamic_array_add_elements_at_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	const void *ptr_to_first_element,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	int line_number,
	size_t struct_size
){
	size_t new_number_of_elements = 0U; 
	dynamic_array_internal_type *array = (dynamic_array_internal_type*) dynamic_array;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	Boolean_type addition_overflow_detected = Boolean_false;
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = __LINE__;
	debug_info.struct_size = (unsigned short) struct_size;
	debug_info.internal_struct_size = (unsigned short) sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		if (array != NULL and array->interface != NULL) {
			dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		}
		return;
	}
#else
	UNUSED_PARAMETER(file_name);
	UNUSED_PARAMETER(line_number);
	UNUSED_PARAMETER(struct_size);
#endif
	assert(array != NULL);
	assert(array->interface != NULL);
	assert(ptr_to_first_element != NULL);
	if (ptr_to_first_element == NULL) {
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		debug_info.error = dynamic_array_error_null_pointer_exception;
		debug_info.library_line_number = __LINE__;
		dynamic_array_report_error(array->interface->error_reporter, debug_info);
		dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
#endif
		return;
	}

	assert(element_size == array->element_size);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size) {
		debug_info.error = dynamic_array_error_element_size_mismatch;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = element_size;
		debug_info.info_2 = array->element_size;
		dynamic_array_report_error(array->interface->error_reporter, debug_info);
		dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		return;
	}
#endif
	assert(index <= array->number_of_elements);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (index > array->number_of_elements) {
		debug_info.error = dynamic_array_error_index_out_of_range;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = index;
		debug_info.info_2 = array->number_of_elements;
		dynamic_array_report_error(array->interface->error_reporter, debug_info);
		dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		return;
	}
#endif

#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	addition_overflow_detected = dynamic_array_addition_overflow_detected(array->number_of_elements, number_of_elements);
	if (addition_overflow_detected) {
		debug_info.error = dynamic_array_error_addition_overflow_detected;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = array->number_of_elements;
		debug_info.info_2 = number_of_elements;
		dynamic_array_report_error(array->interface->error_reporter, debug_info);
		dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		return;
	}
#endif
	if (number_of_elements < 1) {
		return;
	}
	new_number_of_elements = array->number_of_elements + number_of_elements;
	if (new_number_of_elements > array->capacity) {
		void *ptr = NULL;
		size_t old_byte_count = 0U, new_byte_count = 0U;
		size_t new_capacity = array->capacity;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		Boolean_type multiplication_overflow_detected = Boolean_false;
#endif
		while (new_capacity < new_number_of_elements) {
			new_capacity += new_capacity;
		}
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		multiplication_overflow_detected = dynamic_array_multiplication_overflow_detected(new_capacity, array->element_size);
		if (multiplication_overflow_detected) {
			debug_info.error = dynamic_array_error_multiplication_overflow_detected;
			debug_info.library_line_number = __LINE__;
			debug_info.info_1 = new_capacity;
			debug_info.info_2 = array->element_size;
			dynamic_array_report_error(array->interface->error_reporter, debug_info);
			dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
			return;
		}
#endif
		old_byte_count = array->capacity * array->element_size;
		new_byte_count = new_capacity * array->element_size;
		ptr = allocator_reallocate(array->interface->allocator, array->ptr, old_byte_count, new_byte_count);
		if (ptr != NULL) {
			array->ptr = ptr;
			array->capacity = new_capacity;
		} else {
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
			debug_info.error = dynamic_array_error_memory_reallocation_failure;
			debug_info.library_line_number = __LINE__;
			debug_info.info_1 = new_byte_count;
			dynamic_array_report_error(array->interface->error_reporter, debug_info);
			dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
#endif
			return;
		}
	}

	if (index == array->number_of_elements) {
		const size_t offset = array->number_of_elements * array->element_size;
		unsigned char *ptr = (unsigned char*) array->ptr;
		const size_t total_bytes_to_copy = number_of_elements * element_size;
		memcpy(&ptr[offset], ptr_to_first_element, total_bytes_to_copy);
		array->number_of_elements = new_number_of_elements;
	} else if (index < array->number_of_elements) {
		const size_t src_offset = index * array->element_size;
		const size_t dst_offset = (index + number_of_elements) * array->element_size;
		const size_t total_elements_to_move = array->number_of_elements - index;
		const size_t total_bytes_to_move = total_elements_to_move * array->element_size;
		const size_t total_bytes_to_copy = number_of_elements * element_size;
		unsigned char *ptr = (unsigned char*) array->ptr;
		memmove(&ptr[dst_offset], &ptr[src_offset], total_bytes_to_move);
		memcpy(&ptr[src_offset], ptr_to_first_element, total_bytes_to_copy);
		array->number_of_elements = new_number_of_elements;
	}
}

void dynamic_array_remove_elements_starting_from_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	void *output_buffer,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	int line_number,
	size_t struct_size
){
	dynamic_array_internal_type *array = (dynamic_array_internal_type*) dynamic_array;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = __LINE__;
	debug_info.struct_size = (unsigned short) struct_size;
	debug_info.internal_struct_size = (unsigned short) sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		if (array != NULL && array->interface != NULL) {
			dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		}
		return;
	}
#else
	UNUSED_PARAMETER(file_name);
	UNUSED_PARAMETER(line_number);
	UNUSED_PARAMETER(struct_size);
#endif
	assert(array != NULL);
	assert(array->interface != NULL);
	assert(element_size == array->element_size);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size) {
		debug_info.error = dynamic_array_error_element_size_mismatch;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = element_size;
		debug_info.info_2 = array->element_size;
		dynamic_array_report_error(array->interface->error_reporter, debug_info);
		dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		return;
	}
#endif
	assert(index < array->number_of_elements);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (index >= array->number_of_elements) {
		debug_info.error = dynamic_array_error_index_out_of_range;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = index;
		debug_info.info_2 = array->number_of_elements;
		dynamic_array_report_error(array->interface->error_reporter, debug_info);
		dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		return;
	}
#endif
	if (number_of_elements > 0) {
		unsigned char *ptr = NULL;
		size_t offset = 0U, total_bytes_to_zero = 0U;
		const size_t number_of_elements_from_index_to_last_index = array->number_of_elements - index;
		const size_t number_of_elements_to_remove = (number_of_elements < number_of_elements_from_index_to_last_index) ?
			number_of_elements : number_of_elements_from_index_to_last_index;
		const size_t number_of_elements_to_move = number_of_elements_from_index_to_last_index - number_of_elements_to_remove;

		if (output_buffer != NULL) {
			const size_t total_bytes_to_copy = number_of_elements_to_remove * element_size;
			const size_t src_offset = index * array->element_size;
			unsigned char *src_ptr = ((unsigned char*) array->ptr) + src_offset;
			unsigned char *dst_ptr = (unsigned char*) output_buffer;
			memcpy(dst_ptr, src_ptr, total_bytes_to_copy);
		}

		if (number_of_elements_to_move > 0) {
			const size_t src_offset = (index + number_of_elements_to_remove) * array->element_size;
			const size_t dst_offset = index * array->element_size;
			const size_t total_bytes_to_move = number_of_elements_to_move * array->element_size;
			unsigned char *ptr = (unsigned char*) array->ptr;
			memmove(&ptr[dst_offset], &ptr[src_offset], total_bytes_to_move);
		}

		assert(array->number_of_elements >= number_of_elements_to_remove);
		array->number_of_elements -= number_of_elements_to_remove;
		offset = array->number_of_elements * array->element_size;
		total_bytes_to_zero = number_of_elements_to_remove * array->element_size;
		ptr = (unsigned char*) array->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
	}
}

void dynamic_array_resize_(
	dynamic_array_type_ *dynamic_array,
	size_t new_size,
	size_t element_size,
	const char *file_name,
	int line_number,
	size_t struct_size
){
	const size_t new_number_of_elements = new_size;
	dynamic_array_internal_type *array = (dynamic_array_internal_type*) dynamic_array;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = __LINE__;
	debug_info.struct_size = (unsigned short) struct_size;
	debug_info.internal_struct_size = (unsigned short) sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		if (array != NULL and array->interface != NULL) {
			dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		}
		return;
	}
#else
	UNUSED_PARAMETER(element_size);
	UNUSED_PARAMETER(file_name);
	UNUSED_PARAMETER(line_number);
	UNUSED_PARAMETER(struct_size);
#endif
	assert(array != NULL);
	assert(array->interface != NULL);
	assert(element_size == array->element_size);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size) {
		debug_info.error = dynamic_array_error_element_size_mismatch;
		debug_info.library_line_number = __LINE__;
		debug_info.info_1 = element_size;
		debug_info.info_2 = array->element_size;
		dynamic_array_report_error(array->interface->error_reporter, debug_info);
		dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
		return;
	}
#endif
	if (new_number_of_elements > array->number_of_elements) {
		size_t extra_number_of_elements = 0U;
		size_t offset = 0U;
		size_t total_bytes_to_zero = 0U;
		unsigned char *ptr = NULL;

		if (new_number_of_elements > array->capacity) {
			size_t old_byte_count = 0U, new_byte_count = 0U;
			void *ptr = NULL;
			size_t new_capacity = array->capacity;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
			Boolean_type multiplication_overflow_detected = Boolean_false;
#endif
			while (new_capacity < new_number_of_elements) {
				new_capacity += new_capacity;
			}
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
			multiplication_overflow_detected = dynamic_array_multiplication_overflow_detected(new_capacity, array->element_size);
			if (multiplication_overflow_detected) {
				debug_info.error = dynamic_array_error_multiplication_overflow_detected;
				debug_info.library_line_number = __LINE__;
				debug_info.info_1 = new_capacity;
				debug_info.info_2 = array->element_size;
				dynamic_array_report_error(array->interface->error_reporter, debug_info);
				dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
				return;
			}
#endif
			old_byte_count = array->capacity * array->element_size;
			new_byte_count = new_capacity * array->element_size;
			ptr = allocator_reallocate(array->interface->allocator, array->ptr, old_byte_count, new_byte_count);
			if (ptr != NULL) {
				array->ptr = ptr;
				array->capacity = new_capacity;
			} else {
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
				debug_info.error = dynamic_array_error_memory_reallocation_failure;
				debug_info.library_line_number = __LINE__;
				debug_info.info_1 = new_byte_count;
				dynamic_array_report_error(array->interface->error_reporter, debug_info);
				dynamic_array_handle_exception(array->interface->exception_handler, debug_info.error);
#endif
				return;
			}
		}

		extra_number_of_elements = new_number_of_elements - array->number_of_elements;
		offset = array->number_of_elements * array->element_size;
		total_bytes_to_zero = extra_number_of_elements * array->element_size;
		ptr = (unsigned char*) array->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
		array->number_of_elements = new_number_of_elements;
	} else if (new_number_of_elements < array->number_of_elements) {
		const size_t number_of_elements_to_remove = array->number_of_elements - new_number_of_elements;
		const size_t offset = new_number_of_elements * array->element_size;
		const size_t total_bytes_to_zero = number_of_elements_to_remove * array->element_size;
		unsigned char *ptr = (unsigned char*) array->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
		array->number_of_elements = new_number_of_elements;
	}
}
