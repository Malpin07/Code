<!-- TOC -->
* [C++(七)封装](#c七封装)
  * [权限控制](#权限控制)
* [class](#class)
  * [构造器constructor](#构造器constructor)
  * [initial list 初始化列表](#initial-list-初始化列表)
  * [析构器destructor](#析构器destructor)
* [层次管理](#层次管理)
* [分文件编程](#分文件编程)
<!-- TOC -->
# C++(七)封装
封装，可以达到，对外提供接口，屏蔽数据，对内开放数据。

## 权限控制

struct 中所有行为和属性都是 public 的(默认)，此举也是为了 C++兼容 C 语言，
因为 C 语言中没有权限的概念。

C++中的 class 可以指定行为和属性的访问方式，默认为 private，此举要求你必
须指定权限，不然就没有办法外部访问。

|访问属性 | 属性     | 对象内部 | 对象外部 |
|--------|--------|------|------|
|public  | 公有     | 可访问  | 可访问  |
|private | 私有     | 可访问  | 不可访问  |
|protected|受保护|可访问|不可访问|


初步使用封装:
```c++
#include <iostream>
#include <string.h>
using namespace std;

class Stack{
public:
    void init();
    bool isEmpty();
    bool isFull();
    void push(int data);
    int pop();
private:
    int space[1024];
    int top;
};

void Stack::init()
{
    memset(space,0,sizeof(space));
    top = 0;
}
bool Stack::isEmpty()
{
    return top == 0;
}
bool Stack::isFull()
{
    return top == 1024;
}
void Stack::push(int data)
{
    space[top++] = data;
}
int Stack::pop()
{
    return space[--top];
}


int main(){
    Stack s;
    s.init();
    if(!s.isFull())
        s.push(10);
    if(!s.isFull())
        s.push(20);
    if(!s.isFull())
        s.push(30);
    if(!s.isFull())
        s.push(40);
    while(!s.isEmpty())
        cout<<s.pop()<<endl;
    return 0;
}
```

# class

## 构造器constructor

构造器是类的初始化函数，当对象被创建时，系统自动调用构造器进行初始化。

无返回值 可以有参数

构造器可以有默认参数,可以被重载

系统提供的默认构造器，当没有自定义构造器时，系统会自动生成一个默认构造器。

无论重载还是默认参数,都应该将无参的空体构造器包含进来

生成的无参的对象,是一种比较常见的现象,对象数组;

```c++
#include <iostream>
#include <string.h>
using namespace std;

class Stack{
public:
    Stack(){
        top = 0;
        size = 1024;
        space = new int[1024];
        memset(space, 0, sizeof(int)*1024);
    }

    Stack(int size){
        top = 0;
        this->size = size;
        space = new int[size];
        memset(space, 0, sizeof(int)*size);
    }


    //默认参数会在现在的代码中冲突
//    Stack(int size=1024){
//        top = 0;
//        this->size = size;
//        space = new int[size];
//        memset(space, 0, sizeof(int)*size);
//    }

    bool isEmpty();
    bool isFull();
    void push(int data);
    int pop();
private:
    int *space;
    int top;
    int size;
};


bool Stack::isEmpty()
{
    return top == 0;
}
bool Stack::isFull()
{
    return top == size;
}
void Stack::push(int data)
{
    space[top++] = data;
}
int Stack::pop()
{
    return space[--top];
}


int main(){
    Stack s(2);

    if(!s.isFull())
        s.push(10);
    if(!s.isFull())
        s.push(20);
    if(!s.isFull())
        s.push(30);
    if(!s.isFull())
        s.push(40);
    while(!s.isEmpty())
        cout<<s.pop()<<endl;
    return 0;
}
```

## initial list 初始化列表

C++11 引入了初始化列表，可以用来初始化类成员变量。

*** 注意: 初始化的顺序与成员变量的声明顺序相同。与列表中赋值顺序无关。***
不能使用列表中初始化的成员,去初始化其他成员,做法很容易引发错误


必须用此格式来初始化引用数据。

必须用此格式来初始化非静态 const 数据成员(C++98)。

```c++  
//列表只能初始化类成员变量，不能初始化局部变量
   Stack(int size): top(0), size(size), space(new int[size]){
      
        memset(space, 0, sizeof(int)*size);
    }
    
   Stack(int size): top(0), size(size), space(new int[size]{0}){

    }
```

## 析构器destructor
析构器是类的析构函数，

~开头与类名同的函数，在类对象销毁时(栈/堆对象)，自动调用，

无返回值 不能有参数

析构器不能被重载

系统提供的默认析构器，当没有自定义析构器时，系统会自动生成一个默认析构器。

```c++

#include <iostream>
#include <string.h>
using namespace std;

class Stack{
public:
    Stack(){
        top = 0;
        size = 1024;
        space = new int[1024];
        memset(space, 0, sizeof(int)*1024);
    }
    ~Stack(){
        delete[] space;
    }
    
private:
    int *space;
    int top;
    int size;
};



```

# 层次管理
```c++

#include <iostream>
#include <string.h>
using namespace std;
class Student
{
public:
    Student(int a, char* n )
    {
        cout<<"Constructor called"<<endl;
        _age  = a;
        _name = new char[strlen(n)];
        strcpy(_name,n);
    }
    ~Student()
    {
        cout<<"Destructor called"<<endl;
        delete []_name;
    }

private:
    char *_name;
    int _age;
};
int main()
{
    Student s(10,"hello");
    Student *ps  = new Student(10,"hello");
    delete ps;
    return 0;
}
```

# 分文件编程

myStack.h
```c++
//
// Created by gophe on 24-7-28.
//

#ifndef CDEMO_MYSTACK_H
#define CDEMO_MYSTACK_H


class myStack {
public:
    myStack();
    //myStack(int size);
    myStack(int size=10);//参数默认值只能在这定义,初始化列表在.cpp中定义

    ~myStack();
    bool isEmpty();
    bool isFull();
    void push(int data);
    int pop();
private:
    int *space;
    int top;
    int size;
};


#endif //CDEMO_MYSTACK_H

```


myStack.cpp
```c++
//
// Created by gophe on 24-7-28.
//

#include "Headers/myStack.h"

myStack::myStack(){
    top = 0;
    size = 100;
    space = new int[100];
}
//  上下两种均可
myStack::myStack():size(10),top(0),space(new int[10]){

}

myStack::myStack(int s)
{
    top = 0;
    size = s;
    space = new int[s];
}
//  上下两种均可
//初始化列表在.cpp中定义
myStack::myStack(int s):size(s),top(0),space(new int[s])
{
}

myStack::~myStack()
{
    delete[] space;
}

bool myStack::isEmpty()
{
    return top == 0;
}
bool myStack::isFull()
{
    return top == size;
}
void myStack::push(int data)
{
    space[top++] = data;
}
int myStack::pop()
{
    return space[--top];
}

```

main.cpp
```c++
#include <iostream>
#include "Headers/myStack.h"

using namespace std;


int main(){
    myStack s(2);

    if(!s.isFull())
        s.push(10);
    if(!s.isFull())
        s.push(20);
    if(!s.isFull())
        s.push(30);
    if(!s.isFull())
        s.push(40);
    while(!s.isEmpty())
        cout<<s.pop()<<endl;
    return 0;
}


```
