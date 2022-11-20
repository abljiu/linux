#include<stdio.h>
typedef union
{
	long l;
	int i[5];
	char c;
}UNION;
typedef struct
{
	int like;
	UNION coin;
	double collect;
}STRUCT;
int main(void)
{
	printf("%zu\n",sizeof(UNION));
	printf("%zu\n",sizeof(STRUCT));
 } 
