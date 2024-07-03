# C语言实现链表的各种功能

## 链表的定义

链表是一种数据结构，它是由一系列节点组成的线性结构。每个节点包含两个部分：数据和指针。数据部分存储着实际的数据，指针部分指向下一个节点。

链表的特点是：

- 每个节点都可以自由地插入或删除。
- 链表的第一个节点称为头节点，最后一个节点称为尾节点。
- 链表中节点的数量可以动态变化。

## 链表的实现

链表的实现可以分为两步：

1. 定义链表节点的结构。
2. 实现链表的操作函数。

### 定义链表节点的结构

```c  
文件名:link_list.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int ElemType;

typedef struct linkList{
    ElemType data;
    struct linkList* next;
}LNode;

//初始化链表
bool initList(LNode** head);

//链表是否为空
bool isEmpty(LNode* head);

//链表长度
int length(LNode* head);

//链表头部插入元素
bool insert(LNode* head, ElemType data);

//链表尾部插入元素
bool append(LNode* head, ElemType data);

//插入链表指定位置
bool insertAt(LNode* head, ElemType data, int pos);

//链表删除元素头删
bool delete(LNode* head);

//链表删除指定位置元素
bool deleteAt(LNode* head, int pos);

//删除链表元素尾删
bool deleteTail(LNode* head);


//链表中查找指定位置元素
LNode* searchAt(LNode* head, int pos);

//修改链表指定位置元素
bool modify(LNode* head, ElemType data, int pos);

//清空链表
bool clearList(LNode* head);

//销毁链表
bool destroyList(LNode** head);

//打印链表
bool printList(LNode* head);
```

### 实现链表的操作函数

```c  
文件名:link_list.c


#include "link_list.h"

#define DEBUG_PRINT 1

//初始化链表
bool initList(LNode** head){
    if(NULL==head){
#if DEBUG_PRINT
        printf("初始化链表的入参为空\n");
#endif
        return false;
    }
    //初始化  calloc()申请的空间自动初始化为0
    (*head)=(LNode*)calloc(1, sizeof(LNode));
    (*head)->next=NULL;
    (*head)->data=0;//头节点中数据用来保存链表中的元素个数
    return true;
}
//链表是否为空
bool isEmpty(LNode* head){
    if(NULL==head){
#if DEBUG_PRINT
        printf("isEmpty()的入参为空\n");
#endif
        return false;
    }
    if(head->next==NULL){
        return true;
    }
    return false;
}
//链表长度
int length(LNode* head){
    if(NULL==head){
#if DEBUG_PRINT
        printf("length()的入参为空\n");
#endif
        return false;
    }
    return head->data;
}
//链表头部插入元素
bool insert(LNode* head, ElemType data){
    //入参判断
    if(NULL==head){
#if DEBUG_PRINT
        printf("insert()的入参为空\n");
#endif
        return false;
    }

    //为新节点申请空间
    LNode * newNode=(LNode*)calloc(1, sizeof(LNode));
    newNode->data=data;
    newNode->next=head->next;
    head->next=newNode;
    head->data++;
}
//链表尾部插入元素
bool append(LNode* head, ElemType data){
    //入参判断
    if(NULL==head){
#if DEBUG_PRINT
        printf("insert()的入参为空\n");
#endif
        return false;
    }
    //为新节点申请空间
    LNode * newNode=(LNode*)calloc(1, sizeof(LNode));
    newNode->data=data;

   // LNode *temp=head->next;//head->next可能为NULL,下方对temp->next=(NULL->next),会报错
    LNode *temp=head;
    while (temp->next!=NULL){
        temp=temp->next;
    }
    newNode->next=temp->next;
    temp->next=newNode;
    head->data++;
    return true;
}
//插入链表指定位置
bool insertAt(LNode* head, ElemType data, int pos){
    //入参判断
    if(NULL==head){
#if DEBUG_PRINT
        printf("insertAt()的入参为空\n");
#endif
        return false;
    }
    if(pos<0|| pos>head->data ){
#if DEBUG_PRINT
        printf("insertAt()的插入位置不合理\n");
#endif
        return false;
    }
    LNode *temp=head;
    int  flg=0;//标记循环的次数是否到了插入位置 ,没到说明插入位置不合理
    for (int i = 0; i < pos; ++i) {
        flg++;
        if(temp->next!=NULL){
            temp=temp->next;
        } else{
            break;
        }
    }
    if(flg==pos){
        //为新节点申请空间
        LNode * newNode=(LNode*)calloc(1, sizeof(LNode));
        newNode->data=data;
        newNode->next= temp->next;
        temp->next=newNode;
        head->data++;
        return true;
    } else{
        return false;
    }
}
//链表删除元素头删
bool delete(LNode* head){
    //入参判断
    if(NULL==head){
#if DEBUG_PRINT
        printf("delete()的入参为空\n");
#endif
        return false;
    }
    if(isEmpty(head)){
        printf("链表已空\n");
        return true;
    }
    LNode *temp=head->next;
    head->next=head->next->next;
    free(temp);
    head->data--;
    return true;

}
//链表删除指定位置元素
bool deleteAt(LNode* head, int pos){
    //入参判断
    if(NULL==head ){
#if DEBUG_PRINT
        printf("deleteAt()的入参为空\n");
#endif
        return false;
    }
    if(NULL==head->next){ //要判断NULL==head->next 下面temp=head->next
        printf("空表不能删除\n");
        return false;
    }
    if(pos<0|| pos >= head->data ){
#if DEBUG_PRINT
        printf("deleteAt()的删除位置不合理\n");
#endif
        return false;
    }
    LNode *temp=head->next; //temp=head->next保证删除0位置也正常返回
    LNode *P=head;
    int flg=0;
    for (int i = 0; i < pos; ++i) {
        flg++;
        if(temp->next!=NULL){ //保证temp->next不能指空
            P=temp;
            temp=temp->next;
        } else{
            break;
        }
    }
    if(flg==pos){//查0位置不走循环,返回了temp=head->next
        P->next=temp->next;
        free(temp);
        head->data--;
        return true;
    } else{
        return false;
    }

}
//删除链表元素尾删
bool deleteTail(LNode* head){
    //入参判断
    if(NULL==head ){
#if DEBUG_PRINT
        printf("delete()的入参为空\n");
#endif
        return false;
    }
    //只有头节点无需删除
    if(NULL==head->next){
        printf("表只有头节点\n");
        return true;
    }

    //找到尾节点的前一个节点
    LNode *temp=head;
    LNode * P=NULL;
    while (temp->next!=NULL){
        P=temp;
        temp=temp->next;
    }
    if(P){
        //循环退出时P指向尾节点的前一个节点,temp就是尾节点
        P->next=NULL;
        free(temp);
        head->data--;
    }

    return true;
}
//链表中查找指定位置元素
LNode* searchAt(LNode* head, int pos){
    //入参判断
    if(NULL==head ){
#if DEBUG_PRINT
        printf("insertAt()的入参为空\n");
#endif
        return false;
    }
    if(NULL==head->next){ //要判断NULL==head->next 下面temp=head->next
        printf("空表不能查询\n");
        return false;
    }
    if(pos<0|| pos >= head->data ){
#if DEBUG_PRINT
        printf("searchAt()的查找位置不合理\n");
#endif
        return false;
    }

    LNode *temp=head->next; //temp=head->next保证查0位置也正常返回
    int flg=0;
    for (int i = 0; i < pos; ++i) {
        flg++;
        if(temp!=NULL){
            temp=temp->next;
        } else{
            break;
        }
    }
    if(flg==pos){//查0位置不走循环,返回了temp=head->next
        return temp;
    } else{
        return false;
    }


}
//修改链表指定位置元素
bool modify(LNode* head, ElemType data, int pos){
    //入参判断
    if(NULL==head ){
#if DEBUG_PRINT
        printf("modify()的入参为空\n");
#endif
        return false;
    }
    if(NULL==head->next){ //要判断NULL==head->next 下面temp=head->next
        printf("空表不能查询\n");
        return false;
    }
    if(pos<0|| pos >= head->data ){
#if DEBUG_PRINT
        printf("modify()的修改位置不合理\n");
#endif
        return false;
    }

    LNode *temp=head->next; //temp=head->next保证修改0位置也正常返回
    int flg=0;
    for (int i = 0; i < pos; ++i) {
        flg++;
        if(temp!=NULL){
            temp=temp->next;
        } else{
            break;
        }
    }
    if(flg==pos){
        temp->data=data;
        return true;
    } else{
        return false;
    }
}
//清空链表
bool clearList(LNode* head){
    //入参判断
    if(NULL==head ){
#if DEBUG_PRINT
        printf("clearList()的入参为空\n");
#endif
        return false;
    }
    if(NULL==head->next){ //要判断NULL==head->next 下面temp=head->next
        printf("链表中没有数据\n");
        return true;
    }
    LNode * temp=head->next;
    LNode *P=head;
    while (temp!=NULL){
        P=temp;
        temp=temp->next;
        free(P);
        head->data--;
    }
    head->next=NULL;
    return true;

}

//销毁链表
bool destroyList(LNode** head){
    //入参判断
    if(NULL==head || NULL==*head){
#if DEBUG_PRINT
        printf("destroyList()的入参为空\n");
#endif
        return false;
    }
    clearList(*head);
    free(*head);
    (*head)=NULL;
    return true;
}

//打印链表
bool printList(LNode* head){
    //入参检查
    if(NULL==head){
#if DEBUG_PRINT
        printf("length()的入参为空\n");
#endif
        return false;
    }
    if(NULL==head->next){
        printf("表为空\n");
        return true;
    }
    LNode *temp=head->next;
    while (temp){
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
    return true;
}



```
# main.c测试功能

```c  
文件名:main.c
#include "link_list.h"

int main(){
    LNode *head;
    initList(&head);
    printf("head=%p\n",head);
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");

    //测试头插
    insert(head,100);
    insert(head,200);
    insert(head,300);
    printList(head);
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    //300 200 100
    printf("----------------------------\n");
    //测试尾插
    append(head,400);
    append(head,500);
    append(head,600);
    printList(head);
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    //300 200 100 400 500 600
    printf("----------------------------\n");
    //测试插入链表指定位置
    insertAt(head,333,1);
    insertAt(head,444,0);
    insertAt(head,555,8);//最后一个插入
    insertAt(head,666,10);//报错///insertAt()的插入位置不合理
    printList(head);//444 300 333 200 100 400 500 600 555
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");
    //链表删除元素头删
    delete(head);
    delete(head);
    printList(head);//333 200 100 400 500 600 555
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");
    //删除链表元素尾删
    deleteTail(head);
    printList(head);//333 200 100 400 500 600
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));//length=6
    printf("----------------------------\n");
    //链表中查找指定位置元素
    LNode *N=NULL;
    searchAt(head,-1);//位置不合理
    N=searchAt(head,6);//位置不合理
    N=searchAt(head,5);//查找数据:600
    if(N){
        printf("查找数据:%d\n",N->data);
    } else{
        printf("没查到\n");
    }
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");
    //修改链表指定位置元素
    modify(head,777,0);
    modify(head,888,6);//modify()的修改位置不合理
    printList(head);//777 200 100 400 500 600
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");
    //链表删除指定位置元素
    deleteAt(head,0);
    printList(head);//200 100 400 500 600
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");
    //清空链表
    clearList(head);
    printf("head=%p\n",head);//head=0000000000B11450
    printf("head->next=%p\n",head->next);//head->next=0000000000000000
    printList(head);//表为空
    printf("Empty=%d\n",isEmpty(head));//Empty=1
    printf("length=%d\n",length(head));//length=0
    printf("----------------------------\n");

    //销毁
    destroyList(&head);
    printf("head=%p\n",head);//head=0000000000000000
    printf("----------------------------\n");
}
```




## 总结

链表是一种常见的数据结构，在实际应用中有着广泛的应用。本文介绍了链表的定义、实现、操作、测试等功能。

链表的实现主要是定义链表节点的结构，然后实现链表的操作函数。链表的操作函数包括：初始化链表、链表是否为空、链表长度、链表头部插入元素、链表尾部插入元素、插入链表指定位置、链表删除元素头删、链表删除指定位置元素、删除链表元素尾删、链表中查找指定位置元素、修改链表指定位置元素、清空链表、销毁链表、打印链表。

链表的操作函数都有相应的注释，可以很方便地理解各个函数的作用。

链表的测试代码主要是对链表的操作函数进行测试 ,可以作为学习链表的入门代码。



