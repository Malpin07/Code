<!-- TOC -->
* [friend](#friend)
  * [友元不是成员](#友元不是成员)
  * [全局函数作友元](#全局函数作友元)
  * [成员函数作友元](#成员函数作友元)
  * [前向声明](#前向声明)
* [友元类](#友元类)
  * [友元类示例:](#友元类示例)
* [总结](#总结)
  * [声明位置](#声明位置)
  * [友元利弊](#友元利弊)
  * [注意事项](#注意事项)
<!-- TOC -->
# friend

采用类的机制后实现了数据的隐藏与封装，类的数据成员一般定义为私有成员，成
员函数一般定义为公有的，依此提供类与外界间的通信接口。

但是，有时需要定义一些函数，这些函数不是类的一部分，但又需要频繁地访问类
的数据成员，这时可以将这些函数定义为该类的友元函数。除了友元函数外，还有友元
类，两者统称为友元。

友元的作用是提高了程序的运行效率(即减少了类型和安全性检查及调用的时间
开销)，但它破坏了类的封装性和隐藏性，使得非成员函数可以访问类的私有成员。

友元可以是一个函数，该函数被称为友元函数；友元也可以是一个类，该类被称为
友元类。

```c++
#include <iostream>
using namespace std;

class Complex{
    friend Complex operator+(Complex &c1, Complex &c2); //声明友元函数
    public:
    Complex(double r=0, double i=0):real(r),image(i){}
    void display(){
        cout<<"("<<real<<","<<image<<")"<<endl;
    }
private:

    double real;
    double image;
};



Complex operator+(Complex &c1, Complex &c2){
    Complex c;
    c.real = c1.real + c2.real; //访问私有的成员变量,不被允许 //声明友元函数后可以访问私有成员变量
    c.image = c1.image + c2.image; //访问私有的成员变量,不被允许

    return c;
}

int main()
{

    Complex c1(2,3), c2(4,5);
    Complex c3(0,0);
    c3 = c1 + c2;
    c3.display();
    return 0;
}
```

## 友元不是成员
友元函数终究不是成员函数，成员中有隐参 this 指针，可以直接访问成员，而友
元中则没有，必须得通过对象来访问。

友元仅是打破了，外部访问中的 private 权限。

> 声明为谁的友元，就可以通过谁的对象，访问谁的私有成员
> 
> 


## 全局函数作友元
```c++



#include <iostream>
#include <cmath>

using namespace std;

class Point{
    //声明友元函数
    friend float distance(const Point &p1,const Point &p2);
private:
    float _x, _y;
public:
    Point(float x=0, float y=0):_x(x),_y(y){};
    void display(){
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }

};

//距离计算函数
float distance(const Point &p1,const Point &p2){
    float dx = p1._x - p2._x;
    float dy = p1._y - p2._y;
    //计算两点之间的距离
    return sqrt(dx*dx + dy*dy);

}

int main(){

    Point p1(3,4);
    p1.display();
    Point p2(7,8);
    p2.display();
    float d = distance(p1,p2);
    cout<<"距离 p1 --- p2  "<<d<<endl;
    return 0;

}
```

```c++
输出: 
(3,4)
(7,8)
距离 p1 --- p2  5.65685
```

## 成员函数作友元


```c++


#include <iostream>
#include <cmath>
using namespace std;


//!前向声明 是一种不完全类型的声明,不能定义对象,
//! 但可以定义指针和引用,因为指针和引用都是4字节,都是确定的大小
//!作为参数和返回值,仅用在函数声明中

class Point; //前向声明

//成员函数作友元
class ManagerPoint {
public:
    //距离计算函数
    //由于用到的Point,还没定义,结合前向声明的特点,
    //在此处只能声明函数,,这个函数的实现只能放在Point函数实现之后了
    float distance(const Point &p1, const Point &p2);
};

class Point{
    //声明友元函数
    friend float ManagerPoint::distance(const Point &p1,const Point &p2);
private:
    float _x, _y;
public:
    Point(float x=0, float y=0):_x(x),_y(y){};
    void display(){
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }

};


//距离计算函数
float ManagerPoint::distance(const Point &p1, const Point &p2) {
    float dx = p1._x - p2._x;
    float dy = p1._y - p2._y;
    //计算两点之间的距离
    return sqrt(dx * dx + dy * dy);

}




int main(){

    Point p1(3,4);
    p1.display();
    Point p2(7,8);
    p2.display();

    
    ManagerPoint mp;
    float d = mp.distance(p1,p2);
    cout<<"距离 p1 --- p2  "<<d<<endl;
    return 0;

}
```

## 前向声明

前向声明，是一种不完全型(incomplete type)声明，即只需提供类名(无需提供
类实现)即可。正因为是类型不，功能也很有限:

```c++
1 不能定义对象。
2 可以用于定义指向这个类型的指针或引用。因为指针和引用都是4字节,都是确定的大小
3 用于声明(不是定义)，作为形参类型或者函数的返回值类型。
```

> 指针和引用的大小均是 4，对于编译器来说是可以确定的，但是对于一个不完类型
编译器是无法确定其大小的。

>所以上例中的 distance(Point &a, Point &b)中的引用改为 distance(Point
a, Point b)是不可行的。
> 
> 若改为指针类型，distance(Point *a, Point *b)则是可行的。

前向声明常见于头文件中，而在其头文件所在的 cpp 文件中被包含。


# 友元类

当希望一个类中所有成员函数，均可存取另一个类的私有成员时，可以将该类声明
为另一类的友元类。

友元类，导致封装破坏的面积扩大化，但由于其简易操作的特性，而常常在实战开
发中被使用。

声明:
```c++
class A
{
friend class B;
public:
private:
…
};
```

## 友元类示例:

```c++

#include <iostream>
#include <cmath>
using namespace std;


class Point{
    //声明友元类
    friend class ManagerPoint;
private:
    float _x, _y;
public:
    Point(float x=0, float y=0):_x(x),_y(y){};
    void display(){
        cout<<"("<<_x<<","<<_y<<")"<<endl;
    }

};


class ManagerPoint {
public:
    //距离计算函数
    //由于用到的Point,还没定义,结合前向声明的特点,
    //在此处只能声明函数,,这个函数的实现只能放在Point函数实现之后了
    float distance(const Point &p1, const Point &p2);
};

//距离计算函数
float ManagerPoint::distance(const Point &p1, const Point &p2) {
    float dx = p1._x - p2._x;
    float dy = p1._y - p2._y;
    //计算两点之间的距离
    return sqrt(dx * dx + dy * dy);

}

int main(){

    Point p1(3,4);
    p1.display();
    Point p2(7,8);
    p2.display();

    //使用友元类
    ManagerPoint mp;
    float d = mp.distance(p1,p2);
    cout<<"距离 p1 --- p2  "<<d<<endl;
    return 0;

}

```

# 总结
## 声明位置
友元声明以关键字 friend 开始，它只能出现在类定义中。

因为友元不是类授权的成员，所以它不受其所在类的声明区域 public  private 和 protected 的影响。

通常我们选择把所有友元声明组织在一起并放在类头之后。

具体放的位置，要看团队的一致风格
## 友元利弊
友元不是类成员，但是它可以通过对象访问类中的私有成员。

友元的作用在于提高程序的运行效率，但是，它破坏了类的封装性和隐藏性，使得非成员函数可以访问类的
私有成员。

不过，类的访问权限确实在某些应用场合显得有些呆板，从而容忍了友元这一特别语法现象。

## 注意事项

1. 友元关系不能被继承。

2. 友元关系是单向的，不具有交换性。若类 B 是类 A 的友元，类 A 不一定是类 B 的友元，
要看在类中是否有相应的声明。

3. 友元关系不具有传递性。若类 B 是类 A 的友元，类 C 是 B 的友元，
类 C 不一定是类 A 的友元，同样要看类中是否有相应的声明。