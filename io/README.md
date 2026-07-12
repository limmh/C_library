# README for keyboard_input and sleep I/O Libraries

```markdown
# I/O Utilities Library

Cross-platform keyboard input and sleep utilities for C applications.

## Overview

This library provides low-level terminal I/O functions:

- **Keyboard Input**: Read raw keyboard events without line buffering
- **Sleep**: Cross-platform thread suspension with millisecond precision

Supports Windows and POSIX systems (Linux, macOS, etc.).

## Quick Start

### Keyboard Input (Blocking)

```c
#include "io/keyboard_input.h"
#include <stdio.h>

int main(void) {
    printf("Press any key...\n");
    
    keyboard_input_result_type result = keyboard_input_from_terminal();
    
    if (result.error == 0) {
        printf("You pressed: ");
        for (size_t i = 0; i < result.input.number_of_bytes; i++) {
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

## API Reference

### Keyboard Input

#### `keyboard_input_from_terminal()`

Read keyboard input in blocking mode.

**Signature:**
```c
keyboard_input_result_type keyboard_input_from_terminal(void);
```

**Returns:**
- `input.keycode[]`: Raw keyboard bytes (OS-specific)
- `input.number_of_bytes`: Number of valid bytes (0 on error)
- `error`: 0 on success, errno value on failure

**Behavior:**
- Blocks until keyboard input available
- Terminal in raw mode (no line buffering)
- Returns immediately after one key press

**Linux Notes:**
- Terminal temporarily switched to raw mode
- Restored before function returns
- ANSI escape sequences for special keys

**Windows Notes:**
- Uses `getch()` for input
- Extended keys (arrows, function keys) return 2 bytes
- First byte: 0x00 or 0xE0, second byte: scan code

**Example:**
```c
keyboard_input_result_type result = keyboard_input_from_terminal();
if (result.error == 0) {
    if (keyboard_input_is_extended_key(result.input)) {
        printf("Extended key pressed (arrow, function key, etc.)\n");
    } else {
        printf("Regular key: %c\n", result.input.keycode[0]);
    }
}
```

---

#### `keyboard_input_from_terminal_nonblocking()`

Read keyboard input in non-blocking mode.

**Signature:**
```c
keyboard_input_result_type keyboard_input_from_terminal_nonblocking(void);
```

**Returns:**
- Same as `keyboard_input_from_terminal()`
- `number_of_bytes == 0` if no input available (not an error)

**Behavior:**
- Does not block
- Returns immediately whether input available or not
- Check `number_of_bytes` to determine if key was pressed

**Example:**
```c
while (1) {
    keyboard_input_result_type result = keyboard_input_from_terminal_nonblocking();
    
    if (result.number_of_bytes > 0) {
        printf("Key pressed: 0x%02X\n", result.input.keycode[0]);
        break;
    }
    
    // Do other work while waiting for input
    sleep_ms(100);
}
```

---

#### `keyboard_input_set_terminal_echo_mode(bool echo_mode)`

Enable or disable terminal echo.

**Signature:**
```c
int keyboard_input_set_terminal_echo_mode(bool echo_mode);
```

**Parameters:**
- `echo_mode`: true to enable echo, false to disable

**Returns:**
- 0 on success
- errno value on failure

**Behavior:**
- When enabled: typed characters displayed on terminal
- When disabled: typed characters not displayed (password entry)

**Example:**
```c
// Read password without echoing
keyboard_input_set_terminal_echo_mode(false);
keyboard_input_result_type result = keyboard_input_from_terminal();
keyboard_input_set_terminal_echo_mode(true);
printf("\n");  // Move to next line after password
```

---

#### `keyboard_input_terminal_echo_mode()`

Query current terminal echo mode.

**Signature:**
```c
bool keyboard_input_terminal_echo_mode(void);
```

**Returns:**
- true if echo is enabled
- false if echo is disabled

**Example:**
```c
bool current_echo = keyboard_input_terminal_echo_mode();
printf("Echo is currently: %s\n", current_echo ? "enabled" : "disabled");
```

---

#### `keyboard_input_is_extended_key(input)`

Check if keyboard input is an extended key.

**Signature:**
```c
#define keyboard_input_is_extended_key(input) \
    keyboard_input_is_extended_key_(&(input))
```

**Parameters:**
- `input`: keyboard_input_type instance

**Returns:**
- true if input is extended key (arrow, function key, etc.)
- false if regular key

**Extended Key Behavior:**

**Linux:**
- Extended keys are ANSI escape sequences
- ESC (0x1B) followed by additional bytes
- Bare ESC key press is NOT considered extended

**Windows:**
- Extended keys return 2 bytes
- First byte: 0x00 or 0xE0
- Second byte: scan code

**Example:**
```c
keyboard_input_result_type result = keyboard_input_from_terminal();

if (keyboard_input_is_extended_key(result.input)) {
    printf("Special key pressed (arrow, F-key, etc.)\n");
    
    // Print all bytes
    for (size_t i = 0; i < result.input.number_of_bytes; i++) {
        printf("  Byte %zu: 0x%02X\n", i, result.input.keycode[i]);
    }
} else {
    printf("Regular key: '%c' (0x%02X)\n",
           result.input.keycode[0],
           result.input.keycode[0]);
}
```

---

### Sleep

#### `sleep_sec(unsigned int time_in_seconds)`

Sleep for specified number of seconds.

**Signature:**
```c
void sleep_sec(unsigned int time_in_seconds);
```

**Parameters:**
- `time_in_seconds`: Duration in seconds

**Behavior:**
- Suspends thread for at least specified duration
- Actual duration may be longer due to system scheduling
- On Windows: asserts no overflow when converting to milliseconds

**Platform Notes:**
- **POSIX (Linux, macOS)**: Uses `sleep()` or `nanosleep()`
- **Windows**: Uses `Sleep()` with millisecond conversion

**Example:**
```c
printf("Starting 5-second countdown...\n");
for (int i = 5; i > 0; i--) {
    printf("%d...\n", i);
    sleep_sec(1);
}
printf("Blastoff!\n");
```

---

#### `sleep_ms(unsigned int time_in_milliseconds)`

Sleep for specified number of milliseconds.

**Signature:**
```c
void sleep_ms(unsigned int time_in_milliseconds);
```

**Parameters:**
- `time_in_milliseconds`: Duration in milliseconds

**Behavior:**
- Suspends thread for at least specified duration
- Actual duration may be longer due to system scheduling
- Higher precision than `sleep_sec()`

**Example:**
```c
printf("High-resolution sleep test\n");
printf("Sleeping 100ms...\n");
sleep_ms(100);
printf("Done!\n");

printf("Sleeping 500ms...\n");
sleep_ms(500);
printf("Done!\n");
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

### `keyboard_input_result_type`

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

## Usage Examples

### Example 1: Simple Key Echo

```c
#include "io/keyboard_input.h"
#include <stdio.h>
#include <ctype.h>

int main(void) {
    printf("Press any key (ESC to quit):\n");
    
    while (1) {
        keyboard_input_result_type result = keyboard_input_from_terminal();
        
        if (result.error != 0) {
            printf("Error: %d\n", result.error);
            break;
        }
        
        unsigned char key = result.input.keycode[0];
        
        if (key == 0x1B) {  // ESC key
            printf("\nExiting...\n");
            break;
        }
        
        if (isprint(key)) {
            printf("You pressed: '%c' (0x%02X)\n", key, key);
        } else {
            printf("You pressed special key: 0x%02X\n", key);
        }
    }
    
    return 0;
}
```

---

### Example 2: Arrow Key Detection

```c
#include "io/keyboard_input.h"
#include <stdio.h>

void print_key_name(keyboard_input_type input) {
    if (keyboard_input_is_extended_key(input)) {
        // Handle extended keys
        if (input.number_of_bytes >= 2) {
            unsigned char first = input.keycode[0];
            unsigned char second = input.keycode[1];
            
            #ifdef _WIN32
            // Windows extended key format
            if (first == 0xE0 || first == 0x00) {
                switch (second) {
                    case 0x48: printf("UP arrow\n"); break;
                    case 0x50: printf("DOWN arrow\n"); break;
                    case 0x4B: printf("LEFT arrow\n"); break;
                    case 0x4D: printf("RIGHT arrow\n"); break;
                    default: printf("Extended key: 0x%02X 0x%02X\n", first, second);
                }
            }
            #else
            // Linux ANSI escape sequence
            printf("ANSI escape sequence: 0x%02X 0x%02X\n", first, second);
            #endif
        }
    } else {
        printf("Regular key: '%c' (0x%02X)\n", input.keycode[0], input.keycode[0]);
    }
}

int main(void) {
    printf("Press arrow keys (ESC to quit):\n");
    
    while (1) {
        keyboard_input_result_type result = keyboard_input_from_terminal();
        
        if (result.error != 0) break;
        
        if (result.input.keycode[0] == 0x1B) break;  // ESC
        
        print_key_name(result.input);
    }
    
    return 0;
}
```

---

### Example 3: Password Input

```c
#include "io/keyboard_input.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    unsigned char password[64] = {0};
    size_t length = 0;
    
    printf("Enter password: ");
    
    // Disable echo
    keyboard_input_set_terminal_echo_mode(false);
    
    while (length < sizeof(password) - 1) {
        keyboard_input_result_type result = keyboard_input_from_terminal();
        
        if (result.error != 0) {
            printf("\nError reading input\n");
            break;
        }
        
        unsigned char key = result.input.keycode[0];
        
        if (key == 0x0D) {  // ENTER key
            break;
        } else if (key == 0x08) {  // BACKSPACE key
            if (length > 0) length--;
        } else if (key >= 0x20 && key < 0x7F) {  // Printable
            password[length++] = key;
        }
    }
    
    // Re-enable echo
    keyboard_input_set_terminal_echo_mode(true);
    printf("\n");
    
    printf("Password length: %zu characters\n", length);
    
    return 0;
}
```

---

### Example 4: Non-Blocking Input Loop

```c
#include "io/keyboard_input.h"
#include "io/sleep.h"
#include <stdio.h>

int main(void) {
    printf("Running animation loop (press Q to quit):\n");
    
    const char spinner[] = { '|', '/', '-', '\\' };
    int frame = 0;
    
    while (1) {
        // Do work (animation)
        printf("\rProcessing %c", spinner[frame % 4]);
        fflush(stdout);
        frame++;
        
        // Check for keyboard input without blocking
        keyboard_input_result_type result = keyboard_input_from_terminal_nonblocking();
        
        if (result.number_of_bytes > 0) {
            unsigned char key = result.input.keycode[0];
            if (key == 'Q' || key == 'q') {
                printf("\nQuitting...\n");
                break;
            }
        }
        
        // Small sleep to avoid busy-waiting
        sleep_ms(100);
    }
    
    return 0;
}
```

---

## Platform-Specific Notes

### Linux/macOS (POSIX)

```
Keyboard Input:
- Uses termios for raw mode
- Reads from stdin without buffering
- ANSI escape sequences for special keys
- Terminal restored on function return

Extended Keys:
- ESC (0x1B) followed by sequence
- Examples:
  - Up arrow: ESC [ A
  - Down arrow: ESC [ B
  - Function keys: ESC [ n ~
```

### Windows

```
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
```

---

## Design Decisions

### Return Struct vs Error Code

The library uses `keyboard_input_result_type` (struct containing result + error) rather than just returning error codes:

**Benefits:**
- Single function call (no separate data retrieval)
- Clear error semantics (error field always present)
- Composable (result can be passed to other functions)
- Thread-safe (no global state)

---

### Non-Blocking Function Variant

Separate `keyboard_input_from_terminal_nonblocking()` function enables:

- Event-driven applications
- Animation loops with input handling
- Responsive UIs with background work

Check `number_of_bytes == 0` to detect "no input available" (not an error).

---

### OS-Specific Encoding

Raw keycodes returned as-is:

- **Advantage**: Maximum fidelity to keyboard hardware
- **Advantage**: Works even for non-ASCII keyboards
- **Trade-off**: Caller must handle platform differences

Use `keyboard_input_is_extended_key()` to abstract the complexity.

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

## Compilation

### Linux/macOS

```bash
gcc -c io/keyboard_input.c -o keyboard_input.o
gcc -c io/sleep.c -o sleep.o
gcc -o myprogram myprogram.c keyboard_input.o sleep.o
```

### Windows

```bash
cl /c io/keyboard_input.c
cl /c io/sleep.c
cl myprogram.c keyboard_input.obj sleep.obj
```

---

## See Also

- [io/keyboard_input.h](./keyboard_input.h) - Full header with detailed documentation
- [io/sleep.h](./sleep.h) - Sleep function signatures
- [integer_to_string](../conversions/integer_to_string.h) - Number formatting utilities

---

## License

[Your License Here]

---
```

This README provides:

✅ **Quick start examples** (copy-paste ready)
✅ **Complete API reference** (every function documented)
✅ **Data type documentation** (struct layouts explained)
✅ **Real-world examples** (password input, animation loops, etc.)
✅ **Platform notes** (Windows vs POSIX differences)
✅ **Design rationale** (why certain choices were made)
✅ **Error handling guidance** (common issues and solutions)
✅ **Limitations** (what users should know)

The examples are practical and demonstrate:
- Basic usage
- Arrow key detection
- Password entry (echo mode)
- Non-blocking input with animation

This mirrors the quality of your integer_to_string and timer library documentation. 👏
