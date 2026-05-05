#include "dynamic_string.h"
#include "dynamic_array.h"
#include "macro_alignof.h"
#include "static_assert.h"

#include <assert.h>
#include <iso646.h>

typedef struct dynamic_string_internal_type
{
	dynamic_array_type(char) array;
} dynamic_string_internal_type;

STATIC_ASSERT(sizeof(dynamic_string_type) == sizeof(dynamic_string_internal_type), "The size of dynamic_string_type shall be the same as the size of dynamic_string_internal_type.");
STATIC_ASSERT(ALIGNOF(dynamic_string_type) == ALIGNOF(dynamic_string_internal_type), "dynamic_string_type and dynamic_string_internal_type must have the same memory alignment.");

dynamic_string_type
dynamic_string_create_(
	const char *string,
	size_t byte_length,
	const dynamic_array_interface_type *interface
){
	const char null_character = '\0';
	dynamic_string_internal_type internal_string = {0};
	dynamic_string_type dyn_string = {{0}};
	assert(interface != NULL);
	if (string != NULL and byte_length > 0) {
		internal_string.array = dynamic_array_create_from_source_with_interface(char, string, byte_length, *interface);
	} else {
		internal_string.array = dynamic_array_create_empty_with_interface(char, *interface);
	}
	dynamic_array_append_element(char, internal_string.array, null_character);
	memcpy(&dyn_string, &internal_string, sizeof(dyn_string));
	return dyn_string;
}

void dynamic_string_delete_(
	dynamic_string_type *pdynstring
){
	dynamic_string_internal_type *pdstring = (dynamic_string_internal_type*) pdynstring;
	assert(pdstring != NULL);
	dynamic_array_delete(pdstring->array);
}

size_t dynamic_string_byte_length_(
	const dynamic_string_type *pdynstring
){
	size_t length = 0U;
	const dynamic_string_internal_type *pdstring = (const dynamic_string_internal_type*) pdynstring;
	assert(pdstring != NULL);
	length = dynamic_array_length(pdstring->array);
	assert(length > 0);
	assert(dynamic_array_element(char, pdstring->array, length - 1) == '\0'); /* make sure the string is null-terminated */
	return (length > 0) ? (length - 1U) : 0U;
}

char *dynamic_string_ptr_(
	dynamic_string_type *pdynstring,
	size_t char_index
){
	dynamic_string_internal_type *pdstring = (dynamic_string_internal_type*) pdynstring;
	assert(pdstring != NULL);
	assert(char_index <= dynamic_string_byte_length_(pdynstring));
	return &dynamic_array_element(char, pdstring->array, char_index);
}

const char *dynamic_string_const_ptr_(
	const dynamic_string_type *pdynstring,
	size_t char_index
){
	const dynamic_string_internal_type *pdstring = (const dynamic_string_internal_type*) pdynstring;
	assert(pdstring != NULL);
	assert(char_index <= dynamic_string_byte_length_(pdynstring));
	return &dynamic_array_element(char, pdstring->array, char_index);
}

const char *dynamic_string_cstring_(
	const dynamic_string_type *pdynstring
){
	return dynamic_string_const_ptr_(pdynstring, 0U);
}

void dynamic_string_assign_(
	dynamic_string_type *pdynstring,
	const char *source_string,
	size_t byte_length
){
	const char null_character = '\0';
	dynamic_string_internal_type *pdstring = (dynamic_string_internal_type*) pdynstring;
	assert(pdstring != NULL);
	if (source_string != NULL and byte_length > 0) {
		dynamic_array_assign(char, pdstring->array, source_string, byte_length);
	} else {
		dynamic_array_clear(pdstring->array);
	}
	dynamic_array_append_element(char, pdstring->array, null_character);
} 

void dynamic_string_insert_(
	dynamic_string_type *pdynstring,
	size_t index,
	const char *source_string,
	size_t byte_length
){
	dynamic_string_internal_type *pdstring = (dynamic_string_internal_type*) pdynstring;
	assert(pdstring != NULL);
	if (source_string != NULL and byte_length > 0) {
		dynamic_array_add_elements_at_index(char, pdstring->array, index, source_string, byte_length);
	}
}

void dynamic_string_append_(
	dynamic_string_type *pdynstring,
	const char *source_string,
	size_t byte_length
){
	dynamic_string_internal_type *pdstring = (dynamic_string_internal_type*) pdynstring;
	assert(pdstring != NULL);
	if (source_string != NULL and byte_length > 0) {
		const size_t index = dynamic_string_byte_length_(pdynstring);
		dynamic_array_add_elements_at_index(char, pdstring->array, index, source_string, byte_length);
	}
}

void dynamic_string_remove_substring_(
	dynamic_string_type *pdynstring,
	size_t index,
	size_t byte_length
){
	const char null_character = '\0';
	size_t new_length = 0U;
	dynamic_string_internal_type *pdstring = (dynamic_string_internal_type*) pdynstring;
	assert(pdstring != NULL);
	dynamic_array_remove_elements_starting_from_index(char, pdstring->array, index, byte_length);
	new_length = dynamic_array_length(pdstring->array);
	if (new_length == 0 or dynamic_array_element(char, pdstring->array, new_length - 1) != null_character) {
		dynamic_array_append_element(char, pdstring->array, null_character);
	}
}

void dynamic_string_clear_(
	dynamic_string_type *pdynstring
){
	const char null_character = '\0';
	dynamic_string_internal_type *pdstring = (dynamic_string_internal_type*) pdynstring;
	assert(pdstring != NULL);
	dynamic_array_clear(pdstring->array);
	dynamic_array_append_element(char, pdstring->array, null_character);
}
