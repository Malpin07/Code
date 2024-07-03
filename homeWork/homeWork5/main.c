#include "link_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_t* createList(ElemType data);//环形链表初始化
int insert_list(node_t *head, ElemType data);//环形链表插入节点
int print_l(node_t *head);
//约瑟夫环
int main( int argc,const char *argv[]) {
    if(argc!= 3){
        printf("参数错误\n");
        return -1;
    }
       int man =  atoi(argv[1]) ;
       int num =  atoi(argv[2]) ;
    printf("人数:%d  ,报数:%d\n",man,num);
    //人数5 ,报数 3
    //创建链表
    node_t *head = NULL;
    head = createList(1);
    //插入节点
    for (int i = 2; i <=man ; ++i) {
        insert_list(head, i);

    }
    //打印链表
    print_l(head);
    printf("\n");
    //报数开始
    int flag=0;
    node_t *temp=head;
    int n=0;
    while (head->next!=head){//循环到最后一个节点,环形链表,最后一个节点的next指向head

        flag++;// flag 计数 =1 (从0开始++ =1)
        if(flag==num){//报数到达
                      // head的位置是要删除节点
            n++;
            //删除
            printf("第%d次删除 :%d ,\n",n,head->data);
            temp->next=head->next;//temp指向head的前一个节点,将要删除节点(head)的下一个节点链接到temp
            free(head);//释放head节点
            head=temp->next;//head重新指向删除后的下一个节点
            flag=0;//清空计数
            print_l(head);//打印
            printf("\n");//换行
        //未到达报数
        }else{
            temp=head;
            head=head->next;//head后移
            //temp一直指向head前一个节点,用于删除节点.
        }

    }



    /*node_t *phead = NULL;
    create_node(&phead, -1);
    node_t *phead2 = NULL;
    create_node(&phead2, -1);
    printf("phead = %p\n", phead); // 非NULL

    //测试头插
    insert_list_by_head(phead, 10);
    insert_list_by_head(phead, 20);
    insert_list_by_head(phead, 30);
    print_list(phead); // 30 20 10

    //测试尾插
    insert_list_by_tail(phead, 40);
    insert_list_by_tail(phead, 50);
    insert_list_by_tail(phead, 60);
    print_list(phead); // 30 20 10 40 50 60

    //测试任意位置插入
    insert_list_by_pos(phead, 7, 100); //位置不合理
    insert_list_by_pos(phead, 6, 200);
    insert_list_by_pos(phead, 2, 300);
    print_list(phead); // 30 20 300 10 40 50 60 200

    //测试头删
    delete_list_by_head(phead);
    delete_list_by_head(phead);
    print_list(phead); // 300 10 40 50 60 200

    //测试尾删
    delete_list_by_tail(phead);
    delete_list_by_tail(phead);
    print_list(phead); // 300 10 40 50

    //测试任意位置删除
    delete_list_by_pos(phead, 4);//位置不合理
    delete_list_by_pos(phead, 3);
    delete_list_by_pos(phead, 1);
    print_list(phead); // 300 40


    node_t *n;
    if(search_list_by_pos(phead,0,&n) !=-1){
        printf("%d \n",n->data);//300
    }
    modify_list_by_pos(phead,0,200);
    print_list(phead); // 200  ,40  ,


    insert_list_by_head(phead2, 10);
    insert_list_by_head(phead2, 20);
    insert_list_by_head(phead2, 30);
    //合并链表
    merge_list(phead,&phead2);
    print_list(phead);//200  ,40  ,30  ,20  ,10  ,
    //翻转链表
    overturn_list(phead);
    print_list(phead);//200  ,40  ,30  ,20  ,10  ,



    insert_list_by_pos(phead, 2, 300);
    insert_list_by_pos(phead, 2, 440);
    sort_list(phead);
    print_list(phead);//10  ,20  ,30  ,40  ,200  ,300  ,440  ,
    //测试翻转
    overturn_list(phead);
    print_list(phead); // 440  ,300  ,200  ,40  ,30  ,20  ,10  ,

    //测试剔重
    insert_list_by_pos(phead, 3, 90);
    insert_list_by_pos(phead, 3, 90);
    insert_list_by_pos(phead, 6, 80);
    insert_list_by_pos(phead, 8, 80);
    insert_list_by_tail(phead, 90);
    insert_list_by_tail(phead, 90);
    insert_list_by_tail(phead, 90);
    insert_list_by_tail(phead, 190);
    insert_list_by_tail(phead, 190);
    print_list(phead); // 440  ,300  ,200  ,90  ,90  ,40  ,80  ,30  ,80  ,20  ,10  ,90  ,90  ,90  ,
    tichong_list(phead);
    print_list(phead); // 440  ,300  ,200  ,90   ,40  ,80  ,30 ,20  ,10*/
    return 0;
}
//环形链表初始化
node_t* createList(ElemType data){
    node_t *head=(node_t*)malloc(sizeof (node_t));
    head->data=data;
    head->next=head;
    return head;
}
//插入节点
int insert_list(node_t *head, ElemType data){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->data = data;//给新节点赋值
    //插到末尾
    node_t* temp = head;
    while(temp->next!=head){
        temp=temp->next;
    }
    temp->next=newNode;
    newNode->next=head;
    return 0;
}
//遍历环形链表
int print_l(node_t *head){
    node_t *temp=head;
    do {
        printf("%d  ",temp->data);
        temp=temp->next;
    } while (temp!=head);

}

