#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myList.h"



//创建新链表
Node* createLinkList(){
    Node* head = (Node*)malloc(sizeof(Node));
    if(head == NULL)
        return NULL;
    head->next = NULL;
    return head;
}

//在链表末位插入元素
int insertLinkList(Node* head, ElemType data){
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;//给新节点赋值
    newNode->next = NULL;//新节点的指针域置为空
    Node *p = head;//p指向头节点
    while(p->next!= NULL){//遍历链表，找到最后一个节点
        p = p->next;//p指向下一个节点
    }
    p->next = newNode;//将新节点插入到链表末尾
    return OK;
}
//在链表首位插入元素
int insertLinkListHead(Node* head, ElemType data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;//给新节点赋值
    newNode->next=head->next;//让新来的节点有所指向,避免打断链表
    head->next=newNode;//将新节点插入到链表首位
    return OK;
}




//遍历链表
void traverseLinkList(Node* head) {
    Node *p = head->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//链表长度
int lengthLinkList(Node* head){
    int len = 0;
    Node *p = head->next;
    while(p!= NULL){
        len++;
        p = p->next;
    }
    return len;
}


//查找数据
Node* findLinkList(Node* head, ElemType data){
    /*实际上是传递指针本身的副本，而不是指针指向的数据。
     * 这意味着函数内对指针本身的修改（例如修改指针的指向）不会影响外部传入的指针。
     * 但是，函数内对指针指向的数据的修改会影响到外部传入的指针指向的数据。*/
    head = head->next;
    while(head!= NULL){
        if(head->data == data)
            break;
        head = head->next;
    }
    return head;
}

//删除元素
int deleteLinkList(Node* head, Node* find){
    if(find->next == NULL){//判断是否是尾节点
        while(head->next!= find){//找到前一个节点
            head = head->next;
        }
        head->next = find->next;//将前一个节点的指针域指向要删除节点的下一个节点
        free(find);
    } else{ //删除中间节点
        Node* p = find->next;//指向了要删除节点的下一个节点
        find->data = find->next->data;//把要删除节点的,下一个节点的数据,复制到要删除的节点上
        find->next = find->next->next;//将要删除节点的,下一个节点的指针域,指向要删除节点的下下个节点
        //之前的要删除节点变成了,他的下一个节点相同的样子,已经链接了他的下下个节点
        //释放掉多余的节点(释放之前的要删除节点的下一个)
        free(p);
    }

    return OK;

}

//链表排序(冒泡) 使用指针
void popLinkList(Node* head){
    int len = lengthLinkList(head);

    //p是要比较的节点,prep是要比较的节点前驱,e是p的下一个节点是被比较的节点
    Node *prep,*p,*e,*temp;
    for(int i = 0; i < len-1; i++){
        //每次循环都指向头节点
        prep= head;
        p=head->next;
        e=p->next;
        for(int j = 0; j < len-i-1; j++) {//遍历链表,对每两个相邻节点进行比较
            if(p->data > e->data){
                //交换两个节点的值
                //交换之前的链表形式:prep->p->e
                prep->next=e;
                p->next=e->next;
                e->next=p;
                //交换后的链表形式:prep->e->p
                //保证三个指针的顺序是prep->p->e
                /*//交换指针p,e的指向
                temp=p;
                p=e;
                e=temp;*/
                /*交换优化 p不动 动e和prep*/
                prep=e;
                e=p->next;
                continue;
            }
            //3个指针向后移动
            prep=prep->next;
            p=p->next;
            e=p->next;

        }

    }
}

//链表逆置
void reverseLinkList(Node* head){
    Node *p = head->next;//指向头节点的下一个节点
    head->next=NULL;//头节点的指针域置为空
    Node *temp;//临时节点
    while(p!= NULL){//遍历链表,逆置节点的指针域
        /*temp=p;//保存当前节点的指针域
        p=p->next;//指向下一个节点,先将p移动到下一个节点
        temp->next=head->next;//将当前节点的指针域指向头节点的下一个节点,第一次指空,第二次是头插
        head->next=temp;//将头节点的指针域指向当前节点*/
        //p是要插入节点,先让t指向p的next,以便插入p之后p后移
        temp= p->next;
        p->next=head->next;//先让p有指向
        head->next=p;//p头插
        p=temp;//p后移
        //循环判断p是不是null
    }
}


//销毁链表
void destroyLinkList(Node* head){
    Node *temp;
    while (head){
        printf("释放节点%d\n",head->data);
        temp=head->next;
        free(head);
        head=temp;

    }
}

#if 0
//链表排序(冒泡) 常规数据交换
void popLinkList(Node* head){
    int len = lengthLinkList(head);
    head=head->next;//头节点指向下一个,跳过头节点
    Node *t ;//t指向要比较的节点
    for(int i = 0; i < len-1; i++){
        t= head;//每次循环都指向头节点
        for(int j = 0; j < len-i-1; j++) {//遍历链表,对每两个相邻节点进行比较
            if(t->data > t->next->data){//如果当前节点的值大于下一个节点的值
                //交换两个节点的值
                t->data ^= t->next->data;
                t->next->data^=  t->data;
                t->data ^= t->next->data;
            }
            //指针向后移动
            t = t->next;
        }
    }
}
# endif