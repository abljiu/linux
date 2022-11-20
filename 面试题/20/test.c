#include<stdio.h>
double fib(int n);
double fib(int n)
{
    double a=1,b=1,c=1;
    while(n>2)
    {
        c=a+b;
        a=b;
        b=c;
        n--;
    }
    return c;
}
int main()
{
    int n;
    scanf("%d",&n);
    printf("%.0lf",fib(n));
}