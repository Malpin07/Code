#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct _QueueNode{
//    int data;
//    struct _QueueNode* next;
//}QueueNode;
//
//typedef struct _QueueLink{
//    QueueNode * rear;
//    QueueNode * front;
//    int count;
//}Link_queue;
//
//
//int create_queue(Link_queue **my_queue);
//int push_queue(Link_queue *my_queue, int data);
//int is_empty(Link_queue *my_queue);
//int pop_queue(Link_queue *my_queue, int *data);
//int clean_queue(Link_queue *my_queue);
//int destroy_queue(Link_queue **my_queue);
//int print_queue(Link_queue *my_queue);


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//链表节点结构体
typedef struct _Node{
    int data;
    struct _Node *next;
}node_t;

//链式队列的结构体
typedef struct _Queue{
    node_t *front;
    node_t *rear;
    int count;
}queue_t;

int create_queue(queue_t **my_queue);
int push_queue(queue_t *my_queue, int data);
int is_empty(queue_t *my_queue);
int pop_queue(queue_t *my_queue, int *data);
int clean_queue(queue_t *my_queue);
int destroy_queue(queue_t **my_queue);
int print_queue(queue_t *my_queue);

#endif
