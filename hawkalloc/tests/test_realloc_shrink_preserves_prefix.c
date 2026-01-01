#include <stdio.h>
#include <stdlib.h>
#include "../include/hawkalloc.h"

//test_realloc_shrink_preserves_prefix.c
int main(){
    int *ptr;
    ptr = (int *)ha_malloc(10*sizeof(int));
    if (ptr == NULL){
        return 1;
    }
    printf("Memory allocated using ha_malloc.\n");
    printf("Changing values...\n");
    for (int i = 0; i < 10; i++){
        ptr[i] = i;
        printf("After changing the value : ptr[%d] = %d\n", i, ptr[i]);
    }
    printf("Reallocating memory to a smaller size using ha_realloc...\n");
    int *new_ptr;
    new_ptr = (int *)ha_realloc(ptr, 5*sizeof(int));
    if (new_ptr == NULL){
        ha_free(ptr);
        return 1;
    }
    printf("Verifying that the prefix data is preserved after shrinking...\n");
    for (int i = 0; i < 5; i++){
        if (new_ptr[i] != i){
            printf("Data mismatch at index %d: expected %d, got %d\n", i, i, new_ptr[i]);
            ha_free(new_ptr);
            return 1;
        }
        printf("Data at index %d is correct: %d\n", i, new_ptr[i]);
    }
    printf("Freeing memory...\n");
    ha_free(new_ptr);
    printf("Memory freed successfully.\n");
    return 0;
}