#ifndef __Seq_List_H__
#define __Seq_List_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 15
#define INFEASIBLE -1 //不合理
#define OK 1 //一般正确

//数据元素的结构体
typedef struct _Node{
    int data;//数据项以一个int为例  如果有多个数据项 在此处罗列即可
}node_t;

//数据对象的结构体
typedef struct _List{
    node_t s[N];
    int count;//保存表中已有的数据元素的个数
}list_t;

list_t *create_list_1();
int create_list_2(list_t **p);
int insert_list_by_tail(list_t *my_list, int data);
int print_list(list_t *my_list);
int insert_list_by_pos(list_t *my_list, int pos, int data);
int IsFull(list_t* L);
int IsEmpty(list_t* L);
int  del_list_by_tail (list_t *my_list);
int del_list_by_pos(list_t *my_list ,int pos);
void DestroyList(list_t **L);
void ClearList(list_t *L);
int modify_list_by_pos(list_t *my_list, int pos, int new_data);
int search_list_by_pos(list_t *my_list, int position, int *num);
int overturn_list(list_t *L);
int SortList(list_t *L,int (int ,int, int),int);

int sort_list(list_t *my_list, int flag);
int tichong_list(list_t *my_list);


#endif