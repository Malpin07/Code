
<!-- TOC -->
* [RTTI 运行时类型信息](#rtti-运行时类型信息)
  * [引例](#引例)
* [typeid](#typeid)
  * [基础类型应用](#基础类型应用)
  * [多态体系应用](#多态体系应用)
    * [引例:typeid 指针和引用](#引例typeid-指针和引用)
  * [注意事项](#注意事项)
* [dynamic_cast 向下转型](#dynamic_cast-向下转型)
  * [引例:](#引例-1)
  * [交叉转换](#交叉转换)
  * [注意事项](#注意事项-1)
<!-- TOC -->
# RTTI 运行时类型信息

RTTI(run time type identificaiton)，允许程序员在运行时进行对象信息识
别。typeid /dynamic_cast 是 C++ 运行时类型信息重要组成部分。

运行时信息，来自于多态，所以以下运算符只用于基于多态的继承体系中。

RTTI（Run-Time Type Information/Run-Time Type Identification，运行时类型信息/运行时类型识别）
是一种编程语言特性，允许程序在运行时获取对象的类型信息。
这种特性在C++中尤为常见，尽管其他语言如Java和C#也提供了类似的功能。

```c++
在C++中，RTTI主要通过两个运算符来实现：

typeid运算符：用于获取一个表达式的类型信息。返回一个std::type_info对象，该对象包含类型的相关信息。

dynamic_cast运算符：用于在类层次结构中进行安全的向下转换（即从基类指针或引用转换为派生类指针或引用）。
```
## 引例

下面是一个简单的例子，展示了如何使用typeid和dynamic_cast。
```c++
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {} // 虚析构函数，确保RTTI正常工作
};

class Derived : public Base {
public:
    void derivedFunction() {
        std::cout << "Derived function called" << std::endl;
    }
};

int main() {
    Base* basePtr = new Derived();

    // 使用typeid获取类型信息
    if (typeid(*basePtr) == typeid(Derived)) {
        std::cout << "basePtr points to a Derived object" << std::endl;
    }

    // 使用dynamic_cast进行安全的向下转换
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    if (derivedPtr) {
        derivedPtr->derivedFunction();
    }

    delete basePtr;
    return 0;
}

在这个示例中，typeid用于检查basePtr指向的对象是否是Derived类型，
而dynamic_cast用于将basePtr安全地转换为Derived*类型，
以便调用Derived类中的成员函数。

需要注意的是，
RTTI在某些情况下可能会带来性能开销，
因此在性能敏感的应用中，开发者可能会选择禁用RTTI。
```

# typeid
```c++
运算符 typeid 返回包含操作数数据类型信息的 type_info 对象的一个引用，信
息中包括数据类型的名称，要使用 typeid,程序中需要包含头文件<typeinfo>。

其中 type_info 重载了操作符 ==，!= 分别用来比较是否相等、不等，函数 name()
返回类型名称。

type_info 的拷贝和赋值均是私有的，故不可拷贝和赋值。

常用于返回检查，调试之用。
```

## 基础类型应用

```c++
//TODO: RTTI 运行时类型信息

#include <iostream>
#include <typeinfo>
using namespace std;
int main()
{
//基本类型
    cout<<typeid(char).name()<<endl;
    cout<<typeid(short).name()<<endl;
    cout<<typeid(int).name()<<endl;
    cout<<typeid(long long).name()<<endl;
    cout<<typeid(float).name()<<endl;
    cout<<typeid(double).name()<<endl;
//函数类型
    void (*pf)(int);
    cout<<typeid(pf).name()<<endl;
    //指针类型
    cout<<typeid(int*).name()<<endl;
    cout<<typeid(const int*).name()<<endl;
    cout<<typeid(int* const).name()<<endl;
    return 0;
}
```
输出:

```c++
c
s
i
x
f
d
PFviE
Pi
PKi
Pi

```

## 多态体系应用
引用和解引用的指针，在多态体系中，均可以通过 typeid 获得真实有效的信息。

注意在多态体系中，要想应用 typeid，必须虚析构。

### 引例:typeid 指针和引用
```c++


#include <iostream>
#include <typeinfo>
using namespace std;
class A
{
public:
    virtual ~A(){} // 若无此虚函数， 则称运行时信息不成立
};
class B:public A{
};
class C:public A{
};
void func(A *pa)
{
    cout<<typeid(pa).name()<<endl;
    cout<<typeid(*pa).name()<<endl;
}
void func(A &ra)
{
    cout<<typeid(ra).name()<<endl;
}
int main(int argc, char *argv[])
{
    B b;
    C c;
    A *p1 = &b;
    A *p2 = &c;
    A *p3 = &b;

    cout<<typeid(b).name()<<endl; //1B
    cout<<typeid(p1).name()<<endl; //P1A
    cout<<typeid(*p1).name()<<endl; //1B

    if(typeid(*p1) != typeid(*p2)){
        cout<<"p1和p2的类型不同"<<endl;
    }//p1和p2的类型不同


    A & r1 = b;
    A & r2 = c;
    A & r3 = b;


    cout<<typeid(r1).name()<<endl; //1B
    cout<<typeid(r2).name()<<endl; //1C
    cout<<typeid(r3).name()<<endl; //1B

    if(typeid(r1) != typeid(r2)){
        cout<<"p1和p2的类型不同"<<endl;
    }//p1和p2的类型不同

    return 0;
}
```
## 注意事项
```c++
确保基类定义了至少一个虚函数(虚析构也算)。

不要将 typeid 作用于指针，应该作用于引用，或解引用的指针。

typeid 是一个运算符，而不是函数。

typeid 运算符返回的 type_info 类型，其拷贝构造函数和赋值运算函数都声明为
private 了，这意味着其不能用于 stl 容器，所以我们一般不能不直接保存 type_info
信息，而保存 type_info 的 name 信息


指针类型：
当 typeid 作用于指针时，它返回的是指针类型本身。例如，如果 a 和 b 都是 Base* 类型的指针，那么 typeid(a) 和 typeid(b) 返回的都是 Base* 类型。

对象类型：
当 typeid 作用于指针所指向的对象时，它返回的是对象的动态类型。动态类型是指对象在运行时的实际类型，而不是静态类型。例如，如果 a 是一个指向 Base 类的指针，但实际指向的是一个 Derived 类的对象（Derived 是 Base 的派生类），那么 typeid(*a) 返回的是 Derived 类型。

空指针异常：
如果 typeid 作用于一个解引用的指针（即 *ptr），而这个指针的值为空（即 nullptr），那么 typeid 会抛出 bad_typeid 异常。这是因为解引用一个空指针是非法操作，typeid 在这种情况下无法确定对象的类型。

总结来说，typeid 运算符在处理指针和对象时表现出不同的行为：
对于指针，返回指针类型本身。
对于指针所指向的对象，返回对象的动态类型。
如果指针为空，解引用时会抛出 bad_typeid 异常。
```

# dynamic_cast 向下转型
```c++
应用于类的指针、类的引用或者 void*。
dynamic_cast 运算符可以在执行期决定真正的类型。
如果 downcast 是安全的（也就说，如果基类指针或者引用确实
指向一个派生类对象）这个运算符会传回适当转型过的指针。
如果 downcast 不安全，这个运算符会传回空指针（也就是说，
基类指针或者引用没有指向一个派生类对象）。
dynamic_cast 主要用于类层次间的上行转换和下行转换，还可
以用于类之间的交叉转换。
```

## 引例:
```c++     
#include <iostream>
#include <typeinfo>

using namespace std;

// 定义类A，它有一个虚析构函数
class A
{
public:
    virtual ~A(){}  // 虚析构函数，用于支持多态
};

// 定义类B，继承自A
class B : public A {};

// 定义类C，继承自A
class C : public A {};

// 定义类D，不继承自A
class D {};

int main(int argc, char *argv[])
{
    // 创建一个B类的对象b
    B b;
    
    // 将b的地址赋值给指向A类的指针pa
    A *pa = &b;
    
    // 尝试将pa向下转型为B类的指针
    B* pb = dynamic_cast<B*>(pa);
    if(pb != NULL)
        cout << "pb != NULL" << endl;  // 如果转型成功，输出pb != NULL
    else
        cout << "pb == NULL" << endl;  // 如果转型失败，输出pb == NULL
    
    // 尝试将pa向下转型为C类的指针
    C *pc = dynamic_cast<C*>(pa);
    if(pc != NULL)
        cout << "pc != NULL" << endl;  // 如果转型成功，输出pc != NULL
    else
        cout << "pc == NULL" << endl;  // 如果转型失败，输出pc == NULL
    
    // 尝试将pa向下转型为D类的指针
    D *pd = dynamic_cast<D*>(pa);
    if(pd != NULL)
        cout << "pd != NULL" << endl;  // 如果转型成功，输出pd != NULL
    else
        cout << "pd == NULL" << endl;  // 如果转型失败，输出pd == NULL
    
    return 0;
}
```

```c++
输出:

pb != NULL
pc == NULL
pd == NULL
```

## 交叉转换

通过交叉转换，可以在多重继承的类层次结构中灵活地在不同基类之间进行转换，从而实现更复杂的设计和功能。

```c++

#include <iostream>
#include <typeinfo>

class Base1 {
public:
    virtual ~Base1() {}
};

class Base2 {
public:
    virtual ~Base2() {}
};

class Derived : public Base1, public Base2 {
};

int main() {
    Derived* derivedPtr = new Derived();

    // 从 Derived* 转换为 Base1*（上行转换）
    Base1* base1Ptr = dynamic_cast<Base1*>(derivedPtr);
    if (base1Ptr) {
        std::cout << "转换为 Base1* 成功" << std::endl;
    } else {
        std::cout << "转换为 Base1* 失败" << std::endl;
    }

    // 从 Derived* 转换为 Base2*（上行转换）
    Base2* base2Ptr = dynamic_cast<Base2*>(derivedPtr);
    if (base2Ptr) {
        std::cout << "转换为 Base2* 成功" << std::endl;
    } else {
        std::cout << "转换为 Base2* 失败" << std::endl;
    }

    // 从 Base1* 转换为 Base2*（交叉转换）
    Base2* crossCastPtr = dynamic_cast<Base2*>(base1Ptr);
    if (crossCastPtr) {
        std::cout << "交叉转换为 Base2* 成功" << std::endl;
    } else {
        std::cout << "交叉转换为 Base2* 失败" << std::endl;
    }

    delete derivedPtr;
    return 0;
}


```
```c++
输出:
转换为 Base1* 成功
转换为 Base2* 成功
交叉转换为 Base2* 成功
```


## 注意事项
```c++
虚函数：交叉转换依赖于虚函数，因为 dynamic_cast 需要运行时类型信息（RTTI）来确定对象的实际类型。
多重继承：交叉转换通常发生在多重继承的情况下，即一个类同时继承自多个基类。
安全性：dynamic_cast 在运行时进行类型检查，确保转换的安全性。
如果转换不合法，
对于指针类型，dynamic_cast 会返回 nullptr；
对于引用类型，会抛出 std::bad_cast 异常。
```