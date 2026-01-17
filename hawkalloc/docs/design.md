Overview

This document describes the design decisions behind HawkAlloc, a custom memory allocator implemented in C for Linux user-space.

The goal of this project is to understand and experiment with core memory management concepts such as heap organization, block metadata, free list management, fragmentation, and multithreaded safety.

This project is part of a personal series focused on diving deeper into operating systems concepts, improving low-level programming skills, and exploring systems design in a hands-on manner.

This allocator is not intended to replace the system allocator.


Scope / Non-Goals

In Scope:
- Dynamic memory allocation concepts
- Use of mmap and munmap to obtain and release memory
- Management of heap memory in user space
- Understanding the relationship between stack and heap memory
- Basic allocator behaviors similar to malloc and free

Non-Goals:
- Full compatibility with the glibc allocator
- Kernel-level memory management
- Advanced performance optimizations
- NUMA-aware allocation strategies


Memory Source

This project uses mmap to allocate memory from the operating system.

The choice of mmap is motivated by the following reasons:
- Explicit control over allocated memory regions
- Ability to return memory directly back to the operating system
- Clear separation between allocator-managed memory and other process memory regions


Block Layout

Each allocated block consists of a header followed by a payload area returned to the user.

The block header stores metadata required by the allocator, including:
- Block size
- Allocation status (allocated/free)
- Pointers used to link free blocks

Payload memory is aligned to a fixed boundary to ensure correct behavior for common data types.


Allocation Strategy

When a memory request is received, the allocator searches its free list for a suitable block.

The following strategy is used:
- First-fit search through the free list
- If a free block is larger than requested, it may be split
- If no suitable block is found, a new arena is allocated


Freeing and Coalescing

When a block is freed:
- It is marked as free
- It is inserted back into the free list
- Adjacent free blocks may be merged to reduce fragmentation
- (Current) forward coalescing only - does not coalesce with previous block (planned with the next edit)

Coalescing is performed eagerly to improve long-term memory reuse.