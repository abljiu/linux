#include<stdio.h>
int main() { 
int a = 2020;
unsigned long c;
  printf("%p\n", &a);
  printf("我们想要修改的地址：");
  scanf("%lx", &c);
  printf("请随便输入一个数字：");
  scanf("%d", (int *)c);
  printf("a = %d\n", a);
}
