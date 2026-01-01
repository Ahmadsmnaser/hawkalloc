#include <stdio.h>
#include <stdlib.h>
#include "../include/hawkalloc.h"

//test_free_null.c
int main(){
    ha_free(NULL);
    printf("ha_free(NULL) executed without crashing.\n");
    return 0;
}