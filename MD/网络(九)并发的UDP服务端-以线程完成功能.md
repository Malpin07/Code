# 网络(九)并发的UDP服务端 以线程完成功能

# 客户端

```c
// todo UDP发送端
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define LOGIN_SUCCESS 1
#define LOGIN_FAIL 0
//?发送数据
//?@param fd 套接字描述符
//?@param addr 目标地址
//?@param addrlen 地址长度
void send_data(int fd, struct sockaddr_in * addr , socklen_t addrlen);

void login(int fd, struct sockaddr_in * addr ,struct sockaddr_in * new_addr , socklen_t new_addrlen);

//命令行参数 ip port
int main(int argc, char *argv[] ){
//    if(argc!= 3){
//        printf("Usage: %s ip port\n", argv[0]);
//        exit(EXIT_FAILURE);
//    }

    //!通过socket函数创建套接字
    //!@param domain 协议族，AF_INET表示IPv4协议族
    //!@param type 套接字类型，SOCK_DGRAM表示UDP套接字
    //!@param protocol 协议，一般为0 让系统⾃动识别
    //!@return 成功返回套接字描述符，失败返回-1
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){    //创建套接字失败
        perror("socket err");
        exit(EXIT_FAILURE);
    }

    //准备接收消息的地址
    /*      struct sockaddr_in {
                short int sin_family; // 地址族 AF_INET
                unsigned short int sin_port; // 端口号
                struct in_addr sin_addr;// IP地址
                unsigned char sin_zero[8]; // 填充字节 为了对齐sockaddr
            };
    */
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8083);//htons函数将主机字节序转换为网络字节序

    //addr.sin_addr.s_addr=inet_addr("192.168.74.1");//inet_addr()将点分十进制IP地址转换为网络字节序IP地址

    //inet_aton()将点分十进制IP地址转换为网络字节序IP地址
    //@param ip 字符串形式的IP地址
    //@param in_addr 结构体变量，用于存储IP地址
    int ret=inet_aton("172.17.140.183", &addr.sin_addr); // 成功返回⾮0,失败返回0
    if(ret == 0){
        perror("inet_aton err");
        exit(EXIT_FAILURE);
    }
    printf("ip == %d\n",addr.sin_addr.s_addr);



    //inet_ntoa()将网络字节序IP地址转换为点分十进制IP地址
    //char *ip=inet_ntoa(addr.sin_addr); // 成功返回⾮0,失败返回0
    //printf("ip == %s\n",ip);

    //获取  和服务端的新建的子进程通信
    struct sockaddr_in new_addr;
    login(fd, &addr, &new_addr, sizeof(new_addr));

    //与新的子进程通信
    send_data(fd, &new_addr, sizeof(new_addr));

    return 0;
}

//!发送数据
//!@param fd 套接字描述符
//!@param addr 目标地址
//!@param addrlen 地址长度
void send_data(int fd, struct sockaddr_in * addr , socklen_t addrlen){

    while (1){
        int n = 0;//返回发送的字节数
        char buf[1024] = {0};
        printf("请输入要发送的消息：");
        fgets(buf, 1024, stdin);


        //!发送数据
        //!@param fd 套接字描述符
        //!@param buf 发送缓冲区
        //!@param len 发送缓冲区长度
        //!@param flags 发送标志  0 表示默认操作
        //!@param addr 目标地址
        //!@param addrlen 地址长度
        //!@return 成功返回发送的字节数，失败返回-1
        n= sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)addr, addrlen);
        if(n == -1){
            perror("sendto err");
            exit(EXIT_FAILURE);
        }

        if(strncmp(buf, "exit",4) == 0){
            break;
        }
    }

}


void login(int fd, struct sockaddr_in * addr ,struct sockaddr_in * new_addr , socklen_t addrlen){
    char login_status=LITTLE_ENDIAN;

    while (1){
        int n = 0;//返回发送的字节数
        char buf[1024] = {0};
        printf("请输入要发送的消息：");
        fgets(buf, 1024, stdin);



        n= sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)addr, addrlen);
        if(n == -1){
            perror("sendto err");
            exit(EXIT_FAILURE);
        }

        //接收消息服务器的响应
        n= recvfrom(fd, &login_status, sizeof(login_status), 0, (struct sockaddr *)new_addr, &addrlen);
        if(n == -1){
            perror("recvfrom err");
            exit(EXIT_FAILURE);
        }
        if(login_status == LOGIN_SUCCESS){
            printf("登录成功\n");
            printf("新的子进程的地址为：%s:%d\n",inet_ntoa(new_addr->sin_addr),ntohs(new_addr->sin_port));
            break;
        }else if(login_status == LOGIN_FAIL){
            printf("登录失败\n");
            continue;
        }


        if(strncmp(buf, "exit",4) == 0){
            break;
        }
    }


}

```


# 服务端

服务端创建主线程,接收客户端的请求,创建新的子线程,
子线程完成后续交互,子线程中创建新的套接字,返回给客户端,后续交互将在新的套接字中完成.
将子线程分离,线程运行结束将由系统回收资源
```c
// todo UDP服务器端程序
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#define LOGIN_SUCCESS 1
#define LOGIN_FAIL 0




//接收数据
void recv_data(int sockfd);
void *pthread_todo(void *arg);

//初始化套接字
int  init_socket(char *ip, char* port);

int TheLogin(char *ip, char * port);

//定义结构体为子线程传递参数
struct thread_arg {
    char *ip;
    unsigned char login_status;
    struct sockaddr_in thread_addr;//客户端的地址
}thread_arg;

int main(int argc, char *argv[]){


    //验证
    int new_sockfd = TheLogin("172.17.140.183", "8083");
    //接收数据
    //由子线程完成

    //关闭套接字
    close(new_sockfd);
    return 0;
}

//接收数据
void recv_data(int sockfd) {
    struct sockaddr_in client_addr;//客户端的地址
    int client_addr_len = sizeof(client_addr);

    while(1) {
        char recv_buf[1024]={0};

        //接收数据
        //*@param sockfd 套接字描述符
        //*@param buf 接收缓冲区
        //*@param len 接收缓冲区长度
        //*@param flags 接收标志
        //*@param src_addr 发送方地址
        //*@param addrlen 发送方地址长度
        //*@return 成功返回接收到的字节数，失败返回-1
        int ret = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *) &client_addr, &client_addr_len);
        if (ret == -1) {
            perror("recvfrom err");
            exit(EXIT_FAILURE);
        }
        //打印接收到的信息
        char *ip_str = inet_ntoa(client_addr.sin_addr);//将网络字节序IP地址转换为点分十进制IP地址
        int port = ntohs(client_addr.sin_port); //将网络字节序端口号转换为主机字节序端口号
        printf("接收到来自%s:%d的数据：%s\n", ip_str, port, recv_buf);

        if(strncmp(recv_buf, "exit", 4) == 0){
            //退出程序
            break;
        }
    }
    close(sockfd);
    return;
}


int  init_socket(char *ip,char *port){
    //!通过socket函数创建套接字
    //!@param domain 协议族，AF_INET表示IPv4协议族
    //!@param type 套接字类型，SOCK_DGRAM表示UDP套接字
    //!@param protocol 协议，一般为0 让系统⾃动识别
    //!@return 成功返回套接字描述符，失败返回-1
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){    //创建套接字失败
        perror("socket err");
        exit(EXIT_FAILURE);
    }

    //准备服务器地址
    /*      struct sockaddr_in {
                short int sin_family; // 地址族 AF_INET
                unsigned short int sin_port; // 端口号
                struct in_addr sin_addr;// IP地址
                unsigned char sin_zero[8]; // 填充字节 为了对齐sockaddr
            };
    */
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(port));//htons函数将主机字节序转换为网络字节序

    //inet_aton()将点分十进制IP地址转换为网络字节序IP地址
    //*@param ip 字符串形式的IP地址
    //*@param in_addr 结构体变量，用于存储IP地址
    int ret=inet_aton(ip, &addr.sin_addr); // 成功返回⾮0,失败返回0
    if(ret == 0){
        perror("inet_aton err");
        exit(EXIT_FAILURE);
    }


    //!绑定套接字到服务器地址
    //!@param sockfd 套接字描述符
    //!@param addr 服务器地址
    //!@param addrlen 服务器地址长度
    //!@return 成功返回0，失败返回-1
    int ret2 = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret2 == -1){
        perror("bind err");
        exit(EXIT_FAILURE);
    }


    return fd;
}


int TheLogin(char *ip, char *port){
    unsigned char login_status;
    int new_sockfd;
    //初始化套接字
    int sockfd = init_socket(ip, port);
    //线程创建
    pthread_t recv_thread;


    struct sockaddr_in client_addr;//客户端的地址
    int client_addr_len = sizeof(client_addr);

    while(1) {
        char recv_buf[1024]={0};

        int ret = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *) &client_addr, &client_addr_len);
        if (ret == -1) {
            perror("recvfrom err");
            exit(EXIT_FAILURE);
        }
        //打印接收到的信息
        char *ip_str = inet_ntoa(client_addr.sin_addr);//将网络字节序IP地址转换为点分十进制IP地址
        int port = ntohs(client_addr.sin_port); //将网络字节序端口号转换为主机字节序端口号
        printf("接收到来自%s:%d的数据：%s\n", ip_str, port, recv_buf);

        //登录验证
        //判断是否为登录请求
        login_status = ( strncmp(recv_buf, "login",5)==0 ? LOGIN_SUCCESS: LOGIN_FAIL ) ;
        if(login_status == LOGIN_SUCCESS){
             //使用子线程完成后续交互
             struct thread_arg pack;
             pack.ip = ip;
             pack.login_status = login_status;
             pack.thread_addr = client_addr;
             //创建子线程
             pthread_create(&recv_thread, NULL, pthread_todo, &pack);
             printf("子线程创建成功\n");
        } else{
            //回传失败消息
            sendto(sockfd, &login_status, sizeof(login_status), 0, (struct sockaddr *) &client_addr, client_addr_len);
        }
        //将新建的线程设置为分离状态
        pthread_detach(recv_thread);
        printf("子线程分离成功\n");

    }

}

void *pthread_todo(void *arg){
    //子线程函数
     struct thread_arg *pack = (struct thread_arg*)arg;



    //创建新的套接字文件描述符
    int new_sockfd = init_socket(pack->ip, "0");
    printf("子线程创建新的套接字文件描述符：%d\n", new_sockfd);
    sendto(new_sockfd, &pack->login_status, sizeof(pack->login_status), 0,\
    (struct sockaddr *) &pack->thread_addr, sizeof(pack->thread_addr));

    //接收数据
    recv_data(new_sockfd);

    pthread_exit(NULL);

}
```