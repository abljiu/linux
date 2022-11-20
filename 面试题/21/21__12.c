#include<stdio.h>
#include<malloc.h>
int *func1(void) {
  static int n = 0;
  n = 1;
  return &n;
}
int *func2(void) {
  int *p = (int *)malloc(sizeof(int));
  *p = 3;
  return p;
}
int *func3(void) {
   int n = 4;
   return &n;
}
int main(void) {
  *func1() = 4;
  *func2() = 5;
  *func3() = 6;
}