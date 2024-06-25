#include "io.h"
#include "mem.h"
#include <stdio.h>


int* sca(int i,int* f(int )){
    int* p=f(i);

    for (int j = 0; j < i; ++j) {
        printf("%d,",p[j]);
    }
    printf("\n*************\n");
    return p;
}

void pri(int * p,int i){
    for (int j = 0; j < i; ++j) {
        printf("%d,",p[j]);
    }
    printf("\n");
}