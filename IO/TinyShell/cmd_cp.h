#ifndef cmd_cp
#define cmd_cp
#include "cmd_handle.h"

enum file_type{
    FT_DIR=0,//目录
    FT_FILE=1,//文件
    FT_ERR=2,//错误
    FT_UNK=3//未知文件类型
};

typedef struct{
    enum file_type src_type;//源文件类型
    char src_path[SZ_PATH];
}

//cp命令入口
int cmd_cp_execute(cmd_t *pcmd);

#endif