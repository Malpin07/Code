#include "BinarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct _TreeNode{
    int _data;
    struct _TreeNode *_left;
    struct _TreeNode *_right;
}TreeNode;

void initNst(){

}

//有bug找不到
//void insertBst(TreeNode** r,int _data){
//    //树是空就添加到根
//    if(*r == NULL){
//        *r = (TreeNode*)malloc(sizeof(TreeNode));
//        (*r)->__data=_data;
//        (*r)->_right=(*r)->_left=NULL;
//    } else{
//        //树不是空,判断大小,找到合理位置
//        while (1){//添加后break;
//            if(_data > (*r)->__data){ //_data比当前节点大,去当前节点右边找到一个空位
//                if((*r)->_right == NULL){
//                    (*r)->_right=(TreeNode*)malloc(sizeof(TreeNode));
//                    (*r)->_right->__data = _data;
//                    (*r)->_right->_left = (*r)->_right->_right = NULL;
//                    break;
//                } else{
//                    (*r)=(*r)->_right;
//                }
//
//            } else{
//                //_data比当前节点小
//                if((*r)->_left==NULL){
//                    (*r)->_left=(TreeNode*)malloc(sizeof(TreeNode));
//                    (*r)->_left->__data=_data;
//                    (*r)->_left->_left = (*r)->_left->_right = NULL;
//                    break;
//                } else{
//                    (*r)=(*r)->_left;
//                }
//            }
//        }
//    }
//}

/*
void insertBst(TreeNode ** root, int _data)
{
    TreeNode *tmp ,*st = *root;
    if((*root) == NULL)
    {
        (*root) = (TreeNode*)malloc(sizeof(TreeNode));
        (*root)->_data = _data;
        (*root)->left = (*root)->right = NULL;
    }
    else
    {
        while(1)
        {
            if(_data >(st)->_data)
            {
                if( (st)->right == NULL)
                {
                    tmp = (TreeNode*)malloc(sizeof(TreeNode));
                    tmp->_data = _data;
                    tmp->left = tmp->right = NULL;
                    (st)->right = tmp;
                    break;
                }
                else
                    (st) = (st)->right;
            }
            else
            {
                if((st)->left == NULL)
                {
                    tmp = (TreeNode*)malloc(sizeof(TreeNode));
                    tmp->_data = _data;
                    tmp->left = tmp->right = NULL;
                    (st)->left = tmp;
                    break;
                }
                else
                    (st) = (st)->left;
            }
        }
    }
}
*/

//改进版
void insertBst(TreeNode** r,int _data){
    if(*r==NULL){
        *r = (TreeNode*)malloc(sizeof(TreeNode));
        (*r)->_data=_data;
        (*r)->_right=(*r)->_left=NULL;
    } else{

        if(_data > (*r)->_data){
            insertBst( &(*r)->_right,_data);
        } else{
            insertBst( &(*r)->_left,_data);
        }
    }
}

TreeNode * srarchBst(TreeNode* r,int find){
    while (r){
        if(find==r->_data){
            return r;
        }
        else if(find>r->_data){
            r=r->_right;
        } else{
            r=r->_left;
        }
    }
    return NULL;
}
TreeNode * srarchBst_1(TreeNode* r,int find){

       if(r){
           if(r->_data==find){
               return r;
           } else if(find >r->_data){
               return srarchBst_1(r->_right,find);
           } else{
               return srarchBst_1(r->_left,find);
           }
       }

    return NULL;
}


//中序遍历
void midOrder(TreeNode* t){
    if(t){
        midOrder(t->_left);
        printf("%d  ",t->_data);
        midOrder(t->_right);
    }
}

TreeNode * getmin(TreeNode* r){
    if (r){
        while (r->_left){
            r= r->_left;
        }
        return r;
    }
}
TreeNode * getmax(TreeNode* r){
    if (r){
        while (r->_right){
            r= r->_right;
        }
        return r;
    }
}

//获取父节点
TreeNode * getParent(TreeNode* r,TreeNode* child) {
   static TreeNode * parent = NULL;
    if(r)
    {
        if(r->_left==child || r->_right==child){
            parent=r;
        }
        getParent(r->_left,child);
        getParent(r->_right,child);
    }
    return parent;
}

//删除节点
TreeNode * deleteBst(TreeNode** r,TreeNode* pdel) {
    TreeNode *t =*r;
    TreeNode *parent;
    if(pdel->_left==NULL && pdel->_right==NULL){
        //判断是否删根
        if(*r==pdel){
            free(t);
            *r=NULL;
            return NULL;
        }
        //查找父节点
        parent= getParent(*r,pdel);
        if (parent->_left==pdel){
            parent->_left=NULL;
        } else{
            parent->_right=NULL;
        }

    }else if(pdel->_left!=NULL && pdel->_right==NULL){
        //判断是否删根
        if(*r==pdel){

        }
    }else if(pdel->_left==NULL && pdel->_right!=NULL){
        //判断是否删根
        if(*r==pdel){

        }
    } else{

    }

}
int main(){
    //初始化空树
    TreeNode * root=NULL;
    insertBst(&root,50);
    insertBst(&root,30);
    insertBst(&root,20);
    insertBst(&root,40);
    insertBst(&root,70);
    insertBst(&root,60);
    insertBst(&root,80);

    midOrder(root);

    TreeNode *find=srarchBst_1(root,80);
    if(find){
        printf("%d\n",find->_data);
    } else{
        printf("无");
    }
    deleteBst(&root,find);
    midOrder(root);
//    printf("%d\n", (getmax(root))->_data);
//    printf("%d\n", (getmin(root))->_data);

//    TreeNode *father = getParent(root,find);
//    if(father){
//        printf("%d\n",father->_data);
//    } else{
//        printf("无");
//    }
}