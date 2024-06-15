#include "DoubleLinkedList.h"
#include <stdio.h>
int main() {

    Dnode* head= createList();
    insertList(head,5);
    insertList(head,20);
    insertList(head,3);
    insertList(head,444);
    insertList(head,56);
    insertList(head,61);
    insertList(head,7448);
    traverseList(head);

    printf("%d\n",lenList(head));
    Dnode *find=searchList(head,5);
    if(NULL!=find){
        printf("%d\n",find->data);
    } else{
        printf("NULL");
    }

    deleteList(find);
    traverseList(head);
    sortList(head);
    traverseList(head);

    return 0;
}