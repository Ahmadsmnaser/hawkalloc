#include "../include/allocator.h"

// /* Definitions for the arena bounds referenced across the allocator.
//  * These are declared `extern` in include/allocator.h and must have
//  * a single definition in one translation unit to satisfy the linker.
//  */
char *arena_start = NULL;
char *arena_end = NULL;
