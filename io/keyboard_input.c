#include "keyboard_input.h"
#include "sizeof_array.h"

#include <assert.h>
#include <errno.h>
#include <iso646.h>

/* OS-specific header files */
#if !(defined(_WIN32) || defined(WIN32))
#include <fcntl.h>
#include <poll.h>
#include <termios.h>
#include <unistd.h>
#else
#include <conio.h>
#include <Windows.h>
#endif

keyboard_input_result_type keyboard_input_from_terminal(void)
{
	keyboard_input_result_type result = {{0U, {0U}}, 0};

#if !(defined(_WIN32) || defined(WIN32))

	struct termios old_terminal_settings = {0};
	int status = tcgetattr(STDIN_FILENO, &old_terminal_settings);
	if (status == 0) {
		const int Esc = 0x1B;
		struct termios new_terminal_settings = old_terminal_settings;
		new_terminal_settings.c_lflag &= ~((tcflag_t)ICANON); /* disable canonical mode (line buffering) */
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
			if (status != 0 and result.error == 0) {
				result.error = errno;
			}
		} else {
			result.error = errno;
		}
	} else {
		result.error = errno;
	}

#else

	const Boolean_type echo_mode = keyboard_input_terminal_echo_mode();
	result.input.keycode[0] = (unsigned char) (echo_mode ? getche() : getch());
	if (result.input.keycode[0] == 0 or result.input.keycode[0] == 0xE0) {
		/* Extended keys always have a second byte already in the buffer. A bare character has no following byte. */
		if (_kbhit()) {
			result.input.keycode[1] = (unsigned char) (echo_mode ? getche() : getch());
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

keyboard_input_result_type keyboard_input_from_terminal_nonblocking(void)
{
	keyboard_input_result_type result = {{0U, {0U}}, 0};
#if !(defined(_WIN32) || defined(WIN32))
	const int old_fcntl_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	if (old_fcntl_flags != -1) {
		const int new_fcntl_flags = old_fcntl_flags | O_NONBLOCK;
		int status = fcntl(STDIN_FILENO, F_SETFL, new_fcntl_flags);
		if (status != -1) {
			result = keyboard_input_from_terminal();
			if (result.error == EAGAIN or result.error == EWOULDBLOCK) {
				result.error = 0;
			}
		} else {
			result.error = errno;
		}
		status = fcntl(STDIN_FILENO, F_SETFL, old_fcntl_flags);
		if (status == -1 and result.error == 0) {
			result.error = errno;
		}
	} else {
		result.error = errno;
	}
#else
	if (_kbhit()) {
		result = keyboard_input_from_terminal();
	}
#endif
	return result;
}


int keyboard_input_set_terminal_echo_mode(Boolean_type echo_mode)
{
	int error = 0;
#if !(defined(_WIN32) || defined(WIN32))
	struct termios terminal_settings = {0};
	int status = tcgetattr(STDIN_FILENO, &terminal_settings);
	if (status == 0) {
		if (echo_mode) {
			terminal_settings.c_lflag |= (tcflag_t) ECHO;
		} else {
			terminal_settings.c_lflag &= ~((tcflag_t) ECHO);
		}
		status = tcsetattr(STDIN_FILENO, TCSANOW, &terminal_settings);
		if (status != 0) {
			error = errno;
		}
	} else {
		error = errno;
	}
#else
	HANDLE stdin_handle = GetStdHandle(STD_INPUT_HANDLE);
	if (stdin_handle != INVALID_HANDLE_VALUE) {
		DWORD mode = 0U;
		BOOL success = GetConsoleMode(stdin_handle, &mode);
		if (success) {
			const DWORD new_mode = echo_mode ? (mode | ENABLE_ECHO_INPUT) : (mode & ~((DWORD) ENABLE_ECHO_INPUT));
			success = SetConsoleMode(stdin_handle, new_mode);
			if (not success) {
				error = EPERM;
			}
		} else {
			error = EIO;
		}
	} else {
		error = EIO;
	}
#endif
	return error;
}

Boolean_type keyboard_input_terminal_echo_mode(void)
{
	Boolean_type echo_mode = Boolean_false;
#if !(defined(_WIN32) || defined(WIN32))
	struct termios terminal_settings = {0};
	int status = tcgetattr(STDIN_FILENO, &terminal_settings);
	if (status == 0) {
		echo_mode = ((terminal_settings.c_lflag & (tcflag_t) ECHO) != 0);
	}
#else
	HANDLE stdin_handle = GetStdHandle(STD_INPUT_HANDLE);
	if (stdin_handle != INVALID_HANDLE_VALUE) {
		DWORD mode = 0U;
		BOOL success = GetConsoleMode(stdin_handle, &mode);
		if (success) {
			echo_mode = ((mode & ENABLE_ECHO_INPUT) != 0U);
		}
	}
#endif
	return echo_mode;
}

Boolean_type keyboard_input_is_extended_key_(const keyboard_input_type *p_input)
{
	assert(p_input != NULL);
#if !(defined(_WIN32) || defined(WIN32))
	/* Linux: escape sequence has ESC as first byte and at least one more byte */
	return (p_input->number_of_bytes > 1U and p_input->keycode[0] == 0x1B);
#else
	/* Windows: first byte (0x00 or 0xE0) followed by a scan code byte */
	return (p_input->number_of_bytes == 2U and (p_input->keycode[0] == 0x00 or p_input->keycode[0] == 0xE0));
#endif
}
