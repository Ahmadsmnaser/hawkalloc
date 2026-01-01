This document defines the expected behavior of HawkAlloc’s public allocation functions, including edge cases.


Function Behavior:

malloc(size):
- If size == 0, the function returns NULL.
- Otherwise, it returns a pointer to a memory block of at least size bytes, or NULL on failure.

free(ptr):
- If ptr is NULL, no action is performed.
- Otherwise, the memory block pointed to by ptr is released back to the allocator.

realloc(ptr, size):
- If ptr is NULL, the call behaves like malloc(size).
- If size == 0, the call behaves like free(ptr) and returns NULL.
- Otherwise, a new block of memory is allocated, the existing data is preserved up to the minimum of the old and new sizes, and the old block is freed.

calloc(num, size):
- Allocates memory for num * size bytes.
- All allocated bytes are initialized to zero.


Notes
- Each free block is linked into a free list using pointers stored in the block header.
- These behaviors are chosen for clarity and consistency rather than strict standard compliance.
- Error handling follows a fail-fast approach, returning NULL on allocation failure.