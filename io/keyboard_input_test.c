#include "keyboard_input.h"
#include <ctype.h>
#include <iso646.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int error = 0;
	const int Esc_key = 0x1B;
	unsigned long count = 0U;
	Boolean_type echo_mode = Boolean_false;

	printf("Press Esc to exit.\n");

	echo_mode = keyboard_input_terminal_echo_mode();
	error = keyboard_input_set_terminal_echo_mode(Boolean_false);
	if (error != 0) {
		printf("An error occurred: %s\n", strerror(error));
	}

	for (;;) {
		size_t index = 0U;
		keyboard_input_type input = {0};

		keyboard_input_result_type result = keyboard_input_from_terminal();
		input = result.input;
		error = result.error;

		++count;
		printf("Input %lu: ", count);

		for (index = 0U; index < input.number_of_bytes; ++index) {
			printf("%02X ", input.keycode[index]);
		}

		if (input.number_of_bytes > 0U) {
			printf("(");
			for (index = 0U; index < input.number_of_bytes; ++index) {
				const unsigned char c = input.keycode[index];
				if (isspace(c)) {
					printf("<%d>", c);
				} else if (isprint(c)) {
					printf("%c", c);
				} else {
					printf("<%d>", c);
				}
			}
			printf(")");
		}

		if (error != 0) {
			printf("\nAn error occurred: %s", strerror(error));
		}

		printf("\n");

		if (input.number_of_bytes == 1U and input.keycode[0] == Esc_key) {
			break;
		}
	}

	(void) keyboard_input_set_terminal_echo_mode(echo_mode);
	return 0;
}
