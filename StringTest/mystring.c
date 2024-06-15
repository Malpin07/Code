#include <stdio.h>
#include "mystring.h"
int myStrlen(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
char *myStrcat(char *dest, char *src) {
    char *temp = dest;
    while (*dest){dest++;}
    while ((*dest++ = *src++) != '\0') {}
    return temp;
}
char *myStrcpy(char *dest, char *src) {
    char *temp = dest;
    while ((*dest++ = *src++) != '\0') {}
    return temp;
}
int myStrcmp(char *str1, char *str2) {
    for(;(*str1 == *str2) && (*str1&&*str2) ;str1++,str2++);
    return *str1 - *str2;
}

