

# 栈对象返回的问题

## RVO / NRVO

(具名)返回值优化((Name)Return Value Optimization，简称(N)RVO)，是这
么一种优化机制：当函数需要返回一个对象的时候，如果自己创建一个临时对象用户返
回，那么这个临时对象会消耗一个构造函数(Constructor)的调用、一个复制构造函
数的调用(Copy Constructor)以及一个析构函数(Destructor)的调用的代价。

通过优化的方式，可以减少这些开销。

Windows 和 Linux 的 RVO 和 NRVO 是有区别的。

```c++
A foo()
{
    //    return A(); //不具名返回
    A a;
    return a;
    //具名返回
}
int main()
{
    foo();
}
```
>在 main()函数调用 foo()之前，会在自己的栈帧中开辟一个临时空间，该空间的
地址作为隐藏参数传递给 foo()，在需要返回 A 对象时，就在这个临时空间上构造一个
A a，然后这个空间的地址再利用寄存器 eax 返回给 main()函数，这样 main()函数就
能获得 foo()函数的返回值了。
> 
> 

## 接收栈对象的方式不同，会影响优化效果
