#include "Stack.h"
#include <stdio.h>
int main(){

    Stack* stack;
    initStack(&stack);
    for (ElemType i = 0; i <=10; ++i) {
            push(stack,i);
    }
    resetStack(stack);
    while (!isStackEmpty(stack)){
        printf("%d ",pop(stack));
    }

    clearStack(&stack);
    return 0;
}