#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include "Boolean_type.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct keyboard_input_type
{
	size_t number_of_bytes;
	unsigned char keycode[8]; /* OS and locale specific */
} keyboard_input_type;

typedef struct keyboard_input_result_type
{
	keyboard_input_type input;
	int error; /* errno */
} keyboard_input_result_type;

/*
 * Reads one keyboard input event from the terminal without line buffering or echo.
 *
 * Blocks until at least one byte is available from the terminal.
 *
 * On Linux, the terminal is temporarily switched to raw mode for the duration
 * of the call and restored before returning.
 *
 * On Windows, reads one key-down event using getch(). Extended keys (arrow keys,
 * function keys, etc.) are returned as two bytes: a first byte (0x00 or
 * 0xE0) followed by a scan code byte.
 *
 * Return value:
 * A keyboard_input_result_type containing:
 *   - input.keycode        : the raw bytes of the key event (OS-specific encoding)
 *   - input.number_of_bytes: the number of valid bytes in keycode (0 on error)
 *   - error                : 0 on success, errno value
 *
 * Notes:
 * - Use keyboard_input_is_extended_key() to test whether the input is an
 *   extended key (arrow keys, function keys, etc.).
 * - The caller must not access keycode[i] for i >= input.number_of_bytes.
 */
keyboard_input_result_type
get_keyboard_input_from_terminal(void);

/*
 * Reads one keyboard input event from the terminal without line buffering or echo.
 *
 * Does not block.
 *
 * Return value:
 * A keyboard_input_result_type containing:
 *   - input.keycode        : the raw bytes of the key event (OS-specific encoding)
 *   - input.number_of_bytes: the number of valid bytes in keycode (0 on error)
 *   - error                : 0 on success, errno value
 *
 * Notes:
 * - Use keyboard_input_is_extended_key() to test whether the input is an
 *   extended key (arrow keys, function keys, etc.).
 * - The caller must not access keycode[i] for i >= input.number_of_bytes.
 */

keyboard_input_result_type
get_keyboard_input_from_terminal_nonblocking(void);

/*
 * Returns Boolean_true if the input represents an extended key (a key with no
 * directly printable ASCII character, such as arrow keys or function keys).
 *
 * On Linux, extended keys arrive as ANSI escape sequences: ESC (0x1B) followed
 * by one or more additional bytes. A bare ESC keypress has number_of_bytes == 1
 * and is NOT considered an extended key.
 *
 * On Windows, extended keys arrive as two bytes: a first byte (0x00
 * for legacy function keys, 0xE0 for navigation/arrow keys) followed by a
 * scan code byte.
 */
Boolean_type
keyboard_input_is_extended_key(keyboard_input_type input);

#ifdef __cplusplus
}
#endif

#endif
