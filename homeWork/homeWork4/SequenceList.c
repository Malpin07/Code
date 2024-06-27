#include "SequenceList.h"
//创建顺序表--使用返回值实现
//list_t *create_list_1(){
//    list_t *p = (list_t *)malloc(sizeof(list_t));
//    if(NULL == p){
//        printf("内存分配失败\n");
//        return NULL;
//    }
//    memset(p, 0, sizeof(list_t));//清0
//    return p;
//}

//创建顺序表--使用地址传参实现
int create_list_2(list_t **p){
    if(NULL == p){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }
    *p = (list_t *)malloc(sizeof(list_t));
    if(NULL == *p){
        printf("内存分配失败\n");
        return INFEASIBLE;
    }
    memset(*p, 0, sizeof(list_t));//清0
    return OK;
}

//向顺序表中插入元素--尾插
int insert_list_by_tail(list_t *my_list, int data){
    if(NULL == my_list){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }
    if(N == my_list->count){
        printf("表已满 插入失败\n");
        return INFEASIBLE;
    }
    my_list->s[my_list->count].data = data;
    my_list->count++;
    return OK;
}

//打印顺序表中所有元素----实际不需要，只是学习阶段用来测试、看现象的
int print_list(list_t *my_list){
    if(NULL == my_list){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }
    int i = 0;
    for(i = 0; i < my_list->count; i++){
        printf("%d  ", my_list->s[i].data);
    }
    printf("\n");
    return OK;
}

//向顺序表中插入元素--任意位置插入
int insert_list_by_pos(list_t *my_list, int pos, int data){
    if(NULL == my_list){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }
    if (IsFull(my_list)){
        printf("已满\n");
        return INFEASIBLE;
    }
    if(pos > my_list->count || pos < 0 ) {
        printf("位置不合理\n");
        return INFEASIBLE;
    }

    for (int i = my_list->count; i >=pos ; i--) {
        my_list->s[i].data = my_list->s[i-1].data;
    }
    my_list->s[pos].data=data;
    my_list->count++;
    return OK;
}

//尾删
int  del_list_by_tail (list_t *my_list){
    if(NULL == my_list){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }
    if (IsEmpty(my_list)){
        printf("已空\n");
        return INFEASIBLE;
    }
    my_list->count--;
    return OK;
}

//删除指定位置元素
int del_list_by_pos(list_t *my_list ,int pos){
    if(NULL == my_list){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }
    if (IsEmpty(my_list)){
        printf("已空\n");
        return INFEASIBLE;
    }
    if(pos >= my_list->count || pos < 0 ) {
        printf("%d",my_list->count);
        printf("删除位置不合理\n");
        return INFEASIBLE;
    }

    for (int i = pos; i < my_list->count-1 ; i++) {
        my_list->s[i]=my_list->s[i+1];
    }

    my_list->count--;
    return OK;
}

//表为满,则返回1,否则返回0
int IsFull(list_t* L){
    if(L->count>=N){
        return 1;
    }else return 0;
}
//表为空,则返回1,否则返回0
int IsEmpty(list_t* L){
    if(L->count==0){
        return 1;
    }else return 0;
}

//销毁已存在的线性表
void DestroyList(list_t **L){
    //直接操作并修改原指针： 如果传入的是一个一级指针 list_t *L，
    // 那么在函数内部只能操作其指向的内存内容，但无法修改这个指针本身。
    // 如果要让外部也能感知到这个指针已经被置为 NULL，需要使用二级指针。
    //
    //避免悬挂指针： 如果只是释放内存而不置 NULL，
    // 外部仍然有一个一级指针指向已释放的内存，
    // 这会导致悬挂指针，进而可能引发崩溃或不可预知的错误。
    if(L) free(*L);
    *L=NULL;
}

//将线性表清空
void ClearList(list_t *L){
    L->count=0;//置0表示线性表为空
}

//修改指定位置的元素
int modify_list_by_pos(list_t *my_list, int pos, int new_data){
    if(NULL == my_list){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }
    if(0 > pos || pos >= my_list->count){
        printf("位置不合理 修改失败\n");
        return INFEASIBLE;
    }
    my_list->s[pos].data = new_data;
    return OK;
}

//查找指定位置的元素
int search_list_by_pos(list_t *my_list, int position, int *num){
    if(NULL == my_list || NULL == num){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }
    if(0 > position || position >= my_list->count){
        printf("指定的位置没有元素\n");
        return INFEASIBLE;
    }
    *num = my_list->s[position].data;
    return OK;
}
//顺序表的排序
int SortList(list_t *L,int controller(int , int , int ),int flag){
    if(NULL == L){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }


    int temp= L->count-1;
    for (int i = 0; i < temp ; ++i) {
        for (int j = 0; j <temp-i ; ++j) {
                     if(controller(L->s[j].data,L->s[j+1].data,flag)){
                         L->s[j].data=  L->s[j].data^L->s[j+1].data;
                         L->s[j+1].data=  L->s[j].data^L->s[j+1].data;
                         L->s[j].data=  L->s[j].data^L->s[j+1].data;
                     }
        }
    }
    return OK;
}
int controller(int a,int b,int flag){
    if(flag){
        return a<b?1:0;
    } else{
        return a>b?1:0;
    }
}
//顺序表排序  flag==0 升序  flag==1 降序
int sort_list(list_t *my_list, int flag){
   return SortList(my_list,controller,flag);
}
//顺序表翻转
int overturn_list(list_t *L){
    if(NULL == L){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }


    int temp= L->count-1;
    for (int i = 0; i < temp/2; ++i) {
        L->s[i].data=L->s[i].data ^ L->s[temp-i].data;
        L->s[temp-i].data=L->s[i].data ^ L->s[temp-i].data;
        L->s[i].data=L->s[i].data ^ L->s[temp-i].data;
        temp--;
    }
    return OK;
}
//顺序表剔重
int tichong_list(list_t *my_list){
    if(NULL == my_list){
        printf("入参为NULL\n");
        return INFEASIBLE;
    }


    int temp=my_list->count-1;
    for (int i = 0; i < my_list->count ; i++) {
        int n=my_list->s[i].data;
        for (int j = temp; j > i ; j--) {
            if (n==my_list->s[j].data){
                del_list_by_pos(my_list,j);
                temp--;
            }
        }
    }
    return OK;
}