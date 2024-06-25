# Makefile
Makefile是用来编写编译规则的文件，Makefile可以根据文件的时间戳决定文件是否参与本次编译。

在大型项目中会使用Makefile做工程管理，决定本次那个文件参与编译，可以提升编译的效率。

## make

make命令是GNU Make的命令，它可以用来编译、链接、生成可执行文件等。

## Makefile的规则

Makefile的规则是由一系列的规则组成的，每条规则都包含三个部分：目标、依赖、命令。

- 目标：要生成的文件或可执行文件。
- 依赖：目标所依赖的文件或其他目标。
- 命令：用来生成目标的命令。

## Makefile的语法

1. 注释：以#开头的行表示注释。
2. 目标：以一个或多个空格或制表符开头，后面跟着一个或多个空格或制表符的字符串表示目标。
3. 依赖：以一个或多个空格或制表符开头，后面跟着一个或多个空格或制表符的字符串表示依赖。
4. 命令：以一个或多个空格或制表符开头，后面跟着一个或多个空格或制表符的字符串表示命令。
5. 变量：以变量名和等号开头，后面跟着一个或多个空格或制表符的字符串表示变量。
6. 条件语句：以ifeq、ifneq、ifdef、ifndef、else、endif开头，后面跟着一个或多个空格或制表符的字符串表示条件语句。
7. 伪目标：以.PHONY开头，后面跟着一个或多个空格或制表符的字符串表示伪目标。

## Makefile的示例
```
a.out:test.c   #a.out真实目标，会生成a.out文件
    gcc test.c -o a.out

clean:       #伪目标，不会生成clean文件                                                         
    rm a.out         
```
在终端上执行make，执行编译的命令
在终端上执行make clean,执行清除编译的命令
## Makefile编译文件
```
test:test.o
    gcc test.o -o test                                                         
test.o:test.s
    gcc -c test.s -o test.o
test.s:test.i
    gcc -S test.i -o test.s
test.i:test.c
    gcc -E test.c -o test.i

clean:
    rm test.i test.s test.o test
```
## 编译多文件
```
test:main.o add.o sub.o
    gcc main.o add.o sub.o -o test
main.o:main.c
    gcc -c main.c -o main.o
add.o:add.c
    gcc -c add.c -o add.o
sub.o:sub.c
    gcc -c sub.c -o sub.o
clean:
    rm *.o test  

```
## Makefile中引入变量
在Makefile中变量的使用和shell脚本中相同，不需要定义变量，直接使用变量即可。
VAR1=123

在Makefile中获取变量的值：

$(变量名)或${变量名}

### Makefile中的赋值方式，有四种：

#### =：延后赋值

```makefile
VAR1 = 123
VAR2 = $(VAR1)
VAR1 = 456
```

VAR2的值为123，因为VAR1的值被赋值为456之后，才被赋值给VAR2。

#### :=：即时赋值

```makefile
VAR1 := 123
VAR2 := $(VAR1)
VAR1 = 456
```

VAR2的值为123，因为VAR1的值被赋值为123之后，才被赋值给VAR2。

#### +=：追加赋值

```makefile
VAR1 = 123
VAR2 += $(VAR1)
VAR1 = 456
```

VAR2的值为123 456，因为VAR1的值被赋值为456之后，被追加到VAR2的后面。

#### :=：立即赋值
```
var1=123
var2:=$(var1)   #立即将var1赋值给var2 
var1=456

all:    
    @echo $(var2)  #结果是123
```


#### +=:附加赋值
```
var2=123
var2 += 456 

all:    
    @echo $(var2)  #结果是123 456                                              
~                                
``` 
#### ?=询问赋值
```
var2?=123 #询问var2之前是否被赋值过，如果被赋值过本次赋值不成立，
          #如果没有赋值过，本次赋值成立                                        

all:    
    @echo $(var2) 
```
## Makefile中的特殊变量

- $@：代表目标文件名。
- $^：代表所有的依赖文件名。
- $<：代表第一个依赖文件名。
- $*：代表目标文件名的前缀。
- $(MAKECMDGOALS)：代表make命令行中指定的目标。
- $(CURDIR)：代表当前目录。
- $(word n,list)：代表list中的第n个元素。
- $(words list)：代表list中的元素个数。
- $(dir file)：代表file的目录。
- $(notdir file)：代表file的文件名。
- $(wildcard pattern)：代表当前目录下匹配pattern的文件名。
- $(shell command)：执行shell命令，并返回命令的输出。
- $(abspath file)：代表file的绝对路径。
- $(addprefix prefix,list)：代表将list中的元素添加prefix前缀。
- $(addsuffix suffix,list)：代表将list中的元素添加suffix后缀。
- $(call function,param1,param2,...)：调用函数，并返回函数的返回值。
- $(error message)：打印错误信息并退出。
- $(warning message)：打印警告信息。
- $(info message)：打印提示信息。

## Makefile中的通配符号

1. %：匹配任意字符串。
2. *：匹配任意字符串，包括空字符串。
3. ?：匹配任意单个字符。
4. [chars]：匹配chars中的任意单个字符。
5. [!chars]：匹配除了chars中的任意单个字符。
6. {a,b,c}：匹配a、b、c中的任意一个字符串。
7. \：转义字符。


### 实例
编译.c文件，生成.o文件，并链接生成可执行文件。
```makefile
obj=main
objs=student.o main.o controller.o
main:$(objs)
	gcc -o $@ $^
%.o:%.c
	gcc  $^ -c -o $@
clean:
	rm $(objs) $(obj)
```