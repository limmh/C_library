#ifndef TIMER_H
#define TIMER_H

#include "Boolean_type.h"
#include "fixed_width_integer_types.h"
#include "inline_or_static.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum timer_state_type
{
	timer_state_stopped = 0,
	timer_state_running = 1,
	timer_state_paused = 2,
	timer_state_elapsed = 3
} timer_state_type;

/**
 * timer_type: Timer data structure containing time, duration and state information
 * start_time: Starting time (any time unit)
 * current_time: Current time set by timer functions (any time unit, shall be the same as that of start_time)
 * duration: Timer duration (any time unit, shall be the same as that of start_time)
 * state: Timer state (updated by timer functions)
 */
typedef struct timer_type
{
	uint32_t start_time;
	uint32_t current_time;
	uint32_t duration;
	timer_state_type state;
} timer_type;

/**
 * Initialize a timer with specified duration.
 * 
 * The timer begins in stopped state. Call timer_start() to begin timing.
 * 
 * @param duration The duration in time units (milliseconds, ticks, etc.)
 *                 Interpretation depends on caller's time source
 * @return Initialized timer in stopped state
 * 
 * Preconditions: None
 * Postconditions: timer_is_stopped(result) == true
 * 
 * Example:
 *   timer_type t = timer_init(1000);  // 1000 unit timer
 *   t = timer_start(t, get_current_time());
 */
timer_type timer_init(uint32_t duration);

/**
 * Reset a timer.
 * 
 * The timer is reset to stopped state and will have a new duration.
 * Call timer_start() to begin timing again.
 * 
 * @param timer Timer in any state
 * @param new_duration The new duration in time units
 * @return Initialized timer in stopped state
 * 
 * Preconditions: None
 * Postconditions: timer_is_stopped(result) == true
 * 
 * Example:
 *   timer_type t = timer_init(1000);  // 1000 unit timer
 *   // some code
 *   t = timer_reset(t, 500); // 500 unit timer
 */
timer_type timer_reset(timer_type timer, uint32_t new_duration);

/**
 * Start a timer.
 * 
 * Records the current time as the start point. Timer begins counting
 * toward elapsed duration. Call timer_update() periodically with current
 * time to check if duration has elapsed.
 * 
 * @param timer Timer in stopped state
 * @param current_time Current time from chosen time source
 * @return Timer in running state (or unchanged if precondition not met)
 * 
 * Preconditions: timer_is_stopped(timer) == true
 * Postconditions: timer_is_running(result) == true (if precondition met)
 * 
 * Notes:
 * - Time parameter should come from a consistent clock
 * - Do not mix time sources (milliseconds + microseconds)
 */
timer_type timer_start(timer_type timer, uint32_t current_time);

/**
 * Stop a timer.
 * 
 * @param timer Timer in any state
 * @return Timer in stopped state
 * 
 * Preconditions: None
 * Postconditions: timer_is_stopped(result) == true
 */
timer_type timer_stop(timer_type timer);

/**
 * Pause a running timer.
 * 
 * Transitions timer from running to paused state. The elapsed time is
 * recorded. Call timer_resume() to continue timing from where it paused.
 * 
 * @param timer Timer in running state
 * @param current_time Current time from chosen time source
 * @return Timer in paused state (or unchanged if precondition not met)
 * 
 * Preconditions: timer_is_running(timer) == true
 * Postconditions: timer_is_paused(result) == true (if precondition met)
 * 
 * Notes:
 * - Elapsed time is preserved
 * - Can pause multiple times, resuming at different times
 * - Handles time gaps correctly (see timer_resume())
 */
timer_type timer_pause(timer_type timer, uint32_t current_time);

/**
 * Resume a paused timer.
 * 
 * Continues timing from where it paused. Correctly handles cases where
 * resume happens long after pause (time gaps). Remaining time is preserved.
 * 
 * @param timer Timer in paused state
 * @param current_time Current time from chosen time source
 * @return Timer in running or elapsed state (or unchanged if precondition not met)
 * 
 * Preconditions: timer_is_paused(timer) == true
 * Postconditions: timer_is_running(result) || timer_is_elapsed(result)
 *                 (if precondition met)
 * 
 * Notes:
 * - If time has already elapsed while paused, transitions to elapsed
 * - Correctly handles large time gaps
 * - Does not change total duration
 * - Example: 1000ms timer, paused at 400ms elapsed, resumed 5 seconds later
 *           still has 600ms remaining (not 5600ms!), not elapsed yet
 */
timer_type timer_resume(timer_type timer, uint32_t current_time);

/**
 * Update a timer and check for elapsed condition.
 * 
 * Call this function periodically with current time. If elapsed duration
 * reaches the specified duration, timer transitions to elapsed state.
 * 
 * @param timer Timer in running or elapsed state
 * @param current_time Current time from chosen time source
 * @return Timer with updated state
 * 
 * Preconditions: timer_is_running(timer) || timer_is_elapsed(timer)
 * 
 * Notes:
 * - Call periodically (e.g., once per game frame)
 * - Ensure current_time is monotonically increasing
 * - If current_time goes backward, behavior may be incorrect
 * - Once elapsed, timer remains in elapsed state until reset/stopped
 * 
 * Example:
 *   while (running) {
 *       uint32_t now = get_time();
 *       timer = timer_update(timer, now);
 *       if (timer_has_elapsed(timer)) {
 *           handle_timeout();
 *       }
 *   }
 */
timer_type timer_update(timer_type timer, uint32_t current_time);

/***
 * Determine the elapsed duration of a timer
 * 
 * @param timer Timer in any state
 * @return uint32_t Duration which has elapsed (can be greater than the timer duration)
 */
INLINE_OR_STATIC
uint32_t timer_elapsed_duration(timer_type timer)
{
	return (timer.current_time > timer.start_time) ? (timer.current_time - timer.start_time) : 0U;
}

/***
 * Determine the remaining duration of a timer
 * 
 * @param timer Timer in any state
 * @return uint32_t Remaining duration (0 if elapsed duration is greater than or equal to the timer duration)
 */
INLINE_OR_STATIC
uint32_t timer_remaining_duration(timer_type timer)
{
	const uint32_t elapsed_duration = timer_elapsed_duration(timer);
	return (timer.duration > elapsed_duration) ? (timer.duration - elapsed_duration) : 0U;
}

/**
 * Check whether the duration of a timer has elapsed.
 * 
 * @param timer Timer in any state
 * @return bool true if the timer duration has elapsed, false otherwise
 */
INLINE_OR_STATIC
bool timer_has_elapsed(timer_type timer)
{
	return (timer.state == timer_state_elapsed);
}

/**
 * Check whether a timer is still running.
 * 
 * @param timer Timer in any state
 * @return bool true if the timer is still running, false otherwise
 */
INLINE_OR_STATIC
bool timer_is_running(timer_type timer)
{
	return (timer.state == timer_state_running);
}

/**
 * Check whether a timer is paused.
 * 
 * @param timer Timer in any state
 * @return bool true if the timer is paused, false otherwise
 */
INLINE_OR_STATIC
bool timer_is_paused(timer_type timer)
{
	return (timer.state == timer_state_paused);
}

/**
 * Check whether a timer is stopped.
 * 
 * @param timer Timer in any state
 * @return bool true if the timer is stopped, false otherwise
 */
INLINE_OR_STATIC
bool timer_is_stopped(timer_type timer)
{
	return (timer.state == timer_state_stopped);
}

/* 64-bit timer */
#ifdef UINT64_MAX
typedef struct timer64_type
{
	uint64_t start_time;
	uint64_t current_time;
	uint64_t duration;
	timer_state_type state;
} timer64_type;

/**
 * Initialize a 64-bit timer.
 * Refer to timer_init for more details.
 */
timer64_type timer64_init(uint64_t duration);

/**
 * Reset a 64-bit timer.
 * Refer to timer_reset for more details.
 */
timer64_type timer64_reset(timer64_type timer, uint64_t new_duration);

/**
 * Start a 64-bit timer.
 * Refer to timer_start for more details.
 */
timer64_type timer64_start(timer64_type timer, uint64_t current_time);

/**
 * Stop a 64-bit timer.
 * Refer to timer_stop for more details.
 */
timer64_type timer64_stop(timer64_type timer);

/**
 * Pause a 64-bit timer.
 * Refer to timer_pause for more details.
 */
timer64_type timer64_pause(timer64_type timer, uint64_t current_time);

/**
 * Resume a 64-bit timer.
 * Refer to timer_resume for more details.
 */
timer64_type timer64_resume(timer64_type timer, uint64_t current_time);

/**
 * Update a 64-bit timer.
 * Refer to timer_update for more details.
 */
timer64_type timer64_update(timer64_type timer, uint64_t current_time);

/***
 * Determine the elapsed duration of a 64-bit timer
 * 
 * @param timer Timer in any state
 * @return uint64_t Duration which has elapsed (can be greater than the timer duration)
 */
INLINE_OR_STATIC
uint64_t timer64_elapsed_duration(timer64_type timer)
{
	return (timer.current_time > timer.start_time) ? (timer.current_time - timer.start_time) : 0U;
}

/***
 * Determine the remaining duration of a 64-bit timer
 * 
 * @param timer Timer in any state
 * @return uint64_t Remaining duration (0 if elapsed duration is greater than or equal to the timer duration)
 */
INLINE_OR_STATIC
uint64_t timer64_remaining_duration(timer64_type timer)
{
	const uint64_t elapsed_duration = timer64_elapsed_duration(timer);
	return (timer.duration > elapsed_duration) ? (timer.duration - elapsed_duration) : 0U;
}

/**
 * Check whether the duration of a 64-bit timer has elapsed.
 * Refer to timer_has_elapsed for more details.
 */
INLINE_OR_STATIC
bool timer64_has_elapsed(timer64_type timer)
{
	return (timer.state == timer_state_elapsed);
}

/**
 * Check whether a 64-bit timer is still running.
 * Refer to timer_is_running for more details.
 */
INLINE_OR_STATIC
bool timer64_is_running(timer64_type timer)
{
	return (timer.state == timer_state_running);
}

/**
 * Check whether a timer is paused.
 * Refer to timer_is_paused for more details.
 */
INLINE_OR_STATIC
bool timer64_is_paused(timer64_type timer)
{
	return (timer.state == timer_state_paused);
}

/**
 * Check whether a timer is stopped.
 * Refer to timer_is_stopped for more details.
 */
INLINE_OR_STATIC
bool timer64_is_stopped(timer64_type timer)
{
	return (timer.state == timer_state_stopped);
}
#endif

#ifdef __cplusplus
}
#endif

#endif
