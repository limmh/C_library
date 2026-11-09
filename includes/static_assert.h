#ifndef SAFER_C_LIBRARY_STATIC_ASSERT_H
#define SAFER_C_LIBRARY_STATIC_ASSERT_H
/*
Compile time assertion macro for C89 and C99
Note:
- Manually define SAFER_C_LIBRARY_STATIC_ASSERT_AVAILABLE to 1 in the compiler flags if static_assert is supported by your compiler, but
  the C or C++ version your compiler is not up to date.
- For pre-C11 standards, the macro cannot be used inside C structs.
*/

/** @brief macro for compile-time assertion */

#if (defined(__cplusplus) && (__cplusplus >= 201103L)) || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)) \
	|| (defined(SAFER_C_LIBRARY_STATIC_ASSERT_AVAILABLE) && SAFER_C_LIBRARY_STATIC_ASSERT_AVAILABLE != 0)
#ifndef __cplusplus
#include <assert.h>
#endif
#define SAFER_C_LIBRARY_STATIC_ASSERT(condition, message) static_assert(condition, message)
#else
#include "macro_concatenate.h"
#if defined(__COUNTER__)
#define SAFER_C_LIBRARY_STATIC_ASSERT(condition, message) typedef int SAFER_C_LIBRARY_CONCATENATE(static_assert_array_type_, __COUNTER__)[(condition) ? 1 : -1]
#elif defined(__LINE__)
#define SAFER_C_LIBRARY_STATIC_ASSERT(condition, message) typedef int SAFER_C_LIBRARY_CONCATENATE(static_assert_array_type_, __LINE__)[(condition) ? 1 : -1]
#pragma message("The SAFER_C_LIBRARY_STATIC_ASSERT macro cannot be implemented properly because __COUNTER__ is not defined by your compiler.")
#pragma message("Only one instance of SAFER_C_LIBRARY_STATIC_ASSERT is allowed on each line.")
#else
#error "The SAFER_C_LIBRARY_STATIC_ASSERT macro cannot be implemented because neither __COUNTER__ nor __LINE__ is defined by your compiler."
#endif
#endif

#ifdef SAFER_C_LIBRARY_STATIC_ASSERT_HAS_SHORT_MACRO
#ifndef STATIC_ASSERT
#define STATIC_ASSERT(condition, message) SAFER_C_LIBRARY_STATIC_ASSERT(condition, message)
#else
#error "The STATIC_ASSERT macro has been defined and shall not be redefined."
#endif
#endif

#endif
