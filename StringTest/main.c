#include <stdio.h>
#include "mystring.h"

int main() {
    char str1[] = "fello";
    int len = myStrlen(str1);
    printf("Length of the string is: %d\n", len);
    char str2[] = "fello";
     int cmp = myStrcmp(str1, str2);
    printf("Comparison of the strings: %d\n", cmp);

    return 0;
}
