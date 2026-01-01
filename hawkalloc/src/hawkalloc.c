#include <stdlib.h>
#include <stddef.h>
#include "../include/hawkalloc.h"
#include "../include/allocator.h"

#define ARENA_SIZE 64 * 1024 // 64KB

void *ha_malloc(size_t bytes)
{
    if (bytes == 0)
    {
        return NULL;
    }
    if (free_list_header == NULL)
    {
        init_allocator(ARENA_SIZE); // Initialize with 64KB
    }
    BlockMemory *block = find_first_fit(bytes);
    if (block == NULL)
    {
        return NULL;
    }
    return (void *)((char *)block + sizeof(BlockMemory));
}

void *ha_realloc(void *ptr, size_t new_size)
{
    if (ptr == NULL)
    {
        return ha_malloc(new_size);
    }
    if (new_size == 0)
    {
        ha_free(ptr);
        return NULL;
    }
    BlockMemory *block = (BlockMemory *)((char *)ptr - sizeof(BlockMemory));
    size_t old_size = block->size;
    size_t min;
    if (old_size < new_size)
    {
        min = old_size;
    }
    else
    {
        min = new_size;
    }
    void *new_ptr = ha_malloc(new_size);
    if (new_ptr == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < min; i++)
    {
        ((char *)new_ptr)[i] = ((char *)ptr)[i];
    }
    ha_free(ptr);
    return new_ptr;
}

void *ha_calloc(size_t num, size_t size)
{
    if (num == 0 || size == 0 || ((num > __SIZE_MAX__ / size) && size != 0))
    {
        return NULL;
    }
    size_t total_size = num * size;
    void *ptr = ha_malloc(total_size);
    if (ptr == NULL)
    {
        return NULL;
    }
    // Initialize allocated memory to zero
    for (size_t i = 0; i < total_size; i++)
    {
        ((char *)ptr)[i] = 0;
    }
    return ptr;
}

void ha_free(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    BlockMemory *block = (BlockMemory *)((char *)ptr - sizeof(BlockMemory));
    block->is_free = true;
    // Add the block back to the free list
    BlockMemory *current = free_list_header;
    if (current == NULL)
    {
        free_list_header = block;
        block->next_free = NULL;
        block->prev_free = NULL;
        return;
    }
    else
    {
        block->next_free = current;
        block->prev_free = NULL;
        current->prev_free = block;
        free_list_header = block;
        return;
    }
}