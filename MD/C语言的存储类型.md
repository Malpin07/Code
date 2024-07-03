# c语言的存储类型-存储类

## 基本类型

- 整型：char、short、int、long
- 浮点型：float、double
- 字符型：char
- 指针型：指针变量

## 复合类型

1. 数组：数组变量
2. 结构体：结构体变量
3. 共用体：共用体变量
4. 枚举：枚举变量
5. 联合体：联合体变量

## 存储类

- auto：自动存储类，默认的存储类，声明的变量将在栈上分配内存，生命周期与变量相同。
- static：静态存储类，声明的变量只分配一次内存，在程序的整个运行期间都存在，直到程序结束。
- register：寄存器存储类，声明的变量将被存放在寄存器中，生命周期与变量相同。
- extern：外部存储类，声明的变量在其他文件中定义，在本文件中只声明，不分配内存。
- typedef：类型定义，给已有类型定义别名。
- volatile：易失性存储类，声明的变量在程序运行过程中可能发生变化，编译器不会对其进行优化。
- const：常量存储类，声明的变量的值不能被修改。
- restrict：限制指针存储类，声明的指针只能指向特定内存区域。

## C11 C99 新增关键字 

1. _Alignas：用于对齐变量，可以指定变量的对齐方式。
2. _Atomic：用于声明原子变量，可以保证变量的原子性操作。
3. _Generic：用于泛型编程，可以根据变量的实际类型执行不同的操作。
4. _Noreturn：用于声明不会返回的函数。
5. _Static_assert：用于在编译时进行断言。
6. _Thread_local：用于声明线程局部变量，可以保证变量在线程间的隔离。
7. _Alignof：用于获取变量的对齐方式。
8. _Bool：用于声明布尔类型。
9. _Complex：用于声明复数类型。
10. _Imaginary：用于声明虚数类型。
11. inline：用于声明内联函数。
12. restrict：用于声明指针的限制。

# 存储类

## auto

auto 存储类是默认的存储类，声明的变量将在栈上分配内存，生命周期与变量相同。

```c    
  autoint a = 10; // 声明一个整型变量 a，分配在栈上

```


## static

同时编译多个文件时，所有未加 static 前缀的全局变量和函数都具有全局可见性。如果加了 static，就会对其它源文件隐藏。

存储在静态数据区的变量会在程序刚开始运行时就完成初始化，也是唯一的一次初始化。共有两种变量存储在静态存储区：全局变量和 static 变量，只不过和全局变量比起来，static 可以控制变量的可见范围，说到底 static 还是用来隐藏的。

static 的另一个作用是默认初始化为 0。
其实全局变量也具备这一属性，因为全局变量也存储在静态数据区。在静态数据区，内存中所有的字节默认值都是 0x00，某些时候这一特点可以减少程序员的工作量。

```c    
  static int b = 20; // 声明一个整型变量 b，分配在静态数据区

  static int c; // 声明一个整型变量 c，分配在静态数据区，默认初始化为 0
  

```


## register

register修饰的是寄存器类型的变量，在一个处理器中寄存器的个数是有限的，

所以不能将所有的变量都定义成寄存器类型的变量，寄存器类型的变量比一般

的变量运算效率高，寄存器类型的变量不能取地址。

```c    
  register int d = 40; // 声明一个整型变量 d，分配在寄存器中

```
## extern

extern 存储类声明的变量在其他文件中定义，在本文件中只声明，不分配内存。

```c    
  extern int e; // 声明一个整型变量 e，在其他文件中定义

```

## typedef

typedef 类型定义，给已有类型定义别名。

```c    
  typedef int myInt; // 给 int 类型定义别名 myInt

```
### 结构体和typedef

```c
方法1：
typedef struct student{
char name[20];
int age;
char sex;
}stu_t;   //这里的stu_t是结构体类型，不是变量了
stu_t s1; //s1就是结构体变量了

方法2：
struct student{
char name[20];
int age;
char sex;
};
typedef struct student stu_t; //stu_t是结构体类型
stu_t s1; //s1是结构体变量

方法3：
typedef struct{
char name[20];
int age;
char sex;
}stu_t;   //这里的stu_t是结构体类型，不是变量了

stu_t s1; //s1就是结构体变量了
```  
## volatile

volatile 在取数据的时候每次都从内存上获取而不从缓存上获取数据。

```c    
  volatile int f = 50; // 声明一个整型变量 f，编译器不会对其进行优化

  int g = 60; // 声明一个整型变量 g，编译器可能会对其进行优化

```

### volatile使用的场景
> 多线程访问全局变量的时候需要加volatile
> 多硬件寄存器地址封装的时候需要再前面加上volatile
> 在中断中访问非自动类型的变量需要将volatile

```c
eg:

volatile int flags; 这里的flags代表触摸屏被按下的状态，0没有触摸屏幕

1触摸了屏幕。如果flags不加volatile的时候，flags在被cpu参与运算的时候就会先

放到cache高速缓存上，如果此时触摸了屏幕内存上的flags的值就是1，但是缓存

中的值还是0，这就回出现缓存中的数据和内存上的数据不一致的现象，所以为了

解决这种问题需要再flags前加上volatile。每次取数据的时候就不存缓存中获取了，

而是直接从内存上获取最新的结果。
```
## const

const修饰的变量是只读变量，const修饰的全局变量在.ro data段，const修饰的局部变量在栈上。const经常和指针结合使用，const在谁前谁就不能修改。

> 不能说const修饰的是常量
> 
```c
#include <stdio.h>

const int a=10;
void test(void)
{
    const int b=10; //这里的b可以通过q指针修改，说明b在栈区
    int *q = &b; 
 
    *q = 200;

    printf("b = %d\n",b);
}
int main(int argc, const char *argv[])
{
    //int *p = &a;
    //*p = 10;  //会出现"段错误"，全局变量a在.ro data段
  
    test();
    
    return 0;
} 
```

const int *p = &a:*p不能被修改,p是可以修改的

int const *p = &a;:*p不能被修改,p是可以修改的

int * const p=&a;:p不能被修改，但*p可以修改

const int * const p = &a;:p不能被修改，*p也不可以修改

```c
#include <stdio.h>

int main(int argc, const char *argv[])
{
    const int a = 10; 
    int b = 555;
    const int *p = &a; 
    //*p = 666; //编译无法通过，因为*p被const修饰了，无法更改
        
    p = &b; //这个赋值是正确的，p是可以被改变的                                                 
    return 0;
}
```
```c
#include <stdio.h>

int main(int argc, const char *argv[])
{
    const int a = 10; 
    int b = 555;
    int * const p = &a; 

    *p = 666;
    printf("a = %d\n",a);

    //p = &b; //p被const修饰了，p不能改，但*p可以改 
    return 0;
}
```