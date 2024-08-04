
<!-- TOC -->
* [this指针](#this指针)
  * [this 特性](#this-特性)
  * [this作用](#this作用)
<!-- TOC -->
# this指针
系统在创建对象时，默认生成的指向当前对象的指针。这样作的目的，就是为了带
来使用上的方便。

## this 特性

1. 指向当前对象，可用于用所有的成员函数，但不能应用于初始化列表。
2. this 是以隐含参数的形式传入，而非成员的一部分，所以不会影响 sizeof（obj）的大小。
3. this指针的类型是ClassName* const，即指向常量的指针，不能改变指向的对象，但可以改变对象的内容。

```c++
#include <iostream>
using namespace std;
class Stu
{
public:
    Stu()
    {
    cout<<this<<endl;
    }
};
int main()
{
    Stu s;
    cout<<&s<<endl;
    Stu s2;
    cout<<&s2<<endl;
    return 0;
}

输出:
    
    0x62fe1f
    0x62fe1f
    0x62fe1e
    0x62fe1e
```

## this作用
1. 指向当前对象，避免入参与成员名相同
2. 支持基于返回 this 引用的多重串联调用的函数（连续赋值）。
```c++
#include <iostream>
using namespace std;
class Stu
{
public:
    Stu(string name, int age)
    {
        //name = name;
        //age = age;
        this->name = name;
        this->age = age;
    }
    //**
    Stu & growUp(){
        this->age++;
        return *this;  // return this; ??
    }

    void display()
    {
        cout<<name<<" : "<<age<<endl;
    }

private:
    string name;
    int age;
};
int main()
{
    Stu s("zhangsan",18);
    s.display();
    s.growUp().growUp().growUp().growUp().growUp();
    s.display();
    return 0;
}

输出:
    zhangsan : 18
    zhangsan : 23
```