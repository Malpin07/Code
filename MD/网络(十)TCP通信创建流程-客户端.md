# TCP通信创建流程

## 1. 客户端创建TCP连接
```c
在整个流程中, 主要涉及以下⼏个接⼝
            socket() : 创建套接字, 使⽤的套接字类型为流式套接字
            connect() : 连接服务器
            send() : 数据发送
            recv() : 数据接收
```

# 创建套接字

首先，我们需要创建套接字，套接字是通信的基础。我们可以通过 socket() 函数来创建套接字。
```c
int socket(int domain, int type, int protocol);
参数:
    @domain
            地址族
            AF_UNIX, AF_LOCAL  本地通信,数据不仅过网卡
            AF_INET         IPV4 ineter⽹通信  
            AF_INET6        IPV6 ineter⽹通信
            AF_PACKET       网卡上的数据包通信
            ....
            
            
    @ type
            使⽤协议类型
                SOCK_STREAM 流式套接字（TCP）
                SOCK_DGRAM 报⽂套接字（UDP）
                SOCK_RAW原始套接字: （IP,ICMP）
                ......
                
    @protocol
            协议编号
            0 : 让系统⾃动识别
            IPPROTO_TCP : TCP协议
            IPPROTO_UDP : UDP协议


返回值:
        成功返回得到的⽂件描述符。当前可使用的最小描述符
        失败返回 -1
```

# 连接服务器

创建套接字之后，我们需要连接服务器。连接服务器需要调用 connect() 函数。
```c
发起对套接字的连接 (基于⾯向连接的协议)
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
参数:
    @sockfd
            套接字描述符
            
    @addr   连接的套接字的地址结构对象的地址 (⼀般为服务器)
            服务器地址
                struct sockaddr {
                    unsigned short sa_family; // 地址族 对应socket()中的domain
                    char sa_data[14]; // 地址数据 ip地址端口信息
                };
                        
                struct sockaddr_in { 
                    short int sin_family; // 地址族 AF_INET
                    unsigned short int sin_port; // 端口号
                    struct in_addr sin_addr;// IP地址
                    unsigned char sin_zero[8]; // 填充字节 为了对齐sockaddr
                };
                
                struct in_addr {
                    uint32_t       s_addr; // IP地址
                };
            
    @addrlen
            地址长度


返回值:
        成功返回0
        失败返回-1 并设置 errno
```

# 数据发送

连接服务器之后，我们就可以向服务器发送数据。发送数据需要调用 send() 函数。
```c
基于套接字（建⽴连接）发送数据
int send(int sockfd, const void *buf, size_t len, int flags);
参数:
    @sockfd
            套接字描述符
            
    @buf    发送的数据
            
    @len    发送数据的长度
            
    @flags  发送标志
函数返回值:
    成功返回发送的字节数
    失败返回-1,并设置errno
```            

# 数据接收

服务器向客户端发送数据之后，客户端就可以接收数据。接收数据需要调用 recv() 函数。
```c
接收套接字的数据 (基于⾯向连接的协议)
int recv(int sockfd, void *buf, size_t len, int flags);
参数:
    @sockfd
            套接字描述符
            
    @buf    接收的数据
            
    @len    接收数据的长度
            
    @flags  接收标志
函数返回值:
    成功返回接收的字节数
    失败返回-1,并设置errno
``` 

# 完整流程

```c
//todo tcp客户端,循环发送数据,接收回传数据
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define N 128
//初始化socket
int  init_socket(char *ip,char *port){

    int init_socket_fd= socket(AF_INET,SOCK_STREAM,0);
    if (init_socket_fd==-1){
        printf("init_socket err");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    socklen_t len=sizeof(server_addr);
    bzero(&server_addr,len);
    server_addr.sin_family=AF_INET;
    inet_aton(ip,&server_addr.sin_addr);
    server_addr.sin_port= htons(atoi(port));

    //连接
    int ret= connect(init_socket_fd,(struct sockaddr*)&server_addr,len);
    if (ret==-1){
        printf("connect error,连接失败\n");
        exit(EXIT_FAILURE);
    }


return init_socket_fd;
}

//客户端接收数据
int Client_Receive_data(int socket_fd){
    char receive_msg[N];
    bzero(receive_msg,N);
    int recv_len= recv(socket_fd, receive_msg,sizeof(receive_msg),0);
    if (recv_len == -1) {
        printf("recv error\n");
        exit(EXIT_FAILURE);
    }

    receive_msg[recv_len] = '\0';
    printf("收到客户端数据:[%s]\n",receive_msg);
}


//客户端发送数据
int  Client_Send_data(int socket_fd){
    char msg[N];
    
    while (1){
    bzero(&msg, sizeof (msg));
    printf("请输入:\n");
    fgets(msg, sizeof(msg),stdin);
    msg[strlen(msg)-1]='\0';
    
    printf("发送数据%s\n",msg);
    
    int  Send_data_len= send(socket_fd,&msg, strlen(msg),0);
        if (Send_data_len==-1){
            printf("发送失败 send err\n");
            exit(EXIT_FAILURE);
        }
    printf("发送了%d个字节\n",Send_data_len);
    
    if (strncmp(msg, "exit", 4) == 0) {
        printf("退出通信\n");
        close(socket_fd);
        break;
    }
    break;
    //接收
    Client_Receive_data(socket_fd);
    
    }

    return 0;
}

int main(){
    //初始化连接
    int socket_fd = init_socket("172.17.128.1","8888");
    //发送数据
    Client_Send_data(socket_fd);


    return 0;
}

```

    