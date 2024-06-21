# shell编程

## 1.shell脚本
shell脚本是一种解释性语言，它是由shell命令组成的，可以被解释器解释执行，从而实现一些自动化任务。
shell种类如下：

sh :是贝尔实验室的工程师研发出来的。

csh：具备c语言风格的命令行解析器

ksh：在sh的基础上增加数组，函数，和用户交互效果。

bash：它具备csh和ksh的所有的优点，在ubuntu上使用的就是/bin/bash
### shell编程的基本写法
1. 脚本以#!/bin/bash开头
2. 脚本中可以包含任意shell命令
3. 脚本中可以包含变量
4. 脚本中可以包含条件判断和循环
5. 脚本中可以包含函数
6. 脚本中可以包含注释
7. 脚本中可以包含其他shell脚本

### shell脚本的执行方式

执行shell脚本有如下三种方式：

```shell
./01test.sh
bash 01test.sh
source 01test.sh

执行脚本方式的区别：

./执行脚本，脚本必须拥有可执行权限。而bash和source执行脚本的时候脚本可以没有执行权限
./和bash执行脚本的时候是会新开子终端执行，然后将结果回传到当前终端。而source是在当前终端执行的脚本。
```

## 脚本的执行权限

```shell
#!/bin/bash

chmod +x 脚本名.sh #给脚本添加执行权限
```



## 脚本的注释

```shell


#!/bin/bash

# 单行注释

:<<EOF

多行注释

EOF

```
## 2.shell脚本的变量
shell中的变量没有类型，使用的时候也不要定义。shell中的

变量在赋值的时候使用=（前后不能有空格），在shell脚本中

值默认都是字符串。

### 变量的定义及赋值

```shell
#!/bin/bash
var1=123                                                                                     
var2=abc  #在shell脚本中给变量赋值的时候不能再等号前后出现空格
var3='hello world' #如果值字符串中有空格需要使用单引号
var4="hi $var2"  #如果值字符串中有获取变量值过程使用双引号
echo $var1
echo $var2
echo $var3
echo $var4

```

### 变量的使用
```
 $变量名或${变量名}
 
 注意在获取变量的结果时，不能写成如下方式：

$(变量名) #shell脚本中命令置换语法

$[变量名] #shell脚本中算术运算语法
```

#### 使用shell脚本对var1和var2进行交换

```shell
#!/bin/bash
var1="www.baidu.com"
var2="www.hqyj.com"
                                  
echo "交换前：var1=$var1,var2=$var2"
var3=$var1
var1=$var2
var2=$var3
echo "交换后：var1=$var1,var2=$var2"
```

## 位置变量

位置变量是指在执行shell脚本时，将执行脚本时传递给脚本的参数，赋值给位置变量。

位置变量从$1开始，$1表示第一个参数，$2表示第二个参数，依次类推。

```shell
./05var.sh 11 22 abc www.baidu.com

$0:脚本的名字

$1:获取的是11字符串

$2:获取的是22字符串

$3:获取的是abc字符串

$4:获取的是www.baidu.com字符串

$5...$9...${n}:获取对应位置的变量

$*或$@：代表的是命令行所有的参数

$#:命令行参数的个数

```
```shell
#!/bin/bash

echo $0
echo $1
echo $2
echo $*
echo $@
echo $#
```
## 命令置换

命令置换是指在执行shell脚本时，将命令执行的结果赋值给变量。

命令置换的格式是$(命令)  `命令`

```shell
变量名=`ls`
或
变量名=$(ls)


#!/bin/bash
var1=`ls`  #将ls的结果赋值给var1
var2=$(ls /) #将ls /的结果赋值给var2变量

echo "$var1"
echo "*********************************"
echo "$var2" 
```
> 环境变量
> 在linux系统中系统使用的变量叫做环境变量,使用如下命令可以查看环境变量。
> env 查看所有的环境变量
> echo ${PATH} 只查看PATH环境变量
> HOME:存放当前用户家目录的环境变量
> USERNAME：存放当前用户的用户名
> PATH:存放ubuntu系统可执行程序（命令）的路径
> ```shell
> #!/bin/bash
> var1=${HOME}
> var2=${PATH}
> echo $var1
> echo $var2
> export PATH=${PATH}:/home/linux/ #export修改的环境变量可以作用当前终端，需要使用source执行
> ```
> 注：如果想要永久修改系统的PATH，可以在如下文件中修改
> 
> sudo vi /etc/environment
> 
> 或者
> 
> sudo vi ~/.bashrc在这个文件中添加如下语句
> 
> export PATH=${PATH}:/home/linux/

## 数组

数组是shell中的一种特殊变量，可以存储多个值。数组通过小括号表示，成员和成员间是空格分隔的。
```shell
arr=(11 22 33 abc www.baidu.com)

或

arr=([0]=11 [1]=22 [5]=cc)
```
### shell中数组成员访问方式

```shell
${数组名[下标]} #数组成员的访问方式

或
${数组名[*]}
${数组名[@]}#访问数组中的所有的成员
```
```shell
#!/bin/bash
arr=(11 22 33 44) 

echo ${arr[0]}
echo ${arr[1]}
echo ${arr[2]}
echo ${arr[3]}

echo "**********************************"
echo ${arr[*]}
echo "**********************************"
echo ${arr[@]}  
```

### 获取数组中成员所占的字节数

```shell
echo ${#arr[下标]}

#!/bin/bash
arr=(11 22 33 www.baidu.com)

echo "**********************************"
echo ${#arr[3]} #获取arr[3]所占的字节数
echo "**********************************"
echo ${#arr} #获取长度

```
### 数组的拼接

```shell
arr1=(abc 123)

arr1=(${arr1[*]} hello) #将hello字符串拼接到arr1结尾

#!/bin/bash
arr1=(abc 123)
arr2=(www tttt hhhh)

arr1=(${arr1[*]} ${arr2[@]}) #将arr2拼接到arr1的结尾
echo ${arr1[*]} #abc 123 www tttt hhhh
arr1=(${arr1[0]} ${arr2[@]} ${arr1[1]}) #将arr2插入到arr1[0]和arr1[1]之间
echo ${arr1[*]}  #abc www tttt hhhh 123
```

### 数组的截取

```shell
${数组名[@或*]:起始位置:截取长度}

#!/bin/bash
arr1=(abc 123 www tttt hhhh)

echo ${arr1[@]:1:3} #从下标为1开始截取3个字符串
echo ${arr1[*]:1:3}
```


## 运算符

### 算术运算符
运算方式
1. (( ))
2. ret=$[]
3. expr

幂运算符：**


```shell
+：加法
-：减法
*：乘法
/：除法
%：取余
```
```shell
#!/bin/bash

var1=10
var2=20

echo $((var1+var2))
echo $((var1-var2))
echo $((var1*var2))
echo $((var1/var2))
echo $((var1%var2))

n=1
((n++))
echo $n

((mul=5*5))
echo $mul

((mul1=3**4))
echo $mul1
i=10
j=5
((j+=i++))
echo $j
echo $i
```
```shell
30
-10
200
0
10
2
25
81
15
11
```
### $[ ]:
```shell
#!/bin/bash
sum=$[10+20]
echo $sum

val1=10
val2=20
sum=$[val1+val2]
echo $sum
sun=$[$val1+$val2]

n=0
#$[n++]#错误写法
n=$[n+1]
echo $n
n=$[++n]
echo $n

```
```shell
30
30
1
2

```
### expr:
```shell
#!/bin/bash
expr 10+20 #expr自带打印功能 运算符前后无空格不进行运算
expr 10 + 20

  
  
val1=10
val2=20
expr $val1 + $val2

expr 10 \* 20 #使用反斜杠进行转义
expr 3 ** 4 #expr不支持幂运算

expr length "123456789" #获取字符串长度
expr substr "123456789" 1 5 #截取
expr index "123456789" 9 #获取子字符串的在字符串中的位置
expr match "qwer" "qw" #后面和前面比较,相同返回子串长度,不同返回0
```
### 练习截取文件名
```shell
fl=$1
echo $fl
N=$(expr index $fl ".")
#L=$(expr length $fl)
expr substr $fl 1 $(($N-1))
expr substr $fl $(($N+1)) $(expr length $fl)
```



### 关系运算符

```shell
-eq：等于 equal
-ne：不等于 Not equal
-gt：大于 Greater than
-ge：大于等于 Greater than or equal 
-lt：小于  Less than
-le：小于等于 Less than or equal t
```
```shell
#!/bin/bash

var1=10
var2=20

if [ $var1 -eq $var2 ]
then
    echo "var1等于var2"
else
    echo "var1不等于var2"
fi
```

### 逻辑运算符

```shell
!：非
-o：或
-a：与
```
```shell
#!/bin/bash

var1=10
var2=20

if [ $var1 -eq 10 -o $var2 -eq 20 ]
then
    echo "var1等于10或var2等于20"
else
    echo "var1不等于10且var2不等于20"
fi
```

## read 输入
### 读取用户输入

```shell
read 变量名
```

```shell
#!/bin/bash
    

echo "请输入你的名字："
read name

echo "你好，$name！"
```
#### read的选项

```shell
-p：指定提示信息
-t：指定等待时间
-n：指定读取字符的个数
-a：将输入的值以数组的形式读入
-s：隐藏输入的字符
```

```shell
#!/bin/bash


read -p "请输入：" name

echo "$name！"
```

```shell
#!/bin/bash

read -p "请输入：" -t 5 name

echo "$name"
```

```shell
#!/bin/bash


read -p "请输入：" -n 5 name

echo "$name"
```
```shell
#!/bin/bash
read -p "请输入：" -a arr

echo "你输入的数组为："
echo ${arr[@]}
echo "第一个元素为：${arr[0]}"
echo "第二个元素为：${arr[1]}"
```
```shell

#!/bin/bash

echo "输入："
read -s password

echo $password
```

## echo 输出

```shell
echo 输出内容
```
> echo -n 不换行输出内容
> 
> echo -e 解析内容中的转义字符

## 条件语句

### if语句

```shell
if [ 条件判断 ]
then
    语句块1
elif [ 条件判断 ]
then
    [语句块2]
    ...
else
    [语句块n]
fi
```
```shell
#!/bin/bash


if [ $var1 -eq 10 ]
then
    echo "var1等于10"
elif [ $var1 -eq 20 ]
then
    echo "var1等于20"
else
    echo "var1不等于10或20"
fi
```
#### if对象判断方法

```
(1)字符串对象(一定要注意在进行字符串的判断的时候都需要加上""
    -z 判断字符串是否为空            
    -n 判断字符串是否为非空        
    =或== 都是用来判读字符串是否相等  
    !=    不等于           
    \>    大于 (防止误认为重定向)  
    \<    小于                
    练习1：输入两个字符串，判断大小

(2)数字对象
    -eq : 等于     
    -ne : 不等于    
    -gt : 大于      
    -lt : 小于  
    -ge : 大于等于  
    -le : 小于等于   
    练习2：请输入一个学生的成绩，判断学生等级 
    练习3：输入年份，判断平闰年

(3)文件属性
    -b filename 判断文件是否存在，是否是块设备    
    -c filename 判断文件是否存在，是否是字符设备  
    -d filename 判断文件是否存在，是否是目录      
    -f filename 判断文件是否存在，是否是普通文件   
    -p filename 判断文件是否存在，是否是管道文件   
    -L filename 判断文件是否存在，是否是链接文件 （经测试链接文件也是普通文件）
    -S filename 判断文件是否存在，是否是套接字文件 
    -e filename 判断文件是否存在
    -s filename 判断文件是否存在，判断文件是否为空
    练习4：输入文件名，输出文件的类型

(4)文件权限
    -r filename 判断文件是否存在，是否有可读权限 
    -w filename 判断文件是否存在，是否有可写权限  
    -x filename 判断文件是否存在，是否有可执行权限
    练习5：输入文件名判断文件是否有可以权限，如果没有给它加上
    可写权限，然后向文件最后追加一句话

(5)文件比较
    -nt  文件是否更新 
    -ot  文件是否更旧 
    -ef  文件的inode是否一致 

(6)逻辑运算
    -a   与   
    -o   或  
    !    非
```

#### 字符串比较
```shell
#!/bin/bash
read -p "str1:" str1
read -p "str2:" str2

if [ -n "$str1" -a -n "$str2" ]
then
	if [ "$str1" \> "$str2" ]
	then
		echo "str1>str2"
	elif [ "$str1" \< "$str2" ]
	then
		echo "str1<str2"
	else
		echo "=="
	fi
else
	echo "null"
fi
```
#### 输入学生的成绩判断是否合法
```shell
#!/bin/bash
read -p "input score >  " score
if [ -n "$score" ]
then
    if [ "$score" -lt 0 -o "$score" -gt 100 ]
    then
        echo "输入的成绩不合法"
    else
        echo "输入的成绩合法"
    fi  
else
    echo "没有输入学生成绩，请重新输入"
fi  
```
#### 请输入学生的成绩，输出学生的等级
```shell
#!/bin/bash

read -p "input score >  " score
if [ -n "$score" ]
then
    if [ "$score" -lt 0 -o "$score" -gt 100 ]
    then
        echo "输入的成绩不合法"
    else
        if [ $score -ge 90 ]
        then                                                             
            echo "A"
        elif [ $score -ge 80 ]
        then 
            echo "B"
        elif [ $score -ge 70 ]
        then
            echo "C"
        elif [ $score -ge 60 ]
        then 
            echo "D"
        else
            echo "E"
        fi
    fi  
else
    echo "没有输入学生成绩，请重新输入"
fi

```
#### 判断年是平年还是闰年
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

#### 输入文件判断文件是否是普通文件
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
#### 判断文件的权限 
```shell
#!/bin/bash
read -p "input file> " file

if [ -r $file ]
then
    echo "有读权限"
else
    echo "没有读权限"
fi
```
#### 输入文件名判断文件是否有可写权限，如果没有给它加上可写权限，然后向文件最后追加一句话
```shell
#!/bin/bash
read -p "input file> " file

if [ -w $file ]
then
    echo "有写权限"
else
    echo "没有写权限，添加了写权限"
    chmod u+w $file
fi

echo "向文件中追加了hello world"                                                                
echo "hello world" >> $file
```

#### 判断文件的时间戳
```shell
#!/bin/bash

read -p "input file1 > " f1
read -p "input file2 > " f2

if [ $f1 -nt $f2 ]
then
    echo "f1的时间戳新于f2"
else
    echo "f1的时间戳旧于f2"                                                                     
fi
````
#### 输入(xx.c)文件，判断文件的时间戳时候新于当前的脚本文件，如果新于脚本文件就对当前文件进行gcc，编译否则就不编译。编译之后执行可执行程序。
```shell
#!/bin/bash
mkfile=$0
read -p "input file > " gcc_file

if [ $gcc_file -nt $mkfile ]
then
    echo ".c文件的时间戳更新，需要编译文件"
    gcc $gcc_file
else
    if [ ! -e "a.out" ]
    then
        echo ".c文件的时间戳旧，但是a.out不存在，也进行编译"
        gcc $gcc_file                                            
    fi  
fi

echo "*********执行a.out************"
./a.out
echo "*********结束a.out************"
```

### case语句

```shell
case 变量 in
值1)
    语句块1
    ;;
值2)
    语句块2
    ;;
...
*)
    语句块n
    ;;
esac
```
```shell
#!/bin/bash
    
echo "请输入数字："
read num


case $num in
1)
    echo "你输入的数字是1"
    ;;
2)
    echo "你输入的数字是2"
    ;;
*)
    echo "你输入的数字不是1或2"
    ;;
esac
```


## 循环语句

### for循环



```shell
for 变量 in 值1 值2 ... 值n
do
    语句块
done
```

```shell
#!/bin/bash

    
for i in 1 2 3 4 5
do
    echo $i
done
```

### select /in
select/in会增加用户交互效果，本身也是循环语句
```shell
select 变量 in 值1 值2 ... 值n
do
    语句块
    
done
```
#### 用法实例
```shell
#!/bin/bash
export PS3="input >" #修改选择提示符       
select var in 11 22 33 44
do
    echo $var
done
```
```shell
#!/bin/bash
export PS3="input >"
select chose in windows macOS iPhone Android HormonyOS
do
    case $chose in
        windows)
            echo "欢迎进入windows操作系统"
            ;;
        macOS)
            echo "欢迎进入macOS操作系统"
            ;;
        *)  
            echo "欢迎进入移动设备操作系统"
            ;;
    esac
done   
#结束上述程序：ctr+d或者ctrl+c
```

### while循环



```shell
while [ 条件判断 ]
do
    语句块
done
```



```shell
#!/bin/bash



i=1
    
while [ $i -le 5 ] #循环5次
do
    echo $i
    i=$((i+1))
    
done
```

### 练习
> 判断用户家目录下是否存在file-dir和dir-dir目录，如果不存在就创建，如果存在就清空
> 向脚本输入任意一个路径，将这个路径下的文件拷贝到file-dir下将目录拷贝到dir-dir下
> 输出拷贝的文件的个数和目录的个数
> 
```shell
#!/bin/bash
arr=("/home/linux/file-dir" "/home/linux/dir-dir")

i=0
while [ $i -lt ${#arr[*]} ]
do
    if [ -d ${arr[$i]} ]
    then
        read -p "${arr[$i]}目录存在，是否清空[Y/n]? " chose
        case $chose in
            "YES"|"yes"|"Y"|"y")
                echo "已清空${arr[$i]}目录"
                rm -rf ${arr[$i]}/*
                ;;
            "NO"|"no"|"N"|"n")
                echo "不清空，程序退出..."
                exit                    
                ;;
            *)
                echo "输入错误，请重试..."
                continue 
                ;;
        esac
    else
        echo "目录${arr[$i]}不存在，已新建"
        mkdir ${arr[$i]}
    fi  
    ((i++))
done

read -p "input path > " path
if [ -z $path ]
then
    echo "没有输入路径，请重试..."
    exit
else
    if [ ! -d $path ]
    then
        echo "输入的路径不存在，请重试..."
        exit
    fi  
fi

prr=(`ls ${path}`)
i=0
f=0
d=0
while [ $i -lt ${#prr[*]} ]
do
    if [ -f "$path/${prr[$i]}" ]
    then
        cp $path/${prr[$i]} ${arr[0]}
        ((f++))
    elif [ -d "$path/${prr[$i]}" ]
    then
        cp $path/${prr[$i]} ${arr[1]} -r
        ((d++))
    fi  
    ((i++))
done

echo "拷贝的文件个数:$f"
echo "拷贝的目录个数:$d"
~      
```
> 使用shell脚本编写一个实时时钟代码
> 
```shell
#!/bin/bash
year=2024
month=12
day=31
hour=23
min=59
sec=57

while true
do

#秒+1
	sec=$((sec+1))
	if (( $sec == 60 ))
	then
		min=$((min+1))
		sec=0
	fi
#分钟+1
	if (( $min == 60 ))
	then
		hour=$((hour+1))
		min=0
	fi
#小时+1
	if (( $hour == 24 ))
	then
		day=$((day+1))
		AddMonth
		hour=0
	fi



AddMonth(){

#月+1
case $month in
4|6|9|11)
          if (($day==31))
          then
              month=$((month+1))
              day=1
          fi
          ;;
	    2)
        if (((year%4==0&&year%100!=0) || (year%400==0)))
        then
                if (($day==30))
                then
                  month=$((month+1))
                  day=1
                fi
        else
                if (($day==29))
                then
                  month=$((month+1))
                  day=1
                fi
        fi
        ;;
1|3|5|7|8|10|12)
        if (($day==32))
        then
          month=$((month+1))
          day=1
          AddYear
        fi
		 ;;
esac

}
#年+1
AddYear(){

if (($month==13))
then
	year=$((year+1))
	month=1
fi
}
	printf "%d-%02d-%02d %02d:%02d:%02d\r" $year $month $day $hour $min $sec
	sleep 1
done

```


### until循环



```shell
until [ 条件判断 ]
do
    语句块
done
```



```shell
#!/bin/bash



i=1
    
until [ $i -gt 5 ] #直到i大于5才退出循环
do
    echo $i
    i=$((i+1))
    
done
    
echo "循环结束"
```
### break语句
break n #退出n层循环
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
### continue语句
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
## shell中函数的用法

```shell
函数名() {
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


```shell


#!/bin/bash

fun1() {
    echo "这是第一个函数"
}



fun2() {
    echo "这是第二个函数"
}
    
    
fun1
fun2
```

```shell
#!/bin/bash


fun1() {
     echo "这是第一个函数"
     echo "第一个函数的第一个参数为：$1"
     echo "第一个函数的第二个参数为：$2"
        
}



fun2() {
     echo "这是第二个函数"
     echo "第二个函数的第一个参数为：$1"
     echo "第二个函数的第二个参数为：$2"
     
}



fun1 10 20
fun2 30 40
```
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
```shell
#!/bin/bash
function add()
{
    local sum=0
    ((sum=$1+$2))
    echo $sum
}

ret=`add 123 456` #将函数执行的结果赋值给ret
echo "ret=$ret" 
```
### 函数的练习
实现多个数求和的函数
```shell
#!/bin/bash
function sum()
{
    local sum=0
    for var
    do 
        ((sum+=$var))
    done
    echo $sum
}

ret=`sum $@`
echo $ret
```
封装打印二进制的函数
```shell
#!/bin/bash

function print_bin()
{
    flags=0
    echo -n "0b"
    for ((i=0;i<32;i++))
    do  
        if ((($1<<i)&0x80000000))
        then
            echo -n "1"
            ((flags=1))
        else
            if ((flags==1))
            then
            echo -n "0"
            fi                                                                                                                               
        fi
    done

    echo ""
}

read -p "input num > " num 
ret=`print_bin $num`
echo $ret
```

输入用户名判断用户是否存在，如果存在就将用户的uid和gid输出
```shell
#!/bin/bash
function get_username_line()
{
    local line
    line=`grep "^$1" -n /etc/passwd | cut -d ":" -f 1`
    echo $line
}
function get_uid_gid()
{
    local info
    info=`head -$1 /etc/passwd | tail -1 | cut -d ":" -f 3,4`
    echo $info
}
read -p "input username > " usrname
if [ -z "$usrname" ]
then
    echo "请输入用户名，不能输入空"
    exit
else                                              
    line=`get_username_line $usrname`
    if [ -z "$line" ]
    then
        echo "输入的$usrname用户不存在,请重试"
    else
        info=`get_uid_gid $line`
        echo "输入的用户存在，UID和GID是：$info"
    fi  
fi
```
## 脚本的调试

shell脚本的调试有两种方式：
    
1. 输出调试信息
2. 使用shell的内置命令

### 输出调试信息

```shell
#!/bin/bash

echo "脚本开始执行"

# 脚本的执行代码

echo "脚本执行结束"
```

### 使用shell的内置命令

```shell
#!/bin/bash

set -x #开启调试模式

# 脚本的执行代码

set +x #关闭调试模式
```


## other

#### **判断用户家目录下是否存在file-dir和dir-dir目录，如果不存在就创建，如果存在就清空向脚本输入任意一个路径，将这个路径下的文件拷贝到file-dir下将目录拷贝到dir-dir下输出拷贝的文件的个数和目录的个数**
 
    
```shell
#!/bin/bash
arr=("/home/linux/file-dir" "/home/linux/dir-dir")

i=0
while [ $i -lt ${#arr[*]} ]
do
    if [ -d ${arr[$i]} ]
    then
        read -p "${arr[$i]}目录存在，是否清空[Y/n]? " chose
        case $chose in
            "YES"|"yes"|"Y"|"y")
                echo "已清空${arr[$i]}目录"
                rm -rf ${arr[$i]}/*
                ;;
            "NO"|"no"|"N"|"n")
                echo "不清空，程序退出..."
                exit                    
                ;;
            *)
                echo "输入错误，请重试..."
                continue 
                ;;
        esac
    else
        echo "目录${arr[$i]}不存在，已新建"
        mkdir ${arr[$i]}
    fi  
    ((i++))
done

read -p "input path > " path
if [ -z $path ]
then
    echo "没有输入路径，请重试..."
    exit
else
    if [ ! -d $path ]
    then
        echo "输入的路径不存在，请重试..."
        exit
    fi  
fi

prr=(`ls ${path}`)
i=0
f=0
d=0
while [ $i -lt ${#prr[*]} ]
do
    if [ -f "$path/${prr[$i]}" ]
    then
        cp $path/${prr[$i]} ${arr[0]}
        ((f++))
    elif [ -d "$path/${prr[$i]}" ]
    then
        cp $path/${prr[$i]} ${arr[1]} -r
        ((d++))
    fi  
    ((i++))
done

echo "拷贝的文件个数:$f"
echo "拷贝的目录个数:$d"
                        
```


#### **使用shell脚本编写一个实时时钟代码**
```shell
#!/bin/bash

year=2023
month=12
day=31
hour=23
min=59
sec=55
clear

while true
do
    ((sec++))
    if ((sec>=60))
    then
        ((sec=0))
        ((min++))
        if ((min>=60))
        then
            ((min=0))
            ((hour++))
            if ((hour>=24))
            then
                ((hour=0))
                ((day++))
                case $month in
                    1|3|5|7|8|10|12)
                        if ((day>31))
                        then
                            ((day=1))
                            ((month++))
                        fi
                        ;;
                    4|6|9|11)
                        if ((day>30))
                        then
                            ((day=1))
                            ((month++))
                        fi
                        ;;
                    2)
                        if (((year%4==0 && year%100!=0) || (year%400==0)))
                        then
                            if ((day>29))
                            then
                                ((day=1))
                                ((month++))
                            fi
                        else
                            if ((day>28))
                            then
                                ((day=1))
                                ((month++))
                            fi
                        fi
                        ;;
                esac
                if ((month > 12))
                then
                    ((month=1))
                    ((year++))
                fi
            fi

        fi
    fi  
    printf "%d-%02d-%02d %02d:%02d:%02d\r" $year $month $day $hour $min $sec
    sleep 1
done
```