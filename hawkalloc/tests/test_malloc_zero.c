#include <stdio.h>
#include <stdlib.h>
#include "../include/hawkalloc.h"

//test_malloc_zero.c
int main(){
    int *ptr;
    ptr = (int *) ha_malloc(0);
    if (ptr == NULL){
        printf("ha_malloc with zero size returned NULL pointer as expected.\n");
        return 0;}
        else{
            printf("ha_malloc with zero size did not return NULL pointer.\n");
            ha_free(ptr);
            return 1;
        }
}