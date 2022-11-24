#include<stdio.h>
int main(int argc,char **argv)
{
	printf("argc=%d\n",argc);
	while(1)
	{
		argc++;
		if(argc<0)
		{
			printf("%s\n",(char*)argv[0]);
			break;
		}
	}
}
