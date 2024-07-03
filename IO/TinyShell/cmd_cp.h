#ifndef cmd_cp
#define cmd_cp
#include "cmd_handle.h"
#define SZ_PATH 256
enum file_type{
    FT_DIR=0,//目录
    FT_FILE=1,//文件
    FT_ERR=2,//错误
    FT_UNK=3//未知文件类型
};

typedef struct cp_file_info{
    enum file_type src_type;//源文件类型
    char src_path[SZ_PATH];//源文件路径
    char dst_path[SZ_PATH];//目标文件路径
}cp_file_info_t;

//cp命令入口
int cmd_cp_execute(cmd_t *pcmd);
int cmd_cp_parse_path(cp_file_info_t *fileInfo,cmd_t *pcmd);
enum file_type get_file_type(const char *path);
int cmd_cp_parse_type(cp_file_info_t *fileInfo);
#endif