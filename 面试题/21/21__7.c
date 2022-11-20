#include<stdio.h>
int main(void)
{
    int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    int(*b)[3]=a;
    ++b;
    b[1][1]=10;
    int *ptr=(int*)(&a+1);
    printf("%d %d %d\n",a[2][1],**(a+1),*(ptr-1));
}