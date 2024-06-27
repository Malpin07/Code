#ifndef cmd_handle
#define cmd_handle
#include <stdio.h>
#include <string.h>


#define SZ_NAME 8
#define SZ_ARG 32
#define SZ_COUNT 2

//定义命令结构体
typedef struct command {
    char cmd_name[SZ_NAME];//命令名称
    char cmd_arg_list[SZ_COUNT][SZ_ARG];//命令参数列表
    int cmd_arg_count;//命令参数个数
} cmd_t;

//初始化结构体
void init_command(cmd_t *pcmd);

//打印
void print_command(cmd_t *pcmd);

//执行命令的入口
extern int cmd_execute(char *cmd);

//分割命令字符串
int cmd_parse(cmd_t *pcmd,char *cmd_str);

//命令分发
int cmd_dispatch(cmd_t *pcmd);


#endif