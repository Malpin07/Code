#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXROW 10
#define MAXLINE 10
#include "Stack.h"
#include "myList.h"

//定义栈结构
Stack stack;

Point PrePoint[MAXROW][MAXLINE];//记录前一个点

//1 代表墙，2 走过的路，0 代表路
int maze[MAXROW][MAXLINE] =
        {
                1,1,1,1,1,1,1,1,1,1,
                0,0,0,1,1,1,1,1,1,1,
                1,1,0,1,1,1,1,1,1,1,
                1,1,0,0,0,0,1,1,1,1,
                1,1,0,1,1,0,1,1,1,1,
                1,1,0,1,1,0,1,1,1,1,
                1,1,1,1,1,0,1,1,1,1,
                1,1,1,1,1,0,0,0,1,1,
                1,1,1,1,1,1,1,0,0,0,
                1,1,1,1,1,1,1,1,1,1,
        };
void displyMaze()
{
    for(int i=0; i< MAXROW; i++)
    {
        for(int j=0; j<MAXLINE; j++)
        {
            if(maze[i][j] == 1) printf("%2s"," *");
            else if(maze[i][j] == 2) printf("%2s"," #");
            else printf("%2s"," ");
        }
        putchar(10);
    }
    printf(" ====================\n");
}
void displyPoint(){
    for(int i=0; i< MAXROW; i++)
    {
        for(int j=0; j<MAXLINE; j++)
        {

            printf("(%d,%d)",PrePoint[i][j]._x,PrePoint[i][j]._y);

        }
        putchar(10);
    }
    printf(" ====================\n");
}
//push
void visit(int x,int y,Point t){
    //压入新站点
    Point p={x,y};
    push(&stack,p);

    //同时存储前一个站点
    //但是是错位存储,使用新站点坐标储存前一个坐标,最后通过终点,在PrePoint二维数组中找出路径
    PrePoint[x][y]= t;
}
int main(){
    //displyMaze();
    Point sp={1,0},ep={8,9};//起始点和终点
    //错位存储,使用下一个坐标储存前一个坐标,最后通过终点,找出路径
    //memset操作单位为字节,初始化所有元素为-1
    memset(PrePoint,0xff,sizeof(Point)*MAXROW*MAXLINE);


    initStack(&stack);//初始化栈
    push(&stack,sp);//入栈起始点
    int flg=1;//判断是否找到出口的标准
    while (!isStackEmpty(&stack)){//栈不为空
        Point t;
        t= pop(&stack);//弹出的点
        maze[t._x][t._y]=2;//经过的点
        system("cls");
        displyMaze();
        sleep(1);

        //左
        if(t._y-1>=0 && maze[t._x][t._y-1]==0){//判断是否越界
            //下一个合法的点压栈同时保存t点(刚弹出的点,即前一个合法点)
            visit(t._x,t._y-1,t);
        }
        //右
        if(t._y+1<=9 && maze[t._x][t._y+1]==0){
            visit(t._x,t._y+1,t);
        }
        //上方
        if(t._x-1>=0 && maze[t._x-1][t._y] ==0){
            visit(t._x-1,t._y,t);
        }
        //下
        if(t._x+1<=9 && maze[t._x+1][t._y]==0){
            visit(t._x+1,t._y,t);
        }

        //判断是否找到出口
        if (t._x == ep._x  &&  t._y==ep._y){
            printf("出路\n");
            flg=0;//找到出口
            clearStack(&stack);//清空栈

            break;
        }
    }
    if(flg==1){
        printf("没有出口");
    }

    //打印记录路径的二维数组
    displyPoint();
    //正序记录路径的链表
    Node *list=createLinkList();
    //回溯路径
    Point p;
    p=ep;    //终点 ep={8,9}  //起点 sp={1,0}
    while (p._x!=-1){
        //从终点到起点的路径
        //printf("(%d,%d) ",p._x,p._y);//8 9
        //创建链表存储路径

        insertLinkListHead(list,p);
        //回溯到前一个点
        p=PrePoint[p._x][p._y];// PrePoint[8][9]  错位存储,8,9位置存储的是上一个点的坐标
    }
    //打印路径
    traverseLinkList(list);

    return 0;
}