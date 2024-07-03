#include "link_queue.h"
#include "link_queue.h"

int create_queue(queue_t **my_queue){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return -1;
    }
    *my_queue = (queue_t *)malloc(sizeof(queue_t));
    if(NULL == *my_queue){
        printf("内存分配失败\n");
        return 0;
    }
    memset(*my_queue, 0, sizeof(queue_t));
    return 0;
}

int push_queue(queue_t *my_queue, int data){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return 0;
    }
    //创建新节点
    node_t *pnew = (node_t *)malloc(sizeof(node_t));
    if(NULL == pnew){
        printf("内存分配失败\n");
        return -1;
    }
    pnew->data = data;
    pnew->next = NULL;
    //此处判断rear也行 判断 front 也可以  两个都判断也行
    if(NULL == my_queue->front && NULL == my_queue->rear){
        my_queue->front = pnew;
        my_queue->rear = pnew;
    }else{
        my_queue->rear->next = pnew;
        my_queue->rear = pnew;
    }
    my_queue->count++;
    return 0;
}

//返回1 空  返回0 没空
int is_empty(queue_t *my_queue){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return 0;
    }
    return NULL == my_queue->rear && NULL == my_queue->front ? 1 : 0;
}

int pop_queue(queue_t *my_queue, int *data){
    if(NULL == my_queue || NULL == data){
        printf("入参为NULL\n");
        return 0;
    }
    if(is_empty(my_queue)){
        printf("队列空 出队列失败\n");
        return -1;
    }
    *data = my_queue->front->data;
    node_t *pdel = my_queue->front;
    my_queue->front = pdel->next;
    free(pdel);
    pdel = NULL;
    if(NULL == my_queue->front){
        my_queue->rear = NULL;//最后一个元素出队列后 让rear也置NULL
    }
    my_queue->count--;
    return 0;
}

int clean_queue(queue_t *my_queue){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return 0;
    }
    node_t *pdel = NULL;
    while(NULL != my_queue->front){
        pdel = my_queue->front;
        my_queue->front = pdel->next;
        free(pdel);
    }
    pdel = NULL;
    my_queue->rear = NULL;
    return 0;
}

int destroy_queue(queue_t **my_queue){
    if(NULL == my_queue || NULL == *my_queue){
        printf("入参为NULL\n");
        return 0;
    }
    //先清空再销毁
    clean_queue(*my_queue);
    free(*my_queue);
    *my_queue = NULL;
    return 0;
}

int print_queue(queue_t *my_queue){
    if(NULL == my_queue){
        printf("入参为NULL\n");
        return 0;
    }
    node_t *ptemp = my_queue->front;
    while(NULL != ptemp){
        printf("%d  ", ptemp->data);
        ptemp = ptemp->next;
    }
    printf("\n");
    return 0;
}
//
////初始化队列
//int create_queue(Link_queue **my_queue){
//    *my_queue=(Link_queue*)malloc(sizeof(Link_queue));
//    (*my_queue)->front=(*my_queue)->rear=(QueueNode *)malloc(sizeof(QueueNode));
//    (*my_queue)->count=0;
//    return 0;
//}
//
////入队
//int push_queue(Link_queue *my_queue, int data){
//    if(my_queue->rear==NULL){
//        my_queue->rear=(QueueNode*)malloc(sizeof(QueueNode));
//        my_queue->front->next=my_queue->rear;
//        my_queue->rear->data=data;
//        my_queue->rear->next=NULL;
//    }else {
//
//        QueueNode *newnode = (QueueNode *) malloc(sizeof(QueueNode));
//        newnode->data=data;
//        newnode->next=NULL;
//        my_queue->rear->next=newnode;
//        my_queue->rear=newnode;
//    }
//    my_queue->count++;
//    return 0;
//}
//
//int is_empty(Link_queue *my_queue){
//    return my_queue->rear==my_queue->front?1:0;
//}
//
//int pop_queue(Link_queue *queue, int *data){
//    if(is_empty(queue)){
//        printf("队列是空");
//        return -1;
//    }
//
//    *data=queue->front->next->data;
//    if (queue->front->next==queue->rear){//相等出队的是最后一个节点
//        queue->rear=queue->front;
//        free(queue->front->next);//释放
//        queue->front->next=NULL;//置空指针
//    } else{
//        //出队的是头结点后的节点
//        QueueNode *temp=queue->front->next;
//        queue->front->next=queue->front->next->next;
//        free(temp);
//    }
//    return 0;
//
//}
//
//int clean_queue(Link_queue *my_queue);
//int destroy_queue(Link_queue **my_queue);
//int print_queue(Link_queue *my_queue){
//
//    QueueNode* temp= my_queue->front;
//
//    for (int i = 0; i < my_queue->count; ++i) {
//        printf("%d  ,",temp->data);
//        temp=temp->next;
//    }
//    printf("\n");
//    return 0;
//}