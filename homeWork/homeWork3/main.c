#include "student.h"
#include "controller.h"
int main(int argc, const char* argv[])
{
    int flg=-1;

    //初始化Class
    cla * TheClass = initClass();
    printf("%d！\n",TheClass->n);
    //显示欢迎界面
    while (flg) {
        puts("---------------欢迎进入学生管理系统------------------");
        puts("------------1.添加 2.删除 3.修改 4.查询 ------------");
        puts("---------------5.排序 6.展示 7.退出-----------------");
        puts("---------------------------------------------------");
        printf("输入选择 -> ");
        scanf("%d", &flg);

       //getchar();
        switch (flg) {
            case ADD_STU:
                add_stu(TheClass);
                break;
            case DEL_STU:
                del_stu(TheClass);
                break;
            case MOD_STU:
                mod_stu(TheClass);
                break;
            case CHK_STU:
                chk_stu(TheClass);
                break;
            case SOT_STU:
                sortByScore(TheClass);
                break;
            case SHW_STU:
                printAllStudent(TheClass);
                break;
            case QIT_STU:
                flg = 0;
                clearClass(TheClass);
                break;
            default:
                printf("输入选择错误，再试一次\n");
                continue;
        }
        //刷新缓冲区
        fflush(stdin);

    }

    return 0;
}