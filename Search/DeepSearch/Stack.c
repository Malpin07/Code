#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>
//初始化
void initStack(Stack *s){
    s->top= malloc(sizeof(Node));
    s->top->next=NULL;
}

//判断是否空
bool isStackEmpty(Stack *s){
    return s->top->next==NULL;
}

//压栈
void push(Stack* s, Point data){
    Node * cur=(Node *)malloc(sizeof(Node));
    cur->data=data;
    cur->next=s->top->next;
    s->top->next=cur;
}

//出栈
Point pop(Stack* s) {
    Node *temp=s->top->next;
    Point data=temp->data;
    //printf("弹出:%d",data);
    s->top->next=s->top->next->next;
    free(temp);
    return data;

}

//复位栈
void resetStack(Stack* s){
    while (!isStackEmpty(s)){
        pop(s);
    }
}

//清空栈
void clearStack(Stack* s){
    resetStack(s);
    free(s->top);
}