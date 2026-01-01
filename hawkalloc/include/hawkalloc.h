#include <stddef.h>

// Hawk Memory Allocator Interface

/*
 * Allocates a block of memory of at least size bytes. 
 * Returns a pointer to a memory block or NULL on failure
 * The returned memory is uninitialized
 * If bytes is 0, ha_malloc returns NULL
*/
 void* ha_malloc(size_t bytes);

/*
 * Reallocates the given block of memory to a new size.
 * Returns a pointer to the reallocated memory block, or NULL on failure.
 * The contents will be unchanged up to the minimum of the old and new sizes.
 * If the reallocation is successful, the existing data is preserved up to the minimum of the old and new sizes, and the old block is freed.
 * If ptr is NULL, the call behaves like malloc(size).
 * If size == 0, the call behaves like free(ptr) and returns NULL.
*/
 void *ha_realloc(void *ptr, size_t new_size);

/*
 * Allocates memory for an array of num elements of size bytes
 * The memory is set to zero
 * Returns a pointer to the allocated memory, or NULL on failure
 * If num or size is 0, ha_calloc returns NULL
*/
 void *ha_calloc(size_t num, size_t size);

/*
 * Realigns the given block of memry back to the allocator
 * If ptr is NULL, no operation is performed
*/
 void ha_free(void *ptr);
