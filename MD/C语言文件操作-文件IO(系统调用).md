
<!-- TOC -->
* [文件IO (系统调用)](#文件io-系统调用)
  * [文件描述符](#文件描述符)
  * [open函数](#open函数)
  * [read函数](#read函数)
  * [write函数](#write函数)
  * [lseek函数](#lseek函数)
  * [close函数](#close函数)
  * [dup函数](#dup函数)
  * [dup2函数](#dup2函数)
* [stat函数](#stat函数)
* [getpwuid函数](#getpwuid函数)
* [getgrgid函数](#getgrgid函数)
  * [实例](#实例)
* [目录操作](#目录操作)
  * [opendir函数](#opendir函数)
  * [readdir函数](#readdir函数)
  * [rewinddir函数](#rewinddir函数)
  * [closedir函数](#closedir函数)
  * [实例](#实例-1)
<!-- TOC -->
# 文件IO (系统调用)
文件IO就是系统调用，用户空间进入内核空间的过程就是系统调用。
系统调用没有缓冲机制，效率较低，可移植性也相对较差，实时性高。

## 文件描述符
> 文件描述符是使用open函数打开文件时的返回值
> 
> 对文件的读写操作，就是通过文件描述符来完成的。
> 
> 文件描述符是一个整数，在一个程序中文件描述符的范围0-1023共计1024个，
> 
> 使用   uilmit -a   可以查看一个程序中可以打开的文件的个数限制
> 
> (open files 后面对应的就是 这个值也可以使用命令 ulimit -n 2048来修改 但一般都是用默认值)
> 
> 在一个程序启动的过程中，默认就会打开三个描述符(0 1 2)，
> 
> 分别对应标准输入、标准输出、标准错误。
> 
> 其他文件描述符需要通过open函数来打开文件，并获得文件描述符。
> 
> 文件描述符依次递增,文件描述符遵循复用原则,文件描述符关闭后,这个符号就空闲了,可以被其他程序使用.
> 
> 

## open函数
> open函数用来打开文件，并返回文件描述符。
> 

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int open(const char *pathname, int flags, mode_t mode);
```

参数：

- pathname：要打开的文件的路径名
- flags：打开文件的方式，可以是以下值：
  - O_RDONLY：只读方式打开
  - O_WRONLY：只写方式打开
  - O_RDWR：读写方式打开
  - O_CREAT：如果文件不存在，则创建文件
     - 如果指定了这个宏，则第三个参数 mode 必须填
     - 创建文件的权限还得涉及 掩码 umask
     - umask的值 默认为 0002  这个值也可以改的
     - 最终的权限 = (mode & ~umask)
     - 所以 即使给的是 0666 最终的权限也是 0664
  

  - O_APPEND：在文件尾部追加内容
  - O_TRUNC：如果文件存在，清空
  - O_EXCL：如果文件存在，则返回错误,错误码:EEXIST
- mode：文件权限，一般八进制表示;
 

返回值：

- 成功：返回文件描述符
- 失败：返回-1，并设置errno

## read函数
> read函数用来从文件中读取内容。
> 

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

参数：

- fd：文件描述符
- buf：读取到的数据存放的缓冲区
- count：要读取的字节数


返回值：

- 成功：返回实际读取的字节数
- 失败：返回-1，并设置errno

## write函数
> write函数用来向文件中写入内容。
> 
函数原型:
  

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count); 

```
参数:

- fd：文件描述符
- buf：要写入的数据存放的缓冲区
- count：要写入的字节数

返回值:

- 成功：返回实际写入的字节数
- 失败：返回-1，并设置errno

## lseek函数
> lseek函数用来移动文件读写指针的位置。
> 

```c
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

参数：

- fd：文件描述符
- offset：相对于 whence 的偏移量
- whence：
  - SEEK_SET：相对于文件开始位置
  - SEEK_CUR：相对于当前位置
  - SEEK_END：相对于文件结束位置

返回值：

- 成功：返回新的文件位置
- 失败：返回-1，并设置errno

## close函数
> close函数用来关闭文件。
> 

```c
#include <unistd.h>

int close(int fd);
```


参数：

- fd：文件描述符

返回值：

- 成功：返回0
- 失败：返回-1，并设置errno

## dup函数
> dup函数用来复制文件描述符。
> 


```c
#include <unistd.h>


int dup(int oldfd);
```

参数：

- oldfd：被复制的文件描述符

返回值：

- 成功：返回新的文件描述符
- 失败：返回-1，并设置errno

## dup2函数
> dup2函数用来复制文件描述符并修改文件描述符。
> 

```c
#include <unistd.h>

int dup2(int oldfd, int newfd);
```

参数：

- oldfd：被复制的文件描述符
- newfd：新的文件描述符

返回值：

- 成功：返回新的文件描述符
- 失败：返回-1，并设置errno
- 注意：如果newfd已经打开，则先关闭它。


# stat函数
> stat函数用来获取文件属性信息。
>
函数原型:

```c
#include <sys/stat.h>

int stat(const char *pathname, struct stat *buf);
```

参数:

- pathname：文件路径名
- buf：存放文件属性信息的结构体

返回值:

- 成功：返回0
- 失败：返回-1，并设置errno

结构体stat的定义如下:

```c
struct stat {
    dev_t     st_dev;     //磁盘设备号
    ino_t     st_ino;     //inode节点号
    mode_t    st_mode;    //文件类型和权限
               st_mode & S_IFMT(0777) -> 文件权限
               
               获取文件的类型的方式: st_mode & S_IFMT 文件的类型
                    S_IFMT     0170000   获取类型的掩码
                    S_IFSOCK   0140000   套接字文件
                    S_IFLNK    0120000   软链接文件
                    S_IFREG    0100000   普通文件
                    S_IFBLK    0060000   块设备文件
                    S_IFDIR    0040000   目录文件
                    S_IFCHR    0020000   字符设备文件
                    S_IFIFO    0010000   管道文件
               
                例如:判断文件是否是普通文件
                    if((stat.st_mode & S_IFMT) == S_IFREG)
                    或者:
                    if(S_ISREG(stat.st_mode))
               
               
    nlink_t   st_nlink;   //链接数
    uid_t     st_uid;     //所有者用户ID
    gid_t     st_gid;     //所有者组ID
    dev_t     st_rdev;    //设备号(若此对象为设备文件)
    off_t     st_size;    //文件大小(字节数)
    blksize_t st_blksize; //块大小(字节数)
    blkcnt_t  st_blocks;  //块数
    time_t    st_atime;   //最后访问时间
    time_t    st_mtime;   //最后修改时间
    time_t    st_ctime;   //最后状态改变时间
    
    
    #define st_atime st_atim.tv_sec//最后访问时间
    #define st_mtime st_mtim.tv_sec//最后修改时间
    #define st_ctime st_ctim.tv_sec//最后状态改变时间
};
```
> 函数: int lstat(const char *pathname, struct stat *statbuf);
> 
> 可以获取链接的属性




# getpwuid函数
> getpwuid函数用来获取用户信息。
> 
函数原型:

```c
#include <pwd.h>

struct passwd *getpwuid(uid_t uid);
```


参数:

- uid：用户ID

返回值:

- 成功：返回指向passwd结构体的指针
- 失败：返回NULL，并设置errno

passwd结构体的定义如下:

```c
struct passwd {
    char    *pw_name;    //用户名
    char    *pw_passwd;  //密码
    uid_t    pw_uid;     //用户ID
    gid_t    pw_gid;     //组ID
    char    *pw_gecos;   //用户信息
    char    *pw_dir;     //用户主目录
    char    *pw_shell;   //用户登录shell
};
```

# getgrgid函数
> getgrgid函数用来获取组信息。
> 
函数原型:

```c
#include <grp.h>

struct group *getgrgid(gid_t gid);
```


参数:
- gid：组ID

返回值:

- 成功：返回指向group结构体的指针
- 失败：返回NULL，并设置errno

group结构体的定义如下:

```c
struct group {
    char   *gr_name;    //组名
    char   *gr_passwd;  //组密码
    gid_t   gr_gid;     //组ID
    char  **gr_mem;     //组成员列表
};
```

## 实例

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>


int main()
{
    int fd;
    char buf[1024];
    struct passwd *pw;
    struct group *gr;
    struct stat st;

    //打开文件
    fd = open("test.txt", O_RDONLY, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    //读取文件内容
    read(fd, buf, 1024);
    printf("%s\n", buf);

    //关闭文件
    close(fd);

    //获取文件属性
    if (stat("test.txt", &st) == -1) {
        perror("stat");
        exit(1);
    }

    //获取文件所有者信息
    pw = getpwuid(st.st_uid);
    if (pw == NULL) {
        perror("getpwuid");
        exit(1);
    }
    printf("owner: %s\n", pw->pw_name);

    //获取文件所属组信息
    gr = getgrgid(st.st_gid);
    if (gr == NULL) {
        perror("getgrgid");
        exit(1);
    }
    printf("group: %s\n", gr->gr_name);

    return 0;
} 
```

# 目录操作

## opendir函数
> opendir函数用来打开目录。
> 
函数原型: 

```c
#include <dirent.h>

DIR *opendir(const char *name);
```

参数:

- name：目录路径名

返回值:

- 成功：返回指向DIR结构体的指针
- 失败：返回NULL，并设置errno


DIR结构体:
```c
struct dirent {
    ino_t     d_ino;     //inode节点号
    off_t     d_off;     //目录偏移量
    unsigned short d_reclen; //目录项长度
    unsigned char  d_type;  //目录项类型
    char        d_name[NAME_MAX+1]; //目录项名
};
```






## readdir函数
> readdir函数用来读取目录中的文件信息。
> 
函数原型: 

```c
#include <dirent.h>

struct dirent *readdir(DIR *dirp);
```

参数:

- dirp：指向DIR结构体的指针

返回值:

- 成功：返回指向dirent结构体的指针
- 失败：返回NULL，并设置errno

dirent结构体的定义如下:

```c
struct dirent {
    ino_t     d_ino;     //inode节点号
    off_t     d_off;     //目录偏移量
    unsigned short d_reclen; //目录项长度
    unsigned char  d_type;  //目录项类型
    char        d_name[NAME_MAX+1]; //目录项名
};
```

## rewinddir函数
> rewinddir函数用来将目录读写指针指向文件头。
> 
函数原型: 


```c
#include <dirent.h>

void rewinddir(DIR *dirp);
```

参数:

- dirp：指向DIR结构体的指针

返回值:

- 无

## closedir函数
> closedir函数用来关闭目录。
> 
函数原型: 

```c
#include <dirent.h>

int closedir(DIR *dirp);
```

参数:

- dirp：指向DIR结构体的指针

返回值:

- 成功：返回0
- 失败：返回-1，并设置errno

## 实例

```c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>


int main()
{
    DIR *dir;
    struct dirent *dp;
    struct stat st;

    //打开目录
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }

    //读取目录中的文件信息
    while ((dp = readdir(dir)) != NULL) {
        printf("%s\n", dp->d_name);

        //获取文件属性
        if (lstat(dp->d_name, &st) == -1) {
            perror("lstat");
            exit(1);
        }

        //判断文件类型
        if (S_ISDIR(st.st_mode)) {
            printf("d");
        } else if (S_ISREG(st.st_mode)) {
            printf("-");
        } else if (S_ISLNK(st.st_mode)) {
            printf("l");
        } else if (S_ISFIFO(st.st_mode)) {
            printf("p");
        } else if (S_ISSOCK(st.st_mode)) {
            printf("s");
        } else {
            printf("?");
        }

        //获取文件所有者信息
        printf(" %d/%d ", st.st_uid, st.st_gid);

        //获取文件大小
        printf("%ld ", st.st_size);

        //获取文件修改时间
        printf("%s ", ctime(&st.st_mtime));
    }

    //关闭目录
    closedir(dir);

    return 0;
} 
```