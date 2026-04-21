#ifndef STATIC_POOL_H
#define STATIC_POOL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Static pool type (Only for testing, only a chunk of memory can be occupied at a time) */
struct static_pool_type {
	size_t index_of_chunk_occupied;
	unsigned char chunk10[512];
	unsigned char chunk9[256];
	unsigned char chunk8[128];
	unsigned char chunk7[64];
	unsigned char chunk6[32];
	unsigned char chunk5[16];
	unsigned char chunk4[8];
	unsigned char chunk3[4];
	unsigned char chunk2[2];
	unsigned char chunk1[1];
	unsigned char zero_padding;
};

typedef struct static_pool_type static_pool_type;

/**
 * @brief Allocates a block of memory from a static pool
 * @param [in, out] pool A pointer to a static pool instance
 * @param [in] number_of_bytes Number of bytes requested
 * @return void * A pointer to the block of memory requested. Null pointer if the requested failed.
 */
void *static_pool_allocate(static_pool_type *pool, size_t number_of_bytes);

/**
 * @brief Reallocates memory from a static pool
 * @param [in, out] pool A pointer to a static pool instance
 * @param [in] ptr A pointer to a block of previously allocated memory
 * @param [in] new_size New number of bytes requested
 * @return void * A pointer to the new block of memory requested.
 *                Can be the same as or different from the previously allocated block of memory.
 *                If reallocation failed, the return pointer is NULL.
 */
void *static_pool_reallocate(static_pool_type *pool, void *ptr, size_t new_size);

/**
 * @brief Deallocates memory from a static pool
 * @param [in, out] pool A pointer to a static pool instance
 * @param [in] ptr A pointer to a block of previously allocated memory
 */
void static_pool_deallocate(static_pool_type *pool, void *ptr);

/**
 * @brief Gets the largest chunk size of the static pool type
 * @return size_t The largest chunk size
 */
size_t static_pool_largest_chunk_size(void);

#ifdef __cplusplus
}
#endif

#endif
