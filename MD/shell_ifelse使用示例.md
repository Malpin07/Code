<!-- TOC -->
* [if判断字符串是否为空实例](#if判断字符串是否为空实例)
* [if判断整数是否为奇数实例](#if判断整数是否为奇数实例)
* [if判断整数是否为偶数实例](#if判断整数是否为偶数实例)
* [if判断整数是否为正数实例](#if判断整数是否为正数实例)
* [if判断整数是否为负数实例](#if判断整数是否为负数实例)
* [输入两个字符串，输出字符串的大小关系](#输入两个字符串输出字符串的大小关系)
* [输入学生的成绩判断是否合法](#输入学生的成绩判断是否合法)
* [输入学生的成绩判断是否及格](#输入学生的成绩判断是否及格)
* [判断平年闰年](#判断平年闰年)
* [输入文件判断文件是否是普通文件](#输入文件判断文件是否是普通文件)
* [输入文件判断文件是否是目录](#输入文件判断文件是否是目录)
* [判断文件的权限](#判断文件的权限)
<!-- TOC -->

# if判断字符串是否为空实例
```shell
#!/bin/bash

read -p "input string > " str 

if [ -z "$str" ]
then
    echo "str是空"
else
    echo "str非空"                                                                         
fi
```
# if判断整数是否为奇数实例
```shell
#!/bin/bash

read -p "input integer > " num 

if [ $((num % 2)) -eq 1 ]
then
    echo "num是奇数"
else
    echo "num是偶数"                                                                         
fi
```
# if判断整数是否为偶数实例


```shell
#!/bin/bash


read -p "input integer > " num 

if [ $((num % 2)) -eq 0 ]
then
    echo "num是偶数"
else
    echo "num是奇数"                                                                         
fi
```
# if判断整数是否为正数实例

```shell
#!/bin/bash

read -p "input integer > " num 

if [ $num -gt 0 ]
then
    echo "num是正数"
else
    echo "num不是正数"                                                                         
fi
```
# if判断整数是否为负数实例

```shell
#!/bin/bash

read -p "input integer > " num 

if [ $num -lt 0 ]
then
    echo "num是负数"
else
    echo "num不是负数"                                                                         
fi
```
# 输入两个字符串，输出字符串的大小关系

```shell
#!/bin/bash
read -p "input str1 > " str1
read -p "input str2 > " str2

if [ -n "$str1" -a -n "$str2" ]
then
    if [ "$str1" \> "$str2" ]
    then
        echo "str1 > str2"
    elif [ "$str1" \< "$str2" ]              
    then
        echo "str1 < str2"
    else
        echo "str1 = str2"
    fi  
else
    echo "请不要输出空字符串"
fi

```
# 输入学生的成绩判断是否合法

```shell
#!/bin/bash
read -p "input score > " score

if [ $score -ge 0 -a $score -le 100 ]
then
    echo "score合法"
else
    echo "score非法"
fi
```
# 输入学生的成绩判断是否及格

```shell
#!/bin/bash
read -p "input score > " score

if [ $score -ge 60 ]
then
    echo "score及格"
else
    echo "score不及格"
fi
```

# 判断平年闰年

```shell
#!/bin/bash
read -p "input year > " year

if (((year%4==0&&year%100!=0) || (year%400==0)))
then
    echo "闰年"
else
    echo "平年"                                                                
fi

```

# 输入文件判断文件是否是普通文件

```shell
#!/bin/bash

read -p "input file > " file

if [ -f $file ]
then
    echo "这是普通文件"
else
    echo "文件不存在或它不是普通文件"
fi 
```

# 输入文件判断文件是否是目录

```shell
#!/bin/bash

read -p "input file > " file

if [ -d $file ]
then
    echo "这是目录"
else
    echo "文件不存在或它不是目录"
fi 
```

# 判断文件的权限

```shell
#!/bin/bash



read -p "input file > " file

if [ -r $file ]
then
    echo "文件可读"
else
    echo "文件不可读"
fi 


if [ -w $file ]
then
    echo "文件可写"
else
    echo "文件不可写"
fi 


if [ -x $file ]
then
    echo "文件可执行"
else
    echo "文件不可执行"
fi 
```




