#include "student.h"
char sname[20]; // 学生的名字
char sgender; // 学生的性别
int sscore; // 学生的成绩
student* tStu;//temp student
int sub;//学生在数组中位置
char YorN=0;
void add_stu(cla* TheClass){
    printf("输入学生信息:\n");
    printf("输入名字:");
    scanf("%s",sname);
    getchar();
    printf("输入性别:");
    scanf("%c",&sgender);
    printf("输入成绩:");
    scanf("%d",&sscore);

    printf("学生姓名:%s 性别:%c 成绩:%d\n",sname,sgender,sscore);
    int t= addStudent(TheClass,sname,sgender,sscore);
    if(t==1)printf("添加成功了!\n");
}

void del_stu(cla* TheClass){


    printf("输入要删除的学生姓名:");
    scanf("%s",sname);
    getchar();
    sub= findIDByName(TheClass,sname);

    if (sub==-1){
        printf("没有这个学生!\n");
    } else{
        printf("确定要删除吗?[Y/N]:");
        scanf("%c",&YorN);
        if (YorN==89||YorN==121){
            delStudent(TheClass ,sub);
            printf("删除\n");
        } else{
            return;
        }
    }

}
void mod_stu(cla* TheClass){
    printf("输入要修改的学生姓名进行查找:");
    scanf("%s",sname);
    getchar();
    tStu= findByName(TheClass,sname);


    if (sub==-1){
        printf("没有这个学生!\n");
    } else{
        printf("确定要修改吗?[Y/N]:");
        scanf("%c",&YorN);
        if (YorN==89||YorN==121){
            modStudent(TheClass ,sub);
        } else{
            return;
        }
    }
}

void chk_stu(cla* TheClass){
    printf("输入要查找的学生姓名:");
    scanf("%s",sname);
    getchar();
    tStu= findByName(TheClass,sname);
    if (NULL==tStu){
        printf("没有这个学生!\n");
    } else{
        printf("找到:\n");
        printf("姓名:%s,性别%c,成绩%d \n",tStu->name,tStu->gender,tStu->score);
    }
}








































































































