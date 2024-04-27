#include <iostream>
#include <array>			//静态数组类

using namespace std;

//template <class T,double num>		//报错：浮点模板参数是非标准的
//struct A
//{};

struct B
{};

//template <class T,B obj>		 //报错：非类型模板参数不能作为类类型
//struct C
//{};

template <class T,char ch>
struct D
{};

void test()
{
	//array<T,size_t>		size_t是非类型模板参数
	array<int, 10> arr;			//静态数组，等价于int arr[10]
	//非类型模板参数只能是整数类型，不能给浮点数或者自定义类型数据
	B b;
	//C<int,b> c;		//报错：表达式必须含有常量值
	D<float, 'a'> d;
}

int main()
{
	test();
	return 0;
}