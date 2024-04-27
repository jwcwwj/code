#include <iostream>
#include <time.h>

using namespace std;

//1. 普通的命名空间
namespace N1 // N1为命名空间的名称
{
	// 命名空间中的内容，既可以定义变量，也可以定义函数
	int a = 10;
	int Add(int left, int right)
	{
		return left + right;
	}
}

//2. 命名空间可以嵌套
namespace N2
{
	int a = 20;
	int b = 30;
	int Add(int left, int right)
	{
		return left + right;
	}
	namespace N3	//嵌套命名空间
	{
		int c = 40;
		int d = 50;
		int Sub(int left, int right)
		{
			return left - right;
		}
	}
}

//3. 同一个工程中允许存在多个相同名称的命名空间,编译器最后会合成同一个命名空间中。
namespace N1
{
	int Mul(int left, int right)
	{
		return left * right;
	}
}

void test1()
{
	//命名空间的三种使用方式
	//01加命名空间名称及作用域限定符	推荐使用	个人喜欢第一种
	cout << "N1::a = " << N1::a << endl;	//10
	cout << "N2::N3::c - N2::b = " << N2::N3::Sub(N2::N3::c, N2::b) << endl;	//10
	//cout << "N2::N3::c - N2::b = " << N2::N3::Sub(c, N2::b) << endl;			//error
	//cout << "N2::N3::c - N2::b = " << N2::N3::Sub(N2::N3::c,b) << endl;			//error
	//02使用using将命名空间中成员引入	推荐使用，但一般不使用	在空间嵌套多的时候使用，一般使用第一种
	using N2::N3::c;
	cout << "N2::N3::c - N2::b = " << N2::N3::Sub(c, N2::b) << endl;	//10
	using N2::b;
	cout << "N2::N3::c - N2::b = " << N2::N3::Sub(c, b) << endl;			//10
	using N1::a;
	cout << a << endl;		//10
	//03使用using namespace 命名空间名称引入	不推荐使用		在多人合作开发的时候容易产生冲突
	using namespace N1;
	cout << a << endl;	//10
}

//全缺省参数
void TestFunc(int a = 10, int b = 20, int c = 30)
{
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}

//半缺省参数
void TestFunc1(int a, int b = 10, int c = 20)
{
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}

void test2()
{
	//constexpr关键字，c++11新赠的
	//constexpr关键字可以让一个变量变成编译时常量
	constexpr int a = 5;
	int arr[a];
	for (int i = 0; i < a; i++)
	{
		arr[i] = i;
	}
	for (int i = 0; i < a; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int add(int a, int b)
{
	return a + b;
}

//参数类型不同
int add(char a, int b)
{
	return a + b;
}

//参数顺序不同
int add(int a, char b)
{
	return a + b;
}

//参数个数不同
int add(int a, char b,int c)
{
	return a + b + c;
}

void test3()
{
	//常引用
	const int a = 10;
	//int& ra = a; // 该语句编译时会出错，a为常量
	const int& ra = a;
	// int& b = 10; // 该语句编译时会出错，b为常量
	const int& b = 10;
	double d = 12.34;
	//int& rd = d; // 该语句编译时会出错，类型不同
	const int& rd = d;
}

struct A 
{
	int a[100000]; 
};

void TestFunc1(A a) {}
void TestFunc2(A& a) {}
 
void test4()
{
	A a;
	// 以值作为函数参数
	size_t begin1 = clock();
	for (size_t i = 0; i < 1000000; ++i)
		TestFunc1(a);
	size_t end1 = clock();
	// 以引用作为函数参数
	size_t begin2 = clock();
	for (size_t i = 0; i < 1000000; ++i)
		TestFunc2(a);
	size_t end2 = clock();
	// 分别计算两个函数运行结束后的时间
	cout << "TestFunc1(A)-time:" << end1 - begin1 << endl;		//TestFunc1(A) - time:25487
	cout << "TestFunc2(A&)-time:" << end2 - begin2 << endl;		//TestFunc2(A&) - time:18
}

A a;
// 值返回
A TestFunc1() { return a; }
// 引用返回
A& TestFunc2() { return a; }

void test5()
{
	// 以值作为函数的返回值类型
	size_t begin1 = clock();
	for (size_t i = 0; i < 1000000; ++i)
		TestFunc1();
	size_t end1 = clock();
	// 以引用作为函数的返回值类型
	size_t begin2 = clock();
	for (size_t i = 0; i < 1000000; ++i)
		TestFunc2();
	size_t end2 = clock();
	// 计算两个函数运算完成之后的时间
	cout << "TestFunc1 time:" << end1 - begin1 << endl;		//TestFunc1 time : 49019
	cout << "TestFunc2 time:" << end2 - begin2 << endl;		//TestFunc2 time : 21
}

void test6()
{
	//auto关键字与指针类型和引用类型结合起来使用
	int x = 10;
	auto a = &x;
	auto* b = &x;
	auto& c = x;
	//指针不区分auto和auto*是因为右边&取地址符
	cout << typeid(a).name() << endl;	//int*
	cout << typeid(b).name() << endl;	//int*
	cout << typeid(c).name() << endl;	//int	因为x是int类型的，别名的类型和实体的类型一样
	cout << typeid(x).name() << endl;	//int 实体
	*a = 20;
	*b = 30;
	c = 40;
}

void fun(int ptr) 
{
	cout << "fun(int)" << endl;
}

void fun(int* ptr) 
{
	cout << "fun(int*)" << endl;
}

//nullptr
void test7()
{
	bool result1 = nullptr == NULL;  // 结果为 1
	bool result2 = nullptr == 0;     // 结果为 1
	bool result3 = nullptr != NULL;  // 结果为 0
	bool result4 = nullptr != 0;     // 结果为 0
	fun(NULL);			//fun(int)	宏替换，预处理，NULL等价于0	在传统的C头文件(stddef.h)中
	fun(nullptr);		//fun(int*)	关键字
	fun((int*)NULL);	//fun(int*)
	fun(0);				//fun(int)
}

int main()
{
	//test1();		//命名空间
	//test2();		//constexpr关键字，c++11新赠的
	//test3();		//常引用
	//test4();		//参数：传值和传引用
	//test5();		//返回值：值返回和引用返回
	//test6();		//auto关键字
	//cout << typeid(nullptr).name() << endl;		//std::nullptr_t
	//foo(nullptr);
	//test7();

	return 0;
}