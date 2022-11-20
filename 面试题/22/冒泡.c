#include<stdio.h>
int* maopao( int *a); 
int* maopao( int *a)
{
	for(int m=0;m<6-1;m++)
	{
		for(int i=0;i<6-m-1;i++)
		{
			int t;
			if(a[i]>a[i+1])
			{
			t=a[i];
			a[i]=a[i+1];
			a[i+1]=t;
			}
		
		}
	}
return a;
}
void main()
{
	int a[6]={1,4,3,5,2,7};
	int*b=maopao(a);
	for(int i=0;i<6;i++)
	printf("%d ",*(b+i));
}
