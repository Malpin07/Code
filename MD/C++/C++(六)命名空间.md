<!-- TOC -->
* [Namespace 命名空间](#namespace-命名空间)
  * [:: 全局无名命名空间](#-全局无名命名空间)
  * [Namespace 定义](#namespace-定义)
    * [应用](#应用)
  * [同名空间](#同名空间)
<!-- TOC -->
# Namespace 命名空间

命名空间为了大型项目开发，而引入的一种避免命名冲突的一种机制。比如，在一
个大型项目中，要用到多家软件开发商提供的类库。在事先没有约定的情况下，两套类
库可能存在同名的函数或是全局变量而产生冲突。项目越大，用到的类库越多，开发人
员越多，这种冲突就会越明显。

## :: 全局无名命名空间

C++在 C 语言的基础之上，C++首次以语法的行式，确立了全局无名命空间的的存在和使用方法。
```c++
#include <iostream>
using namespace std;
int var = 100;
void func(){
    cout<<" func "<<endl;
}
int main()
{
    int var = 200;
    cout<<"main var= "<<var<<endl;
    cout<<"global var = "<<::var<<endl;
    func();
    ::func();
    return 0;
}
```


## Namespace 定义

语法 C++引入 namespace 的本质是对全局空间再次划分。确切的说，是对全局的
函数和变量再次进行作用域打包。


### 应用


```c++
#include <iostream>
using namespace std;

namespace NS1{
    int a=10;
}

namespace NS2 {
    int a=20;
}
int main() {
 一 :
    cout<<NS1::a<<endl; //10
    cout<<NS2::a<<endl; //20
    
 二: //命名空间成员，融入该语句所在的命令空间，可以会产生冲突。
    using NS1::a;
    cout<<a<<endl; //10
    using NS2::a;  //error: 'a' conflicts with a previous declaration
  

 三: //将命名空间(即全体成员)，融入该语句所在的命名空间。可能会产生命令空间。
    using namespace NS1;
    cout<<a<<endl; //10
    using namespace NS2;//err

 }
```

```c++
命名空间支持嵌套:

namespace NS1{
    int a=10;
    namespace NS2{
        int a=20;
    }
}

int main() {
    cout<<NS1::NS2::a<<endl; //20
    
    
    using NS1::a;
    using NS1::NS2::a;//error 还是会产生冲突
}
```


## 同名空间

同名命名空间可以合并，是协同开发的基础。

```c++a
namespace NS1{
    int a=10;
}


namespace NS1{
    int b=20;
}

int main() {    
    cout<<NS1::a<<endl; //10
    cout<<NS1::b<<endl; //20
}
```