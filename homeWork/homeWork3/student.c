#include "student.h"


int ctrl=1;
//初始化班级
cla* initClass(){
    cla *c=(cla*)malloc(sizeof(cla));
    if(NULL == c) exit(0);
    c->n=-1;
    printf("班级初始化成功!\n");
    return c;
}

//查询
student* findByName(cla* c,char name[]){
    if (NULL==name){
        printf("学生姓名不能为空!\n");
        return NULL;
    }


    int i = 0;
    for ( ;i <= c->n; ++i) {
        if(!strcmp(c->st[i].name,name)){
            return &(c->st[i]);
        }
    }
    return NULL;
}
//返回学生在数组中的位置
int findIDByName(cla* c,char name[]){
    if(c->n==-1){
        printf("系统中没有信息!\n");
    }

    int i = 0;
    for ( ;i <= c->n; ++i) {
        if(!strcmp(c->st[i].name,name)){
            printf("找到学生:\n");
            printf("姓名:%s,性别%c,成绩%d",c->st[i].name,c->st[i].gender,c->st[i].score);
            return i;
        }
    }

    return -1;
}

//添加
int addStudent(cla* c,char name[],char gender,int score){
//    student *stu=(student*)malloc(sizeof(student));
//    if(NULL == stu) exit(0);
//
//    strcpy(stu->name,name);
//    stu->gender=gender;
//    stu->score=score;
//    printf("s-%s %c %d\n",stu->name,stu->gender,stu->score);

//    int l=clsLen(*c);
//    if(l>=MAX_STUDENTS){
//        printf("班级已满!\n");
//        return 0;
//    }
//    c->st[l]=*stu;
    int l=clsLen(*c);
    if(l>MAX_STUDENTS){
        printf("班级已满!\n");
        return 0;
    } else{
        strcpy(c->st[l].name,name);
        c->st[l].gender=gender;
        c->st[l].score=score;
        printf("添加了学生:\n");
        printf("姓名:%s 性别:%c 成绩:%d \n",c->st[l].name,c->st[l].gender,c->st[l].score);
    }
    //printf("c-%s %c %d",c->st[0].name,c->st[0].gender,c->st[0].score);
    ++c->n;
    return 1;
   // printf("c-n:%d",c->n);
}
//删除
void delStudent(cla* c,int sub){
    int i=0;
    for (i = sub; i<=c->n; ++i) {
        c->st[i]=c->st[i+1];
    }
    c->n--;



}
//修改
void modStudent(cla* c,int sub ){
    printf("输入学生信息:\n");
    printf("输入名字:");
    scanf("%s",c->st[sub].name);
    getchar();
    printf("输入性别:");
    scanf("%c",&c->st[sub].gender);
    printf("输入成绩:");
    scanf("%d",&c->st[sub].score);

    printf("更新了数据:\t");
    printf("学生姓名:%s 性别:%c 成绩:%d \n",c->st[sub].name,c->st[sub].gender,c->st[sub].score);

}
//遍历
void printAllStudent(cla* c){


    if(c->n==-1){
        printf("系统中没有信息!\n");
    } else{
        printf("班级中学生信息:\n");
        int i = 0;
        printf("系统中共存储%d位学生信息\n",c->n+1);
        for ( ;i <= c->n; ++i) {
            printf("学生姓名:%s 性别:%c 成绩:%d \n",c->st[i].name,c->st[i].gender,c->st[i].score);
        }
    }


}




//排序
void sortByScore(cla* c){
    printf("按照成绩排序,输入1是从大到小排序,输入2是从小到大排序:");
    scanf("%d",&ctrl);//int CONT=1;//控制排序
    popSort(c,c->n,control);

}
//班级成员数量
int clsLen(cla c){
    return c.n+1;
}

//冒泡排序
void popSort(cla* c,int len,int control(int ,int )){
    for (int i = 0; i <= len-1 ; ++i) {
        for (int j = 0; j <= len-i-1; ++j) {
            if (control(c->st[j].score , c->st[j+1].score)){
                student temp;
                temp= c->st[j];
                c->st[j]= c->st[j+1];
                c->st[j+1]= temp;
            }
        }
    }
}


int control(int a,int b){
    if (ctrl==2){
        return a>b?1:0;
    } else
        return a<b?1:0;
}


//释放内存
void clearClass(cla* c){
    free(c);
    c=NULL;

    printf("班级已清空!\n");
}