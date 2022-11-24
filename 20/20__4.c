#include<stdio.h>
int main(int argc, char * argv[]) 
{
  char ch = 'A';
  int i = 65;
  unsigned int f = 33554433;
  *(int *)&f >>= 24;
  *(int *)&f = *(int *)&f + '?';
  printf("ch = %c i = %c f = %c\n", ch, i, *(int *)&f);
  return 0;
}