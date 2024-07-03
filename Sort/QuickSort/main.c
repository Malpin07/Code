//#include <stdio.h>
//
////快速排序
//void QuickSort(int *p, int low, int high) {
////    if(low<high) {
////        int pivot = p[low];//取第一个元素作为中轴
////        int l = low, h = high;
////        while (l < h) {
////            //从后往前找到比pivot小的元素
////            while (p[h] >= pivot && l < h) {
////                h--;
////            }
////            p[l]= p[h];
////            //从前往后找到比pivot大的元素
////            while (p[l] <= pivot && l < h) {
////                l++;
////            }
////            p[h]= p[l];
////        }
////        //将pivot放到中间
////        p[h]=pivot;
////        QuickSort(p, low, h - 1);//前半段
////        QuickSort(p, h + 1, high);//后半段
////    }
//}
//
//
////比较函数
//int pf(int a, int b){
//    return a < b ? 1 : 0;
//}
//
//int  main(int argc,char *argv[] ,char *evn[]){
//    int arr[] = {64, 1134, 245, 1112, 422, 11, 11};
//    int n = sizeof(arr)/sizeof(arr[0]);
//    QuickSort(arr,0,n-1);
//    for (int i=0; i < n; i++){
//        printf("%d ", arr[i]);
//    }
//    return 0;
//
//}
//
//void QuickSort1(int *p, int low, int high){
//    int pivot = p[low];//取第一个元素作为中轴
//
//
//}


#include <stdio.h>

// 交换两个数的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 快速排序的分区函数
int partition(int arr[], int low, int high) {
    int pivot = arr[low]; // 选择第一个元素作为基准点
    int left = low + 1;
    int right = high;

    while (1) {
        // 从左向右找到第一个大于基准点的元素
        while (left <= right && arr[left] <= pivot) {
            left++;
        }
        // 从右向左找到第一个小于基准点的元素
        while (left <= right && arr[right] >= pivot) {
            right--;
        }
        if (left > right) {
            break; // 如果左右指针交叉，跳出循环
        } else {
            swap(&arr[left], &arr[right]); // 否则，交换左右指针指向的元素
        }
    }
    // 交换基准点与右指针指向的元素
    swap(&arr[low], &arr[right]);
    return right;
}
// 快速排序主函数
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi是分区索引，arr[pi]现在是正确位置
        int pi = partition(arr, low, high);
        // 分别对左右子数组进行排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 打印数组
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 主函数来测试以上代码
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("原始数组: \n");
    printArray(arr, n);
    partition(arr, 0, n - 1);
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("排序后的数组: \n");
    printArray(arr, n);
    return 0;
}
