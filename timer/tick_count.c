#include "tick_count.h"
#include "alternative_operators.h"
#include "Boolean_type.h"
#include "inline_or_static.h"
#include "safer_fixed_width_integers.h"

#include <assert.h>

#if defined(_WIN32) or defined(WIN32) or defined(_WIN64) or defined(WIN64)
#define TICK_COUNT_WINDOWS_BUILD 1
#else
#define TICK_COUNT_WINDOWS_BUILD 0
#endif

#if not TICK_COUNT_WINDOWS_BUILD
#include <time.h>
#include <errno.h>

#ifdef CLOCK_MONOTONIC
#define CLOCK_SOURCE CLOCK_MONOTONIC
#else
#define CLOCK_SOURCE CLOCK_REALTIME
#pragma message("CLOCK_REALTIME is used because CLOCK_MONOTONIC is not defined.")
#endif

#else
#include <Windows.h>
#endif

#define PREVIOUS_LINE (__LINE__ - 1)
#define NEXT_LINE (__LINE__ + 1)

static bool tick_count_overflow_checks_enabled = false;
static tick_count_error_handler_type tick_count_error_handler = NULL;

INLINE_OR_STATIC void tick_count_handle_error(
	tick_count_error_type error,
	int64_t internal_error,
	int64_t info_1,
	int64_t info_2,
	const char *source_file,
	int line
) {
	if (tick_count_error_handler != NULL) {
		tick_count_error_handler(error, internal_error, info_1, info_2, source_file, line);
	}
}

int64_t tick_count_now(void)
{
	int64_t tick_count = 0;
	int line_number = 0;

#if not TICK_COUNT_WINDOWS_BUILD
	int error_code = 0;
	int64_t resolution = 0;
	const int64_t second_to_nanosecond = 1000000000L;
	struct timespec ts = {0}, res = {0};
	bool should_continue = true;
	const bool overflow_checks_enabled = tick_count_overflow_checks_enabled;

	error_code = clock_gettime(CLOCK_SOURCE, &ts);
	line_number = PREVIOUS_LINE;
	if (error_code != 0) {
		should_continue = false;
		tick_count_handle_error(tick_count_error_tick_count_cannot_be_retrieved, errno, 0, 0, __FILE__, line_number);
	}
	
	if (should_continue) {
		error_code = clock_getres(CLOCK_SOURCE, &res);
		line_number = PREVIOUS_LINE;
		if (error_code != 0) {
			should_continue = false;
			tick_count_handle_error(tick_count_error_resolution_cannot_be_retrieved, errno, 0, 0, __FILE__, line_number);
		}
	}

	if (should_continue) {
		if (not overflow_checks_enabled) {
			resolution = (int64_t) res.tv_sec * second_to_nanosecond + res.tv_nsec;
			line_number = PREVIOUS_LINE;
		} else {
			int64_t operand_1 = (int64_t) res.tv_sec;
			int64_t operand_2 = second_to_nanosecond;
			i64_result_type result = safer_i64_multiply(operand_1, operand_2);
			line_number = PREVIOUS_LINE;
			if (result.error == integer_operation_error_none) {
				operand_1 = result.value;
				operand_2 = (int64_t) res.tv_nsec;
				result = safer_i64_add(operand_1, operand_2);
				line_number = PREVIOUS_LINE;
				if (result.error != integer_operation_error_none) {
					tick_count_handle_error(tick_count_error_integer_addition_overflow_occurred, 0, operand_1, operand_2, __FILE__, line_number);
				}
			} else {
				tick_count_handle_error(tick_count_error_integer_multiplication_overflow_occurred, 0, operand_1, operand_2, __FILE__, line_number);
			}
			resolution = result.value;
			line_number = PREVIOUS_LINE;
		}

		if (resolution <= 0 or resolution > second_to_nanosecond) {
			should_continue = false;
			tick_count_handle_error(tick_count_error_resolution_is_invalid, 0, resolution, 0, __FILE__, line_number);
		}
	}

	if (should_continue) {
		if (not overflow_checks_enabled) {
			tick_count = ((int64_t) ts.tv_sec * second_to_nanosecond + ts.tv_nsec) / resolution;
			line_number = PREVIOUS_LINE;
		} else {
			int64_t operand_1 = (int64_t) ts.tv_sec;
			int64_t operand_2 = second_to_nanosecond;
			i64_result_type result = safer_i64_multiply(operand_1, operand_2);
			line_number = PREVIOUS_LINE;
			if (result.error == integer_operation_error_none) {
				operand_1 = result.value;
				operand_2 = (int64_t) ts.tv_nsec;
				result = safer_i64_add(operand_1, operand_2);
				line_number = PREVIOUS_LINE;
				if (result.error != integer_operation_error_none) {
					tick_count_handle_error(tick_count_error_integer_addition_overflow_occurred, 0, operand_1, operand_2, __FILE__, line_number);
				}
			} else {
				tick_count_handle_error(tick_count_error_integer_multiplication_overflow_occurred, 0, operand_1, operand_2, __FILE__, line_number);
			}
			tick_count = result.value / resolution;
		}
	}
#else
	LARGE_INTEGER large_integer = {0};
	BOOL success = QueryPerformanceCounter(&large_integer);
	line_number = PREVIOUS_LINE;
	if (not success) {
		large_integer.QuadPart = 0;
		tick_count_handle_error(tick_count_error_tick_count_cannot_be_retrieved, (int64_t) GetLastError(), 0, 0, __FILE__, line_number);
	}
	tick_count = (int64_t) large_integer.QuadPart;
#endif

	return tick_count;
}

int64_t tick_count_per_second(void)
{
	int64_t ticks_per_second = 0;
	int line_number = 0;

#if not TICK_COUNT_WINDOWS_BUILD
	int64_t error_code = 0, resolution = 0;
	const int64_t second_to_nanosecond = 1000000000L;
	struct timespec res = {0};
	bool should_continue = true;
	const bool overflow_checks_enabled = tick_count_overflow_checks_enabled;

	error_code = clock_getres(CLOCK_SOURCE, &res);
	line_number = PREVIOUS_LINE;
	if (error_code != 0) {
		should_continue = false;
		tick_count_handle_error(tick_count_error_resolution_cannot_be_retrieved, errno, 0, 0, __FILE__, line_number);
	}

	if (should_continue) {
		if (not overflow_checks_enabled) {
			resolution = (int64_t) res.tv_sec * second_to_nanosecond + res.tv_nsec;
		} else {
			int64_t operand_1 = (int64_t) res.tv_sec;
			int64_t operand_2 = second_to_nanosecond;
			i64_result_type result = safer_i64_multiply(operand_1, operand_2);
			line_number = PREVIOUS_LINE;
			if (result.error == integer_operation_error_none) {
				operand_1 = result.value;
				operand_2 = (int64_t) res.tv_nsec;
				result = safer_i64_add(operand_1, operand_2);
				line_number = PREVIOUS_LINE;
				if (result.error != integer_operation_error_none) {
					tick_count_handle_error(tick_count_error_integer_addition_overflow_occurred, 0, operand_1, operand_2, __FILE__, line_number);
				}
			} else {
				tick_count_handle_error(tick_count_error_integer_multiplication_overflow_occurred, 0, operand_1, operand_2, __FILE__, line_number);
			}
			resolution = result.value;
			line_number = PREVIOUS_LINE;
		}

		if (resolution <= 0 or resolution > second_to_nanosecond) {
			tick_count_handle_error(tick_count_error_resolution_is_invalid, 0, resolution, 0, __FILE__, line_number);
		}
	}

	ticks_per_second = (resolution > 0 and resolution < second_to_nanosecond) ? (second_to_nanosecond / resolution) : 1;
#else
	LARGE_INTEGER large_integer = {0};
	BOOL success = QueryPerformanceFrequency(&large_integer);
	line_number = PREVIOUS_LINE;
	if (not success) {
		large_integer.QuadPart = 1;
		tick_count_handle_error(tick_count_error_resolution_cannot_be_retrieved, (int64_t) GetLastError(), 0, 0, __FILE__, line_number);
	} else if (large_integer.QuadPart <= 0) {
		const int64_t frequency = (int64_t) large_integer.QuadPart;
		large_integer.QuadPart = 1;
		tick_count_handle_error(tick_count_error_frequency_is_invalid, 0, frequency, 0, __FILE__, line_number);
	}
	ticks_per_second = (int64_t) large_integer.QuadPart;
#endif

	assert(ticks_per_second > 0);
	return ticks_per_second;
}

int64_t tick_count_difference_in_microseconds(int64_t start_count, int64_t end_count, int64_t ticks_per_second)
{
	const int64_t second_to_microsecond = 1000000L;
	int64_t difference = 0, whole_seconds = 0, remaining_ticks = 0, time_difference = 0;
	const bool overflow_checks_enabled = tick_count_overflow_checks_enabled;

	int line_number = NEXT_LINE;
	if (ticks_per_second > 0) {
		if (not overflow_checks_enabled) {
			difference = end_count - start_count;
		} else {
			i64_result_type result = safer_i64_minus(end_count, start_count);
			line_number = PREVIOUS_LINE;
			if (result.error != integer_operation_error_none) {
				tick_count_handle_error(tick_count_error_integer_subtraction_overflow_occurred, 0, end_count, start_count, __FILE__, line_number);
			}
			difference = result.value;
		}

		whole_seconds = difference / ticks_per_second;
		remaining_ticks = difference % ticks_per_second;

		if (not overflow_checks_enabled) {
			time_difference = whole_seconds * second_to_microsecond + (remaining_ticks * second_to_microsecond) / ticks_per_second;
		} else {
			i64_result_type result = safer_i64_multiply(whole_seconds, second_to_microsecond);
			line_number = PREVIOUS_LINE;
			if (result.error == integer_operation_error_none) {
				const int64_t first_part = result.value;
				line_number = NEXT_LINE;
				result = safer_i64_multiply(remaining_ticks, second_to_microsecond);
				if (result.error == integer_operation_error_none) {
					const int64_t second_part = result.value / ticks_per_second;
					line_number = NEXT_LINE;
					result = safer_i64_add(first_part, second_part);
					if (result.error != integer_operation_error_none) {
						tick_count_handle_error(tick_count_error_integer_addition_overflow_occurred, 0, first_part, second_part, __FILE__, line_number);
					}
				} else {
					tick_count_handle_error(tick_count_error_integer_multiplication_overflow_occurred, 0, remaining_ticks, second_to_microsecond, __FILE__, line_number);
				}
			} else {
				tick_count_handle_error(tick_count_error_integer_multiplication_overflow_occurred, 0, whole_seconds, second_to_microsecond, __FILE__, line_number);
			}
			time_difference = result.value;
		}
	} else {
		tick_count_handle_error(tick_count_error_frequency_is_invalid, 0, ticks_per_second, 0, __FILE__, line_number);
	}
	return time_difference;
}

int64_t tick_count_difference_in_milliseconds(int64_t start_count, int64_t end_count, int64_t ticks_per_second)
{
	const int64_t second_to_millisecond = 1000;
	int64_t difference = 0, whole_seconds = 0, remaining_ticks = 0, time_difference = 0;
	const bool overflow_checks_enabled = tick_count_overflow_checks_enabled;

	int line_number = NEXT_LINE;
	if (ticks_per_second > 0) {
		if (not overflow_checks_enabled) {
			difference = end_count - start_count;
		} else {
			i64_result_type result = safer_i64_minus(end_count, start_count);
			line_number = PREVIOUS_LINE;
			if (result.error != integer_operation_error_none) {
				tick_count_handle_error(tick_count_error_integer_subtraction_overflow_occurred, 0, end_count, start_count, __FILE__, line_number);
			}
			difference = result.value;
		}

		whole_seconds = difference / ticks_per_second;
		remaining_ticks = difference % ticks_per_second;

		if (not overflow_checks_enabled) {
			time_difference = whole_seconds * second_to_millisecond + (remaining_ticks * second_to_millisecond) / ticks_per_second;
		} else {
			i64_result_type result = safer_i64_multiply(whole_seconds, second_to_millisecond);
			line_number = PREVIOUS_LINE;
			if (result.error == integer_operation_error_none) {
				const int64_t first_part = result.value;
				line_number = NEXT_LINE;
				result = safer_i64_multiply(remaining_ticks, second_to_millisecond);
				if (result.error == integer_operation_error_none) {
					const int64_t second_part = result.value / ticks_per_second;
					line_number = NEXT_LINE;
					result = safer_i64_add(first_part, second_part);
					if (result.error != integer_operation_error_none) {
						tick_count_handle_error(tick_count_error_integer_addition_overflow_occurred, 0, first_part, second_part, __FILE__, line_number);
					}
				} else {
					tick_count_handle_error(tick_count_error_integer_multiplication_overflow_occurred, 0, remaining_ticks, second_to_millisecond, __FILE__, line_number);
				}
			} else {
				tick_count_handle_error(tick_count_error_integer_multiplication_overflow_occurred, 0, whole_seconds, second_to_millisecond, __FILE__, line_number);
			}
			time_difference = result.value;
		}
	} else {
		tick_count_handle_error(tick_count_error_frequency_is_invalid, 0, ticks_per_second, 0, __FILE__, line_number);
	}
	return time_difference;
}

int64_t tick_count_difference_in_seconds(int64_t start_count, int64_t end_count, int64_t ticks_per_second)
{
	int64_t difference = 0, time_difference = 0;
	const bool overflow_checks_enabled = tick_count_overflow_checks_enabled;
	int line_number = NEXT_LINE;
	if (ticks_per_second > 0) {
		if (not overflow_checks_enabled) {
			difference = end_count - start_count;
		} else {
			i64_result_type result = safer_i64_minus(end_count, start_count);
			line_number = PREVIOUS_LINE;
			if (result.error != integer_operation_error_none) {
				tick_count_handle_error(tick_count_error_integer_subtraction_overflow_occurred, 0, end_count, start_count, __FILE__, line_number);
			}
			difference = result.value;
		}
		time_difference = difference / ticks_per_second;
	} else {
		tick_count_handle_error(tick_count_error_frequency_is_invalid, 0, ticks_per_second, 0, __FILE__, line_number);
	}
	return time_difference;
}

tick_count_error_handler_type tick_count_set_error_handler(tick_count_error_handler_type error_handler)
{
	tick_count_error_handler_type previous_handler = tick_count_error_handler;
	tick_count_error_handler = error_handler;
	return previous_handler;
}

void tick_count_enable_integer_overflow_checks(void)
{
	tick_count_overflow_checks_enabled = true;
}

void tick_count_disable_integer_overflow_checks(void)
{
	tick_count_overflow_checks_enabled = false;
}
