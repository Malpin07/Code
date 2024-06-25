#1. 编写一个shell脚本完成如下功能 ：
#
#1.在家目录下创建文件夹filer
#
#2.遍历当前文件夹下的文件，如果是普通文件则放入创建的filer中
#
#3.打印出放入filer文件夹中的文件数目

#!/bin/bash

#创建文件夹filer
mkdir filer

#遍历当前文件夹下的文件
for file in *
do
    #如果是普通文件则放入创建的filer中
    if [ -f $file ]
    then
        mv $file filer
    fi
done

#打印出放入filer文件夹中的文件数目
