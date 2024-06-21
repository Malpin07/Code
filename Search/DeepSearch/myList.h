#ifndef __MY__LIST_H__
#define __MY__LIST_H__

#include "Stack.h"

#define TRUE 1      //定义布尔型常量
#define FALSE 0  //定义布尔型常量
#define OK 1 //一般正确
#define ERROR 0 //一般错误
#define INFEASIBLE -1 //不合理错误
#define OVERFLOW -2 //溢出错误
#define MAXSIZE 100  //最大容量

typedef Point ElemType; //定义元素类型

//定义节点结构
typedef struct LNode{
    ElemType data; //数据域
    struct LNode* next; //指针域
} LNode;

LNode* createLinkList();
int insertLinkList(LNode* head, ElemType data);
int insertLinkListHead(LNode* head, ElemType data);
void traverseLinkList(LNode* head);
int lengthLinkList(LNode* head);
LNode* findLinkList(LNode* head, ElemType data);
int deleteLinkList(LNode* head, LNode* find);
void popLinkList(LNode* head);
void reverseLinkList(LNode* head);
void destroyLinkList(LNode* head);

#endif