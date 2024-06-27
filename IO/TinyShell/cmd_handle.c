#include "cmd_handle.h"
#include "cmd_cp.h"
#include "cmd_ls.h"

//#define DEBUG_CMD_HANDLE 1
// int cmd_execute(char *cmd){
//#if DEBUG_CMD_HANDLE
//     printf("cmd_execute: %s\n", cmd);
//#endif
//     return 0;
//}

 int cmd_execute(char *cmd){
     cmd_t command;
     int i;
     if(cmd == NULL){
         return -1;
     }
     //初始化命令结构体
     init_command(&command);
     //分割命令字符串
     cmd_parse(&command,cmd);
     //命令分发
     cmd_dispatch(&command);
     //打印命令结构体
     print_command(&command);
     return 0;
}


//初始化
void init_command(cmd_t *pcmd){
    int i;
    memset(pcmd->cmd_name,0,SZ_NAME);
    for (int j = 0; j < SZ_COUNT; ++j) {
        memset(pcmd->cmd_arg_list[j],0,SZ_ARG);
    }
    pcmd->cmd_arg_count = 0;
}

//分割命令字符串
int cmd_parse(cmd_t *pcmd,char *cmd_str){
    if(cmd_str == NULL|| pcmd == NULL){
        return -1;
    }
    char* p_name = NULL;
    char* p_arg = NULL;

    //分割命令名和参数 strtok()函数用于分割字符串
    //第一个参数为要分割的字符串，第二个参数为分隔符
    //返回值是分割后的第一个字符串的指针
    p_name= strtok(cmd_str," ");
    //将命令名拷贝到命令结构体
    strcpy(pcmd->cmd_name,p_name);


    int i = 0;
    while(1){
        //获取下一个参数
        p_arg = strtok(NULL," ");
        //如果没有参数，则退出循环
        if(p_arg == NULL){
            break;
        }
        //将参数拷贝到命令结构体
        strcpy(pcmd->cmd_arg_list[i++],p_arg);
        //统计参数个数
        pcmd->cmd_arg_count=i;
    }

    return 0;
}

//命令分发
int cmd_dispatch(cmd_t *pcmd){
    if(pcmd == NULL){
        return -1;
    }

    if(strcmp(pcmd->cmd_name,"ls")==0){
        printf("ls command\n");

    }else if(strcmp(pcmd->cmd_name,"cp")==0){
        printf("cp command\n");
        cmd_cp_execute(pcmd);
    }

    return 0;
}


void print_command(cmd_t *pcmd){
    printf("===========\n");
    printf("cmd_name: %s\n", pcmd->cmd_name);
    printf("cmd_arg_count: %d\n", pcmd->cmd_arg_count);
    for (int i = 0; i < pcmd->cmd_arg_count; ++i) {
        printf("cmd_arg_list[%d]: %s\n", i, pcmd->cmd_arg_list[i]);
    }
}