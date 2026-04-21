#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include "Boolean_type.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief keyboard input data */
typedef struct keyboard_input_type
{
	size_t number_of_bytes;
	unsigned char keycode[8]; /* OS and locale specific */
} keyboard_input_type;

/** @brief keyboard input result */
typedef struct keyboard_input_result_type
{
	keyboard_input_type input;
	int error; /* errno */
} keyboard_input_result_type;

/**
 * @brief Gets a keyboard input from the terminal in blocking mode
 * @return keyboard_input_result_type Keyboard input data
 *
 * Reads one keyboard input event from the terminal without line buffering.
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
keyboard_input_result_type keyboard_input_from_terminal(void);

/**
 * @brief Gets a keyboard input from the terminal in non-blocking mode
 * @return keyboard_input_result_type Keyboard input data
 *
 * Reads one keyboard input event from the terminal without line buffering.
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
keyboard_input_result_type keyboard_input_from_terminal_nonblocking(void);

/**
 * @brief Sets the terminal echo mode.
 * @param [in] echo_mode (true or false)
 * @return int Error code
 *
 * Echo mode:
 * - true : echo is enabled  (keys will be displayed on the terminal)
 * - false: echo is disabled (keys will not be displayed on the terminal
 */
int keyboard_input_set_terminal_echo_mode(bool echo_mode);

/**
 * @brief Gets the terminal echo mode.
 * @return bool (true if echo is enabled, false if echo is disabled)
 */
bool keyboard_input_terminal_echo_mode(void);

/**
 * @brief Checks if the keyboard input represents an extended key
 * @param p_input A pointer to a keyboard input data instance
 * @return bool true if the input represents an extended key (a key with no directly
 * printable ASCII character, such as arrow keys or function keys), otherwise false
 *
 * On Linux, extended keys arrive as ANSI escape sequences: ESC (0x1B) followed
 * by one or more additional bytes. A bare ESC keypress has number_of_bytes == 1
 * and is NOT considered an extended key.
 *
 * On Windows, extended keys arrive as two bytes: a first byte (0x00
 * for legacy function keys, 0xE0 for navigation/arrow keys) followed by a
 * scan code byte.
 */
bool keyboard_input_is_extended_key_(const keyboard_input_type *p_input);

/**
 * @brief Checks if the keyboard input represents an extended key
 * @param input An instance of keyboard input (NOT a pointer)
 * @return bool
 */
#define keyboard_input_is_extended_key(input) keyboard_input_is_extended_key_(&(input))

#ifdef __cplusplus
}
#endif

#endif
