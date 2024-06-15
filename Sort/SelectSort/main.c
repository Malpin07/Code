#include <stdio.h>

//选择排序
void SelectSort(int *arr, int n,int (*pf)(int, int)){
    int i, j, minIndex, temp;
    // 遍历整个数组
    for (i = 0; i < n - 1; i++) {
        // 寻找最小元素的下标
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (pf(arr[j] , arr[minIndex])) {
                minIndex = j;
            }
        }
        // 将最小元素与当前元素交换位置
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}


//比较函数
int pf(int a, int b){
    return a < b ? 1 : 0;
}

int  main(int argc,char *argv[] ,char *evn[]){
    int arr[] = {64, 1134, 245, 1112, 422, 11, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    SelectSort(arr, n, pf);

    for (int i=0; i < n; i++){
        printf("%d ", arr[i]);
    }
    return 0;

}