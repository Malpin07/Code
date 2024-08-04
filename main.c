#include <stdio.h>
#include <string.h>
//
//int main() {
//    int num;
//
//    int temp;
////    printf("请输入一个数字：");
////    scanf("%d", &num);
//    for (int i = 0; i < 1000000; ++i) {
//        int sum = 0;
//        num=i;
//        temp = num;
//        while (temp!= 0) {
//            sum += (temp % 10) * (temp % 10) * (temp % 10);
//            temp /= 10;
//        }
//        if (sum == num) {
//            printf("%d 是水仙花数\n", num);
//        }
////        else {
////            printf("%d 不是水仙花数\n", num);
////        }
//    }
//
//
//    return 0;
//}

////二进制显示
//void bin32bdis(int data)
//{
//    int i=32;
//    while(i--)     //32---1
//    {
//        if(data & (1<<i))   //31--0
//            printf("1");
//        else
//            printf("0");
//        if(i%4==0)
//        {
//            if(i%8==0)
//                printf(" ");
//            else
//                printf("-");
//        }
//    }
//    putchar(10);
//}
//
//int main(){
////    char a[100];
////    printf("请输入：");
////    scanf("%s", a);
////    char n[26]={0};
////    for (int i = 0; i <strlen(a) ; ++i) {
////         n[a[i]-97]++;
////    }
////    for (int i = 0; i <26 ; ++i) {
////        printf("%c : %d \n",i+97, n[i]);
////    }
//    int num=123456;
//    printf("%d\n", strlen(&num));
//    printf("%d\n", sizeof(num));
//
//    bin32bdis(num);
//
//    return 0;
//}

//判断大小端
int main(){
    int a=0x12345678;
    char *p=(char*)&a;

    if(*p==0x78){
        printf("小端\n");
    }else{
        printf("大端\n");
    }

    return 0;

}