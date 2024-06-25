#include <stdio.h>
#include <string.h>

//函数使用来计算字符串x的长度的
int fun(char *x){

    char *y = x;
    while(*y++);
    return y-x-1;

}
int main(){

    int p[]={1,2,3};
    char s[]="hello world";
    printf("%d\n",fun(s));
    int* q=&p;
    printf("%d ",*(q++)) ;
    printf("%d ",*(q)) ;


}