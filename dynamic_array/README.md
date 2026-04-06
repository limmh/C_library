# dynamic_array

A generic dynamic array C API.

## Overview

The API provides an opaque, type-agnostic dynamic array container, supporting safe memory management, extensible error reporting, custom memory allocators, and a comprehensive set of macros for ease of use.
It is designed for safety and correctness, suitable for high security and high reliability applications.

## Features

- The API provides bounds checks to prevent out-of-bounds access and other runtime checks.
- Support for custom allocators.
- Customizable exception handling and error reporting or logging.

## Usage Example

```c
#include "dynamic_array.h"

int main(void)
{
    dynamic_array_type(int) dynarray = dynamic_array_create(int, 16);  // Create a dynamic array for ints
    dynamic_array_append_element(int, dynarray, 42);                   // Append an element
    int value = dynamic_array_element(int, dynarray, 0);               // Access an element
    dynamic_array_delete(dynarray);                                    // Clean up
    return 0;
}
```

## Data Types

- `dynamic_array_type(element_type)`: Opaque array type (use in variable declarations).
- `dynamic_array_allocator_type`: Structure for custom memory allocators.
- `dynamic_array_error_type`: Enum of error codes (for error reporting and debugging).
- `dynamic_array_debug_info_type`: Carries file/line/struct size information for diagnostics.

## Key Macros

- Creation: `dynamic_array_create(element_type, size)`, `dynamic_array_create_with_interface(element_type, size, interface)`
- Cleanup: `dynamic_array_delete(array)`
- Element access: `dynamic_array_element(element_type, array, index)`
- Adding/removing elements: `dynamic_array_append_element`, `dynamic_array_add_element_at_index`, `dynamic_array_remove_element_at_index`, etc.
- Resizing: `dynamic_array_resize(array, new_size)`
- Capacity and size: `dynamic_array_capacity(array)`, `dynamic_array_size(array)`
- Diagnostics: `dynamic_array_check(array)`

## Error Handling

You can provide an exception handler and an error reporting function via an interface. By default, errors terminate the program.

## Unit Tests

Unit tests are available. Refer to the unit tests for more examples.

## Compatibility

- C89 and newer C standards.

## License

MIT License
