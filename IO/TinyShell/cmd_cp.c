#include "cmd_cp.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
//cp命令入口
int cmd_cp_execute(cmd_t *pcmd){
    if(pcmd==NULL){
        return -1;
    }

    print_command(pcmd);
    cp_file_info_t  fileInfo;
    int ret= cmd_cp_parse_path(&fileInfo,pcmd);
    if(ret==-1){
        return -1;
    }
    ret= cmd_cp_parse_type(&fileInfo);
    if(ret==-1){
        return -1;

    }

    return 0;
}

int cmd_cp_parse_path(cp_file_info_t *pfileInfo,cmd_t *pcmd){
    if(pcmd==NULL || pfileInfo==NULL){
        return -1;
    }
    strcpy(pfileInfo->src_path,pcmd->cmd_arg_list[0]);
    strcpy(pfileInfo->dst_path,pcmd->cmd_arg_list[1]);



    return 0;
}

int cmd_cp_parse_type(cp_file_info_t *fileInfo){
    enum file_type ftype;
    ftype= get_file_type(fileInfo->src_path);
    if(ftype==FT_ERR){
        return -1;
    } else{
        fileInfo->src_type=ftype;
    }

    return 0;
}

enum file_type get_file_type(const char *path){
    int type=0;
    struct stat statbuf;

    type= stat(path,&statbuf);
    if(type==-1){
        perror("stat():");//打印错误信息
        return FT_ERR;
    }
    if(S_ISDIR(statbuf.st_mode)){//判断是否为目录
        return FT_DIR;
    } else if(S_ISREG(statbuf.st_mode)){//path是否为文件
        return FT_FILE;
    }
    return FT_UNK;//未知类型
}
