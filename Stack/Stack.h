#ifndef __STACK_H__
#define __STACK_H__
#include <stdbool.h>

//线性存储
/*

typedef char ElemType;
typedef struct _Stack{
    int _len;
    int _top;
    ElemType * _space;
}Stack;

//初始化
void initStack();
//判断是否满
bool isStackFull();
//判断是否空
bool isStackEmpty();
//压栈
void push(Stack*,ElemType);
//弹栈
ElemType pop(Stack*);
//复位栈
void resetStack(Stack*);
//清空栈
void clearStack(Stack*);

*/
//链式存储
typedef int ElemType;
typedef struct _Node{
    ElemType data;
    struct _Node* next;
}Node;

typedef struct Stack{
    Node * top;
}Stack;

//初始化
void initStack(Stack*);
//判断是否空
bool isStackEmpty(Stack*);
//压栈
void push(Stack*,ElemType);
//弹栈
ElemType pop(Stack*);
//复位栈
void resetStack(Stack*);
//清空栈
void clearStack(Stack*);
#endif