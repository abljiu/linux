# 西邮Linux兴趣小组2022纳新面试题题解

> - 本题目只作为`Xiyou Linux兴趣小组`2022纳新面试的有限参考。
> - 为节省版面，本试题的程序源码省去了`#include`指令。
> - 本试题中的程序源码仅用于考察C语言基础，不应当作为C语言「代码风格」的范例。
> - 题目难度随机排列。
>  所有题目编译并运行于`x86_64 GNU/Linux`环境。
> 
> 学长寄语：
> 长期以来，西邮Linux兴趣小组的面试题以难度之高名扬西邮校内。我们作为出题人也清楚的知道这份试题略有难度。请别担心。**若有同学能完成一半的题目，就已经十分优秀。** 其次，相比于题目的答案，我们对你的思路和过程更感兴趣，或许你的答案略有瑕疵，但你正确的思路和对知识的理解足以为你赢得绝大多数的分数。最后，做题的过程也是学习和成长的过程，相信本试题对你更加熟悉的掌握C语言的一定有所帮助。祝你好运。我们FZ103见！
> 
> Copyright © 2022 西邮Linux兴趣小组, All Rights Reserved.  
> 本试题使用采用 [知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议](http://creativecommons.org/licenses/by-nc-sa/4.0/) 进行许可。


## 0. 我的计算器坏了？！

> `2^10=1024`对应于十进制的4位，那么`2^10000`对应于十进制的多少位呢?
n*lg2

## 1. printf还能这么玩？

> 尝试着解释程序的输出。

```c
int main(void) {
  if ((3 + 2 < 2) > (3 + 2 > 2))
    printf("Welcome to Xiyou Linux Group\n");
  else
    printf("%d\n", printf("Xiyou Linux Group - 2%d", printf("")));
}
```
输出的结果为：xiyou linux group - 2022
printf嵌套由内向外打印，返回值为打印字符的个数，因此第二个%d的值为0，打印Xiyou Linux Group - 20,而这共计22个字符因此再打印22，所以最后结果为xiyou linux group - 2022

## 2. 你好你好你好呀！

> - 程序的输出有点奇怪，请尝试解释一下程序的输出吧。
> - 请谈谈对`sizeof()`及`strlen()`的理解吧。

```c
int main(void)
{
    char p0[] = "Hello,Linux";
    char *p1 = "Hello,Linux";
    char p2[11] = "Hello,Linux";
    printf("p0==p1: %d, strcmp(p0,p2): %d\n", p0 == p1, strcmp(p0, p2));
    printf("sizeof(p0): %zu, sizeof(p1): %zu, sizeof(*p2): %zu \n",
           sizeof(p0), sizeof(p1), sizeof(*p2));
    printf("strlen(p0): %zu, strlen(p1): %zu\n", strlen(p0), strlen(p1));
}
```
输出结果为：p0==p1:0,strcmp(p0,p2):-72
          sizeof(p0):12,sizeof(p1):8,sizeof(*p2):1
          strlen(p0):11,strlen(p1):11 
sizeof运算符计算字符串在内存中所占大小，strlen函数计算字符串本身长度。
p0 == p1是比较p0和p1的地址，虽然他们的内容相同但是地址不同，因此返回值为0。而strcmp比较字符串ACSII码，而p2数组只有11个char大小无法容纳\0,所以p0小于p2。
sizeof(p0)是数组p0的大小，加上末尾的\0，共计12个字符所以返回12，sizeof(p1)是指针p1大小占八个字节，因此返回8,p2是数组首元素地址，*p2即为占一个字节。
strlen不计算末尾\0，因此strlen(p0)返回11,strlen(p1)返回11。

## 3. 换个变量名不行吗？

> 请结合本题，分别谈谈你对C语言中「全局变量」和「局部变量」的「生命周期」理解。

```c
int a = 3;
void test()
{
    int a = 1;
    a += 1;
    {
        int a = a + 1;
        printf("a = %d\n", a);
    }
    printf("a = %d\n", a);
}
int main(void)
{
    test();
    printf("a= %d\n", a);
}
```
输出结果为：a=32768
          a=2
          a=3
首先打印的a是test函数中的第一个a，因为没有赋初值，所以产生的是随机值。第二个打印a是test函数中第二个a，对应函数中定义的局部变量，因此打印2。第三个打印的是最先定义的全局变量a，因此打印3。
全局变量的生命周期是整个程序，而局部变量的声明周期随着函数的结束而结束。

## 4. 内存对不齐

> `union`与`struct`各有什么特点呢，你了解他们的内存分配模式吗。

```c
typedef union
{
    long l;
    int i[5];
    char c;
} UNION;
typedef struct
{
    int like;
    UNION coin;
    double collect;
} STRUCT;
int main(void)
{
    printf("sizeof (UNION) = %zu \n", sizeof(UNION)); 
    printf("sizeof (STRUCT) = %zu \n", sizeof(STRUCT));
}
```
输出结果为：24
          40
UNION中最大的是i数组，共计20个字节，且为最大类型整数倍，因此UNION大小为20。
STRUCT中有一个int，嵌套了UNION，最最后加上一个double，int先占四个字节，再将UNION与最小对齐数比较为8,因此UNION从8开始对齐，得28,double也要求从8的倍数对齐，因此从32加8得40。

## 5. Bitwise

> - 请使用纸笔推导出程序的输出结果。
> - 请谈谈你对位运算的理解。

```c
int main(void)
{
    unsigned char a = 4 | 7;
    a <<= 3;
    unsigned char b = 5 & 7;
    b >>= 3;
    unsigned char c = 6 ^ 7;
    c = ~c;
    unsigned short d = (a ^ c) << 3;
    signed char e = -63;
    e <<= 2;
    printf("a: %d, b: %d, c: %d, d: %d \n", a, b, c, (char)d);
    printf("e: %#x \n", e);
}
```
输出结果为：a:56,b:4,c:254,d:48
          e:0x4
位运算即将对应二进制数进行相应运算，|是有1则为1,&是都为1才为1,^是不同为1。左移右移是将对应二进制码按位移动，补0或1，多余舍去。
## 6. 英译汉

> 请说说下面数据类型的含义，谈谈`const`的作用。
> 1. `char *const p`。
> 2. `char const *p`。
> 3. `const char *p`。
const在谁前面谁就不可变，`char *const p`const在p前指针不可变，`char const *p`与`const char *p`相同，都为内容不可变。

## 7. 汉译英

> 请用变量`p`给出下面的定义:
> 1. 含有10个指向`int`的指针的数组。
> 2. 指向含有10个`int`数组的指针。
> 3. 含有3个「指向函数的指针」的数组，被指向的函数有1个`int`参数并返回`int`。
1.int *p[10]
2.int (*P)[10]
3.int ((*p)[10])(int)

## 8. 混乱中建立秩序

> 你对排序算法了解多少呢?  
> 请谈谈你所了解的排序算法的思想、稳定性、时间复杂度、空间复杂度。
> 
> 提示：动动你的小手敲出来更好哦~
冒泡排序：
```c
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
```

## 9. 手脑并用

> 请实现ConvertAndMerge函数：  
> 拼接输入的两个字符串，并翻转拼接后得到的新字符串中所有字母的大小写。
> 
> 提示:你需要为新字符串分配空间。

```c
char* convertAndMerge(/*补全签名*/);
int main(void) {
  char words[2][20] = {"Welcome to Xiyou ", "Linux Group 2022"};
  printf("%s\n", words[0]);
  printf("%s\n", words[1]);
  char *str = convertAndMerge(words);
  printf("str = %s\n", str);
  free(str);
}
```
代码如下：
```c
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
```


## 10. 给你我的指针，访问我的心声

>　程序的输出有点奇怪，请尝试解释一下程序的输出吧。

```c
int main(int argc, char **argv) 
{
  int arr[5][5];
  int a = 0;
  for (int i = 0; i < 5; i++) 
  {
    int *temp = *(arr + i);
    for (; temp < arr[5]; temp++) 
    *temp = a++;
  }
  for (int i = 0; i < 5; i++) 
  {
    for (int j = 0; j < 5; j++) 
    {
      printf("%d\t", arr[i][j]);
    }
  }
}
```
输出结果为：0       1       2       3       4       25      26      27      28      29      45      46      47      48      49      60      61      62      63       64      70      71      72      73      74  
该程序实现了遍历五遍二维数组，且每次都从上一次的下一行开始。二维数组名代表二维数组中首个一维数组的地址，首先定义指针temp指向每一个二维数组中的一维数组，temp++表示这次循环完成指向下一个元素，且*temp加一。

## 11. 奇怪的参数

> 你了解argc和argv吗？  
> 直接运行程序argc的值为什么是1？  
> 程序会出现死循环吗？

```c
#include <stdio.h>
int main(int argc, char **argv)
{
    printf("argc = %d\n", argc);
    while (1)
    {
        argc++;
        if (argc < 0)
        {
            printf("%s\n", (char *)argv[0]);
            break;
        }
    }
}
```
输出结果为：
argc=1
/home/abljiu/桌面/面试题/22/11

argc为整形表示输入参数的个数
argv指针数组
argv[0]指向输入程序的路径及名称
argv[i]指向输入的第i-1个参数
不会进入死循环，不停加直到溢出变为负值就会退出循环。

## 12. 奇怪的字符

> 程序的输出有点奇怪，请尝试解释一下程序的输出吧。

```c
int main(int argc, char **argv)
{
    int data1[2][3] = {{0x636c6557, 0x20656d6f, 0x58206f74},
                       //  u o y i     n i L            \0
                       {0x756f7969, 0x6e694c20, 0x00000000}};
    int data2[] = {0x47207875, 0x70756f72, 0x32303220, 0x00000a32};
    char *a = (char *)data1;
    char *b = (char *)data2;
    char buf[1024];
    strcpy(buf, a);
    strcat(buf, b);
    printf("%s \n", buf);
}
```
输出结果为：Welcome to Xiyou Linux Group 2022
程序实现了通过16进制ASCII码输出字符串的过程，由于常用的X86结构是小端模式，低位存储在低地址，那么存储之后的顺序就变成了0X57656c63,并从低地址开始读取每一个字符并输出。strcpy函数将a字符串复制到buf中，而strcat连接buf和b，最终输出的buf就是data1和data2中的所有字符。

## 13. 小试宏刀

> - 请谈谈你对`#define`的理解。
> - 请尝试着解释程序的输出。

```c
#include <stdio.h>
#define SWAP(a, b, t) t = a; a = b; b = t
#define SQUARE(a) a *a
#define SWAPWHEN(a, b, t, cond) if (cond) SWAP(a, b, t)
int main() {
  int tmp;
  int x = 1;
  int y = 2;
  int z = 3;
  int w = 3;
  SWAP(x, y, tmp);
  printf("x = %d, y = %d, tmp = %d\n", x, y, tmp);
  if (x > y) SWAP(x, y, tmp);
  printf("x = %d, y = %d, tmp = %d\n", x, y, tmp);
  SWAPWHEN(x, y, tmp, SQUARE(1 + 2 + z++ + ++w) == 100);
  printf("x = %d, y = %d,tmp=%d\n", x, y, tmp);
  printf("z = %d, w = %d ,tmp = %d\n", z, w, tmp);
}
```
输出结果为：
define仅仅是单纯的替换，容易出现意想不到的错误。
x=2,y=1,tmp=1
x=1,y=2,tmp=2
x=2,y=2
z=5,w=5,tmp=2
首先进行SWAP进行交换，得到的x，y，z分别为2，1，1，由于x>y，所以再次进行交换得到x，y，z分别为1,2,2。
进行`SWAPWHEN(x, y, tmp, SQUARE(1 + 2 + z++ + ++w) == 100);`时相当于将原句替换为`if (1 + 2 + z++ + ++w*1 + 2 + z++ + ++w)tmp = x; x = y; y = tmp`可见if仅仅决定tmp=x，后面的x = y; y = tmp；依旧会照常运行。因此最终得到的结果为x=2,y=2，z=5,w=5,tmp=2。

## 14. GNU/Linux命令 (选做)

> 你知道以下命令的含义和用法吗：
> 
> 注：
> > 嘿！你或许对Linux命令不是很熟悉，甚至你没听说过Linux。  
> > 但别担心，这是选做题，不会对你的面试产生很大的影响！  
> > 了解Linux是加分项，但不了解也不扣分哦！
> - `ls`
> - `rm`
> - `whoami`
> 
> 请问你还了解哪些GNU/Linux的命令呢。
ls表示列出目录的内容。
rm表示删除文件。
whoami表示显示自身用户名。