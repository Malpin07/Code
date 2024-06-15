typedef int ElemType;

typedef struct _Node{

    ElemType data;
    struct _Node *pre;
    struct _Node *next;
}Dnode;

//创建
Dnode* createList();
//插入
void insertList(Dnode*,ElemType);
//遍历
void traverseList(Dnode*);
//获取长度
int lenList(Dnode*);
//查找
Dnode* searchList(Dnode*,ElemType);
//删除节点
void deleteList(Dnode*);
//销毁
void destroyList(Dnode*);
//排序
void sortList(Dnode*);