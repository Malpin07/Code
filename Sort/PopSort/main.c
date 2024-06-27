#include <stdio.h>

//冒泡排序
//回调函数
void bubbleSort(int *p, int n,int (*pf)(int, int)){
    int i, j;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (pf(p[j], p[j+1])){
                p[j]= p[j]^p[j+1];
                p[j+1]= p[j]^p[j+1];
                p[j]= p[j]^p[j+1];
               // temp = arr[j];
               // arr[j] = arr[j+1];
               // arr[j+1] = temp;
            }
        }

    }
}
//比较函数
int pf(int a, int b){

    return a > b? 1 : 0;
}

void popSort(int *p,int n){
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-1-i; ++j) {
            if (p[j]>p[j+1]){
                p[j]= p[j]^p[j+1];
                p[j+1]= p[j]^p[j+1];
                p[j]= p[j]^p[j+1];
            }
        }
    }
}
//冒泡优化
void popSort2(int *p,int n){
    int flag;
    for (int i = 0; i < n-1; ++i) {
        flag=1;
        for (int j = 0; j < n-1-i; ++j) {
            if (p[j]>p[j+1]){
                p[j]= p[j]^p[j+1];
                p[j+1]= p[j]^p[j+1];
                p[j]= p[j]^p[j+1];
                flag=0;
            }
        }
        if(flag=1){
            break;
        }
    }
}

int  main(int argc,char *argv[] ,char *evn[]){
    int arr[] = {64, 1134, 245, 1112, 422, 11, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    popSort(arr,sizeof(arr)/sizeof(*arr));
    //bubbleSort(arr, n, pf);

    printf("array:");
    for (int i=0; i < n; i++){
        printf("%d ", arr[i]);
    }
    return 0;

}