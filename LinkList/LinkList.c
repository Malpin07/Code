/*LinkList.c -- 单链表*/
#include <stdio.h>
#include "myList.h"


/*
Node* move1(Node *head){
    printf("move1:%d",head->data);

    head=head->next;
    printf("move2:%d",head->data);
    head->data=100;
    printf("move3:%d",head->data);

    return head;
}*/
int main(){
    Node* head = createLinkList();//创建链表
    insertLinkList(head, 100);
    insertLinkList(head, 24);
    insertLinkList(head, 3);
    insertLinkList(head, 4);
    insertLinkList(head, 55);
    insertLinkList(head, 55666);

    traverseLinkList(head);
    popLinkList(head);
    traverseLinkList(head);
    reverseLinkList(head);
    traverseLinkList(head);

/*    printf("***************\n");
    printf("move:%d\n",head->data);
    Node* pNode=  move1(head);
    printf("move:%d\n",head->data);
    printf("move:%d\n",head->next->data);
    printf("***************\n");
    printf("move:%d\n",pNode->data);
    printf("move:%d\n",pNode->next->data);*/
    destroyLinkList(head);



    return 0;
}


