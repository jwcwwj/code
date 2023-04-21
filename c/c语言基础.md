

# 1.函数：

```c
//test.h的内容：放置函数的申明
#ifndef __TEST_H__
#define __TEST_H__
//函数Add的声明
int Add(int x, int y);
#endif //__TEST_H__

//test.c的内容：放置函数的实现
#include "test.h"
//函数Add的实现
int Add(int x, int y)
{
	return x+y;
}
```

# 2.数组：

```c
int count = 10;
int arr2[count];//数组时候可以正常创建？   error  不允许count是变量
//数组创建， [] 中要给一个常量才可以，不能使用变量
```

```c
int main()
{ 
	char arr1[] = "abc";
	char arr2[3] = { 'a','b','c' };
	printf("%s\n", arr1);				//abc
	printf("%s\n", arr2);				//abc烫烫烫烫烫bc
	printf("%d\n", sizeof(arr1));		//4
	printf("%d\n", sizeof(arr2));		//3
	printf("%d\n", strlen(arr1));		//3
	printf("%d\n", strlen(arr2));		//15
	return 0;
}
//长度：'\0'结束前的长度，不包括'\0'
//字节：包括'\0'，已经初始化的（可见的）
```

```c
int main()
{
	int arr[10] = { 1,2,3,4,5 };
	printf("%p\n", arr);		//010FFD30
	printf("%p\n", &arr[0]);	//010FFD30
	printf("%d\n", *arr);		//1
	return 0;
}
//1. sizeof(数组名)，计算整个数组的大小，sizeof内部单独放一个数组名，数组名表示整个数组。
//2. &数组名，取出的是数组的地址。&数组名，数组名表示整个数组。
//除此1,2两种情况之外，所有的数组名都表示数组首元素的地址。
```

# 3.操作符：

```c
//对于移位运算符，不要移动负数位，这个是标准未定义的。  	 经过测验后发现移位负数改变之后的值是0
//位操作数的操作数必须是整数

//实现两个数的交换：
int main()
{
    //方法1：
	int a = 10;
	int b = 20;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	printf("%d\n", a);
	printf("%d\n", b);
	return 0;
}

int main()
{
    //方法2：
	int a = 10;
	int b = 20;
	int temp = a;;
	a = b;
	b = temp;
	printf("%d\n", a);
	printf("%d\n", b);
	return 0;
}

int main()
{
    //方法3：
	int a = 10;
	int b = 20;
	a = a + b;
	b = a - b;
	a = a - b;
	printf("%d\n", a);
	printf("%d\n", b);
	return 0;
}
//输出结果：a的结果是20，b的结果是10；

//求一个整数存储在内存中的二进制中1的个数
int main()
{
    //方法1：
	int num = 10;	//00001010
	int count = 0;	//统计1的个数
	while(num)
	{
		if (num % 2 == 1)	//末尾是1
		{
			count++;
		}
		num = num >> 1;		
	}
	printf("count = %d", count);	//2
	return 0;
}

int main()
{
	//方法2:
	int num = 10;		//00001010
	int i;
	int count = 0;//计数
	for (i = 0; i < 32; i++)
	{
		if (((num >> i) & 1) == 1)			//逐位与1进行比较
			count++;
	}
	printf("二进制中1的个数 = %d\n", count);
	return 0;
}

int main()
{
	//方法3:效率最高
	int num = 10;		//00001010
	int count = 0;//计数
	while(num)
	{
		count++;
		num = num & (num - 1);	//有几个1比较几次，小效率最高		 
	}
	printf("二进制中1的个数 = %d\n", count);
	return 0;
}

int a = 10;
int x = 0;
int y = 20;
a = x = y+1;//连续赋值，在c语言中是可以连续赋值的
//上面这条语句相当于
x = y+1;
a = x;

int main()
{
	int a = -10;
	int *p = NULL;
	printf("%d\n", !2);		//0
	printf("%d\n", !0);		//1
	a = -a;
	p = &a;
	printf("%d\n", sizeof(a));		//4
	printf("%d\n", sizeof(int));	//4
	printf("%d\n", sizeof a);		//4
	printf("%d\n", sizeof int);		//error
	return 0;
}

int main()
{
	int i = 0, a = 0, b = 2, c = 3, d = 4;
	i = a++ && ++b && d++;
	//i = a++||++b||d++;
	printf("a = %d\n b = %d\n c = %d\nd = %d\n", a, b, c, d);
	return 0;
}
//输出结果：a是1，b是2，c是3，d是4，i是0

//表达式求值:
//表达式求值的顺序一部分是由操作符的优先级和结合性决定。
//同样，有些表达式的操作数在求值的过程中可能需要转换为其他类型。
//隐式类型转换:
//C的整型算术运算总是至少以缺省整型类型的精度来进行的。
//为了获得这个精度，表达式中的字符和短整型操作数在使用之前被转换为普通整型，这种转换称为整型提升。
//整型提升的意义：
//表达式的整型运算要在CPU的相应运算器件内执行，CPU内整型运算器(ALU)的操作数的字节长度
//一般就是int的字节长度，同时也是CPU的通用寄存器的长度。
//因此，即使两个char类型的相加，在CPU执行时实际上也要先转换为CPU内整型操作数的标准长度。
//通用CPU（general-purpose CPU）是难以直接实现两个8比特字节直接相加运算（虽然机器指令中可能有这种字节相加指令）。
//所以，表达式中各种长度可能小于int长度的整型值，都必须先转换为int或unsigned int，然后才能送入CPU去执行运算。
char a,b,c;
...
a = b + c;
//b和c的值被提升为普通整型，然后再执行加法运算。
//加法运算完成之后，结果将被截断，然后再存储于a中。
//如何进行整体提升呢？	整形提升是按照变量的数据类型的符号位来提升的。

int main()
{
	char c = 1;
	printf("%u\n", sizeof(c));	//1
	printf("%u\n", sizeof(+c));	//4
	printf("%u\n", sizeof(!c));	//1		//不是很理解
	printf("%u\n", sizeof(-c));	//4
	return 0;
}
//备注：c只要参与表达式运算,就会发生整形提升,表达式 +c ,就会发生提升,所以 sizeof(+c) 是4个字节。
//表达式 -c 也会发生整形提升,所以 sizeof(-c) 是4个字节,但是 sizeof(c) ,就是1个字节。

//算数转换：从下向上转换没有精度损失，从上向下转换有精度损失；
//long double
//double
//float
//unsigned long int
//long int
//unsigned int
//int
float f = 3.14;
int num = f;//隐式转换，会有精度丢失
```

# 4.指针：

```c
//一维数组传参
void test(int arr[]){}
//void test(int arr[10]){}
//void test(int *arr){}
//void test2(int *arr[20]){}
void test2(int **arr){}
int main()
{
	int arr[10] = { 0 };
	int *arr2[20] = { 0 };
	test(arr);
	test2(arr2);
	//经过测试都是对的
}

//二维数组传参
//void test(int arr[3][5]){}
//void test(int arr[][]){}	//error
//void test(int arr[][5]){}
//void test(int *arr){}
//void test(int* arr[5]){}
//void test(int(*arr)[5]){}
void test(int **arr){}
int main()
{
    //上面的除了error的都是对的
	int arr[3][5] = { 0 };
	test(arr);
}

//一级指针传参
void print(int *p, int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d\n", *(p + i));
	}
}
int main()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9 };
	int *p = arr;
	int sz = sizeof(arr) / sizeof(arr[0]);
	//一级指针p，传给函数
	print(p, sz);
	return 0;
}

//二级指针传参
void test(int** ptr)
{
	printf("num = %d\n", **ptr);
}

int main()
{
	int n = 10;
	int*p = &n;
	int **pp = &p;
	test(pp);		//n
	test(&p);		//n
	return 0;
}

void test(char **p)
{ }
int main()
{
	char c = 'b';
	char*pc = &c;
	char**ppc = &pc;
	char* arr[10];
	test(&pc);
	test(ppc);
	test(arr);//Ok?  可以
	return 0;
    //三个传参都可以
}

//复杂指针:右左法则
int (*parr3[10])[5];	//parr是保存数组地址的数组，10个元素（数组指针指向数组）
int *(*(*fun)(int*))[10];	//fun先向右看是括号，再向左看是指针，再向右看是括号，说明这个指针是指向函数的，括号里面是函数的参数，再向左看说明所指函数的返回值是指针，遇到括号向右看遇到方括号说明这个函数的返回的指针是指向数组的，数组元素10个，再往左看发现这个数组元素的类型是整形指针；（总结是返回数组指针的函数指针）
int(*func)(int*,int(*)(int*));		//func是一个函数指针，所指函数的特点是有两个参数，第一个参数为整形指针，第二个参数为函数指针，第二个函数指针的特点是参数是一个整形指针，返回值是int，func指向的函数的返回值为int型；
int(*func[5])(int*);	//func是数组，有5个元素，数组元素类型是指针类型，每个数组元素指针指向函数的，指向的函数参数是int*，返回值是int；
int (*(*func)[5])(int*);	//func是指针，func指针指向数组，数组有5个元素，元素类型是指针，数组元素是指针，指向函数，指向的函数参数类型是int*，返回值是int；
int (*(*func)[5])(int*);	//func是指针，func指针指向数组，这个指向的数组有5个元素，元素类型是指针，数组元素指针指向函数，指向的函数的参数是int*，返回值是int；
int (*(*func)(int*)) [5];	//func是一个函数指针，指向一个参数为int*返回值为数组指针的函数，函数返回值指向有5个int类型元素的数组；
int*(*func(int*))[5];	//func是函数，func是参数为int*返回值是数组指针的函数，返回值指向有5个类型为int*的数组；

(*(void (*)())0)();		//把0转换为没有返回值没有参数的函数指针进行解引用，解引用之后作为函数名（函数名是入口地址）；
void (*signal(int , void(*)(int)))(int);	//signal是一个函数，这个函数有两个参数，第一个参数是int，第二个参数是函数指针，返回值是一个函数指针，返回的函数指针指向一个参数为int，无返回值的函数；
//上面的代码简化为2行
typedef void(*pfun_t)(int);
pfun_t signal(int, pfun_t);

函数指针数组：int (*parr1[10]])();
函数指针数组的用途：转移表
//例子：计算器
int add(int a, int b)
{
	return a + b;
}
int sub(int a, int b)
{
	return a - b;
}
int mul(int a, int b)
{
	return a * b;
}
int divi(int a, int b)
{
	return a / b;
}

int main()
	{
	//不用转移表的
    	int x, y;
		int input = 1;
		int ret = 0;
		do
		{
			printf("*************************\n");
			printf(" 1:add 2:sub \n");
			printf(" 3:mul 4:div \n");
			printf("*************************\n");
			printf("请选择：");
			scanf("%d", &input);
			switch (input)
			{
			case 1:
				printf("输入操作数：");
				scanf("%d %d", &x, &y);
				ret = add(x, y);
				printf("ret = %d\n", ret);
				break;
			case 2:
				printf("输入操作数：");
				scanf("%d %d", &x, &y);
				ret = sub(x, y);
				printf("ret = %d\n", ret);
				break;
			case 3:
				printf("输入操作数：");
				scanf("%d %d", &x, &y);
				ret = mul(x, y);
				printf("ret = %d\n", ret);
				break;
			case 4:
				printf("输入操作数：");
				scanf("%d %d", &x, &y);
				ret = divi(x, y);
				printf("ret = %d\n", ret);
				break;
			case 0:
				printf("退出程序\n");
				break;
			default:
				printf("选择错误\n");
				break;
			}
		} while (input);
		return 0;
}

int main()
{
    //用转移表的，优势是好扩展，直接在函数指针数组上添加就好了，不用修改switch语句
	int x, y;
	int input = 1;
	int ret = 0;
	int(*p[5])(int x, int y) = { 0, add, sub, mul, divi }; //转移表  函数指针数组
	while (input)
	{
		printf("*************************\n");
		printf(" 1:add 2:sub \n");
		printf(" 3:mul 4:div \n");
		printf("*************************\n");
		printf("请选择：");
		scanf("%d", &input);
		if ((input <= 4 && input >= 1))
		{
			printf("输入操作数：");
			scanf("%d %d", &x, &y);
			ret = (*p[input])(x, y);
			printf("ret = %d\n", ret);
		}
		else
			printf("输入有误\n");
	}
	return 0;
}
    
//指向函数指针数组的指针：指向函数指针数组的指针是一个指针，指针指向一个数组，数组的元素都是函数指针；
void test(const char* str)
{
	printf("%s\n", str);
}

int main()
{
	//函数指针pfun
	void(*pfun)(const char*) = test;
	//函数指针的数组pfunArr
	void(*pfunArr[5])(const char* str);
	pfunArr[0] = test;
	pfunArr[1] = test;
	//指向函数指针数组pfunArr的指针ppfunArr
	void(*(*ppfunArr)[10])(const char*) = &pfunArr;
	return 0;
}

//回调函数：回调函数就是一个通过函数指针调用的函数。如果你把函数的指针（地址）作为参数传递给另一个函数，当这个指针被用来调用其所指向的函数时，我们就说这是回调函数。回调函数不是由该函数的实现方直接调用，而是在特定的事件或条件发生时由另外的一方调用的，用于对该事件或条件进行响应;
//以排序函数为实例来学习回调函数：
//函数库中实现回调函数
//qosrt函数的使用者得实现一个比较函数 
int int_cmp(const void * p1, const void * p2)
{
    //qsort函数中规定实现比较函数是按递增排序的
	return (*(int *)p1 - *(int *)p2);
}

int main()
{
	int arr[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
	int i = 0;
	qsort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), int_cmp);		//数组 数组的个数 元素的大小 比较函数
	for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}
//自己模拟函数库实现一个冒泡排序函数：
int int_cmp(const void * p1, const void * p2)
{
	return (*(int *)p1 - *(int *)p2);
}

void _swap(void *p1, void * p2, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		char tmp = *((char *)p1 + i);
		*((char *)p1 + i) = *((char *)p2 + i);
		*((char *)p2 + i) = tmp;
	}
}

void bubble(void *base, int count, int size, int(*cmp)(void *, void *))
{
	int i = 0;
	int j = 0;
	for (i = 0; i < count - 1; i++)
	{
		for (j = 0; j < count - i - 1; j++)
		{
			if (cmp((char *)base + j * size, (char *)base + (j + 1)*size) > 0)
			{
				_swap((char *)base + j * size, (char *)base + (j + 1)*size, size);
			}
		}
	}
}

int main()
{
	int arr[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
	//char *arr[] = {"aaaa","dddd","cccc","bbbb"};
	int i = 0;
	bubble(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), int_cmp);
	for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}

//指针和数组笔试题：
	//一维数组
	int a[] = { 1,2,3,4 };				
	printf("%d\n", sizeof(a));			//16 数组大小
	printf("%d\n", sizeof(a + 0));		//4	 把a当做地址，地址的大小4
	printf("%d\n", sizeof(*a));			//4	 第一个元素
	printf("%d\n", sizeof(a + 1));		//4  地址
	printf("%d\n", sizeof(a[1]));		//4  第二个元素
	printf("%d\n", sizeof(&a));			//4  地址
	printf("%d\n", sizeof(*&a));		//16 整个数组
	printf("%d\n", sizeof(&a + 1));		//4 地址
	printf("%d\n", sizeof(&a[0]));		//4 地址
	printf("%d\n", sizeof(&a[0] + 1));	//4 地址

	//字符数组
	char arr[] = { 'a','b','c','d','e','f' };	
	printf("%d\n", sizeof(arr));			//6	数组大小
	printf("%d\n", sizeof(arr + 0));		//4 地址
	printf("%d\n", sizeof(*arr));			//1 第一个元素
	printf("%d\n", sizeof(arr[1]));			//1 第二个元素
	printf("%d\n", sizeof(&arr));			//4 地址
	printf("%d\n", sizeof(&arr + 1));		//4 地址
	printf("%d\n", sizeof(&arr[0] + 1));	//4 地址
	printf("%d\n", strlen(arr));			//随机数  '\0'不确定
	printf("%d\n", strlen(arr + 0));		//随机数
	printf("%d\n", strlen(*arr));			//错误 字符不能求长度
	printf("%d\n", strlen(arr[1]));			//错误 字符不能求长度
	printf("%d\n", strlen(&arr));			//随机数 '\0'不确定
	printf("%d\n", strlen(&arr + 1));		//随机数 '\0'不确定
	printf("%d\n", strlen(&arr[0] + 1));	//随机数 '\0'不确定
	
	char arr[] = "abcdef";				
	printf("%d\n", sizeof(arr));		//7
	printf("%d\n", sizeof(arr + 0));	//4
	printf("%d\n", sizeof(*arr));		//1
	printf("%d\n", sizeof(arr[1]));		//1
	printf("%d\n", sizeof(&arr));		//4
	printf("%d\n", sizeof(&arr + 1));	//4
	printf("%d\n", sizeof(&arr[0] + 1));//4
	printf("%d\n", strlen(arr));		//6
	printf("%d\n", strlen(arr + 0));	//6
	printf("%d\n", strlen(*arr));		//错误 不能求字符的长度
	printf("%d\n", strlen(arr[1]));		//错误
	printf("%d\n", strlen(&arr));		//6
	printf("%d\n", strlen(&arr + 1));	//随机值 加了1个数组的长度
	printf("%d\n", strlen(&arr[0] + 1));//5

	char *p = "abcdef";	
	printf("%d\n", sizeof(p));			//4 指针
	printf("%d\n", sizeof(p + 1));		//4 指针
	printf("%d\n", sizeof(*p));			//1 第一个元素
	printf("%d\n", sizeof(p[0]));		//1 第一个元素
	printf("%d\n", sizeof(&p));			//4 指针
	printf("%d\n", sizeof(&p + 1));		//4 指针
	printf("%d\n", sizeof(&p[0] + 1));	//4 指针
	printf("%d\n", strlen(p));			//6
	printf("%d\n", strlen(p + 1));		//5
	printf("%d\n", strlen(*p));			//错误 字符不能求长度
	printf("%d\n", strlen(p[0]));		//错误 字符不能求长度
	printf("%d\n", strlen(&p));			//不确定
	printf("%d\n", strlen(&p + 1));		//不确定
	printf("%d\n", strlen(&p[0] + 1));	//5

	//二维数组
	int a[3][4] = { {-1,-2,-3,-4},{1,2,3,4},{0} };
	printf("%d\n", sizeof(a));				//48 二维数组
	printf("%d\n", sizeof(a[0][0]));		//4  第一个元素
	printf("%d\n", sizeof(a[0]));			//16 一维数组
	printf("%d\n", sizeof(a[0] + 1));		//4  指针
	printf("%d\n", sizeof(*(a[0] + 1)));	//4  第一行第二个元素
	printf("%d\n", sizeof(a + 1));			//4  地址
	printf("%d\n", sizeof(*(a + 1)));		//16 第二行的值
	printf("%d\n", sizeof(&a[0] + 1));		//4  地址
	printf("%d\n", sizeof(*(&a[0] + 1)));	//16 第二行的值
	printf("%d\n", sizeof(*a));				//16 首元素是第一行
	printf("%d\n", sizeof(a[3]));			//16 越界，不能访问，但是字节大小固定
	printf("%d\n", *(a[0] + 1));			//-2  值
	printf("%d\n", *(a + 1));				//3996840 地址
//总结数组名的意义：
//1. sizeof(数组名)，这里的数组名表示整个数组，计算的是整个数组的大小。
//2. &数组名，这里的数组名表示整个数组，取出的是整个数组的地址。
//3. 除此之外所有的数组名都表示首元素的地址。

int main()
{
	int a[5] = { 1, 2, 3, 4, 5 };
	int *ptr = (int *)(&a + 1);
	printf("%d,%d", *(a + 1), *(ptr - 1));		//2 5
	return 0;
}

//由于还没学习结构体，这里告知结构体的大小是20个字节
struct Test
{
	int Num;
	char *pcName;
	short sDate;
	char cha[2];
	short sBa[4];
}*p;

//假设p 的值为0x100000。 如下表表达式的值分别为多少？
int main()
{
	printf("%p\n", p);							//00000000
	printf("%p\n", p + 0x1);					//00000014 加一个结构体的大小  
	printf("%p\n", (unsigned long)p + 0x1);		//00000001 加一个整数1（数学类型上的1）
	printf("%p\n", (unsigned int*)p + 0x1);		//00000004 加一个指针类型的大小
	printf("%p\n", (double*)p + 0x1);			//00000008 加一个指针类型的大小
	return 0;
}

int main()
{
	int a[4] = { 1, 2, 3, 4 };
	//在内存中存储：01 00 00 00 02 00 00 00 03 00 00 00 04 00 00 00
	int *ptr1 = (int *)(&a + 1);		//跨越1个数组
	int *ptr2 = (int *)((int)a + 1);	//按字节算，起始位置加一个字节
	printf("%x,%x", ptr1[-1], *ptr2);	//4 02000000
	return 0;
}

int main()
{
	int a[3][2] = { (0, 1), (2, 3), (4, 5) };		//{{1,3,5},{0,0,0}}
	int *p;
	p = a[0];		//第一行
	printf("%d", p[0]);		//第一行第一个   1
	return 0;
}

int main()
{
	int a[5][5];
	int(*p)[4];			//一行4个元素
	p = a;
	printf("%p,%d\n", &p[4][2] - &a[4][2], &p[4][2] - &a[4][2]);	//FFFFFFFC(-4) -4
	//地址可以相减，不可以相加
    //原码：1000 0000 0000 0000 0000 0000 0000 0100
	//补码：1111 1111 1111 1111 1111 1111 1111 1011 
	//反码：1111 1111 1111 1111 1111 1111 1111 1100
	//		F	 F    F	   F	F	 F	  F    C
	return 0;
}

int main()
{
	int aa[2][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int *ptr1 = (int *)(&aa + 1);
	int *ptr2 = (int *)(*(aa + 1));					//有没有*都无所谓
	printf("%d,%d", *(ptr1 - 1), *(ptr2 - 1));		//10  5
	return 0;
}

int main()
{
	char *a[] = { "work","at","alibaba" };	
	char**pa = a;				//和&a一样
	int aa[] = { 1,2,3 }; 
	int* aaa = &aa;				//和aa一样
	printf("%d\n", *aaa);		//1
	pa++;
	printf("%d\n", sizeof(a));  //12   3个char*
	printf("%s\n", *pa);		//at
	return 0;
}

int main()
{
	char *c[] = { "ENTER","NEW","POINT","FIRST" };
	char**cp[] = { c + 3,c + 2,c + 1,c };
	char***cpp = cp;
	printf("%s\n", **++cpp);			//POINT
	printf("%s\n", *--*++cpp + 3);		//ER
	printf("%s\n", *cpp[-2] + 3);		//ST
	printf("%s\n", cpp[-1][-1] + 1);	//EW
	return 0;
}
```

# 5.字符串函数的了解和实现：

## 5.1strlen：求字符串长度

```c
//字符串以'\0'作为结束标志，strlen函数返回的是在字符串中'\0'前面出现的字符个数（不包含'\0')。
//参数指向的字符串必须要以'\0'结束。
//注意函数的返回值为size_t，是无符号的（易错）
//函数原型：size_t strlen( const char *string );
//返回值：这些函数都返回字符串中的字符数，不包括终端NULL。没有保留返回值来指示错误。
//参数：以null结尾的const字符串
//模拟实现：
//方法1：计数器方式
size_t my_strlen(const char *string)
{
	assert(string);
	size_t count = 0;
	char* str = string;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}

//方法2：指针方式
size_t my_strlen(const char *string)
{ 
	assert(string);
	char* str = string;
	while (*str != '\0')
	{
		str++;
	}
	return str - string;
}

//方法3：不创建临时变量
size_t my_strlen(const char *string)
{
	assert(string);
	if (*string == '\0')
		return 0;
	return my_strlen(string + 1) + 1;
}

//测试：
int main()
{
    char *str = "hello world";
	printf("%d\n", my_strlen(str));
	return 0;
}
```

## 5.2strcpy：字符串拷贝（长度不受限制的字符串函数）

```c
//将源指向的C字符串复制到目标指向的数组中，包括终止null。
//源字符串必须以 '\0' 结束。
//将源字符串中的 '\0' 拷贝到目标空间。
//目标空间必须足够大，以确保能存放源字符串。
//目标空间必须可变。
//函数原型：char *strcpy( char *strDestination, const char *strSource );
//返回值：返回目标字符串。没有保留返回值来指示错误。
//参数：目标字符串（内存缓冲区） 源字符串
//strcpy函数的作用是将strSource(包括结束空字符)复制到strDestination指定的位置。复制或追加字符串时不执行溢出检查。如果源字符串和目标字符串重叠，则strcpy的行为未定义。 
//模拟实现：
char* my_strcpy(char *strDestination, const char *strSource)	//第一个参数：目标字符串（内存缓存区）   第二个参数：源字符串
{
	assert(strDestination);
	assert(strSource);
	char* dest = strDestination;
	const char* str = strSource;
	while (*dest++ = *str++)
	{
	 
	}
	return strDestination;
}

//测试：
int main()
{
	char dest[20] = "hello";
	char *str = "worl"; 
	my_strcpy(dest, str);
	printf("%s\n", dest);
	return 0;
}
```

## 5.3strcat：字符串追加（长度不受限制的字符串函数）

```c
//将源字符串的副本追加到目标字符串。中的终止空字符目标被源的第一个字符覆盖，并且在末尾包含一个空字符由目标中两者的连接形成的新字符串。
//源字符串必须以 '\0' 结束。
//目标空间必须有足够的大，能容纳下源字符串的内容。
//目标空间必须可修改。
//函数原型：char *strcat( char *strDestination, const char *strSource );
//返回值：这些函数都返回目标字符串(strDestination)。没有保留返回值来指示错误。
//参数：以空结束的目标字符串（内存缓冲区）  以空结束的源字符串
//strcat函数将strSource附加到strDestination，并以空字符结束结果字符串。strSource的初始字符覆盖strDestination的终止空字符。
//复制或追加字符串时不执行溢出检查。如果源字符串和目标字符串重叠，则strcat的行为未定义。
//模拟实现：
char *my_strcat(char *strDestination, const char *strSource)
{
	assert(strDestination);
	assert(strSource);
	char* dest = strDestination;
	const char* str = strSource;
	//找到dest的末尾
	while (*dest)
	{
		dest++;
	}
	while (*dest++ = *str++)
	{

	}
	return strDestination;
}

//测试：
int main()
{
	char dest[20] = "hello";
	char *str = "world"; 
	my_strcat(dest, str);
	printf("%s\n", dest);
    printf("%s\n", my_strcat(dest, str));
	return 0;
}
```

## 5.4strcmp：字符串比较（长度不受限制的字符串函数）

```c
//strcmp函数按字典顺序比较string1和string2，并返回一个指示它们之间关系的值。
//以string2为参照目标比较string1是比string2大还是小还是相等。
//函数原型：int my_strcmp(const char *string1, const char *string2);
//返回值：第一个字符串大于第二个字符串，则返回大于0的数字,第一个字符串等于第二个字符串，则返回0,第一个字符串小于第二个字符串，则返回小于0的数字。
//参数：以空结束的两个字符串
//模拟实现：
//方法1：
int my_strcmp(const char *string1, const char *string2)
{
	assert(string1);
	assert(string2);
	const char* str1 = string1;
	const char* str2 = string2;
	int ret = 0;
	while (*str1 && *str2)
	{
		if (*str1 > *str2)
		{
			ret = 1;
			break;
		}
		else if (*str1 < *str2)
		{
			ret = -1;
			break;
		} 
		str1++;
		str2++;
	}
	if (*str1)
		ret = 1;
	if (*str2)
		ret = -1;
	return ret;
}

//方法2：
int my_strcmp(const char *string1, const char *string2)
{
	assert(string1);
	assert(string2);
	const char* str1 = string1;
	const char* str2 = string2;
	int ret = 0;
	while (!(ret = (*str1++ - *str2++)))		//null字符是0
	{
		;
	}
	if (ret < 0)
		ret = -1;
	else if (ret > 0)
		ret = 1;
	return ret;
}

//方法3：
int my_strcmp(const char *string1, const char *string2)
{
	assert(string1);
	assert(string2);
	const char* str1 = string1;
	const char* str2 = string2;
	int ret = 0;
	while (*str1 != '\0' || *str2 != '\0')		//'\0'字符是0
	{
		if (*str1 - *str2 != 0)
			break;
		str1++;
		str2++;
	}
	ret = *str1 - *str2;
	return ret;
}

//测试：int main()
{
	char* str1 = "hello";
	char* str2 = "helloaa";
	int ret = my_strcmp(str1,str2);
	if (ret == 0)
	{
		printf("str1 == str2");
	}
	else if (ret < 0)
	{
		printf("str1 < str2");
	{
		printf("str1 > str2");
	}
	return 0;
}
```

## 5.5strncpy：字符串拷贝（长度受限制的字符串函数）

```c
//将源文件的num个字符复制到目标文件。
//拷贝num个字符从源字符串到目标空间。
//如果源字符串的长度小于num，则拷贝完源字符串之后，在目标的后边追加0，直到num个。
//函数原型：char *strncpy( char *strDest, const char *strSource, size_t count );
//返回值：返回strDest。没有保留返回值来指示错误。
//参数：目标字符串 源字符串 要复制的字符数
//模拟实现：
char *my_strncpy(char *strDest, const char *strSource, size_t count)
{
	assert(strDest && strSource);
	char* dest = strDest;
	const char* str = strSource;
	while (count--)
	{
		*dest++ = *str++;
	}
	*dest = '\0';
}

//测试：
int main()
{
	char str1[20] = "hello";
	char* str2 = "helloaa";
	my_strncpy(str1, str2, 3);
	printf("%s\n", str1);
	return 0;
}
```

## 5.6strncat：字符串连接（长度受限制的字符串函数） 

```c
//将源文件num字符附加到目标文件，加上一个终止空字符。如果source中C字符串的长度小于num，则只复制终止null字符之前的内容
//函数原型：char *strncat( char *strDest, const char *strSource, size_t count );
//返回值：一个指向目标字符串的指针。没有保留返回值来指示错误。
//参数：以空结束的目标字符串  以空结束的源字符串  要追加的字符数
//模拟实现：
char* my_strncat(char *string1, const char *string2, size_t count)
{
	assert(string1 && string2);
	char* str1 = string1;
	const char* str2 = string2;
	
	while (*str1)
		str1++;

	while(count-- > 0)
	{

		*str1++ = *str2++;
	}
	*str1 = '\0';
	 
	return string1;
}
 
//测试：
int main()
{
	char str1[20] = "hello";
	char* str2 = "helloaa";
	my_strncat(str1,str2,3);
	printf("%s\n",str1);
	return 0;
}

```

## 5.7strncmp：字符串比较（长度受限制的字符串函数）

```c
//strcmp函数按字典顺序比较string1和string2，并返回一个指示它们之间关系的值。
//以string2为参照目标比较string1是比string2大还是小还是相等。 
//函数原型：int strncmp( const char *string1, const char *string2, size_t count );
//返回值：第一个字符串大于第二个字符串，则返回大于0的数字,第一个字符串等于第二个字符串，则返回0,第一个字符串小于第二个字符串，则返回小于0的数字。
//参数：以空结束的两个字符串，要比较的字符数。
//模拟实现：
int my_strncmp(const char *string1, const char *string2, size_t count)
{
	assert(string1 && string2);
	const char* str1 = string1;
	const char* str2 = string2;
	int ret = 0;
	while (--count > 0)
	{
		if (*str1 - *str2 != 0)
			break;
		str1++;
		str2++;
		//count--;
	}
	ret = *str1 - *str2;
	return ret;
}
 
//测试：
int main()
{
	char* str1 = "hello";
	char* str2 = "helloaa";
	int ret = my_strncmp(str1,str2,3);
	if (ret == 0)
	{
		printf("str1 == str2");
	}
	else if (ret < 0)
	{
		printf("str1 < str2");
	}
	else
	{
		printf("str1 > str2");
 	}
	return 0;
}

```

## 5.8strstr：字符串查找

```c
//strstr函数返回一个指向strCharSet在string中第一次出现的指针。搜索不包括终止空字符。
//函数原型：char *strstr( const char *string, const char *strCharSet );
//返回值：这些函数都返回一个指向strCharSet在string中第一次出现的指针，如果strCharSet没有出现在string中，则返回NULL。
//如果strCharSet指向一个长度为零的字符串，则函数返回string。（返回第一次找到指针后面所有的字符）
//参数：要搜索的以空结束的字符串  子字符串
//模拟实现：
char *my_strstr(const char* str1, const char* str2)
{
	assert(str1);
	assert(str2);
	char *cp = (char*)str1;
	char *substr = (char *)str2;
	char *s1 = NULL;
	if (*str2 == '\0')
		return str1;		//如果str2指向一个长度为零的字符串，则函数返回str1。
	while (*cp)
	{
		s1 = cp;
		substr = str2;
		while (*s1 && *substr && (*s1 == *substr))
		{
			s1++;
			substr++;
		}
		if (*substr == '\0')
			return cp;
		cp++;
	}
	return NULL;			//如果str1没有出现在str2中，则返回NULL。
} 

//库函数实现：
char *strstr(const char *haystack, const char *needle) {
	size_t needle_len = strlen(needle);
	if (!needle_len)
		return (char*)haystack;
	const char *hp = haystack;
	while ((hp = strchr(hp, *needle)) != NULL) {
		if (!memcmp(hp, needle, needle_len))
			return (char*)hp;
		hp++;
	}
	return NULL;
}

//测试：
int main()
{
	char str[] = "This is a simple string";
	char * pch;
	char* ptr = my_strstr(str, "ls");
	printf("%s\n", ptr);
	return 0;
}
```

## 5.9strtok：字符串查找

```c
//查找字符串中的下一个标记。
//函数原型：char *strtok( char *strToken, const char *strDelimit );
//返回值：所有这些函数都返回一个指向strToken中找到的下一个令牌的指针。当没有找到更多的令牌时，它们返回NULL。
//每次调用都通过为遇到的每个分隔符替换一个NULL字符来修改strToken。
//参数：strToken:包含令牌的字符串,指定一个字符串，它包含了0个或者多个由sep字符串中一个或者多个分隔符分割的标记。	
//strDelimit:分隔符字符集,是个字符串，定义了用作分隔符的字符集合
//strtok函数查找strToken中的下一个令牌。strDelimit中的字符集指定在当前调用的strToken中可能找到的令牌分隔符。
//在第一次调用strtok时，函数跳过前导分隔符并返回指向strToken中第一个令牌的指针，用空字符终止令牌。
//通过对strtok的一系列调用，可以从strToken的剩余部分中分解出更多的令牌。对strtok的每次调用都通过在该调用返回的令牌后插入一个空字符来修改strToken。
//要从strToken中读取下一个令牌，调用strtok，为strToken参数设置一个NULL值。
//NULL strToken参数使strtok在修改后的strToken中搜索下一个令牌。strDelimit参数可以接受从一次调用到下一次调用的任何值，因此分隔符集可以不同。
//警告:函数使用一个静态变量将字符串解析为令牌。如果对同一个函数进行多个或同时调用，则存在很高的数据损坏和不准确结果的可能性。
//因此，不要试图同时为不同的字符串调用相同的函数，并且要注意从循环中调用这些函数中的一个，因为循环中可能会调用使用相同函数的另一个例程。
//但是，从多个线程同时调用此函数不会产生不良影响。
//strtok函数找到str中的下一个标记，并将其用 \0 结尾，返回一个指向这个标记的指针。（注：strtok函数会改变被操作的字符串，所以在使用strtok函数切分的字符串一般都是临时拷贝的内容并且可修改。）
//strtok函数的第一个参数不为 NULL ，函数将找到str中第一个标记，strtok函数将保存它在字符串中的位置。
//strtok函数的第一个参数为 NULL ，函数将在同一个字符串中被保存的位置开始，查找下一个标记。
//如果字符串中不存在更多的标记，则返回 NULL 指针。

//使用：
int main()
{
	char str[] = "tihs, a, simple, string";
	char* sep = ",";
	char* pch = strtok(str, sep);	//第一次分割
	printf("%s\n", pch);	//this   
	//int len = strlen(pch);
	//char* ptmp = str + len + 1;
	pch = strtok(NULL, sep);		//第二次分割
	printf("%s\n", pch);	// a	 
	//pch = strtok(ptmp,sep);
	return 0;
}

int main()
{
	char str[] = "tihs, a, simple, string";
	char* sep = ",";
	char* pch = strtok(str, sep);	//第一次分割
	while (pch != NULL)
	{
		printf("%s\n", pch);
		pch = strtok(NULL, sep);	//有了第一次分割之后第一个参数就是NULL
	}
	return 0;
}

int main()
{
	char str[] = "-tihs, a, simple-string";	 //第一个-不会分割，分割一定是从第一个不是分隔符的地方开始寻找分隔符进行分割
	char* sep = ",-";				//多个分隔符
	char* pch = strtok(str, sep);	//第一次分割
}

int main()
{
	char *p = "zhangpengwei@bitedu.tech";
	const char* sep = ".@";
	char arr[30];
	char *str = NULL;
	strcpy(arr, p);//将数据拷贝一份，处理arr数组的内容
	for (str = strtok(arr, sep); str != NULL; str = strtok(NULL, sep))
	{
		printf("%s\n", str);
	}
	return 0;
}
```

## 5.10strerror：错误信息报告

```c
//返回错误码，所对应的错误信息
//strerror函数的作用是:将errnum映射到一个错误消息字符串，返回一个指向该字符串的指针。strerror和_strerror实际上都不会打印消息:为此，你需要调用一个输出函数，比如fprintf:
//获取系统错误消息(strerror)或打印用户提供的错误消息(_strerror)。
//函数原型：char *strerror( int errnum );	char *_strerror( const char *strErrMsg );
//返回值：Strerror和_strerror返回一个指向错误消息字符串的指针。对strerror或_strerror的后续调用可以覆盖该字符串。
//参数：错误数量  后面一个函数参数是用户提供的信息
//备注：如果strErrMsg被传递为NULL， _strerror将返回一个指向字符串的指针，该字符串包含产生错误的上一个库调用的系统错误消息。
//错误消息字符串以换行符('\n')结束。如果strErrMsg不等于NULL，那么_strerror将返回一个指向字符串的指针，
//其中(按顺序)包含您的字符串消息、冒号、空格、最后一个产生错误的库调用的系统错误消息和一个换行符。字符串消息的长度最多为94字节。
//_strerror的实际错误数存储在变量errno中。通过变量_sys_errlist访问系统错误消息，该变量是一个按错误号排序的消息数组。
//_strerror通过使用errno值作为变量_sys_errlist的索引来访问适当的错误消息。变量_sys_nerr的值定义为_sys_errlist数组中的最大元素数。
//为了产生准确的结果，在库例程返回错误后立即调用_strerror。否则，后续对strerror或_strerror的调用可以覆盖errno值。
//_strerror不是ANSI定义的一部分，而是微软对它的扩展。不要在需要可移植性的地方使用它;为了兼容ANSI，请使用strerror代替。
//必须包含的头文件：#include <errno.h>		这个头文件中有错误码
//测试：
int main()
{
	FILE* fp = fopen("Text.txt", "r");	//这个文件不存在，打开会报错
	if (fp == NULL)
	{
		printf("errno = %d\n", errno);				//错误编号变量errno是一个全局变量   errno = 2
		char* err_msg = strerror(errno);			//接收错误信息
		printf("err_msg = %s\n", err_msg);			//打印错误信息    err_msg = No such file or directory
		return 0;
	}
}
```

字符分类函数：

| 函数     | 如果他的参数符合下列条件就返回真                             |
| -------- | ------------------------------------------------------------ |
| iscntrl  | 任何控制字符                                                 |
| isspace  | 空白字符：‘空格’、‘换页\f’、‘换行\n’、‘回车\r’、‘制表符\t’、‘垂直制表符\v’ |
| isdigit  | 十进制数字0到9                                               |
| isxdigit | 十六进制数字，包括所有十进制数字，小写字母a到f、大写字母A到F |
| islower  | 小写字母a到z                                                 |
| isupper  | 大写字母A到Z                                                 |
| isalpha  | 字母a到z或A到Z                                               |
| isalnum  | 字母或者数字，a到z或A到Z或0到9                               |
| ispunct  | 标点符号，任何不属于数字或者字母的图形字符（可打印）         |
| isgraph  | 任何图形字符                                                 |
| isprint  | 任何可打印字符，包括图形字符和空白字符                       |

```c
//上面函数的测试：
void my_to_upper(char* str)
{
	assert(str);
	while (*str)
	{
		//if (islower(*str))
		if(*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
}

int main()
{
	char str[] = "abcxyz";
	printf("%s\n",str);
	my_to_upper(str);
	printf("%s\n",str);
	return 0;
}
```

# 6.内存操作函数的了解和实现：

## 5.1memcpy：内存拷贝

```c
//在缓冲区之间复制字符
//函数原型：void *memcpy( void *dest, const void *src, size_t count );
//返回值：Memcpy返回dest的值。
//参数：新缓冲区  要从中进行复制的缓冲区	要复制的字符数
//memcpy函数将src的count字节拷贝到dest，如果源端和目的端有重叠，则不保证拷贝重叠区域的源端原始字节后再覆盖。使用memmove处理重叠区域。
//备注：这个函数在遇到 '\0' 的时候并不会停下来。	
//函数memcpy从source的位置开始向后复制num个字节的数据到destination的内存位置
//如果source和destination有任何的重叠，复制的结果都是未定义的。
//模拟实现：
void *my_memcpy(void *dest, const void *src, size_t count)
{
	assert(dest && src);
	char* pdest = (char*)dest;
	const char* psrc = (const char*)src;
	while (count--)
	{
		*pdest++ = *psrc++;
	}
	return dest;
}
```

## 5.2memmove：内存移动

```c
//将一个缓冲区移动到另一个缓冲区。
//函数原型：void *memmove( void *dest, const void *src, size_t count );
//返回值：Memmove返回dest的值。
//参数：目标对象  源对象  要复制的字符的字节数
//memmove函数从src向dest拷贝字符的计数字节，如果源区域和目标区域的某些区域有重叠，则memmove函数确保在覆盖之前复制重叠区域的原始源字节。
//和memcpy的差别就是memmove函数处理的源内存块和目标内存块是可以重叠的。
//如果源空间和目标空间出现重叠，就得使用memmove函数处理。
//模拟实现：
void *my_memmove(void *dest, const void *src, size_t count)
{
	assert(dest && src);
	char* pdest = (char*)dest;
	char* psrc = (char*)src;
	if (psrc < pdest && pdest < psrc + count)
	//if (psrc >= pdest || pdest >= psrc + count)
	{
		//存在内存重叠
		psrc = psrc + count - 1;
		pdest = pdest + count - 1;
		while (count-- > 0)
		{
			*pdest-- = *psrc--;
		}
	}
	else
	{
		//不存在内存重叠
		while (count-- > 0)
		{
			*pdest++ = *psrc++;
		}
	}
	return dest;
}

//测试：
int main()
{
	//char str[20];
	char str1[10] = "abcxyz";
	//my_memset(str, 1, sizeof(str));
	//my_memcpy(str, str1, strlen(str1) + 1);
	//int flag = my_memcmp(str, str1, strlen(str1));
	my_memmove(str1 + 2, str1, 3);  //cxyz  abcxyz   abab  
	return 0;
}
```

## 5.3memset：内存设置

```c
//将缓冲区设置为指定的字符。
//函数原型：void *memset( void *dest, int c, size_t count );
//返回值：Memset返回dest的值。
//参数：指向目标的指针  要设置的字符  字符数
//memset函数将dest的count字节设置为字符c。
//模拟实现：
void *my_memset(void *dest, int c, size_t count)
{
	assert(dest);
	char* pdest = (char*)dest;
	while (count--)
	{
		*pdest++ = c;
	}
	return dest;
}
```

## 5.4memcmp：内存比较

```c
//比较两个缓冲区中的字符。
//int memcmp( const void *buf1, const void *buf2, size_t count );
//返回值：表示缓冲区之间的关系。  <0表示buf1小于buf2  =0表示buf1等于buf2  >0表示buf1大于buf2
//参数：第一个缓冲区  第二个缓冲区  字符数
//memcmp函数比较buf1和buf2的第一个计数字节，并返回指示它们之间关系的值。
//模拟实现：
int my_memcmp(const void *buf1, const void *buf2, size_t count)
{
	assert(buf1 && buf2);
	int ret = 0;
	const char* pbuf1 = (const char*)buf1;
	const char* pbuf2 = (const char*)buf2;
	while (count--)
	{
		if (*pbuf1 - *pbuf2 != 0)
			break;
		pbuf1++;
		pbuf2++;
	}
	ret = *pbuf1 - *pbuf2;
	return ret;
}
```

# 7.数据的存储：

## 7.1整形在内存中的存储：

一个变量的创建是要在内存中开辟空间的。空间的大小是根据不同的类型而决定的。

计算机中的有符号数有三种表示方法，分别是原码、反码、补码；

三种表示方法均有**符号位**和**数值位**两部分，符号位都是用0表示“正”，用1表示“负”，而数值位三种表示方法各不相同。

正数的原码、反码、补码都相同；

负数的原码、反码、补码按以下规则：
原码：直接将二进制按照正负数的形式翻译成二进制就可以。    

反码：将原码的符号位不变，其他位依次按位取反就可以得到了。  

补码：反码+1就得到补码。  

对于整形来说：数据存放内存中其实存放的是补码。（原因：在计算机系统中，数值一律用补码来表示和存储。原因在于，使用补码，可以将符号位和数值域统一处理； 同时，加法和减法也可以统一处理（CPU**只有加法器**）此外，补码与原码相互转换，其运算过程是相同的，不需要额外的硬件电路。）

计算机中数据内存存放的是补码；

## 7.2大小端：

大端（存储）模式，是指数据的低位保存在内存的高地址中，而数据的高位，保存在内存的低地址中；  （linux）

小端（存储）模式，是指数据的低位保存在内存的低地址中，而数据的高位,，保存在内存的高地址中。  （windows）

为什么会有大小端模式之分呢？这是因为在计算机系统中，我们是以字节为单位的，每个地址单元都对应着一个字节，一个字节为8bit。但是在C语言中除了8bit的char之外，还有16bit的short型，32bit的long型（要看具体的编译器），另外，对于位数大于8位的处理器，例如16位或者32位的处理器，由于寄存器宽度大于一个字节，那么必然存在着一个如果将多个字节安排的问题。因此就导致了大端存储模式和小端存储模式。例如一个 16bit 的 short 型 x ，在内存中的地址为 0x0010 ， x 的值为 0x1122 ，那么 0x11 为高字节， 0x22为低字节。对于大端模式，就将 0x11 放在低地址中，即 0x0010 中， 0x22 放在高地址中，即 0x0011 中。小端模式，刚好相反。我们常用的 X86 结构是小端模式，而 KEIL C51 则为大端模式。很多的ARM，DSP都为小端模式。有些ARM处理器还可以由硬件来选择是大端模式还是小端模式。

```c
//设计一个小程序来判断当前机器的字节序
//方法1：
int check_sys()
{
	int i = 1;
	return (*(char *)&i);
}

int main()
{
	int ret = check_sys();
	if(ret == 1)
	{
		printf("小端\n");
	}
	else
	{
		printf("大端\n");
	}
	return 0;
}

//方法2：
int check_sys()
{
	union
	{
		int i;
		char c;
	}un;
	un.i = 1;
	return un.c
}

int main()
{
	int ret = check_sys();
	if(ret == 1)
	{
		printf("小端\n");
	}
	else
	{
		printf("大端\n");
	}
	return 0;
}

//大小端试题练习：
int main()
{
	char a = -1;
	signed char b = -1;		   
	signed char b = -1;		   
	unsigned char c = -1;	//原码：10000001  反码：11111110  补码：11111111
	printf("a=%d,b=%d,c=%d", a, b, c);	//-1 -1 255 
	return 0;
}

int main()
{
	char a = -128;		//1000 0000  -128
	printf("%u\n", a);	//无符号输出 按整形输出		4294967168
	//原码：1000 0000 0000 0000 0000 0000 0000 1000
	//反码：1111 1111 1111 1111 1111 1111 1111 0111
	//补码：1111 1111 1111 1111 1111 1111 1111 1000   4294967168
	return 0;
}

int main()
{
	char a = 128;			//超出127的范围，就是-128  1000 0000
	printf("%u\n", a);		//4294967168（解决方法和上一个题一样）
	return 0;
}

int main()
{
	int i = -20;			 
	unsigned int j = 10;	 
	printf("%d\n", i + j);		//-10  按照补码进行运算，最后结果是原码展示
	//按照补码的形式进行运算，最后格式化成为有符号整数
	return 0;
}

int main()
{
	int i = -20;
	unsigned int j = 10;
	printf("%u\n", i + j);		//4294967286	 
	//原码：10000000 00000000 00000000 00001010
	//反码：11111111 11111111 11111111 11110101
	//补码：11111111 11111111 11111111 11110110   4294967286
	return 0;
}

int main()
{
	unsigned int i;
	for (i = 9; i >= 0; i--)
	{
		printf("%u\n", i);			//死循环  减到0之后是一个很大的数字，因为输出是无符号输出
	}
}

int main()
{
	char a[1000];
	int i;
	for (i = 0; i < 1000; i++)
	{
		a[i] = -1 - i;				//逆时针循环一圈 -1到-128，127到1
	}
	printf("%d", strlen(a));		//255
	return 0;
}

int main()
{
	unsigned char i = 0;			//char类型的无符号取值范围是0到255
	for (i = 0; i <= 255; i++)
	{
		printf("hello world\n");	//加到255之后变为0  死循环
	}
	return 0;
}
```

## 7.3浮点在内存中的存储：

3.14159 1E10 浮点数家族包括： float、double、long double 类型。 浮点数表示的范围：float.h中定义  

```c
int main()
{
	int n = 9;
	float *pFloat = (float *)&n;
	printf("n的值为：%d\n", n);					//9
	printf("*pFloat的值为：%f\n", *pFloat);		//0.000000
	*pFloat = 9.0;
	printf("num的值为：%d\n", n);				//1091567616
	printf("*pFloat的值为：%f\n", *pFloat);		//9.000000
	return 0;
}
//解释：为什么 0x00000009 还原成浮点数，就成了 0.000000?
//9 -> 0000 0000 0000 0000 0000 0000 0000 1001
//将 0x00000009拆分，得到第一位符号位s=0，后面8位的指数 E=00000000 ，最后23位的有效数字M=000 0000 0000 0000 0000 1001。
//由于指数E全为0，符合指数E全为0的特殊情况。浮点数V就写成： V=(-1)^0 × 0.00000000000000000001001×2^(-126)=1.001×2^(-146) 显然，V是一个很小的接近于0的正数，所以用十进制小数表示就是0.000000。

//解释：浮点数9.0，如何用二进制表示？还原成十进制又是多少？
//浮点数9.0等于二进制的1001.0，即1.001×2^3。
//9.0 -> 1001.0 ->(-1)^0 * 1.001 * 2^3 -> s=0, M=1.001 - 1 = .001, E = 3 +1 27 = 130
//第一位的符号位s=0，有效数字M等于001后面再加20个0，凑满23位，指数E等于3+127=130，即10000010。 所以，写成二进制形式，应该是s+E+M，即0 10000010 001 0000 0000 0000 0000 0000
//这个32位的二进制数，还原成十进制，正是 1091567616。

//根据国际标准IEEE（电气和电子工程协会） 754，任意一个二进制浮点数V可以表示成下面的形式：
//(-1)^S * M * 2^E  
//(-1)^s表示符号位，当s=0，V为正数；当s=1，V为负数。
//M表示有效数字，大于等于1，小于2。
//2^E表示指数位。
int main()
{
    //这里举例是10进制，二进制一样
    float f = 1.125f;  // (-1)^0 * 1.125 * 10^0
    float f = 1234.125f;  // (-1)^0 * 1.234125 * 10^3	
    float f = 10.125;	//二进制是1010.001  (-1)*0 * 1.010001 * 2^3
    return 0;
}
//举例来说： 十进制的5.0，写成二进制是 101.0 ，相当于 1.01×2^2 。 那么，按照上面V的格式，可以得出s=0，M=1.01，E=2。
//十进制的-5.0，写成二进制是 -101.0 ，相当于 -1.01×2^2 。那么，s=1，M=1.01，E=2
```

![image-20230412015927514](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230412015927514.png)

![image-20230412020245992](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230412020245992.png)

```c
//单精度浮点数存储模型是1位符号位,8位指数位，23位有效数位
//双精度浮点数存储模型是1位符号位,11位指数位，52位有效数位
//IEEE 754对有效数字M和指数E，还有一些特别规定。 前面说过， 1≤M<2 ，也就是说，M可以写成 1.xxxxxx 的形式，其中xxxxxx表示小数部分。IEEE754规定，在计算机内部保存M时，默认这个数的第一位总是1，因此可以被舍去，只保存后面的xxxxxx部分。比如保存1.01的时候，只保存01，等到读取的时候，再把第一位的1加上去。这样做的目的，是节省1位有效数字。以32位浮点数为例，留给M只有23位，将第一位的1舍去以后，等于可以保存24位有效数字。至于指数E，情况就比较复杂。
//首先，E为一个无符号整数（unsigned int） 这意味着，如果E为8位，它的取值范围为0~255；如果E为11位，它的取值范围为0~2047。但是，我们知道，科学计数法中的E是可以出现负数的，所以IEEE 754规定，存入内存时E的真实值必须再加上一个中间数，对于8位的E，这个中间数是127；对于11位的E，这个中间数是1023。比如，2^10的E是10，所以保存成32位浮点数时，必须保存成10+127=137，即10001001。
//指数E从内存中取出还可以再分成三种情况：
//E不全为0或不全为1:指数E的计算值减去127（或1023），得到真实值，再将有效数字M前加上第一位的1。 比如： 0.5（1/2）的二进制形式为0.1，由于规定正数部分必须为1，即将小数点右移1位，则为1.0*2^(-1)，其阶码为-1+127=126，表示为01111110，而尾数1.0去掉整数部分为0，补齐0到23位00000000000000000000000，则其二进制表示形式为0 01111110 00000000000000000000000
//E全为0:浮点数的指数E等于1-127（或者1-1023）即为真实值， 有效数字M不再加上第一位的1，而是还原为0.xxxxxx的小数。这样做是为了表示±0，以及接近于0的很小的数字。
//E全为1：如果有效数字M全为0，表示±无穷大（正负取决于符号位s）。
```

```c
//具体实例：
//float = 10.125  
//转换为二进制是1010.001 = 1^0 * 1.010001 * 2^3
//在内存中存储是0（符号位） 100 0001 0（指数位） 010 0010 0000 0000 0000 0000（有效数位）
//符号位是0，指数为是3 + 127 = 130，有效数位是010001（去除1）。
//还有一个是二进制反推数字，原理一样；
//补充：指数位和有效数位是从最左边分配的，有效数位后面补0；
```

# 8.自定义类型：

## 8.1结构体：

```c
//初始化：定义变量的同时赋初值。
struct Point p3 = {x, y};

struct Stu //类型声明
{
char name[15];//名字
int age; //年龄
};
struct Stu s = {"zhangsan", 20};//初始化

//结构体内存对齐（重点）:
//字节对齐要区分四个概念：
//1.基本数据类型的自身对齐值：
//2.程序的指定对齐值：#pragmaticpack (2)
//3.自定义类型的自身对齐值：内部成员中最大的一个；
//4.自定义类型的有效对齐值：元素对齐值和指定对齐值中选择小的一个；

//测试：
#pragma pack(2)

typedef struct Teat
{
	char a;   //1+1
	int c;	  //4
	double b; //8
}Test;

int main()
{
	printf("%d\n", sizeof(Test));	//14
	return 0;
}

//和上面一个进行有效对齐值对比
#pragma pack(2)

typedef struct Teat
{
	char a;   //1
	char c;	  //1
	char b;	  //1
}Test;

int main()
{
	printf("%d\n", sizeof(Test));	//3
	return 0;
}

typedef struct Test
{
	short a;	//2 + 6
	struct t
	{
		double c;  //8
		int b;     //4
		char d;    //1+3
	};
	int e;		   //4+4
}Test;

int main()
{
    //在c语言平台下
	printf("%d\n", sizeof(Test));   //32
	return 0;
}

int main()
{
    //在c++语言平台下
	printf("%d\n", sizeof(Test));   //8 在c++中不加struct t中的t是32，原因是不加t把c、b、d当做Test结构体中成员，加上t就变成类型t，里面的成员就是哑成员
	return 0;
}

//练习题：
typedef struct S1
{
	char c1;	//1+3
	int i;		//4
	char c2;	//1+3
}S1;

int main()
{
	printf("%d\n", sizeof(S1));		//12
	return 0;
}

typedef struct S2
{
	char c1;	//1
	char c2;	//1+2
	int i;		//4
}S2;

int main()
{
	printf("%d\n", sizeof(S2));	//8
	return 0;
}

typedef struct S3
{
	double d;	//8
	char c;		//1+3
	int i;		//4
}S3;

int main()
{
	printf("%d\n", sizeof(S3));	//16
	return 0;
}

typedef struct S3
{
	double d;	//8
	char c;		//1+3
	int i;		//4
}S3;

typedef struct S4
{
	char c1;		//1+7
	struct S3 s3;	//16
	double d;		//8
}S4;

int main()
{
	printf("%d\n", sizeof(S4));		//32
	return 0;
}

//结构体的对齐规则：
//1. 第一个成员在与结构体变量偏移量为0的地址处。
//2. 其他成员变量要对齐到某个数字（对齐数）的整数倍的地址处。	对齐数 = 编译器默认的一个对齐数 与 该成员大小的较小值。(VS中默认的值为8)
//3. 结构体总大小为最大对齐数（每个成员变量都有一个对齐数）的整数倍。
//4. 如果嵌套了结构体的情况，嵌套的结构体对齐到自己的最大对齐数的整数倍处，结构体的整体大小就是所有最大对齐数（含嵌套结构体的对齐数）的整数倍。

//为什么存在内存对齐？
//1. 平台原因(移植原因)： 不是所有的硬件平台都能访问任意地址上的任意数据的；某些硬件平台只能在某些地址处取某些特定类型的数据，否则抛出硬件异常。
//2. 性能原因： 数据结构(尤其是栈)应该尽可能地在自然边界上对齐。 原因在于，为了访问未对齐的内存，处理器需要作两次内存访问；而对齐的内存访问仅需要一次访问。
//总体来说：结构体的内存对齐是拿空间来换取时间的做法。
//那在设计结构体的时候，我们既要满足对齐，又要节省空间，如何做到：让占用空间小的成员尽量集中在一起。
typedef struct S1
{
	char c1;	//1+3
	int i;		//4
	char c2;	//1+3
}S1;

typedef struct S2
{
	char c1;	//1
	char c2;	//1+2
	int i;		//4
}S2;

int main()
{
	printf("%d\n", sizeof(S1));		//12
	printf("%d\n", sizeof(S2));		//8
	return 0;
}
//S1和S2类型的成员一模一样，但是S1和S2所占空间的大小有了一些区别。

//设置默认对齐数：#pragma pack(8)
//取消设置的默认对齐数，还原为默认：#pragma pack()
//结构在对齐方式不合适的时候，我么可以自己更改默认对齐数。

#pragma pack(4)

struct A
{
	struct
	{
		char a;	//1+1
		short b;//2
		char c; //1+1
	}h;
	short d;	//2
};
//8

struct B
{ 
	char a;	//1+1
	short b;//2
	char c; //1+1
	short d;//2
};
//8

struct C
{
	struct
	{
		char a;	//1+1
		short b;//2
		char c; //1+1
	}h;
	long d;		//4+2
};
//12

//写一个宏，计算结构体中某变量相对于首地址的偏移，并给出说明（offsetof的实现）
//offsetof宏是C语言中一个已经实现的宏，其主要作用就是在给定的结构体类型中，对某个存在的结构体成员的相对于结构体起始地址偏移量的计算。
//实现：
//1、像这种在同一空间中、有相对位置偏移量的计算，可以采用“指针-指针”的形式计算得知。就是直接通过末地址-起始地址得到一个相对数值，再强制转换为int 或 size_t得到偏移量。
//2、我们可以把一个结构体当成为一个独立的空间，毕竟只是通过相对数值的方式求出偏移量，不妨将结构体起始位置当成0，可以将对应指针设为0，这样指向指定结构体成员时，其地址就是相对数值。
//具体实现：
#define OFFSETOF1(type_name,mem_name)  (size_t)&(((type_name*)0)->mem_name)			//宏是没有类型检查的

struct list {
	char name[20];		//20
	int age;			//4
	double grade;		//8
}n1;
int main() {
	printf("%d\n", OFFSETOF1(struct list, age)); //20
	printf("%d\n", OFFSETOF1(struct list, name)); //0
	printf("%d\n", OFFSETOF1(struct list, grade)); //24
	return 0;
}

//结构体传参：首选地址传参
//原因：函数传参的时候，参数是需要压栈，会有时间和空间上的系统开销。如果传递一个结构体对象的时候，结构体过大，参数压栈的的系统开销比较大，所以会导致性能的下降
//结论：结构体传参的时候，要传结构体的地址。
```

## 8.2位段（位域）：

```c
//位段的声明和结构体是类似的，有两个不同：
//1.位段的成员必须是int、unsigned int 或signed int。
//2.位段的成员名后边有一个冒号和一个数字。

//位段的内存分配：
//1. 位段的成员可以是 int unsigned int signed int 或者是 char （属于整形家族）类型。
//2. 位段的空间上是按照需要以4个字节（ int ）或者1个字节（ char ）的方式来开辟的。
//3. 位段涉及很多不确定因素，位段是不跨平台的，注重可移植的程序应该避免使用位段。
//4. 位段不能跨字节和类型存储，类型不同的时候也存在字节对齐。

typedef struct a
{
	char a : 1;		//1+3
	int b : 1;		//4
}a;

int main()
{
	printf("%d\n", sizeof(a));		//8
	return 0;
}

int main()
{
	unsigned char arr[4];
	struct t
	{
		unsigned char a;		//占一个字节
		//下面的占第二个字节：101001（从右边开始，右边是低位，左边是高位）（装不下就舍去左边）
		unsigned char b : 1;
		unsigned char c : 2;
		unsigned char d : 3;
	}*ta;
	ta = (struct t*)arr;
	memset(arr, 0, 4);	//数组初始化为0
	ta->a = 2;	//二进制
	ta->b = 3;	//0011	取出1
	ta->c = 4;  //0100	取出00
	ta->d = 5;	//0101	取出101
	printf("%02x %02x %02x %02x\n", arr[0], arr[1], arr[2], arr[3]);	//02 29 00 00   16进制输出2位结果
	return 0;
}

struct A
{
	int _a : 2;		//第一个字节
	int _b : 5;		//第一个字节
	int _c : 10;	//第二个和第三个字节
	int _d : 30;	//第5678这四个字节、
    //这里存在字节具体分配的问题，不是很理解
};

int main()
{
	printf("%d\n", sizeof(struct A));	//8   
	return 0;
}

struct S
{
	char a : 3;
	char b : 4;
	char c : 5;
	char d : 4;
};

int main()
{
	struct S s = { 0 };
	s.a = 10;
	s.b = 12;
	s.c = 3;
	s.d = 4;
	return 0;
}
```

![image-20230413032707227](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230413032707227.png)

```c
//位段的跨平台问题：
//1. int位段被当成有符号数还是无符号数是不确定的。(有符号)
//2. 位段中最大位的数目不能确定。（16位机器最大16，32位机器最大32，写成27，在16位机器会出问题。（在写代码之前就知道代码的运行环境）
//3. 位段中的成员在内存中从左向右分配，还是从右向左分配标准尚未定义。(这个是之前不理解的)（从右边的低位向左边的高位进行分配，这个是vs测试出来的）
//4. 当一个结构包含两个位段，第二个位段成员比较大，无法容纳于第一个位段剩余的位时，是舍弃剩余的位还是利用，这是不确定的。（vs测试是舍去的）

//特殊情况：
struct Test
{
	char a : 3;
	char   : 2;	//占位,中间空出两个位
	char b : 1;	//b只能使用空出来两位之后的1个位
};

//总结：跟结构相比，位段可以达到同样的效果，但是可以很好的节省空间，但是有跨平台的问题存在。（但在写代码之前知道环境，所以跨平台不是问题了）
//位段的应用:在网络协议中，越是接近底层的会使用位段。
```

![image-20230413033714224](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230413033714224.png)

## 8.3枚举：

```c
//枚举就是把可能出现的情况一一列举；
//常量的可能出现情况：const、宏、枚举；

enum Color//颜色	枚举类型
{	
	RED,		//0	枚举常量 可能取值
	GREEN,		//1
	BLUE		//2
};

//定义的时候赋初值
enum Color//颜色
{
	RED=1,	
	GREEN=2,	
	BLUE=4
};

//枚举的优点：我们可以使用 #define 定义常量，为什么非要使用枚举？
//1. 增加代码的可读性和可维护性；
//2. 和#define定义的标识符比较枚举有类型检查，更加严谨；
//3. 防止了命名污染（封装）；
//4. 便于调试；
//5. 使用方便，一次可以定义多个常量。

//枚举的特点：
//1.枚举默认是从0开始的；
//2.枚举指定值之后，下一个值是从指定的值+1计算的；
//3.枚举常量的可能取值可以是负数，但必须是整数；

//枚举的使用：
typedef enum Color//颜色
{
	RED = 1,
	GREEN = 2,
	BLUE = 4
}c;
 
int main()
{
	printf("%d\n", sizeof(c));		//4  原因：枚举的同一时刻只能用一个
	enum Color m;
	m = RED;		//同一时刻只能使用其中的一个
	enum Color clr = GREEN;//只能拿枚举常量给枚举变量赋值，才不会出现类型的差异。
	clr = 5; //c语言检查不严格，语法允许，但c++类型检查严格，会报错，不推荐这样做；
	return 0;
}
```

## 8.4联合（共用体）：

```c
//联合类型的定义：联合也是一种特殊的自定义类型 这种类型定义的变量也包含一系列的成员，特征是这些成员公用同一块空间（所以联合也叫共用体）。
//联合类型的声明
typedef union Un
{
	char c;
	int i;
}u;
 
int main()
{
	//联合变量的定义
	union Un un;
	u s;
	//计算连个变量的大小
	printf("%d\n", sizeof(un));	//4  联合类型的大小是其中成员大小的最大值
	return 0;
}

//联合的特点：联合的成员是共用同一块内存空间的，这样一个联合变量的大小，至少是最大成员的大小（因为联合至少得有能力保存最大的那个成员）。
union Un
{
	int i;
	char c;
};

int main()
{
	union Un un;
	// 下面输出的结果是一样的吗？
	printf("%x\n", &(un.i));	//93fdac
	printf("%x\n", &(un.c));	//93fdac
	//下面输出的结果是什么？
	un.i = 0x11223344;			
	un.c = 0x55;				
	printf("%x\n", un.i);		//11223355
	return 0;
}

//联合大小的计算：
//1.联合的大小至少是最大成员的大小。
//2.当最大成员大小不是最大对齐数的整数倍的时候，就要对齐到最大对齐数的整数倍。
union Un1
{
	char c[5];	//5+3	最大成员是整个数组
	int i;		//4		最大对齐数
};
union Un2
{
	short c[7];	//14+2
	int i;		//4
};

int main()
{
	printf("%d\n", sizeof(union Un1));	//8
	printf("%d\n", sizeof(union Un2));	//16
	return 0;
}
```

# 9.动态内存管理：

## 9.1常用函数：

```c
头文件：stdlib.h
1.malloc:
函数原型：void *malloc( size_t size );
返回值：malloc返回一个指向已分配空间的void指针，如果可用内存不足则返回NULL。若要返回指向非void类型的指针，请对返回值使用类型强制转换。返回值所指向的存储空间保证与任何类型的对象的存储进行了适当的对齐。如果size为0,malloc在堆中分配一个长度为0的项，并返回指向该项的有效指针。总是检查malloc的返回值，即使请求的内存量很小。
参数：size：大小，要分配的字节
malloc返回一个指向已分配空间的void指针，如果可用内存不足则返回NULL。malloc函数分配一个至少大小字节的内存块。由于对齐和维护信息需要空间，块可能比size字节大。
启动代码使用malloc为_environ、envp和argv变量分配存储空间。    

总结：
这个函数向内存申请一块连续可用的空间，并返回指向这块空间的指针。
如果开辟成功，则返回一个指向开辟好空间的指针。
如果开辟失败，则返回一个NULL指针，因此malloc的返回值一定要做检查。
返回值的类型是 void* ，所以malloc函数并不知道开辟空间的类型，具体在使用的时候使用者自己来决定。
如果参数 size 为0，malloc的行为是标准是未定义的，取决于编译器。

int main()
{
	//代码1		 
	int num = 0;
	scanf("%d", &num);
	//int arr[num] = { 0 };	错误的，num应该是确定的值
	//代码2
	int* ptr = NULL;
	ptr = (int*)malloc(num * sizeof(int));
	if (NULL != ptr)//判断ptr指针是否为空
	{
		int i = 0;
		for (i = 0; i < num; i++)
		{
			*(ptr + i) = 0;
		}
	}
	free(ptr);//释放ptr所指向的动态内存
	ptr = NULL;
	return 0;
}
    
2.calloc:
在内存中分配一个元素初始化为0的数组。
函数原型：void *calloc( size_t num, size_t size );
返回值：calloc返回一个指向已分配空间的指针。返回值所指向的存储空间保证与任何类型的对象的存储进行了适当的对齐。若要获取指向非void类型的指针，请对返回值使用类型强制转换。
参数：num：元素数量    size：大小，每个元素的字节长度
calloc函数为长度为字节的num元素数组分配存储空间。每个元素初始化为0。
calloc调用malloc，以便使用c++ _set_new_mode函数设置新的处理程序模式。
    
总结：
函数的功能是为 num 个大小为 size 的元素开辟一块空间，并且把空间的每个字节初始化为0。
与函数malloc的区别只在于calloc会在返回地址之前把申请的空间的每个字节初始化为全0。

3.realloc:
重新分配内存块。
函数原型：void *realloc( void *memblock, size_t size );
返回值：realloc返回一个指向重新分配(可能移动)内存块的空指针。如果大小为0且buffer参数不为NULL，或者没有足够的可用内存将块扩展到给定的大小，则返回值为NULL。在第一种情况下，释放原始块。在第二种情况下，原始块保持不变。返回值指向一个存储空间，该存储空间保证为存储任何类型的对象进行了适当的对齐。若要获取指向非void类型的指针，请对返回值使用类型强制转换。
参数：memblock：指向先前分配的内存块的指针	size：以字节为单位的新大小
realloc函数改变已分配内存块的大小。memblock参数指向内存块的开始。如果memblock为NULL, realloc的行为与malloc相同，并分配一个大小为字节的新块。如果memblock不是NULL，它应该是一个由之前调用calloc、malloc或realloc返回的指针。
size参数给出块的新大小，以字节为单位。尽管新块可以位于不同的位置，但块的内容在新旧大小中较短的部分是不变的。因为新的块可以在新的内存位置，realloc返回的指针不能保证是通过memblock参数传递的指针。
realloc调用malloc，以便使用c++ _set_new_mode函数设置新的处理程序模式。
    
总结：realloc函数的出现让动态内存管理更加灵活。
有时会我们发现过去申请的空间太小了，有时候我们又会觉得申请的空间过大了，那为了合理的时候内存，我们一定会对内存的大小做灵活的调整。那 realloc 函数就可以做到对动态开辟内存大小的调整。 
这个函数调整原内存空间大小的基础上，还会将原来内存中的数据移动到新的空间。
realloc在调整内存空间的是存在两种情况：
情况1：原有空间之后有足够大的空间：
    当是情况1 的时候，要扩展内存就直接原有内存之后直接追加空间，原来空间的数据不发生变化
情况2：原有空间之后没有足够大的空间
    当是情况2 的时候，原有空间之后没有足够多的空间时，扩展的方法是：在堆空间上另找一个合适大小的连续空间来使用。这样函数返回的是一个新的内存地址。
    
int main()
{
	int *ptr = malloc(100);
	if (ptr != NULL)
	{
		//业务处理
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	//扩展容量
	//代码1
	//ptr = realloc(ptr, 1000);  不推荐，这样没办法接受返回值判断空间是否申请成功
	//代码2
	int*p = NULL;
	p = realloc(ptr, 1000);
	if (p != NULL)
	{
		ptr = p;
	}
	//业务处理
	free(ptr);
	return 0;
}

4.free:
函数原型：void free( void *memblock);
返回值：没有
参数：先前分配的内存块将被释放。
函数释放先前通过调用calloc、malloc或realloc分配的内存块(memblock)。释放的字节数等价于块被分配(或在realloc情况下被重新分配)时请求的字节数。如果memblock为NULL，指针将被忽略，并立即返回free。试图释放无效指针(指向未通过calloc、malloc或realloc分配的内存块的指针)可能会影响后续的分配请求并导致错误。
在释放内存块之后，_heapmin通过合并未使用的区域并将它们释放回操作系统来最小化堆上的空闲内存量。未释放到操作系统的已释放内存将恢复到空闲池，并可再次进行分配。
    
总结：
free函数用来释放动态开辟的内存。
如果参数memblock指向的空间不是动态开辟的，那free函数的行为是未定义的。
如果参数memblock是NULL指针，则函数什么事都不做。
```

## 9.2内存泄漏检测和动态内存常见错误：

```c
内存泄漏检测：
vld	  下载链接：https://kinddragon.github.io/vld/
头文件：#include <vld.h>
.lib静态库  .dll动态库
安装：.h放在include文件夹中  .lib和.dll放在lib文件夹中（把vld下载的内容放在vs的对应文件夹中）
使用：F5启动调试然后会报告内存泄漏的情况
参考文档：https://blog.csdn.net/devillixin/article/details/126196206
双击热备防止服务器断电
    
动态内存常见错误：
1.对NULL指针的解引用操作
int main()
{
	int *p = (int *)malloc(INT_MAX);	//INT_MAX的值很大，申请不到栈区空间，返回NULL
	*p = 20;//如果p的值是NULL，就会有问题
	free(p);
    return 0;
}

2.对动态开辟空间的越界访问
int main()
{
	int i = 0;
	int *p = (int *)malloc(10 * sizeof(int));
	if (NULL == p)
	{
		exit(EXIT_FAILURE);
	}
	for (i = 0; i <= 10; i++)	
	{
		*(p + i) = i;//当i是10的时候越界访问
	}
	free(p);
	return 0;
}

3.对非动态开辟内存使用free释放
int main()
{
	int a = 10;
	int *p = &a; 
	free(p);	//free不能释放不是堆上申请的内存
	return 0;
}

4.使用free释放一块动态开辟内存的一部分
int main()
{
	int *p = (int *)malloc(100);
	p++;
	free(p);//p不再指向动态内存的起始位置，malloc申请100字节内存的时候，free会记录，free的时候会释放1000字节的内存
	return 0;
}

5.对同一块动态内存多次释放
int main()
{
	int *p = (int *)malloc(100);
	free(p);
	free(p);//重复释放	NULL可以多次释放
	return 0;
}

6.动态开辟内存忘记释放（内存泄漏）
int main()
{
	int *p = (int *)malloc(100);
	if (NULL != p)
	{
		*p = 20;
	}
	free(p);	//忘记free，会造成内存泄漏
	return 0;
}

忘记释放不再使用的动态开辟的空间会造成内存泄漏。动态开辟的内存一定要释放，并且正确释放。
```

## 9.3笔试题：

```c
void GetMemory(char *p)
{
	p = (char *)malloc(100);
}

int main()
{
	char *str = NULL;
	GetMemory(str);		//这是一个传值操作，形参p的更改和str没有关系，str没有在堆上真正的申请到内存
	strcpy(str, "hello world");
	printf(str);
	return 0;
}

char *GetMemory()
{
	char p[] = "hello world";	//是临时空间，返回到调用函数之后就被释放了，前面加上一个static就不会被释放了
	return p;
}

int main()
{
	char *str = NULL;
	str = GetMemory();
	printf(str);
	return 0;
}

void GetMemory(char **p, int num)
{
	*p = (char *)malloc(num);
}

int main()
{
	char *str = NULL;
	GetMemory(&str, 100);
	strcpy(str, "hello");
	//printf(str);
	printf("%s\n", str);
	free(str);	//记得要释放
	return 0;
}

int main()
{
	char *str = (char *)malloc(100);
	strcpy(str, "hello");
	free(str);
	//str = NULL;
	//释放之后记得将指针置位NULL
	if (str != NULL)
	{
		strcpy(str, "world");
		printf(str);
	}
	return 0;
}
```

## 9.4内存开辟图：

```c
C/C++程序内存分配的几个区域：
1.栈区（stack）：在执行函数时，函数内局部变量的存储单元都可以在栈上创建，函数执行结束时这些存储单元自动被释放。栈内存分配运算内置于处理器的指令集中，效率很高，但是分配的内存容量有限。栈区主要存放运行函数而分配的局部变量、函数参数、返回数据、返回地址等。
2. 堆区（heap）：一般由程序员分配释放， 若程序员不释放，程序结束时可能由OS回收 。分配方式类似于链表。
3. 数据段（静态区）（static）存放全局变量、静态数据。程序结束后由系统释放。
4. 代码段(.data)：存放函数体（类成员函数和全局函数）的二进制代码，已初始化的全局变量。
5.bss：定义的变量没有初始化（未初始呼哈的全局变量）。

//测试栈和堆的地址大小关系
int main()
{
	unsigned char a = 10;
	printf("%d\n", &a);		//bifb43
	unsigned char* b = (unsigned char*)malloc(sizeof(a) * 10);
	printf("%d\n", &b);		//bifb34
	//总结：堆的地址小于栈的地址
	//《程序员的自我修养》说栈的地址比堆高
	return 0;
}
```

![image-20230414210228673](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230414210228673.png)

## 9.5柔型数组：

```c
C99 中，结构中的最后一个元素允许是未知大小的数组，这就叫做柔性数组成员。
typedef struct test
{
	char a;
	double b;
	int c;
	char ar[0];	//柔性数组成员，不占空间	有些编译器会报错无法编译改成int a[];
}test;

int main()
{
	printf("size = %d\n", sizeof(test));	//24
	return 0;
}

柔性数组的特点:
1.结构体中的柔性数组成员前面必须至少一个其他成员。
2.sizeof返回的这种结构大小不包括柔性数组的内存。
3.包含柔性数组成员的结构用malloc()函数进行内存的动态分配，并且分配的内存应该大于结构的大小，以适应柔性数组的预期大小。
    
typedef struct test
{
	//int i;
	int a[];
}test;

int main()
{
	printf("size = %d\n", sizeof(test));	//4 在c语言中有没有i元素输出结果都是4，在c++中只有柔性数组输出是1
	return 0;
}

typedef struct test
{
	char a;
	double b;
	int c;
	int ptr[];
}test;

int main()
{ 
	char str[] = "hello bit";
	test *pt = (test*)malloc(sizeof(test) + strlen(str) + 1);
	if (NULL == pt)
	{
		printf("Out of Memory.\n");
		return;
	}
	strcpy(pt->ptr, str);
	printf("str = %s\n", pt->ptr);		//hello bit
	return 0;
}

typedef struct st_type
{
	int i;
	int a[0];//柔性数组成员
}type_a;

int main()
{ 
	int i = 0;
	type_a *p = (type_a*)malloc(sizeof(type_a) + 100 * sizeof(int));
	//业务处理
	p->i = 100;
	for (i = 0; i < 100; i++)
	{
		p->a[i] = i;	//这样柔性数组成员a，相当于获得了100个整型元素的连续空间。
	}
	free(p);
	return 0;
}

//上面的代码也可以用指针：
typedef struct st_type
{
	int i;
	int *p_a;
}type_a;

int main()
{ 
	type_a *p = malloc(sizeof(type_a));
	p->i = 100;
	p->p_a = (int *)malloc(p->i * sizeof(int));
	//业务处理
	for (i = 0; i < 100; i++)
	{
		p->p_a[i] = i;
	}
	//释放空间   变得麻烦
	free(p->p_a);
	p->p_a = NULL;
	free(p);
	p = NULL;
	return 0;
}

理解柔性数组（柔性数组的特性）：
1.用柔性数组不开辟空间；
2.可以把需要操作的数据和结构体统一合并起来；
3.释放空间的时候可以把结构体空间和整体空间一起释放，而不需要单独释放；
    
柔性数组好处：
1.方便释放内存：如果我们的代码是在一个给别人用的函数中，你在里面做了二次内存分配，并把整个结构体返回给用户。用户调用free可以释放结构体，但是用户并不知道这个结构体内的成员也需要free，所以你不能指望用户来发现这个事。所以，如果我们把结构体的内存以及其成员要的内存一次性分配好了，并返回给用户一个结构体指针，用户做一次free就可以把所有的内存也给释放掉。
2.有利于访问速度：连续的内存有益于提高访问速度，也有益于减少内存碎片。（其实，我个人觉得也没多高了，反正你跑不了要用做偏移量的加法来寻址）
    
int main()
{
	//动态申请一个5行5列的数组
	//开辟
	int** par = (int**)malloc(sizeof(int*) * 5);
	if (NULL == par)
	{
		return 0;
	}
	for (int i = 0; i < 5; i++)
	{
		par[i] = (int*)malloc(sizeof(int) * 5);
	}

	//使用
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			par[i][j] = i + j;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%d ", par[i][j]);
		}
		printf("\n");
	}

	//释放
	for (int i = 0; i < 5; i++)
	{
		free(par[i]);
	}
	free(par);
	return 0;
}

//不是所有申请空间的函数都能用free释放
int main()
{
	int* ptr = _alloca(sizeof(int) * 10);	//不能释放 原因是申请的内存在栈上
	//free(ptr);
	return 0;
}
```

# 10.文件操作：

## 10.1文件基础知识：

```c
在程序设计中，我们一般谈的文件有两种：程序文件、数据文件（从文件功能的角度来分类的）。
程序文件：包括源程序文件（后缀为.c）,目标文件（windows环境后缀为.obj）,可执行程序（windows环境后缀为.exe）。
数据文件：文件的内容不一定是程序，而是程序运行时读写的数据，比如程序运行需要从中读取数据的文件，或者输出内容的文件。
文件名（路径）：一个文件要有一个唯一的文件标识，以便用户识别和引用。（文件名包含3部分：文件路径+文件名主干+文件后缀）（为了方便起见，文件标识常被称为文件名。）
```

## 10.2文件的打开和关闭：

```c
文件指针：缓冲文件系统中，关键的概念是“文件类型指针”，简称“文件指针”。每个被使用的文件都在内存中开辟了一个相应的文件信息区，用来存放文件的相关信息（如文件的名
字，文件状态及文件当前的位置等）。这些信息是保存在一个结构体变量中的。该结构体类型是有系统声明的，取名FILE。
不同的C编译器的FILE类型包含的内容不完全相同，但是大同小异。
每当打开一个文件的时候，系统会根据文件的情况自动创建一个FILE结构的变量，并填充其中的信息，使用者不必关心细节。
一般都是通过一个FILE的指针来维护这个FILE结构的变量，这样使用起来更加方便。
创建一个FILE*的指针变量:FILE* pf;//文件指针变量
定义pf是一个指向FILE类型数据的指针变量。可以使pf指向某个文件的文件信息区（是一个结构体变量）。通过该文件信息区中的信息就能够访问该文件。也就是说，通过文件指针变量能够找到与它关联的文件。

fopen：打开文件
函数原型：FILE *fopen( const char *filename, const char *mode );
打开方式c、n和t模式选项是微软对fopen和_fdopen的扩展，不应该用于需要ANSI可移植性的地方。
返回值：每个函数都返回一个指向打开文件的指针。空指针值表示错误。
参数：filename：文件名、路径    mode：允许的访问类型
fopen函数的作用是:打开filename指定的文件。
    
fclose：关闭文件
函数原型：int fclose( FILE *stream );
返回值：如果流被成功关闭，fclose返回0。_fcloseall返回关闭的流的总数。两个函数都返回EOF以指示错误。
参数：流、指向FILE结构的指针
fclose函数的作用是关闭流。_fcloseall关闭所有打开的流，除了stdin, stdout, stderr(和，在MS-DOS®，_stdaux和_stdprn)。它还关闭和删除由tmpfile创建的任何临时文件。在这两个函数中，所有与流相关的缓冲区都会在关闭之前被刷新。当流关闭时，系统分配的缓冲区将被释放。用户使用setbuf和setvbuf分配的缓冲区不会自动释放。

int main()
{
	FILE * pFile = NULL;	//可以不初始化
	//打开文件
	pFile = fopen("myfile.txt", "w");	//写  输出数据（以控制台为标准）
	//文件操作
	if (pFile == NULL)
	{
		printf("open file error.\n");
		printf("%s\n", strerror(errno));
		return 0;
	}	
	fputs("fopen example", pFile);  //写入文件内容
	//关闭文件
	fclose(pFile);
	return 0;
}
```

| 文件使用方式        | 含义                                                         | 如果指定文件存在   | 如果指定文件不存在 |
| ------------------- | ------------------------------------------------------------ | ------------------ | ------------------ |
| w  只写   输出数据  | 打开一个空文件进行写入                                       | 销毁文件里面的内容 | 建立一个新的文件   |
| r  只读    输入数据 | 打开以供阅读                                                 | 打开成功           | 打开失败           |
| w+  读写            | 可读可写（文件可以不存在）                                   | 销毁文件里面的内容 | 建立一个新的文件   |
| r+  读写            | 可读可写（文件必须存在）                                     | 打开成功           | 打开失败           |
| a  追加  只写       | 向文件末尾添加数据（在写入新数据到文件之前不删除EOF标记）    | 打开成功           | 创建一个新的文件   |
| a+  追加  可读可写  | 向文件末尾添加数据（写操作只发生在文件末尾，现有数据不能被覆盖） | 打开成功           | 创建一个新的文件   |
| wb  只写            | 为了输出数据，打开一个二进制文件                             | 打开成功           | 建立一个新的文件   |
| rb  只读            | 为了输入数据，打开一个二进制文件                             | 打开成功           | 打开失败           |
| ab  追加            | 向一个二进制文件尾添加数据                                   | 打开成功           | 建立一个新的文件   |
| wb+  读写           | 为了读和写打开一个二进制文件                                 | 打开成功           | 建立一个新的文件   |
| rb+   读写          | 为了读和写打开一个二进制文件                                 | 打开成功           | 打开失败           |
| ab+  读写           | 打开一个二进制文件，在文件尾进行读和写                       | 打开成功           | 建立一个新的文件   |

```c
a：在写入新数据到文件之前不删除EOF标记的情况下，在文件的末尾打开以进行写入(追加);如果文件不存在，则首先创建该文件。
a+：打开阅读和追加;追加操作包括在新数据写入文件之前删除EOF标记，在写入完成后恢复EOF标记;如果文件不存在，则首先创建该文件。
当以“a”或“a+”访问类型打开文件时，所有写操作都发生在文件的末尾。文件指针可以使用fseek或rewind重新定位，但总是在执行任何写操作之前移回文件的末尾。因此，现有数据不能被覆盖。
“a”模式在追加到文件之前不会删除EOF标记。发生追加操作后，MS-DOS TYPE命令只显示到原始EOF标记的数据，而不显示追加到文件的任何数据。“a+”模式在附加到文件之前删除EOF标记。追加之后，MS-DOS TYPE命令显示文件中的所有数据。“a+”模式需要附加到以CTRL+Z EOF标记结束的流文件中。
当指定了“r+”、“w+”或“a+”访问类型时，允许读和写(文件被称为打开以“更新”)。但是，当您在读写之间切换时，必须有一个中间的fflush、fsetpos、fseek或rewind操作。如果需要，可以为fsetpos或fseek操作指定当前位置。

不常见的：
t：以文本(翻译)模式打开。在这种模式下，CTRL+Z在输入时被解释为文件结束字符。在使用“a+”打开的文件中，fopen检查文件末尾的CTRL+Z，如果可能的话，将其删除。这样做是因为使用fseek和ftell在以CTRL+Z结尾的文件中移动，可能会导致fseek在接近文件末尾时行为不正确。同样，在文本模式中，回车换行组合在输入时被转换为单行换行，换行字符在输出时被转换为回车换行组合。当Unicode流- i /O函数以文本模式(默认)运行时，源流或目标流被假定为多字节字符序列。因此，Unicode流输入函数将多字节字符转换为宽字符(就像调用mbtowc函数一样)。出于同样的原因，Unicode流输出函数将宽字符转换为多字节字符(就像调用wctomb函数一样)。
c：启用相关文件名的提交标志，以便在调用fflush或_flushall时将文件缓冲区的内容直接写入磁盘。
n：将相关文件名的提交标志重置为“no-commit”。这是默认值。如果你将程序链接到COMMODE.OBJ，它也会覆盖全局提交标志。全局提交标志默认为“no-commit”，除非你显式地将你的程序链接到COMMODE.OBJ。
```

## 10.3文件的读写：

```c
int main()
{
	int ar[] = { 12,23,34,45,56,67,78,89,90,100 };
	int n = sizeof(ar) / sizeof(ar[0]);
	FILE* fp = fopen("text.txt", "w");	//写操作打开文件
	if (NULL == fp)
	{
		printf("open file error.\n");
		return 0;
	}

	for (int i = 0; i < n; i++)
	{
		//printf("%d ", ar[i]);		默认往屏幕上打印
		fprintf(fp, "%d ", ar[i]);	//往打开的文件里面写入
	}

	fclose(fp);
	return 0;
}

int main()
{
	int ar[10];
	FILE*fp = fopen("text.txt", "r");	//读操作打开文件

	if (NULL == fp)
	{
		printf("open file error.\n");
		return 0;
	}

	for (int i = 0; i < 10; i++)
	{
		//scanf("%d", &ar[i]);		    //默认从键盘输入数组中
		fscanf(fp, "%d", &ar[i]);		//从文件里面输入到数组中
	}
	fclose(fp);
	return 0;
}

int main()
{
	int ar[] = { 12,23,34,45,56,67,78,89,90,100 };
	int n = sizeof(ar) / sizeof(ar[0]);
	FILE* fp = fopen("text.txt", "wb");	//写操作打开二进制文件
	if (NULL == fp)
	{
		printf("open file error.\n");
		return 0;
	}
	fwrite(ar, sizeof(int), n, fp);	  //一次性写入
	fclose(fp);
	return 0;
}

//一般不这样写
int main()
{
	FILE* fpin = fopen("test.c", "r");
	if (NULL == fpin)
	{
		printf("open input file error.\n");
		return 0;
	}

	FILE* fpout = fopen("mytest.c", "w");
	if (NULL == fpout)
	{
		printf("open output file error.\n");
		return 0;
	}

	//拷贝过程
	char ch = fgetc(fpin);
	while (ch != EOF)
	{
		fputc(ch, fpout);
		ch = fgetc(fpin);
	}
	fputc(ch, fpout);

	fclose(fpin);
	fclose(fpout);
	return 0;
}

//改进之后
int main()
{
	FILE* fpin = fopen("test.c", "r");
	if (NULL == fpin)
	{
		printf("open input file error.\n");
		return 0;
	}

	FILE* fpout = fopen("mytest.c", "w");
	if (NULL == fpout)
	{
		printf("open output file error.\n");
		return 0;
	}

	//拷贝过程
	while (!feof(fpin))		//没到末尾返回假，到末尾了返回真
	{
		char ch = fgetc(fpin);
		fputc(ch, fpout);
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}

int main()
{
	FILE* fpin = fopen("test.c", "r");
	if (NULL == fpin)
	{
		printf("open input file error.\n");
		return 0;
	}

	FILE* fpout = fopen("mytest.c", "w");
	if (NULL == fpout)
	{
		printf("open output file error.\n");
		return 0;
	}

	char buffer[256] = { 0 };

	//拷贝过程
	while (!feof(fpin))		//没到末尾返回假，到末尾了返回真
	{
		char* res = fgets(buffer, 256, fpin);		//返回值是读入字符的真实个数
		if (res == NULL)		//表示读完了
			break;
		fputs(buffer, fpout);
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}

//控制台传参
//参数：程序名称 源文件 目标文件  
int main(int argc,int* argv[])
{
	FILE* fpin = fopen(argv[1], "r");
	if (NULL == fpin)
	{
		printf("open input file error.\n");
		return 0;
	}

	FILE* fpout = fopen(argv[2], "w");
	if (NULL == fpout)
	{
		printf("open output file error.\n");
		return 0;
	}

	char buffer[256] = { 0 };

	//拷贝过程
	while (!feof(fpin))		//没到末尾返回假，到末尾了返回真
	{
		char* res = fgets(buffer, 256, fpin);		//返回值是读入字符的真实个数
		if (res == NULL)		//表示读完了
			break;
		fputs(buffer, fpout);
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}

//二进制读写图片、音频
//控制台传参
//参数：程序名称 源文件 目标文件  
int main(int argc,int* argv[])
{
	FILE* fpin = fopen(argv[1], "rb");
	if (NULL == fpin)
	{
		printf("open input file error.\n");
		return 0;
	}

	FILE* fpout = fopen(argv[2], "wb");
	if (NULL == fpout)
	{
		printf("open output file error.\n");
		return 0;
	}

	char buffer[256] = { 0 };

	//拷贝过程
	while (!feof(fpin))		//没到末尾返回假，到末尾了返回真
	{
		size_t sz = fread(buffer, sizeof(char), 256, fpin);
		if (sz == 0)
			break;
		fwrite(buffer, sizeof(char), sz, fpout);
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}
```

## 10.4文件的读写函数查询：

```c
文件的顺序读写：
字符输入函数：适用于所有输入流；
fgetc：从流中读取一个字符
函数原型：int fgetc( FILE *stream );
返回值：fgetc将读取的字符作为int返回，或返回EOF以指示错误或文件结束。对于这个函数，使用feof或ferror来区分错误和文件结束条件。对于fgetc，如果发生读错误，流的错误指示器将被设置。
参数：stream：流、指向FILE结构的指针
函数中的每一个都从文件的当前位置读取一个字符;在fgetc的情况下，这是与流相关的文件。然后，该函数将相关的文件指针(如果定义了)递增到指向下一个字符。如果流位于文件的末尾，则设置流的文件结束指示器。 
int main()
{
	FILE *stream;
	char buffer[81];
	int  i, ch;

	//打开文件，从中读取
	if ((stream = fopen("test.c", "r")) == NULL)		//打开文件返回空指针表示错误
		exit(0);

	//读入前80个字符并将其放入“缓冲区”
	ch = fgetc(stream);
	for (i = 0; (i < 80) && (feof(stream) == 0); i++)		//不是文件末尾feof返回0
	{
		buffer[i] = (char)ch;
		ch = fgetc(stream);
	}

	//将null添加到结束字符串
	buffer[i] = '\0';
	printf("%s\n", buffer);		//读到数组（缓冲区）里面进行打印
	fclose(stream);
	return 0;
} 
    
字符输出函数：适用于所有输出流；
fputc：将字符写入流
函数原型：int fputc( int c, FILE *stream );
返回值：函数返回已写入的字符。对于fputc,EOF的返回值表示错误。 
参数：c：待写字符	stream：流、指向FILE结构的指针
这个函数中的每一个都将单个字符c写入到相关文件位置指示符(如果定义了)所指示的位置，并适当前进该指示符。在fputc的情况下，文件与流相关联。如果文件不支持定位请求或以追加模式打开，则将字符追加到流的末尾。 
int main()
{
	char strptr1[] = "This is a test of fputc!\n";
	char *p;

	//Print line to stream using fputc.   
	p = strptr1;
	while ((*p != '\0') && fputc(*(p++), stdout) != EOF);	//屏幕上输出：This is a test of fputc!	
	return 0;
}
    
文本行输入函数：适用于所有输入流
fgets：从流中获取字符串。
函数原型：char *fgets( char *string, int n, FILE *stream );
返回值：这些函数都返回string。返回NULL表示错误或文件结束条件。使用feof或error来确定是否发生了错误。
参数：string：数据存储位置（字符串）	n：要读取的最大字符数		stream：指向FILE结构的指针
fgets函数从输入流参数中读取一个字符串，并将其存储在string中。fgets从当前流位置读取字符，直到并包括第一个换行字符，直到流的末尾，或者直到读取的字符数等于n； 以先到的为准。存储在string中的结果附加一个空字符。换行符如果被读取，则包含在字符串中。
fgets类似于gets函数;但是，gets将换行符替换为NULL。
//这个程序使用fgets来显示屏幕上文件中的一行
int main()
{
	FILE *stream;
	char line[100];

	if ((stream = fopen("test.c", "r")) != NULL)
	{
		//fgets返回值：返回NULL表示错误或文件结束条件
		if (fgets(line, 100, stream) == NULL)	//从stream流指向的文件中读取100个字符(按行读取字符，一行只有20个就读取20个)放入到line字符数组中
			printf("fgets error\n");
		else
			printf("%s", line);
		fclose(stream);
	}
	return 0;
}

文本行输出函数：适用于所有输出流
fputs：将字符串写入流
函数原型：int fputs( const char *string, FILE *stream );
返回值：如果执行成功，函数返回一个非负值。如果发生错误，fputs返回EOF。
参数：string：输出字符串		stream：指向FILE结构的指针
fputs函数将字符串复制到当前位置的输出流。 
//这个程序使用fputs来写向标准输出流输出一行
int main()
{
	fputs("Hello world from fputs.\n", stdout);	//向屏幕输出Hello world from fputs.
	return 0;
}   
    
格式化输入函数：适用于所有输入流（fscanf从文件中读取各种数据）（文件输入）
fscanf：从流中读取格式化的数据。
函数原型：int fscanf( FILE *stream, const char *format [, argument ]... ) ;
返回值：这些函数中的每一个都返回成功转换和分配的字段数;返回值不包括已读取但未分配的字段。返回值为0表示没有分配字段。如果发生错误，或者在第一次转换之前到达文件流的末尾，则返回值为fscanf的EOF
参数：stream：指向FILE结构的指针	format：格式（格式控制字符串 论点 可选参数）（和scanf格式一样） 
fscanf函数将数据从流的当前位置读入参数指定的位置(如果有的话)。每个实参必须是指向类型变量的指针，该变量在格式上对应于类型说明符。format控制输入字段的解释，具有与scanf的format参数相同的形式和功能;有关格式的说明和scanf用法相同，如果复制发生在重叠的字符串之间，则行为未定义。
//这个程序写入格式化数据到文件。然后使用fscanf来从文件中读取各种数据。
int main()
{
	FILE *stream;
	long l;
	float fp;
	char s[81];
	char c;

	stream = fopen("fscanf.out", "w+");
	if (stream == NULL)
		printf("The file fscanf.out was not opened\n");
	else
	{
		fprintf(stream,"%s %ld %f %c","a-string",65000, 3.14159, 'x');
		//设置指针到文件的开头
		fseek(stream, 0L, SEEK_SET);
		//从文件中读回数据
		fscanf(stream, "%s", s);
		fscanf(stream, "%ld", &l);
		fscanf(stream, "%f", &fp);
		fscanf(stream, "%c", &c);
		//输出数据读取
		printf("%s\n", s);
		printf("%ld\n", l);
		printf("%f\n", fp);
		printf("%d\n", c);	//32
		fclose(stream);
	}
	return 0;
}
    
格式化输出函数：适用于所有输出流（fprintf把数据输出到文件）
fprintf：将格式化的数据打印到流。
函数原型：int fprintf( FILE *stream, const char *format [, argument ]...);
返回值：fprintf返回写入的字节数。当发生输出错误时，这个函数返回一个负值。
参数：stream：指向FILE结构的指针	format：格式（格式控制字符串 论点 可选参数）（和printf格式一样）
fprintf格式化并打印一系列字符和值到输出流。每个函数参数(如果有的话)都会根据format中相应的格式规范进行转换和输出。对于fprintf, format参数具有与printf相同的语法和用法。
//这个程序使用fprintf来格式化各种并将其打印到名为fprintf.out的文件中。它然后显示fprintf。在屏幕上使用系统函数调用操作系统type命令。
int main()
{
	FILE *stream;
	int i = 10;
	double fp = 1.5;
	char s[] = "this is a string";
	char c = '\n';
	stream = fopen("fprintf.out", "w");
	fprintf(stream, "%s%c", s, c);
	fprintf(stream, "%d\n", i);
	fprintf(stream, "%f\n", fp);
	fclose(stream);
	system("type fprintf.out");		//输出写到文件中的内容
	return 0;
}

二进制输入函数：适用于文件
fread：从流中读取数据
函数原型：size_t fread( void *buffer, size_t size, size_t count, FILE *stream );
返回值：fread返回实际读取的完整条目的数量，如果发生错误或在到达count之前遇到文件结束，则可能小于count。使用feof或error函数来区分读取错误和文件结束条件。如果size或count为0，则fread返回0，缓冲区内容保持不变。
参数：buffer：数据存储位置	size：字节大小(以字节为单位)	count：要读取的最大个数	stream：指向FILE结构的指针
fread函数从输入流中读取并计数大小为字节的项，并将它们存储在缓冲区中。与流相关联的文件指针(如果有的话)会增加实际读取的字节数。如果给定的流以文本模式打开，则回车换行对将被替换为单行换行字符。替换对文件指针或返回值没有影响。如果发生错误，文件指针的位置是不确定的。无法确定部分读取项的值。

二进制输出函数：适用于文件
fwrite：将数据写入流。
函数原型：size_t fwrite( const void *buffer, size_t size, size_t count, FILE *stream );
返回值：fwrite返回实际写入的完整个数，如果发生错误，可能小于count。此外，如果发生错误，则无法确定文件位置指示符。
参数：buffer：指向要写入的数据的指针	size：类型大小(以字节为单位)	count：要写入的最大条目数		stream：指向FILE结构的指针
fwrite函数从缓冲区向输出流写入计数项(每个项的大小为length)。与流相关联的文件指针(如果有的话)按实际写入的字节数递增。如果以文本模式打开stream，则每个回车符将被替换为回车符换行符。替换对返回值没有影响。
//这个程序打开一个名为fread的文件。向文件中写入25个字符。然后它试图打开从文件中读。输出和读取25个字符。如果尝试成功，程序显示实际项目读取的数量。
int main()
{
	FILE *stream;
	char list[30];
	int  i, numread, numwritten;
	//以文本模式打开文件   模式t是文本模式
	if ((stream = fopen("fread.out","w+t")) != NULL)
	{
		for (i = 0; i < 25; i++)
			list[i] = (char)('z' - i);
		//写25个字符到流
		numwritten = fwrite(list, sizeof(char), 25, stream);		//返回值25(字节数)
		printf("Wrote %d items\n", numwritten);	//25
		fclose(stream);

	}
	else
		printf("Problem opening the file\n");

	if ((stream = fopen("fread.out", "r+t")) != NULL)
	{
		//试着读25个字符 
		numread = fread(list, sizeof(char), 25, stream);
		printf("Number of items read = %d\n", numread);		//字符个数：25
		printf("Contents of buffer = %.25s\n", list);		//zyxwvutsrqponmlkjihgfedcb			%.25s表示字符串输出25个字符
		fclose(stream);
	}
	else
		printf("File could not be opened\n");
	return 0;
}

feof：测试流上的文件结束符（EOF）。
函数原型：int feof( FILE *stream );
返回值：feof函数在第一次读取操作之后返回一个非零值，该操作试图读取超过文件末尾的内容。如果当前位置不是文件末尾，则返回0。没有错误返回。
参数：stream：流、指向FILE结构的指针
feof确定是否已到达流的结束。当到达文件末尾时，读操作返回文件结束指示符，直到流关闭或对其调用rewind、fsetpos、fseek或clearerr为止。

ferror：测试流上的错误。
函数原型：int ferror( FILE *stream );
返回值：如果流上没有发生错误，ferror返回0。否则，它返回一个非零值。
参数：stream：流、指向FILE结构的指针
ferror测试与流相关的文件上的读写错误。如果发生了错误，流的错误指示器将保持设置，直到流关闭或重绕，或者直到对其调用clearerr。
int main()
{
	int  count, total = 0;
	char buffer[100];
	FILE *stream;

	if ((stream = fopen("test.c", "r")) == NULL)
		exit(1);

	//循环直到到达文件末尾
	while (!feof(stream))	//feof返回0表示当前位置不是文件末尾
	{
		//尝试读入100个字节
		count = fread(buffer, sizeof(char), 100, stream);
		if (ferror(stream)) {		//读没有错误返回0，有错误返回非0
			perror("Read error");	//打印错误信息
			break;
		}

		//实际读取的字节总数
		total += count;
	}
	printf("Number of bytes read = %d\n", total);	//读取文件有多少字节
	fclose(stream);
	return 0;
}

perror：打印错误信息
函数原型：void perror( const char *string );
返回值：没有
参数：字符串、要打印的字符串消息
perror函数将错误消息打印到stderr，只打印系统错误消息。
错误编号存储在变量errno中(在errno.h中定义，是一个全局变量)。系统错误消息是通过变量_sys_errlist访问的，该变量是一个按错误号排序的消息数组。Perror使用errno值作为_sys_errlist的索引打印相应的错误消息。变量_sys_nerr的值定义为_sys_errlist数组中的最大元素数。为了获得准确的结果，在库例程返回错误后立即调用perror。否则，后续调用会覆盖errno值。
在Windows NT和Windows 95中，errno.h中列出的一些errno值是未使用的。这些值被保留供UNIX操作系统使用。请参阅_doserrno, errno， _sys_errlist和_sys_nerr查看Windows NT和Windows 95使用的errno值列表。Perror为这些平台未使用的任何errno值打印空字符串。
int main()
{
	FILE* fh;
	if (!(fh = fopen("test.c", "r")))			//fopen返回空指针表示打开错误  test.c存在打印另一边else三条语句
	{
		printf("open succeeded on input file\n");
	}
	else
	{
		//创建错误消息的三种方法
		perror("perror says open failed");			//strerror says open failed:No error
		printf("strerror says open failed: %s\n", strerror(errno));	//strerror says open failed:No error
		printf(_strerror("_strerror says open failed"));	//strerror says open failed:No error
		fclose(fh);
    }
	return 0;
}

文件的随机读写：
fseek：将文件指针移动到指定位置。
函数原型：int fseek( FILE *stream, long offset, int origin );
返回值：如果成功，fseek返回0。否则，它返回一个非零值。在无法查找的设备上，返回值未定义。
参数：stream：指向FILE结构的指针	offset：距离原点的字节数（偏移量）		origin：初始位置
fseek函数将与流相关的文件指针(如果有的话)移动到距离原点偏移字节的新位置。流上的下一个操作发生在新的位置。在为更新而打开的流上，下一个操作可以是读或写。参数origin必须是下列常量之一，在STDIO.H中定义:SEEK_CUR：文件指针的当前位置		SEEK_END：文件结束		SEEK_SET：文件开头
可以使用fseek重新定位文件中任何位置的指针。指针也可以位于文件末尾以外的位置。fseek清除文件结束指示符，并消除任何先前对流调用ungetc的影响。（ungetc：把一个（或多个）字符退回到stream代表的文件流中，可以理解成一个“计数器”。）
当打开文件追加数据时，当前文件位置由最后一次I/O操作决定，而不是由下一次写操作发生的位置决定。如果为追加而打开的文件尚未发生I/O操作，则文件位置是文件的开始。
对于以文本模式打开的流，fseek的用途有限，因为回车换行转换可能导致fseek产生意想不到的结果。保证在以文本模式打开的流上工作的唯一fseek操作是:以相对于任何原点值的0偏移量进行查找。使用调用ftell返回的偏移值从文件的开头开始查找。
同样在文本模式下，CTRL+Z在输入时被解释为文件结束字符。在为读/写打开的文件中，fopen和所有相关例程检查文件末尾的CTRL+Z，并在可能的情况下删除它。这样做是因为使用fseek和ftell在以CTRL+Z结束的文件中移动可能会导致fseek在文件末尾附近的行为不正确。
//这个程序打开文件fseek,将指针移动到文件的开头。
int main()
{
	FILE *stream;
	char line[81];
	int  result;

	stream = fopen("fseek.out", "w+");
	if (stream == NULL)
		printf("The file fseek.out was not opened\n");
	else
	{
		fprintf(stream,"The fseek begins here:""This is the file 'fseek.out'.\n");	//写到文件中
		result = fseek(stream, 23L, SEEK_SET);	//从文件开头移动23个长度(23后面有没有L没区别)
		if (result)
			perror("Fseek failed");
		else
		{
			printf("File pointer is set to middle of first line.\n");
			fgets(line, 80, stream);	//从文件中读取一行，最大为80个字符
			printf("%s", line);
		}
		fclose(stream);
	}
	return 0;
	//输出：
	//File pointer is set to middle of first line.
	//his is the file 'fseek.out'.
}

int main()
{
	FILE * pFile;
	pFile = fopen("example.txt", "wb");
	fputs("This is an apple.", pFile);		//写到文件
	fseek(pFile, 9, SEEK_SET);				//从文件开头位置移动9个
	fputs(" sam", pFile);					//写到文件
	fclose(pFile);
	return 0;
	//文件中的内容：This is a sample.
}

ftell：获取文件指针的当前位置（返回文件指针相对于起始位置的偏移量）
函数原型：long ftell( FILE *stream );
返回值：ftell返回当前文件位置。ftell返回的值可能不会反映在文本模式下打开的流的物理字节偏移量，因为文本模式会导致回车换行转换。使用ftell和fseek来正确返回文件位置。出现错误时，ftell返回-1,errno被设置为errno.h中定义的两个常量之一。EBADF常量意味着stream参数不是一个有效的文件句柄值，或者没有引用一个打开的文件。EINVAL表示传递给函数的流参数无效。在无法查找的设备上(如终端和打印机)，或者当流没有指向打开的文件时，返回值是未定义的。
参数：stream：目标文件流、指针
ftell函数获取与流相关的文件指针(如果有的话)的当前位置。该位置表示为相对于流开头的偏移量。
请注意，当打开文件以附加数据时，当前文件位置由最后一次I/O操作决定，而不是由下一次写操作发生的位置决定。例如，如果打开一个文件进行追加操作，而上一次操作是读操作，则文件位置是下一次读操作开始的位置，而不是下一次写操作开始的位置。(当打开文件进行追加操作时，在进行任何写操作之前，文件位置将移动到文件末尾。)如果为追加而打开的文件尚未发生I/O操作，则文件位置是文件的开头。
在文本模式下，CTRL+Z在输入时被解释为文件结束字符。在为读/写打开的文件中，fopen和所有相关例程检查文件末尾的CTRL+Z，并在可能的情况下删除它。这样做是因为使用ftell和fseek在以CTRL+Z结束的文件中移动可能会导致ftell在文件末尾附近的行为不正确。
//这个程序打开一个名为test.c的文件用于阅读，并尝试阅读100个字符。它然后使用ftell来确定文件指针并显示此位置。
int main()
{

	FILE *stream;
	long position;
	char list[100];
	if( (stream = fopen( "test.c", "rb" )) != NULL )		//打开
	{
		//通过读取数据移动指针 
		fread(list, sizeof(char), 100, stream);		//从stream中读取100个字符到list中
		//读取后获取位置
		position = ftell(stream);
		printf("Position after trying to read 100 bytes: %ld\n",position);
		fclose(stream);
	}
	return 0;
	//输出：Position after trying to read 100 bytes: 100
}

int main()
{
	FILE * pFile;
	long size;
	pFile = fopen("test.c", "rb");
	if (pFile == NULL) 
		perror("Error opening file");	//Error opening file: No such file or directory
	else
	{
		fseek(pFile, 0, SEEK_END); //偏移到文件末尾
		size = ftell(pFile);		//统计文件总共多少个字节
		fclose(pFile);
		printf("Size of myfile.txt: %ld bytes.\n", size);	//Size of myfile.txt: 30905 bytes.
	}
	return 0;
}

rewind：将文件指针重新定位到文件的开头
函数原型：void rewind( FILE *stream );
返回值：无返回值
参数：stream：指向FILE结构的指针
rewind函数将与流相关的文件指针重新定位到文件的开头。rewind函数调用类似于(void) fseek(stream, 0L, SEEK_SET);
然而，与fseek不同的是，rewind清除流的错误指示符以及文件结束指示符。此外，与fseek不同，rewind不返回一个值来指示指针是否成功移动。
函数原型：int fseek( FILE *stream, long offset, int origin );	如果成功，fseek返回0。否则，它返回一个非零值。
要清除键盘缓冲区，请使用流stdin的rewind，它在默认情况下与键盘相关联。
//rewindc:这个程序首先打开一个名为rewind.out表示输入和输出，并写入两个整数的文件。接下来，它使用rewind来将文件指针重新定位到文件并将数据读入
int main()
{
	FILE *stream;
	int data1, data2;

	data1 = 1;
	data2 = -37;

	if ((stream = fopen("rewind.out", "w+")) != NULL)
	{
		fprintf(stream, "%d %d", data1, data2);		//写入文件
		printf("The values written are: %d and %d\n", data1, data2);
		rewind(stream);
		fscanf(stream, "%d %d", &data1, &data2);	//文件输入
		printf("The values read are: %d and %d\n", data1, data2);	//-1	-37
		fclose(stream);
	}
	return 0;
}

int main()
{
	int n;
	FILE * pFile;
	char buffer[27];
	pFile = fopen("myfile.txt", "w+");
	for (n = 'A'; n <= 'Z'; n++)
		fputc(n, pFile);	//按字符写入文件
	rewind(pFile);
	fread(buffer, 1, 26, pFile);	//从pFILE流中读取26个字符
	fclose(pFile);
	buffer[26] = '\0';
	puts(buffer);	//打印	ABCDEFGHIJKLMNOPQRSTUVWXYZ
	return 0;
} 
```

## 10.5文件其余概念：

```c
文本文件和二进制文件：
根据数据的组织形式，数据文件被称为文本文件或者二进制文件。
数据在内存中以二进制的形式存储，如果不加转换的输出到外存，就是二进制文件。
如果要求在外存上以ASCII码的形式存储，则需要在存储前转换。以ASCII字符的形式存储的文件就是文本文件。

一个数据在内存中是怎么存储的呢？
字符一律以ASCII形式存储，数值型数据既可以用ASCII形式存储，也可以使用二进制形式存储。
如有整数10000，如果以ASCII码的形式输出到磁盘，则磁盘中占用5个字节（每个字符一个字节），而二进制形式输出，则在磁盘上只占4个字节（VS2019测试）。
//测试代码：
int main()
{
	int a = 10000;
	FILE* pf = fopen("test.txt", "w");		 
	fwrite(&a, sizeof(int), 1, pf);	//二进制写入到文件  把a传入到文件
	fclose(pf);
	pf = NULL;
	return 0;
}

文件读取结束的判定：
feof的使用：在文件读取过程中，不能用feof函数的返回值直接用来判断文件的是否结束，而是应用于当文件读取结束的时候，判断是读取失败结束，还是遇到文件尾结束。
1.文本文件读取是否结束，判断返回值是否为EOF（fgetc），或者NULL（fgets）
例如：fgetc 判断是否为EOF或者fgets判断返回值是否为NULL
2.二进制文件的读取结束判断，判断返回值是否小于实际要读的个数。
例如：fread判断返回值是否小于实际要读的个数
//文本文件的例子：
int main(void)
{
	int c;	//注意：int，非char，要求处理EOF
	FILE* fp = fopen("test.c", "r");
	if (!fp) {	//读取失败
		perror("File opening failed");
		return EXIT_FAILURE;	//#define EXIT_FAILURE 1			
	}
	//fgetc 当读取失败的时候或者遇到文件结束的时候，都会返回EOF
	while ((c = fgetc(fp)) != EOF)  
	{
		putchar(c);
	}
	//判断是什么原因结束的
	if (ferror(fp))			//没有返回值，打印错误信息
		puts("I/O error when reading");
	else if (feof(fp))		
    //feof函数在第一次读取操作之后返回一个非零值，该操作试图读取超过文件末尾的内容。如果当前位置不是文件末尾，则返回0。没有错误返回。
		puts("End of file reached successfully");
	fclose(fp);
}
 
//二进制文件的例子：
int main()
{
	double a[5] = { 1,2,3,4,5 };
	FILE *fp = fopen("test.bin", "wb"); // 必须用二进制模式
	fwrite(a, sizeof(*a), 5, fp); // 写double的数组
	fclose(fp);

	double b[5];
	fp = fopen("test.bin", "rb");
	size_t ret_code = fread(b, sizeof(*b), 4, fp); // 读double的数组
	if (ret_code == 5) {
		puts("Array read successfully, contents: ");
		for (int n = 0; n < 5; ++n) printf("%f ", b[n]);
		putchar('\n');
	} 
	else { //错误处理
		if (feof(fp))
			printf("Error reading test.bin: unexpected end of file\n");
		else if (ferror(fp)) {
			perror("Error reading test.bin");
		}
	}
	fclose(fp);
	return 0;
}

文件缓冲区：
ANSIC标准采用“缓冲文件系统”处理的数据文件的，所谓缓冲文件系统是指系统自动地在内存中为程序中每一个正在使用的文件开辟一块“文件缓冲区”。从内存向磁盘输出数据会先送到内存中的缓冲区，装满缓冲区后才一起送到磁盘上。如果从磁盘向计算机读入数据，则从磁盘文件中读取数据输入到内存缓冲区（充满缓冲区），然后再从缓冲区逐个地将数据送到程序数据区（程序变量等）。缓冲区的大小根据C编译系统决定的。
int main()
{
	FILE* pf = fopen("test.txt", "w");
	fputs("abcdef", pf);//先将代码放在输出缓冲区
	printf("睡眠10秒-已经写数据了，打开test.txt文件，发现文件没有内容\n");
	Sleep(10000);
	printf("刷新缓冲区\n");
	fflush(pf);//刷新缓冲区时，才将输出缓冲区的数据写到文件（磁盘）
	//fflush 在高版本的VS上不能使用了
	printf("再睡眠10秒-此时，再次打开test.txt文件，文件有内容了\n");
	Sleep(10000);
	fclose(pf);
	//fclose在关闭文件的时候，也会刷新缓冲区
	pf = NULL;
	return 0;
}
这里可以得出一个结论：
因为有缓冲区的存在，C语言在操作文件的时候，需要做刷新缓冲区或者在文件操作结束的时候关闭文件。
如果不做，可能导致读写文件的问题。
    
int main()
{
	FILE *stream;
	char *p, buffer[] = "This is the line of output\n";
	int ch = 0;
	//创建标准的流并写入它
	stream = stdout;
	for (p = buffer; (ch != EOF) && (*p != '\0'); p++)
		ch = putc(*p, stream);
	return 0;
	//输出结果：This is the line of output
}
```

# 11程序环境：

```c
程序的翻译环境和执行环境：
在ANSI C的任何一种实现中，存在两个不同的环境。第1种是翻译环境，在这个环境中源代码被转换为可执行的机器指令。 第2种是执行环境，它用于实际执行代
码。

翻译环境：
组成一个程序的每个源文件通过编译过程分别转换成目标代码（object code）。
每个目标文件由链接器（linker）捆绑在一起，形成一个单一而完整的可执行程序。
链接器同时也会引入标准C函数库中任何被该程序所用到的函数，而且它可以搜索程序员个人的程序库，将其需要的函数也链接到程序中。

源文件：gcc -o test test.c
预处理：
	gcc -o test.i -E test.c
	展开头文件   宏替换   不进行语法检查  生成预处理文件
编译：
	gcc -o test.s -S test.i
	进行语法、词法、语义检查、符号汇总  生成汇编文件
汇编：
	gcc -o test.o -c test.s
	生成可重定位目标文件	形成符号表  汇编指令变成二进制指令
链接：
	gcc -o test test.o
	合并段表	符号表的合并和符号表的重定位		生成最终的可执行文件
总结：隔离编译，一起链接
文件：.i预处理文件
	 .s汇编文件
	 .o目标文件

执行环境（运行环境）：
1. 程序必须载入内存中。在有操作系统的环境中：一般这个由操作系统完成。在独立的环境中，程序的载入必须
由手工安排，也可能是通过可执行代码置入只读内存来完成。
2. 程序的执行便开始。接着便调用main函数。
3. 开始执行程序代码。这个时候程序将使用一个运行时堆栈（stack），存储函数的局部变量和返回地址。程序同
时也可以使用静态（static）内存，存储于静态内存中的变量在程序的整个执行过程一直保留他们的值。
4. 终止程序。正常终止main函数；也有可能是意外终止。

linux：
	编辑器  vim
	编译器  gcc/g++
	调试器	 gdb
	make   多文件自动化编译
vim的学习：
	https://coolshell.cn/articles/5426.html
	https://coolshell.cn/articles/5479.html

预处理：
预定义符号：
__FILE__ //进行编译的源文件
__LINE__ //文件当前的行号
__DATE__ //文件被编译的日期
__TIME__ //文件被编译的时间
__STDC__ //如果编译器遵循ANSI C，其值为1，否则未定义
//使用： 
int main()
{
	printf("%s\n", __FILE__);	//c:\users\19827\source\repos\tests\testc\test.c
	printf("%d\n", __LINE__);	//14	当前所在行数
	printf("%s\n", __DATE__);	//Apr 17 2023
	printf("%s\n", __TIME__);	//06:56:16
	return 0;
}

//日志
void log(char* msg)
{
	printf("log:%s:%d:%s:%s:%s\n", __FILE__, __LINE__, __DATE__, __TIME__, msg);
}

int main()
{
	FILE* fp = fopen("test.txt", "r");
	if (fp == NULL)
	{
		log("open file error.");
		return;		// return 0;
	}
	log("open file ok.");
	return 0;
}

//上面代码的缺陷是行号永远不变，下面进行改进
//日志
void log(int line, char* msg)	//参数也可以有char* file  __FILE__可以用file替换
{
	printf("log:%s:%d:%s:%s:%s\n", __FILE__, line, __DATE__, __TIME__, msg);
}

#define log(msg) log(__LINE__,msg)

int main()
{
	FILE* fp = fopen("test.txt", "r");
	if (fp == NULL)
	{
		log("open file error.");
		return;		// return 0;
	}
	log("open file ok.");
	return 0;
}

#define	定义标识符
//续行符：缺点是这样的代码不好找错误，比如在续行符（\）后面加上一个空格，就会报错，还不好找
#define my_str "djdjslddsdasld\
dsdsdasdasdasdasd\
dsdasdsfdsdsdsd"

int main()
{
	printf("%s", my_str);
	return 0;
}

#define PRINT(FORMAT, VALUE)\
printf("the value is "  FORMAT  "\n", VALUE);

int main()
{
	PRINT("%d", 10);	//the value is 25 
	return 0;
} 

字符串是有自动连接的特点的。
int main()
{
	char* p = "hello ""bit\n";
	printf("hello", " bit\n");	//hello	 
	printf("%s", p);	//hello bit
	return 0;
}

//# 取值 	#x会预处理器处理为"x"
#define SQUARE(x) printf(#x "*" #x "= %d\n",((x) * (x)));	//使用宏需要注意的是不要节省括号

int main()
{
	SQUARE(5);	//25
	return 0;
}

#define PRINT(FORMAT, VALUE)\
printf("the value of " #VALUE " is "FORMAT "\n", VALUE);

int main()
{
	int i = 10;
 	PRINT("%d", i + 3);	//the value of i + 3 is 13
	return 0;
}


//## 连接符
#define MY_STRUCT(name)\
struct struct_##name\
{\
	int a;\
	int b;\
	int c;\
}

//结构体类型
MY_STRUCT(wn);
MY_STRUCT(bss);

int main()
{
	struct struct_wn wn;
	return 0;
}


#define ADD_TO_SUM(num, value) sum##num += value;

int main()
{ 	
	int sum5;	//没有这个定义sum5是不对的
	ADD_TO_SUM(5, 10);	////作用是：给sum5增加10
	return 0;
}

这样的连接必须产生一个合法的标识符。否则其结果就是未定义的。
备注：##不要经常使用，容易出错；

注意：
1.宏参数和#define定义中可以出现其他#define定义的变量。但是对于宏，不能出现递归。
2.当预处理器搜索#define定义的符号的时候，字符串常量的内容并不被搜索。
3.带副作用的宏参数：当宏参数在宏的定义中出现超过一次的时候，如果参数带有副作用，那么你在使用这个宏的时候就可能出现危险，导
致不可预测的后果。副作用就是表达式求值的时候出现的永久性效果。

#define MAX(a, b) ( (a) > (b) ? (a) : (b) )

int main()
{
	int x = 5;
	int y = 8;
	int z = MAX(x++, y++);
	printf("x=%d y=%d z=%d\n", x, y, z);	//输出：x = 6 y = 10 z = 9
	return 0;
}

int main()
{
	#define MALLOC(num, type)\
	(type *)malloc(num * sizeof(type))
	MALLOC(10, int);//类型作为参数			//预处理器替换之后：(int *)malloc(10 * sizeof(int));
	return 0;
}
```



| 属性             | #define定义宏                                                | 函数                                                         |
| ---------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 代码长度         | 短，每次使用时，宏代码都会被插入到程序中。除了非常小的宏之外，程序的长度会大幅度增长。 | 长，函数代码只会出现在一个地方，每次使用这个函数时，都调用那个地方的同一份代码。 |
| 执行速度         | 快，不用调用函数，不会产生开销，实际执行小型计算工作时间短。 | 慢，存在函数的调用和返回的额外开销，所以相对慢一些。         |
| 操作符优先级     | 宏参数的求值是在所有周围表达式的上下文环境里，除非加上括号，否则邻近操作符的优先级可能会产生不可预料的后果，所以建议宏在书写的时候全部加括号。 | 函数参数只在函数调用的时候求值一 次，它的结果值传递给函数。表达式的求值结果更容易预测。 |
| 带有副作用的参数 | 参数可能被替换到宏体中的多个位置，所以带有副作用的参数求值可能会产生不可预料的结果。 | 函数参数只在传参的时候求值一次， 结果更容易控制。            |
| 参数类型         | 宏的参数与类型无关，只要对参数的操作是合法的，它就可以使用于任何参数类型。 | 函数的参数是与类型有关的，如果参数的类型不同，就需要不同的函数， 即使他们执行的任务是不同的。 |
| 调试             | 宏是不方便调试的。                                           | 函数是可以逐语句调试的。                                     |
| 递归             | 宏是不能递归的。                                             | 函数是可以递归的。                                           |
| 命名约定         | 把宏名全部大写。                                             | 函数名单词首字母大写剩下小写。                               |

```c
#undef：这条指令用于移除一个宏定义。
#undef NAME		//如果现存的一个名字需要被重新定义，那么它的旧名字首先要被移除。

//命令行提供数组大小进行编译（linux）
int main()
{
	int array[ARRAY_SIZE];
	int i = 0;
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		array[i] = i;
	}
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}
编译指令：gcc -D ARRAY_SIZE=10 programe.c

条件编译：
1.
#if 常量表达式
//...
#endif
//常量表达式由预处理器求值。
如：
#define __DEBUG__ 1
#if __DEBUG__
//..
#endif
2.多个分支的条件编译
#if 常量表达式
//...
#elif 常量表达式
//...
#else
//...
#endif
3.判断是否被定义
#if defined(symbol)
#ifdef symbol
    
#if !defined(symbol)
#ifndef symbol
4.嵌套指令
#if defined(OS_UNIX)
		#ifdef OPTION1
				unix_version_option1();
		#endif
		#ifdef OPTION2
				unix_version_option2();
		#endif
#elif defined(OS_MSDOS)
		#ifdef OPTION2
				msdos_version_option2();
		#endif
#endif
      
文件包含（头文件）：
本地文件包含：#include <filename.h>
库文件包含：#include <stdio.h>			库文件也可以使用 #include "stdio.h"包含，但是这样做查找的效率就低些，当然这样也不容易区分是库文件还是本地文件了。（原因：是先在本地文件下查找，再在库文件路径下查找）
linux环境的标准头文件的路径：/usr/include
vs环境的标准头文件的路径：C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\include（这个不同版本会有略微不同，不过都在include中）（安装路径）
嵌套文件包含的解决措施：条件编译
头文件的内容：
#ifndef __TEST_H__
#define __TEST_H__
#endif //__TEST_H__
或者#pragma once就可以避免头文件的重复引入

其他预处理指令：
    #error
    #pragma
    #line
    #pragma pack()
```















































































































