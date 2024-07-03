#ifndef __LINK_STACK_H__
#define __LINK_STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//链表节点结构体
typedef struct _Node{
    int data;
    struct _Node *next;
}node_t;

//链式栈结构体
typedef struct _Stack{
    node_t *top;
    int count; //记录栈中元素个数
    //如果有其他属性信息 在此处罗列即可
}stack_t;

int create_stack(stack_t **my_stack);
int push_stack(stack_t *my_stack, int data);
int print_stack(stack_t *my_stack);
int is_empty(stack_t *my_stack);
int pop_stack(stack_t *my_stack, int *num);
int clean_list(stack_t *my_stack);
int destroy_stack(stack_t **my_stack);

#endif