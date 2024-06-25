#ifndef QUEUE_H
#define QUEUE_H

typedef struct _Queue{
    char  * _space;
    int _len;
    int _rear;
    int _front;
}Queue;

//初始化
void initQueue(Queue* queue,int size);
//判断满
int isQueueFull(Queue* queue);
//判断空
int isQueueEmpty(Queue* queue);
//入队
void enQueue(Queue* queue,char data);
//出队
char deQueue(Queue* queue);
#endif