#include<stdio.h>
int a=1;
int const b=3;
const int c=3;
void func0(int n)
{
    n+=1;
    n=a;
}void func1(int *n)
{
    *n+=1;
    n=&a;
}
void func2(const int *n)
{
    *n+=1;
    n=&a;
}
void func3(int *const n)
{
    *n+=1;
    n=&a;
}
void func4(const int *const n)
{
    *n+=1;
    n=&a;
}

