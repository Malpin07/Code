#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>
//初始化
void initStack(Stack *s,int size){
    s->_top=0;
    s->_len=size;
    s->_space=(TreeNode*) malloc(sizeof(TreeNode*)*s->_len);

}

//判断是否空
int isStackEmpty(Stack *s){
    return s->_top==NULL;
}

//压栈
void push(Stack* s, TreeNode* data){
    s->_space[s->_top]=data;
    s->_top++;

}

//出栈
TreeNode* pop(Stack* s) {
    return s->_space[--s->_top];
}

//复位栈
void resetStack(Stack* s){
    s->_top=0;
}

//清空栈
void clearStack(Stack* s){
    resetStack(s);
    free(s->_space);
}