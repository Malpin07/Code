#include "cmd_cp.h"
#include "cmd_ls.h"
#include "cmd_handle.h"
#include <stdio.h>
#include <string.h>


#define SZ_CMD 64
int main(){

    char command[SZ_CMD]={0};//存储命令缓冲区


    for (;;){
        printf("TinyShell >");
        //读取命令
        //stdin是标准输入，从键盘输入 类似的还有stdout、stderr
        //stdout 是标准输出，显示输出
        //stderr 也是标准输出，但是用于显示错误信息
        fgets(command,SZ_CMD,stdin);
        //从标准输入读取命令，存入command缓冲区，直到遇到换行符'\n'
        //"ls -l" ==>"ls -l\n",要去掉换行符
        //strlen函数计算字符串的长度，返回字符串的长度，不包括'\0'
        command[strlen(command)-1]='\0';//去掉换行符'\n' ,使命令以'\0'结尾

        //判断命令是否为quit
        if(strncmp(command,"quit",4)==0){
            printf("退出程序...\n");
            break;
        }

        //cmd_handle函数处理命令
        cmd_execute(command);



    }

    return 0;
}