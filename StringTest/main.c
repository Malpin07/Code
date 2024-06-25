#include <stdio.h>
#include "mystring.h"

int main() {

    char str1[] = "fello";


    char * p=str1;
    printf("%p ",str1);//000000dde0bff8fa
    printf("%s ",p);//fello //000000994cfff94a
    printf("%s ",str1);//fello
    printf("%s ",p+1);
    printf("%s ",str1+1);
    printf("%s",&str1+1);//����
    printf("%s ",p+4);
    printf("%p",&p);//0000000a1f9ff940
    printf("%s",&(*p));//000000dde0bff8fa



//    int len = myStrlen(str1);
//    printf("Length of the string is: %d\n", len);
//    char str2[] = "fello";
//     int cmp = myStrcmp(str1, str2);
//    printf("Comparison of the strings: %d\n", cmp);

    return 0;
}
