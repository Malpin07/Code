typedef int ElemType;
typedef struct _Node{

    ElemType data;
    struct _Node *pre;
    struct _Node *next;
}Dnode;


Dnode* createList();

void insertList(Dnode*,ElemType);

void traverseList(Dnode*);