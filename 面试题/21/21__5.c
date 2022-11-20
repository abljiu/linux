#include<stdio.h>
unsigned sum(unsigned n)
{
    return n?sum(n-1)+n:0;
}
int main(void)
{
    printf("%u\n",sum(100));
}