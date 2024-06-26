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
}myQueue;

//初始化
void initStack();
//判断是否满
bool isStackFull();
//判断是否空
bool isStackEmpty();
//压栈
void push(myQueue*,ElemType);
//弹栈
ElemType pop(myQueue*);
//复位栈
void resetStack(myQueue*);
//清空栈
void clearStack(myQueue*);

*/
//链式存储
typedef struct _Point{
    int _x;
    int _y;
}Point;
typedef struct _Node{
    Point data;
    struct _Node* next;
}Node;

typedef struct myQueue{
    Node * top;
}Stack;

//初始化
void initStack(Stack*);
//判断是否空
bool isStackEmpty(Stack*);
//压栈
void push(Stack*, Point);
//弹栈
Point pop(Stack*);
//复位栈
void resetStack(Stack*);
//清空栈
void clearStack(Stack*);
#endif