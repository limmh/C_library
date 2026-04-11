#ifndef SAFER_INTEGER_MATH
#define SAFER_INTEGER_MATH

#include "Boolean_type.h"
#include "fixed_width_integer_types.h"
#include "inline_or_static.h"

#ifdef __cplusplus
extern "C" {
#endif

INLINE_OR_STATIC
bool i32_is_even(int32_t integer) {
	return (integer % 2) == 0;
}

INLINE_OR_STATIC
bool i32_is_odd(int32_t integer) {
	return !i32_is_even(integer);
}

INLINE_OR_STATIC
bool u32_is_even(uint32_t integer) {
	return (integer % 2U) == 0U;
}

INLINE_OR_STATIC bool u32_is_odd(uint32_t integer) {
	return !u32_is_even(integer);
}

bool i32_is_divisible(int32_t dividend, int32_t divisor);

bool u32_is_divisible(uint32_t dividend, uint32_t divisor);

bool i32_is_prime(int32_t integer);

bool u32_is_prime(uint32_t integer);

#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)
INLINE_OR_STATIC bool i64_is_even(int64_t integer) {
	return (integer % 2) == 0;
}

INLINE_OR_STATIC bool i64_is_odd(int64_t integer) {
	return !i64_is_even(integer);
}

INLINE_OR_STATIC bool u64_is_even(uint64_t integer) {
	return (integer % 2U) == 0U;
}

INLINE_OR_STATIC bool u64_is_odd(uint64_t integer) {
	return !u64_is_even(integer);
}

bool i64_is_divisible(int64_t dividend, int64_t divisor);

bool u64_is_divisible(uint64_t dividend, uint64_t divisor);

bool i64_is_prime(int64_t integer);

bool u64_is_prime(uint64_t integer);
#endif

#ifdef __cplusplus
}
#endif

#endif
