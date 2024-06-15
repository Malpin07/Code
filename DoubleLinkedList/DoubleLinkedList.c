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
    //先让新节点有指向
    cur->next=head->next;//只有head的时候head->next=head
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

//长度
int lenList(Dnode* head){
    int len=0;
    Dnode *temp = head->next;
    while (temp != head) {
        temp = temp->next;
        len++;
    }
    return len;
}

//查找节点
Dnode* searchList(Dnode* head,ElemType find){
    Dnode *clock=head->next;
    Dnode *unclock=head->pre;

    while (unclock!=clock->pre){
        if(clock->data==find){
            return clock;
        }
        if(unclock->data==find){
            return unclock;
        }
        if(clock==unclock){
            break;
        }
        clock=clock->next;
        unclock=unclock->pre;
    }
    return NULL;
}



//删除节点
void deleteList(Dnode* dl){
    dl->pre->next=dl->next;
    dl->next->pre=dl->pre;
    free(dl);
}
//销毁链表
void destroyList(Dnode* head){
    head->pre->next=NULL;
    Dnode *temp;
    while(head){
        temp=head;
        head=head->next;
        printf("销毁节点%d \n",temp->data);
        free(temp);
    }
}
//排序
void sortList(Dnode* head){
    int len=lenList(head);
    //p是要比较的节点,prep是要比较的节点前驱,e是p的下一个节点是被比较的节点
    Dnode *p,*e,*temp;

    for(int i=0;i<len-1;i++) {
        p = head->next;
        e=p->next;
        for (int j = 0; j < len - i - 1; j++) {
            if (p->data > e->data) {
                e->pre=p->pre;
                p->pre->next=e;

                p->next=e->next;
                p->pre=e;


                e->next=p;
                p->next->pre=p;

                e=p->next;//恢复p和e的先后顺序
                continue;
            }
            p=p->next;//向后移动
            e=p->next;

        }
    }
}