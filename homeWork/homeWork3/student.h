#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD_STU 1
#define DEL_STU 2
#define MOD_STU 3
#define CHK_STU 4
#define SOT_STU 5
#define SHW_STU 6
#define QIT_STU 7
#define MAX_STUDENTS 30

typedef struct _STUDENT{
    char name[20]; // 学生的命令
    char gender; // 学生的性别
    int score; // 学生的成绩
}student;

typedef struct _CLA{
    student st[MAX_STUDENTS]; // 班级最大能够容纳30个学生
    int n; // 用来记录班级内的学生的个数
}cla;


//初始化
cla* initClass();
//查询
student* findByName(cla*,char[]);
//添加
int addStudent(cla* ,char [],char ,int );
//删除
void delStudent(cla* ,int);
//修改
void modStudent(cla* ,int );
//遍历
void printAllStudent(cla*);
//排序
void sortByScore(cla* );
//班级成员数量
int clsLen(cla);

//返回学生在数组中的位置
int findIDByName(cla* ,char []);
//冒泡排序
void popSort(cla* c,int len,int control(int ,int ));

//排序控制
int control(int a,int b);

//清空班级
void clearClass(cla* c);
#endif