#include<stdio.h>
#include<stdlib.h>
char* convertAndMerge(char s1[],char s2[]);
char* convertAndMerge(char s1[],char s2[])
{
	char *str=(char*)malloc(40*sizeof(char));
    sprintf(str,"%s%s",s1,s2);
   
    for(int i=0;i<40;i++)
    {
    	if(*(str+i)>96)
    	{
    		*(str+i)-=32;
		}
		else if(*(str+i)<91&&*(str+i)>64)
		{
			*(str+i)+=32;
		}
	
	}
    return str;
}
int main(void)
{ 
    
	char words[2][20]={"Welcome to Xiyou","Linux Group 2022"};
	printf("%s\n",words[0]);
	printf("%s\n",words[1]);
	char*str =convertAndMerge(words[0],words[1]);
	printf("str=%s\n",str);
	free(str);
}
