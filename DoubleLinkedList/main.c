#include "DoubleLinkedList.h"

int main() {

    Dnode* head= createList();
    insertList(head,1);
    insertList(head,2);
    insertList(head,3);
    insertList(head,4);
    insertList(head,5);
    insertList(head,6);
    traverseList(head);

    return 0;
}