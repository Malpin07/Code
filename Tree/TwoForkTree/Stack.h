#ifndef __MYSTACK_H__
#define __MYSTACK_H__

typedef struct _TreeNode
{
    int _data;
    struct _TreeNode *_left;
    struct _TreeNode *_right;
}TreeNode;

typedef struct _Stack
{   int _len;
    int _top;
    TreeNode * * _space;
}Stack;

void initStack(Stack * s, int size);
int isStackFull(Stack * s);
int isStackEmpty(Stack * s);
void push(Stack * s, TreeNode *ch);
TreeNode * pop(Stack *s);
void clearStack(Stack *s);
void resetStack(Stack *s);
#endif // MYSTACK_H