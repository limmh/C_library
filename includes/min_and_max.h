#ifndef MIN_AND_MAX_H
#define MIN_AND_MAX_H

#include "fixed_width_integer_types.h"
#include "inline_or_static.h"

INLINE_OR_STATIC
char min_char(char a, char b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
char max_char(char a, char b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
signed char min_schar(signed char a, signed char b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
signed char max_schar(signed char a, signed char b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
unsigned char min_uchar(unsigned char a, unsigned char b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
unsigned char max_uchar(unsigned char a, unsigned char b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
short min_short(short a, short b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
short max_short(short a, short b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
unsigned short min_ushort(unsigned short a, unsigned short b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
unsigned short max_ushort(unsigned short a, unsigned short b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
int min_int(int a, int b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
int max_int(int a, int b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
unsigned int min_uint(unsigned int a, unsigned int b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
unsigned int max_uint(unsigned int a, unsigned int b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
long min_long(long a, long b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
long max_long(long a, long b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
unsigned long min_ulong(unsigned long a, unsigned long b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
unsigned long max_ulong(unsigned long a, unsigned long b)
{
	return (a > b) ? a : b;
}

#if defined(LLONG_MIN) && defined(LLONG_MAX)

INLINE_OR_STATIC
long long min_llong(long long a, long long b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
long long max_llong(long long a, long long b)
{
	return (a > b) ? a : b;
}

#endif

#if defined(ULLONG_MAX)

INLINE_OR_STATIC
unsigned long long min_ullong(unsigned long long a, unsigned long long b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
unsigned long long max_ullong(unsigned long long a, unsigned long long b)
{
	return (a > b) ? a : b;
}

#endif

INLINE_OR_STATIC
int8_t min_i8(int8_t a, int8_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
int8_t max_i8(int8_t a, int8_t b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
uint8_t min_u8(uint8_t a, uint8_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
uint8_t max_u8(uint8_t a, uint8_t b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
int16_t min_i16(int16_t a, int16_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
int16_t max_i16(int16_t a, int16_t b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
uint16_t min_u16(uint16_t a, uint16_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
uint16_t max_u16(uint16_t a, uint16_t b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
int32_t min_i32(int32_t a, int32_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
int32_t max_i32(int32_t a, int32_t b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
uint32_t min_u32(uint32_t a, uint32_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
uint32_t max_u32(uint32_t a, uint32_t b)
{
	return (a > b) ? a : b;
}

#if defined(INT64_MIN) && defined(INT64_MAX)

INLINE_OR_STATIC
int64_t min_i64(int64_t a, int64_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
int64_t max_i64(int64_t a, int64_t b)
{
	return (a > b) ? a : b;
}

#endif

#if defined(UINT64_MAX)

INLINE_OR_STATIC
uint64_t min_u64(uint64_t a, uint64_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
uint64_t max_u64(uint64_t a, uint64_t b)
{
	return (a > b) ? a : b;
}

#endif

INLINE_OR_STATIC
ptrdiff_t min_ptrdiff(ptrdiff_t a, ptrdiff_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
ptrdiff_t max_ptrdiff(ptrdiff_t a, ptrdiff_t b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
size_t min_size(size_t a, size_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
size_t max_size(size_t a, size_t b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
intptr_t min_intptr(intptr_t a, intptr_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
intptr_t max_intptr(intptr_t a, intptr_t b)
{
	return (a > b) ? a : b;
}

INLINE_OR_STATIC
uintptr_t min_uintptr(uintptr_t a, uintptr_t b)
{
	return (a < b) ? a : b;
}

INLINE_OR_STATIC
uintptr_t max_uintptr(uintptr_t a, uintptr_t b)
{
	return (a > b) ? a : b;
}

#endif
