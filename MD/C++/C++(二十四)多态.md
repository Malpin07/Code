<!-- TOC -->
* [C++(二十四)多态](#c二十四多态)
  * [赋值兼容是多态的必要条件](#赋值兼容是多态的必要条件)
    * [引例:](#引例)
  * [安全转化](#安全转化)
* [静多态](#静多态)
* [多态](#多态)
  * [引例:](#引例-1)
  * [补充](#补充)
    * [override 关键字](#override-关键字)
    * [虚函数在子类中的,访问属性并不影响多态](#虚函数在子类中的访问属性并不影响多态)
* [纯虚函数](#纯虚函数)
* [虚函数类的析构函数](#虚函数类的析构函数)
* [案例:](#案例)
<!-- TOC -->

# C++(二十四)多态
C++中所谓的多态(polymorphism)是指，由继承而产生的相关的不同的类，其对
象对同一消息会作出不同的响应。

比如，Mspaint 中的单击不同图形，执行同一个拖动动作而绘制不同的图形，就
是典型的多态应用。

多态性是面向对象程序设计的一个重要特征，能增加程序的灵活性。可以减轻系统
升级,维护,调试的工作量和复杂度.

## 赋值兼容是多态的必要条件

赋值兼容规则是指，在需要基类对象的任何地方，都可以使用公有派生类的对象来替代。

只有在公有派生类中才有赋值兼容，赋值兼容是一种默认行为，不需要任何的显示
的转化步骤

```c++
赋值兼容细化
1 派生类的对象可以赋值给基类对象。
2 派生类的对象可以初始化基类的引用。
3 派生类对象的地址可以赋给指向基类的指针。
```
### 引例:
```c++
#if 1
//todo 赋值兼容

#include <iostream>
#include <typeinfo>
using namespace std;


class Shape {
protected:
    int x_,y_;

public:
    Shape(int x=0, int y=0) : x_(x), y_(y) {
        cout<<"Shape :"<<this<<endl;
        cout<< typeid(this).name() << endl;
    }

    void draw() {
        cout << "Shape draw: " <<"("<<x_<<","<<y_<<")"<< endl;
    }
};

class Circle: public Shape {
protected:
    int  radius_;


public:
    Circle(int x=0, int y=0, int r=0) : Shape(x,y), radius_(r) {
        cout<<"Circle :"<<this<<endl;
        cout<< typeid(this).name() << endl;
    }
    void draw() {
        cout << "Shape draw: " <<"("<<x_<<","<<y_<<")"<< " radius: "<<radius_<< endl;
    }

};


class Rect: public Shape {

};
int main() {
    Shape s(1,2);
    s.draw();
    cout<<"----------"<<endl;
    Circle c(3,4,5);
    s = c; //赋值兼容:1.派生类的对象可以赋值给基类对象。
    s.draw();
    cout<<"----------"<<endl;

    Shape & rs = c; //赋值兼容:2.派生类的对象可以初始化基类的引用。
    rs.draw();
    cout<<"----------"<<endl;

    Shape * ps=&c; //赋值兼容:3.派生类对象的地址可以赋给指向基类的指针。
    ps->draw();
    cout<<"----------"<<endl;

    return 0;


}
# endif
```
```c++
输出:
Shape :0x62fe08
P5Shape
Shape draw: (1,2)
----------
Shape :0x62fdfc
P5Shape
Circle :0x62fdfc
P6Circle
Shape draw: (3,4)
----------
Shape draw: (3,4)
----------
Shape draw: (3,4)
----------
```

## 安全转化

赋值兼容是安全的。

子类对象初始化的时候，调用父类的构造器，也是发生了赋值兼容的问题。
除此之外，其它任何父类成员调用，均是如此。

大范围的指针向小范围的指针转化是安全的。反之，不亦然。

>父类也可以通过强转的方式转化为子类。 父类对象强转为子类对象后，访问从父
类继承下来的部分是可以的，但访问子类的部分，则会发生越界的风险，越界的结果是
未知的。
> 

# 静多态

静多态，也就是我们说的函数重载。表面来看，是由重载规则来限定的，内部实现却是 Namemangling(命名倾轧)。

此种行为，发生在编译期，故称为静多态。

# 多态

(动)多态，不是在编译器阶段决定，而是在运行阶段决定，故称为动多态。动多
态行成的条件如下:

```c++
多态实现的条件(十分重要)
1 父类中有虚函数，即共用接口。
2 子类 override(覆写)父类中的虚函数。
3 通过己被子类对象赋值的父类指针，调用共用接口。
```

## 引例:
```c++

#if 1
//todo 多态
//!1,父类中有虚函数;加virtual关键字 (声明型关键字)
//!2,子类 override 覆写 父类的虚函数 ;覆写:子类中同名,同参,同返回才能构成覆写
//!3,子类对象赋给了父类指针,通过父类的指针调用虚函数,形成多态;
#include <iostream>
#include <typeinfo>
using namespace std;


class Shape {
protected:
    int x_,y_;

public:
    Shape(int x=0, int y=0) : x_(x), y_(y) {
        cout<<"Shape :"<<this<<endl;
        cout<< typeid(this).name() << endl;
    }
    virtual void draw();//*1,父类中有虚函数,加virtual关键字 (声明型关键字)
};
void Shape::draw() {
    cout << "Shape draw: " <<"("<<x_<<","<<y_<<")"<< endl;
}


class Circle: public Shape {
protected:
    int  radius_;


public:
    Circle(int x=0, int y=0, int r=0) : Shape(x,y), radius_(r) {
        cout<<"Circle :"<<this<<endl;
        cout<< typeid(this).name() << endl;
    }

    virtual void draw() {//*2,子类 override 覆写 父类的虚函数 覆写:子类中同名,同参,同返回才能构成覆写
        cout << "Shape draw: " <<"("<<x_<<","<<y_<<")"<< " radius: "<<radius_<< endl;
    }

};


class Rect: public Shape {
protected:
    int width_;
    int height_;
public:
    Rect(int x=0, int y=0, int w=0, int h=0) : Shape(x,y), width_(w), height_(h) {
        cout<<"Rect :"<<this<<endl;
        cout<< typeid(this).name() << endl;
    }
    virtual void draw() {
        cout << "Shape draw: " <<"("<<x_<<","<<y_<<")"<< " width: "<<width_<<" height: "<<height_<< endl;
    }


};





int main() {
    Circle c(3,4,5);
    //Shape * ps=&c; //*3,子类对象赋给了父类指针,通过父类的指针调用虚函数,形成多态;
    //ps->draw();

    cout<<"----------"<<endl;

    Rect r(1,2,3,4);
    //Shape * pr=&r;
    //pr->draw();

    Shape *ps;
    for(;;){
        int  choice;
        cout<<"1.Circle"<<endl;
        cout<<"2.Rect"<<endl;
        cin>>choice;

        switch(choice){
            case 1:
                ps=&c;
                break;
            case 2:
                ps=&r;
                break;
        }
        ps->draw();
    }


    return 0;
}
# endif
```
## 补充
### override 关键字
override 关键字是 C++11 引入的一个关键字，用于显式地表明一个成员函数是重写（覆盖）基类中的虚函数。

使用 override 关键字可以提高代码的可读性和可维护性，并且可以帮助编译器在编译时检查是否正确地重写了基类的虚函数。

>具体来说，override 关键字有以下几个作用：
>
> 1. 显式声明：明确表明该函数是重写基类的虚函数，提高代码的可读性。
> 
> 2. 编译时检查：如果函数签名与基类的虚函数不匹配，编译器会报错，避免因函数签名不匹配导致的运行时错误。

### 虚函数在子类中的,访问属性并不影响多态
> 虚函数在子类中的,访问属性并不影响多态
> 
> 多态是通过虚函数表（vtable）机制实现的，而虚函数表的生成和使用与函数的访问属性无关。

具体来说，无论虚函数在子类中是public、protected还是private，
只要在基类中声明为虚函数，并且在子类中进行了重写（override），
就可以通过基类的指针或引用来调用子类的虚函数，从而实现多态。


# 纯虚函数

```c++
纯虚函数与多态
1 纯虚函数只有声明，没有实现，被"初始化"为 0。
2 含有纯虚函数的类，称为 Abstract Base Class(抽象基类)，不可实例化。即不能创
建对象，存在的意义就是被继承，提供族类的公共接口，java 中称为 Interface。
3 如果一个类中声明了纯虚函数，而在派生类中没有该函数的定义，则该虚函数在
派生类中仍然为纯虚函数，派生类仍然为纯虚基类。依然不能实例化
```

# 虚函数类的析构函数
```c++
含有虚函数的类，析构函数也应该声明为虚函数，称为虚析构函数。
在 delete 父类指针，指向的堆上子类对象时，
会调用子类的析构函数，实现完整析构。
```

在C++中，如果你有一个包含虚函数的类，并且你希望通过父类指针删除一个堆上的子类对象，
那么将析构函数声明为虚函数（即虚析构函数）是非常重要的。
这样做可以确保在删除父类指针时，
能够正确调用子类的析构函数，从而实现完整的析构过程。

```c++
#include <iostream>

class Base {
public:
    virtual ~Base() { // 虚析构函数
        std::cout << "Base destructor called" << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() override { // 子类的析构函数
        std::cout << "Derived destructor called" << std::endl;
    }
};

int main() {
    Base* ptr = new Derived();
    delete ptr; // 通过父类指针删除子类对象
    return 0;
}

```

>Base类有一个虚析构函数。当我们通过Base类型的指针ptr删除一个Derived对象时，由于析构函数是虚函数，所以会先调用Derived类的析构函数，然后再调用Base类的析构函数。输出将会是：
> 
> > Derived destructor called
> >
> > Base destructor called


如果没有将Base类的析构函数声明为虚函数，那么只会调用Base类的析构函数，
而不会调用Derived类的析构函数，这可能会导致资源泄漏或其他未定义行为。



# 案例:
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