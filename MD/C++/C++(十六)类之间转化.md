# C++(十五)类之间转化

## 自定义类型-转化构造函数

```c++
class 目标类
{
    目标类(const 源类型 & 源类对象引用)
    {
        根据需求完成从源类型到目标类型的转换
    }
}

目标
实现其它类型到本类类型的转化。

原理
转换构造函数，本质是一个构造函数。是只有一个参数的构造函数。如有多
个参数，只能称为构造函数，而不是转换函数。转换构造，强调的是一转一。

应用
用于传参或是作返回。
```

## explicit 关键字

关键字 explicit 可以禁止"单参数构造函数"被用于自动类型转换。
即 explicit 仅用于单参构造(默认参数构成的单参亦算)。

转化多是刻意而为之，以隐式的形式发生，为了示意同正常构造的不同，常用
explicti 关键字修饰，要求在转化时显示的调用其构造器完成转化。


```c++
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
//转化构造函数的本质，也是构造函数
class Point2D
{
    //友元类
    friend class Point3D;
public:
    Point2D(int x=0, int y=0 )
            :_x(x),_y(y){}
private:
    int _x;
    int _y;
};

class Point3D
{
public:
    Point3D(int x=0, int y=0 ,int z=0)
            :_x(x),_y(y),_z(z){}
    //转换构造函数
    explicit Point3D(const Point2D & d2)
    {
        this->_x = d2._x;
        this->_y = d2._y;
        this->_z = rand()%100;
    }
    void dumpFormat()
    {
        cout<<"("<<_x<<","<<_y<<","<<_z<<")"<<endl;
    }
private:
    int _x;
    int _y;
    int _z;
};

void foo(Point3D d3)
{
    d3.dumpFormat();
}


int main()
{
    srand(time(NULL));
    Point2D  d2(10,100);

    Point3D  d3 =(Point3D) d2;//在这里隐式调用了转换构造函数
    //!转化多是刻意而为之，以隐式的形式发生，为了示意同正常构造的不同，常用
    //!explicti 关键字修饰，要求在转化时显示的调用其构造器完成转化。

    d3.dumpFormat();
    //foo(d2);
    foo((Point3D)d2);
    return 0;
}

```
```c++


```c++
#include <iostream>
using namespace std;
//关键字 explicit 可以禁止"单参数构造函数"被用于自动类型转换
class mystring
{
public:

    explicit mystring(const char* s= nullptr)
    {
        cout<<"    mystring(const char* s= nullptr)"<<endl;
    }
};
int main()
{
    mystring s("qwer"); //显示调用转换构造
    mystring s2 = "qwer"; //隐式调用转换构造,被explicit禁止
    return 0;
}



```
```


## 自定义类型-操作符函数转化
转换函数必须是类方法，转换函数无参数，无返回。

```c++
class 源类{
    operator 目标类(void)
    {
        return 目标类构造器(源类实参);
    }
}
```

```c++
//todo 自定义类型-操作符函数转化
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Point3D
{
public:
    Point3D(int x=0, int y=0 ,int z=0)
            :_x(x),_y(y),_z(z){}

    void dumpFormat()
    {
        cout<<"("<<_x<<","<<_y<<","<<_z<<")"<<endl;
    }
private:
    int _x;
    int _y;
    int _z;
};


class Point2D
{

public:
    Point2D(int x=0, int y=0 ):_x(x),_y(y){}

    //操作符函数转化
    operator Point3D (void){
        return Point3D(_x,_y,rand()%100);
    }

private:
    int _x;
    int _y;
};




void foo(Point3D d3)
{
    d3.dumpFormat();
}


int main()
{
    srand(time(NULL));
    Point2D  d2(10,100);

    Point3D  d3 = d2;
    d3.dumpFormat();
    return 0;
}

```
