#include<stdio.h>
int i = 2;
void func() {
  if(i != 0) {
  static int m = 0;
  int n = 0;
  n++;
  m++;
  printf("m = %d, n = %d\n", m, n);
  i--;
  func();
  } else {
  return;
  }
}
int main(int argc, char *argv[]) {
  func();
  return 0;
}
