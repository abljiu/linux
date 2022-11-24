#include<stdio.h>
int main(int argc , char *argv[]) 
{
  unsigned char a = 255;
  char ch = 128;
  a-=ch;
  printf("a = %d ch = %d\n", a,ch);
}
