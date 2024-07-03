#ifndef loop_QUEUE_H
#define loop_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

//循环队列的结构体
typedef struct _Queue{
    int s[N];
    int front;
    int rear;
}queue_t;

int create_queue(queue_t **my_queue);
int is_full(queue_t *my_queue);
int push_queue(queue_t *my_queue, int data);
int is_empty(queue_t *my_queue);
int pop_queue(queue_t *my_queue, int *data);
int clean_queue(queue_t *my_queue);
int destroy_queue(queue_t **my_queue);
int print_queue(queue_t *my_queue);

#endif