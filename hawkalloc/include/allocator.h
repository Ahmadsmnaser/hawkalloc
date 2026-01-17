#ifndef HAWKALLOC_ALLOCATOR_H
#define HAWKALLOC_ALLOCATOR_H

#include <stddef.h>
#include <stdbool.h>

// Block memory structure
typedef struct BlockMemory {
    size_t size;                 // Size of the memory block in bytes
    bool is_free;                // Flag indicating if the block is free or allocated
    struct BlockMemory* next_free;   // Pointer to the next memory block in the list
    struct BlockMemory* prev_free;   // Pointer to the previous memory block in the list
} BlockMemory;

extern BlockMemory *free_list_header; // Head of the free list
extern char* arena_start; // Start of the memory arena
extern char* arena_end; // End of the memory arena

void init_allocator(size_t total_size);
BlockMemory *find_first_fit(size_t requested_size);
void split_block(BlockMemory *block, size_t requested_size);
void remove_from_free_list(BlockMemory *block);

#endif // HAWKALLOC_ALLOCATOR_H
