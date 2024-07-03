#include "link_queue.h"
int main(int argc, const char *argv[])
{
    queue_t *my_queue = NULL;
    create_queue(&my_queue);
    printf("my_queue = %p\n", my_queue); // 非NULL

    //入队列
    push_queue(my_queue, 10);
    push_queue(my_queue, 20);
    push_queue(my_queue, 30);
    push_queue(my_queue, 40);
    print_queue(my_queue); // 10 20 30 40

    //出队列
    int value = 0;
    pop_queue(my_queue, &value);
    printf("value = %d\n", value); //10
    pop_queue(my_queue, &value);
    printf("value = %d\n", value); //20
    print_queue(my_queue); // 30 40

    push_queue(my_queue, 60);
    push_queue(my_queue, 70);
    print_queue(my_queue); // 30 40 60 70

    pop_queue(my_queue, &value);
    printf("value = %d\n", value); //30
    pop_queue(my_queue, &value);
    printf("value = %d\n", value); //40
    pop_queue(my_queue, &value);
    printf("value = %d\n", value); //60
    pop_queue(my_queue, &value);
    printf("value = %d\n", value); //70
    pop_queue(my_queue, &value); // 空了 失败

    //清空
    push_queue(my_queue, 100);
    push_queue(my_queue, 200);
    print_queue(my_queue); // 100 200
    clean_queue(my_queue);
    print_queue(my_queue); // 没有元素了

    //销毁
    destroy_queue(&my_queue);
    printf("my_queue = %p\n", my_queue); // NULL

    return 0;

}

//int main1(){
//
//    queue_t *my_queue = NULL;
//    create_queue(&my_queue);
//    printf("my_queue = %p\n", my_queue); // 非NULL
//
//    //入队列
//    push_queue(my_queue, 10);
//    push_queue(my_queue, 20);
//    push_queue(my_queue, 30);
//    push_queue(my_queue, 40);
//    push_queue(my_queue, 50); //满了 失败
//    print_queue(my_queue); // 10 20 30 40
//
//    //出队列
//    int value = 0;
//    pop_queue(my_queue, &value);
//    printf("value = %d\n", value); //10
//    pop_queue(my_queue, &value);
//    printf("value = %d\n", value); //20
//
//    push_queue(my_queue, 60);
//    push_queue(my_queue, 70);
//    push_queue(my_queue, 80); //满了 失败
//
//    pop_queue(my_queue, &value);
//    printf("value = %d\n", value); //30
//    pop_queue(my_queue, &value);
//    printf("value = %d\n", value); //40
//    pop_queue(my_queue, &value);
//    printf("value = %d\n", value); //60
//    pop_queue(my_queue, &value);
//    printf("value = %d\n", value); //70
//    pop_queue(my_queue, &value); // 空了 失败
//
//    //清空
//    push_queue(my_queue, 100);
//    push_queue(my_queue, 200);
//    print_queue(my_queue); // 100 200
//    clean_queue(my_queue);
//    print_queue(my_queue); // 没有元素了
//
//    //销毁
//    destroy_queue(&my_queue);
//    printf("my_queue = %p\n", my_queue); // NULL
//
//    return 0;
//}