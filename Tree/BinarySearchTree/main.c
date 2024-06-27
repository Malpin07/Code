#include "BinarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct _TreeNode{
    int _data;
    struct _TreeNode *_left;
    struct _TreeNode *_right;
}TreeNode;



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
    //判断树是否为空
    if((*root) == NULL)
    {   //树为空,添加到根
        (*root) = (TreeNode*)malloc(sizeof(TreeNode));
        (*root)->_data = _data;
        (*root)->left = (*root)->right = NULL;
    }
    else
    {   //树不为空,判断大小,找到合理位置
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
    //树是空就添加到根
    //递归进入到这是添加节点到相应的位置
    if(*r==NULL){
        *r = (TreeNode*)malloc(sizeof(TreeNode));
        (*r)->_data=_data;
        (*r)->_right=(*r)->_left=NULL;
    } else{
        //树不是空,判断大小,找到合理位置
        if(_data > (*r)->_data){
            //_data比当前节点大,去当前节点右边找到一个空位
            insertBst( &(*r)->_right,_data);
        } else{
            //_data比当前节点小
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
//查找
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
//获取树的最小值
TreeNode * getmin(TreeNode* r){
    if (r){
        while (r->_left){
            r= r->_left;
        }
        return r;
    }
}
//获取树的最大值
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
    if(NULL==*r||NULL==pdel){
        return NULL;
    }
    TreeNode *t =*r;
    TreeNode *parent;

    TreeNode* minRight;//在有左右子树的情况删除使用
    //判断是否为叶子节点
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
        free(pdel);
    //判断是否只有左子树
    }else if(pdel->_left!=NULL && pdel->_right==NULL){
        //判断是否删根
        if(*r==pdel){
            *r= pdel->_left;
            free(pdel);
            return NULL;
        }
        //查找父节点
        parent= getParent(*r,pdel);
        //此分支中要删除节点的pdel_left不为空,先找到要删除节点的父节点,
        //判断要删除节点,在父节点的左还是右
        //if 要删除节点在父节点左:同时此分支中要删除节点的pdel_left不为空,
        //将要删除节点左边的链接到父节点左边 (要删除节点左边一定小于要删除节点的父节点)
        //elif 要删除节点在父节点右边:同时此分支中要删除节点的pdel_left不为空,
        //将要删除节点左边的链接到父节点右边 (要删除节点左边一定大于要删除节点的父节点)

        if(parent->_left==pdel){
            parent->_left=pdel->_left;
        } else{
            parent->_right=pdel->_left;
        }
        free(pdel);
    //判断是否只有右子树
    }else if(pdel->_left==NULL && pdel->_right!=NULL){
        //判断是否删根
        if(*r==pdel){
            *r= pdel->_right;
            free(pdel);
            return NULL;
        }

        //查找父节点
        parent= getParent(*r,pdel);
        //在要删除节点的pdel_right不为空 的分支中
        //判断要删除节点,在父节点的左还是右
        //if 要删除节点在父节点左:同时此分支中要删除节点的pdel_right不为空,
        //将要删除节点右边 的链接到父节点左边 (要删除节点右边一定小于要删除节点的父节点)
        //elif 要删除节点在父节点右边:同时此分支中要删除节点的pdel_right不为空,
        //将要删除节点右边 的链接到父节点右边 (要删除节点右边一定大于要删除节点的父节点)

        if(parent->_left==pdel){
            parent->_left=pdel->_right;
        } else{
            parent->_right=pdel->_right;
        }
        free(pdel);


    //有左右子树的情况
    } else{

        //找到要删除节点的 右边树的 最小值(最左的),这个最小值一定没有左节点,可能有右节点
        minRight=getmin(pdel->_right);
        //将要删除节点覆盖
        pdel->_data= minRight->_data;
        //查找minRight父节点,为删除minRight准备
        parent= getParent(*r,minRight);

        //if 找到的最小节点刚好是"要删除节点pdel"的右边节点
        //将minRight的右节点链接到minRight的父节点上(此时父节点就是被覆盖的pdel)
        if(minRight==pdel->_right){
            //parent是查找到的minRight父节点
            parent->_right= minRight->_right;
        } else{
            // if minRight是 "要删除节点pdel" 右子树之下最小的(最左的),minRight可能有右节点
            //minRight右节点一定小于minRight父节点,
            // 将minRight右节点链接到,minRight父节点的左边,
            parent->_left=minRight->_right;
        }
        free(minRight);

    }

}


//销毁树
void destroyBst(TreeNode* r){
    if(r){
        destroyBst(r->_left);
        destroyBst(r->_right);
        printf("销毁节点: %d\n",r->_data);
        free(r);
    }
}

int main(){
    //初始化空树
    /*                 30
     *         8                36
     *              15      32         100
     * */
    TreeNode * root=NULL;
    insertBst(&root,30);
    insertBst(&root,8);
    insertBst(&root,15);
    insertBst(&root,36);
    insertBst(&root,100);
    insertBst(&root,32);

    //中序遍历
    midOrder(root);
    //查找
    TreeNode *find=srarchBst_1(root,100);
    if(find){
        printf("找到了:%d\n",find->_data);
    } else{
        printf("无");
    }
    //删除
    deleteBst(&root,find);
    //中序遍历
    midOrder(root);
    //销毁
    destroyBst(root);

}