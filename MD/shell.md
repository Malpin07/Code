<!-- TOC -->
* [shell](#shell)
  * [基本写法](#基本写法)
    * [脚本执行](#脚本执行)
    * [区别](#区别)
    * [练习](#练习)
  * [shell中的变量  ${变量名}](#shell中的变量-变量名)
    * [变量定义和赋值](#变量定义和赋值)
    * [获取变量的值](#获取变量的值)
    * [位置变量](#位置变量)
  * [命令置换 变量名=`ls` 变量名=$(ls)](#命令置换-变量名ls-变量名ls)
  * [环境变量](#环境变量)
  * [数组](#数组)
    * [数组的操作](#数组的操作)
    * [数组拼接](#数组拼接)
  * [shell中算术运算](#shell中算术运算)
    * [(())](#)
    * [$[]](#-1)
    * [expr](#expr)
  * [输入输出](#输入输出)
    * [read输入](#read输入)
      * [read -p "提示语" 变量名](#read--p-提示语-变量名)
      * [向arr中输入数组元素](#向arr中输入数组元素)
      * [使用静默模式向变量中输入字符串](#使用静默模式向变量中输入字符串)
      * [read -n 个数 变量](#read--n-个数-变量)
      * [read -t 秒数 变量](#read--t-秒数-变量)
    * [输出](#输出)
      * [echo 输出](#echo-输出)
      * [echo -e 输出 会解析转义字符](#echo--e-输出-会解析转义字符)
      * [echo -n 输出](#echo--n-输出)
  * [控制语句](#控制语句)
    * [if/else 控制语句](#ifelse-控制语句)
  * [if对象判断方法](#if对象判断方法)
    * [字符串对象](#字符串对象)
    * [数字对象](#数字对象)
    * [文件对象](#文件对象)
    * [文件权限对象](#文件权限对象)
    * [文件比较运算](#文件比较运算)
    * [逻辑运算](#逻辑运算)
    * [使用示例](#使用示例)
  * [case/in语句](#casein语句)
    * [case/in匹配项的写法](#casein匹配项的写法)
    * [使用示例](#使用示例-1)
      * [输入年和月输出这个月有多少天](#输入年和月输出这个月有多少天)
  * [while循环](#while循环)
    * [示例](#示例)
  * [for循环](#for循环)
    * [示例](#示例-1)
  * [select/in循环](#selectin循环)
    * [示例](#示例-2)
  * [break语句](#break语句)
  * [continue语句](#continue语句)
* [函数](#函数)
  * [示例](#示例-3)
  * [示例](#示例-4)
<!-- TOC -->

# shell
## 基本写法
```bash
#!/bin/bash # 指定 shell 解释器
ls # 执行命令
```

### 脚本执行
```bash
chmod +x script.sh # 使脚本可执行
```
4种方式：
> 1. 直接运行脚本 `./script.sh`
> 2. bash 运行脚本 `bash script.sh`
> 3. source 运行脚本 `source script.sh`
> 4. 使用 . (空格)脚本名称 来执行

三种方式的区别：
> 1. `./script.sh` 新创建的脚本，默认没有x执行权限，需要给它用#chmod +x test.sh的方式，添加执行权限。在生产环境中不要轻易的给文件可执行权限;
    
> 2. `bash script.sh` 该方式虽然不需要手动给脚本添加x执行权限，但是它会改变脚本默认解释器类型。比如说：脚本首行定义的是#!/bin/bash，使用该方式，它会给你改用/bin/sh解释器，也就说，最终效果=#!/bin/bash --posix
>   
> 特别之处：该方式 1.不需单独给脚本分配x执行权限；2.甚至都不需要在脚本首行声明脚本解释器类型，因为脚本是被当做该命令的参数使用的。
> 3. `source script.sh` .和source的权限，继承的是/bin/bash的权限，在执行时也是将test.sh作为参数，并不需要test.sh有执行权限；
> 和bash执行不一样的是，source和.不会创建子进程，是在当前shell进程下执行的，因为他们是内建命令，所以脚本中赋值的本地变量也会影响当前shell的，用的时候一定要注意（尽量使用前面的3种方式）。
> 
> 4. 使用 . (空格)脚本名称 来执行, 该方式，不需要单独添加x执行权限，它和source类似，权限继承与bash。
> 

### 区别
相对路径、绝对路径执行方法，需要chmod +x test.sh，给脚本单独添加x执行权限。
后2种方法，均不需要单独添加x执行权限。

相对路径、绝对路径执行方法，脚本执行时会开启一个子shell环境，在子shell执行完后，子shell环境随即关闭，然后又回到当前shell中。
后面两种. 和source方式，则是在当前shell中执行，不会开启子shell。

### 练习
```shell
#1.在自己的用户主目录下新建两个子目录subdir1 subdir2 
#2.将/etc/passwd文件拷贝到subdir1 ,将/etc/group拷贝到subdir2 
#3.将subdir2重命名为subdir 
#4.对subdir1进行打包并且压缩成xz格式 
#5.将打包后的xz格式文件拷贝到subdir目录下 
#6.解压subidr目录下的压缩格式文件 
#7.查看subidr目录下所有的文件
```

```shell
#!/bin/bash
cd ~
mkdir subdir1 subdir2
cp /etc/passwd ~/subdir1/
cp /etc/group ~/subdir2/
mv subdir2  subdir 
tar -cJvf subdir1.tar.xz subdir1
cp subdir1.tar.xz subdir/
cd subdir
tar -xvf subdir1.tar.xz
ls -l
```

## shell中的变量  ${变量名}
shell中的变量没有类型，使用的时候也不要定义。shell中的

变量在赋值的时候使用=（前后不能有空格），在shell脚本中

值默认都是字符串。

### 变量定义和赋值
```shell
#!/bin/bash
var1=123                                                                                     
var2=abc  #在shell脚本中给变量赋值的时候不能再等号前后出现空格
var3='hello world' #如果值字符串中有空格需要使用单引号
var4="test $var2"  #如果值字符串中有获取变量值过程使用双引号
echo $var1
echo $var2
echo $var3
echo $var4
````

### 获取变量的值
使用$变量名获取变量的值。或者使用${变量名}获取变量的值。

$变量名

${变量名}

> 使用shell脚本对var1和var2进行交换
> 
> ```shell
> #!/bin/bash
> var1=123
> var2=abc
> 
> var3=$var1
> var1=$var2
> var2=$var3
>
> ```
> 

### 位置变量
$0 表示脚本名，$1表示第一个参数，$2表示第二个参数，以此类推。
$*或$@：代表的是命令行所有的参数
$#：代表的是命令行参数的个数

```shell
#!/bin/bash
echo "脚本名：$0"
echo "第一个参数：$1"
echo "第二个参数：$2"
echo "所有参数：$*"
echo "参数个数：$#"
```



## 命令置换 变量名=`ls` 变量名=$(ls)

命令置换是指在shell脚本中，将命令的输出结果赋值给变量。

```shell
#!/bin/bash
var1=`ls`  #将ls的结果赋值给var1
var2=$(ls /) #将ls /的结果赋值给var2变量

echo "$var1"
echo "*********************************"
echo "$var2" 
```

## 环境变量
环境变量是指在系统中预先定义好的变量，这些变量在shell脚本中可以直接使用。

env 查看所有的环境变量

echo ${PATH} 只查看PATH环境变量

HOME:存放当前用户家目录的环境变量

USERNAME：存放当前用户的用户名

PATH:存放ubuntu系统可执行程序（命令）的路径

```shell

#!/bin/bash
var1=${HOME}
var2=${PATH}

echo $var1
echo $var2

export PATH=${PATH}:/home/linux/ #export修改的环境变量可以作用当前终端，需要使用source执行      
```

> 注：如果想要永久修改系统的PATH，可以在如下文件中修改
> 
> sudo vi /etc/environment 
> 或者
> 
>  sudo vi ~/.bashrc在这个文件中添加如下语句
> 
> export PATH=${PATH}:/home/linux/
> 
> 

## 数组
数组是一种特殊的变量，可以存储多个值。

数组的定义格式为：

成员和成员间是空格分隔的

数组名=(值1 值2 值3...)

arr=(11 22 33 abc)

数组的索引从0开始。

### 数组的操作

```shell
#!/bin/bash

#定义数组
arr=(1 2 3 4 5)



#获取数组的长度
length=${#arr[@]}
echo "数组的长度为：$length"



#获取数组的第n个元素
echo "数组的第1个元素为：${arr[0]}"
echo "数组的第2个元素为：${arr[1]}"
echo "数组的第3个元素为：${arr[2]}"
echo "数组的第4个元素为：${arr[3]}"
echo "数组的第5个元素为：${arr[4]}"



#获取数组的所有元素
echo "数组的所有元素为："
for i in ${arr[@]}
do
    echo $i
done


#获取数组中成员所占的字节数
echo "数组中成员所占的字节数："
for i in ${#arr[@]}
do
    echo ${#arr[$i]}
    
done


```

###  数组拼接

```shell
#!/bin/bash
arr1=(abc 123)
arr2=(www tttt hhhh)

arr1=(${arr1[*]} ${arr2[@]}) #将arr2拼接到arr1的结尾
echo ${arr1[*]} #abc 123 www tttt hhhh
arr1=(${arr1[0]} ${arr2[@]} ${arr1[1]}) #将arr2插入到arr1[0]和arr1[1]之间
echo ${arr1[*]}  #abc www tttt hhhh 123
```
```shell
#!/bin/bash
arr=(`ls`)
echo "当前目录下文件个数=${#arr[*]}" 
```

## shell中算术运算
在shell脚本中可以进行整数的算术运算，shell脚本的变量默认都是

字符串，所以需要使用以下的运算符号进行算术运算。shell脚本中

不能进行浮点运算。
```shell
(())

ret=$[]

expr
```
### (())
(())进行算术运算效率最高，支持c语言的各种写法。
```shell
#!/bin/bash

((sum=3+4))  #将3+4的结果赋值给sum
echo $sum

var1=123
var2=456
((sum=var1+var2)) #在使用(())进行算数运算时变量加不加$都是可以正常执行的
echo $sum

((sum=$var1+$var2))
echo $sum

n=0
((n++))  #可以进行自加运算
echo $n

((mul=3*4)) #shell脚本中的乘运算
echo $mul

((mul=3**4)) #shell脚本中的幂运算
echo $mul

i=10
sum=100
((sum+=i++)) #c语言的运算表达式在shell中也是支持的
echo "$sum----$i" 

sum=$((5+10)) #将算术运算的结果赋值给sum变量时候需要加$符号
echo $sum
```

### $[]
在使用$[]进行算术运算的时候表达式格式必须是ret=$[运算的表达式]，效率没有(())高。
```shell
#!/bin/bash
sum=$[3+4]
echo $sum

var1=123
var2=456
sum=$[var1+var2]
echo $sum

sum=$[$var1+$var2]
echo $sum

mul=$[3*4]
echo $mul

mul=$[3**4]  #3*3*3*3
echo $mul

n=0
#$[n++]  这种写法是错误的                           
#echo $n
n=$[n+1]
echo $n
```

### expr
expr在使用的时候严格注意格式，expr在进行算术运算的时候效率没有(())和$[]效率高。

```shell
#!/bin/bash
expr 3+4  #expr本身自带打印功能，如果+运算符前后没有空格不进行算术运算
          #表达式的结果是3+4
expr 3 + 4 #进行算数运算，将运算的结果打印到终端上

var1=123
var2=456
expr $var1 + $var2  #在使用expr进行算数运算的时候变量前必须加$符号

expr 3 \* 4  #expr在进行乘运算的时候需要加\进行转义，否则会认为*是通配符号

#expr 3 ** 4  #expr不支持幂运算 

sum=`expr 3 \* 4` #将expr表达式赋值给变量的时候需要使用命令置换
sum=$(expr 3 \* 4)
echo $sum


```

> expr可以进行字符串的操作
>
```shell
#!/bin/bash
str="www.hqyj.com"

expr match $str "www.hq"
#拿后面的字符串和前面的字符串进行比较如果完全相同返回子字符串长度
expr match $str "w1w.hq"
#拿后面的字符串和前面的字符串进行比较如果不同返回0

expr substr $str 1 5 
#从str中提起字符串，1表示从第一个字符开始，5提取5个字符

expr index $str 'h' 
#获取h字符在str中的下标，上述表达式的结果返回5      

expr length $str
#获取str字符串中字符的个数

echo ${#str}
#这个方式也可以获取str所占的字节的个数
```

## 输入输出
### read输入
read命令从标准输入（键盘）读取数据，并将其存储在变量中。

```shell
#!/bin/bash

echo "请输入你的名字："
read name
echo "你好，$name！"
```

#### read -p "提示语" 变量名

-p选项可以指定提示语。

```shell
#!/bin/bash

read -p "请输入你的名字：" name
echo "你好，$name！"
```

#### 向arr中输入数组元素


```shell
#!/bin/bash
read -p "input arr > "  -a  arr  #通过终端向arr输入数组
echo ${arr[*]}  #打印数组中所有的成员
echo ${arr[2]}  #打印下标位2对应的数组的成员  
```

#### 使用静默模式向变量中输入字符串

```shell
#!/bin/bash
read -s -p "请输入密码：" password
echo "你的密码是：$password"
```


####  read -n 个数 变量

输入n个字符自动停止

```shell
#!/bin/bash
read -p "input str > " -n 3 str  #在终端输入三个字符后自动结束输入
echo 
echo $str 
```

#### read -t 秒数 变量

设置等待时间，如果在指定时间内没有输入，则自动结束输入。

```shell
#!/bin/bash
read -p "input str > " -t 3 str  #在3秒内输入字符串，如果在3秒内没有输入，则自动结束输入
echo 
echo $str 
```

### 输出

#### echo 输出
echo 变量1 变量2 ...
```shell
#!/bin/bash

echo "hello world"
```

#### echo -e 输出 会解析转义字符

-e选项可以输出颜色和样式。

```shell
#!/bin/bash

echo -e "\033[1;31m hello world \033[0m" 
```

#### echo -n 输出

-n选项可以输出字符串时不换行。

```shell
#!/bin/bash

echo -n "hello world"
```

## 控制语句

### if/else 控制语句

```shell
#用法1
if [ 表达式 ]   ==> if test 表达式
then
 语句成立执行当前代码块
fi
#用法2
if [ 表达式 ] 
then
 表达式成立执行当前代码块
else
 表达式不成立执行else代码块
fi
#用法3
if [ 表达式1 ]
then
 代码块1
elif [ 表达式2 ]
then
 代码块2
elif [ 表达式3 ]
then
 代码块3
else
 代码块4
fi
```

## if对象判断方法
### 字符串对象
```shell
进行字符串的判断的时候都需要加上""
    -z 判断字符串是否为空            
    -n 判断字符串是否为非空        
    =或== 都是用来判读字符串是否相等  
    !=    不等于           
    \>    大于 (防止误认为重定向)  
    \<    小于
```
### 数字对象
```shell
    -eq : 等于     
    -ne : 不等于    
    -gt : 大于      
    -lt : 小于  
    -ge : 大于等于  
    -le : 小于等于   
```
### 文件对象
```shell
    -b filename 判断文件是否存在，是否是块设备    
    -c filename 判断文件是否存在，是否是字符设备  
    -d filename 判断文件是否存在，是否是目录      
    -f filename 判断文件是否存在，是否是普通文件   
    -p filename 判断文件是否存在，是否是管道文件   
    -L filename 判断文件是否存在，是否是链接文件 （经测试链接文件也是普通文件）
    -S filename 判断文件是否存在，是否是套接字文件 
    -e filename 判断文件是否存在
    -s filename 判断文件是否存在，判断文件是否为空
```
### 文件权限对象
```shell
    -r filename 判断文件是否存在，是否有可读权限 
    -w filename 判断文件是否存在，是否有可写权限  
    -x filename 判断文件是否存在，是否有可执行权限
```
### 文件比较运算
```shell
    -nt  文件是否更新 
    -ot  文件是否更旧 
    -ef  文件的inode是否一致 
```
### 逻辑运算
```shell
    -a   与   
    -o   或  
    !    非
```

### 使用示例
[shell_ifelse使用示例.md](shell_ifelse%E4%BD%BF%E7%94%A8%E7%A4%BA%E4%BE%8B.md)

## case/in语句

```shell
case 变量 in
 匹配项1)
  语句块1
  ;;
 匹配项2)
  语句块2
  ;;
  *)
  语句块n
  ;;
esac
```
### case/in匹配项的写法
```shell
通配符

*：所有的任意的字符

[0-9]或[a-z]或者[abxyz]匹配[]内的任意一个字符

[^abc]:表示匹配除abc之外的任意一个字符

?:通配任意一个字符

在匹配项中可以使用|运算符

"YES"|"yes"|"Y"|"y")

```

### 使用示例
```shell
#!/bin/bash
echo "输入1或2："
read num
case $num in
1|2)
 echo "你输入的数字是$num"
 ;;
*)
 echo "你输入的数字不是1或2"
 ;;
esac
```
#### 输入年和月输出这个月有多少天
```shell
#!/bin/bash
read -p "input (year month) > " year month

case $month in
    1|3|5|7|8|10|12)
        echo "$year-$month has 31 day!"
        ;;
    4|6|9|11)
        echo "$year-$month has 30 day!"
        ;;
    2)  
        if (((year%4==0&&year%100!=0) || (year%400==0)))
        #if [ $((year%4)) -eq 0  -a $((year%100)) -ne 0 -o $((year%400)) -eq 0 ]
        then
            echo "$year-$month has 29 day!"
        else
            echo "$year-$month has 28 day!"
        fi
        ;;
    *)  
        echo "input error,try again"          
        ;;
esac
```
## while循环

```shell
while [ 表达式 ]
do
 语句块
done
```
### 示例
```shell
#!/bin/bash
i=1
while [ $i -le 10 ] 
do
 echo $i
 ((i++))
done
```

## for循环

```shell
#用法1
for ((i=0;i<100;i++))
do
 循环体
done

#用法2
for 变量 in 参数列表
do
 循环体
done

#用法3
for 变量    #将位置变量作为参数列表
do
 循环体
done
```

### 示例
```shell
#!/bin/bash
i=0
sum=0

for ((i=0;i<=100;i++))
do
    ((sum+=i))
done                                                                           

echo $sum


for i in 1 2 3 4 5
do
    echo $i
done

for file in `ls`
do
    echo $file
done
```

## select/in循环
```shell
select 变量 in 列表
do
 语句
done
```

### 示例

```shell
#!/bin/bash
export PS3="input >" #修改选择提示符 
select item in 1 2 3 4 5
do
    echo "你选择的选项是：$item"
done
```


## break语句

break n #退出n层循环

```shell
#!/bin/bash
i=1
while [ $i -le 10 ] 
   
 
 do
    echo $i
    ((i++))
    if [ $i -eq 5 ]
    then
        break  #退出当前循环
    fi
done
```
```shell
#!/bin/bash
i=0
while true
do
    echo "这是外循环"
    sleep 1
    while true
    do
        echo "这是内循环"
        sleep 1
        ((i++))
        if [ $i -ge 5 ] 
        then
            break 2   #退出两层循环  
        fi
    done
done
```
## continue语句
continue n #结束n层当前循环，进而执行下一次循环
```shell
#!/bin/bash
i=0
while true
do
    echo "这是外循环"
    sleep 1
    while true
    do
        echo "这是内循环"
        sleep 1
        ((i++))
        if [ $i -ge 5 ] 
        then
            continue 2 
        fi
    done
done

```
# 函数
```shell
function 函数名()
{
 函数体
 return 结果
}
```
function是用来声明函数的，这里的function是可以省略的，但是习惯上是需要写function的


函数命名规则和c语言的函数命名规则是一样的



shell中的函数没有参数列表但是可以通过位置变量传参


$0 $1..$9..${n}


$*或$@或$#


shell中的函数体通过{}包括


shell中的函数可以通过return返回[0-255]区间内的结果，如果要返回其他值通过echo完成


shell的函数调用方法，shell中的函数只有调用才会执行


函数名 参数1 参数2...

## 示例
```shell
#!/bin/bash

#定义函数
function my_func()
{
    echo "hello world"
}


#调用函数
my_func
```

## 示例
实现多个数求和的函数
```shell
#!/bin/bash

function add()
{
    var1=1
    var2=$1
    #echo $0  #这里的$0不是函数名，而是脚本的名字
    local sum=0
    ((sum=$var1+$var2))
    return $sum #这里return的时候只能返回0-255之间的数
}

add 256 
echo $? #获取上一步执行的结果
echo $sum
#在函数内定义的变量默认是全局变量,如果在变量前加了local表示它是局部变量   
```


