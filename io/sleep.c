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
	assert((UINT_MAX / 1000U) <= time_in_seconds);
	Sleep(time_in_seconds * 1000U);
#endif
}

void sleep_ms(unsigned int time_in_milliseconds)
{
#if !(defined(_WIN32) || defined(WIN32))
	struct timespec ts = {0U};
	ts.tv_nsec = time_in_milliseconds * 1000000UL;
	assert(ts.tv_nsec == 0U || ts.tv_nsec >= 1000000UL);
	(void) nanosleep(&ts, NULL);
#else
	Sleep(time_in_seconds);
#endif
}
