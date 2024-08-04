<!-- TOC -->
* [C++(二十三)多重继承](#c二十三多重继承)
  * [继承语法](#继承语法)
  * [构造](#构造)
  * [三角问题](#三角问题)
  * [三角关系中需要解决的问题：](#三角关系中需要解决的问题)
  * [四角继承 virtual](#四角继承-virtual)
    * [引例:](#引例)
    * [示例](#示例)
    * [示例2](#示例2)
* [虚继承](#虚继承)
<!-- TOC -->
# C++(二十三)多重继承

## 继承语法
```c++
派生类名:public 基类名 1，public 基类名 2，...,protected基类名 n
```

## 构造
```c++
派生类名::派生类名(总参列表)
        ：基类名 1(参数表 1)，基类名(参数名 2)....基类名 n(参数名 n)，
        内嵌子对象 1(参数表 1),内嵌子对象 2(参数表 2)...内嵌子对象 n(参数表 n)
{
    // 派生类新增成员的初始化语句；
}
```
```c++
#include <iostream>
using namespace std;

class Sofa{
    public:
    void sit(){
        cout << "Sitting on the sofa" << endl;
    }
};


class Bed{
public:
    void sleep(){
        cout << "Sleeping in a Bed" << endl;
    }
};

class SofaBed: public Sofa, public Bed{
    public:

};

int main() {
    SofaBed sofaBed;
    sofaBed.sit();
    sofaBed.sleep();
    return 0;
}
```

## 三角问题
多个父类中重名的成员，继承到子类中后，为了避免冲突，携带了各父类的作用域
信息,子类中要访问继承下来的重名成员，则会产生二义性，为了避免冲突，访问时需
要提供父类的作用域信息。

```c++
#include <iostream>
using namespace std;

class X{
public:
    X(int data){
        this->data = data;
        cout << "X constructor called" << endl;
    }

    void  setData(int data){
        this->data = data;
    }
    int data;
};

class Y{
public:
    Y(int data){
        this->data = data;
        cout << "Y constructor called" << endl;
    }
    int getData(){
        return data;
    }

    int data;
};

class Z: public X, public Y{
public:
    Z(int data1, int data2): X(data1), Y(data2) {
        cout << "Z constructor called" << endl;
    }
    void printData(){
        cout << "data: " << X::data << endl;
        cout << "data: " << Y::data << endl;
    }
};


int main() {
    Z z(77, 88);
    z.printData();
    z.setData(99);
    z.printData();

    cout << "getData: " << z.getData() << endl;
    return 0;
}

```

```c++
输出:
X constructor called
Y constructor called
Z constructor called
data: 77
data: 88
data: 99
data: 88
getData: 88
```

## 三角关系中需要解决的问题：
```c++
1.数据冗余问题，
2.访问不方便的问题。

解决方案，是三角转四角的问题。具体操作：
1.提取公共成员构成祖父类，即虚基类，
2.各父类虚继承虚基类。
```

## 四角继承 virtual

### 引例:
```c++
//TODO 三角转四角
//1.提取公共成员构成祖父类，即虚基类，
//2.各父类虚继承虚基类。
#include <iostream>
using namespace std;

class A{
    protected:
        int data;
};



class X:virtual public A{
public:
    X(int data){
        this->data = data;
        cout << "X constructor called" << endl;
    }

    void  setData(int data){
        this->data = data;
    }

};

class Y:virtual public A{
public:
    Y(int data){
        this->data = data;
        cout << "Y constructor called" << endl;
    }
    int getData(){
        return data;
    }

};

class Z: public X, public Y{
public:
    Z(int data1, int data2): X(data1), Y(data2) {
        cout << "Z constructor called" << endl;
    }
    void printData(){
//        cout << "data: " << X::data << endl;
//        cout << "data: " << Y::data << endl;
        cout << "data: " << data << endl;
    }
};


int main() {
    Z z(77, 88);
    z.printData();
    z.setData(99);
    z.printData();

    cout << "getData: " << z.getData() << endl;
    return 0;
}

```
```c++
输出:
data: 88
data: 99
getData: 99
```


### 示例
虚基类: 被虚继承的类就是虚基类  经提取，存有公共元素的，被虚继承的祖父类
虚继承:是一种对继承的扩展

```c++
//TODO 三角转四角
//1.提取公共成员构成祖父类，即虚基类，
//2.各父类虚继承虚基类。
#include <iostream>
using namespace std;

class A{
    protected:
        int data;
};



class X:virtual public A{
public:
    X(int data=0){
        this->data = data;
        cout << "X constructor called" << endl;
    }

    void  setData(int data){
        this->data = data;
    }

};

class Y:virtual public A{
public:
    Y(int data=0){
        this->data = data;
        cout << "Y constructor called" << endl;
    }
    int getData(){
        return data;
    }

};

class Z: public X, public Y{
public:
    Z(int data) {
        this->data = data;
        cout << "Z constructor called" << endl;
    }
    void printData(){
        cout << "data: " << data << endl;
    }
};


int main() {
    Z z(77);
    z.printData();
    z.setData(99);
    z.printData();

    cout << "getData: " << z.getData() << endl;
    return 0;
}

```

```c++
输出:
X constructor called
Y constructor called
Z constructor called
data: 77
data: 99
getData: 99
```


### 示例2
```c++      
//todo 虚继承示例
#include <iostream>
using namespace std;

class Furniture{
protected:
    float weight;
    int color;
public:
    void dis(){
        cout << "Furniture weight: " << weight << endl;
        cout << "Furniture color: " << color << endl;
    }


};


class Sofa: virtual public Furniture{
public:
    Sofa(float weight=0, int color=0){
        this->weight = weight;
        this->color = color;
        cout << "Sofa constructor called" << endl;
    }
    void sit(){
        cout << "Sitting on the sofa" << endl;
    }
};


class Bed: virtual public Furniture{
public:
    Bed(float weight=0, int color=0){
        this->weight = weight;
        this->color = color;
        cout << "Sofa constructor called" << endl;
    }
    void sleep(){
        cout << "Sleeping in a Bed" << endl;
    }
};

class SofaBed: public Sofa, public Bed{
    public:
    SofaBed(float weight, int color){
        this->weight = weight;
        this->color = color;
        cout << "SofaBed constructor called" << endl;
    }
    void dis(){
        cout << "SofaBed weight: " << weight << endl;
        cout << "SofaBed color: " << color << endl;
    }
};

int main() {
    SofaBed sofaBed(100, 200);
    sofaBed.dis();
    sofaBed.sit();
    sofaBed.sleep();
    return 0;
}
```

```c++
输出:
Sofa constructor called
Sofa constructor called
SofaBed constructor called
SofaBed weight: 100
SofaBed color: 200
Sitting on the sofa
Sleeping in a Bed
```

# 虚继承
```c++
虚继承（virtual inheritance）
在C++中主要用于解决多重继承中的菱形继承问题（Diamond Problem）。
具体来说，当一个类通过多条路径继承同一个基类时，
虚继承可以确保基类的实例在派生类中只有一个，从而避免数据冗余和二义性。
```