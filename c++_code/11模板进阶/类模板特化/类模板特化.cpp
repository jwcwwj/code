#include <iostream>

using namespace std;

//类模板特化：
//应用场景：类型萃取
//前提：已有一个通用的模板

template <class T1,class T2>
struct D
{
public:
	D(const T1& d1, const T2& d2)
		:_d1(d1)
		,_d2(d2)
	{
		cout << "D(T1, T2)" << endl;
	}

	T1 _d1;
	T2 _d2;
};

//特化类模板
//1.全特化：所有的类型都是具体类型，没有类型的限制
template<>
struct D<char, double>
{
	D(const char& d1, const double& d2)
		:_d1(d1)
		, _d2(d2)
	{
		cout << "D(char, double)" << endl;
	}

	char _d1;
	double _d2;
};

//全特化
void test1()
{
	D<int, int> d1(1,1);			//通用模板的实例化
	//输出：D(T1, T2)
	D<char, double> d2('a', 1.1);	//全特化版本的实例化
	//输出：D(char, double)
}

//2.1偏特化：只特化部分类型
template <class T1>
struct D<T1, char>
{
	D(const T1& d1, const char& d2)
		:_d1(d1)
		, _d2(d2)
	{
		cout << "D(T1, char)" << endl;
	}

	T1 _d1;
	char _d2;
};

//偏特化
void test2()
{
	D<int, char> d3(1, 'a');	//偏特化版本的实例化
	//输出：D(T1, char)
}

//2.2偏特化给模板参数做进一步的限制
template <class T1, class T2>
struct D<T1*,T2*>
{
public:
	D(const T1& d1, const T2& d2)
		:_d1(d1)
		, _d2(d2)
	{
		cout << "D(T1*, T2*)" << endl;
	}

	T1 _d1;
	T2 _d2;
};

//2.2偏特化给模板参数做进一步的限制
void test3()
{
	D<int*, int*> d4(1, 2);
	//输出：D(T1*, T2*)
}

int main()
{
	//test1();		//全特化
	//test2();		//偏特化
	test3();		//偏特化给模板参数做进一步的限制
	return 0;
}