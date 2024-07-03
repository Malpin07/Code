#include "loop_queue.h"

int create_queue(queue_t **my_queue){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return -1;
    }
    *my_queue = (queue_t *)malloc(sizeof(queue_t));
    if(NULL == *my_queue){
        printf("内存分配失败\n");
        return -1;
    }
    (*my_queue)->front = (*my_queue)->rear = 0;
    return 0;
}

//返回1 满了  返回0 没满
int is_full(queue_t *my_queue){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return -1;
    }
    return (my_queue->rear+1)%N == my_queue->front ? 1 : 0;
}

int push_queue(queue_t *my_queue, int data){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return -1;
    }
    if(is_full(my_queue)){
        printf("队列满 入队列失败\n");
        return -1;
    }
    my_queue->s[my_queue->rear] = data;
    my_queue->rear = (my_queue->rear+1)%N;
    return 0;
}

//返回1 空了  返回0 没空
int is_empty(queue_t *my_queue){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return -1;
    }
    return my_queue->rear == my_queue->front ? 1 : 0;
}

int pop_queue(queue_t *my_queue, int *data){
    if(NULL == my_queue || NULL == data){
        printf("入参为NULL\n");
        return -1;
    }
    if(is_empty(my_queue)){
        printf("队列空 出队列失败\n");
        return -1;
    }
    *data = my_queue->s[my_queue->front];
    my_queue->front = (my_queue->front+1)%N;
    return 0;
}

int clean_queue(queue_t *my_queue){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return -1;
    }
    //此处只需要让rear==front即可 不必置0
    my_queue->rear = my_queue->front = 0;
    return 0;
}

int destroy_queue(queue_t **my_queue){
    if(NULL == my_queue || NULL == *my_queue){
        printf("入参为NULL\n");
        return -1;
    }
    free(*my_queue);
    *my_queue = NULL;
    return 0;
}

int print_queue(queue_t *my_queue){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return -1;
    }
    for(int i = my_queue->front; i != my_queue->rear; i=(i+1)%N){
        printf("%d  ", my_queue->s[i]);
    }
    printf("\n");
    return 0;
}