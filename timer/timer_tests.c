#include "timer.h"
#include "unit_testing.h"
#include <iso646.h>

TEST(timer_basic_timing, "Timer starts, runs, elapses")
{
	timer_type timer = timer_init(100);
	ASSERT(timer_is_stopped(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 0U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 100U);

	timer = timer_start(timer, 100);
	ASSERT(timer_is_running(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 0U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 100U);

	timer = timer_update(timer, 150);
	ASSERT(timer_is_running(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 50U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 50U);

	timer = timer_update(timer, 200);
	ASSERT(timer_has_elapsed(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 100U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 0U);

	timer = timer_update(timer, 250);
	ASSERT(timer_has_elapsed(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 150U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 0U);

	timer = timer_reset(timer, 500);
	ASSERT(timer_is_stopped(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 0U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 500U);
}

TEST(timer_pause_and_resume, "Pause/resume preserves remaining time")
{
	timer_type timer = timer_init(1000);
	ASSERT(timer_is_stopped(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 0U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 1000U);

	timer = timer_start(timer, 0);
	ASSERT(timer_is_running(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 0U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 1000U);

	timer = timer_pause(timer, 400);
	ASSERT(timer_is_paused(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 400U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 600U);

	timer = timer_resume(timer, 5000);
	ASSERT(timer_is_running(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 400U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 600U);

	timer = timer_update(timer, 5600);
	ASSERT(timer_has_elapsed(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 1000U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 0U);
}

TEST(timer_multiple_pause_and_resume_cycles, "Multiple pause/resume cycles work")
{
	timer_type timer = timer_init(1000);
	ASSERT(timer_is_stopped(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 0U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 1000U);

	timer = timer_start(timer, 0);
	ASSERT(timer_is_running(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 0U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 1000U);

	/* First pause at 250ms */
	timer = timer_pause(timer, 250);
	ASSERT(timer_is_paused(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 250U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 750U);

	/* Resume at 500ms (gap of 250ms), elapsed duration is 250ms */
	timer = timer_resume(timer, 500);
	ASSERT(timer_is_running(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 250U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 750U);

	/* Second pause at 750ms */
	timer = timer_pause(timer, 750);
	ASSERT(timer_is_paused(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 500U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 500U);

	/* Resume at 10000ms, elapsed duration is 500ms */
	timer = timer_resume(timer, 10000);
	ASSERT(timer_is_running(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 500U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 500U);

	timer = timer_update(timer, 10500);
	ASSERT(timer_has_elapsed(timer));
	ASSERT_UINT32_EQUAL(timer_elapsed_duration(timer), 1000U);
	ASSERT_UINT32_EQUAL(timer_remaining_duration(timer), 0U);
}

TEST(timer_edge_zero_duration, "Zero duration timer elapses immediately")
{
	timer_type timer = timer_init(0);
	timer = timer_start(timer, 100);
	ASSERT(timer_has_elapsed(timer));
	timer = timer_update(timer, 101);
	ASSERT(timer_has_elapsed(timer));
}

TEST(timer_edge_same_time, "Updating with same time does not change state")
{
	timer_type timer = timer_init(1000);
	timer = timer_start(timer, 100);
	ASSERT(timer_is_running(timer));
	timer = timer_update(timer, 100);
	ASSERT(timer_is_running(timer));
}

TEST(timer_stop_discards_state, "Stopping resets to stopped state")
{
	timer_type timer = timer_init(1000);
	timer = timer_start(timer, 0);
	ASSERT(timer_is_running(timer));
	timer = timer_update(timer, 500);
	ASSERT(timer_is_running(timer));
	timer = timer_stop(timer);
	ASSERT(timer_is_stopped(timer));
}

#ifdef UINT64_MAX
TEST(timer64_basic_timing, "64-bit timer works like 32-bit")
{
	timer64_type timer = timer64_init((uint64_t)UINT32_MAX + 1U);
	ASSERT(timer64_is_stopped(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 0U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), (uint64_t)UINT32_MAX + 1U);

	timer = timer64_start(timer, 0);
	ASSERT(timer64_is_running(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 0U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), (uint64_t)UINT32_MAX + 1U);

	timer = timer64_update(timer, UINT32_MAX);
	ASSERT(timer64_is_running(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), UINT32_MAX);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 1U);

	timer = timer64_update(timer, (uint64_t)UINT32_MAX + 1U);
	ASSERT(timer64_has_elapsed(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), (uint64_t)UINT32_MAX + 1U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 0U);

	timer = timer64_update(timer, (uint64_t)UINT32_MAX * 2U);
	ASSERT(timer64_has_elapsed(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), (uint64_t)UINT32_MAX * 2U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 0U);
}

TEST(timer64_pause_and_resume, "Pause/resume preserves remaining time")
{
	timer64_type timer = timer64_init(1000);
	ASSERT(timer64_is_stopped(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 0U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 1000U);

	timer = timer64_start(timer, 0);
	ASSERT(timer64_is_running(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 0U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 1000U);

	timer = timer64_pause(timer, 400);
	ASSERT(timer64_is_paused(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 400U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 600U);

	timer = timer64_resume(timer, 5000);
	ASSERT(timer64_is_running(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 400U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 600U);

	timer = timer64_update(timer, 5600);
	ASSERT(timer64_has_elapsed(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 1000U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 0U);
}

TEST(timer64_multiple_pause_and_resume_cycles, "Multiple pause/resume cycles work")
{
	timer64_type timer = timer64_init(1000);
	ASSERT(timer64_is_stopped(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 0U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 1000U);

	timer = timer64_start(timer, 0);
	ASSERT(timer64_is_running(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 0U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 1000U);

	/* First pause at 250ms */
	timer = timer64_pause(timer, 250);
	ASSERT(timer64_is_paused(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 250U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 750U);

	/* Resume at 500ms (gap of 250ms), elapsed duration is 250ms */
	timer = timer64_resume(timer, 500);
	ASSERT(timer64_is_running(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 250U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 750U);

	/* Second pause at 750ms */
	timer = timer64_pause(timer, 750);
	ASSERT(timer64_is_paused(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 500U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 500U);

	/* Resume at 10000ms, elapsed duration is 500ms */
	timer = timer64_resume(timer, 10000);
	ASSERT(timer64_is_running(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 500U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 500U);

	timer = timer64_update(timer, 10500);
	ASSERT(timer64_has_elapsed(timer));
	ASSERT_UINT64_EQUAL(timer64_elapsed_duration(timer), 1000U);
	ASSERT_UINT64_EQUAL(timer64_remaining_duration(timer), 0U);
}

TEST(timer64_edge_zero_duration, "Zero duration timer elapses immediately")
{
	timer64_type timer = timer64_init(0);
	timer = timer64_start(timer, 100);
	ASSERT(timer64_has_elapsed(timer));
	timer = timer64_update(timer, 101);
	ASSERT(timer64_has_elapsed(timer));
}

TEST(timer64_edge_same_time, "Updating with same time does not change state")
{
	timer64_type timer = timer64_init(1000);
	timer = timer64_start(timer, 100);
	ASSERT(timer64_is_running(timer));
	timer = timer64_update(timer, 100);
	ASSERT(timer64_is_running(timer));
}

TEST(timer64_stop_discards_state, "Stopping resets to stopped state")
{
	timer64_type timer = timer64_init(1000);
	timer = timer64_start(timer, 0);
	ASSERT(timer64_is_running(timer));
	timer = timer64_update(timer, 500);
	ASSERT(timer64_is_running(timer));
	timer = timer64_stop(timer);
	ASSERT(timer64_is_stopped(timer));
}
#endif

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		timer_basic_timing,
		timer_pause_and_resume,
		timer_multiple_pause_and_resume_cycles,
		timer_edge_zero_duration,
		timer_edge_same_time,
		timer_stop_discards_state
#ifdef UINT64_MAX
		,
		timer64_basic_timing,
		timer64_pause_and_resume,
		timer64_multiple_pause_and_resume_cycles,
		timer64_edge_zero_duration,
		timer64_edge_same_time,
		timer64_stop_discards_state
#endif
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
