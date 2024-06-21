#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myList.h"



//创建新链表
LNode* createLinkList(){
    LNode* head = (LNode*)malloc(sizeof(LNode));
    if(head == NULL)
        return NULL;
    head->next = NULL;
    return head;
}

//在链表末位插入元素
int insertLinkList(LNode* head, ElemType data){
    LNode* newLNode = (LNode*)malloc(sizeof(LNode));

    newLNode->data = data;//给新节点赋值
    newLNode->next = NULL;//新节点的指针域置为空
    LNode *p = head;//p指向头节点
    while(p->next!= NULL){//遍历链表，找到最后一个节点
        p = p->next;//p指向下一个节点
    }
    p->next = newLNode;//将新节点插入到链表末尾
    return OK;
}
//在链表首位插入元素
int insertLinkListHead(LNode* head, ElemType data){
    LNode* newLNode = (LNode*)malloc(sizeof(LNode));
    newLNode->data = data;//给新节点赋值
    newLNode->next=head->next;//让新来的节点有所指向,避免打断链表
    head->next=newLNode;//将新节点插入到链表首位
    return OK;
}




//遍历链表
void traverseLinkList(LNode* head) {
    LNode *p = head->next;
    while (p != NULL) {
        printf("(%d,%d) ", p->data._x, p->data._y);
        p = p->next;
    }
    printf("\n");
}

//链表长度
int lengthLinkList(LNode* head){
    int len = 0;
    LNode *p = head->next;
    while(p!= NULL){
        len++;
        p = p->next;
    }
    return len;
}

