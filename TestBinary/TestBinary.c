#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//二进制显示
void bin32bdis(int data)
{
    int i=32;
    while(i--)     //32---1
    {
        if(data & (1<<i))   //31--0
            printf("1");
        else
            printf("0");
        if(i%4==0)
        {
            if(i%8==0)
                printf(" ");
            else
                printf("-");
        }
    }
    putchar(10);
}


//循环移位
void circleMove(unsigned  int *pa,int n){
    n%=32;//取余
    printf("%d\n",n);

    if(n>0){
        *pa=  (*pa<<n)  |   (*pa  >> (sizeof (*pa)*8-n));//左移
    } else{
        *pa=  ( *pa>>(-n) )  |   (*pa  << ( sizeof (*pa)*8-(-n) ) );//右移
    }
}


//交换两个变量的值 a+b=c
void Swap(char *a,char *b){
    *a= *a ^ *b;
    *b= *b ^ *a;
    *a= *b ^ *a;
}

//加密普通
#if 0
//加密(普通)
void encode(char *data,char* key){
    int len=strlen(data);
    int n=strlen(key);
    int j=0;
    for(int i=0;i<len;i++){
        if(data[i] == key[j]){
            j++;
        }else{
            data[i]=data[i]^key[j++];
            if(j==n)
                j=0;
        }
    }
}
//解密(普通)
void decode(char *data,char* key){
    int len=strlen(data);
    int n=strlen(key);
    int j=0;
    for(int i=0;i<len;i++){
        if(data[i] == key[j]){
            j++;
        }else{
            data[i]=data[i]^key[j++];
            if(j==n)
                j=0;
        }
    }
}
#endif


//加密二进制文件

void encode(char *buf,int n){
    for(int i=0;i<n;i++) {
        unsigned char ch=buf[i];//取出一个字节
        buf[i]=  (ch<<1)  |  (ch>>7);//左移
    }
}
void decode(char *buf,int n){
    for(int i=0;i<n;i++) {
        unsigned char ch=buf[i];//取出一个字节
        buf[i]=   (ch<<1)  |  (ch>>7);//右移
    }

}
int main() {
    FILE *pf1=fopen("02.jpeg","rb+");//rb+ 以读写方式打开文件
    if(pf1==NULL){//判断文件是否打开成功
        printf("open file failed\n");
        exit(-1);
    }

    FILE *pf2=fopen("03.jpeg","wb+");//wb+ 以读写方式打开文件
    if(pf2==NULL){//判断文件是否打开成功
        printf("open file failed\n");
        exit(-1);
    }

    char buf[1024];
    int n;
    //读文件
    //fread(buf,1,1024,pf1);每次读1024字节 直到读完  n=1024 >0 循环
    while((n=fread(buf,1,1024,pf1))>0){
        decode(buf,n);
        fwrite(buf,1,n,pf2);//写文件
    }
    fclose(pf1);
    fclose(pf2);
    return 0;
}

int main1() {
//    int a = 3;
//    int b=11;
//    //& 按位与运算
//    //跟1按位与运算，结果不变，跟0按位与运算，结果为0,在某些位保持不变的情况下,某些清零
//    bin32bdis(a);  //0000-0000 0000-0000 0000-0000 0000-0011
//    bin32bdis(b);  //0000-0000 0000-0000 0000-0000 0000-1011
//    bin32bdis(a&b);//0000-0000 0000-0000 0000-0000 0000-0011


    int c=3;
    int d=9;
    //| 按位或运算
    //跟1按位或运算，变1，跟0按位或运算，不变 在某些位保持不变的情况下,某些置一
    //bin32bdis(c);  //0000-0000 0000-0000 0000-0000 0000-0011
    //bin32bdis(d);  //0000-0000 0000-0000 0000-0000 0000-1001
    //bin32bdis(c|d);//0000-0000 0000-0000 0000-0000 0000-1011

    int e=3;
    //~ 按位取反运算
    //bin32bdis(e);   //0000-0000 0000-0000 0000-0000 0000-0011
    //bin32bdis(~e);  //1111-1111 1111-1111 1111-1111 1111-1100

    int f=3;
    int g=9;
    //^ 按位异或运算
    //跟1按位异或运算 取反,跟0按位异或运算,不变  相同为0,不同为1
    //某些位保持不变的情况下,某些位取反
    //bin32bdis(f);  //0000-0000 0000-0000 0000-0000 0000-0011
    //bin32bdis(g);  //0000-0000 0000-0000 0000-0000 0000-1001
    //bin32bdis(f^g);//0000-0000 0000-0000 0000-0000 0000-1010

    int k=9;
//    bin32bdis(k);
//    circleMove(&k,5);
//    bin32bdis(k);

    int x=10,y=20;
    char z='a';
    char t='b';
//    Swap(&x,&y);
//    Swap(&z,&t);
//    printf("%d %d\n",x,y);
//    printf("%c %c\n",z,t);


//    char str[]="hello world";
//    char key[]="ooo";
//    encode(str,key);
//    printf("%s\n",str);
//    decode(str,key);
//    printf("%s\n",str);
    return 0;
}


