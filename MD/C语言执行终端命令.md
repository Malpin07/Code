
# C语言在linux环境下执行终端命令
<!-- TOC -->
* [C语言在linux环境下执行终端命令](#c语言在linux环境下执行终端命令)
  * [1.system()函数](#1system函数)
  * [2.popen()函数](#2popen函数)
  * [3.fork()和exec系列函数](#3fork和exec系列函数)
    * [exec系列函数的语法：](#exec系列函数的语法)
  * [4.system()和exec系列函数的区别](#4system和exec系列函数的区别)
  * [5.总结](#5总结)
<!-- TOC -->
## 1.system()函数

system()函数用来执行一个shell命令，并返回执行结果。

语法：

```c    
    #include <stdlib.h>
    int system(const char *command);
```

1. command：要执行的命令字符串。

2. 函数返回值：如果命令执行成功，则返回0；如果命令执行失败，则返回-1。 
System函数的行为依赖于操作系统和环境。在大多数情况下，System函数会创建一个新的进程来执行指定的命令，然后等待该命令完成，并返回命令的退出状态。如果命令执行成功，System函数通常会返回0。如果命令执行失败，System函数会返回非0值。

如果需要更精细的控制，如命令的输出、错误处理、命令的并行执行等，可能需要使用更复杂的API，如popen或fork/exec系列函数。

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int status = system("echo 'hello word' > test.txt");
    if (status == 0) {
        printf("Command executed successfully\n");
    } else {
        printf("Command failed with status %d\n", status);
    }
    return 0;
}

//将hello word输出到test.txt文件中

```



## 2.popen()函数

popen函数是C语言标准库中的一个功能强大的工具，它允许程序与命令行命令进行交互。具体来说，popen函数用于创建一个管道，并通过这个管道与启动的新进程通信。这个新进程是由popen函数执行的命令行命令生成的子进程。

语法：


```c
#include <stdio.h>
#include <stdlib.h>

FILE *popen(const char *command, const char *type);
```

1. command：要执行的命令字符串。

2. type：指定管道的类型，可以是"r"、"w"或"rw"。"r"表示只读，"w"表示只写，"rw"表示读写。

3. 函数返回值：如果命令执行成功，则返回指向管道的文件指针；如果命令执行失败，则返回NULL。

command参数指定了要执行的命令，而type参数决定了打开的文件模式，可以是"r"（表示读模式）或"w"（表示写模式）。
当type为"r"时，popen函数返回的文件指针连接到命令的标准输出上，即我们可以从这个文件指针读取命令的输出；反之，当type为"w"时，文件指针连接到命令的标准输入上，即我们可以向这个文件指针写入数据，这些数据将作为命令的输入。

popen函数是通过fork一个子进程来执行命令的，而这个子进程是通过调用/bin/sh -c来执行command指定的命令。
这意味着command可以包含多个命令，它们会被当作一个脚本执行。

在使用popen函数后，必须使用pclose函数来关闭由popen函数返回的文件指针。pclose函数不仅关闭了文件指针，还会等待命令执行完毕，并返回shell的终止状态。如果popen函数调用失败，它会返回NULL，并且可以通过检查errno来获取具体的错误信息。

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = popen("ls -l", "r");
    if (fp == NULL) {
        perror("popen");
        exit(1);
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)!= NULL) {
        printf("%s", buffer);
    }
    int status = pclose(fp);
    if (status == -1) {
        perror("pclose");
        exit(1);
    }
    return 0;
}

//列出当前目录的文件信息

```


## 3.fork()和exec系列函数

fork()和exec系列函数是C语言标准库中的另一种执行命令的函数。fork()函数创建一个新的进程，并返回子进程的PID。
exec系列函数用来替换当前进程的执行文件，并执行指定的命令。
fork()函数的语法：

```c
#include <unistd.h>
pid_t fork(void);
```

### exec系列函数的语法：
exec函数里的参数可以分成3个部分, 执行文件部分, 命令参数部分, 环境变量部分。

- 执行文件部分：指定要执行的命令，可以是绝对路径，也可以是相对路径。
- 命令参数部分：以数组的形式传递命令的参数。
- 环境变量部分：以数组的形式传递环境变量。
```c
#include <unistd.h>
int execl(const char *path, const char *arg0,..., (char *)0);
int execle(const char *path, const char *arg0,..., char *const envp[]);
int execlp(const char *file, const char *arg0,..., (char *)0);
int execv(const char *path, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);
int execvp(const char *file, char *const argv[]);
```
这些函数的功能都类似，它们都用来执行指定的命令。

- execl()：以参数列表的方式执行命令，最后一个参数必须是NULL。
- execle()：与execl()类似，但可以指定环境变量。
- execlp()：在PATH环境变量中搜索命令的路径，然后执行。
- execv()：以参数数组的方式执行命令。
- execve()：与execv()类似，但可以指定环境变量。
- execvp()：在PATH环境变量中搜索命令的路径，然后执行。

这些函数的区别在于参数的传递方式。execl系列函数以参数列表的方式传递参数，execv系列函数以参数数组的方式传递参数。


> exec函数会取代执行它的进程,  也就是说, 一旦exec函数执行成功, 它就不会返回了, 进程结束.   但是如果exec函数执行失败, 它会返回失败的信息,  而且进程继续执行后面的代码! 
>

> 通常exec会放在fork() 函数的子进程部分, 来替代子进程执行啦, 执行成功后子程序就会消失,  但是执行失败的话, 必须用exit()函数来让子进程退出!

1. execl()函数：

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int status = execl("/bin/ls", "ls", "-l", NULL);
    if (status == -1) {
        perror("execl");
        exit(1);
    }
    return 0;
}


//列出当前目录的文件信息

```

2. execle()函数：

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *envp[] = {"PATH=/bin", NULL};
    int status = execle("/bin/ls", "ls", "-l", NULL, envp);
    if (status == -1) {
        perror("execle");
        exit(1);
    }
    return 0;
}

//列出当前目录的文件信息, 并指定环境变量

```

3. execlp()函数：

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int status = execlp("ls", "ls", "-l", NULL);
    if (status == -1) {
        perror("execlp");
        exit(1);
    }
    return 0;
}


//列出当前目录的文件信息, 在PATH环境变量中搜索命令的路径

```

4. execv()函数：

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    char *argv[] = {"ls", "-l", NULL};
    int status = execv("/bin/ls", argv);
    if (status == -1) {
        perror("execv");
        exit(1);
    }
    return 0;
}

//列出当前目录的文件信息, 以参数数组的方式传递参数

```

5. execve()函数：

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *argv[] = {"ls", "-l", NULL};
    char *envp[] = {"PATH=/bin", NULL};
    int status = execve("/bin/ls", argv, envp);
    if (status == -1) {
        perror("execve");
        exit(1);
    }
    return 0;
}

//列出当前目录的文件信息, 以参数数组的方式传递参数, 并指定环境变量

```

6. execvp()函数：

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *argv[] = {"ls", "-l", NULL};
    int status = execvp("ls", argv);
    if (status == -1) {
        perror("execvp");
        exit(1);
    }
    return 0;
}



//列出当前目录的文件信息, 在PATH环境变量中搜索命令的路径, 以参数数组的方式传递参数

```

## 4.system()和exec系列函数的区别

system()函数和exec系列函数都可以用来执行命令，但是它们的区别在于：

- system()函数：system()函数是C语言标准库中的函数，它直接调用/bin/sh来执行命令，因此它可以执行任何命令，包括shell脚本。
- exec系列函数：exec系列函数是C语言标准库中的高级函数，它们通过fork()和exec()系列函数来执行命令，因此它们只能执行可执行文件，不能执行shell脚本。

因此，如果需要执行shell脚本，则应该使用system()函数；如果需要执行可执行文件，则应该使用exec系列函数。

## 5.总结

- system()函数：system()函数用来执行一个shell命令，并返回执行结果。
- popen()函数：popen函数是C语言标准库中的一个功能强大的工具，它允许程序与命令行命令进行交互。
- fork()和exec系列函数：fork()和exec系列函数是C语言标准库中的另一种执行命令的函数。fork()函数创建一个新的进程，并返回子进程的PID。exec系列函数用来替换当前进程的执行文件，并执行指定的命令。
- 推荐使用exec系列函数来执行命令，因为它更加灵活，可以指定环境变量。
- 推荐使用popen()函数来执行命令，因为它可以获取命令的输出，并且可以与程序进行交互。
- 推荐使用system()函数来执行shell脚本，因为它可以执行更复杂的脚本。
- 推荐使用exec系列函数来执行可执行文件，因为它可以执行更加精确的控制。


