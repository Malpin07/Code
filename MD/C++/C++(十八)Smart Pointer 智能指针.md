# Smart Pointer 智能指针

C++作为语言层面也提供了，相应的解决方案，即智能指针，auto_ptr。虽然
auto_ptr 己经 deserted 了(引自 Google C++ 编程规范)，它的后继者，诸如
share_ptr, weak_ptr 灵感均取自于此。

# RAII Theory
RAII(Resource Acquisition Is Initialization),也称为"资源获取即初始
化"，是 C++语言的一种管理资源、避免泄漏的惯用法。

C++标准保证任何情况下，已构造的对象最终会销毁，即它的析构函数最终会被调
用。
简单的说，RAII 的做法是使用一个对象，在其构造时获取资源，在对象生命期控
制对资源的访问使之始终保持有效，最后在对象析构的时候释放资源。

即 new 获取资源，constructor 构造资源 初始化。

# auto_ptr
```c++
#include <iostream>
#include <memory>
using namespace std;
class A
{
public:
    A(){
        cout<<"A()"<<endl;
    }
    ~A(){
        cout<<"~A()"<<endl;
    }
    void func(){
        cout<<"hahaha"<<endl;
    }
};

void foo()
{
//    A *p = new A;//需要手动释放
//    delete p;

    auto_ptr<A> p(new A); //智能指针，离开作用域自动释放内存
    p->func();
    (*p).func(); //等价于上一行
}

int main()
{
    foo();
    return 0;
}
```

## 实现auto_ptr类似功能
主要利用重载 * 和 -> 运算符，实现对资源的访问。
>类名& operator*()   (?? operator. ??)
>类名* operator->()
```c++

#include <iostream>
#include <memory>
using namespace std;
class A
{
public:
    A(){
        cout<<"A()"<<endl;
    }
    ~A(){
        cout<<"~A()"<<endl;
    }
    void func(){
        cout<<"hahaha"<<endl;
    }
};

class SmartPtr{
public:
    SmartPtr(A * pa){
        _pa= pa;
    }
    ~SmartPtr(){
        delete _pa;
    }
    A& operator*(){
        return *_pa;
    }
    A* operator->(){
        return _pa;
    }


    A& get_pa(){
       return *_pa;
    }
    A* get_pa_ptr(){
        return _pa;
    }



private:
    A * _pa;
};

void foo()
{
    SmartPtr sp(new A);


    sp.get_pa().func();
    sp->func();//等价于上一行 重载了*
    sp.get_pa_ptr()->func();
    sp->func(); //等价于上一行 重载了->

}

int main()
{
    foo();
    return 0;
}
```