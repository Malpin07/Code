#include <stdio.h>
#include <string.h>
int main()
{
    char buf[] = "aaaaaaaaaa@bbbbbbbbbbbb@ccccccccccc@ddddddddd";
    char delim[] = "@"; // "@#"
    int size = sizeof(buf);

    for(int i=0; i<size; i++)
        printf("%c",buf[i]);
    putchar(10);
    strtok(buf,delim);

    for(int i=0; i<size; i++)
        printf("%c",buf[i]);
    putchar(10);
    strtok(NULL,delim); // strtok(buf,delim);

    for(int i=0; i<size; i++)
        printf("%c",buf[i]);
    putchar(10);

    strtok(NULL,delim); // strtok(buf,delim);

    for(int i=0; i<size; i++)
        printf("%c",buf[i]);
    putchar(10);
//第一个或是最后一个是分隔符，如何
    return 0;
}