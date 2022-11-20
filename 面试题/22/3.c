#include<stdio.h>
int a=3;
void test()
{
	int a=1;
	a+=1;
   {
	int a=a+1;
	printf("a=%d\n",a);
   }
    printf("a=%d\n",a);
}
int main(void)
{
  test();
  printf("a=%d\n",a);	
}

