#include <stdio.h>


void QuickSort(int *p, int low, int high) {

    if(low<high) {

        int pivot = p[low];//取第一个元素作为中轴
        int l = low, h = high;


        while (l < h) {
            //从后往前找到比pivot小的元素
            while (p[h] >= pivot && l < h) {
                h--;
            }
            p[l]= p[h];
            //从前往后找到比pivot大的元素
            while (p[l] <= pivot && l < h) {
                l++;
            }
            p[h]= p[l];
        }
        //将pivot放到中间
        p[h]=pivot;
        QuickSort(p, low, h - 1);//前半段
        QuickSort(p, h + 1, high);//后半段
    }
}


//比较函数
int pf(int a, int b){
    return a < b ? 1 : 0;
}

int  main(int argc,char *argv[] ,char *evn[]){
    int arr[] = {64, 1134, 245, 1112, 422, 11, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    QuickSort(arr,0,n-1);
    for (int i=0; i < n; i++){
        printf("%d ", arr[i]);
    }
    return 0;

}