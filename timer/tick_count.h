#ifndef SAFER_C_LIBRARY_TICK_COUNT_H
#define SAFER_C_LIBRARY_TICK_COUNT_H

#include "fixed_width_integer_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief tick count errors */
typedef enum tick_count_error_type {
	tick_count_error_none = 0,
	tick_count_error_tick_count_cannot_be_retrieved,
	tick_count_error_resolution_cannot_be_retrieved,
	tick_count_error_resolution_is_invalid,
	tick_count_error_frequency_is_invalid,
	tick_count_error_integer_addition_overflow_occurred,
	tick_count_error_integer_subtraction_overflow_occurred,
	tick_count_error_integer_multiplication_overflow_occurred
} tick_count_error_type;

/** @brief tick count error handler */
typedef void (*tick_count_error_handler_type)(
	tick_count_error_type /* tick count error */,
	int64_t /* internal error (OS-specific) */,
	int64_t /* info 1 */,
	int64_t /* info 2 */,
	const char* /* name of the tick count source file */,
	int /* line in source_file where the error occurred */
);

/**
 * @brief Returns the current tick count.
 * The tick count is OS specific and should not be used as time in applications directly.
 * The difference between two tick count values can be used to determine the elapsed time.
 * @return int64_t
 */
int64_t tick_count_now(void);

/**
 * @brief Returns the tick count per second, i.e. frequency.
 * The value is also OS specific.
 * @return int64_t
 */
int64_t tick_count_per_second(void);

/**
 * @brief Returns the time difference between two tick count values in microseconds
 * @param [in] start_count The starting tick count
 * @param [in] end_count The final tick count
 * @param [in] ticks_per_second The number of ticks per second (frequency)
 * @return int64_t
 */
int64_t tick_count_difference_in_microseconds(int64_t start_count, int64_t end_count, int64_t ticks_per_second);

/**
 * @brief Returns the time difference between two tick count values in milliseconds
 * @param [in] start_count The starting tick count
 * @param [in] end_count The final tick count
 * @param [in] ticks_per_second The number of ticks per second (frequency)
 * @return int64_t
 */
int64_t tick_count_difference_in_milliseconds(int64_t start_count, int64_t end_count, int64_t ticks_per_second);

/**
 * @brief Returns the time difference between two tick count values in seconds
 * @param [in] start_count The starting tick count
 * @param [in] end_count The final tick count
 * @param [in] ticks_per_second The number of ticks per second (frequency)
 * @return int64_t
 */
int64_t tick_count_difference_in_seconds(int64_t start_count, int64_t end_count, int64_t ticks_per_second);

/**
 * @brief Sets the error handler and returns the previous error_handler
 * If error_handler is NULL, no error handler will be invoked when there is an error.
 * @param [in] error_handler The new error handler
 * @return tick_count_error_handler_type
 *
 * Errors and debug info:
 * 1. tick_count_error_none: no debug info
 * 2. tick_count_error_tick_count_cannot_be_retrieved: info_1 == 0, info_2 == 0
 * 3. tick_count_error_resolution_cannot_be_retrieved: info_1 == 0, info_2 == 0
 * 4. tick_count_error_resolution_is_invalid: info_1 == resolution, info_2 == 0
 * 5. tick_count_error_frequency_is_invalid: info_1 == frequency, info_2 == 0
 * 6. tick_count_error_integer_addition_overflow_occurred: info_1 == operand_1, info_2 == operand 2
 * 7. tick_count_error_integer_subtraction_overflow_occurred: info_1 == operand 1, info_2 == operand 2
 * 8. tick_count_error_integer_multiplication_overflow_occurred: info_1 == operand 1, info_2 == operand 2
 */
tick_count_error_handler_type tick_count_set_error_handler(tick_count_error_handler_type error_handler);

/**
 *@brief Enables integer overflow checks
 */
void tick_count_enable_integer_overflow_checks(void);

/**
 * @brief Disables integer overflow checks
 */
void tick_count_disable_integer_overflow_checks(void);

#ifdef __cplusplus
}
#endif

#endif
