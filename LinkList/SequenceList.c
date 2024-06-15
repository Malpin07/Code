/*SequenceList.c -- 顺序表*/
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1      //定义布尔型常量
#define FALSE 0  //定义布尔型常量
#define OK 1 //一般正确
#define ERROR 0 //一般错误
#define INFEASIBLE -1 //不合理错误
#define OVERFLOW -2 //溢出错误
#define MAXSIZE 100  //最大容量
typedef int Status;
typedef char ElemType;


//定义顺序表结构
typedef struct {
    /*表示 data 是一个指针，它可以指向动态分配的内存块，
    因此数组的大小不需要在编译时确定，它可以在运行时分配所需的内存空间。*/
    //ElemType *data;//定义一个指针变量，指向动态分配的内存块

    /*定义了一个固定大小的数组，其大小在编译时就已确定。
    这意味着它在程序执行期间无法改变大小，它将一直占用固定大小的内存空间。*/
    ElemType data[MAXSIZE];//定义一个固定大小的数组
    int length;//顺序表长度
} SeqList;

//初始化顺序表,建立一个空表
Status InitList(SeqList *L);
//销毁已存在的线性表
Status DestroyList(SeqList *L);
//将线性表清空
Status ClearList(SeqList *L);
//返回线性表的长度
int GetLength(SeqList L);
//若线性表为空,则返回TRUE,否则返回FALSE
Status IsEmpty(SeqList L);
//在线性表L中第i个位置插入新元素e
Status ListInsert(SeqList *L, int i, ElemType e);
//在线性表L中删除第i个位置的元素,用e返回
Status ListDelete(SeqList *L, int i, ElemType *e);

//若线性表为满,则返回TRUE,否则返回FALSE
Status IsFull(SeqList L);
//在线性表中查找给定值e相等的元素,成功返回元素在表中的序号,失败返回0
int LocateElem(SeqList L, ElemType e);
//将线性表L中的第i个元素返回给e
Status GetElem(SeqList L, int i, ElemType *e);
//遍历线性表
void TraverseList(SeqList L);



int  main(){
    SeqList L;//定义顺序表
    InitList(&L);//初始化顺序表
    printf("长度:%d\n",GetLength(L));
    printf("若线性表为空,则返回TRUE,否则返回FALSE:%d\n",IsEmpty(L));


    ListInsert(&L,1,'a');
    ListInsert(&L,2,'b');
    ListInsert(&L,3,'c');
    ListInsert(&L,4,'d');
    printf("长度:%d\n",GetLength(L));

    TraverseList(L);
    return 0;
}

//初始化顺序表,建立一个空表
Status InitList(SeqList *L) {
    //L->data = calloc (MAXSIZE, sizeof(ElemType));
    //if(!L->data)exit(OVERFLOW);
    L->length=0;
    return OK;
}

//销毁已存在的线性表
Status DestroyList(SeqList *L){
    if(L->data) free(L->data);
}

//将线性表清空
Status ClearList(SeqList *L){
    L->length=0;//置0表示线性表为空
}

//返回线性表的长度
int GetLength(SeqList L){
    return L.length;
}

//若线性表为满,则返回TRUE,否则返回FALSE
Status IsFull(SeqList L){
    if(L.length>=MAXSIZE){
        return TRUE;
    }else return FALSE;
}
//在线性表L中第i个位置插入新元素e
Status ListInsert(SeqList *L, int i, ElemType e){
    int k;
    if(L->length>=MAXSIZE){//判断是否已满
        return OVERFLOW;//返回溢出错误
    }
    if(i<1||i>L->length+1){//判断位置是否合理
        return ERROR;//返回错误
    }
    if(i<=L->length){
        for(k=L->length;k>=i;k--){//从后往前移动元素
            L->data[k+1]= L->data[k];//后移元素
        }
    }
    L->data[i-1]=e;//插入新元素
    L->length++;//表长度加1
    return OK;
}
//在线性表L中删除第i个位置的元素,用e返回
Status ListDelete(SeqList *L, int i, ElemType *e){
    int k;
    if(i<1||i>L->length+1){//判断位置是否合理
        return ERROR;//返回错误
    }
    *e= L->data[i-1];//用e返回被删除的元素
    if(i<=L->length) {//
        for (k = i; k < L->length; k++) {
            L->data[k - 1] = L->data[k];//前移元素
        }
    }
    L->length--;//表长度减1
    return OK;
}






//若线性表为空,则返回TRUE,否则返回FALSE
Status IsEmpty(SeqList L){
    if(L.length==0){
        return TRUE;
    }else return FALSE;
}

//将线性表L中的第i个元素返回给e
Status GetElem(SeqList L, int i, ElemType *e){
    if(i<1||i>L.length){//判断位置是否合理
        return ERROR;
    }
    *e=L.data[i-1];
    return OK;

}

//在线性表中查找给定值e相等的元素,成功返回元素在表中的序号,失败返回0
int LocateElem(SeqList L, ElemType e){
    int i;
    for(i=1;i<=L.length;i++){
        if(L.data[i-1]==e){
            return i;
        }
    }
    return 0;
}

//遍历线性表
void TraverseList(SeqList L){
    int i;
    for(i=1;i<=L.length;i++){
        printf("%c ",L.data[i-1]);
    }
    printf("\n");
}