#include "../include/allocator.h"
#include <sys/mman.h>

#ifndef MMAP_ANON_FLAG
#  if defined(MAP_ANONYMOUS)
#    define MMAP_ANON_FLAG MAP_ANONYMOUS
#  elif defined(MAP_ANON)
#    define MMAP_ANON_FLAG MAP_ANON
#  else
#    define MMAP_ANON_FLAG 0
#  endif
#endif


BlockMemory *free_list_header = NULL;
size_t min_payload = 16;

void remove_from_free_list(BlockMemory *block)
{
    if (block->prev_free != NULL)
    {
        block->prev_free->next_free = block->next_free;
    }
    else
    {
        free_list_header = block->next_free;
    }
    if (block->next_free != NULL)
    {
        block->next_free->prev_free = block->prev_free;
    }
}

void replace_in_free_list(BlockMemory *old_block, BlockMemory *new_block)
{
    new_block->next_free = old_block->next_free;
    new_block->prev_free = old_block->prev_free;
    if (old_block->next_free != NULL)
    {
        old_block->next_free->prev_free = new_block;
    }
    if (old_block->prev_free != NULL)
    {
        old_block->prev_free->next_free = new_block;
    }
    else
    {
        free_list_header = new_block;
    }
}

/*
 * Verfing that the free list is null
 * If it is null, we request a memory block from the OS (64KB)
 * Using mmap to allocate a block of memory of size total_size
 * initalizing the free list with a single block of memory
 */
void init_allocator(size_t total_size)
{
    if (free_list_header == NULL)
    {
        void *ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MMAP_ANON_FLAG, -1, 0);
        if (ptr == MAP_FAILED)
        {
            return;
        }
        free_list_header = (BlockMemory *)ptr;
        free_list_header->size = total_size - sizeof(BlockMemory);
        free_list_header->is_free = true;
        free_list_header->next_free = NULL;
        free_list_header->prev_free = NULL;
    }
    else
    {
        return;
    }
}
/*
 * Itarates through the free list
 * Finding the first block that is larger than or equal to the requested size
 * Calling split_block if the block is much larger than the requested size
 * Marking the block as allocated and deleting it from the free list
 * Returns a pointer to that block
 */
BlockMemory *find_first_fit(size_t requested_size)
{
    BlockMemory *current = free_list_header;
    while (current != NULL)
    {
        if (current->size >= requested_size)
        {
            if (min_payload + sizeof(BlockMemory) <= current->size - requested_size)
            {
                split_block(current, requested_size);
            }
            current->is_free = false;
            // Remove from free list
            remove_from_free_list(current);
            return current;
        }
        else
        {
            current = current->next_free;
        }
    }
    return NULL;
}

/*
 * Splits a block of memory into two blocks
 * Verfing that the block is larger than the requested size
 * If it is, we split the block into two blocks
 * The fisrt block is of the requested size and marked as allocated
 * The second block is the remaining size and marked as free
 * Adding the second block back to the free list
 * Updating the size of the first block
 */
void split_block(BlockMemory *block, size_t requested_size){
    if(min_payload + sizeof(BlockMemory) <= block->size - requested_size){
        BlockMemory *new_block = (BlockMemory *)((char *)block + sizeof(BlockMemory) + requested_size);
        new_block->size = block->size - requested_size - sizeof(BlockMemory);
        new_block->is_free = true;
        // Replace block in free list with new_block
        replace_in_free_list(block, new_block);
        block->next_free = NULL;
        block->prev_free = NULL;
        block->size = requested_size;
    }else{
        return;
    }
}

