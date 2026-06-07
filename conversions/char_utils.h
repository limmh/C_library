#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

#include "Boolean_type.h"
#include "inline_or_static.h"
#include <assert.h>

/** @brief Checks whether an ASCII character is a decimal digit (0 to 9) */
INLINE_OR_STATIC bool character_is_decimal_digit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

/** @brief Checks whether an ASCII character is uppercase */
INLINE_OR_STATIC bool character_is_uppercase_alphabet(char ch)
{
	return (ch >= 'A' && ch <= 'Z');
}

/** @brief Checks whether an ASCII character is lowercase */
INLINE_OR_STATIC bool character_is_lowercase_alphabet(char ch)
{
	return (ch >= 'a' && ch <= 'z');
}

/** @brief Checks whether an ASCII character is a white space or new line */
INLINE_OR_STATIC bool character_is_whitespace(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');
}

/** @brief Checks whether an ASCII character is a hexadecimal digit (0 to 9, A to F or a to z) */
INLINE_OR_STATIC bool character_is_hexadecimal_digit(char ch)
{
	return character_is_decimal_digit(ch) || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f');
}

/** @brief Checks whether an ASCII character is a binary digit (0 or 1) */
INLINE_OR_STATIC bool character_is_binary_digit(char ch)
{
	return (ch == '0' || ch == '1');
}

/** @brief Checks whether an ASCII character is a valid digit */
INLINE_OR_STATIC bool character_is_valid_digit(char ch)
{
	return character_is_decimal_digit(ch) || character_is_uppercase_alphabet(ch) || character_is_lowercase_alphabet(ch);
}

/** @brief Checks whether an ASCII digit is supported by a number base */
INLINE_OR_STATIC bool digit_is_supported_by_base(char digit, int base)
{
	bool result = false;
	assert(base >= 2 && base <= 36);
	if (character_is_decimal_digit(digit)) {
		const int value = digit - '0';
		result = value < base;
	} else if (character_is_lowercase_alphabet(digit)) {
		const int value = digit - 'a' + 10;
		result = value < base;
	} else if (character_is_uppercase_alphabet(digit)) {
		const int value = digit - 'A' + 10;
		result = value < base;
	}
	return result;
}

/** @brief Converts an ASCII digit to its integer value */
INLINE_OR_STATIC int digit_to_integer(char digit)
{
	int integer = 0;
	assert(character_is_valid_digit(digit));
	if (character_is_decimal_digit(digit)) {
		integer = digit - '0';
	} else if (character_is_uppercase_alphabet(digit)) {
		integer = digit - 'A' + 10;
	} else if (character_is_lowercase_alphabet(digit)) {
		integer = digit - 'a' + 10;
	}
	return integer;
}

#endif
