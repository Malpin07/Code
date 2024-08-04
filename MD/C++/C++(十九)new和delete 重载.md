<!-- TOC -->
* [operator new/delete 重载](#operator-newdelete-重载)
<!-- TOC -->

# operator new/delete 重载

```c++
语法格式
void  *operator new(size_t);
void  operator delete(void *);
void  *operator new[](size_t);
void  operator delete[](void *);
```

```c++
#include <iostream>
using namespace std;

class A
{
public:
    // 构造函数
    A(){
        // _x=1;
        // _y=2;
        // 在new中初始化了
        cout << "A()" << endl;
    }

    // 析构函数
    ~A(){
        cout << "~A()" << endl;
    }

    // 成员函数，输出_x和_y的值
    void func(){
        cout << _x << "  " << _y << endl;
    }

    // 重载new操作符
    void *operator new(size_t size){ // size为8，因为A类的大小为8字节（两个int）
        cout << size << endl;
        cout << "operator new" << endl;
        void *p = malloc(size); // 分配内存
        ((A*)p)->_x = 100; // 初始化_x
        ((A*)p)->_y = 200; // 初始化_y
        return p; // 返回分配的内存指针
    }

    // 重载delete操作符
    void operator delete(void *p){ // 8
        cout << "operator delete" << endl;
        free(p); // 释放内存
    }

    // 重载new[]操作符
    void *operator new[](size_t size){
        cout << "operator new[]" << endl;
        cout << size << endl;
        void *p = malloc(size); // 分配内存
        cout << p << endl;
        return p; // 返回分配的内存指针
    }

    // 重载delete[]操作符
    void operator delete[](void *p){
        cout << "operator delete[]" << endl;
        cout << p << endl;
        free(p); // 释放内存
    }

private:
    int _x; // 私有成员变量_x
    int _y; // 私有成员变量_y
};

int main(){
    // 使用重载的new操作符创建A类的对象
    A *pa = new A;
    pa->func(); // 调用成员函数func，输出_x和_y的值
    delete pa; // 使用重载的delete操作符释放内存

    // 使用重载的new[]操作符创建A类的数组
    A *pb = new A[3];
    delete[] pb; // 使用重载的delete[]操作符释放内存

    return 0;
}

```


如果是用 operator new[]申请的空间，用 delete 释放会造成，只有第一个元素
释放的情形。