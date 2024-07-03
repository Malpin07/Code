#include "link_stack.h"


//创建栈
int create_stack(stack_t **my_stack){
    if(my_stack==NULL){
        printf("入参为NULL\n");
        return -1;
    }
    *my_stack=(stack_t*)calloc(1, sizeof(stack_t));
    if(*my_stack==NULL){
        printf("分配失败\n");
        return -1;
    }
    (*my_stack)->count=0;
    (*my_stack)->top=NULL;
    return 0;
}

//压栈
int push_stack(stack_t *my_stack, int data){
        if(my_stack==NULL){
            printf("入参为NULL\n");
            return -1;
        }
        node_t* newNode=(node_t*)calloc(1, sizeof(node_t));
        if(newNode==NULL){
            printf("分配失败\n");
            return -1;
        }
        newNode->data=data;
        newNode->next=my_stack->top;
        my_stack->top=newNode;
        my_stack->count++;
        return 0;
}
//出栈
int pop_stack(stack_t *my_stack, int *num){
        if(num==NULL){
            printf("入参为NULL");
            return -1;
        }
        if(is_empty(my_stack)){
            printf("栈是空!\n");
            return -1;
        }

        node_t *temp= my_stack->top;
        *num = temp->data;
        my_stack->top=my_stack->top->next;
        my_stack->count--;

        return 0;
}
//判空
int is_empty(stack_t *my_stack){
    if(my_stack==NULL){
        printf("入参为NULL");
        return -1;
    }

    if (my_stack->count==0){
        return 1;
    } else{
        return 0;
    }
}

//打印栈
int print_stack(stack_t *my_stack){
    if(my_stack==NULL){
        printf("入参为NULL\n");
        return -1;
    }
    if(my_stack->top==NULL){
        printf("栈是空\n");
        return -1;
    }

    node_t * temp=my_stack->top;
    while (temp!=NULL){
        printf("%d  \n",temp->data);
        temp=temp->next;
    }
    return 0;
}


//清空栈
int clean_list(stack_t *my_stack){

    if(my_stack==NULL){
        printf("入参为NULL");
        return -1;
    }
    node_t * del=NULL;
    while (my_stack->top!=NULL){
         del=my_stack->top;
        my_stack->top=my_stack->top->next;
        printf("销毁%d, \n",del->data);
        free(del);
    }
    return 0;
}
//销毁栈
int destroy_stack(stack_t **my_stack){
    if(my_stack==NULL||*my_stack==NULL){
        printf("入参为NULL");
        return -1;
    }
    clean_list(*my_stack);

    free(*my_stack);
    *(my_stack)=NULL;
}


