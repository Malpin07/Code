<!-- TOC -->
* [C++(二)内存管理](#c二内存管理)
  * [new/delete](#newdelete-)
    * [new/new[]用法:](#newnew用法)
* [返回值判断](#返回值判断)
  * [内存申请失败](#内存申请失败)
  * [try/catch 捕获异常](#trycatch-捕获异常)
  * [set_new_handler](#set_new_handler)
  * [不会抛出异常处理方式](#不会抛出异常处理方式)
<!-- TOC -->
# C++(二)内存管理

c 语言中提供了 malloc 和 free 两个系统函数，完成对堆内存的申请和释放。而 c++则
提供了两关键字 new 和 delete ;

## new/delete 

### new/new[]用法:

>int *p = new int; //开辟大小为 sizeof(int)空间
> 
>int *a = new int(5); //开辟大小为 sizeof(int)空间，并初始化为 5
> 

```c++
// todo new/delete

#include <iostream> //<iostream>
using namespace std; //
int main() {

    //单变量
    int *p=new int(20);
    cout<<*p<<endl; //20
    *p=10;
    cout<<*p<<endl; //10

    string *s=new string("hello");
    cout<<*s<<endl; //hello
    *s="world";
    cout<<*s<<endl; //world


    struct Sut{
        int age;
        string name;
    };
    Sut* s1=new Sut;
    s1->age=20;
    s1->name="Tom";
    cout<<s1->age<<endl; //20
    cout<<s1->name<<endl; //Tom


    Sut* s2=new Sut{10,"Jerry"};
    cout<<s2->age<<endl; //10
    cout<<s2->name<<endl; //Jerry
    
    delete s2;
    delete s1;
    delete p;
    delete s;
    return 0;
}
```

多变量空间:
```c++

int main() {
     //多变量
     //一维数组
     char* p= new char[40]; //分配40个字节的内存
     memset(p,0,40); //将内存块全部初始化为0
     strcpy(p,"hello world");
     cout<<p<<endl;//hello world

     int *pi=new int[5]{0};//分配5个int类型的内存，并初始化为0
     pi[0]=10;
     for(int i=0;i<5;i++){
         cout<<pi[i]<<" "; //10 0 0 0 0
     }

    char **ppc=new char *[5]{NULL};
    ppc[0]="qqq";
    ppc[1]="www";
    ppc[2]="eee";

    ppc[3]=new char[10];
    strcpy(ppc[3],"xxxxx");
    cout<<endl;

    while(*ppc) {
        cout<<*ppc++<<" "; //qqq www eee xxxxx
    }
    cout<<endl;

    //多维数组
    int (*q)[3] = new int[2][3];
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            q[i][j] = i+j;
        }
    }
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            cout<<q[i][j]<<" ";
        }
        cout<<endl;
    }

    int (*qq)[3][4] = new int [2][3][4];
    
    
    delete[] qq; //释放内存
    delete[] q; //释放内存
    delete[] ppc[3]; //释放内存
    delete[] ppc; //释放内存
    delete[] pi; //释放内存
    delete[] p; //释放内存
}
```

> new/delete 是关键字，效率高于 malloc 和 free.
> 
> 配对使用，避免内存泄漏和多重释放。
> 
> 避免，交叉使用。比如 malloc 申请的空间去 delete，new 出的空间被 free;
> 
> new/delete 关键字，重点用在类对像的申请与释放。申请的时候会调用构造器完成初始化，释
放的时候，会调用析构器完成内存的清理。
> 


# 返回值判断
## 内存申请失败
```c++
int main()
{
    double * pd[50];
    for(int i=0; i<50; i++)
    {
        pd[i] = new double[50000000];
        cout<<i<<endl;
    }
return 0;
}
```
直接抛出异常,结束程序:
```c++
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc

```
## try/catch 捕获异常
```c++

int main()
{
    double * pd[50];

    try {
        for(int i=0; i<50; i++)
        {
            pd[i] = new double[50000000];

            cout<<i<<endl;
        }
    }catch (std::bad_alloc & e){
        cout<<"内存分配失败: "<<e.what()<<endl;
    }

    cout<<"程序结束"<<endl;



    return 0;
}
```
```c++
内存分配失败: std::bad_alloc
程序结束
```
## set_new_handler
```c++

void newErr()
{
    cout<<"new error"<<endl;
    exit(-1);
}

int main()
{
    double * pd[50];
    //set_new_handler 是用来设置一个新的内存分配函数的，当内存分配失败时，会调用这个函数。
    set_new_handler(newErr);

    for(int i=0; i<50; i++)
    {
        pd[i] = new double[50000000];

        cout<<i<<endl;
    }

    cout<<"程序结束"<<endl;



    return 0;
}

输出:
new error
```

## 不会抛出异常处理方式
```c++
int main()
{
    double * pd[50];
    //set_new_handler 是用来设置一个新的内存分配函数的，当内存分配失败时，会调用这个函数。
    //set_new_handler(newErr);

    for(int i=0; i<50; i++)
    {
        //(nothrow)设置异常处理，如果内存分配失败，不会抛出异常，而是返回nullptr
        pd[i] = new (nothrow)double[50000000];
        if(pd[i] == nullptr){
            cout<<"分配内存失败:"<<__FILE__<<" "<<__func__ <<" "<<__LINE__<<endl;
            exit(-1);
        }

    }
    cout<<"程序结束"<<endl;
    return 0;
}
```

