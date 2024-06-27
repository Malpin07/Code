#include <stdio.h>
//插入排序

void insertSort(int *arr,int n){
    int i ,j;
    int t;

    //第一个数进入天然有序少排一次
    //让插入的每个都有序
    for ( i = 1; i < n; i++) {
       t=arr[i];
       //t保存的是待插入的数
       //j和i同一位置
       //t是待插入的数，同前一个比较，如果t比前一个小，让前一个数后移
       //直到找到j-1位置的数,比t小的，然后插入到j位置
       for(j=i ; j-1>=0 && t < arr[j-1] ;j--){
            arr[j]=arr[j-1];
       }
       arr[j]=t;
    }

}


int main(){

    int arr[]={5,2,4,6,1,3};
    int n=sizeof(arr)/sizeof(arr[0]);
    insertSort(arr,n);

    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }


    return 0;
}