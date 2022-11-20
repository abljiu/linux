#include<stdio.h>
int main ()
{
	char p0[]="Hello,Linux";
	char* p1="Hello,Linux";
	char p2[11]="Hello,Linux";
	printf("p0==p1:%d,strcmp(p0,p2):%d\n",p0==p1,strcmp(p0,p2));
	printf("sizeof(p0):%zu,sizeof(p1):%zu,sizeof(*p2):%zu\n",sizeof(p0),sizeof(p1),sizeof(*p2));
	printf("strlen(p0):%zu,strlen(p1):%zu\n",strlen(p0),strlen(p1));
}
