#include "fat_pointer.h"
#include "unit_testing.h"
#include "sizeof_array.h"
#include <stddef.h>
#include <string.h>

TEST(fat_pointer_referencing_a_char_buffer, "Fat pointer referencing a char buffer")
{
	fat_pointer_error_type error = fat_pointer_error_none;
	const char *read_only_string = "Hello, World";
	char buffer[13] = {0};
	char *ptr = NULL;
	fat_pointer_type(char) cfatptr = fat_pointer_create(char, buffer, sizeof_array(buffer), 0U);

	/* before modification */
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 0U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));

	/* adding elements */
	error = fat_pointer_add_elements_at_index(char, cfatptr, 0U, read_only_string, strlen(read_only_string) + 1U);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));
	ptr = fat_pointer_element_ptr(char, cfatptr, 0U);
	ASSERT(ptr == &buffer[0]);
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 0U), 'H');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 1U), 'e');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 2U), 'l');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 3U), 'l');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 4U), 'o');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 5U), ',');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 6U), ' ');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 7U), 'W');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 8U), 'o');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 9U), 'r');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 10U), 'l');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 11U), 'd');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 12U), '\0');
	ASSERT_SIZE_EQUAL(strlen(fat_pointer_element_ptr(char, cfatptr, 0U)), 12U);
	ASSERT_EQUAL(buffer[0], 'H');
	ASSERT_EQUAL(buffer[1], 'e');
	ASSERT_EQUAL(buffer[2], 'l');
	ASSERT_EQUAL(buffer[3], 'l');
	ASSERT_EQUAL(buffer[4], 'o');
	ASSERT_EQUAL(buffer[5], ',');
	ASSERT_EQUAL(buffer[6], ' ');
	ASSERT_EQUAL(buffer[7], 'W');
	ASSERT_EQUAL(buffer[8], 'o');
	ASSERT_EQUAL(buffer[9], 'r');
	ASSERT_EQUAL(buffer[10], 'l');
	ASSERT_EQUAL(buffer[11], 'd');
	ASSERT_EQUAL(buffer[12], '\0');
	ASSERT_SIZE_EQUAL(strlen(buffer), 12U);

	/* removing elements */
	error = fat_pointer_remove_elements_starting_from_index(char, cfatptr, 0U, 7U);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 6U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));
	ptr = fat_pointer_element_ptr(char, cfatptr, 0U);
	ASSERT(ptr == &buffer[0]);
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 0U), 'W');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 1U), 'o');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 2U), 'r');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 3U), 'l');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 4U), 'd');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 5U), '\0');
	ASSERT_SIZE_EQUAL(strlen(fat_pointer_element_ptr(char, cfatptr, 0U)), 5U);
	ASSERT_EQUAL(buffer[0], 'W');
	ASSERT_EQUAL(buffer[1], 'o');
	ASSERT_EQUAL(buffer[2], 'r');
	ASSERT_EQUAL(buffer[3], 'l');
	ASSERT_EQUAL(buffer[4], 'd');
	ASSERT_EQUAL(buffer[5], '\0');
	ASSERT_SIZE_EQUAL(strlen(buffer), 5U);

	/* removing a single element at a time */
	error = fat_pointer_remove_element_at_index(char, cfatptr, 3U);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 5U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));
	ptr = fat_pointer_element_ptr(char, cfatptr, 0U);
	ASSERT(ptr == &buffer[0]);
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 0U), 'W');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 1U), 'o');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 2U), 'r');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 3U), 'd');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 4U), '\0');
	ASSERT_SIZE_EQUAL(strlen(fat_pointer_element_ptr(char, cfatptr, 0U)), 4U);
	ASSERT_EQUAL(buffer[0], 'W');
	ASSERT_EQUAL(buffer[1], 'o');
	ASSERT_EQUAL(buffer[2], 'r');
	ASSERT_EQUAL(buffer[3], 'd');
	ASSERT_EQUAL(buffer[4], '\0');
	ASSERT_SIZE_EQUAL(strlen(buffer), 4U);

	error = fat_pointer_resize(cfatptr, 0U);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 0U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));

	error = fat_pointer_resize(cfatptr, 13U);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 0U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 1U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 2U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 3U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 4U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 5U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 6U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 7U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 8U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 9U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 10U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 11U), '\0');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 12U), '\0');

	fat_pointer_destroy(cfatptr);
}

TEST(fat_pointer_referencing_an_integer_buffer, "Fat pointer referencing an integer array")
{
	fat_pointer_error_type error = fat_pointer_error_none;
	size_t index = 0U;
	int var = 0, var2 = 0;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int dest_array[sizeof_array(array) / 2U] = {0};
	fat_pointer_type(int) fatptr = fat_pointer_create(int, array, sizeof_array(array), sizeof_array(array));

	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 0);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 1);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 2);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 3);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 4);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 5U), 5);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 6U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 7U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 8U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 9U), 9);

	for (index = 0U; index < fat_pointer_length(fatptr); ++index) {
		++fat_pointer_element(int, fatptr, index);
	}

	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 1);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 2);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 3);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 4);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 5);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 5U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 6U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 7U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 8U), 9);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 9U), 10);
	ASSERT_EQUAL(array[0], 1);
	ASSERT_EQUAL(array[1], 2);
	ASSERT_EQUAL(array[2], 3);
	ASSERT_EQUAL(array[3], 4);
	ASSERT_EQUAL(array[4], 5);
	ASSERT_EQUAL(array[5], 6);
	ASSERT_EQUAL(array[6], 7);
	ASSERT_EQUAL(array[7], 8);
	ASSERT_EQUAL(array[8], 9);
	ASSERT_EQUAL(array[9], 10);

	index = 0U;
	error = fat_pointer_move_elements_starting_from_index_to_buffer(int, fatptr, index, dest_array, sizeof_array(dest_array)); 
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 5U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 9);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 10);
	ASSERT_EQUAL(array[0], 6);
	ASSERT_EQUAL(array[1], 7);
	ASSERT_EQUAL(array[2], 8);
	ASSERT_EQUAL(array[3], 9);
	ASSERT_EQUAL(array[4], 10);
	ASSERT_EQUAL(dest_array[0], 1);
	ASSERT_EQUAL(dest_array[1], 2);
	ASSERT_EQUAL(dest_array[2], 3);
	ASSERT_EQUAL(dest_array[3], 4);
	ASSERT_EQUAL(dest_array[4], 5);

	var = 11;
	error = fat_pointer_push_back(int, fatptr, var);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 6U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 9);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 10);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 5U), 11);
	ASSERT_EQUAL(array[0], 6);
	ASSERT_EQUAL(array[1], 7);
	ASSERT_EQUAL(array[2], 8);
	ASSERT_EQUAL(array[3], 9);
	ASSERT_EQUAL(array[4], 10);
	ASSERT_EQUAL(array[5], 11);

	error = fat_pointer_pop_back(int, fatptr, var2);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 5U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 9);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 10);
	ASSERT_EQUAL(array[0], 6);
	ASSERT_EQUAL(array[1], 7);
	ASSERT_EQUAL(array[2], 8);
	ASSERT_EQUAL(array[3], 9);
	ASSERT_EQUAL(array[4], 10);
	ASSERT_EQUAL(var2, 11);

	error = fat_pointer_resize(fatptr, 10U);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 9);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 10);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 5U), 0);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 6U), 0);	
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 7U), 0);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 8U), 0);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 9U), 0);	

	fat_pointer_destroy(fatptr);
}

TEST(fat_pointer_referencing_a_struct_buffer, "Fat pointer referencing a struct buffer")
{
	typedef struct name_type {const char *first_name; const char *last_name;} name_type;
	typedef struct date_type {short year; unsigned char month; unsigned char day;} date_type;
	typedef struct person_type {name_type name; date_type date_of_birth;} person_type;

	person_type people[4] = {0};
	person_type person = {0};

	fat_pointer_type(person_type) person_fatptr = fat_pointer_create(person_type, people, sizeof_array(people), 0U);

	person.name.first_name = "John";
	person.name.last_name = "Doe";
	person.date_of_birth.year = 1990;
	person.date_of_birth.month = 1;
	person.date_of_birth.day = 1;
	fat_pointer_append_element(person_type, person_fatptr, person);

	person.name.first_name = "Jane";
	person.date_of_birth.year = 1995;
	person.date_of_birth.month = 12;
	fat_pointer_append_element(person_type, person_fatptr, person);

	person.name.last_name = "Smith";
	person.date_of_birth.year = 1991;
	person.date_of_birth.month = 11;
	person.date_of_birth.day = 30;
	fat_pointer_add_element_at_index(person_type, person_fatptr, 1, person);

	person.name.first_name = "John";
	person.date_of_birth.year = 1987;
	person.date_of_birth.month = 5;
	person.date_of_birth.day = 21;
	fat_pointer_add_element_at_index(person_type, person_fatptr, 0, person);

	ASSERT(fat_pointer_element_ptr(person_type, person_fatptr, 0U) == &people[0]);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(person_fatptr), 4U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(person_fatptr), 4U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(person_fatptr), sizeof(person));

	ASSERT_STRING_EQUAL(fat_pointer_element(person_type, person_fatptr, 0).name.first_name, "John");
	ASSERT_STRING_EQUAL(fat_pointer_element(person_type, person_fatptr, 0).name.last_name, "Smith");
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 0).date_of_birth.year, 1987);
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 0).date_of_birth.month, 5);
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 0).date_of_birth.day, 21);

	ASSERT_STRING_EQUAL(fat_pointer_element(person_type, person_fatptr, 1).name.first_name, "John");
	ASSERT_STRING_EQUAL(fat_pointer_element(person_type, person_fatptr, 1).name.last_name, "Doe");
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 1).date_of_birth.year, 1990);
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 1).date_of_birth.month, 1);
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 1).date_of_birth.day, 1);

	ASSERT_STRING_EQUAL(fat_pointer_element(person_type, person_fatptr, 2).name.first_name, "Jane");
	ASSERT_STRING_EQUAL(fat_pointer_element(person_type, person_fatptr, 2).name.last_name, "Smith");
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 2).date_of_birth.year, 1991);
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 2).date_of_birth.month, 11);
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 2).date_of_birth.day, 30);

	ASSERT_STRING_EQUAL(fat_pointer_element(person_type, person_fatptr, 3).name.first_name, "Jane");
	ASSERT_STRING_EQUAL(fat_pointer_element(person_type, person_fatptr, 3).name.last_name, "Doe");
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 3).date_of_birth.year, 1995);
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 3).date_of_birth.month, 12);
	ASSERT_EQUAL(fat_pointer_element(person_type, person_fatptr, 3).date_of_birth.day, 1);

	fat_pointer_remove_elements_starting_from_index(person_type, person_fatptr, 0U, 4U);

	ASSERT_SIZE_EQUAL(fat_pointer_capacity(person_fatptr), 4U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(person_fatptr), 0U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(person_fatptr), sizeof(person));

	fat_pointer_destroy(person_fatptr);
}

TEST(immutable_fat_pointer_referencing_a_const_char_buffer, "Immutable fat pointer referencing a const char buffer")
{
	const char *read_only_string = "Hello, World";
	const char *ptr = NULL;
	immutable_fat_pointer_type(char) cfatptr = immutable_fat_pointer_create(char, read_only_string,
		strlen(read_only_string) + 1U, strlen(read_only_string) + 1U);

	ASSERT_SIZE_EQUAL(immutable_fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(immutable_fat_pointer_length(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(immutable_fat_pointer_element_size(cfatptr), sizeof(char));

	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 0U), 'H');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 1U), 'e');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 2U), 'l');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 3U), 'l');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 4U), 'o');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 5U), ',');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 6U), ' ');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 7U), 'W');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 8U), 'o');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 9U), 'r');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 10U), 'l');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 11U), 'd');
	ASSERT_EQUAL(immutable_fat_pointer_element(char, cfatptr, 12U), '\0');

	ptr = immutable_fat_pointer_element_ptr(char, cfatptr, 0U);
	ASSERT(ptr == read_only_string);
	ASSERT_SIZE_EQUAL(strlen(ptr), 12U);

	immutable_fat_pointer_destroy(cfatptr);
}

TEST(immutable_fat_pointer_referencing_a_const_integer_array, "Immutable fat pointer referencing a const integer array")
{
	const int const_array[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	const int *ptr = NULL;
	immutable_fat_pointer_type(int) cfatptr = immutable_fat_pointer_create(int, const_array,
		sizeof_array(const_array), sizeof_array(const_array));

	ASSERT_SIZE_EQUAL(immutable_fat_pointer_capacity(cfatptr), 10U);
	ASSERT_SIZE_EQUAL(immutable_fat_pointer_length(cfatptr), 10U);
	ASSERT_SIZE_EQUAL(immutable_fat_pointer_element_size(cfatptr), sizeof(int));

	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 0U), 10);
	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 1U), 20);
	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 2U), 30);
	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 3U), 40);
	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 4U), 50);
	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 5U), 60);
	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 6U), 70);
	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 7U), 80);
	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 8U), 90);
	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 9U), 100);

	ptr = immutable_fat_pointer_element_ptr(int, cfatptr, 0U);
	ASSERT(ptr == const_array);

	immutable_fat_pointer_destroy(cfatptr);
}

TEST(immutable_fat_pointer_referencing_const_struct_array, "Immutable fat pointer referencing const struct array")
{
	typedef struct name_type {const char *first_name; const char *last_name;} name_type;
	typedef struct date_type {short year; unsigned char month; unsigned char day;} date_type;
	typedef struct person_type {name_type name; date_type date_of_birth;} person_type;

	const person_type people[4] = {
		{{"John", "Smith"}, {1987, 5, 21}},
		{{"John", "Doe"}, {1990, 1, 1}},
		{{"Jane", "Smith"}, {1991, 11, 30}},
		{{"Jane", "Doe"}, {1995, 12, 1}}
	};

	immutable_fat_pointer_type(person_type) person_fatptr = immutable_fat_pointer_create(person_type, people, sizeof_array(people), sizeof_array(people));

	ASSERT(immutable_fat_pointer_element_ptr(person_type, person_fatptr, 0U) == &people[0]);
	ASSERT_SIZE_EQUAL(immutable_fat_pointer_capacity(person_fatptr), 4U);
	ASSERT_SIZE_EQUAL(immutable_fat_pointer_length(person_fatptr), 4U);
	ASSERT_SIZE_EQUAL(immutable_fat_pointer_element_size(person_fatptr), sizeof(person_type));

	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 0).name.first_name, "John");
	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 0).name.last_name, "Smith");
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 0).date_of_birth.year, 1987);
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 0).date_of_birth.month, 5);
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 0).date_of_birth.day, 21);

	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 1).name.first_name, "John");
	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 1).name.last_name, "Doe");
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 1).date_of_birth.year, 1990);
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 1).date_of_birth.month, 1);
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 1).date_of_birth.day, 1);

	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 2).name.first_name, "Jane");
	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 2).name.last_name, "Smith");
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 2).date_of_birth.year, 1991);
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 2).date_of_birth.month, 11);
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 2).date_of_birth.day, 30);

	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 3).name.first_name, "Jane");
	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 3).name.last_name, "Doe");
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 3).date_of_birth.year, 1995);
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 3).date_of_birth.month, 12);
	ASSERT_EQUAL(immutable_fat_pointer_element(person_type, person_fatptr, 3).date_of_birth.day, 1);

	immutable_fat_pointer_destroy(person_fatptr);
}

TEST(immutable_fat_pointer_string_array, "Immutable fat pointer referencing array of string pointers")
{
	const char * const string_array[] = {"Alice", "Bob", "Charlie", "Diana", "Eve"};

	immutable_fat_pointer_type(char*) cfatptr = immutable_fat_pointer_create(char*, string_array,
		sizeof_array(string_array), sizeof_array(string_array));

	ASSERT_SIZE_EQUAL(immutable_fat_pointer_capacity(cfatptr), 5U);
	ASSERT_SIZE_EQUAL(immutable_fat_pointer_length(cfatptr), 5U);

	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(char*, cfatptr, 0U), "Alice");
	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(char*, cfatptr, 1U), "Bob");
	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(char*, cfatptr, 2U), "Charlie");
	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(char*, cfatptr, 3U), "Diana");
	ASSERT_STRING_EQUAL(immutable_fat_pointer_element(char*, cfatptr, 4U), "Eve");

	immutable_fat_pointer_destroy(cfatptr);
}

TEST(immutable_fat_pointer_comparison_with_mutable_fat_pointer, "Mutable and immutable fat pointers can reference same data")
{
	int array[5] = {1, 2, 3, 4, 5};

	fat_pointer_type(int) mfatptr = fat_pointer_create(int, array, sizeof_array(array), sizeof_array(array));
	immutable_fat_pointer_type(int) cfatptr = immutable_fat_pointer_create(int, array,
		sizeof_array(array), sizeof_array(array));

	ASSERT_EQUAL(fat_pointer_capacity(mfatptr), immutable_fat_pointer_capacity(cfatptr));
	ASSERT_EQUAL(fat_pointer_length(mfatptr), immutable_fat_pointer_length(cfatptr));
	ASSERT_EQUAL(fat_pointer_element_size(mfatptr), immutable_fat_pointer_element_size(cfatptr));

	ASSERT_EQUAL(fat_pointer_element(int, mfatptr, 0), immutable_fat_pointer_element(int, cfatptr, 0));
	ASSERT_EQUAL(fat_pointer_element(int, mfatptr, 1), immutable_fat_pointer_element(int, cfatptr, 1));
	ASSERT_EQUAL(fat_pointer_element(int, mfatptr, 2), immutable_fat_pointer_element(int, cfatptr, 2));
	ASSERT_EQUAL(fat_pointer_element(int, mfatptr, 3), immutable_fat_pointer_element(int, cfatptr, 3));
	ASSERT_EQUAL(fat_pointer_element(int, mfatptr, 4), immutable_fat_pointer_element(int, cfatptr, 4));

	/* modify via the mutable pointer and verify that the immutable pointer sees the change */
	fat_pointer_element(int, mfatptr, 0U) = 100;
	ASSERT_EQUAL(immutable_fat_pointer_element(int, cfatptr, 0U), 100);

	immutable_fat_pointer_destroy(cfatptr);
	fat_pointer_destroy(mfatptr);
}

/* More tests may be added in the future */

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		fat_pointer_referencing_a_char_buffer,
		fat_pointer_referencing_an_integer_buffer,
		fat_pointer_referencing_a_struct_buffer,
		immutable_fat_pointer_referencing_a_const_char_buffer,
		immutable_fat_pointer_referencing_a_const_integer_array,
		immutable_fat_pointer_referencing_const_struct_array,
		immutable_fat_pointer_comparison_with_mutable_fat_pointer,
		immutable_fat_pointer_string_array
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
