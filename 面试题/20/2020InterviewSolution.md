# 西邮Linux兴趣小组2020纳新试题题解

>注：
> 1. 本题仅作为面试有限参考
> 2. 为节省版面，省去所有`#include`指令
> 3. 题目难度与序号无关
> 4. 若无特殊声明，均假设在`Linux x86_64 GCC`编译器环境下


## 1. 请试着解释其输出。

```c
int main(int argc , char *argv[]) {
  unsigned char a = 255;
  char ch = 128;
  a -= ch;
  printf("a = %d ch = %d\n", a, ch);
}
```
char类型的最大值为127，如果给char类型赋值128则会溢出一位变成最小值-128,但在运行表达式时依旧会带入赋给的值进行运算。
## 2. 下面代码的运行输出结果是什么，并说说你的理解。

```c
int main(int argc, char *argv[]) {
  char *str = "Xi You Linux Group 20";
  printf("%d\n", printf(str));
  return 0;
}
```
printf由内到外进行打印，优先进行内部的str打印，该表示方法printf(str)表示打印str指针所指的字符串，则先打印出“Xi You Linux Group 20“，并且返回值21给%d（因为str中共有21个字符），再进行外部打印%d，%d为21,则打印21。
那么最后输出的结果即为Xi You Linux Group 2021

## 3. 这段代码的输出结果是什么？为什么会出现这样的结果？

```c
int i = 2;
void func() {
  if(i != 0) {
  static int m = 0;
  int n = 0;
  n++;
  m++;
  printf("m = %d, n = %d\n", m, n);
  i--;
  func();
  } else {
  return;
  }
}
int main(int argc, char *argv[]) {
  func();
  return 0;
}
```
结果为m = 1, n = 1
     m = 2, n = 1
在func函数中每次运行一次func函数i的值都会减一，而全局变量i在本函数中就成为了计数器，则在进行两次func函数后i=0，退出递归。

在func函数中定义了一个静态变量m和一个局部变量n，静态变量m的内存在整个程序完成之后释放，而局部变量n内存则随着函数的结束释放，因此每次进行函数时都会重新生成一个n变量，值自然不会变化，m变量在第一次进行func函数时就初始化完成了，并在函数第一次结束时就保存在了静态储存区，在第二遍进行func函数时进行m++，因此m=2。


## 4. 下面程序会出现什么结果？为什么会出现这样的结果？

```c
int main(int argc, char * argv[]) {
  char ch = 'A';
  int i = 65;
  unsigned int f = 33554433;
  *(int *)&f >>= 24;
  *(int *)&f = *(int *)&f + '?';
  printf("ch = %c i = %c f = %c\n", ch, i, *(int *)&f);
  return 0;
}
```
*(int *)&f相当于定义了一个指针并通过取值运算符取值，f的二进制为10000000000000000000000001，```c*(int *)&f >>= 24```操作将f二进制值右移24位，得到10即为2,此时f等于2。'?'的ASCII值为63，因此f=65。


## 5. 下面代码的运行输出结果是什么，并说说你的理解。

```c
int main(int argc, char *argv[]) {
  int a[2][2];
  printf("&a = %p\t&a[0] = %p\t&a[0][0] = %p\n", &a, &a[0], &a[0][0]);
  printf("&a+1 = %p\t&a[0]+1 = %p\t&a[0][0]+1= %p\n", &a+1, &a[0]+1, &a[0][0]+1);
  return 0;
}
```
输出结果为：
&a = 0x7fffffffde50     &a[0] = 0x7fffffffde50  &a[0][0] = 0x7fffffffde50
&a+1 = 0x7fffffffde60   &a[0]+1 = 0x7fffffffde58        &a[0][0]+1= 0x7fffffffde54
二维数组名取地址等于二维数组首元素地址等于二维数组中一维数组的首元素地址。
&a+1等于跨越整个二维数组的长度，&a[0]+1等于跨与整个一维数组的长度，&a[0][0]+1等于跨越二维数组中一个元素的长度。

## 6. 下列程序的功能是什么？有什么问题，你能找出问题并解决它吗？

```c
int* get_array() {
  int array[1121]; 
  for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
    array[i] = i;
  }
  return array;
}
int main(int argc, char *argv[]) { 
  int *p = get_array();
}
```
该程序定义了一个array函数，函数中定义了一个数组并通过for循环为数组中每一个元素赋值，并返回数组的地址。定义的数组是一个局部变量在函数运行结束后释放内存，因此返回的地址找不到对应的变量。只需要在int array[1121]前加上static，将其改变为一个静态变量。


## 7. 下面代码的运行输出结果是什么，并说说你的理解。

```c
int main(int argc, char *argv[]) {
  char str[] = "XiyouLinuxGroup"; 
  char *p = str; 
  char x[] = "XiyouLinuxGroup\t\106F\bamily";
  printf("%zu %zu %zu %zu\n", sizeof(str), sizeof(p), sizeof(x), strlen(x));
  return 0;
}
```
输出结果为：16 8 25 24
sizeof运算符计算字符串在内存中所占大小，strlen函数计算字符串本身长度。
由于字符串末尾附带\0因此sizeof（str）为16,p为指针占八个字节所以sizeof（p）为8，而\t将光标移到下一个制表位置（8的整数倍），\b将光标向前移动一位，因此sizeof(x)为25,strlen（x）为24。
## 8. 如下程序，根据打印结果，你有什么思考？

```c
int add(int *x, int y) {
  return *x = (*x^y) + ((*x&y)<<1);
}
int a;
int main(int argc, char *argv[]) {
  int b = 2020;
  if(add(&b, 1) || add(&a, 1)) {
  printf("XiyouLinuxGroup%d\n", b);
  printf("Waiting for y%du!\n", a);
  }
  if(add(&b, 1) && a++) {
  printf("XiyouLinuxGroup%d\n", b);
  printf("Waiting for y%du!\n", a);
}
  return 0;
} 
```
输出结果为：XiyouLinuxGroup2021
          Waiting for y0u!
奇数与1进行异或运算等于该数减一，偶数与1进行异或运算等于该数加一。
奇数与1进行按位与运算等于1，偶数与1进行异或运算等于0。


## 9. 在下段程序中，我们可以通过第一步打印出`a`的地址，假如在你的机器上面打印结果是`0x7ffd737c6db4`；我们在第二步用`scanf`函数将这个地址值输入变量`c`中；第三步，随机输入一个数字，请问最终输出了什么结果，你知道其中的原理吗？

```c
void func() { 
  int a = 2020;
  unsigned long c;
  printf("%p\n", &a);
  printf("我们想要修改的地址：");
  scanf("%lx", &c);
  printf("请随便输入一个数字：");
  scanf("%d", (int *)c);
  printf("a = %d\n", a);
}
```
该程序最终将a的值改变成了随机输入的数字。
func函数首先打印了a的地址，在将地址的16进制值赋值给无符号长整形c，再将c进行强制类型转换变成指针并将输入的随机数录入到c中，最后变量a的地址就变成了c，并且值为输入的随机值。

## 10. 请问一个C语言程序从源代码到可执行文件中间会进行哪些过程，你能简单描述一下每个环节都做了什么事情吗？
1.进行预处理：展开头文件，进行宏替换，去掉注释等
  将所有的“#define”删除，并且展开所有的宏定义。
  处理所有条件预编译指令。
  处理#include预编译指令，将包含的文件插入到该预编译指令的位置。
  删除所有的注释。
  添加行号和文件名标识，以便于编译时编译器产生的调式用的行号信息及用于编译时产生编译错误或警告时能够显示行号。
2.编译:把预处理完的文件进行一系列词法分析、语法分析、语义分析及优化后生产相应的汇编代码文件，并检查其中的语法。
3.汇编：将代码转变为机器能读懂的语言。
4.链接 合成可执行的程序，链接地址并分配空间。

## 11. 请解释一下这行代码做了什么？

```c
puts((char*)(int const[]){
0X6F796958,0X6E694C75,0X72477875,
0X3270756F,0X313230,0X00000A
});
```
输出结果为：XiyouLinuxGroup2021
这行代码输出了一个字符串，根据每个字符对应的16进制ASCII码输出该字符，而我们常用的X86结构是小端模式，而KEIL C51则为大端模式，小端模式将低位存入低地址，例如0X6F796958,的存储顺序就变成了0X5869796F，读数据永远是从低地址开始，那么输出时就变成了Xiyo这四个字符。

## 12. 请随机输入一串字符串，你能解释一下输出结果吗？

```c
int main(int argc, char *argv[]) {
  char str[1121];
  int key;
  char t;
  fgets(str, 1121, stdin);
  for(int i = 0; i < strlen(str) - 1; i++) {
    key = i;
    for(int j = i + 1; j < strlen(str); j++) {
      if(str[key] > str[j]) {
        key = j;
      }
    } 
    t = str[key];
    str[key] = str[i];
    str[i] = t;
  } 
  puts(str);
  return 0;
}
```
程序将随机输入的字符串进行排序。首先通过fgets将输入的字符串输入到字符数组str中，再通过两层for循环依次将str[i]之后的数进行两两比较，找出str[i]之后最小的数，并交换其位置，完成后进入下一次循环i+1,直到str[i]为倒数第二个字符。

## 13. 用循环和递归求`Fibonacci`数列，你觉得这两种方式那种更好？说说你的看法。如果让你求`Fibonacci`数列的第100项，你觉得还可以用常规的方法求解吗？请试着求出前100项的值（tip大数运算）。
我认为递归更好，递归更加快捷方便,但是递归在计算较大值是运算很慢，循环会更加快捷。
代码如下：
#include<stdio.h>
double fib(int n);
double fib(int n)
{
    double a=1,b=1,c=1;
    while(n>2)
    {
        c=a+b;
        a=b;
        b=c;
        n--;
    }
    return c;
}
int main()
{
    int n;
    scanf("%d",&n);
    printf("%.0lf",fib(n));
}

## 14. Linux 实操题

> 请通过命令创建一个目录，在该目录中创建几个后缀为`.Linux`的文件，然后通过命令查询这几个文件的基本属性信息（如文件大小，文件创建时间等），之后使用命令查看该目录下文件名含有“`.Linux`”的文件的数量（不包括子目录下的文件），把得到的数字写入到一个文件中，最后删除此目录。
创建目录：mkdir 123
创建文件：touch 123/XXX.Linux
查询信息；stat  XXX.Linux
查看目录下文件数量：cd 123
                ls -l|grep "^-"|grep "*Linux"|wc -l > 111
                rm -rf 123
      


