#include "QueueLink.h"
#include <stdlib.h>
#include <stdio.h>
//初始化
void initQueue(QueueLink* queue){
    //创建头节点
    //queue->front始终指向头
    queue->front=queue->rear=(QueueNode*)malloc(sizeof(QueueNode));
    //queue->rear->next=NULL;
}
//判断满
int isQueueFull(QueueLink* queue);
//判断空
int isQueueEmpty(QueueLink* queue){
    return queue->front==queue->rear;
}
//入队
void enQueue(QueueLink* queue,char data) {
    QueueNode *cur = (QueueNode *) malloc(sizeof(QueueNode));
    cur->data=data;
    cur->next=NULL;//新进永远是尾
    //第一个进来,queue->rear和 queue->front是同一个
    queue->rear->next=cur;
    queue->rear=cur;//移动rear指向新节点
}
//出队
char deQueue(QueueLink* queue){
    char ch=queue->front->next->data;
    if (queue->front->next==queue->rear){//相等出队的是最后一个节点
        queue->rear=queue->front;
        free(queue->front->next);//释放
        queue->front->next=NULL;//置空指针
    } else{
        //出队的是头结点后的节点
        QueueNode *temp=queue->front->next;
        queue->front->next=queue->front->next->next;
        free(temp);
    }
    return ch;
}
//清空
void resetQueue(QueueLink* queue){
    //保留头节点,使用head删除所有节点
    QueueNode* head= queue->front->next;
    queue->front->next=NULL;
    queue->rear = queue->front;
    QueueNode *temp;
    while (head){//head不为空就循环
        temp=head->next;
        printf("释放 %c\n",head->data);
        free(head);
        head=temp;//head后移
    }

}
//删除
void clearQueue(QueueLink* queue){
    resetQueue(queue);
    free(queue->front);
    printf("释放头节点");

}