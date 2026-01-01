#include <stdio.h>
#include <stdlib.h>
#include "../include/hawkalloc.h"

// test_realloc_to_zero.c
int main()
{
    int *ptr;
    ptr = (int *)ha_malloc(10 * sizeof(int));
    printf("Memory allocated using ha_malloc.\n");
    printf("Using ha_realloc to resize to zero...\n");
    ptr = (int *)ha_realloc(ptr, 0);
    if (ptr != NULL)
    {
        printf("ha_realloc to zero size did not return NULL pointer.\n");
        return 1;
    }
    else
    {
        printf("ha_realloc to zero size returned NULL pointer as expected.\n");
        return 0;
    }
}