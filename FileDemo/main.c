#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义学生结构体
typedef struct student{
    char name[30];
    char sex;
    int age;
    float score;
}Stu;
 // 定义链表节点
typedef struct StuNode{
    Stu data;
    struct StuNode *next;
}StuNode;

// 初始化数据到文件中
void initDataToFiles(){
    Stu s[4]={
        {"Tom", 'M', 18, 85.5},
        {"Jerry", 'M', 19, 90.0},
        {"Lily", 'F', 17, 75.0},
        {"Lucy", 'F', 18, 80.0}
    };

    FILE *fp = fopen("students.data", "w+");// 打开文件，以读写方式打开
    if (fp == NULL){// 判断文件是否打开成功
        printf("Open file failed!\n");
        exit(1);
    }

    // 写入数据到文件中
    fwrite((void*)s,sizeof(s),1,fp);
    // 关闭文件
    fclose(fp);
}




// 读取文件中的数据生成链表
StuNode* readDataFromFiles(char* fileName){
    // 打开文件
    FILE *fp = fopen(fileName, "r+");
    if (fp == NULL){
        printf("Open file failed!\n");
        exit(1);
    }else{
        printf("Open file success!\n");
    }
    // 创建头节点
    StuNode *head = (StuNode*)malloc(sizeof(StuNode));
    // 初始化头节点
    head->next = NULL;
    // 读取文件中的数据
    StuNode *cur = (StuNode*)malloc(sizeof(StuNode));
    // 循环读取文件中的数据
    while (fread(&cur->data, sizeof(Stu), 1, fp)){// 读取文件中的数据
            cur->next= head->next;// 给新节点一个指向
             head->next = cur;// 头节点指向新节点 头插法
            cur = (StuNode*)malloc(sizeof(StuNode));// 申请新的节点
    }
    free(cur);// 释放最后申请的节点
    fclose(fp);// 关闭文件
    return head;
}

// 打印链表中的数据
void printList(StuNode* head) {
    StuNode *cur = head->next;// 指向头节点的下一个节点
        while (cur!= NULL) {
            // 循环打印链表中的数据
            printf("姓名：%s 性别：%c 年龄：%d 成绩：%.1f\n", cur->data.name, cur->data.sex, cur->data.age, cur->data.score);
            cur = cur->next;// 指向下一个节点
        }
}

void add(StuNode* head){
    StuNode *cur = (StuNode*)malloc(sizeof(StuNode));
    printf("请输入姓名：");
    scanf("%s",cur->data.name);
    printf("请输入性别：");
    getchar();// 输入回车
    scanf("%c", &cur->data.sex);
    printf("请输入年龄：");
    scanf("%d", &cur->data.age);
    printf("请输入成绩：");
    scanf("%f", &cur->data.score);
    cur->next = head->next;// 给新节点一个指向
    head->next = cur;// 头节点指向新节点 头插法
    printf("添加成功！\n");
}

//查找
StuNode* search(StuNode* head){
    char name[30];
    printf("请输入要查找的姓名：");
    scanf("%s",name);
    StuNode *cur = head->next;// 指向头节点的下一个节点

    while(cur!=NULL){
        // 返回值为0，表示str1和str2相等；
        // 若结果小于0，表示str1的字母顺序小于str2的字母顺序；
        // 若结果大于0，表示str1的字母顺序大于str2的字母顺序。
        if(strcmp(cur->data.name,name)==0){
            return cur;
        }
        cur=cur->next;//指向下一个节点
    }
    printf("没有找到该学生！\n");
    return NULL;
}


//删除
void delete(StuNode* head){


    StuNode* p= search(head);
    if(p==NULL){
        printf("没有找到该学生！\n");
        return;
    }

    while(head->next!=p){
        head=head->next;
    }
    head->next=p->next;//删除节点
    free(p);
    printf("删除成功！\n");
}

//链表长度
int len(StuNode* head){
    int len=0;
    while (head->next!=NULL){
        len++;//遍历链表,统计节点个数
        head=head->next;//指向下一个节点
    }
    return len;
}

//排序
void sortList(StuNode* head){
    int le= len(head);

    //p是要比较的节点,prep是要比较的节点前驱,e是p的下一个节点是被比较的节点
    StuNode *prep,*p,*e,*temp;
    for (int i = 0; i < le-1; ++i) {
        //每次循环都指向头节点
        prep=head;
        p=head->next;
        e=p->next;
        for (int j = 0; j < le-1-i; ++j) {//遍历链表,对每两个相邻节点进行比较
            if(strcmp(p->data.name,e->data.name)>0){

                //交换两个节点的值
                //交换之前的链表形式:prep->p->e
                prep->next=e;
                p->next=e->next;
                e->next=p;
                //交换后的链表形式:prep->e->p
                //保证三个指针的顺序是prep->p->e
                //交换指针p,e的指向
                temp=p;
                p=e;
                e=temp;
                //以下是优化写法
                //p不动
                //e指向p的下一个节点
                //prep指向e
//                prep=e;
//                e=p->next;
//                continue;

            }
            //3个指针向后移动
            prep=prep->next;
            p=p->next;
            e=p->next;
        }
    }
}

//保存到文件
void save(StuNode* head,char* fileName){
    FILE *fp = fopen(fileName, "w+");// 打开文件，以读写方式打开
    if (fp == NULL){// 判断文件是否打开成功
        printf("Open file failed!\n");
        exit(1);
    }
    head=head->next;
    while (head){
        // 写入数据到文件中
        fwrite(&head->data,sizeof(Stu),1,fp);
        head=head->next;
    }
    // 关闭文件
    fclose(fp);
}


//销毁
void destroy(StuNode* head){
    StuNode *temp;
    while (head){
        printf("释放节点\n");
        temp =head;
        head = head->next;
        free(temp);
    }
}
int main() {
    initDataToFiles();
    StuNode *head = (StuNode *) readDataFromFiles("students.data");

    while (1){
        printList(head);
        printf("表长%d\n",len(head)) ;
        printf("==========\n");
        printf("1->add\t 2->search\t 3->delete 4->exit\n");
        int choice;
        scanf("%d",&choice);
        switch(choice){
            case 1:
                add (head);
                printf("add\n");
                sortList(head);
                break;
            case 2:
                printf("search\n");
                StuNode *p = search(head);
                if(p!=NULL){
                    printf("找到该学生：\n");
                    printf("姓名：%s 性别：%c 年龄：%d 成绩：%.1f\n", p->data.name, p->data.sex, p->data.age, p->data.score);
                    printf("**************************\n");
                }
                break;
            case 3:
                printf("delete\n");
                delete(head);
                break;
            case 4:
                printf("exit\n");
                save(head,"students.data");
                destroy(head);
                return 0;
            default:
                printf("输入错误\n");
                break;
        }
    }
}