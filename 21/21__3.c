#include<stdio.h>
#include<stdlib.h>
int func(int(*x)[]);
int func(int(*x)[])
{

    for(int i =0;i<10;i++)
    {
        for(int j=0;j<13;j++)
        {
            printf("%d ",(*(*x+i)+j));
        }
    }
    
}

int main()
{
    int arr[10][13];
    for(int i =0;i<10;i++)
    {
        for(int j=0;j<13;j++)
        {
            arr[i][j]=rand();
        }
    }
    func(arr);
}