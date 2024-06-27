#include "SequenceList.h"

int main(){

    list_t *my_list = NULL;
    //my_list = create_list_1();
    create_list_2(&my_list);
    //printf("my_list = %p\n", my_list); //非NULL
    //测试尾插
    insert_list_by_tail(my_list, 10);
    insert_list_by_tail(my_list, 20);
    insert_list_by_tail(my_list, 30);
    print_list(my_list); // 10 20 30

    //测试任意位置插入
    //insert_list_by_pos(my_list, 4, 40);//位置不合理
    insert_list_by_pos(my_list, 3, 40);
    insert_list_by_pos(my_list, 1, 50);

    print_list(my_list); // 10 50 20 30 40
    //printf("%d",my_list->count);
    del_list_by_pos(my_list,5);
    print_list(my_list); // 10 50 20 30 40
    printf("------\n");
    printf("翻转:\n");
    overturn_list(my_list);
    print_list(my_list); //40  50  20  30  10

    printf("------\n");
    printf("排序:\n");
    sort_list(my_list,1);
    print_list(my_list); //

    printf("------\n");
    printf("去重前:\n");
    insert_list_by_tail(my_list, 20);
    insert_list_by_tail(my_list, 20);
    insert_list_by_tail(my_list, 20);
    insert_list_by_tail(my_list, 20);
    insert_list_by_tail(my_list, 30);
    insert_list_by_tail(my_list, 30);
    insert_list_by_tail(my_list, 30);
    print_list(my_list); //10  20  30  40  50  20  20  20  20  30  30  30

    printf("去重后:\n");
    tichong_list(my_list);
    print_list(my_list);//10  20  30  40  50

    return 0;
}