# Integer-String Conversion API

A comprehensive, portable, and safe C API for converting between integers and their string representations in various number bases.

---

## Overview

This API provides:

- **Integer-to-String Conversion**: Convert signed/unsigned integers (32-bit and 64-bit) to string representations in bases 2-36.
- **String-to-Integer Conversion**: Parse strings in various bases back to integers with comprehensive error handling.
- **Value-Semantic API**: Functions return values by value (not pointers), enabling stack allocation and efficient copying.
- **Explicit Error Handling**: All errors are represented as explicit enum values, never silent failures.
- **No Undefined Behavior**: Comprehensive validation and bounds checking ensure safe conversion.
- **Portability**: Uses fixed-width integer types and is portable across all C89+ compliant systems.

---

## Features

### Integer-to-String Conversion

- **Supported Bases**: 2-36 (binary, octal, decimal, hexadecimal, and arbitrary bases).
- **Formatting Options**:
  - Case selection (lowercase `a-z` or uppercase `A-Z` for bases > 10).
  - Optional number base prefix (e.g., `0x` for hex, `0b` for binary, `0` for octal).
  - Optional plus sign for positive integers.
- **Types Supported**:
  - `int32_t` -> `i32string_type`
  - `uint32_t` -> `u32string_type`
  - `int64_t` -> `i64string_type`
  - `uint64_t` -> `u64string_type`
- **Convenience Functions**: Specialized functions for common bases (2, 8, 10, 16) with optional prefixes.
- **Stack Allocation**: String buffers are embedded in return structs, no heap allocation needed.

### String-to-Integer Conversion

- **Flexible Input**: Accepts various formats:
  - Plain numbers: `"123"`, `"-456"`
  - With prefixes: `"0xff"`, `"0b1010"`, `"0777"`
  - With whitespace: `"  +789  "` (leading/trailing spaces handled)
- **Comprehensive Error Reporting**: distinct error codes for precise failure diagnosis.
- **Overflow/Underflow Detection**: Explicitly detects when parsed value exceeds type limits.

---

## Data Types

### String Storage Types

```c
typedef struct i32string_type {
    char content[(sizeof(int32_t) * CHAR_BIT) + 4U];  // 36 bytes
} i32string_type;

typedef struct u32string_type {
    char content[(sizeof(uint32_t) * CHAR_BIT) + 4U]; // 36 bytes
} u32string_type;

typedef struct i64string_type {
    char content[(sizeof(int64_t) * CHAR_BIT) + 4U];  // 68 bytes
} i64string_type;

typedef struct u64string_type {
    char content[(sizeof(uint64_t) * CHAR_BIT) + 4U]; // 68 bytes
} u64string_type;
```

**Why these sizes?**
- Worst case: binary representation of a 64-bit number is 64 bits + sign (1) + prefix (2) + NUL (1) = 68 bytes.
- All strings are **always null-terminated**.
- **Stack-allocated**: No heap allocation needed.

### Formatting Options

```c
typedef enum int_to_string_option_type {
    int_to_string_option_default = 0,
    int_to_string_option_lowercase = 0,      // a-z for bases > 10
    int_to_string_option_uppercase = 1,      // A-Z for bases > 10
    int_to_string_option_add_prefix = 2,     // 0x, 0b, 0 for hex/binary/octal
    int_to_string_option_add_plus_sign = 4   // + for positive integers
} int_to_string_option_type;
```

**Options can be combined via bitwise OR:**
```c
i32string_type str = i32_to_i32string(255, 16, 
    int_to_string_option_uppercase | int_to_string_option_add_prefix);
// Result: "0xFF"
```

### Error Codes

```c
typedef enum string_to_int_error_type {
    string_to_int_error_none = 0,                                      // Success
    string_to_int_error_null_string,                                   // Input pointer is NULL
    string_to_int_error_zero_length,                                   // Length parameter is 0
    string_to_int_error_empty_string,                                  // String is empty (NUL at start)
    string_to_int_error_invalid_base,                                  // Base < 2
    string_to_int_error_unsupported_base,                              // Base > 36
    string_to_int_error_only_whitespaces,                              // String contains only whitespace
    string_to_int_error_incomplete_string,                             // String ends prematurely (e.g., "-" alone)
    string_to_int_error_invalid_character,                             // Invalid character for base
    string_to_int_error_invalid_prefix,                                // Invalid prefix (e.g., "0q" for hex)
    string_to_int_error_whitespace_after_sign,                         // Whitespace after +/- (e.g., "- 123")
    string_to_int_error_digit_not_supported_by_base,                   // Digit exceeds base (e.g., "9" in binary)
    string_to_int_error_invalid_trailing_character,                    // Non-whitespace after valid number
    string_to_int_error_value_smaller_than_minimum_signed_value,       // Negative overflow
    string_to_int_error_value_greater_than_maximum_signed_value,       // Positive overflow
    string_to_int_error_value_smaller_than_minimum_unsigned_value,     // Negative value for unsigned type
    string_to_int_error_value_greater_than_maximum_unsigned_value      // Unsigned overflow
} string_to_int_error_type;
```

### Result Types

```c
typedef struct string_to_i32_result_type {
    int32_t value;
    string_to_int_error_type error;
} string_to_i32_result_type;

// Similar for u32, i64, u64
```

**Pattern**: Every operation returns both the result and an explicit error code.

---

## API Reference

### Integer to String

#### Core Functions

```c
i32string_type i32_to_i32string(int32_t value, int base, int_to_string_option_type options);
u32string_type u32_to_u32string(uint32_t value, int base, int_to_string_option_type options);
i64string_type i64_to_i64string(int64_t value, int base, int_to_string_option_type options);
u64string_type u64_to_u64string(uint64_t value, int base, int_to_string_option_type options);
```

**Parameters:**
- `value`: Integer to convert.
- `base`: Radix for conversion (2-36).
- `options`: Formatting flags (case, prefix, plus sign).

**Returns:** String struct with null-terminated content.

**Example:**
```c
i32string_type str = i32_to_i32string(255, 16, int_to_string_option_uppercase);
printf("%s\n", str.content);  // Output: "FF"

i64string_type str2 = i64_to_i64string(-42, 2, 
    int_to_string_option_add_prefix | int_to_string_option_lowercase);
printf("%s\n", str2.content);  // Output: "-0b101010"
```

#### Convenience Functions

**Binary:**
```c
i32string_type base2_i32_to_i32string(int32_t value);
i32string_type base2_i32_to_i32string_with_prefix(int32_t value);
i32string_type base2_i32_to_i32string_with_prefix_in_uppercase(int32_t value);
// Similar for u32, i64, u64
```

**Octal:**
```c
i32string_type base8_i32_to_i32string(int32_t value);
i32string_type base8_i32_to_i32string_with_prefix(int32_t value);
// Similar for u32, i64, u64
```

**Decimal:**
```c
i32string_type base10_i32_to_i32string(int32_t value);
// Similar for u32, i64, u64
```

**Hexadecimal:**
```c
i32string_type base16_i32_to_i32string(int32_t value);                      // lowercase, no prefix
i32string_type base16_i32_to_i32string_in_uppercase(int32_t value);         // uppercase, no prefix
i32string_type base16_i32_to_i32string_with_prefix(int32_t value);          // lowercase with 0x
i32string_type base16_i32_to_i32string_with_prefix_in_uppercase(int32_t value); // uppercase with 0x
// Similar for u32, i64, u64
```

---

### String to Integer

#### Core Functions

```c
string_to_i32_result_type string_to_i32(const char *string, size_t length, int base);
string_to_u32_result_type string_to_u32(const char *string, size_t length, int base);
string_to_i64_result_type string_to_i64(const char *string, size_t length, int base);
string_to_u64_result_type string_to_u64(const char *string, size_t length, int base);
```

**Parameters:**
- `string`: Input string to parse (need not be null-terminated if length is specified).
- `length`: Number of characters to parse.
- `base`: Radix for parsing (2-36).

**Returns:** Result struct containing parsed value and error code.

**Preconditions:**
- `string` must be non-NULL (checked at runtime).
- `length` must be > 0 (checked at runtime).
- `base` must be in [2, 36] (checked at runtime).

**Postconditions:**
- If `error == string_to_int_error_none`, `value` contains the parsed integer.
- If `error` is set, `value` may be zero or may contain a value, but it should not be relied upon.

**Example:**
```c
string_to_i32_result_type result = string_to_i32("255", 3, 16);
if (result.error == string_to_int_error_none) {
    printf("Parsed: %d\n", result.value);  // Output: 255
} else {
    printf("Error: %s\n", string_to_int_error_message(result.error));
}

// With leading/trailing whitespace
string_to_i32_result_type result2 = string_to_i32("  -123  ", 8, 10);
if (result2.error == string_to_int_error_none) {
    printf("Parsed: %d\n", result2.value);  // Output: -123
}

// Hexadecimal with prefix
string_to_i32_result_type result3 = string_to_i32("0xFF", 4, 16);
if (result3.error == string_to_int_error_none) {
    printf("Parsed: %d\n", result3.value);  // Output: 255
}
```

#### Convenience Macros for String Structs

```c
#define i32string_to_i32(i32string, base) i32string_to_i32_(&(i32string), base)
#define u32string_to_u32(u32string, base) u32string_to_u32_(&(u32string), base)
#define i64string_to_i64(i64string, base) i64string_to_i64_(&(i64string), base)
#define u64string_to_u64(u64string, base) u64string_to_u64_(&(u64string), base)
```

**Example (Roundtrip):**
```c
// Convert to string
i32string_type str = base16_i32_to_i32string_with_prefix(255);  // "0xff"

// Parse back to integer
string_to_i32_result_type result = i32string_to_i32(str, 16);
if (result.error == string_to_int_error_none) {
    printf("Roundtrip: %d\n", result.value);  // Output: 255
}
```

#### Error Messaging

```c
const char *string_to_int_error_message(string_to_int_error_type error);
```

**Returns:** Human-readable error description (pointer to read-only string, always non-NULL).

**Example:**
```c
string_to_i32_result_type result = string_to_i32("999999999999", 12, 10);
if (result.error != string_to_int_error_none) {
    printf("Error: %s\n", string_to_int_error_message(result.error));
    // Output: "The integer value in the string is higher than the maximum of the signed integer."
}
```

---

## Usage Examples

### Example 1: Convert Integers to Various Bases

```c
#include "integer_to_string.h"
#include <stdio.h>

int main(void) {
    int32_t value = 255;
    
    // Binary
    i32string_type bin = base2_i32_to_i32string_with_prefix(value);
    printf("Binary: %s\n", bin.content);  // "0b11111111"
    
    // Octal
    i32string_type oct = base8_i32_to_i32string_with_prefix(value);
    printf("Octal: %s\n", oct.content);   // "0377"
    
    // Decimal
    i32string_type dec = base10_i32_to_i32string(value);
    printf("Decimal: %s\n", dec.content); // "255"
    
    // Hexadecimal
    i32string_type hex = base16_i32_to_i32string_with_prefix_in_uppercase(value);
    printf("Hex: %s\n", hex.content);     // "0XFF"
    
    return 0;
}
```

### Example 2: Parse Strings in Different Bases

```c
#include "string_to_integer.h"
#include <stdio.h>

int main(void) {
    // Decimal
    string_to_i32_result_type dec = string_to_i32("123", 3, 10);
    if (dec.error == string_to_int_error_none) {
        printf("Decimal: %d\n", dec.value);  // "123"
    }
    
    // Hexadecimal with prefix
    string_to_i32_result_type hex = string_to_i32("0xFF", 4, 16);
    if (hex.error == string_to_int_error_none) {
        printf("Hex: %d\n", hex.value);      // "255"
    }
    
    // Binary with leading whitespace
    string_to_i32_result_type bin = string_to_i32("  0b1010  ", 10, 2);
    if (bin.error == string_to_int_error_none) {
        printf("Binary: %d\n", bin.value);   // "10"
    }
    
    // Error handling
    string_to_i32_result_type overflow = string_to_i32("2147483648", 10, 10);  // INT32_MAX + 1
    if (overflow.error != string_to_int_error_none) {
        printf("Error: %s\n", string_to_int_error_message(overflow.error));
        // "The integer value in the string is higher than the maximum of the signed integer."
    }
    
    return 0;
}
```

### Example 3: Roundtrip Conversion

```c
#include "integer_to_string.h"
#include "string_to_integer.h"
#include <stdio.h>

int main(void) {
    int32_t original = -12345;
    
    // Convert to string
    i32string_type str = base10_i32_to_i32string(original);
    printf("String: %s\n", str.content);  // "-12345"
    
    // Parse back to integer
    string_to_i32_result_type result = i32string_to_i32(str, 10);
    if (result.error == string_to_int_error_none) {
        printf("Parsed: %d\n", result.value);  // "-12345"
        printf("Match: %s\n", (result.value == original) ? "yes" : "no");  // "yes"
    }
    
    return 0;
}
```

### Example 4: Handling Errors Explicitly

```c
#include "string_to_integer.h"
#include <stdio.h>

void safe_parse(const char *input, size_t length, int base) {
    string_to_i32_result_type result = string_to_i32(input, length, base);
    
    switch (result.error) {
        case string_to_int_error_none:
            printf("Success: %d\n", result.value);
            break;
        case string_to_int_error_null_string:
            printf("Error: NULL input string\n");
            break;
        case string_to_int_error_invalid_base:
            printf("Error: Invalid base (must be 2-36)\n");
            break;
        case string_to_int_error_value_greater_than_maximum_signed_value:
            printf("Error: Value too large for int32_t\n");
            break;
        case string_to_int_error_invalid_character:
            printf("Error: Invalid character for base %d\n", base);
            break;
        default:
            printf("Error: %s\n", string_to_int_error_message(result.error));
    }
}

int main(void) {
    safe_parse("12345", 5, 10);      // Success: 12345
    safe_parse("0xFF", 4, 16);       // Success: 255
    safe_parse("999999999999", 12, 10); // Error: Value too large for int32_t
    safe_parse("12G", 3, 16);        // Error: Invalid character for base 16
    
    return 0;
}
```

---

## Design Principles

### 1. **Value Semantics**
- Functions return values by value, not pointers.
- Strings are stack-allocated (no heap needed).
- Enables efficient copying and functional composition.

### 2. **Explicit Error Handling**
- No silent failures (no return codes like -1 or NULL used ambiguously).
- All errors represented as explicit enum values.
- Users must explicitly check error codes; compiler cannot force this, but API makes it clear.

### 3. **No Undefined Behavior**
- All inputs validated (null checks, range checks, overflow detection).
- Comprehensive assertions and runtime checks ensure safety.
- Portable across all C89+ compliant systems.

### 4. **Type Safety**
- Fixed-width integer types (`int32_t`, `uint64_t`) used throughout.
- Separate types for signed/unsigned and different widths.
- Prevents accidental type confusion.

### 5. **Convenience Without Sacrifice**
- Specialized functions for common bases (2, 8, 10, 16) reduce boilerplate.
- Macros provide type-safe syntax without macro complexity.
- Both flexibility (generic functions) and simplicity (specialized functions) available.

---

## Portability

- **C Standard**: C89 or later
- **Endianness**: Independent (no assumptions about byte order).
- **Platform**: Portable to all platforms with C89+ support (x86, ARM, MIPS, etc.).
- **Dependencies**: Standard C library and header files in this repository.

---

## Performance Considerations

- **Stack Allocation**: No heap allocation overhead; strings embedded in return structs.
- **Inlining**: Convenience functions are possibly inlined for potential compiler optimization.
- **No Dynamic Memory**: All operations have predictable, constant-time performance (within single operation).
- **Minimal Copying**: Value semantics allow compilers to optimize with move semantics or register passing.

---

## Limitations and Edge Cases

### Integer-to-String

- **Bases 2-36**: Any base outside this range results in undefined behavior (use asserts to verify).
- **Negative Numbers**: Sign is always included for signed types; prefix applies after sign.
- **Zero**: Represented as `"0"` (never empty, never negative).

### String-to-Integer

- **Whitespace Handling**: Leading and trailing whitespace is skipped; whitespace after sign is an error.
- **Prefix Recognition**: Prefixes (`0x`, `0b`, `0`) are recognized only at the start (after whitespace and/or sign).
- **Incomplete Strings**: `"-"` or `"0x"` alone are errors (no digits follow).
- **Negative Unsigned**: Parsing `"-123"` as `uint32_t` results in underflow error (not automatic conversion to large positive value).

---

## Testing

Comprehensive unit tests cover:

- All supported bases (2-36).
- Edge cases (zero, min/max values).
- Error conditions (overflow, underflow, invalid input).
- Roundtrip conversions (integer -> string -> integer).
- Whitespace and prefix handling.
- Signed/unsigned type conversions.

---

## Thread Safety

- **Read-Only**: All functions are read-only; no global state mutation.
- **No Locks**: No synchronization primitives used.
- **Safe to Call Concurrently**: Multiple threads can safely call these functions simultaneously.

---

## See Also

- ISO C99 Standard: Fixed-width integer types (`<stdint.h>`).
- POSIX `strtol()`, `strtoul()`: Related (but less safe) standard library functions.
- Header file in this library: `includes/fixed_width_integer_types.h`.
