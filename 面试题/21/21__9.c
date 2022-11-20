#include<stdio.h>
#include<malloc.h>
#include<string.h>
char*convert( char*s);
char*convert( char*s)
{
    char*str=(char *)malloc(sizeof(char)*30);
    strcpy(str,s);
    for(int i=0;i<22;i++)
    {
        if(*(str+i)>='a'&&*(str+i)<='z')
        *(str+i)-=32;
        else if(*(str+i)>='A'&&*(str+i)<='Z')
        *(str+i)+=32;
    }
    return str;
    free(str);
}

int main(void)
{
    char *str="XiyouLinux Group 2022";
    char *temp=convert(str);
    puts(temp);
}