#include "keyboard_input.h"
#include "sizeof_array.h"

#include <assert.h>
#include <iso646.h>

/* OS-specific header files */
#if !(defined(_WIN32) || defined(WIN32))
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <termios.h>
#include <unistd.h>
#else
#include <conio.h>
#endif

keyboard_input_result_type
get_keyboard_input_from_terminal(void)
{
	keyboard_input_result_type result = {{0U, {0U}}, 0};

#if !(defined(_WIN32) || defined(WIN32))

	struct termios old_terminal_settings = {0};
	int status = tcgetattr(STDIN_FILENO, &old_terminal_settings);
	if (status == 0) {
		const int Esc = 0x1B;
		struct termios new_terminal_settings = old_terminal_settings;
		new_terminal_settings.c_lflag &= ~((tcflag_t)ICANON | ECHO); /* disable canonical mode (line buffering) and disable echo */
		new_terminal_settings.c_cc[VMIN] = 1; /* minimum number of characters to read */
		new_terminal_settings.c_cc[VTIME] = 0; /* timeout in deciseconds (0: no timeout) */

		status = tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal_settings);
		if (status == 0) {
			ssize_t number_of_bytes_read = read(STDIN_FILENO, &(result.input.keycode[0]), 1U);
			assert(number_of_bytes_read <= 1);
			if (number_of_bytes_read == 1) {
				/* Check for further bytes to differentiate from a single ESC press */
				if (result.input.keycode[0] == Esc) {
					const int timeout_ms = 50;
					struct pollfd file_descriptor = {STDIN_FILENO, POLLIN, 0};
					if (poll(&file_descriptor, 1, timeout_ms) > 0) {
						const size_t number_of_remaining_bytes = sizeof(result.input.keycode) - 1U;
						number_of_bytes_read = read(STDIN_FILENO, &(result.input.keycode[1]), number_of_remaining_bytes);
						assert(number_of_bytes_read <= (ssize_t) number_of_remaining_bytes);
						result.input.number_of_bytes += (number_of_bytes_read >= 0) ? (size_t) number_of_bytes_read : 0U;
						result.error = (number_of_bytes_read >= 0) ? 0 : errno;
					}
				}
				result.input.number_of_bytes += 1U;
			} else if (number_of_bytes_read < 0) {
				result.error = errno;
			}

			status = tcsetattr(STDIN_FILENO, TCSADRAIN, &old_terminal_settings);
			if (status != 0) {
				result.error = errno;
			}
		} else {
			result.error = errno;
		}
	} else {
		result.error = errno;
	}

#else

	result.input.keycode[0] = (unsigned char) getch();
	if (result.input.keycode[0] == 0 or result.input.keycode[0] == 0xE0) {
		/* Extended keys always have a second byte already in the buffer. A bare character has no following byte. */
		if (_kbhit()) {
			result.input.keycode[1] = (unsigned char) getch();
			result.input.number_of_bytes = 2U;
		} else {
			result.input.number_of_bytes = 1U;
		}
	} else {
        result.input.number_of_bytes = 1U;
    }

#endif

	assert(result.input.number_of_bytes <= sizeof_array(result.input.keycode));
	return result;
}

keyboard_input_result_type
get_keyboard_input_from_terminal_nonblocking(void)
{
	keyboard_input_result_type result = {{0U, {0U}}, 0};
#if !(defined(_WIN32) || defined(WIN32))
	const int old_fcntl_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	if (old_fcntl_flags != -1) {
		const int new_fcntl_flags = old_fcntl_flags | O_NONBLOCK;
		const int status = fcntl(STDIN_FILENO, F_SETFL, new_fcntl_flags);
		if (status != -1) {
			result = get_keyboard_input_from_terminal();
			if (result.error == EAGAIN or result.error == EWOULDBLOCK) {
				result.error = 0;
			}
		} else {
			result.error = errno;
		}
		if (fcntl(STDIN_FILENO, F_SETFL, old_fcntl_flags) == -1) {
			result.error = errno;
		}
	} else {
		result.error = errno;
	}
#else
	if (_kbhit()) {
		result = get_keyboard_input_from_terminal();
	}
#endif
	return result;
}

Boolean_type keyboard_input_is_extended_key(keyboard_input_type input)
{
#if !(defined(_WIN32) || defined(WIN32))
	/* Linux: escape sequence has ESC as first byte and at least one more byte */
	return (input.number_of_bytes > 1U and input.keycode[0] == 0x1B);
#else
	/* Windows: first byte (0x00 or 0xE0) followed by a scan code byte */
	return (input.number_of_bytes == 2U and (input.keycode[0] == 0x00 or input.keycode[0] == 0xE0));
#endif
}
