#include "Queue.h"
#include <stdlib.h>
//初始化
void initQueue(Queue* queue,int size){
    queue->_len=size;
    queue->_space=(char *) malloc(sizeof(queue->_len));
    queue->_rear=queue->_front=0;

}
//判断满
int isQueueFull(Queue* queue){
    return (queue->_rear+1)%queue->_len==queue->_front;
}
//判断空
int isQueueEmpty(Queue* queue){
    return queue->_rear==queue->_front;
}
//入队
void enQueue(Queue* queue,char data){
    queue->_space[queue->_rear]=data;
    queue->_rear++;
    queue->_rear=queue->_rear % queue->_len;

}
//出队
char deQueue(Queue* queue){
    char ch=queue->_space[queue->_front];
    queue->_front++;
    queue->_front=queue->_front % queue->_len;

    return ch;
}