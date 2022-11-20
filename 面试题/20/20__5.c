#include<stdio.h>
int main(int argc, char *argv[]) 
{
  int a[2][2];
  printf("&a = %p\t&a[0] = %p\t&a[0][0] = %p\n", &a, &a[0], &a[0][0]);
  printf("&a+1 = %p\t&a[0]+1 = %p\t&a[0][0]+1= %p\n", &a+1, &a[0]+1, &a[0][0]+1);
  return 0;
}