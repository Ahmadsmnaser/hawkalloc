#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
// tests/stress_test_v2.c

#include "../include/hawkalloc.h"

#define NUM_ALLOCS 10000
#define MIN_SIZE 1
#define MAX_SIZE 4096

static uint8_t pattern_a(int i) { return (uint8_t)((i * 131) ^ 0xA5); }
static uint8_t pattern_b(int i) { return (uint8_t)((i * 73) ^ 0x5A); }

static void write_pattern(void *p, size_t sz, int tag)
{
    uint8_t *b = (uint8_t *)p;
    b[0] = pattern_a(tag);
    if (sz > 1)
        b[sz - 1] = pattern_b(tag);
}

static int check_pattern(void *p, size_t sz, int tag)
{
    uint8_t *b = (uint8_t *)p;
    if (b[0] != pattern_a(tag))
        return 0;
    if (sz > 1 && b[sz - 1] != pattern_b(tag))
        return 0;
    return 1;
}

static size_t rand_size(void)
{
    return (size_t)(rand() % (MAX_SIZE - MIN_SIZE + 1)) + MIN_SIZE;
}

static void shuffle_ints(int *arr, int n)
{
    for (int i = n - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

int main(int argc, char **argv)
{
    unsigned seed = (unsigned)time(NULL);
    if (argc >= 2)
        seed = (unsigned)strtoul(argv[1], NULL, 10);
    srand(seed);

    printf("stress_test_v2: seed=%u\n", seed);

    void *ptrs[NUM_ALLOCS];
    size_t sizes[NUM_ALLOCS];

    // Phase 1: allocations + pattern
    for (int i = 0; i < NUM_ALLOCS; ++i)
    {
        sizes[i] = rand_size();
        ptrs[i] = ha_malloc(sizes[i]);
        if (!ptrs[i])
        {
            printf("FAIL: allocation failed at i=%d size=%zu\n", i, sizes[i]);
            return 1;
        }
        write_pattern(ptrs[i], sizes[i], i);
    }
    printf("Phase 1 OK: %d allocations\n", NUM_ALLOCS);

    int idx[NUM_ALLOCS];
    for (int i = 0; i < NUM_ALLOCS; ++i)
        idx[i] = i;
    shuffle_ints(idx, NUM_ALLOCS);

    int half = NUM_ALLOCS / 2;

    // Phase 2: free random half (with verification)
    for (int k = 0; k < half; ++k)
    {
        int i = idx[k];

        if (!check_pattern(ptrs[i], sizes[i], i))
        {
            printf("FAIL: pattern corrupted BEFORE free at i=%d size=%zu\n", i, sizes[i]);
            return 2;
        }

        ha_free(ptrs[i]);
        ptrs[i] = NULL;
        sizes[i] = 0;
    }
    printf("Phase 2 OK: freed %d blocks (random)\n", half);

    // Phase 3: re-allocate into freed slots + pattern again
    for (int k = 0; k < half; ++k)
    {
        int i = idx[k];

        sizes[i] = rand_size();
        ptrs[i] = ha_malloc(sizes[i]);
        if (!ptrs[i])
        {
            printf("FAIL: re-allocation failed at i=%d size=%zu\n", i, sizes[i]);
            return 3;
        }
        write_pattern(ptrs[i], sizes[i], i + 100000);
    }
    printf("Phase 3 OK: re-allocated %d blocks\n", half);

    // Phase 4: verify all live blocks then free all
    for (int i = 0; i < NUM_ALLOCS; ++i)
    {
        if (!ptrs[i])
            continue;

        int tag = (i >= 0 && sizes[i] > 0) ? i : i;
        (void)tag;
    }

    uint8_t was_realloc[NUM_ALLOCS] = {0};
    for (int k = 0; k < half; ++k)
        was_realloc[idx[k]] = 1;

    for (int i = 0; i < NUM_ALLOCS; ++i)
    {
        if (!ptrs[i])
            continue;

        int tag = was_realloc[i] ? (i + 100000) : i;
        if (!check_pattern(ptrs[i], sizes[i], tag))
        {
            printf("FAIL: pattern corrupted BEFORE final free at i=%d size=%zu\n", i, sizes[i]);
            return 4;
        }

        ha_free(ptrs[i]);
        ptrs[i] = NULL;
        sizes[i] = 0;
    }

    printf("Phase 4 OK: verified + freed all blocks\n");
    printf("SUCCESS \n");
    return 0;
}
