#include <stdio.h>
#include <stdlib.h>
#include "../include/hawkalloc.h"

//test_realloc_null.c
int main(){
    int *ptr;
    ptr = (int *)ha_realloc(NULL, 10*sizeof(int));
    if (ptr == NULL){
        return 1;
    }
    printf("Memory allocated using ha_realloc with NULL pointer.\n");
    printf("Changing values...\n");
    for (int i = 0; i < 10; i++){
        printf("Before changing the value : ptr[%d] = %d\n", i, ptr[i]);
        ptr[i] = i;
        printf("After changing the value : ptr[%d] = %d\n", i, ptr[i]);
    }
    printf("Freeing memory...\n");
    ha_free(ptr);
    printf("Memory freed successfully.\n");
    return 0;
}