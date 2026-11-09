#include "tick_count.h"
#include "inline_or_static.h"

#include <assert.h>
#include <stdio.h>

static void error_handler(
	tick_count_error_type error,
	int64_t internal_error,
	int64_t info_1,
	int64_t info_2,
	const char *source_file,
	int line
) {
	assert(source_file != NULL);
	printf("Source file: %s (line %d)\n", source_file, line);
	printf("Error code: %d\n", (int) error);
	printf("Internal error code: %lld\n", (long long) internal_error);
	switch (error) {
	case tick_count_error_none:
		printf("No error.\n");
		break;
	case tick_count_error_tick_count_cannot_be_retrieved:
		printf("Tick count cannot be obtained.\n");
		break;
	case tick_count_error_resolution_cannot_be_retrieved:
		printf("Clock or counter resolution cannot be obtained.\n");
		break;
	case tick_count_error_resolution_is_invalid:
		printf("Clock or counter resolution (%lld) is invalid.\n", (long long) info_1);
		break;
	case tick_count_error_frequency_is_invalid:
		printf("Clock or counter frequency (%lld) is invalid.\n", (long long) info_1);
		break;
	case tick_count_error_integer_addition_overflow_occurred:
		printf("Integer addition overflow: %lld + %lld\n", (long long) info_1, (long long) info_2);
		break;
	case tick_count_error_integer_subtraction_overflow_occurred:
		printf("Integer subtraction overflow: %lld - %lld\n", (long long) info_1, (long long) info_2);
		break;
	case tick_count_error_integer_multiplication_overflow_occurred:
		printf("Integer multiplication overflow: %lld * %lld\n", (long long) info_1, (long long) info_2);
		break;
	default:
		break;
	}
}

INLINE_OR_STATIC void test_code(void)
{
	volatile long i = 0;
	for (i = 0; i < 1000000000L; ++i);
	printf("Final value: %ld\n", i);
}

INLINE_OR_STATIC void run_test(void)
{
	int64_t start = 0, end = 0;
	const int64_t ticks_per_sec = tick_count_per_second();

	start = tick_count_now();
	test_code();
	end = tick_count_now();

	printf("ticks per second = %lld\n", (long long) ticks_per_sec);
	printf("start tick = %lld\n", (long long) start);
	printf("end tick = %lld\n", (long long) end);
	printf("duration (seconds) = %lld\n", (long long) tick_count_difference_in_seconds(start, end, ticks_per_sec));
	printf("duration (milliseconds) = %lld\n", (long long) tick_count_difference_in_milliseconds(start, end, ticks_per_sec));
	printf("duration (microseconds) = %lld\n", (long long) tick_count_difference_in_microseconds(start, end, ticks_per_sec));
}

int main(void)
{
	tick_count_set_error_handler(error_handler);
	tick_count_disable_integer_overflow_checks();
	printf("Test without integer overflow checks\n");
	run_test();
	printf("-----\n");
	tick_count_enable_integer_overflow_checks();
	printf("Test with integer overflow checks\n");
	run_test();
	return 0;
}
