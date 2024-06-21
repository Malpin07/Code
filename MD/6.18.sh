#判断用户家目录下是否存在file-dir和dir-dir目录，如果不存在就创建，如果存在就清空
#向脚本输入任意一个路径，将这个路径下的文件拷贝到file-dir下将目录拷贝到dir-dir下
#!/bin/bash
cd ~
if [ ! -d file-dir ]
then
  mkdir file-dir
else
  rm -rf file-dir/*
fi

if [ ! -d  dir-dir ]
then
  mkdir dir-dir
else
  rm -rf dir-dir/*
fi

read -p "输入路径:" pat

cp -r $pat/* file-dir/
cd ~/file-dir/
find . -type f -exec mv {} ~/dir-dir \;

echo ls -R file-dir | grep / |wc -l
echo ls dir-dir/|wc -l