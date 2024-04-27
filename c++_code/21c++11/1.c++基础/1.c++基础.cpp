#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <utility>

using namespace std;

struct A
{
public:
	explicit A(int a = 10)
		:_a(a)
	{}

	A(int a,int b,int c)
		:_a(a)
	{}

	int _a;
};

template <class T>
class Vector
{
public:
	Vector(size_t n)
		: _arr(new T[n])
		, _size(0)
		, _capacity(n)
	{}

	/*
	//不明白
	Vector(size_t n,size_t n2.size_t n3)
		: _arr(new T[n])
		, _size(0)
		, _capacity(n)
	{}
	*/

	Vector(const initializer_list<T>& lst)		//这个容器叫做初始化列表
		:_arr(new T(lst.size()))
		, _size(lst.size())
		, _capacity(_size)
	{
		int idx = 0;
		for (const auto& e : lst)
			_arr[idx++] = e;
	}

private:
	T* _arr;
	size_t _size;
	size_t _capacity;
};

//初始化列表
void test1()
{
	int a = 100;
	A a1(100);
	//A a2 = 100;		//单参构造的隐式类型转换(加上explicit就不能使用单参构造了)

	int arr[] = { 1,2,3,4 };

	//c++11中支持内置类型和自定义类型的列表初始化
	//内置类型列表初始化
	int b = { 10 };
	int c{ 100 };

	//自定义类型
	//A a3 = { 1 };		//单参构造的隐式类型转换
	A a4{ 5 };

	A a5 = { 1,2,3 };	//c++11支持多参构造的隐式类型转换
	A a6{ 4,5,6 };

	vector<int> v = { 1,2,3,4,5 };
	for (auto& e : v)
		cout << e << " ";
	cout << endl;

	list<int> l = { 1,2,3,4,5 };
	set<int> s = { 3,4,5,2,1,4,2 };		//本身会去重的
	map<int, int> m = { {1,2},{2,3} };		//先初始化pair对象，再用pair对象初始化map容器
	
	pair<int, int> p = { 1,3 };		//列表初始化初始pair类型的对象
	map<int, int> m1 = { p };

	//自定义的容器类，如果需要实现初始化列表进行初始化，需要定义一个构造函数，
	//参数为初始化列表（initializer_list）	只有begin、end、size接口
	Vector<int> v2 = { 1,2,3 };		//自己定义的类型中加initializer_list<T> 
	Vector<int> v3 = { 1 };
}

int fun(int a)
{
	return a;
}

//类型推导
void test2()
{
	auto a = 10;
	int b = 1;
	int c = 2;
	decltype(b + c) d;		//推导d
	cout << typeid(d).name() << endl;	//int
	cout << typeid(decltype(fun(a))).name() << endl;	//int	返回值的类型
	cout << typeid(decltype(fun)).name() << endl;		//int __cdecl(int)	函数指针的类型
}

class A1
{
public:
	A1(int a)
	{}

	A1() = default;		//让编译器显示生成一个无参的构造函数（默认的构造函数）

	A1(const A1&) = default;

	A1& operator=(const A1&) = default;
};

class B
{
public:
	B()
	{}

	B(const	B&) = delete;	//加上delete表示是已经删除的函数

	B& operator=(const B&) = delete;

	void func() = delete;		//delete只能在删除的时候使用
};

void fun1() = delete;

//默认成员函数控制
void test3()
{
	//1.default：加上default表示是默认的函数
	//没有太大的实际用处（除了 让编译器显示生成一个无参的构造函数）

	//2.delete：加上delete表示是已经删除的函数
	B b;
	//B copy(b);		//不能使用了（防止拷贝）
	//b.func();			//不能使用了
	//fun1();			//不能使用了

	//delete只能用于申明函数中，不能用于函数定义中
	//delete可以在成员函数和非成员函数中都可以使用
}

//上面出现的c++11新语法都是可有可无的
 
int main()
{
	//test1();
	//test2();
	test3();
	return 0;
}