#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int ElemType;
typedef struct _Node{
    ElemType data;
    struct _Node* next;
}node_t;

int  create_node(node_t **head, ElemType data);

int insert_list_by_head(node_t *head ,ElemType data);

int print_list(node_t *head);

int insert_list_by_tail(node_t* head, ElemType data);
//插入任意位置
int insert_list_by_pos(node_t *head,int pos, ElemType data);

//头删
int delete_list_by_head( node_t *head );
//尾删
int delete_list_by_tail( node_t *head );
//删除任意位置
int delete_list_by_pos( node_t *head, int pos);
//修改指定位置元素
int modify_list_by_pos( node_t *head, int pos, ElemType data);
//查找指定位置元素
int search_list_by_pos( node_t *head, int pos, node_t **data);
//两个链表合并
int merge_list( node_t *head1, node_t **head2);
//链表翻转
int overturn_list( node_t *head);
//链表排序
int sort_list( node_t *head);
//链表剔重
int tichong_list(node_t *head);

int lengthLinkList(node_t *head);

int clean_list(node_t *phead);
int destroy_list(node_t **phead);

