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