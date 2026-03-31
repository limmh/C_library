#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct keyboard_input_type
{
	size_t number_of_bytes;
	unsigned char keycode[8]; /* OS-specific */
} keyboard_input_type;

typedef struct keyboard_input_result_type
{
	keyboard_input_type input;
	int error; /* errno */
} keyboard_input_result_type;

keyboard_input_result_type
get_unbuffered_keyboard_input(void);

#ifdef __cplusplus
}
#endif

#endif
