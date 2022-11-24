#include<stdio.h>
struct test1 {
  int a;
  short b;
  double c;
};
struct test2 {
  short b;
  int a;
  double c;
};
int main(void) {
  struct test1 t1;
  struct test2 t2;
  printf("sizeof (t1) : %d\n", sizeof(t1));
  printf("sizeof(t2): %d\n", sizeof(t2));
}