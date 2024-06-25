#ifndef __Tree_QUEUE_H__
#define __Tree_QUEUE_H__
typedef struct _TreeNode{
    char _data;
    struct _TreeNode *_left;
    struct _TreeNode *_right;

}TreeNode;
typedef struct _QueueNode{
    TreeNode* data;
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
void enQueue(QueueLink* queue,TreeNode* data);
//出队
TreeNode* deQueue(QueueLink* queue);
//清空
void resetQueue(QueueLink* queue);
//删除
void clearQueue(QueueLink* queue);





#endif