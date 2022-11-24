#include<stdio.h>
int* get_array() 
{
  int array[1121]; 
  for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
    array[i] = i;
  }
  return array;
}
int main(int argc, char *argv[]) 
{ 
  int *p = get_array();
}