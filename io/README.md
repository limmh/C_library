# I/O Utilities Library

Keyboard input and sleep utilities for C applications.

## Overview

This library provides low-level terminal I/O functions:

- **Keyboard Input**: Read raw keyboard events without line buffering
- **Sleep**: Cross-platform thread suspension with millisecond precision

## Quick Start

### Keyboard Input (Blocking)

```c
#include "io/keyboard_input.h"
#include <stdio.h>

int main(void) {
    keyboard_input_result_type result = {0};

    printf("Press any key...\n");
    result = keyboard_input_from_terminal();

    if (result.error == 0) {
        size_t i = 0;
        printf("You pressed: ");
        for (i = 0; i < result.input.number_of_bytes; ++i) {
            printf("%02X ", result.input.keycode[i]);
        }
        printf("\n");
    } else {
        printf("Error reading keyboard: %d\n", result.error);
    }

    return 0;
}
```

### Sleep

```c
#include "io/sleep.h"
#include <stdio.h>

int main(void) {
    printf("Sleeping for 2 seconds...\n");
    sleep_sec(2);

    printf("Sleeping for 500 milliseconds...\n");
    sleep_ms(500);

    printf("Done!\n");
    return 0;
}
```

---

## Data Types

### `keyboard_input_type`

```c
typedef struct keyboard_input_type {
    size_t number_of_bytes;      // Valid bytes in keycode (0-8)
    unsigned char keycode[8];    // Raw keyboard event bytes
} keyboard_input_type;
```

**Fields:**
- `number_of_bytes`: Number of valid bytes in keycode array
- `keycode[]`: Raw bytes representing the key event
  - Single byte: Regular ASCII key
  - Multiple bytes: Extended key (escape sequence or scan code)

---

### keyboard_input_result_type

```c
typedef struct keyboard_input_result_type {
    keyboard_input_type input;  // Keyboard input data
    int error;                  // errno value (0 = success)
} keyboard_input_result_type;
```

**Fields:**
- `input`: The keyboard input data
- `error`: System error code
  - 0: Success
  - Non-zero: errno value (see `<errno.h>`)


---

## Platform-Specific Notes

### Linux/macOS (POSIX)

Keyboard Input:
- Uses termios for raw mode
- Reads from stdin without buffering
- ANSI escape sequences for special keys
- Terminal restored on function return

Extended Keys:
- ESC (0x1B) followed by sequence

### Windows

Keyboard Input:
- Uses getch() for unbuffered input
- Two-byte encoding for extended keys
- First byte: 0x00 (function keys) or 0xE0 (navigation)
- Second byte: scan code

Arrow Key Codes:
- Up: 0xE0 0x48
- Down: 0xE0 0x50
- Left: 0xE0 0x4B
- Right: 0xE0 0x4D

---

## Design Decisions

### Return Struct vs Error Code

The library uses `keyboard_input_result_type` (struct containing result + error) rather than just returning error codes.

**Reasons:**
- Single function call (no separate data retrieval)
- Clear error semantics (error field always present)
- Composable (result can be passed to other functions)

### Non-Blocking Function Variant

Separate `keyboard_input_from_terminal_nonblocking()` function enables:

- Event-driven applications
- Loops with input handling
- Responsive UIs with background work

Check `number_of_bytes == 0` to detect "no input available" (not an error).

### OS-Specific Encoding

Use `keyboard_input_is_extended_key()` to check whether a key is an extended key.

---

## Error Handling

All functions that return `keyboard_input_result_type` indicate errors via the `error` field:

```c
keyboard_input_result_type result = keyboard_input_from_terminal();

if (result.error == 0) {
    // Success - process result.input
} else {
    // Error - check errno
    printf("Error: %s\n", strerror(result.error));
}
```

Common error values:
- `EINVAL`: Invalid operation
- `EIO`: I/O error
- `ENOTTY`: Not a terminal
- `EINTR`: Interrupted by signal (can retry)

---

## Limitations

### Keyboard Input

- **No unicode support**: Returns raw OS-specific keycodes
- **Terminal-dependent**: Behavior varies by terminal emulator
- **Extended keys vary by OS**: Different encoding on Windows vs POSIX
- **No key repeat detection**: Cannot distinguish repeated press from held key

### Sleep

- **Not precise**: Actual duration may be longer (depends on OS scheduler)
- **Thread blocks**: Current thread cannot do work during sleep
- **Maximum duration**: Limited by unsigned int range (4 billion milliseconds ≈ 46 days)

---

## License

MIT License
