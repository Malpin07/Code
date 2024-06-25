#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
int* men(int i){
    int* arr;
    arr=malloc(i*sizeof(int));
    for (int j=0;j<i;j++){
        printf("输入第%d个数:",j+1);
        scanf("%d",&arr[j]);
    }
    return arr;
}

int fr(int **p){
    if(NULL==*p){
        free(*p);
        *p=NULL;
    }
    printf("释放\n");
}