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


