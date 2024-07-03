
<!-- TOC -->
* [用户管理命令](#用户管理命令)
  * [adduser命令](#adduser命令)
  * [addgroup命令](#addgroup命令)
  * [usermod命令](#usermod命令)
  * [userdel命令](#userdel命令)
  * [groupdel命令](#groupdel命令)
  * [passwd命令](#passwd命令)
  * [su命令](#su命令)
  * [id命令](#id命令)
  * [whoami命令](#whoami命令)
  * [groups命令](#groups命令)
  * [gpasswd命令](#gpasswd命令)
  * [chage命令](#chage命令)
  * [chsh命令](#chsh命令)
* [关机命令](#关机命令)
  * [重启命令](#重启命令)
* [重启](#重启)
* [注销](#注销)
* [磁盘管理命令](#磁盘管理命令)
  * [df命令](#df命令)
  * [du命令](#du命令)
  * [fdisk命令](#fdisk命令)
  * [mkfs命令](#mkfs命令)
  * [mount命令](#mount命令)
  * [umount命令](#umount命令)
* [网络管理命令](#网络管理命令)
  * [ifconfig命令](#ifconfig命令)
  * [ip命令](#ip命令)
  * [netstat命令](#netstat命令)
  * [ping命令](#ping命令)
  * [wget命令](#wget命令)
  * [curl命令](#curl命令)
  * [ssh命令](#ssh命令)
  * [scp命令](#scp命令)
  * [ssh-keygen命令](#ssh-keygen命令)
  * [ssh-copy-id命令](#ssh-copy-id命令)
<!-- TOC -->
# 用户管理命令

## adduser命令
添加用户命令
sudo adduser lei # 添加用户lei
```shell
sudo adduser lei
[sudo] linux 的密码： 
正在添加用户"lei"...
正在添加新组"lei" (1001)...
正在添加新用户"lei" (1001) 到组"lei"...
创建主目录"/home/lei"...
正在从"/etc/skel"复制文件...
新的 密码： 
重新输入新的 密码： 
passwd：已成功更新密码
正在改变 lei 的用户信息
请输入新值，或直接敲回车键以使用默认值
 全名 []: 
 房间号码 []: 
 工作电话 []: 
 家庭电话 []: 
 其它 []: 
这些信息是否正确？ [Y/n] y
```

## addgroup命令
添加组命令
sudo addgroup 组名 # 添加组
```shell
sudo addgroup lei
```

## usermod命令
修改用户信息命令
sudo usermod -l 新用户名 用户名 # 修改用户名
```shell
sudo usermod -l lei_new lei
```

## userdel命令
删除用户命令
sudo userdel 用户名 # 删除用户
```shell
sudo userdel lei
```


## groupdel命令
删除组命令
sudo groupdel 组名 # 删除组
```shell
sudo groupdel lei
```

## passwd命令
修改用户密码命令
sudo passwd 用户名 # 修改密码
```shell
sudo passwd lei
```

## su命令
切换用户命令
su - 用户名 # 切换到用户名的用户
```shell
su  lei
```

## id命令
查看用户信息命令
id 用户名 # 查看用户名的用户信息
```shell
id lei
```

## whoami命令
查看当前用户命令
whoami # 查看当前用户
```shell
whoami
```

## groups命令

查看用户所在组命令

groups 用户名 # 查看用户名的用户所在组
```shell
groups lei
```

## gpasswd命令
管理用户组命令
gpasswd -a 用户名 组名 # 将用户加入到组
```shell
gpasswd -a lei lei_group
```

gpasswd -d 用户名 组名 # 将用户从组中删除
```shell
gpasswd -d lei lei_group
```

gpasswd -A 用户名 组名 # 将用户添加到组，并将用户设为组管理员
```shell
gpasswd -A lei lei_group
```


## chage命令
修改用户密码有效期命令
chage -m 0 用户名 # 设定密码永不过期
```shell
chage -m 0 lei
```


## chsh命令
修改用户默认shell命令

chsh -s /bin/bash 用户名 # 修改用户默认shell为bash
```shell
chsh -s /bin/bash lei
```


# 关机命令

shutdown命令
shutdown -h now # 立即关机
```shell
    
shutdown -h now

sudo shutdown -h 15:20 :在15:20分关机

sudo shutdown -h +60:在60分钟后关机

sudo shutdown -c:取消当前关机命令
```

## 重启命令
```shell
sudo shutdown -r 15:20 :在15:20分重启

sudo shutdown -r +60:在60分钟后重启

shudo shutdown -r now:立即重启
```
# 重启

reboot命令

reboot # 立即重启
```shell
sudo reboot
```
# 注销

logout命令

logout # 注销当前用户
```shell
logout
```

# 磁盘管理命令

## df命令
查看磁盘使用情况命令
df -h # 查看磁盘使用情况
```shell
df -h
```

## du命令
查看目录或文件大小命令
du -sh 文件或目录 # 查看文件或目录的大小
```shell
du -sh /home/lei
```

## fdisk命令
磁盘分区命令
fdisk /dev/分区 # 进入分区管理界面
```shell
fdisk /dev/sda # 进入sda分区管理界面
```

## mkfs命令
格式化磁盘命令
mkfs -t 文件系统类型 /dev/分区 # 格式化分区为文件系统类型
```shell
mkfs -t ext4 /dev/sda1 # 格式化sda1分区为ext4格式
```

## mount命令
挂载磁盘命令
mount /dev/分区 挂载点 # 挂载分区到挂载点
```shell
mount /dev/sda1 /mnt # 挂载sda1分区到/mnt目录
```


## umount命令
卸载磁盘命令
umount 挂载点 # 卸载挂载点
```shell
umount /mnt # 卸载/mnt目录
```


# 网络管理命令

## ifconfig命令
查看网络接口信息命令
ifconfig # 查看网络接口信息


## ip命令
查看网络接口信息命令
ip addr show # 查看网络接口信息

ip route show # 查看路由信息


## netstat命令
查看网络连接信息命令
netstat -an # 查看网络连接信息


## ping命令
测试网络连通性命令
ping 主机名或IP地址 # 测试主机名或IP地址的网络连通性
```shell
ping www.baidu.com
```


## wget命令
下载文件命令
wget 下载地址 # 下载文件
```shell
wget http://www.example.com/file.zip
```


## curl命令
下载文件命令
curl 下载地址 # 下载文件
```shell
curl http://www.example.com/file.zip
```


## ssh命令
远程登录命令
ssh 用户名@主机名 # 远程登录主机
```shell
ssh lei@192.168.1.100
```


## scp命令
远程拷贝文件命令
scp 源文件 目标用户名@主机名:目标路径 # 远程拷贝文件
```shell
scp /home/lei/file.txt lei@192.168.1.100:/home/
```


## ssh-keygen命令
创建SSH密钥对命令
ssh-keygen -t 密钥类型 # 创建SSH密钥对
```shell
ssh-keygen -t rsa
```


## ssh-copy-id命令
将公钥拷贝到远程主机命令
ssh-copy-id -i 私钥文件 用户名@主机名 # 将公钥拷贝到远程主机
```shell
ssh-copy-id -i ~/.ssh/id_rsa.pub lei@192.168.1.100
```








