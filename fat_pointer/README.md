# Fat Pointer API

A bounds-checked pointer wrapper for C.

## Overview

The Fat Pointer API provides a safer abstraction over raw C pointers by encapsulating:

- **Pointer to data**: The actual memory address
- **Capacity**: Maximum number of elements allowed
- **Size/Length**: Current number of valid elements
- **Element size**: Number of bytes per element

This enables bounds checking, range validation, and safer element access while maintaining a non-owning reference to external data.

## Key Features

- **Bounds checking**: Validates array access operations
- **Non-owning**: References external data without taking ownership
- **Support for contiguous data**: Works with any contiguous data type (arrays, buffers, etc.)
- **Error handling**: Explicit error codes for most operations
- **Debug support**: File and line number tracking for error reporting
- **No allocation**: Zero dynamic memory overhead
- **Customizable**: Custom error and exception handlers

## Quick Start

```c
#include "fat_pointer.h"

int main(void) {
    // Create a buffer
    int buffer[100] = {0};
    int initial_size = 10;
    
    // Create fat pointer (non-owning reference)
    fat_pointer_type(int) arr = fat_pointer_create(
        int,              // Element type
        buffer,           // Underlying data
        100,              // Capacity
        initial_size      // Initial size
    );
    
    // Access elements safely
    fat_pointer_element(int, arr, 0) = 42;
    
    // Add more elements
    int new_values[] = {1, 2, 3};
    fat_pointer_append_elements(int, arr, new_values, 3);
    
    // Query information
    printf("Size: %zu\n", fat_pointer_size(arr));
    printf("Capacity: %zu\n", fat_pointer_capacity(arr));
    
    // Clean up
    fat_pointer_destroy(arr);
    
    return 0;
}
```

---

## Error Handling

### Error Codes

```c
typedef enum fat_pointer_error_type {
    fat_pointer_error_none,                             // Success
    fat_pointer_error_null_pointer_exception,           // Null pointer passed
    fat_pointer_error_no_pointer,                       // Internal pointer issue
    fat_pointer_error_incorrect_capacity,               // Capacity mismatch
    fat_pointer_error_incorrect_element_size,           // Element size mismatch
    fat_pointer_error_index_out_of_range,               // Index out of bounds
    fat_pointer_error_element_size_mismatch,            // Type mismatch
    fat_pointer_error_addition_overflow_detected,       // Overflow in addition
    fat_pointer_error_multiplication_overflow_detected, // Overflow in multiplication
    fat_pointer_error_no_source_elements,               // Source buffer empty
    fat_pointer_error_no_enough_capacity,               // Insufficient capacity
    fat_pointer_error_too_many_elements_to_remove       // Remove count exceeds size
} fat_pointer_error_type;
```

### Error Reporting Handler

```c
void custom_error_handler(fat_pointer_debug_info_type info) {
    fprintf(stderr, "Error in %s at line %d: %d\n",
            info.file_name, info.line_number, info.error);
}

int main(void) {
    fat_pointer_set_report_handler(custom_error_handler);
    // ... use fat pointers ...
}
```

---

### Exception Handler

```c
void custom_exception_handler(fat_pointer_error_type error) {
    fprintf(stderr, "Fat pointer exception: %d\n", error);
    exit(1);
}

int main(void) {
    fat_pointer_set_exception_handler(custom_exception_handler);
    // ... operations can now throw exceptions ...
}
```

---

## Usage Examples

### Example 1: Dynamic Array Wrapper

```c
#include "fat_pointer.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    // Allocate buffer
    int *buffer = malloc(sizeof(int) * 100);
    
    // Create fat pointer (non-owning)
    fat_pointer_type(int) arr = fat_pointer_create(
        int, buffer, 100, 0
    );
    
    // Add elements
    for (int i = 0; i < 10; ++i) {
        fat_pointer_append_element(int, arr, i * 10);
    }
    
    // Access elements
    for (size_t i = 0; i < fat_pointer_size(arr); ++i) {
        printf("%d ", fat_pointer_element(int, arr, i));
    }
    printf("\n");
    
    // Clean up
    fat_pointer_destroy(arr);
    free(buffer);
    
    return 0;
}
```

---

### Example 2: Stack-Based Buffer

```c
#include "fat_pointer.h"
#include "sizeof_array.h"
#include <stdio.h>

int main(void) {
    // Stack-allocated buffer
    char buffer[1024];
    
    // Create fat pointer
    fat_pointer_type(char) str = fat_pointer_create(
        char, buffer, sizeof_array(buffer), 0
    );
    
    // Build string safely
    const char *hello = "Hello";
    fat_pointer_append_elements(char, str, hello, strlen(hello));

    fat_pointer_append_element(char, str, (char)' ');

    const char *world = "World";
    fat_pointer_append_elements(char, str, world, strlen(world));

    // Print the string to the screen
    printf("%s\n", &fat_pointer_element(char, str, 0U));
    
    fat_pointer_destroy(str);
    return 0;
}
```

---

### Example 3: Struct Array

```c
#include "fat_pointer.h"
#include "sizeof_array.h"
#include <stdio.h>

typedef struct person_type {
    int id;
    char name[32];
} person_type;

int main(void) {
    // Allocate array of structs
    person_type people[50] = {{0, {0}}};
    
    // Create fat pointer
    fat_pointer_type(person_type) roster = fat_pointer_create(
        person_type, people, sizeof_array(people), 0
    );
    
    // Add people
    person_type alice = {1, "Alice"};
    person_type bob = {2, "Bob"};
    
    fat_pointer_append_element(person_type, roster, alice);
    fat_pointer_append_element(person_type, roster, bob);
    
    // Access
    for (size_t i = 0, size = fat_pointer_size(roster); i < size; ++i) {
        person_type *p = fat_pointer_element_ptr(person_type, roster, i);
        printf("%d: %s\n", p->id, p->name);
    }
    
    fat_pointer_destroy(roster);
    return 0;
}
```

---

### Example 4: Error Handling

```c
#include "fat_pointer.h"
#include "sizeof_array.h"
#include <stdio.h>

int main(void) {
    int buffer[10] = {0};
    
    fat_pointer_type(int) arr = fat_pointer_create(
        int, buffer, sizeof_array(buffer), 5
    );
    
    // Try to access out of bounds
    const int index = 42;
    fat_pointer_error_type error = fat_pointer_append_element(int, arr, index);
    
    if (error != fat_pointer_error_none) {
        printf("Operation failed with error: %d\n", error);
        
        switch (error) {
        case fat_pointer_error_no_enough_capacity:
            printf("Buffer is full\n");
            break;
        case fat_pointer_error_index_out_of_range:
            printf("Index out of range\n");
            break;
        default:
            printf("Another error\n");
        }
    }
    
    fat_pointer_destroy(arr);
    return 0;
}
```

---

## Performance

- **Memory overhead**: 32 bytes (64-bit systems) per fat pointer
- **Access time**: O(1) for all operations
- **Creation time**: O(1), no initialization needed
- **Element access**: Direct memory access, no indirection
- **Bounds checking**: Minimal overhead (comparisons only)

---

## Limitations

- **Non-owning**: Caller must manage underlying data lifetime
- **Fixed capacity**: Cannot exceed initial capacity
- **Type safety**: Macro-based (compile-time only)
- **No reallocation**: Cannot grow beyond capacity
- **Manual management**: User handles memory allocation/deallocation

---

## Use Cases

**Suitable for:**
- Wrapping stack-allocated buffers with bounds checking
- Non-owning array references
- Safe iteration over external data
- Temporary array views
- Safe element access without dynamic allocation

**Not suitable for:**
- Owning data collections
- Dynamic sizing beyond capacity
- Ownership transfer
- Long-term data storage

---

## License

MIT License
