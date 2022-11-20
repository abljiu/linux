#include<stdio.h>
void func(void)
{
    double a=-2;
    unsigned int b=1;
    b+=a;
    int c=-1;
    unsigned short d=c*256;
    c<<=4;
    int e=2;
    e=~e|6;
    d=(d&0xff)+0x2022;
    printf("a=0x%hx\tb=0x%hx\td=0x%hx\te=0x%x\n",a,b,d,e);
    printf("c=0x%hhx\t\n",(signed char)c);
}
int main()
{
    func();
}