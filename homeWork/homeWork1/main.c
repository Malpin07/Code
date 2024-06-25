#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "sort.h"
#include "mem.h"

int CONT=1;
int control(int a,int b){
    if (CONT==0){
        return a>b?1:0;
    } else
    return a<b?1:0;
}

int main() {
    int *p;
    int i;
    printf("输入排序的个数:");
    scanf("%d",&i);
    p= sca(i,men);
    printf("输入1是从大到小排序,输入0是从小到大排序:");
    scanf("%d",&CONT);
    popSort(p, i,control);
    pri(p,i);
    fr(&p);

    return 0;

}