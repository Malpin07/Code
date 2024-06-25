# c语言中的结构体
## 结构体的定义
```c
struct 结构类型名{
    变量类型 成员1;
    变量类型 成员2;
    变量类型 成员3;
    变量类型 成员4;
    ...
}；
```
```shell
结构体的关键字是struct

结构体类型名说明的是结构体的类型，在定义结构体的时候类型名可以省略。

结构体中所有的成员都放在{}中，{}后必须写;

结构体中可以有多个成员，成员的类型可以相同也可以不同。结构体是构造类型的一种。

结构体成员的类型可以是

基本类型char,short,int,long,double,float

数组：char a[3],int b[5]

指针类型：char *,int *,double *,float *,void *

结构体类型：结构体中可以嵌套结构体

结构体中不能写函数，但可以是函数指针。

结构体类型定义变量的方法

struct 结构体类型名 变量;

struct 结构体类型名 *指针变量;

访问内部成员的方法

变量.成员

指针变量->成员
```

## 结构体的使用
```c
定义变量方法1：
struct student{
char name[20];
int age;
char sex;
}stu1;
定义变量方法2：
struct student stu2;
```
## 结构变量的赋值
```c
方法1：定义变量的同时赋值
struct student{
    char name[20];
    int age;
    char sex;
}stu1 = {"zhangsan",20,'m'};

struct student stu2 = {"lisi",22,'w'};
方法2：先定义后赋值
struct student{
    char name[20];
    int age;
    char sex;
}stu1;
struct student stu2;

strcpy(stu1.name,"zhangsan");
stu1.age = 20;
stu1.sex = 'm';
    
strcpy(stu2.name,"lisi");
stu2.age=22;
stu2.sex='w';

方法2：跳成员赋值
struct student{
    char name[20];
    int age;
    char sex;
}stu1 = {
    .name = "zhangsan",
    .sex = 'm',
};

struct student stu2 = {
    .age = 22,
    .sex = 'w'
};
```
## 结构体数组的定义


```c
struct student{
    char name[20];
    int age;
    char sex;
}stu[3];
```
## 结构体数组的使用


```c


struct student{
    char name[20];
    int age;
    char sex;
    
}stu[3] = {
        
    {"zhangsan",20,'m'},
    {"lisi",22,'w'},
    {"wangwu",21,'m'}
};

printf("stu[0]的姓名：%s\n",stu[0].name);
printf("stu[0]的年龄：%d\n",stu[0].age);
printf("stu[0]的性别：%c\n",stu[0].sex);


printf("stu[1]的姓名：%s\n",stu[1].name);
printf("stu[1]的年龄：%d\n",stu[1].age);
printf("stu[1]的性别：%c\n",stu[1].sex);


printf("stu[2]的姓名：%s\n",stu[2].name);
printf("stu[2]的年龄：%d\n",stu[2].age);
printf("stu[2]的性别：%c\n",stu[2].sex);
```

## 结构体指针的定义


```c
struct student{
    char name[20];
    int age;
    char sex;
};


struct student *p;
```
## 结构体指针的使用


```c
struct student{
    char name[20];
    int age;
    char sex;
};


struct student stu1 = {"zhangsan",20,'m'};
struct student stu2 = {"lisi",22,'w'};


p = &stu1;
printf("stu1的姓名：%s\n",p->name);
printf("stu1的年龄：%d\n",p->age);
printf("stu1的性别：%c\n",p->sex);

p = &stu2;
printf("stu2的姓名：%s\n",p->name);
printf("stu2的年龄：%d\n",p->age);
printf("stu2的性别：%c\n",p->sex);
```

## 结构体嵌套的定义


```c
struct student{
    char name[20];
    int age;
    char sex;
    struct class{
        char name[20];
        int grade;
    }cls;
};
```
## 结构体和typedef结合的使用

```c
typedef struct student{
    char name[20];
    int age;
    char sex;
    
} STU;
STU stu1 = {"zhangsan",20,'m'};
STU stu2 = {"lisi",22,'w'};

printf("stu1的姓名：%s\n",stu1.name);
printf("stu1的年龄：%d\n",stu1.age);
printf("stu1的性别：%c\n",stu1.sex);



printf("stu2的姓名：%s\n",stu2.name);
printf("stu2的年龄：%d\n",stu2.age);
printf("stu2的性别：%c\n",stu2.sex);

```

## 结构体内部指针的用法

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int a;
    int *p; 
}aa_t;

int main(int argc, const char *argv[])
{
    aa_t *w; 

    w =(aa_t *)malloc(sizeof(aa_t)); //malloc申请了12字节内存
    if(w == NULL){
        printf("malloc error\n");     
        return -1; 
    }   

    w->a = 10; //对a赋值是成立的
    //*w->p = 20;//这样的赋值会出现段错误，w->p指针没有指向的内存
    w->p = malloc(4); //给p指针申请内存，否则它没有指向的内存
    *w->p = 20; 

    printf("a = %d,*p = %d\n",w->a,*w->p);

    return 0;
}
```

## 结构体内部结构体的用法

```c
#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int a;
    int *p; 
}aa_t;
typedef struct {
    int b;
    aa_t c[2]; 
    aa_t *q; 
}bb_t;

int main(int argc, const char *argv[])
{
    bb_t *w; 

    w = (bb_t *)malloc(sizeof(bb_t));
    
    w->b = 10; 

    w->c.a = 20; 
    w->c.p =(int *)malloc(4);
    *w->c.p = 30; 
    
    w->q = (aa_t *)malloc(sizeof(aa_t));
    w->q->a = 40; 
    w->q->p = (int *)malloc(4);
    *w->q->p = 50; 

    printf("%d,%d,%d,%d,%d\n",w->b,w->c.a,*w->c.p,w->q->a,*w->q->p);     
    return 0;
}
```

# 结构体的内存对齐



