#ifndef QUEUE_H
#define QUEUE_H

typedef struct _QueueNode{
    char data;
    struct _QueueNode* next;
}QueueNode;
typedef struct _QueueLink{
    QueueNode * front;//前
    QueueNode * rear;//后
}QueueLink;

//初始化
void initQueue(QueueLink* queue);
//判断满
int isQueueFull(QueueLink* queue);
//判断空
int isQueueEmpty(QueueLink* queue);
//入队
void enQueue(QueueLink* queue,char data);
//出队
char deQueue(QueueLink* queue);
//清空
void resetQueue(QueueLink* queue);
//删除
void clearQueue(QueueLink* queue);





#endif