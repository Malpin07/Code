# Functor 对象模拟函数

把类对象，像函数名一样使用。

仿函数(functor)，就是使一个类的使用看上去像一个函数。其实现就是类中实现
一个 operator()，这个类就有了类似函数的行为，就是一个仿函数类了。

## operator() 语法格式

```c++
class 类名
{
    返值类型 operator()(参数类型)
        函数体
}
```
```c++
#include <iostream>
#include <math.h>
using namespace std;

class Pow
{
public:
    //仿函数
    double operator()(double a, int b){
        double result = 1;
        for(int i=0;i<b;i++){
            result *= a;
        }
        return result;
    }

};
int main()
{
    cout<<pow(5,2)<<endl;
    Pow mypow;
    cout<<mypow(5,2)<<endl;
    return 0;
}
```
## functor 的优势
```c++
functor 的优势在于，是对象形式，可以携带更多的的信息，用于作出判断。
比如，我们可以在对象初始化的时候，传入参数来决定状态，而不用去修改原代码。
```
## functor使用示例
```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//局限性较大
bool myCompare(int a, int b){
    return a < b;
}

//仿函数,可以携带更多参数
class Compare{
public:
    Compare(bool flag=true):flag(flag){}
    bool operator()(int a, int b){
        if (flag==true)
            return a < b;
        else
            return a > b;
    }
private:
    bool flag;
};

int main(){
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    vector<int> vi(arr, arr+11);
    sort(vi.begin(), vi.end(), Compare(false));

//c98的写法
//    vector<int>::iterator itr;
//    for(itr=vi.begin();itr!=vi.end();++itr){
//        cout<<*itr<<" ";
//    }

    //c++11的写法
    for(auto itr=vi.begin();itr!=vi.end();++itr){
        cout<<*itr<<" ";
    }

    //c++17的写法
//    for(auto i : vi){
//        cout<<i<<" ";
//    }

    return 0;
}

```