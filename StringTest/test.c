#include <stdio.h>
#include <string.h>
int main()
{


        char buf[] = "sys:x:3:3:Ownerofsystemfiles:/usr/sys:";
        char *p = strtok(buf,":");
        while(p != NULL)
        {
            printf("%s\n",p);
            p = strtok(NULL,":");
        }
        return 0;

}

char * myStrstr(char *s1,char *s2)
{
    if(*s2) //查找的数据为空
    {
        while(*s1)
        {
            for(int n=0;*(s1+n) == *(s2+n); n++)
            {
                if(*(s2+n+1) == '\0')
                    return s1;
            }
            s1++;
        }
        return NULL;
    }
    else
        return NULL;
}


