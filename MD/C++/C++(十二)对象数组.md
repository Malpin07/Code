<!-- TOC -->
* [对象数组](#对象数组)
<!-- TOC -->

# 对象数组
```c++
//todo 对象数组
#include <iostream>
using namespace std;


class Stu
{
public:
    Stu(string n):_name(n){}
    //or
    //Stu(string n=""):_name(n){}

    void dis()
    {
        cout<<_name<<endl;
    }
private:
    string _name;
};

int main()
{
//  Stu s;  //没有无参构造器
 //   Stu s[5]= {Stu("zhangsan"),Stu("lisi")}; //不能指定个数，或部分初始化，则会报错。没有默认参数,就会报错

    Stu s[]= {Stu("zhangsan"),Stu("lisi")};


//  Stu * ps = new Stu[4]{Stu("zhangsan")};//没有默认参数,就会报错


//  C11 中支持此种初始化方法，但必须对指定的类个数初始化,否则会报错。

    Stu * ps = new Stu[1]{Stu("zhangsan")};
    return 0;
}
```

> 栈对象数组
> 
> 如果生成的数组，未初始化，则必调用无参构造器。或手动调用带参构造器。
> 
> 堆对象数组
> 
> 如果生成的数组，未初始化，则必调用无参构造器。或手动调用带参构造器。
> 
> 

>构造器无论是重载还是默认参数，一定要把系统默认的无参构造器包含进来。不然
生成数组的时候，可能会有些麻烦。
>

二段式初始始化:

在对象数组中，要求对象必须包含默认无参构造器的情况，但有时，默认无参构造
器并不能完全满足我们的需求，可能要再次初始化。

二段初始化，常将默认无参构造器置为空。然后再次调用初始化函数，比如 cocos
中对象生成就是这样的。