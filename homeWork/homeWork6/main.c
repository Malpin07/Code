#include "link_stack.h"
#include <stdio.h>
#include <string.h>
int pairing(stack_t *,char *);
int main(){
    stack_t *my_stack = NULL;
    create_stack(&my_stack);
    char buff1[1024] = "askd{asdf}asdf{asdf[asdf]adf(adsf(adf)f)}jfh"; //配对
    char buff2[1024] = "askd{asdf}asdf{asdf[asdf]adf(adsf(adf)f}jfh";  //不配对
    char buff3[1024] = "askd{asdf}asdf{asdf[asdf]adf(adsf(adf)f)jfh";  //不配对
    char buff4[1024] = "askd{asdf}asdf{asdf[asdf)adf(adsf(adf)f)}jfh"; //不配对
    if(pairing(my_stack,buff1)==-1){
        printf("%s,不配对\n",buff1);
    } else{
        printf("%s,配对\n",buff1);
    }

    if(pairing(my_stack,buff2)==-1){
        printf("%s,不配对\n",buff2);
    } else{
        printf("%s,配对\n",buff2);
    }

    if(pairing(my_stack,buff3)==-1){
        printf("%s,不配对\n",buff3);
    } else{
        printf("%s,配对\n",buff3);
    }

    if(pairing(my_stack,buff4)==-1){
        printf("%s,不配对\n",buff4);
    } else{
        printf("%s,配对\n",buff4);
    }
/*//入栈
    push_stack(my_stack, 10);
    push_stack(my_stack, 20);
    push_stack(my_stack, 30);
    print_stack(my_stack); // 30 20 10

//出栈
    int value = 0;
    pop_stack(my_stack, &value);
    printf("value = %d\n", value); // 30
    pop_stack(my_stack, &value);
    printf("value = %d\n", value); // 20

//入栈
    push_stack(my_stack, 40);
//出栈
    pop_stack(my_stack, &value);
    printf("value = %d\n", value); // 40
    pop_stack(my_stack, &value);
    printf("value = %d\n", value); // 10
    pop_stack(my_stack, &value); //空了 失败

//入栈
    printf("***************************\n");
    push_stack(my_stack, 100);
    push_stack(my_stack, 200);
    print_stack(my_stack); // 200 100
    clean_list(my_stack);//清空
    print_stack(my_stack); // 没有元素了

//销毁
    destroy_stack(&my_stack);
    printf("my_stack = %p\n", my_stack); // NULL*/
    return 0;
}
//使用栈，实现判断字符串中括号是否配对的功能
int pairing(stack_t * my_stack,char *buff){
    if(my_stack==NULL){
        printf("入参为NULL");
        return -1;
    }
    if(buff==NULL){
        printf("入参为NULL");
        return -1;
    }
    for (int i = 0; i < strlen(buff) ; ++i) {
        int temp=-1;
        if(buff[i]==40 || buff[i]==60 || \
        buff[i]==91|| buff[i]==123 ) {
            push_stack(my_stack, buff[i]);
        }
        if(buff[i]==41 || buff[i]==62 || \
        buff[i]==93  || buff[i]==125 ) {
            if(!is_empty(my_stack)){
                pop_stack(my_stack,&temp);
            }
            if(temp==40&&buff[i]==41){
                continue;
            } else if(temp==60&&buff[i]==60){
                continue;
            } else if(temp==91&&buff[i]==93){
                continue;
            } else if(temp==123&&buff[i]==125){
                continue;
            } else{
                return -1;
            }
        }
    }
    if(!is_empty(my_stack)){
        return -1;
    }
    return 0;
}