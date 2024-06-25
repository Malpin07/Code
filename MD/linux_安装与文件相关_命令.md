#Linux系统命令

## 软件安装卸载命令
### 软件包介绍
软件包中包含安装的可执行程序（binary）,包含软件的说明文档，包含软件的使用的

man手册等，将这些内容打包成一个软件包，可以给用户安装使用。

(1).deb：ubuntu系统可以安装的包格式

(2).rpm：redhat系统可以安装的包格式

### 软件包命名格式
软件包的命名格式一般为：

包名-版本号.后缀名

例如：

gcc-4.8.2.tar.gz

### dpkg命令
dpkg是一个离线安装软件包的命令，dpkg不会安装依赖的库，
前提是用户需要有安装的包。

安装

sudo dpkg -i sl_5.02-1_amd64.deb

运行

sl

卸载

sudo dpkg -r sl

-r在卸载软件包的时候会保留配置文件

完全卸载

sudo dpkg -P sl

将软件包和配置文件全部卸载掉

查看软件的安装信息

sudo dpkg -l sl

查看软件安装位置信息

sudo dpkg -L sl

### apt-get命令
apt-get是一个在线安装软件包的命令，apt-get会自动安装依赖的库。

安装

sudo apt-get install sl

运行

sl

卸载

sudo apt-get remove sl

-r在卸载软件包的时候会保留配置文件

完全卸载

sudo apt-get purge sl

将软件包和配置文件全部卸载掉

更新软件包列表

sudo apt-get update

查看软件的安装信息

sudo apt-cache show sl

查看软件安装位置信息

sudo dpkg -L sl

### apt-get命令
rpm是一个安装rpm包的命令，rpm包是二进制文件，可以直接运行。

安装

sudo apt-get install sl


卸载

sudo apt-get remove sl

清除软件包

sudo apt-get clean

更新软件包列表

sudo apt-get update


下载不安装

sudo apt-get download sl

下载源代码

sudo apt-get source sl

## 压缩和解压命令
### 压缩文件后缀
常见的压缩文件后缀有：

.gz：打包的tar文件，并用gzip压缩

.bz2：打包的tar文件，并用bzip2压缩

.xz：打包的tar文件，并用xz压缩

## 压缩命令
压缩的对象是文件，而非目录

gzip压缩用时比较短，压缩率不高。

bzip2压缩用时居中，压缩率居中。

xz压缩用时比较长，压缩率高。

```shell
gzip vmlinux #对vmlinux文件进行gzip压缩

gunzip vmlinux.gz #对vmlinux.gz文件进行解压缩

bzip2 vmlinux  #对vmlinux文件进行bzip2压缩

bunzip2 vmlinux.bz2 #对vmlinux.bz2文件进行解压缩

xz vmlinux  #对vmlinux文件进行xz压缩

unxz vmlinux.xz #对vmlinux.xz文件进行解压缩
```
## 打包和解包命令
### tar命令
tar命令是Linux下最常用的打包和解包命令，可以打包和解包各种类型的文件。

tar在使用的时候需要跟如下参数
-c: 建立一个新的打包文件
-v: 显示过程
-f: 指定打包后的文件名
-z: 调用gzip压缩
-j: 调用bzip2压缩
-J: 调用xz压缩
-x: 解开打包文件


```shell
tar -cvf jdk.tar.gz jdk #打包jdk目录为jdk.tar.gz文件

tar -xvf jdk.tar.gz #解包jdk.tar.gz文件

tar -cvzf jdk.tar.gz jdk #打包jdk目录为jdk.tar.gz文件，并用gzip压缩

tar -xvf jdk.tar.gz #解包jdk.tar.gz文件，并用gzip解压缩

tar -cvfj jdk.tar.bz2 jdk #打包jdk目录为jdk.tar.bz2文件，并用bzip2压缩

tar -xvfj jdk.tar.bz2 #解包jdk.tar.bz2文件，并用bzip2解压缩

tar -cvJf jdk.tar.xz jdk #打包jdk目录为jdk.tar.xz文件，并用xz压缩

tar -xvfJ jdk.tar.xz #解包jdk.tar.xz文件，并用xz解压缩
```

## 文件分割命令
### split命令
split命令可以将一个大文件分割成多个小文件。
-b: 指定每个分割文件的大小
-d: 指定分割文件后缀
-n: 指定分割文件的个数
-a: 指定文件名长度

```shell
split -b 10m linux.iso linux #将linux.iso分割为大小为10m的小文件，文件名为linux

cat linux* > linux.iso #将分割后的文件合并为一个文件

```
## 文件操作相关命令
### cat命令
cat filename读取文件并打印到终端上

cat -n test.c #文件及文件的行号显示到终端上。

cat /etc/issue #查看ubuntu的版本号

              uname -r 查看ubuntu对应的linux内核的版本号
### head命令
head ：命令是用来查看文件的，默认显示文件的前10行

head -n 20 filename #显示文件的前20行

### tail命令
tail ：命令是用来查看文件的，默认显示文件的最后10行

tail -n 20 filename #显示文件的最后20行

### more命令
more ：命令是用来分页显示文件内容的，每次显示一屏的内容，按空格键向下翻页，按q键退出。

### less命令
less ：命令是用来分页显示文件内容的，每次显示一屏的内容，按空格键向下翻页，按q键退出。

### 管道命令
| ：管道命令，将前一个命令的输出作为后一个命令的输入。

```shell
head -20 /etc/passwd | tail -5 #查看/etc/passwd文件的前20行，并输出最后5行
```

### wc 命令
wc 命令是用来统计文件中行数、字数、字节数的命令。

-l：统计行数
-w：统计字数
-c：统计字节数

```shell
wc -l /etc/passwd #统计/etc/passwd文件有多少行

wc -w /etc/passwd #统计/etc/passwd文件有多少字

wc -c /etc/passwd #统计/etc/passwd文件有多少字节
```
### grep 命令
grep 命令是用来搜索文本中匹配的字符串的命令。

-i：忽略大小写
-n：显示行号
-v：显示不匹配的行
-w：只显示全词匹配的行
-x：只显示完全匹配的行
-R：递归搜索目录

-^root：搜索以root开头的行
-root$：搜索以root结尾的行

```shell
grep -i "root" /etc/passwd #搜索/etc/passwd文件中包含root的行，忽略大小写

grep -n "root" /etc/passwd #搜索/etc/passwd文件中包含root的行，并显示行号

grep -v "root" /etc/passwd #搜索/etc/passwd文件中不包含root的行

grep -w "root" /etc/passwd #搜索/etc/passwd文件中只包含一个完整的root的行 和-i类似

grep -x "root" /etc/passwd #搜索/etc/passwd文件中只包含root的行

grep -R "root" /etc/ #递归搜索/etc/目录下所有文件包含root的行



```

> root  : x       : 0 : 0 :    root      :  /root   : /bin/bash
> 
> 用户名: 密码占位符:UID:GID:开机看到的用户名:用户的家目录:命令行解析器

### find 命令
[linux_find+exec.md](linux_find%2Bexec.md)

### cut 命令
cut 命令用来从文件中提取指定部分，并输出到标准输出设备上。

-d：指定分隔符
-f：指定提取哪个域

```shell
cut -d: -f1 /etc/passwd #提取/etc/passwd文件中第一个域

cut -d: -f1,3 /etc/passwd #提取/etc/passwd文件中第一个和第三个域

cut -d: -f1-3 /etc/passwd #提取/etc/passwd文件中前三个域
```

### sort 命令
sort 命令用来对文件内容进行排序。

-n：按数字排序
-r：反向排序
-u：排序后，相同的行只显示一次

```shell
sort /etc/passwd #对/etc/passwd文件进行排序

sort -n /etc/passwd #对/etc/passwd文件进行数字排序

sort -r /etc/passwd #对/etc/passwd文件进行反向排序

sort -u /etc/passwd #对/etc/passwd文件进行排序，相同的行只显示一次
```

### uniq 命令
uniq 命令用来删除文件中重复的行。

-c：显示每行重复出现的次数
-u：只显示唯一的行


```shell
uniq /etc/passwd #删除/etc/passwd文件中重复的行

uniq -c /etc/passwd #显示/etc/passwd文件中每行重复出现的次数

uniq -u /etc/passwd #只显示/etc/passwd文件中唯一的行

```

### diff 命令
diff 命令用来比较两个文件的内容差异。

-i：忽略大小写
-w：忽略空格和制表符的不同
-b：忽略空格的不同

```shell
diff /etc/passwd /etc/shadow #比较/etc/passwd和/etc/shadow文件的内容差异

diff -i /etc/passwd /etc/shadow #比较/etc/passwd和/etc/shadow文件的内容差异，忽略大小写


```
## 文件属性命令

> -rw-rw-r-- 1 gopher gopher 1519 Jun 24 19:21 main.c
> 

### chmod命令
chmod命令用来修改文件或目录的权限。
  >rw-rw-r--

>通过八进制数值方式修改权限
> 
> r : 4
> 
> w：2 
> 
> x：1
> 
> -：无权限0
> 
> rw-rw-r--对应权限的八进制值是：0664
> 
> chmod 0777 main.c #修改main.c的权限为rwxrwxrwx


+:添加权限

-:去权限

r:读权限

w:写权限

x:执行权限

u：仅修改文件或目录的用户权限

g：仅修改文件或目录的组权限

o：仅修改文件或目录的其他用户权限

a+x：添加文件所有用户都有执行权限

```shell
chmod 777 file #将file文件权限修改为777


chmod u=rwx,g=rw,o=r file #将file文件权限修改为所有用户都有读写执行权限，组用户有读写权限，其他用户有只读权限

chmod u+x,g-x,o=r file #将file文件权限修改为所有用户都有执行权限，组用户没有执行权限，其他用户有只读权限

chmod u=rwx,g=rw,o=r dir #将dir目录权限修改为所有用户都有读写执行权限，组用户有读写权限，其他用户有只读权限

```

### chown命令
chown命令用来修改文件或目录的拥有者和群组。

-R：递归修改文件或目录的拥有者和群组

```shell
chown gopher file #将file文件拥有者修改为gopher

chown gopher:root file #将file文件拥有者和群组修改为gopher和root

chown -R gopher dir #将dir目录拥有者和群组修改为gopher

```

### chgrp命令
chgrp命令用来修改文件或目录的群组。

-R：递归修改文件或目录的群组

```shell
chgrp root file #将file文件群组修改为root

chgrp -R root dir #将dir目录群组修改为root

```

### ln命令
ln命令用来创建链接文件或目录。
#### 硬链接
ln 源文件 硬链接文件名
-f：强制创建

硬链接的特点

硬链接文件被创建硬链接数会+1
删除源文件后，硬链接文件依然可以使用
硬链接文件和源文件的inode号是相同的，说明两者占用同一块硬盘空间
当硬链接数减为0的时候文件才从文件系统上被移除掉了
硬链接只能链接文件，不能链接目录
```shell
ln addr.txt www.txt #创建硬链接，名为www.txt，指向addr.txt

``` 

#### 软链接
ln -s 源文件 软链接文件名
-s：创建软链接
-f：强制创建

软链接的特点

软链接类似于windows上的快捷方式
软链接可以链接文件也可以链接目录
软链接文件的类型是l
当删除源文件后链接就断开了，当源文件恢复了软链接文件又可以使用了
当创建软链接后硬链接数是不会增加的
```shell
ln -s addr.txt www.txt #创建软链接，名为www.txt，指向addr.txt

``` 



