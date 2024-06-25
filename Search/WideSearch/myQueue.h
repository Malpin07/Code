#ifndef QUEUE_H
#define QUEUE_H
typedef struct _Point{
    int _x;
    int _y;
}Point;
typedef struct _QueueNode{
    Point data;
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
void enQueue(QueueLink* queue,Point data);
//出队
Point deQueue(QueueLink* queue);
//清空
void resetQueue(QueueLink* queue);
//删除
void clearQueue(QueueLink* queue);





#endif