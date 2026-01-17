#include <stdio.h>
#include <stdlib.h>
#include "../include/hawkalloc.h"
//tests/stress_test.c

int main(){
    int const num_allocs = 10000;
    void* ptrs[num_allocs];

    for(int i = 0; i < num_allocs; i++){
        size_t size = rand() % 512 + 1; // Random size between 1 and 256 bytes
        ptrs[i] = ha_malloc(size);
        if(ptrs[i] == NULL){
            printf("Allocation failed at iteration %d\n", i);
            return 1;   
        }
    }
    printf("All allocations successful.\n");


    for(int i = 0; i < num_allocs/2; i++){
        ha_free(ptrs[i]);
    }
    printf("Freed first half of allocations.\n");

    for(int i = 0; i < num_allocs/2; i++){
        size_t size = rand() % 512 + 1; // Random size between 1 and 512 bytes
        ptrs[i] = ha_malloc(size);
        if(ptrs[i] == NULL){
            printf("Re-allocation failed at iteration %d\n", i);
            return 1;   
        }
    }
    printf("All re-allocations successful.\n");
    
    for(int i = 0; i < num_allocs; i++){
        ha_free(ptrs[i]);
    }

    printf("All memory blocks freed successfully.\n");
    return 0;
}