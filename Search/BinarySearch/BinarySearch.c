#include <stdio.h>
// 二分查找算法
int binarySearch(int *p, int low, int high, int find) {
    int mid;
    while (low<=high){
        mid=(low+high)/2;
        if(find==p[mid]){
            return mid;
        } else if(find>p[mid]){
            low=mid+1;
        } else if(find<p[mid]){
            high=mid-1;
        }
    }
    return -1;
}
// 改进版二分查找算法
int NewbinarySearch(int *p, int low, int high, int find) {
    int mid;
    if (low<=high){
        mid=(low+high)/2;
        if(find==p[mid]){
            return mid;
        } else if(find>p[mid]){

            return NewbinarySearch(p, mid+1, high, find);
        } else if(find<p[mid]){
            return NewbinarySearch(p, mid, mid-1, find);
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int n = sizeof(arr)/sizeof(arr[0]);
    int find = 15;
    int result = NewbinarySearch(arr, 0, n-1, find);
    if(result!=-1){
        printf("下标:%d\n", result);
    } else {
        printf("没找到\n");
    }
    return 0;
}