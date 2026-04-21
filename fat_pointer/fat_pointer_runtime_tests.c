#include "fat_pointer.h"
#include <stdio.h>
#include <stdlib.h>

static int exception_flag = 0;

void my_exception_handler(fat_pointer_error_type error) {
	exception_flag = error;
}

void test_creation_and_basic_access() {
	int buffer[10];
	fat_pointer_type(int) f = fat_pointer_create(int, buffer, 10, 3);

	assert(fat_pointer_capacity(f) == 10);
	assert(fat_pointer_length(f) == 3);

	/* Set first three elements */
	*fat_pointer_element_ptr(int, f, 0) = 10;
	*fat_pointer_element_ptr(int, f, 1) = 20;
	*fat_pointer_element_ptr(int, f, 2) = 30;

	assert(fat_pointer_element(int, f, 1) == 20);
}

void test_add_and_remove_elements() {
	int buffer[5] = {1,2,3,4,5};
	fat_pointer_type(int) f = fat_pointer_create(int, buffer, 5, 5);

	int new_el = 42;
	fat_pointer_remove_element_at_index(int, f, 2);
	assert(fat_pointer_length(f) == 4);

	fat_pointer_add_element_at_index(int, f, 1, new_el);
	assert(fat_pointer_length(f) == 5);
	assert(fat_pointer_element(int, f, 1) == 42);
}

void test_resize_and_zero() {
	size_t i = 0U;
	int buffer[6] = {0};
	fat_pointer_type(int) f = fat_pointer_create(int, buffer, 6, 6);

	fat_pointer_resize(int, f, 3);
	assert(fat_pointer_length(f) == 3);

	fat_pointer_zero(f);
	for (i = 0; i < 3; ++i) {
		assert(fat_pointer_element(int, f, i) == 0);
	}
}

void test_out_of_bounds_and_errors() {
	int buf[4] = {0};
	fat_pointer_type(int) f = fat_pointer_create(int, buf, 4, 1);

	/* Set handler, expect error (out of bounds) */
	fat_pointer_set_exception_handler(my_exception_handler);

	exception_flag = 0;
	fat_pointer_element_ptr(int, f, 10); /* Should call handler and abort/exit (or set flag) */
	assert(exception_flag == fat_pointer_error_index_out_of_range);
}

void test_type_size_mismatch() {
	double buf[2] = {1.5, 2.5};
	/* The following line should static assert/fail at compile time (if your macro static_assert works)
	fat_pointer_type(float) f = fat_pointer_create(float, buf, 2, 2); */
}

int main(void) {
	test_creation_and_basic_access();
	test_add_and_remove_elements();
	test_resize_and_zero();

	/* Uncomment to test error paths, but be aware you may abort/exit: */
	/* test_out_of_bounds_and_errors(); */

	printf("All fat_pointer tests passed.\n");
	return 0;
}