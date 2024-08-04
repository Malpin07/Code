<!-- TOC -->
* [C++(四)类型强转](#c四类型强转)
  * [static_cast](#static_cast)
  * [reinterpret_cast](#reinterpret_cast)
  * [const_cast](#const_cast)
  * [dynamic_cast](#dynamic_cast)
<!-- TOC -->

# C++(四)类型强转
新类型的强制转换可以提供更好的控制强制转换过程，允许控制各种不同种类的强
制转换。C++提供了四种转化 static_cast，reinterpret_cast，dynamic_cast
和 const_cast 以满足不同需求，C++风格的强制转换好处是，它们能更清晰的表明
它们要干什么。

C 语言转换风格，在 C++中依然适用。

## static_cast
|语法格式|static_cast<type>(expression)|
|--------|--------|
|适用场景|static_cast 是 C++ 中的一种类型转换操作符，用于在相关类型之间进行显式转换。它提供了比 C 风格的类型转换更严格的类型检查，并且在许多情况下比 reinterpret_cast 更安全。|

```c++
1. 基本数据类型之间的转换
static_cast 可以用于基本数据类型之间的转换，例如将 int 转换为 float，或者将 double 转换为 int：
        
        int i = 42;
        float f = static_cast<float>(i); // 将 int 转换为 float
        
        double d = 3.14;
        int j = static_cast<int>(d); // 将 double 转换为 int
        CopyInsert
2. 指针类型之间的转换
在指针类型之间进行转换时，static_cast 可以用于在相关类型之间进行转换，例如在基类指针和派生类指针之间进行转换：
        
        class Base {
        public:
            virtual void print() {
                std::cout << "Base" << std::endl;
            }
        };
        
        class Derived : public Base {
        public:
            void print() override {
                std::cout << "Derived" << std::endl;
            }
        };
        
        Base* basePtr = new Derived();
        Derived* derivedPtr = static_cast<Derived*>(basePtr); // 将基类指针转换为派生类指针
        derivedPtr->print(); // 输出 "Derived"
        CopyInsert
3. 枚举类型和整数类型之间的转换
static_cast 可以用于枚举类型和整数类型之间的转换：
        
        enum Color { RED, GREEN, BLUE };
        
        Color c = RED;
        int i = static_cast<int>(c); // 将枚举类型转换为整数类型
        
        int j = 1;
        Color c2 = static_cast<Color>(j); // 将整数类型转换为枚举类型
        CopyInsert
4. 空指针类型的转换
static_cast 可以用于将 void* 指针转换为具体类型的指针：
        
        void* voidPtr = malloc(sizeof(int));
        int* intPtr = static_cast<int*>(voidPtr); // 将 void* 指针转换为 int* 指针
        *intPtr = 42;
        CopyInsert
5. 移除 const 限定符
虽然 static_cast 不能直接移除 const 限定符，但可以通过 const_cast 移除 const 后，再使用 static_cast 进行转换：
        
        const int* constPtr = new int(42);
        int* nonConstPtr = const_cast<int*>(constPtr); // 移除 const 限定符
        int value = *nonConstPtr;
```


## reinterpret_cast
|语法格式|reinterpret_cast<type>(expression)|
|--------|--------|
|适用场景|reinterpret_cast 是 C++ 中的一种类型转换操作符，用于将一种类型的指针转换为另一种类型的指针，即使这两种类型之间没有任何关系。reinterpret_cast 提供了最低级别的类型转换，通常用于需要直接操作内存布局的底层编程场景。|

```c++
1. 指针类型之间的转换
在某些情况下，你可能需要将一个指针类型转换为另一个指针类型，而这些类型之间没有继承关系或其他明显的关联。例如：
        
        void* ptr = malloc(sizeof(int));
        int* intPtr = reinterpret_cast<int*>(ptr);
        *intPtr = 42;
    
2. 函数指针的转换
在处理函数指针时，有时需要将一种类型的函数指针转换为另一种类型的函数指针。例如：
        
        typedef void (*FuncPtr)();
        void myFunction() {
            // 函数体
        }
        
        FuncPtr funcPtr = reinterpret_cast<FuncPtr>(&myFunction);
        funcPtr();
  
3. 位模式的转换
有时需要将一个类型的位模式解释为另一个类型的位模式。例如，将一个整数转换为一个指针：

        int value = 42;
        void* ptr = reinterpret_cast<void*>(value);
 
4. 处理底层硬件接口
在编写底层驱动程序或与硬件交互时，可能需要直接操作内存地址和寄存器。例如：
    
        volatile uint32_t* reg = reinterpret_cast<volatile uint32_t*>(0x12345678);
        *reg = 0xFFFFFFFF;
  
5. 跨平台开发
在跨平台开发中，有时需要将数据结构从一个平台特定的表示转换为另一个平台特定的表示。例如：
    
        struct PlatformA {
            int value;
        };
        
        struct PlatformB {
            int value;
        };
        
        PlatformA a = {42};
        PlatformB* b = reinterpret_cast<PlatformB*>(&a);

```

## const_cast

const_cast只有在将 const 添加到原始的非 const 时才是安全的
变量。尝试从原始 const 对象中删除 const 状态，以及
然后对其执行写入操作将导致未定义的行为。

总之，const_cast 是一种用于添加或移除指针或引用的 const 限定符的类型转换操作符。它主要用于在需要修改原本被声明为 const 的对象时，提供一种显式的方式来绕过 const 限制。然而，这种操作通常是不推荐的，应该谨慎使用。


|语法格式|const_cast<type>(expression)|
|--------|--------|
|适用场景|const_cast 是 C++ 中的一种类型转换操作符，用于移除 const 限定符。const_cast 用于将 const 指针转换为非 const 指针，或者将 const 引用转换为非 const 引用。const_cast 通常用于将 const 成员函数的 this 指针转换为非 const 指针，以便调用非 const 成员函数。它主要用于在需要修改原本被声明为 const 的对象时，提供一种显式的方式来绕过 const 限制。|

```c++
1. 移除 const 限定符
在某些情况下，你可能需要修改一个原本被声明为 const 的对象。虽然这种操作通常是不推荐的，但在某些底层编程场景中可能是必要的。例如：

        const int a = 10;
        int* p = const_cast<int*>(&a); // 移除 const 限定符
        *p = 20; // 修改 const 对象的值
       
2. 添加 const 限定符
虽然 const_cast 主要用于移除 const 限定符，但它也可以用于添加 const 限定符。例如：

        int b = 30;
        const int* cp = const_cast<const int*>(&b); // 添加 const 限定符
      
3. 与非 const 成员函数一起使用
在某些情况下，你可能需要调用一个非 const 成员函数，但只有 const 对象的指针或引用。使用 const_cast 可以临时移除 const 限定符，调用非 const 成员函数，然后再恢复 const 限定符。例如：

        class MyClass {
        public:
            void nonConstFunction() {
                // 非 const 成员函数
            }
        };
        
        void foo(const MyClass* obj) {
            MyClass* nonConstObj = const_cast<MyClass*>(obj);
            nonConstObj->nonConstFunction();
        }
     
4. 与 volatile 限定符一起使用
        const_cast 也可以用于添加或移除 volatile 限定符。例如：
        
        volatile int v = 42;
        int* vp = const_cast<int*>(&v); // 移除 volatile 限定符
        *vp = 50;

```


>注意事项:
> 
>1. 安全性：使用 const_cast 移除 const 限定符是非常危险的，因为它可能导致未定义行为。只有在确实需要修改原本被声明为 const 的对象时，才应该使用 const_cast。
>2. 可读性：使用 const_cast 会使代码的可读性降低，因为它明确地绕过了 const 限制。在可能的情况下，尽量使用其他更安全的方式来实现相同的功能。
>3. 替代方案：在可能的情况下，尽量使用 const 成员函数来处理 const 对象，避免使用 const_cast。
>

## dynamic_cast
    

dynamic_cast 是 C++ 中的一种类型转换操作符，用于在运行时执行向下转型（downcasting）或向上转型（upcasting）。dynamic_cast 用于在运行时执行指针或引用的向上或向下转型，从而允许程序员在运行时判断指针或引用是否指向正确的类型。dynamic_cast 主要用于实现多态性（polymorphism），即不同类型的对象可以共享同一个基类。

dynamic_cast 与 static_cast 和 reinterpret_cast 不同，它不仅可以用于基本数据类型之间的转换，还可以用于指针、引用、成员指针、函数指针之间的转换。dynamic_cast 还可以用于类之间的转换，即使这两个类之间没有继承关系。

dynamic_cast 与 const_cast 类似，它也用于移除 const 限定符。但是，dynamic_cast 与 const_cast 不同，它可以用于执行向上或向下转型。

|语法格式|dynamic_cast<type>(expression)|
|--------|--------|
|适用场景|dynamic_cast 是 C++ 中的一种类型转换操作符，用于在运行时执行向下转型（downcasting）或向上转型（upcasting）。dynamic_cast 用于在运行时执行指针或引用的向上或向下转型，从而允许程序员在运行时判断指针或引用是否指向正确的类型。dynamic_cast 主要用于实现多态性（polymorphism），即不同类型的对象可以共享同一个基类。|


```c++
1. 向下转型
dynamic_cast 可以用于执行向下转型（downcasting），即将指向派生类的指针或引用转换为指向基类的指针或引用。例如：

        class Base {
        public:
            virtual void print() {
                std::cout << "Base" << std::endl;
            }
        };
        
        class Derived : public Base {
        public:
            void print() override {
                std::cout << "Derived" << std::endl;
            }
        };
        
        Base* basePtr = new Derived();
        Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // 向下转型
        if (derivedPtr) {
            derivedPtr->print(); // 输出 "Derived"
        } else {
            std::cout << "Error: not a Derived object" << std::endl;
        }
        CopyInsert

2. 向上转型
dynamic_cast 可以用于执行向上转型（upcasting），即将指向基类的指针或引用转换为指向派生类的指针或引用。例如：

        class Base {
        public:
            virtual void print() {
                std::cout << "Base" << std::endl;
            }
        };
        
        class Derived : public Base {
        public:
            void print() override {
                std::cout << "Derived" << std::endl;
            }
        };
        
        Base* basePtr = new Derived();
        Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // 向下转型
        if (derivedPtr) {
            derivedPtr->print(); // 输出 "Derived"
        } else {
            std::cout << "Error: not a Derived object" << std::endl;
        }
        CopyInsert

3. 类之间的转换
dynamic_cast 可以用于类之间的转换，即使这两个类之间没有继承关系。例如：

        class Base {
        public:
            virtual void print() {
                std::cout << "Base" << std::endl;
            }
        };
        
        class Derived : public Base {
        public: 
            void print() override {
                std::cout << "Derived" << std::endl;
            }
        };
        
        Base* basePtr = new Derived();
        Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // 向下转型
        if (derivedPtr) {
            derivedPtr->print(); // 输出 "Derived"
        } else {
            std::cout << "Error: not a Derived object" << std::endl;
        }
        CopyInsert

4. 成员指针的转换
dynamic_cast 可以用于将成员指针转换为其他类型的成员指针。例如：

        class Base {
        public:
            virtual void print() {
                std::cout << "Base" << std::endl;
            }
        };
        
        class Derived : public Base {
        public:
            void print() override {
                std::cout << "Derived" << std::endl;
            }
        };
        
        Base* basePtr = new Derived();
        void (Base::*baseFunc)() = &Base::print;
        void (Derived::*derivedFunc)() = dynamic_cast<void (Derived::*)()>(baseFunc); // 成员指针转换
        (basePtr->*derivedFunc)(); // 输出 "Base"
        CopyInsert

5. 函数指针的转换
dynamic_cast 可以用于将函数指针转换为其他类型的函数指针。例如：

        typedef void (*FuncPtr)();
        void myFunction() {
            // 函数体
        }
        
        FuncPtr funcPtr = &myFunction;
        void (*newFuncPtr)() = dynamic_cast<void(*)()>(funcPtr); // 函数指针转换
        newFuncPtr(); // 调用函数
        CopyInsert

6. 空指针的转换
dynamic_cast 可以用于将空指针转换为其他类型的指针。例如：

        void* voidPtr = nullptr;
        int* intPtr = dynamic_cast<int*>(voidPtr); // 空指针转换
        if (intPtr) {
            std::cout << "Error: not a null pointer" << std::endl;
        } else {
            std::cout << "intPtr is a null pointer" << std::endl;
        }
        CopyInsert

7. 转换失败时的行为
dynamic_cast 在转换失败时，会返回 nullptr。因此，在使用 dynamic_cast 时，需要先判断转换是否成功。例如：

        class Base {
        public:
            virtual void print() {
                std::cout << "Base" << std::endl;
            }
        };
        
        class Derived : public Base {
        public:
            void print() override {
                std::cout << "Derived" << std::endl;
            }
        };
        
        Base* basePtr = new Base();
        Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // 向下转型
        if (derivedPtr) {
            derivedPtr->print(); // 输出 "Base"
        } else {
            std::cout << "Error: not a Derived object" << std::endl;
        }
        CopyInsert

8. 转换的安全性
dynamic_cast 转换的安全性与 static_cast 和 reinterpret_cast 类似。但是，dynamic_cast 转换的安全性比 static_cast 和 reinterpret_cast 更高，因为它可以执行多态性（polymorphism）转换。

9. 转换的效率
dynamic_cast 转换的效率与 static_cast 和 reinterpret_cast 类似。但是，dynamic_cast 转换的效率比 static_cast 和 reinterpret_cast 更高，因为它可以在运行时执行转换。

```