<!-- TOC -->
* [C++(二十二)派生类的友元](#c二十二派生类的友元)
  * [派生类析构函数](#派生类析构函数)
<!-- TOC -->
# C++(二十二)派生类的友元

由于友元函数并非类成员，因引不能被继承，在某种需求下，可能希望派生类的友
元函数能够使用基类中的友元函数。为此可以通过强制类型转换，将派生类的指针或是
引用强转为其父类的引用或是指针，然后使用转换后的引用或是指针来调用基类中的友
元函数。

```c++
#if 1
#include <iostream>
using namespace std;

// 定义Student类
class Student {
    // 友元函数声明，允许operator<<访问Student的私有成员
    friend ostream & operator<<(ostream& os, const Student& s);

public:
    // 构造函数，初始化a和b
    Student(int a, int b) : a(a), b(b) {
        cout << "Student constructor called" << endl;
    }

private:
    int a; // 私有成员变量a
    int b; // 私有成员变量b
};

// 重载Student类的输出运算符
ostream & operator<<(ostream& os, const Student& s) {
    os << s.a << " " << s.b; // 输出a和b的值
    return os;
}

// 定义Grade类，继承自Student类
class Grade : public Student {
    // 友元函数声明，允许operator<<访问Grade的私有成员
    friend ostream & operator<<(ostream& os, const Grade& g);

public:
    // 构造函数，初始化a、b和c
    Grade(int a, int b, int c) : Student(a, b), c(c) {
        cout << "Grade constructor called" << endl;
    }

private:
    int c; // 私有成员变量c
};

// 重载Grade类的输出运算符
ostream & operator<<(ostream& os, const Grade& g) {
    os << (Student&)g; // 先输出基类Student的部分
    os << " " << g.c << endl; // 再输出c的值
    return os;
}

int main() {
    // 创建一个Grade对象，并初始化a=10, b=20, c=30
    Grade g(10, 20, 30);
    // 输出Grade对象g的内容
    cout << g << endl;
    return 0;
}

#endif

```

## 派生类析构函数
析构函数的执行顺序与构造函数相反。

派生类的析构函数的功能，保证层级内与其对应的构造函数，
完成清理工作。无需指明析构关系。