#ifndef DEBUG_MODE_INTEGER_H
#define DEBUG_MODE_INTEGER_H

#include "safer_integer.h"
#include "fixed_width_integer_types.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INTEGER_RESULT_MODE_DEFAULT 0
#define INTEGER_RESULT_MODE_WRAPAROUND 1
#define INTEGER_RESULT_MODE_SATURATION 2

/**
 * @brief Sets the output file pointer
 * @param [in] file_pointer New file pointer
 * @return FILE * The previous file pointer
 */
FILE *debug_mode_integer_set_output_file(FILE *file_pointer); /* return previous output file */

/** @brief integer operation type */
typedef enum integer_operation_type
{
	integer_operation_unsupported = 0,
	integer_operation_addition,
	integer_operation_subtraction,
	integer_operation_multiplication,
	integer_operation_division,
	integer_operation_remainder
} integer_operation_type;

/** @brief integer operation result mode */
typedef enum integer_result_mode_type
{
	integer_result_mode_default = INTEGER_RESULT_MODE_DEFAULT,
	integer_result_mode_wraparound = INTEGER_RESULT_MODE_WRAPAROUND,
	integer_result_mode_saturation = INTEGER_RESULT_MODE_SATURATION
} integer_result_mode_type;

/** @brief int debug information */
typedef struct int_debug_info_type
{
	const char *file_name;
	const char *operand1_name;
	const char *operand2_name;
	int operand1;
	int operand2;
	int result;
	int minimum_value;
	int maximum_value;
	int line_number;
	integer_operation_type operation;
	integer_result_mode_type result_mode;
	integer_operation_error_type error;
} int_debug_info_type;

/** @brief int debug handler */
typedef void (*int_debug_handler_type)(const int_debug_info_type*);

/**
 * @brief Sets the int debug handler
 * @param [in] handler New int debug handler
 * @return int_debug_handler_type The previous int debug handler
 */
int_debug_handler_type debug_mode_int_set_handler(int_debug_handler_type handler);

/** @brief Resets the int debug handler */
void debug_mode_int_reset_handler(void);

/**
 * @brief Adds two int operands. If integer overflow is detected, reports the error.
 * @param [in] a Operand 1
 * @param [in] b Operand 2
 * @param [in] result_mode Result mode
 * @param [in] a_name Name of operand 1
 * @param [in] b_name Name of operand 2
 * @param [in] file_name Name of source file
 * @param [in] line_number Line where the function is called
 * @return int
 */
int debug_mode_int_add(int a, int b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/**
 * @brief Subtracts an int operand from an int operand. If integer oveflow is detected, reports the error.
 * @param [in] a Operand 1
 * @param [in] b Operand 2
 * @param [in] result_mode Result mode
 * @param [in] a_name Name of operand 1
 * @param [in] b_name Name of operand 2
 * @param [in] file_name Name of source file
 * @param [in] line_number Line where the function is called
 * @return int
 */
int debug_mode_int_minus(int a, int b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/**
 * @brief Multiplies two int operands. If integer overflow is detected, reports the error.
 * @param [in] a Operand 1
 * @param [in] b Operand 2
 * @param [in] result_mode Result mode
 * @param [in] a_name Name of operand 1
 * @param [in] b_name Name of operand 2
 * @param [in] file_name Name of source file
 * @param [in] line_number Line where the function is called
 * @return int
 */
int debug_mode_int_multiply(int a, int b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/**
 * @brief Divides an int operand by an int operand. If integer overflow or division by zero is detected, reports the error.
 * @param [in] a Operand 1
 * @param [in] b Operand 2
 * @param [in] result_mode Result mode
 * @param [in] a_name Name of operand 1
 * @param [in] b_name Name of operand 2
 * @param [in] file_name Name of source file
 * @param [in] line_number Line where the function is called
 * @return int
 */
int debug_mode_int_divide(int a, int b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/**
 * @brief Returns the remainder when an int operand is divided by an int operand.
 * If integer overflow or division by zero is detected, reports the error.
 * @param [in] a Operand 1
 * @param [in] b Operand 2
 * @param [in] result_mode Result mode
 * @param [in] a_name Name of operand 1
 * @param [in] b_name Name of operand 2
 * @param [in] file_name Name of source file
 * @param [in] line_number Line where the function is called
 * @return int
 */
int debug_mode_int_remainder(int a, int b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/** @brief unsigned int debug information */
typedef struct uint_debug_info_type
{
	const char *file_name;
	const char *operand1_name;
	const char *operand2_name;
	unsigned int operand1;
	unsigned int operand2;
	unsigned int result;
	unsigned int minimum_value;
	unsigned int maximum_value;
	int line_number;
	integer_operation_type operation;
	integer_result_mode_type result_mode;
	integer_operation_error_type error;
} uint_debug_info_type;

/** @brief unsigned int debug handler */
typedef void (*uint_debug_handler_type)(const uint_debug_info_type*);

/**
 * @brief Sets the unsigned int debug handler
 * @param [in] handler New unsigned int debug handler
 * @return uint_debug_handler_type The previous unsigned int debug handler
 */
uint_debug_handler_type debug_mode_uint_set_handler(uint_debug_handler_type handler); /* returns the previous handler */

/** @brief Resets the int debug handler */
void debug_mode_uint_reset_handler(void);

/**
 * @brief Adds two unsigned int operands. If the result wraps around, report the behavior.
 * @param [in] a Operand 1
 * @param [in] b Operand 2
 * @param [in] result_mode Result mode
 * @param [in] a_name Name of operand 1
 * @param [in] b_name Name of operand 2
 * @param [in] file_name Name of source file
 * @param [in] line_number Line where the function is called
 * @return unsigned int
 */
unsigned int debug_mode_uint_add(unsigned int a, unsigned int b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/**
 * @brief Subtracts an unsigned int operand from an unsigned int operand. If the result wraps around, report the behavior.
 * @param [in] a Operand 1
 * @param [in] b Operand 2
 * @param [in] result_mode Result mode
 * @param [in] a_name Name of operand 1
 * @param [in] b_name Name of operand 2
 * @param [in] file_name Name of source file
 * @param [in] line_number Line where the function is called
 * @return unsigned int
 */
unsigned int debug_mode_uint_minus(unsigned int a, unsigned int b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/**
 * @brief Multiplies two unsigned int operands. If the result wraps around, report the behavior.
 * @param [in] a Operand 1
 * @param [in] b Operand 2
 * @param [in] result_mode Result mode
 * @param [in] a_name Name of operand 1
 * @param [in] b_name Name of operand 2
 * @param [in] file_name Name of source file
 * @param [in] line_number Line where the function is called
 * @return unsigned int
 */
unsigned int debug_mode_uint_multiply(unsigned int a, unsigned int b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/**
 * @brief Divides an unsigned int operand by an unsigned int operand. If division by zero is detected, report the error.
 * @param [in] a Operand 1
 * @param [in] b Operand 2
 * @param [in] result_mode Result mode
 * @param [in] a_name Name of operand 1
 * @param [in] b_name Name of operand 2
 * @param [in] file_name Name of source file
 * @param [in] line_number Line where the function is called
 * @return unsigned int
 */
unsigned int debug_mode_uint_divide(unsigned int a, unsigned int b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/**
 * @brief Returns the remainder when an unsigned int operand is divided by an unsigned int operand.
 * If division by zero is detected, report the error.
 * @param [in] a Operand 1
 * @param [in] b Operand 2
 * @param [in] result_mode Result mode
 * @param [in] a_name Name of operand 1
 * @param [in] b_name Name of operand 2
 * @param [in] file_name Name of source file
 * @param [in] line_number Line where the function is called
 * @return unsigned int
 */
unsigned int debug_mode_uint_remainder(unsigned int a, unsigned int b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/** @brief long int debug information */
typedef struct long_debug_info_type
{
	const char *file_name;
	const char *operand1_name;
	const char *operand2_name;
	long operand1;
	long operand2;
	long result;
	long minimum_value;
	long maximum_value;
	int line_number;
	integer_operation_type operation;
	integer_result_mode_type result_mode;
	integer_operation_error_type error;
} long_debug_info_type;

/** @brief long int debug handler */
typedef void (*long_debug_handler_type)(const long_debug_info_type*);

/** @brief Sets the long int debug handler */
long_debug_handler_type debug_mode_long_set_handler(long_debug_handler_type handler); /* returns the previous handler */

/** @brief Resets the long int debug handler */
void debug_mode_long_reset_handler(void);

/** @brief long int version of debug mode addition */
long debug_mode_long_add(long a, long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief long int version of debug mode subtraction */
long debug_mode_long_minus(long a, long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief long int version of debug mode multiplication */
long debug_mode_long_multiply(long a, long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief long int version of debug mode division */
long debug_mode_long_divide(long a, long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief long int version of debug mode remainder operation */
long debug_mode_long_remainder(long a, long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/** @brief unsigned long int debug information */
typedef struct ulong_debug_info_type
{
	const char *file_name;
	const char *operand1_name;
	const char *operand2_name;
	unsigned long operand1;
	unsigned long operand2;
	unsigned long result;
	unsigned long minimum_value;
	unsigned long maximum_value;
	int line_number;
	integer_operation_type operation;
	integer_result_mode_type result_mode;
	integer_operation_error_type error;
} ulong_debug_info_type;

/** @brief unsigned long int debug handler */
typedef void (*ulong_debug_handler_type)(const ulong_debug_info_type*);

/** @brief Sets the unsigned long int debug handler */
ulong_debug_handler_type debug_mode_ulong_set_handler(ulong_debug_handler_type handler); /* returns the previous handler */

/** @brief Resets the unsigned long int debug handler */
void debug_mode_ulong_reset_handler(void);

/** @brief unsigned long version of debug mode addition */
unsigned long debug_mode_ulong_add(unsigned long a, unsigned long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief unsigned long version of debug mode subtraction */
unsigned long debug_mode_ulong_minus(unsigned long a, unsigned long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief unsigned long version of debug mode multiplication */
unsigned long debug_mode_ulong_multiply(unsigned long a, unsigned long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief unsigned long version of debug mode division */
unsigned long debug_mode_ulong_divide(unsigned long a, unsigned long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief unsigned long version of debug mode remainder operation */
unsigned long debug_mode_ulong_remainder(unsigned long a, unsigned long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

#if defined(LLONG_MIN) && defined(LLONG_MAX)
/** @brief long long int debug handler */
typedef struct llong_debug_info_type
{
	const char *file_name;
	const char *operand1_name;
	const char *operand2_name;
	long long operand1;
	long long operand2;
	long long result;
	long long minimum_value;
	long long maximum_value;
	int line_number;
	integer_operation_type operation;
	integer_result_mode_type result_mode;
	integer_operation_error_type error;
} llong_debug_info_type;

/** @brief long long int debug handler */
typedef void (*llong_debug_handler_type)(const llong_debug_info_type*);

/** @brief Sets the long long int debug handler */
llong_debug_handler_type debug_mode_llong_set_handler(llong_debug_handler_type handler); /* returns the previous handler */

/** @brief Resets the long long int debug handler */
void debug_mode_llong_reset_handler(void);

/** @brief long long version of debug mode addition */
long long debug_mode_llong_add(long long a, long long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief long long version of debug mode subtraction */
long long debug_mode_llong_minus(long long a, long long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief long long version of debug mode multiplication */
long long debug_mode_llong_multiply(long long a, long long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief long long version of debug mode division */
long long debug_mode_llong_divide(long long a, long long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief long long version of debug mode remainder operation */
long long debug_mode_llong_remainder(long long a, long long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
#endif

#if defined(ULLONG_MAX)
/** @brief unsigned long long int debug handler */
typedef struct ullong_debug_info_type
{
	const char *file_name;
	const char *operand1_name;
	const char *operand2_name;
	unsigned long long operand1;
	unsigned long long operand2;
	unsigned long long result;
	unsigned long long minimum_value;
	unsigned long long maximum_value;
	int line_number;
	integer_operation_type operation;
	integer_result_mode_type result_mode;
	integer_operation_error_type error;
} ullong_debug_info_type;

/** @brief unsigned long long int debug handler */
typedef void (*ullong_debug_handler_type)(const ullong_debug_info_type*);

/** @brief Sets the long long int debug handler */
ullong_debug_handler_type debug_mode_ullong_set_handler(ullong_debug_handler_type handler); /* returns the previous handler */

/** @brief Resets the long long int debug handler */
void debug_mode_ullong_reset_handler(void);

/** @brief unsigned long long version of debug mode addition */
unsigned long long debug_mode_ullong_add(unsigned long long a, unsigned long long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief unsigned long long version of debug mode subtraction */
unsigned long long debug_mode_ullong_minus(unsigned long long a, unsigned long long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief unsigned long long version of debug mode multiplication */
unsigned long long debug_mode_ullong_multiply(unsigned long long a, unsigned long long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief unsigned long long version of debug mode division */
unsigned long long debug_mode_ullong_divide(unsigned long long a, unsigned long long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief unsigned long long version of debug mode remainder operation */
unsigned long long debug_mode_ullong_remainder(unsigned long long a, unsigned long long b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
#endif

/** @brief int8_t version of debug mode addition */
int8_t debug_mode_i8_add(int8_t a, int8_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int8_t version of debug mode subtraction */
int8_t debug_mode_i8_minus(int8_t a, int8_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int8_t version of debug mode multiplication */
int8_t debug_mode_i8_multiply(int8_t a, int8_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int8_t version of debug mode division */
int8_t debug_mode_i8_divide(int8_t a, int8_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int8_t version of debug mode remainder operation */
int8_t debug_mode_i8_remainder(int8_t a, int8_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/** @brief uint8_t version of debug mode addition */
uint8_t debug_mode_u8_add(uint8_t a, uint8_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint8_t version of debug mode subtraction */
uint8_t debug_mode_u8_minus(uint8_t a, uint8_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint8_t version of debug mode multiplication */
uint8_t debug_mode_u8_multiply(uint8_t a, uint8_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint8_t version of debug mode division */
uint8_t debug_mode_u8_divide(uint8_t a, uint8_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint8_t version of debug mode remainder operation */
uint8_t debug_mode_u8_remainder(uint8_t a, uint8_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/** @brief int16_t version of debug mode addition */
int16_t debug_mode_i16_add(int16_t a, int16_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int16_t version of debug mode subtraction */
int16_t debug_mode_i16_minus(int16_t a, int16_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int16_t version of debug mode multiplication */
int16_t debug_mode_i16_multiply(int16_t a, int16_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int16_t version of debug mode division */
int16_t debug_mode_i16_divide(int16_t a, int16_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int16_t version of debug mode remainder operation */
int16_t debug_mode_i16_remainder(int16_t a, int16_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/** @brief uint16_t version of debug mode addition */
uint16_t debug_mode_u16_add(uint16_t a, uint16_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint16_t version of debug mode subraction */
uint16_t debug_mode_u16_minus(uint16_t a, uint16_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint16_t version of debug mode multiplication */
uint16_t debug_mode_u16_multiply(uint16_t a, uint16_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint16_t version of debug mode division */
uint16_t debug_mode_u16_divide(uint16_t a, uint16_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint16_t version of debug mode remainder operation */
uint16_t debug_mode_u16_remainder(uint16_t a, uint16_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/** @brief int32_t version of debug mode addition */
int32_t debug_mode_i32_add(int32_t a, int32_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int32_t version of debug mode subtraction */
int32_t debug_mode_i32_minus(int32_t a, int32_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int32_t version of debug mode multiplication */
int32_t debug_mode_i32_multiply(int32_t a, int32_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int32_t version of debug mode division */
int32_t debug_mode_i32_divide(int32_t a, int32_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int32_t version of debug mode remainder operation */
int32_t debug_mode_i32_remainder(int32_t a, int32_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/** @brief uint32_t version of debug mode addition */
uint32_t debug_mode_u32_add(uint32_t a, uint32_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint32_t version of debug mode subtraction */
uint32_t debug_mode_u32_minus(uint32_t a, uint32_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint32_t version of debug mode multiplication */
uint32_t debug_mode_u32_multiply(uint32_t a, uint32_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint32_t version of debug mode division */
uint32_t debug_mode_u32_divide(uint32_t a, uint32_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint32_t version of debug mode remainder operation */
uint32_t debug_mode_u32_remainder(uint32_t a, uint32_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

#if defined(INT64_MIN) && defined(INT64_MAX)
/** @brief int64_t version of debug mode addition */
int64_t debug_mode_i64_add(int64_t a, int64_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int64_t version of debug mode subtraction */
int64_t debug_mode_i64_minus(int64_t a, int64_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int64_t version of debug mode multiplication */
int64_t debug_mode_i64_multiply(int64_t a, int64_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int64_t version of debug mode division */
int64_t debug_mode_i64_divide(int64_t a, int64_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief int64_t version of debug mode remainder operation */
int64_t debug_mode_i64_remainder(int64_t a, int64_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
#endif

#if defined(UINT64_MAX)
/** @brief uint64_t version of debug mode addition */
uint64_t debug_mode_u64_add(uint64_t a, uint64_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint64_t version of debug mode subtraction */
uint64_t debug_mode_u64_minus(uint64_t a, uint64_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint64_t version of debug mode multiplication */
uint64_t debug_mode_u64_multiply(uint64_t a, uint64_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint64_t version of debug mode division */
uint64_t debug_mode_u64_divide(uint64_t a, uint64_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief uint64_t version of debug mode remainder operation */
uint64_t debug_mode_u64_remainder(uint64_t a, uint64_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
#endif

/** @brief ptrdiff_t version of debug mode addition */
ptrdiff_t debug_mode_ptrdiff_add(ptrdiff_t a, ptrdiff_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief ptrdiff_t version of debug mode subtraction */
ptrdiff_t debug_mode_ptrdiff_minus(ptrdiff_t a, ptrdiff_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief ptrdiff_t version of debug mode multiplication */
ptrdiff_t debug_mode_ptrdiff_multiply(ptrdiff_t a, ptrdiff_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief ptrdiff_t version of debug mode division */
ptrdiff_t debug_mode_ptrdiff_divide(ptrdiff_t a, ptrdiff_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief ptrdiff_t version of debug mode remainder operation */
ptrdiff_t debug_mode_ptrdiff_remainder(ptrdiff_t a, ptrdiff_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

/** @brief size_t version of debug mode addition */
size_t debug_mode_size_add(size_t a, size_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief size_t version of debug mode subtraction */
size_t debug_mode_size_minus(size_t a, size_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief size_t version of debug mode multiplication */
size_t debug_mode_size_multiply(size_t a, size_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief size_t version of debug mode division */
size_t debug_mode_size_divide(size_t a, size_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);
/** @brief size_t version of debug mode remainder operation */
size_t debug_mode_size_remainder(size_t a, size_t b, integer_result_mode_type result_mode, const char *a_name, const char *b_name, const char *file_name, int line_number);

#ifdef __cplusplus
}
#endif

#endif
