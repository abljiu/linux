#include<stdio.h>
#define Swap1(a, b, t) \
  do {                 \
    t = a;             \
    a = b;             \
    b = t;             \
  } while (0)
#define Swap2(a, b) \
  do {              \
    int t = a;      \
    a = b;          \
    b = t;          \
  } while (0)
void Swap3(int a, int b) {
  int t = a;
  a = b;
  b = t;
  
}
int main()
{
    int a=1,b=3,t=6;
    Swap3(a,b);
    printf("%d %d",a,b);
}