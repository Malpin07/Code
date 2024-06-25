#include <stdio.h>
#include "Stack.h"


//#if 0
//            a1
//    b2              c3
//d4       e5                f6
//preOrder : 1 2 4 5 3 6 中左右
//midOrder : 4 2 5 1 3 6 左中右
//postOrder: 4 5 2 6 3 1 左右中;
//#endif


//****** 栈遍历 *************
//先序遍历
void preOrderBySTACK(TreeNode* r){
    if(r){
        Stack s;
        initStack(&s,100);
        while(r || !isStackEmpty(&s)){//判断树是否空,,同时判断循环过程中r直到底之后栈中是否有数据,栈有数据就不能跳出循环
            while(r){//压栈
                printf("%d",r->_data);
                push(&s,r);
                r = r->_left;
            }
            r = pop(&s);
            r = r->_right;
        }

    }
}

//中序遍历
void midOrderBySTACK(TreeNode* r){
    if(r){
        Stack s;
        initStack(&s,100);
        while(r || !isStackEmpty(&s)){//判断树是否空,,同时判断循环过程中r直到底之后栈中是否有数据,栈有数据就不能跳出循环
            while(r){//压栈
                push(&s,r);
                r = r->_left;
            }
            r = pop(&s);
            printf("%d",r->_data);
            r = r->_right;
        }

    }
}

//后序遍历
/*
 * 对于任一节点 P，
1.先将节点 P 入栈；
2.若 P 不存在左孩子和右孩子，或者 P 存在左孩子或右孩子，但左右孩子已经被
 输出，则可以直接输出节点 P，并将其出栈，将出栈节点 P 标记为上一个输出的节点，
 再将此时的栈顶结点设为当前节点；
3.若不满足 2）中的条件，则将 P 的右孩子和左孩子依次入栈，当前节点重新置
 为栈顶结点，之后重复操作 2）；
4.直到栈空，遍历结束。
 */
void postOrderBySTACK(TreeNode* t){

    Stack s;
    initStack(&s,100);
    TreeNode *cur; //当前结点
    TreeNode *pre=NULL; //前一次访问的结点
    push(&s,t);//压入
    while(!isStackEmpty(&s))
    {
        cur = pop(&s);//弹出 cur每次循环都会指向上次循环最后压进去的节点
        push(&s,cur);//再次压入
        if((cur->_left==NULL&&cur->_right==NULL)||
           (pre!=NULL&&(pre==cur->_left||pre==cur->_right)))
        {
            //如果当前结点没有孩子结点或者孩子节点都已被访问过
            printf("%d\t",cur->_data);
            pop(&s);
            pre=cur;
        }
        else
        {
            if(cur->_right != NULL)
                push(&s,cur->_right);
            if(cur->_left != NULL)
                push(&s,cur->_left);
        }
    }
}


//求树的高度
int getHeightByPostOrder(TreeNode * t){
    int lH, rH, maxH;
    if (t){
        lH = getHeightByPostOrder(t->_left);
        rH = getHeightByPostOrder(t->_right);
        maxH = (lH>rH)?lH:rH;
        return maxH +1;
    } else{
        return 0;
    }


}



//****** 递归遍历 *************
//先序遍历
void preOrder(TreeNode* t){
    if(t){

        printf("%d",t->_data);
        preOrder(t->_left);
        preOrder(t->_right);
    }
}
//后序遍历
void postOrder(TreeNode* t){
    if(t){
        postOrder(t->_left);
        postOrder(t->_right);
        printf("%d",t->_data);
    }
}
//中序遍历
void midOrder(TreeNode* t){
    if(t){

        midOrder(t->_left);
        printf("%d",t->_data);
        midOrder(t->_right);
    }
}

int main(){
    TreeNode a,b,c,d,e,f;
    TreeNode *root=&a;

    a._data=1;b._data=2;c._data=3;
    d._data=4;e._data=5;f._data=6;
    a._left=&b;a._right=&c;
    b._left=&d;b._right=&e;
    c._left=NULL;c._right=&f;

    d._left=d._right=e._left=e._right=f._left=f._right=NULL;


    //preOrderBySTACK(root);
    //midOrderBySTACK(root);
    //postOrderBySTACK(root);
    int hi=getHeightByPostOrder(root);
    printf("%d",hi);
    return 0;
}