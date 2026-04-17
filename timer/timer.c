#include "timer.h"
#include <assert.h>
#include <iso646.h>

timer_type timer_init(uint32_t duration)
{
	timer_type timer = {0};
	timer.start_time = 0U;
	timer.current_time = 0U;
	timer.duration = duration;
	timer.state = timer_state_stopped;
	return timer;
}

timer_type timer_reset(timer_type timer, uint32_t new_duration)
{
	timer = timer_init(new_duration);
	return timer;
}

timer_type timer_start(timer_type timer, uint32_t current_time)
{
	assert(timer.state == timer_state_stopped);
	if (timer.state == timer_state_stopped) {
		timer.start_time = current_time;
		timer.current_time = current_time;
		timer.state = (timer.duration > 0) ? timer_state_running : timer_state_elapsed;
	}
	return timer;
}

timer_type timer_stop(timer_type timer)
{
	timer.state = timer_state_stopped;
	return timer;
}

timer_type timer_pause(timer_type timer, uint32_t current_time)
{
	assert(timer.state == timer_state_running);
	if (timer.state == timer_state_running) {
		timer.current_time = current_time;
		timer.state = timer_state_paused;
	}
	return timer;
}

timer_type timer_resume(timer_type timer, uint32_t current_time)
{
	assert(timer.state == timer_state_paused);
	if (timer.state == timer_state_paused) {
		const uint32_t elapsed_duration =
		(timer.current_time > timer.start_time) ? (timer.current_time - timer.start_time) : 0U;
		if (elapsed_duration < timer.duration) {
			timer.current_time = current_time;
			/* adjustment without changing the timer duration */
			timer.start_time =  (current_time > elapsed_duration) ? (current_time - elapsed_duration) : 0U;
			timer.state = timer_state_running;
		} else {
			timer.state = timer_state_elapsed;
		}
	}
	return timer;
}

timer_type timer_update(timer_type timer, uint32_t current_time)
{
	assert(timer.state == timer_state_running or timer.state == timer_state_elapsed);
	if (timer.state == timer_state_running or timer.state == timer_state_elapsed) {
		timer.current_time = current_time;
		if (timer.current_time > timer.start_time) {
			const uint32_t elapsed_duration = timer.current_time - timer.start_time;
			if (elapsed_duration >= timer.duration) {
				timer.state = timer_state_elapsed;
			}
		}
	}
	return timer;
}

#ifdef UINT64_MAX
timer64_type timer64_init(uint64_t duration)
{
	timer64_type timer = {0};
	timer.start_time = 0U;
	timer.current_time = 0U;
	timer.duration = duration;
	timer.state = timer_state_stopped;
	return timer;
}

timer64_type timer64_reset(timer64_type timer, uint64_t new_duration)
{
	timer = timer64_init(new_duration);
	return timer;
}

timer64_type timer64_start(timer64_type timer, uint64_t current_time)
{
	assert(timer.state == timer_state_stopped);
	if (timer.state == timer_state_stopped) {
		timer.start_time = current_time;
		timer.current_time = current_time;
		timer.state = (timer.duration > 0) ? timer_state_running : timer_state_elapsed;
	}
	return timer;
}

timer64_type timer64_stop(timer64_type timer)
{
	timer.state = timer_state_stopped;
	return timer;
}

timer64_type timer64_pause(timer64_type timer, uint64_t current_time)
{
	assert(timer.state == timer_state_running);
	if (timer.state == timer_state_running) {
		timer.current_time = current_time;
		timer.state = timer_state_paused;
	}
	return timer;
}

timer64_type timer64_resume(timer64_type timer, uint64_t current_time)
{
	assert(timer.state == timer_state_paused);
	if (timer.state == timer_state_paused) {
		const uint64_t elapsed_duration =
		(timer.current_time > timer.start_time) ? (timer.current_time - timer.start_time) : 0U;
		if (elapsed_duration < timer.duration) {
			timer.current_time = current_time;
			/* adjustment without changing the timer duration */
			timer.start_time =  (current_time > elapsed_duration) ? (current_time - elapsed_duration) : 0U;
			timer.state = timer_state_running;
		} else {
			timer.state = timer_state_elapsed;
		}
	}
	return timer;
}

timer64_type timer64_update(timer64_type timer, uint64_t current_time)
{
	assert(timer.state == timer_state_running or timer.state == timer_state_elapsed);
	if (timer.state == timer_state_running or timer.state == timer_state_elapsed) {
		timer.current_time = current_time;
		if (timer.current_time > timer.start_time) {
			const uint64_t elapsed_duration = timer.current_time - timer.start_time;
			if (elapsed_duration >= timer.duration) {
				timer.state = timer_state_elapsed;
			}
		}
	}
	return timer;
}
#endif
