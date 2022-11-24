#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[]) 
{
  char str[] = "XiyouLinuxGroup"; 
  char *p = str; 
  char x[] = "XiyouLinuxGroup\t\106F\bamily";
  printf("%zu %zu %zu %zu\n", sizeof(str), sizeof(p), sizeof(x), strlen(x));
  printf("%s\n",x);
  return 0;
}