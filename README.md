# C library with portable and safer APIs

## Overview

This repository contains a collection of portable C application programming interfaces (APIs) and sample programs.

## Motivation and Details

The standard library of the C programming language provides some APIs to access operating system (OS) resources and input/output (I/O) devices.
However, the C standard library does not provide many high level abstractions which are available in other programming languages.
There are no standard generic containers such as linked lists, dynamic arrays and dynamic strings.

As a result, many C programmers usually develop their own high level abstractions that they need for their applications,
while some programmers may rely only on the features provided by the standard library and mix low level details and business logic in their application code.
Due to the lack of generic programming support and the lack of RAII , it is not possible to implement truly generic data structures in C.

Despite the limitations, programmers have emulated generic containers in C using different ways.
The use of preprocessor macros is a common technique because C does not have a template system for generic programming.
All the data structures and data handling logic are fully coded in a header file.
The code can be inlined by the compiler more easily, but debugging is more difficult because the code is part of the preprocessor macros.
Another approach is to represent a heap-allocated contiguous memory block as a void pointer, but doing so means the type information is lost.

The dynamic arrays, dynamic strings and fat pointers in this library rely on a combination of the two approaches.
The core data structures contain a void pointer each, and their data handling logic is in separate source files instead of header files.
Function macros are provided to allow element size and debugging information to be passed to the actual functions.
The C language contains a lot of undefined behavior and it is easy to invoke undefined behavior.
Something as simple as an integer operation can easily trigger undefined behavior, e.g. signed integer overflow, if we are not careful enough.
Both C and C++ have the same integer operation issues and their standard libraries do not address the undefined behavior associated with integer operations.
This library contains a safer integer API to allow safer integer operations in C and C++ applications.

This library also contains some other APIs which make user-mode application development easier in C.
Some other popular libraries contain more useful features than this library, so this library is not meant to replace or compete with those libraries.
The author's main purpose is to share alternative approaches to implement data containers and safer APIs.
Certain APIs are implemented using basic functional programming techniques and value semantics.
The library focuses on correctness, ease of use, portability and testability, but not on performance optimization.
Hence, it is generally meant for user-mode applications and not for resource-constrained systems.

## Features

- **Header files implementing new C features for C89 and C99**  
  A backward compatible Boolean type for C89, static_assert and alignof for C89 and C99, string references, etc.
- **Dynamic arrays and strings**  
  A dynamic array API which supports per-instance custom allocator, common dynamic array operations and debugging.  
  A dynamic string API is also available.  
  Macros are used for dynamic array and string operations.
- **Fat pointers**  
  A fat pointer API which supports runtime bounds checking and error reporting.
- **Safer integer arithmetic operations**  
  Safer integer arithmetic C API for runtime integer operation error debugging and reporting.  
  Safer integer types for emulation of built-in integers and for debugging and reporting integer operation and conversion errors (requires C++)
- **Conversions**  
  API for conversions between integers and strings.
- **Simple tokenizer**  
  A tokenizer module for splitting text into simple tokens.
- **Timer API**  
  A portable timer API which emphasizes value semantics and has no dependency on the system clock.
- **Input/Output (IO)**  
  Input/output APIs which hide operating system (OS) details.
- **Terminal text color**  
  API for configuring the color of text on the terminal.
- **Unit testing**  
  A lightweight and simple unit testing library for C or C++ code.  
  Suitable for testing pure functions and black box interfaces.
- **Reference type emulation**  
  An experiment to demonstrate the interoperability between C pointers and C++ references.  
  References are emulated in C code using preprocessor macros.  
  Avoid using this in production code.
- **Sample programs**  
  Small programs demonstrating the use of the APIs.

## Getting Started

1. Clone the repository.
2. Make sure a recent version of CMake is installed.
3. In the local repository folder, create a new folder, e.g. build.
4. Use CMake to generate the build files for your target platform in the new folder you created.
5. Run the generated build to compile all library modules and programs.

## License

MIT License
