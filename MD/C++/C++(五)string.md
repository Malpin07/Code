<!-- TOC -->
* [C++(五)String 字符串类](#c五string-字符串类)
  * [1. 定义和初始化](#1-定义和初始化)
  * [2. 字符串比较](#2-字符串比较)
  * [数值与字符串互转函数](#数值与字符串互转函数)
    * [value to string](#value-to-string)
    * [string to value](#string-to-value)
  * [string 数组](#string-数组)
<!-- TOC -->
# C++(五)String 字符串类

string 是 C++中处理字符串的类，是对 c 语言中字符串的数据和行为的包装。使
对字符串的处理，更简单易用。


## 1. 定义和初始化
```c++

int main(){

    string *ps= new string("hello");
    cout<<ps<<endl; //0xf55e40
    cout<<*ps<<endl; //hello


    //初始化字符串
    string s1="world";
    string s2("next");

    cout<<sizeof(string )<<endl; //32
    cout<<sizeof(s1)<<endl; //32
    cout<<sizeof(s2)<<endl; //32
    cout<<s1<<endl; //world
    cout<<s2<<endl; //next

    //字符串再次赋值
    s1=s2;
    cout<<s1<<endl; //next

    //cin输入字符串
    //字符串会获取输入第一个空格之前的的数据
    //cin>>s1;
    //cout<<s1<<endl; //输入的数据


    //使用getline函数获取输入的所有数据,包括空格
    getline(cin,s1);
    cout<<s1<<endl; //输入的数据
}
```

## 2. 字符串比较
string 重载了运算符+  <  >  =  !=  += 使字符串的操作变的非常简单。其运
算方式类似于普通数值运算，这是运算符重载的好处。

```c++  

int main() {
    string s="hello world";
    string x="hello world";
    string y="helloworld!";



    cout<<s.size()<<endl; //获取字符串长度  11
    cout<<s.length()<<endl; //获取字符串长度  11
    cout<<s.empty()<<endl; //判断字符串是否为空  0


    //查找字符串
    cout<<s.find("l")<<endl; //查找字符串中第一个出现的位置  2
    cout<<s.find("l",3)<<endl; //查找字符串中从位置3开始出现的第一个位置  3


    //比较字符串
    cout<<s.compare(x)<<endl; //比较两个字符串是否相等  0
    cout<<s.compare(y)<<endl; //比较两个字符串是否相等  -1
    if(s==x){
        cout<<"s==x"<<endl;
    }
    if(s==y){
        cout<<"s==y"<<endl;
    } else{
        cout<<"s!=y"<<endl;
    }

    //截取字符串
    cout<<s.substr(3)<<endl; //获取从位置3开始到结尾的字符串  lo world
    cout<<s.substr(3,5)<<endl; //获取从位置3开始的5个字符  lo wor



    //拼接
    string z=s+x;
    cout<<z<<endl; //hello worldhello world

    y+=s;
    cout<<y<<endl; //helloworld!hello world
    
    //替换
    string a="hello world";
    string b=a.replace(3,5,"good");
    cout<<a<<endl; //hello world
    cout<<b<<endl; //hegoodd world
}
```
## 数值与字符串互转函数

### value to string

|string to_string(int val);|
|----|
|string to_string(unsigned val);|
|string to_string(unsigned long val);|
|string to_string(long long val);|
|string to_string(unsigned long long val);|
|string to_string(float val);|
|string to_string(double val);|
|string to_string(long double val);|



```c++
    int inta = 1234;
    string str = to_string(inta);
    cout<<str<<endl; //1234
    str += "5678";
    cout<<str<<endl; //12345678
```

### string to value

|int stoi(const string& str, size_t* idx = 0, int base = 10);|
|----|
|long stol(const string& str, size_t* idx = 0, int base = 10);|
|long long stoll(const string& str, size_t* idx = 0, int base = 10);|
|unsigned long stoul(const string& str, size_t* idx = 0, int base = 10);|
|unsigned long long stoull(const string& str, size_t* idx = 0, int base = 10);|
|float stof(const string& str, size_t* idx = 0);|
|double stod(const string& str, size_t* idx = 0);|
|long double stold(const string& str, size_t* idx = 0);|

函数参数:

- str: 要转换的字符串。
- idx: 指向当前解析位置的指针。
- base: 进制。

返回值:

- 转换后的数值。

```c++
   
    string str = "12345678";
    int inta = stoi(str);
    cout<<inta<<endl; //12345678
    
    string str = "1111a";
    int a  = stoi(str);
    a++;
    cout<<a<<endl;//1112

    string strbin = "-10010110001";
    string strhex= "0x7f";
    int bin = stoi(strbin,nullptr,2);
    int hex = stoi(strhex,nullptr,16);
    cout<<"bin:"<<bin<<endl;
    cout<<"hex:"<<hex<<endl;
```

## string 数组

```c++

    string strArray[10] = {
            "0",
            "1",
            "22",
            "333",
            "4444",
            "55555",
            "666666",
            "7777777",
            "88888888",
            "999999999",
    };
    for(int i=0; i<10; i++)
    {
        cout<<strArray[i]<<endl;
    }
```