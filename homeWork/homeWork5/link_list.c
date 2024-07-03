#include "link_list.h"

int  create_node(node_t **head, ElemType data){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }

    *head=(node_t*)calloc(1, sizeof(node_t));
    if(*head){
        printf("创建成功\n");
        (*head)->data=data;
        (*head)->next=NULL;
        return 0;
    }
    return -1;
}

//遍历
int print_list(node_t *head){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    node_t *temp=head;
    while (temp->next){
        temp=temp->next;
        printf("%d  ,",temp->data);


    }
    printf("\n");
    return 0;
}

//在链表头插入元素
int insert_list_by_head(node_t *head ,ElemType data){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    node_t *newNode;
    newNode=(node_t*)calloc(1, sizeof(node_t));
    if(newNode){
        newNode->data=data;
        newNode->next=head->next;
        head->next=newNode;

        return 0;
    }
    return -1;
}

//在链表末位插入元素
int insert_list_by_tail(node_t *head, ElemType data){//typedef int ElemType;
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->data = data;//给新节点赋值
    newNode->next = NULL;//新节点的指针域置为空
    node_t *p = head;
    while(p->next!= NULL){//遍历链表，找到最后一个节点
        p = p->next;//p指向下一个节点
    }
    p->next = newNode;//将新节点插入到链表末尾
    return 0;
}




//插入任意位置
int insert_list_by_pos(node_t *head,int pos, ElemType data){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    if(pos <0){
        printf("位置错误\n");
        return -1;
    }
    node_t *temp= head;
    int i=0;
    for (i=0; i<pos; i++){
        if(temp->next==NULL){
            break;
        }
        temp=temp->next;
    }
    if(i<pos){
        printf("位置错误\n");
        return -1;
    }
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->data = data;//给新节点赋值
    newNode->next = NULL;//新节点的指针域置为空
    //执行插入操作
    newNode->next = temp->next;
    temp->next = newNode;
    return 0;

}






//头删
int delete_list_by_head( node_t *head ){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    if(head->next==NULL){
        printf("链表为空\n");
        return -1;
    } else{
        node_t *temp=head->next;
        head->next=temp->next;
        free(temp);
        return 0;
    }

}

//尾删
int delete_list_by_tail( node_t *head ){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    node_t *p=head;
    if(head->next==NULL){
        printf("链表为空\n");
        return -1;
    } else{
        while(p->next->next!=NULL){
            p=p->next;
        }
        node_t *temp=p->next;
        p->next=NULL;
        free(temp);
        return 0;
    }
}

//删除任意位置
int delete_list_by_pos( node_t *head, int pos){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    if(pos<0){
        printf("位置错误\n");
        return -1;
    }
    if(head->next==NULL){
        printf("链表为空\n");
        return -1;
    }
    //找到删除位置
    node_t *p=head;//
    int i=0;
    for (i=0; i<pos; i++){
        if(p->next->next==NULL){//如果下下个节点为空,说明位置错误
            printf("位置错误\n");
            return -1;
        }
        p=p->next;//p指向下一个节点
    }

    //找到了删除位置
    node_t* temp= p->next;
    //执行删除操作
    p->next=p->next->next;
    free(temp);
    return 0;



}

//修改指定位置元素
int modify_list_by_pos( node_t *head, int pos, ElemType data){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    if(pos<0){
        printf("位置错误\n");
        return -1;
    }
    if(head->next==NULL){
        printf("链表为空\n");
        return -1;
    }

    node_t * temp;
    if(search_list_by_pos(head,pos,&temp) !=-1){
        temp->data=data;
    }

    return 0;

}
//查找指定位置元素
int search_list_by_pos( node_t *head, int pos, node_t **data){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    if(pos<0){
        printf("位置错误\n");
        return -1;
    }
    node_t *p= head;
    int i=0;
    for (i=0; i<pos; i++){
        if(p->next->next==NULL){
            printf("位置错误\n");
            return -1;
        }
        p=p->next;
    }
    *data=p->next;

    return 0;
}

int clean_list(node_t *head){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    //删除节点
    node_t *temp=NULL;
    while (NULL != head->next){
         temp=head->next;
         head->next= head->next->next;
        free(temp);
    }
    temp=NULL;
    return 0;
}

int destroy_list(node_t **phead){
    if(NULL == phead || NULL == *phead){
        printf("入参为NULL\n");
        return -1;
    }
    //防止用户没有清空直接销毁导致内存泄漏
    //所以在此处调用一次清空
    clean_list(*phead);
    free(*phead);
    *phead = NULL;
    return 0;
}

//两个链表合并
int merge_list( node_t *head1, node_t **head2){
    if(NULL==head1 || NULL==head2 || NULL==*head2){
        printf("入参为空\n");
        return -1;
    }
    node_t * temp=(*head2)->next;
    (*head2)->next=NULL;
    free((*head2));
    (*head2)=NULL;

    node_t *temp2=head1;
    while (temp2->next){
        temp2=temp2->next;
    }
    temp2->next=temp;
}



//表长
int lengthLinkList(node_t *head){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    int len = 0;
    node_t *p = head->next;
    while(p!= NULL){
        len++;
        p = p->next;
    }
    return len;
}
//链表排序
int sort_list(node_t *head){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    int len= lengthLinkList(head);
    if(len==0||len==1){
        printf("无需排序\n");
        return -1;
    }
    node_t* node=head->next;//跳过头节点
    node_t* temp;
    for (int i = 0; i < len-1; ++i) {
        temp=node;
        for (int j = 0; j < len-i-1; ++j) {
            if(temp->data>temp->next->data){
                temp->data = temp->data ^ temp->next->data;
                temp->next->data = temp->data ^ temp->next->data;
                temp->data = temp->data ^ temp->next->data;
            }
            temp=temp->next;
        }
    }
    return 0;
}


//链表剔重
int tichong_list(node_t *head){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    if(head->next==NULL){
        printf("链表为空\n");
        return -1;
    }
    if(head->next->next==NULL){
        printf("链表只有一个数据\n");
        return -1;
    }
    node_t *p = head->next;//指向头节点的下一个节点
    node_t *q=NULL;//指向当前节点p的下一个节点
    node_t *temp=NULL;//保存当前节点p,用来删除重复节点
    while (p != NULL) {
    temp = p;//缓存当前节点 p。
    q = p->next;
    // 内层循环用来检查后续节点是否存在与当前节点相同数据的节点
    while (q != NULL) {
        // 找到重复的节点
        if (p->data == q->data) {
            temp->next = q->next; // 从链表中删除重复节点
            free(q); // 释放重复节点的内存
            q = temp->next; // 指向下一个待检查的节点
        } else {//如果数据不相同
            temp = q;//将 temp 更新为 q 节点
            q = q->next;//q 移动到下一个节点。
        }
    }
    p = p->next;//外层循环更新 p 为下一个节点，继续查看下一个节点。
}

//    node_t *p =head;
//    node_t *q=NULL;
//    node_t *temp=NULL;
//    while (p->next!=NULL){
//        q=p;//q指向p
//        while (q->next!=NULL){
//           if (p->data == q->next->data){
//               temp= q->next;
//               q->next=q->next->next;
//               free(temp);
//           } else{
//               q=q->next;
//           }
//        }
//        p=p->next;
//    }
    return 0;
}


//链表翻转
int overturn_list(node_t *head){
    if(NULL==head){
        printf("入参为空\n");
        return -1;
    }
    if(NULL==head->next){
        printf("链表为空\n");
        return -1;
    }
    node_t *p = head->next;//指向头节点的下一个节点
    head->next=NULL;//头节点的指针域置为空
    node_t *temp;
    while(p!= NULL){//遍历链表,逆置节点
        temp=p;//保存当前节点p
        p=p->next;//先将p移动到下一个节点
        temp->next=head->next;//将当前节点的指针域指向头节点的下一个节点,第一次指空,第二次是头插
        head->next=temp;//将头节点的指针域指向当前节点
    }
    return 0;
}
