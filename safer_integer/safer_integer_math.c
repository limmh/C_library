#include "safer_integer_math.h"
#include "safer_fixed_width_integers.h"
#include <iso646.h>

bool i32_is_divisible(int32_t dividend, int32_t divisor)
{
	bool result = false;
	if (dividend == INT32_MIN and divisor == -1) {
		result = true;
	} else if (divisor != 0) {
		result = (dividend % divisor) == 0;
	}
	return result;
}

bool u32_is_divisible(uint32_t dividend, uint32_t divisor)
{
	bool result = false;
	if (divisor != 0U) {
		result = (dividend % divisor) == 0U;
	}
	return result;
}

bool i32_is_prime(int32_t integer)
{
	bool result = false;
	if (integer < 2) {
		result = false;
	} else if (integer == 2 or integer == 3) {
		result = true;
	} else if (i32_is_even(integer)) {
		result = false;
	} else {
		const int32_t limit = INT16_MAX;
		int32_t count = 3;
		int32_t product = count * count;
		while (product < integer) {
			if ((integer % count) == 0) { /* integer is divisible by count */
				break;
			}
			count += 2;
			if (product < limit) {
				product = count * count;
			} else {
				const i32_result_type i32_result = safer_i32_multiply(count, count);
				if (i32_result.error == integer_operation_error_none) {
					product = i32_result.value;
				} else {
					result = true;
					break;
				}
			}
		}
		if (not result) {
			result = (product > integer);
		}
	}
	return result;
}

bool u32_is_prime(uint32_t integer)
{
	bool result = false;
	if (integer < 2U) {
		result = false;
	} else if (integer == 2U or integer == 3U) {
		result = true;
	} else if (u32_is_even(integer)) {
		result = false;
	} else {
		const uint32_t limit = UINT16_MAX;
		uint32_t count = 3U;
		uint32_t product = count * count;
		while (product < integer) {
			if ((integer % count) == 0U) { /* integer is divisible by count */
				break;
			}
			count += 2U;
			if (product < limit) {
				product = count * count;
			} else {
				const u32_result_type u32_result = safer_u32_multiply(count, count);
				if (u32_result.error == integer_operation_error_none) {
					product = u32_result.value;
				} else {
					result = true;
					break;
				}
			}
		}
		if (not result) {
			result = (product > integer);
		}
	}
	return result;
}

#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)
bool i64_is_divisible(int64_t dividend, int64_t divisor)
{
	bool result = false;
	if (dividend == INT64_MIN and divisor == -1) {
		result = true;
	} else if (divisor != 0) {
		result = (dividend % divisor) == 0;
	}
	return result;
}

bool u64_is_divisible(uint64_t dividend, uint64_t divisor)
{
	bool result = false;
	if (divisor != 0U) {
		result = (dividend % divisor) == 0U;
	}
	return result;
}

bool i64_is_prime(int64_t integer)
{
	bool result = false;
	if (integer < 2) {
		result = false;
	} else if (integer == 2 or integer == 3) {
		result = true;
	} else if (i64_is_even(integer)) {
		result = false;
	} else {
		const int64_t limit = INT32_MAX;
		int64_t count = 3;
		int64_t product = count * count;
		while (product < integer) {
			if ((integer % count) == 0) { /* integer is divisible by count */
				break;
			}
			count += 2;
			if (product < limit) {
				product = count * count;
			} else {
				const i64_result_type i64_result = safer_i64_multiply(count, count);
				if (i64_result.error == integer_operation_error_none) {
					product = i64_result.value;
				} else {
					result = true;
					break;
				}
			}
		}
		if (not result) {
			result = (product > integer);
		}
	}
	return result;
}

bool u64_is_prime(uint64_t integer)
{
	bool result = false;
	if (integer < 2U) {
		result = false;
	} else if (integer == 2U or integer == 3U) {
		result = true;
	} else if (u64_is_even(integer)) {
		result = false;
	} else {
		const uint64_t limit = UINT32_MAX;
		uint64_t count = 3U;
		uint64_t product = count * count;
		while (product < integer) {
			if ((integer % count) == 0U) { /* integer is divisible by count */
				break;
			}
			count += 2U;
			if (product < limit) {
				product = count * count;
			} else {
				const u64_result_type u64_result = safer_u64_multiply(count, count);
				if (u64_result.error == integer_operation_error_none) {
					product = u64_result.value;
				} else {
					result = true;
					break;
				}
			}
		}
		if (not result) {
			result = (product > integer);
		}
	}
	return result;
}
#endif
