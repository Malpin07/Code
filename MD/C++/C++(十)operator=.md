<!-- TOC -->
* [operator=](#operator)
  * [赋值运算符重载](#赋值运算符重载)
  * [语法格式](#语法格式)
  * [特性](#特性)
  * [实现string类](#实现string类)
<!-- TOC -->

# operator=

## 赋值运算符重载
用一个己有对象，给另外一个己有对象赋值。两个对象均己创建结束后，发生的赋值行为。


## 语法格式
```c++
类名
{
    类名& operator=(const 类名& 源对象)
    拷贝体
}
```
```c++
class A
{
    A& operator=(const A& another)
    {
    //函数体
        return *this;
    }
};

```

## 特性
1. 系统提供默认的赋值运算符重载，一经实现，不复存在。
2. 系统提供的也是等位拷贝，也就浅拷贝，会造成内存泄漏，重析构。
3. 要实现深深的赋值，必须自定义。 (1.自赋值 2.内存泄露 3.重析构)
4. 返回引用，通常不能用 const 修饰。string a,b,c; (a= b) = c; (a+b) = c

## 实现string类

mystring.h
```c++
/**
 * Created by gopher on 24-7-28 下午6:45
 */
#ifndef CDEMO_MYSTRING_H
#define CDEMO_MYSTRING_H
#include <cstring>
#include <iostream>
using namespace std;

class mystring {
private:
    char * _str;
public:
    mystring();
    mystring(char * str);
    ~mystring();
    mystring(const mystring & another);
    mystring & operator = (const mystring & another);
    mystring operator + (const mystring & another);
    mystring & operator += (const mystring & another);
    bool operator > (const mystring & another);
    bool operator >= (const mystring & another);

    bool operator < (const mystring & another);
    bool operator <= (const mystring & another);

    bool operator == (const mystring & another);

    char at(int n);
    char& operator[](int idx);


    void dis();

};


#endif //CDEMO_MYSTRING_H

```


mystring.cpp

```c++

/**
 * Created by gopher on 24-7-28 下午6:45
 */
#include "mystring.h"


mystring::mystring(){
    _str = new char[1];
    _str[0] = '\0';
}
mystring::mystring(char * str){
    int len = strlen(str);
    _str = new char[len+1];
    strcpy(_str, str);
}
mystring::~mystring(){
    delete[] _str;
}
mystring::mystring(const mystring & another){
    _str = new char[strlen(another._str)+1];
    strcpy(_str, another._str);

}

mystring & mystring::operator = (const mystring & another){
    if (this == &another){
        return *this;
    }
    delete[] this->_str;
    int  len =strlen(another._str);
    _str = new char [len+1];
    strcpy(_str, another._str);
    return *this;
}

mystring mystring::operator + (const mystring & another){
    int  len = strlen(this->_str)+strlen(another._str);
    mystring ms;
    delete[] ms._str;
    ms._str= new char[len+1];
    strcpy(ms._str, this->_str);
    strcat(ms._str, another._str);
    return ms;
}


mystring& mystring::operator += (const mystring & another){
    int catlen=strlen(this->_str);
    int srclen=strlen(another._str);
    int len=catlen+srclen;
    this->_str= static_cast<char *>( realloc(this->_str, len+1) );
    memset(this->_str+catlen,0,srclen+1);
    strcat(this->_str, another._str);
    return *this;
}

bool mystring::operator > (const mystring & another){
    return strcmp(this->_str, another._str)>0;
}
bool mystring::operator >= (const mystring &another){
    return strcmp(this->_str, another._str)>=0;
}
bool mystring::operator < (const mystring &another){
    return strcmp(this->_str, another._str)<0;
}
bool mystring::operator <= (const mystring &another){
    return strcmp(this->_str, another._str)<=0;
}
bool mystring::operator == (const mystring &another){
    return strcmp(this->_str, another._str)==0;
}


char mystring::at(int n){
    if (n<0 || n>=strlen(_str)){
        throw "out of range";
    }else{
        return _str[n];
    }
}

char& mystring::operator [] (int idx){
    if (idx<0 || idx>=strlen(_str)){
        throw "out of range";
    }else{
        return _str[idx];
    }
}



void mystring::dis(){
    cout << _str << endl;
}



```