<!-- TOC -->
* [C++(二十五)依赖倒置](#c二十五依赖倒置)
* [案例](#案例)
<!-- TOC -->

# C++(二十五)依赖倒置

依赖倒置原则（Dependency Inversion Principle，简称DIP）是面向对象设计中的一个重要原则，
它由Robert C. Martin（也称为Uncle Bob）提出。
DIP的核心思想是高层模块不应该依赖于低层模块，
二者都应该依赖于抽象；
抽象不应该依赖于细节，细节应该依赖于抽象。

```c++
在C++中，依赖倒置原则可以通过以下几个方面来实现：

抽象接口：定义抽象接口（通常是纯虚类），高层模块和低层模块都依赖于这个抽象接口。

依赖注入：通过构造函数、方法参数或设置器方法将依赖关系注入到类中，而不是在类内部直接创建依赖对象。

控制反转：通过使用框架或容器来管理对象的创建和依赖关系，实现控制反转。
```

# 案例
```c++
#include <iostream>
using namespace std;

// 定义一个接口类 IReader，所有阅读器类都需要实现这个接口
class IReader
{
public:
    // 纯虚函数，表示所有继承自 IReader 的类都必须实现这个函数
    virtual string getContents() = 0;
    // 析构函数，释放内存
    // 虚析构函数，确保派生类对象在删除时能够正确调用析构函数
    virtual ~IReader() = default;
    //= default：这是C++11引入的特性，表示使用编译器生成的默认析构函数实现。
    // 编译器会自动生成一个析构函数，该析构函数会依次调用类成员和基类的析构函数。
};

// Book 类继承自 IReader，实现 getContents 方法
class Book : public IReader
{
public:
    // 实现 getContents 方法，返回书的内容
    string getContents()
    {
        return "从前有座山，山里有座庙，庙里有个小和尚，要听故事";
    }
    // 析构函数，释放内存
    ~Book() override {
        cout << "Book destructor called" << endl;
    };
};

// NewsPaper 类继承自 IReader，实现 getContents 方法
class NewsPaper : public IReader
{
public:
    // 实现 getContents 方法，返回报纸的内容
    string getContents()
    {
        return "Trump，赢得的下一届美国总统大选";
    }
    // 析构函数，释放内存
    ~NewsPaper() override{
        cout << "NewsPaper destructor called" << endl;
    };
};

// Mother 类，有一个方法 tellStory，接受一个 IReader 指针作为参数
class Mother
{
public:
    // tellStory 方法，通过 IReader 指针调用 getContents 方法，输出内容
    void tellStory(IReader *i)
    {
        cout << i->getContents() << endl;
    }
    // 析构函数，释放内存
    ~Mother(){
        cout << "Mother destructor called" << endl;
    };
};

// 主函数
int main()
{
    // 创建 Mother 对象
    Mother m;//m是栈对象，自动释放内存
    // 创建 Book 对象，并分配内存
    Book *b = new Book;
    // 创建 NewsPaper 对象，并分配内存
    NewsPaper *n = new NewsPaper;

    // 输出提示信息
    cout << "Mother start to tell story" << endl;
    // 调用 tellStory 方法，传入 Book 对象
    m.tellStory(b);

    // 输出提示信息
    cout << "Mother start to tell news" << endl;
    // 调用 tellStory 方法，传入 NewsPaper 对象
    m.tellStory(n);

    // 释放 Book 对象的内存
    delete b;
    // 释放 NewsPaper 对象的内存
    delete n;


    // 返回 0，表示程序正常结束
    return 0;
}

```