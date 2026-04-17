# Timer API

A portable timer API for embedded systems, games, and real-time applications.

## Overview

The timer API provides state-machine-based timers with pause/resume support.  

Key features:
- **Value semantics**: Operations return modified copies
- **Explicit time control**: Caller provides time
- **Pause/resume**: Correctly handles time gaps between pause and resume
- **Flexible time units**: Works with milliseconds, ticks, or custom units
- **32-bit and 64-bit variants**: For different precision and duration needs
- **Defensive**: Precondition checks, safe state transitions

## Quick Start

```c
#include "timer.h"

uint32_t now = get_time_ms();

// Create and start a 5-second timer
timer_type t = timer_init(5000);
t = timer_start(t, now);

// In your main loop:
now = get_time_ms();
t = timer_update(t, now);

if (timer_has_elapsed(t)) {
    // Timeout occurred
}
```

## Basic Usage

### Create Timer
```c
timer_type t = timer_init(1000);  // 1-second timer
```

### Start Timer
```c
t = timer_start(t, get_time_ms());
```

### Update and Check
```c
while (running) {
    t = timer_update(t, get_time_ms());
    
    if (timer_has_elapsed(t)) {
        handle_timeout();
    }
}
```

### Pause and Resume
```c
t = timer_pause(t, get_time_ms());
// ... some time passes ...
t = timer_resume(t, get_time_ms());  // Remaining time preserved
```

### Reset Timer
```c
t = timer_reset(t, 1000);  // New duration, stopped state
```

## API Reference

### Core Functions

| Function | Purpose |
|----------|---------|
| `timer_init(duration)` | Create timer in stopped state |
| `timer_reset(timer, duration)` | Reset to stopped state with new duration |
| `timer_start(timer, time)` | Start timer |
| `timer_stop(timer)` | Stop timer |
| `timer_pause(timer, time)` | Pause running timer |
| `timer_resume(timer, time)` | Resume paused timer |
| `timer_update(timer, time)` | Update and check for elapsed |

### Query Functions (Inline)

| Function | Returns |
|----------|---------|
| `timer_elapsed_duration(timer)` | Elapsed time |
| `timer_remaining_duration(timer)` | Time remaining (0 if elapsed) |
| `timer_has_elapsed(timer)` | true if elapsed |
| `timer_is_running(timer)` | true if running |
| `timer_is_paused(timer)` | true if paused |
| `timer_is_stopped(timer)` | true if stopped |

### 64-bit Variants

All functions have 64-bit versions: `timer64_init()`, `timer64_start()`, etc.

Use for high precision (microseconds) or long durations.

## Examples

### Periodic Timer
```c
timer_type periodic = timer_init(1000);
periodic = timer_start(periodic, get_time_ms());

while (running) {
    periodic = timer_update(periodic, get_time_ms());
    
    if (timer_has_elapsed(periodic)) {
        do_work();
        periodic = timer_reset(periodic, 1000);
        periodic = timer_start(periodic, get_time_ms());
    }
}
```

### Multiple Timers
```c
typedef struct {
    timer_type operation_timeout;
    timer_type auto_save;
    timer_type session;
} timeouts_t;

void update_timers(timeouts_t *t, uint32_t now) {
    t->operation_timeout = timer_update(t->operation_timeout, now);
    t->auto_save = timer_update(t->auto_save, now);
    t->session = timer_update(t->session, now);
    
    if (timer_has_elapsed(t->operation_timeout)) {
        timeout_operation();
        t->operation_timeout = timer_reset(t->operation_timeout, 30000);
        t->operation_timeout = timer_start(t->operation_timeout, now);
    }
}
```

## States

The timer has four states:

```
  +--------------------+-------------------+
  |                    |                   |
  |              reset or stop       reset or stop
  v                    |                   |
+-------+          +-------+           +-------+
|Stopped|--start-->|Running|--update-->|Elapsed|
+-------+          +-------+           +-------+
  ^                   |  ^                 ^
  |                pause |                 |
  |                   | resume             |
  |                   v  |                 |
  |                 +------+               |
  +-reset or stop---|Paused|----resume-----+
                    +------+
```

- **Stopped**: Initial state or timer has been stopped
- **Running**: Timer is active and its duration has not elapsed
- **Paused**: Timer is suspended, its elapsed time preserved
- **Elapsed**: Duration reached

## Design Principles

**Value Semantics**: All operations return modified copies.
```c
timer = timer_init(1000);
timer = timer_start(timer, get_time());
timer = timer_pause(timer, get_time());
timer = timer_resume(timer, get_time());
```

**Explicit Time**: Caller provides time, not library. Testable easily.

```c
timer = timer_update(timer, 100);   // Simulate 100ms
timer = timer_update(timer, 5000);  // Jump to 5 seconds
```

## Performance

- **Size of data structure**: 16 bytes (32-bit), 32 bytes (64-bit)
- **Overhead**: Minimal (stack-allocated, no heap required, no system calls)
- State query functions inlined for zero overhead

## Limitations

- **Time must move forward**: Decreasing time causes incorrect behavior
- **32-bit range**: ~49 days with millisecond precision (use 64-bit for longer)
- **Precision**: Limited by time source (millisecond, microsecond, tick)

## Portability

- **Platforms**: Linux, Unix, Windows, embedded, real-time systems
- **Compiler**: C89 or later
- **Dependencies**: Standard C only and APIs in this repository
- **64-bit timer API**: Available if 64-bit integers are supported

## License

MIT license
