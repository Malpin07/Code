#include <stdio.h>
#include <stdlib.h>

#define SQUARE(x) ((x) * (x))
#define ERR_EXIT(m)\
do\
{\
printf("Err:%s",m);\
exit(-1);\
}while(0)

#undef ERR_EXIT //取消宏定义

int main() {
    int a = 1;
    while (a <= 5) {
        printf("%d\n", SQUARE(a++));//define SQUARE(x) ((x) * (x))
    }

    return 0;
}