#ifndef __MY__LIST_H__
#define __MY__LIST_H__

#define TRUE 1      //定义布尔型常量
#define FALSE 0  //定义布尔型常量
#define OK 1 //一般正确
#define ERROR 0 //一般错误
#define INFEASIBLE -1 //不合理错误
#define OVERFLOW -2 //溢出错误
#define MAXSIZE 100  //最大容量

typedef int ElemType; //定义元素类型

//定义节点结构
typedef struct Node{
    ElemType data; //数据域
    struct Node* next; //指针域
} Node;


Node* createLinkList();
int insertLinkList(Node* head, ElemType data);
int insertLinkListHead(Node* head, ElemType data);
void traverseLinkList(Node* head);
int lengthLinkList(Node* head);
Node* findLinkList(Node* head, ElemType data);
int deleteLinkList(Node* head, Node* find);
void popLinkList(Node* head);
void reverseLinkList(Node* head);
void destroyLinkList(Node* head);

#endif