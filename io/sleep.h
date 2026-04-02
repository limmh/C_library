#ifndef IO_SLEEP_H
#define IO_SLEEP_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Suspends execution of the calling thread for at least the specified number of seconds.
 * The actual sleep duration may be longer than requested due to system scheduling.
 *
 * On Windows, asserts that time_in_seconds does not exceed UINT_MAX / 1000
 * (the maximum value that can be converted to milliseconds without overflow).
 */
void sleep_sec(unsigned int time_in_seconds);

/*
 * Suspends execution of the calling thread for at least the specified number of milliseconds.
 * The actual sleep duration may be longer than requested due to system scheduling.
 */
void sleep_ms(unsigned int time_in_milliseconds);

#ifdef __cplusplus
}
#endif

#endif
