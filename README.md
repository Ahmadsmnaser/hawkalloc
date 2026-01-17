# HawkAlloc 🦅  
A custom memory allocator implemented in C for Linux user-space.

HawkAlloc is a learning-focused low-level project that explores how dynamic memory allocation works under the hood, including heap management, block metadata, free lists, splitting, and coalescing.

> ⚠️ This allocator is **not intended to replace the system allocator**.  
> It is built for educational purposes and systems programming practice.

---

## ✨ Features

- Custom `malloc`, `free`, `calloc`, and `realloc` implementations
- Arena-based allocation using `mmap`
- Explicit block metadata (headers)
- Doubly-linked free list
- First-fit allocation strategy
- Block splitting
- **Forward coalescing** to reduce fragmentation
- Robust test suite + stress testing
- Written in pure C (Linux user-space)

---

## 🧠 Design Overview

### Memory Model
- Memory is obtained from the OS using a single **arena** allocated via `mmap`
- The arena is divided into blocks
- Each block contains:
  - A header (`BlockMemory`)
  - A payload returned to the user

### Free List
- Only **free blocks** are stored in the free list
- The free list is doubly linked
- Allocated blocks are removed from the list

### Allocation Strategy
- **First-fit** search over the free list
- If a free block is significantly larger than requested:
  - It is **split** into:
    - An allocated block
    - A smaller free block

### Freeing & Coalescing
- Freed blocks are reinserted into the free list
- **Forward coalescing**:
  - If the next adjacent block in memory is free, the blocks are merged
- Arena bounds are checked to prevent invalid memory access

> Backward coalescing (via boundary tags) is intentionally left as a future improvement.

---

## 🧪 Testing

### Unit Tests
Located in the `tests/` directory:

- `test_malloc_basic`
- `test_malloc_zero`
- `test_free_null`
- `test_calloc_zeroed`
- `test_realloc_null`
- `test_realloc_to_zero`
- `test_realloc_grow_preserves`
- `test_realloc_shrink_preserves_prefix`

Each test is a standalone C program that validates one specific behavior.

---

### Stress Test (v2)
`stress_test_v2.c` performs:
- 10,000 allocations with random sizes
- Randomized freeing
- Re-allocation into freed slots
- Pattern writing & verification (detects memory corruption)
- Final full cleanup

✔️ All phases pass without crashes or corruption.
