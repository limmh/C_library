#include "keyboard_input.h"
#include <ctype.h>
#include <iso646.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	const int Esc_key = 0x1B;
	unsigned long count = 0U;

	printf("Press Esc to exit.\n");

	for (;;) {
		int error = 0;
		size_t index = 0U;
		keyboard_input_type input = {0};

		keyboard_input_result_type result = get_unbuffered_keyboard_input();
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
				} else if (isprint(input.keycode[index])) {
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

	return 0;
}
