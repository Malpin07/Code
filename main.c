#include <stdio.h>

int main() {
    int num;

    int temp;
//    printf("请输入一个数字：");
//    scanf("%d", &num);
    for (int i = 0; i < 1000000; ++i) {
        int sum = 0;
        num=i;
        temp = num;
        while (temp!= 0) {
            sum += (temp % 10) * (temp % 10) * (temp % 10);
            temp /= 10;
        }
        if (sum == num) {
            printf("%d 是水仙花数\n", num);
        }
//        else {
//            printf("%d 不是水仙花数\n", num);
//        }
    }


    return 0;
}