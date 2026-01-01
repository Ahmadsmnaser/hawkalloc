#include <stdio.h>
#include <stdlib.h>
#include "../include/hawkalloc.h"

//test_realloc_grow_preserves.c
int main(){
    int *ptr;
    ptr = (int *)ha_malloc(5 * sizeof(int));
    if (ptr == NULL)
    {
        return 1;
    }
    printf("Memory allocated using ha_malloc.\n");
    printf("Setting values...\n");
    for (int i = 0; i < 5; i++)
    {
        ptr[i] = i + 1;
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }
    printf("Reallocating memory to hold 10 integers...\n");
    int *new_ptr = (int *)ha_realloc(ptr, 10 * sizeof(int));
    if (new_ptr == NULL)
    {
        ha_free(ptr);
        return 1;
    }
    ptr = new_ptr;
    printf("Verifying preserved values...\n");
    for (int i = 0; i < 5; i++)
    {
        if (ptr[i] != i + 1)
        {
            printf("Value mismatch at index %d: expected %d, got %d\n", i, i + 1, ptr[i]);
            ha_free(ptr);
            return 1;
        }
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }
    printf("All preserved values are correct.\n");
    printf("Freeing memory...\n");
    ha_free(ptr);
    printf("Memory freed successfully.\n");
    return 0;
}