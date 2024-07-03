#include "link_list.h"

int main(){
    LNode *head;
    initList(&head);
    printf("head=%p\n",head);
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");

    //测试头插
    insert(head,100);
    insert(head,200);
    insert(head,300);
    printList(head);
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    //300 200 100
    printf("----------------------------\n");
    //测试尾插
    append(head,400);
    append(head,500);
    append(head,600);
    printList(head);
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    //300 200 100 400 500 600
    printf("----------------------------\n");
    //测试插入链表指定位置
    insertAt(head,333,1);
    insertAt(head,444,0);
    insertAt(head,555,8);//最后一个插入
    insertAt(head,666,10);//报错///insertAt()的插入位置不合理
    printList(head);//444 300 333 200 100 400 500 600 555
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");
    //链表删除元素头删
    delete(head);
    delete(head);
    printList(head);//333 200 100 400 500 600 555
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");
    //删除链表元素尾删
    deleteTail(head);
    printList(head);//333 200 100 400 500 600
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));//length=6
    printf("----------------------------\n");
    //链表中查找指定位置元素
    LNode *N=NULL;
    searchAt(head,-1);//位置不合理
    N=searchAt(head,6);//位置不合理
    N=searchAt(head,5);//查找数据:600
    if(N){
        printf("查找数据:%d\n",N->data);
    } else{
        printf("没查到\n");
    }
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");
    //修改链表指定位置元素
    modify(head,777,0);
    modify(head,888,6);//modify()的修改位置不合理
    printList(head);//777 200 100 400 500 600
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");
    //链表删除指定位置元素
    deleteAt(head,0);
    printList(head);//200 100 400 500 600
    printf("Empty=%d\n",isEmpty(head));
    printf("length=%d\n",length(head));
    printf("----------------------------\n");
    //清空链表
    clearList(head);
    printf("head=%p\n",head);//head=0000000000B11450
    printf("head->next=%p\n",head->next);//head->next=0000000000000000
    printList(head);//表为空
    printf("Empty=%d\n",isEmpty(head));//Empty=1
    printf("length=%d\n",length(head));//length=0
    printf("----------------------------\n");

    //销毁
    destroyList(&head);
    printf("head=%p\n",head);//head=0000000000000000
    printf("----------------------------\n");
}