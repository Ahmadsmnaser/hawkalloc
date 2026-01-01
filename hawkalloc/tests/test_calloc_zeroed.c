#include <stdio.h>
#include <stdlib.h>
#include "../include/hawkalloc.h"
//test_calloc_zeroed.c
int main()
{
    int *ptr;
    ptr = (int *)ha_calloc(10, sizeof(int));
    printf("The address of allocated memory: %p\n", (void *)ptr);
    if (ptr == NULL)
    {
        return 1;
    }
    printf("Memory allocated using ha_calloc.\n");
    printf("Verfiying that memory is zeroed...\n");
    for (int i = 0; i < 10; i++)
    {
        if (ptr[i] != 0)
        {
            printf("Memory not zeroed at index %d\n", i);
            ha_free(ptr);
            return 1;
        }
    }
    printf("All memory is zeroed.\n");
    printf("Changing values...\n");
    for (int i = 0; i < 10; i++)
    {
        ptr[i] = i;
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }
    printf("Freeing memory...\n");
    ha_free(ptr);
    printf("Memory freed successfully.\n");
    return 0;
}