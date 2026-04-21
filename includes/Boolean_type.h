#ifndef BOOLEAN_TYPE_H
#define BOOLEAN_TYPE_H

/*
Notes:
- For C89, Boolean_type is unsigned char because bool is 1-byte for C++ and C99+.
- For C++, Boolean_type is the native bool type.
- For C99 and newer C standards, Boolean_type is _Bool.
- For C++, C99 and newer C standards, any integer will be implicitly converted to Boolean type properly
  when being assigned to a Boolean variable.
*/
#if defined(__cplusplus)

/** @brief Backward-compatible Boolean type */
typedef bool Boolean_type;
/** @brief Equivalent to false */
#define Boolean_false false
/** @brief Equivalent to true */
#define Boolean_true true
/** @brief Macro which allows an integer to be properly converted to a Boolean value */
#define INTEGER_TO_BOOLEAN(integer) (integer)

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)

#if __STDC_VERSION__ < 202311L
#include <stdbool.h>
#endif

/** @brief Backward-compatible Boolean type */
typedef bool Boolean_type;
/** @brief Equivalent to false */
#define Boolean_false false
/** @brief Equivalent to true */
#define Boolean_true true
/** @brief Macro which allows an integer to be properly converted to a Boolean value */
#define INTEGER_TO_BOOLEAN(integer) (integer)

#else

/** @brief Backward-compatible Boolean type */
typedef unsigned char Boolean_type;
/** @brief Equivalent to false */
#define Boolean_false 0
/** @brief Equivalent to true */
#define Boolean_true (!Boolean_false)
/** @brief Macro which allows an integer to be properly converted to a Boolean value */
#define INTEGER_TO_BOOLEAN(integer) ((integer) != 0)

/** @brief Defines bool for C89/C90 */
#ifndef bool
#define bool Boolean_type
#endif

/** @brief Defines false for C89/C90 */
#ifndef false
#define false Boolean_false
#endif

/** @brief Defines true for C89/C90 */
#ifndef true
#define true Boolean_true
#endif

#endif

#endif
