# 西邮Linux兴趣小组2021纳新面试题题解

> 注:
> - 本题目仅作`西邮Linux兴趣小组`2021纳新面试题的有限参考。
> - 为节省版面本试题的程序源码中省略了`#include`指令。
> - 本试题中的程序源码仅用于考察C语言基础，不应当作为C语言代码风格的范例。
> - 题目难度与序号无关。
> - 所有题目均假设编译并运行`x86_64 GNU/Linux`环境。
> 
> Copyright © 2021 西邮Linux兴趣小组, All Rights Reserved.  
> 本试题使用采用 [知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议](http://creativecommons.org/licenses/by-nc-sa/4.0/) 进行许可。



## 1. 大小和长度竟然不是一个意思

> `sizeof()`和`strlen()`有什么异同之处？
> 
> 他们对于不同参数的结果有什么不同？请试举例子说明。

```c
int main(void) {
  char s[] = "I love Linux\0\0\0";
  int a = sizeof(s);
  int b = strlen(s);
  printf("%d %d\n", a, b);
}
```
输出结果为：16 12
sizeof运算符计算字符串在内存中所占大小，strlen函数计算字符串本身长度。
字符串末尾默认带有\0作为结尾，加上前面12个字符和3个\0，共计16个字节所以输出16。
srtrlen仅仅计算字符串从长度因此输出12。

## 2. 箱子的大小和装入物品的顺序有关

> `test1`和`test2`都含有：1个`short`、1个`int`、1个`double`，那么`sizeof(t1)`和`sizeof(t2)`是否相等呢？这是为什么呢？

```c
struct test1 {
  int a;
  short b;
  double c;
};
struct test2 {
  short b;
  int a;
  double c;
};
int main(void) {
  struct test1 t1;
  struct test2 t2;
  printf("sizeof (t1) : %d\n", sizeof(t1));
  printf("sizeof(t2): %d\n", sizeof(t2));
}
```
输出结果为：sizeof(t1):16
          sizeof(t2):16
本题涉及到内存对齐，内存对齐是指：
1.第一个成员在与结构体变量偏移量为0的地址处。（即结构体的首地址处，即对齐到0处）
2.其他成员变量要对齐到某个数字（对齐数）的整数倍的地址处。
3.结构体的总大小为最大对齐数（每个成员变量都有一个对齐数）的整数倍。
4.如果嵌套了结构体，嵌套的结构体对齐到自己的最大对齐数的整数倍处，结构体的整体大小就是所有最大对齐数（含嵌套结构体的对齐数）的整数倍。
对齐数 = 该结构体成员变量自身的大小与编译器默认的一个对齐数的较小值，一般来说默认对齐数为8。
test1中对齐方式如下:aaaabb  cccccccc(共计16字节)
test2中对齐方式如下:bb  aaaacccccccc(共计16字节)

## 3. 哦，又是函数
> 想必在高数老师的教导下大家十分熟悉函数这个概念。那么你了解计算机程序设计中的函数吗？请编写一个`func`函数，用来输出二维数组`arr`中每个元素的值。

```c
/*在这里补全func函数的定义*/
int main(void) {
  int arr[10][13];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 13; j++) {
      arr[i][j] = rand();
    }
  }
  func(arr);
}
```
代码如下：
```c
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
```

## 4.就不能换个变量名吗？

> - 请结合下面的程序，简要谈谈`传值`和`传址`的区别。
> - 简要谈谈你对C语言中变量的生命周期的认识。

```c
int ver = 123;
void func1(int ver) {
  ver++;
  printf("ver = %d\n", ver);
}
void func2(int *pr) {
  *pr = 1234;
  printf("*pr = %d\n", *pr);
  pr = 5678;
  printf("ver = %d\n", ver);
}
int main() {
  int a = 0;
  int ver = 1025;
  for (int a = 3; a < 4; a++) {
    static int a = 5;
    printf("a = %d\n", a);
    a = ver;
    func1(ver);
    int ver = 7;
    printf("ver = %d\n", ver);
    func2(&ver);
  }
  printf("a = %d\tver = %d\n", a, ver);
}
```
输出结果为：
a=5
ver=1026
ver=7
*pr=1234
ver=123
a=0     ver=1025
程序先定义了两个函数，func1对传入的参数进行+1,再打印其值，func2对传入的指针指向的变量赋值1234,再打印其值，之后修改地址为5678,最后打印全局变量ver的值。
执行程序进入main函数，定义a，ver，进入for循环并将3赋值给a，定义静态变量a并赋初值5,首先打印静态变量a的值5，之后将ver的值赋值给a，执行func1函数传入实参ver，+1并打印1026，在将7赋值给ver，打印ver的值7,
进入func2函数传入ver的地址，打印修改后ver的值1234,打印全局变量ver的值123,退出循环打印main函数中最初定义的a和ver的值。
局部变量的生命周期仅在该函数中，内存随着函数的结束释放。全局变量的生命周期是整个程序，随着整个程序的结束释放。静态局部变量同全局变量一样。

## 5. 套娃真好玩！

> 请说明下面的程序是如何完成求和的？

```c
unsigned sum(unsigned n) { return n ? sum(n - 1) + n : 0; }
int main(void) { printf("%u\n", sum(100)); }
```
输出结果为：5050
该程序通过定义了一个函数，函数不断递归，从100每次-1进行递归，直到递归到0，这一过程实现从100到1的求和。

## 6. 算不对的算术

```c
void func(void) {
  short a = -2;
  unsigned int b = 1;
  b += a;
  int c = -1;
  unsigned short d = c * 256;
  c <<= 4;
  int e = 2;
  e = ~e | 6;
  d = (d & 0xff) + 0x2022;
  printf("a=0x%hx\tb=0x%x\td=0x%hx\te=0x%x\n", a, b, d, e);
  printf("c=Ox%hhx\t\n", (signed char)c);
}
```
输出结果为：a=0xfffe        b=0xffff        d=0x2022        e=0xffffffff
          c=0xf0
负数的十六进制是先转化为二进制在进行取反加一
-2的short类型十六进制为0xfffe，b=-1,b的short类型十六进制为0xffff，256的二进制值为0000001000000000，-256的二进制值为1111111000000000，和0xff进行按位与运算的结果为0,因此d=0x2022,6的八位二进制为00000110与111111101按位或结果为11111111,则e为0xffffffff，c二进制为10000001,左移四位得00010000转化为16进制为0xf0。

## 7. 指针和数组的恩怨情仇                                                 

```c
int main(void) {
  int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int(*b)[3] = a;
  ++b;
  b[1][1] = 10;
  int *ptr = (int *)(&a + 1);
  printf("%d %d %d \n", a[2][1], **(a + 1), *(ptr - 1));
}
```
输出结果为：10 4 9
定义一个数组指针b指向数组a，给b+1使它指向第二个一维数组，则b[1][1]指向第三个一维数组的第二个元素，并赋值为10,那么a[2][1]的值就为10,数组名代表数组首元素地址，二维数组数组名代表，二维数组中第一个一维数组的地址，加一变成第二个一维数组的地址，那么**(a + 1)的值就为4,二维数组取地址加一跨越的长度是整个数组，定义指针ptr指向&a + 1，那么ptr-1就指向数组最后一个元素，则 *(ptr - 1)的值为9。

## 8. 移形换位之术

> 下面有`a`、`b`、`c`三个变量和4个相似的函数。
> - 你能说出使用这三个变量的值或地址作为参数分别调用这5个函数，在语法上是否正确吗？
> - 请找出下面的代码中的错误。
> - `const int`和`int const`是否有区别？如果有区别，请谈谈他们的区别。
> - `const int *`和`int const *`是否有区别？如果有区别，请谈谈他们的区别。

```c
int a = 1;
int const b = 2;
const int c = 3;
void funco(int n) {
  n += 1;
  n = a;
}
void func1(int *n) {
  *n += 1;
  n = &a;
}
void func2(const int *n) {
  *n += 1;
  n = &a;
}
void func3(int *const n) {
  *n += 1;
  n = &a;
}
void func4(const int *const n) {
  *n += 1;
  n = &a;
}
```
```c
不正确，func2函数中声明了const int *n，那么指针的内容就不能改变，所以*n += 1不合法。
       func3函数中声明了int *const n，那么指针的指向就不能被改变，所以n = &a不合法。
       func4函数中声明了const int *const n，那么指针的内容和指向就不能被改变，所以*n += 1和n = &a和不合法。
       const int和int const是相同的，const int *和int const *是不同的，const在谁前面谁就不能改变，const int *内容不可变，int const *指针不可变。
```


## 9. 听说翻转字母大小写不影响英文的阅读？

> 请编写`convert`函数用来将作为参数的字符串中的大写字母转换为小写字母，将小写字母转换为大写字母。返回转换完成得到的新字符串。
> 

```c
char *convert(const char *s);
int main(void) {
  char *str = "XiyouLinux Group 2022";
  char *temp = convert(str);
  puts(temp);
}
```
代码如下：
```c
#include<stdio.h>
#include<malloc.h>
#include<string.h>
char*convert( char*s);
char*convert( char*s)
{
    char*str=(char *)malloc(sizeof(char)*30);
    strcpy(str,s);
    for(int i=0;i<22;i++)
    {
        if(*(str+i)>='a'&&*(str+i)<='z')
        *(str+i)-=32;
        else if(*(str+i)>='A'&&*(str+i)<='Z')
        *(str+i)+=32;
    }
    return str;
    free(str);
}

int main(void)
{
    char *str="XiyouLinux Group 2022";
    char *temp=convert(str);
    puts(temp);
}
```

## 10. 交换礼物的方式

> - 请判断下面的三种`Swap`的正误，分别分析他们的优缺点。
> - 你知道这里的`do {...} while(0)`的作用吗？
> - 你还有其他的方式实现`Swap`功能吗？

```c
#define Swap1(a, b, t) \ 
  do {                 \ 
    t = a;             \
    a = b;             \
    b = t;             \
  } while (0)
#define Swap2(a, b) \
  do {              \
    int t = a;      \
    a = b;          \
    b = t;          \
  } while (0)
void Swap3(int a, int b) {
  int t = a;
  a = b;
  b = t;
}
```
int a=1,b=3,t=6;
Swap1(a,b,t)=3 1 1;
Swap2(a,b)=3 1;
Swap3(a,b)=3 1;
函数Swap3必须在函数中打印出交换后，a，b的值，若在函数结束后进行打印则输出原有的a，b值，并不会修改main函数中的值；



## 11. 据说有个东西叫参数

> 你知道`argc`和`argv`的含义吗？请解释下面的程序。你能在不使用`argc`的前提下，完成对`argv`的遍历吗？

```c
int main(int argc, char *argv[]) {
  printf("argc = %d\n", argc);
  for (int i = 0; i < argc; i++)
    printf("%s\n", argv[i]);
}
```
argc为整形表示输入参数的个数
argv指针数组
argv[0]指向输入程序的路径及名称
argv[i]指向输入的第i-1个参数
## 12. 人去楼空

> 这段代码有是否存在错误？谈一谈静态变量与其他变量的异同。

```c
int *func1(void) {
  static int n = 0;
  n = 1;
  return &n;
}
int *func2(void) {
  int *p = (int *)malloc(sizeof(int));
  *p = 3;
  return p;
}
int *func3(void) {
  int n = 4;
  return &n;
}
int main(void) {
  *func1() = 4;
  *func2() = 5;
  *func3() = 6;
}
```
有错误，在func3函数中，返回了n的地址，但是n为函数中定义的局部变量，生存期在函数运行结束后结束，因此main函数中无法将6赋值给n。

malloc函数可以申请分配一块内存地址，分配成功后，malloc函数返回这块内存的首地址，需要一个指针来接受这个地址。
例如:```char*p=(char*)malloc(n*sizeof(char))```
且应在使用前调用头文件```c#include<malloc.h>```并在使用完成后进行手动释放```c free（）``
静态变量（static）将变量储存在静态储存区，程序结束后由系统释放，使得在本函数结束后依旧可以在main函数中使用该变量。

## 13. 奇怪的输出

```c
int main(void) {
  int data[] = {0x636c6557, 0x20656d6f, 0x78206f74,
                0x756f7969, 0x6e694c20, 0x67207875,
                0x70756f72, 0x32303220, 0x00000a31};
  puts((const char*)data);
}
```
输出结果为：Welcome to xiyou Linux group 2021
程序实现了通过16进制ASCII码输出字符串的过程，由于常用的X86结构是小端模式，低位存储在低地址，那么存储之后的顺序就变成了0X57656c63,并从低地址开始读取每一个字符并输出。

## 14. 请谈谈对从「C语言文件到可执行文件」的过程的理解
1.预处理：将#define删除并且展开头文件，出处理预编译指令，删除所有的注释。
2.编译：检查语法，优化源代码。
3.汇编 ：将高级语言转化成机器语言。 
4.链接 ：分配地址和空间，合成可执行的程序。

## 15. (选做) 堆和栈

> 你了解程序中的栈和堆吗？它们在使用上有什么区别呢？请简要说明。
栈由操作系统自动分配释放，用于存放函数的函数值、局部变量等。
堆由开发人员分配和释放，若开发人员不释放，程序结束时由系统回收。

堆和栈的区别：
（1）管理方式不同。栈由操作系统自动分配释放，无需我们手动控制；堆的申请和释放由程序员控制，容易产生内存泄漏。
（2）空间大小不同。每个进程拥有的栈的大小要远远小于堆的大小。理论上程序员可申请的堆的大小为虚拟内存的大小。
（3）分配方式不同。堆都是动态分配的。栈有两种分配方式：静态分配和动态分配。静态分配是由操作系统完成的，比如局部变量的分配。动态分配由alloca函数进行分配，但是栈的动态分配和堆是不同的，它的动态分配是由操作系统进行释放，无需我们手工实现。
（5）分配效率不同。栈由操作系统自动分配，会在硬件层级对栈提供支持，堆由函数或者运算符完成生成和相关管理，堆得效率比栈低得多。
（6）存放的内容不同。栈存放的内容：函数返回地址、相关参数、局部变量和寄存器内容等。而堆的具体存放内容由程序员来定。


## 16. (选做) 多文件

> 一个程序在不使用任何头文件的情况下，如何使用另一个文件中的函数。
如果A中定义了一个函数，要在B中使用该函数，可以在函数前加上extern声明，声明该函数是在其他的联合文件中的。

## 17. (选做) `GNU/Linux`与文件

> - 你知道如何在 `GNU/Linux`下如何使用命令行创建文件与文
件夹吗？
创建文件：touch XXX
创建文件名夹：mkdir XXX
> - 你知道`GNU/Linux`下的命令ls 的每一列的含义吗？
ls表示列出当前目录的清单，每一列代表当前目录的文件夹和文件。
> - 你知道`GNU/Linux`下文件的访问时间、修改时间、创建时间如何查看吗？并简单说说他们的区别。
使用stat命令加文件名查看访问时间修改时间和创建时间。
访问时间是最近一次打开文件的时间，修改时间是最近一次对文件修改的时间，创建时间是该文件创建的时间。