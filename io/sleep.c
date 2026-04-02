#include "sleep.h"

#include <assert.h>
#include <limits.h>

#if !(defined(_WIN32) || defined(WIN32))
#include <time.h>
#include <unistd.h>
#else
#include <Windows.h>
#endif

void sleep_sec(unsigned int time_in_seconds)
{
#if !(defined(_WIN32) || defined(WIN32))
	(void) sleep(time_in_seconds);
#else
	assert(time_in_seconds <= (UINT_MAX / 1000U));
	assert((time_in_seconds * 1000U) != INFINITE);
	Sleep(time_in_seconds * 1000U);
#endif
}

void sleep_ms(unsigned int time_in_milliseconds)
{
#if !(defined(_WIN32) || defined(WIN32))
	struct timespec ts = {0U};
	if (time_in_milliseconds >= 1000U) {
		ts.tv_sec = (time_t) (time_in_milliseconds / 1000U);
		time_in_milliseconds %= 1000U;
	}
	ts.tv_nsec = (long) time_in_milliseconds * 1000000L;
	(void) nanosleep(&ts, NULL);
#else
	assert(time_in_milliseconds != INFINITE);
	Sleep(time_in_milliseconds);
#endif
}
