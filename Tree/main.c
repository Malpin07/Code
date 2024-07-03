
#include <stdio.h>
#include <stdlib.h>

//树节点结构体
typedef struct _Node{
    char data;  //数据域
    struct _Node *lchild;//左子树
    struct _Node *rchild;//右子树
}node_t;

//创建一棵树
int create_tree(node_t **root){
    if(NULL == root){
        return -1;
    }
    char value = getchar();//在终端输入内容
    getchar();//清理垃圾字符
    if('#' == value){ //递归的出口
        return 0;
    }
    *root = (node_t *)malloc(sizeof(node_t));
    if(NULL == *root){
        return -1;
    }
    (*root)->data = value;
    (*root)->lchild = NULL;
    (*root)->rchild = NULL;
    create_tree(&((*root)->lchild));
    create_tree(&((*root)->rchild));
    return 0;
}

//前序遍历
int qianxu(node_t *root){
    if(NULL == root){//递归的出口
        return -1;
    }
    printf("%c", root->data);
    qianxu(root->lchild);
    qianxu(root->rchild);
    return 0;
}

//中序遍历
int zhongxu(node_t *root){
    if(NULL == root){//递归的出口
        return -1;
    }
    zhongxu(root->lchild);
    printf("%c", root->data);
    zhongxu(root->rchild);
    return 0;
}

//后序遍历
int houxu(node_t *root){
    if(NULL == root){//递归的出口
        return -1;
    }
    houxu(root->lchild);
    houxu(root->rchild);
    printf("%c", root->data);
    return 0;
}

//销毁一棵树
int destroy(node_t **root){
    if(*root){
        destroy(&(*root)->lchild);
        destroy(&(*root)->rchild);
        free(*root);
    }
    free(*root);
    *root=NULL;
}

int main(int argc, const char *argv[])
{
    node_t *root = NULL;
    create_tree(&root);
    printf("root = %p\n", root);// 非NULL

    //前序
    qianxu(root);
    printf("\n");

    //中序
    zhongxu(root);
    printf("\n");

    //后序
    houxu(root);
    printf("\n");

    //销毁树
    destroy(&root);
    printf("root = %p\n", root);// NULL

    return 0;
}