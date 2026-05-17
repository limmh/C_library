#ifndef SAFER_INTEGER_MATH
#define SAFER_INTEGER_MATH

#include "Boolean_type.h"
#include "fixed_width_integer_types.h"
#include "inline_or_static.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Checks if a igned 32-bit integer is an even number
 * @param [in] integer Signed 32-bit integer
 * @return bool
 */
INLINE_OR_STATIC bool i32_is_even(int32_t integer) {
	return (integer % 2) == 0;
}

/**
 * @brief Checks if a signed 32-bit integer is an odd number
 * @param [in] integer Signed 32-bit integer
 * @return bool
 */
INLINE_OR_STATIC bool i32_is_odd(int32_t integer) {
	return !i32_is_even(integer);
}

/**
 * @brief Checks if an unsigned 32-bit integer is an even number
 * @param [in] integer Unsigned 32-bit integer
 * @return bool
 */
INLINE_OR_STATIC bool u32_is_even(uint32_t integer) {
	return (integer % 2U) == 0U;
}

/**
 * @brief Checks if an unsigned 32-bit integer is an odd number
 * @param [in] integer Unsigned 32-bit integer
 * @return bool
 */
INLINE_OR_STATIC bool u32_is_odd(uint32_t integer) {
	return !u32_is_even(integer);
}

/**
 * @brief Checks if a signed 32-bit integer is divisible by a signed 32-bit integer
 * @param [in] dividend The operand being divided
 * @param [in] divisor The operand that divides
 * @return bool
 */
bool i32_is_divisible(int32_t dividend, int32_t divisor);

/**
 * @brief Checks if an unsigned 32-bit integer is divisible by an unsigned 32-bit integer
 * @param [in] dividend The operand being divided
 * @param [in] divisor The operand that divides
 * @return bool
 */
bool u32_is_divisible(uint32_t dividend, uint32_t divisor);

/**
 * @brief Checks if a signed 32-bit integer is a prime number
 * @param [in] integer Signed 32-bit integer
 * @return bool
 */
bool i32_is_prime(int32_t integer);

/**
 * @brief Checks if an unsigned 32-bit integer is a prime number
 * @param [in] integer Unsigned 32-bit integer
 * @return bool
 */
bool u32_is_prime(uint32_t integer);

#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)
/**
 * @brief Checks if a igned 64-bit integer is an even number
 * @param [in] integer Signed 64-bit integer
 * @return bool
 */
INLINE_OR_STATIC bool i64_is_even(int64_t integer) {
	return (integer % 2) == 0;
}

/**
 * @brief Checks if a signed 64-bit integer is an odd number
 * @param [in] integer Signed 64-bit integer
 * @return bool
 */
INLINE_OR_STATIC bool i64_is_odd(int64_t integer) {
	return !i64_is_even(integer);
}

/**
 * @brief Checks if an unsigned 64-bit integer is an even number
 * @param [in] integer Unsigned 64-bit integer
 * @return bool
 */
INLINE_OR_STATIC bool u64_is_even(uint64_t integer) {
	return (integer % 2U) == 0U;
}

/**
 * @brief Checks if an unsigned 64-bit integer is an odd number
 * @param [in] integer Unsigned 64-bit integer
 * @return bool
 */
INLINE_OR_STATIC bool u64_is_odd(uint64_t integer) {
	return !u64_is_even(integer);
}

/**
 * @brief Checks if a signed 64-bit integer is divisible by a signed 64-bit integer
 * @param [in] dividend The operand being divided
 * @param [in] divisor The operand that divides
 * @return bool
 */
bool i64_is_divisible(int64_t dividend, int64_t divisor);

/**
 * @brief Checks if an unsigned 64-bit integer is divisible by an unsigned 64-bit integer
 * @param [in] dividend The operand being divided
 * @param [in] divisor The operand that divides
 * @return bool
 */
bool u64_is_divisible(uint64_t dividend, uint64_t divisor);

/**
 * @brief Checks if a signed 64-bit integer is a prime number
 * @param [in] integer Signed 64-bit integer
 * @return bool
 */
bool i64_is_prime(int64_t integer);

/**
 * @brief Checks if an unsigned 64-bit integer is a prime number
 * @param [in] integer Unsigned 64-bit integer
 * @return bool
 */
bool u64_is_prime(uint64_t integer);
#endif

#ifdef __cplusplus
}
#endif

#endif
