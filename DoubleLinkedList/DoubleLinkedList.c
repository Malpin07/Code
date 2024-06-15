#include "DoubleLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

//创建头节点
Dnode* createList(){
    Dnode *head=(Dnode*)malloc(sizeof (Dnode));
    head->pre=head;
    head->next=head;

    return head;
}

//添加新节点,从头插入
void insertList(Dnode* head,ElemType data){
    Dnode *cur=(Dnode*)malloc(sizeof (Dnode));
    cur->data=data;

    cur->next=head->next;
    cur->pre=head;
    head->next=cur;
    cur->next->pre=cur;

}

//遍历
void traverseList(Dnode* head){

    Dnode *temp = head->next;
    while (temp != head) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

}