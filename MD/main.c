/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
pid_t fork(void);
int* func(int i){
    int* arr;
    arr=malloc(i*sizeof(int));
    for (int j=0;j<i;j++){
        scanf("%d",&arr[j]);
    }
    return arr;
}

void pop(int *p,int len){

    for (int i = 0; i < len-1 ; ++i) {
        for (int j = 0; j < len-i-1; ++j) {
                if (p[j]>p[j+1]){
                    p[j]= p[j]^p[j+1];
                    p[j+1]= p[j]^p[j+1];
                    p[j]= p[j]^p[j+1];
                }
        }
    }
}

int main(int argc, const char *argv[])
{
  int * p;
  int i;
    printf("输入排序的个数:");
    scanf("%d",&i);
    p=func(i);
    for (int j = 0; j < i; ++j) {
        printf("%d",p[j]);
    }
    printf("\n");
    pop(p,i);
    for (int j = 0; j < i; ++j) {
        printf("%d",p[j]);
    }
    free(p);
    return 0;
}
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int a=10;//a在常量区

void func(char arr[]){//数组传参的时候,传递的是地址   char arr[]==char *arr
    printf("arr=%d\n",sizeof(arr)); //arr=8
}

int main(int argc, const char *argv[])
{
    func("");

    printf("argc=%d\n",argc);
    char num[10];
    for(int i=1;i<argc;i++){
        num[i-1]=*(argv[i]+i-1);
    }
    int n= atoi(num);
    printf("n=%d\n",n);

    //printf("%c%c%c \n",*argv[1],*(argv[2]+1),*(argv[3]+2));


   /*
    const int a=20;//a在栈上
    int *p =&a;
    *p=30;//a在栈上,所以*p=30会修改a的值
    printf("a=%d\n",a);
    return 0;
    */


/*   int n=100;
   const int *p=&n; //const只能限制p指针去修改n的值
   n=300;
   //*p=200;//报错
   printf("n=%d\n",n);

    int t=100;
    int * const r=&t;*/


    return 0;
}

