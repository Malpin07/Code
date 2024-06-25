#include <stdio.h>
#pragma pack()
/*
#pragma pack()
typedef struct _func{
    int aa;
    int (*add)(int,int);
    int (*sub)(int,int);
    int (*mul)(int,int);
}func;
int add(int a,int b){
    return a+b;
}
int sub(int a,int b){
    return a-b;
}
int mul(int a,int b){
    return a*b;
}
*/
struct FF{
    long a; //4   a a a a
    char b; //1   b b b b
    int c;  //4   c c c c
    short d;//2   d
    // d d
}FF;
/*struct AA{
    short a; //a占2字节
    char b;  //b占1字节，空1字节
};
struct BB{ //12
    struct AA a; //a结构体共占用4字节，它采用2字节对齐
    char b;      //a和b最大字节数是2字节对齐，b占1字节空1字节。
    int c;      //a，b和c采用4字节对齐，a+b一共占用6字节，需要补2字节，所以a和b共占用8字节
}BB;

typedef struct {
    char a:2;   // 2位
    short b:5;  // 5位
    int c:2;    // 2位
} bit;
//二进制显示
void bin32bdis(int data)
{
    int i=32;
    while(i--)     //32---1
    {
        if(data & (1<<i))   //31--0
            printf("1");
        else
            printf("0");
        if(i%4==0)
        {
            if(i%8==0)
                printf(" ");
            else
                printf("-");
        }
    }
    putchar(10);
}*/
int main(){
/* bit b={0};
    b.a=0b01;
    b.b=0b10011;
    b.c=0b10;

    printf("%d",b.b);
    func f={f.aa=10,
            f.add=add,
            f.sub=sub,
            f.mul=mul
            };*/
/*//    printf("%s  ,%s  ,%d  , %d\n",__FILE_NAME__,__func__ ,__LINE__,f.add(2,3));
//    printf("%s  ,%s  ,%d  , %d\n",__FILE_NAME__,__func__ ,__LINE__,f.sub(2,3));
//    printf("%s  ,%s  ,%d  , %d\n",__FILE_NAME__,__func__ ,__LINE__,f.mul(2,3));
//    printf("%s\n",__DATE__);*/
    printf("%d", sizeof(long));
    return 0;
}





















#include <stdio.h>
#include <string.h>
//struct name{  //8  外4 内1
//    int a; //4
//    char b; //5
//    char c; //8
//    int d; //12
//}name={
//        .b=10,
//        .d=1
//};
//
//struct name1{  //8  外8 内1
//    int a;
//    char q;
//    int d;
//    double e;
//}name1;
//
//struct stu{
//    char name[20];
//    int age;
//    char sex;
//};
//int main(){
//    struct stu s1;
//    printf("输入名字:");
//    scanf("%s",s1.name);
//    printf("输入年龄:");
//    scanf("%d",&s1.age);
//    getchar();
//    printf("输入性别:");
//    scanf("%c",&s1.sex);
//    strcpy(s1.name,"sssss");
//    printf("姓名:%s,年龄:%d,性别:%c",s1.name,s1.age,s1.sex);
//
//
//    return 0;
//}

/*
typedef struct _STUDENT{
    char name[20];
    int age;
    int score;
}student;

student stu[4];

int  len=sizeof(stu)/ sizeof(student);
void init(){
    for(int i=0;i< len;i++){
        printf("输入第%d个学生信息:",i+1);
        scanf("%s %d %d",stu[i].name,&stu[i].age,&stu[i].score);
    }
}






int main(){
    init();
    for(int i=0;i< sizeof(stu)/ sizeof(student);i++) {
        printf("name = %-5s,age = %d,score = %d\n", stu[i].name, stu[i].age, stu[i].score);
    }
    printf("*****\n");

    student temp;
    for(int i=0;i< len-1;i++){
        for(int j=0;j<len-i-1;j++){
            if (stu[j].score > stu[j+1].score){
                temp=stu[j];
                stu[j]=stu[j+1];
                stu[j+1]=temp;
            }
        }
    }

    for(int i=0;i< sizeof(stu)/ sizeof(student);i++) {
        printf("name = %-5s,age = %d,score = %d\n", stu[i].name, stu[i].age, stu[i].score);
    }
    return 0;
}*/
