#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

struct A
{
public:
	A(int age = 1,int id = 1,string name = " ")
		:_age(age)
		,_id(id)
		,_name(name)
	{}

	bool operator<(const A&	a)
	{
		//operator重写操作符必须加{}
		return _age < a._age;
	}

	int _age;
	int _id;
	string _name;
};

class Less
{
public:
	bool operator()(const A& a, const A& b)
	{
		return a._id > b._id;
	}
};

void test1()
{
	int array[] = { 4,1,8,5,3,7,0,9,2,6 };
	// 默认按照小于比较，排出来结果是升序
	std::sort(array, array + sizeof(array) / sizeof(array[0]));
	// 如果需要降序，需要改变元素的比较规则
	std::sort(array, array + sizeof(array) / sizeof(array[0]), greater<int>()); //匿名对象
	greater<int> a;
	std::sort(array, array + sizeof(array) / sizeof(array[0]), a);

	vector<A> vec = { {18,1,"a"},{29,3,"b"},{13,25,"c"} };
	sort(vec.begin(), vec.end());
	sort(vec.begin(), vec.end(), Less());		//匿名对象
	//排序的比较方式：仿函数，重载 > 或者 <运算符，函数指针，lambda表达式
	sort(vec.begin(),vec.end(),
		[](const A& a, const A& b)
	{
		return a._name < b._name;
	});
}

void test2()
{
	//lambda表达式：{捕捉列表}(参数列表)(mutable可选)->返回值类型{函数体}
	//捕捉列表：捕获父作用域中的变量
	int a = 10;
	int b = 20;
	[a, b] {return a + b; };
	//参数列表：类似于函数的参数列表
	[a, b](int c, int d, int e) {return a + b + c; };
	//返回值：类似于函数的返回值
	[a, b](int c)->int {return a + b + c; };
	//函数体：类似于函数的函数体，可以有多聚指令
	//mutable：修改捕捉列表中变量的属性为非const，默认为const属性
	//[a, b](int c)->int {a = 10; };	//a,b的属性默认为const属性（表达式必须是可修改的左值）
	[a, b](int c)mutable->int {a = 10; b = 20;  return a; };
	//参数列表和返回值可以忽略
	[] {};
	//返回值类型一般不用写，编译器会自动推导
	[a, b] {return a + b; };
	//如果有mutable，即使参数列表为空，参数列表也需要显示写出来
	[a, b]()mutable {return a + b; };
	//[a, b]->int {return a + b; };		//error，此处不允许使用特性
	[a, b]()->int {return a + b; };

	//上面写的全部是lambda表达式的定义，并没有使用，指令不会运行
	//下面写的是lambda表达式的使用
	auto f = [a, b](int c) {return a + b + c; };
	cout << typeid(f).name() << endl;//class <lambda_b2e39ab5e00dc83db94af3e20fe2d53e>
	//cout << f << endl;
	int e = f(10);
	
	/*
	typedef int(*ptr1)(int);
	ptr1 fff;
	cout << fff(10) << endl;
	//这里如何用函数指针代替auto呢？
	*/

	cout << e << endl;	//40
	//[=]：以值的形式捕捉父作用域中的所有变量
	auto f2 = [=]() {return a + b + e; };
	//[&]：以引用的形式捕捉父作用域中的所有变量
	auto f3 = [&]() {a = 1; b = 1000; };
	f3();	//修改a和b的值
	
	//[=,&变量x]：x引用形式捕捉，其他的以值的形式捕捉
	//[&,变量x]：x值形式捕捉，其他的以引用的形式捕捉
	//错误的捕捉方式：[=,变量x]，[&,&变量x]
	//[this]：捕捉成员函数中的this指针

	int g = 10;
	auto m = [g] {};

	//lambda表达式不能进行赋值，可以进行拷贝
	auto f1 = [](int a) {return a; };
	auto f22 = [](int a) {return a; };
	
	//不能直接进行赋值
	//f = f22;		//error
	
	//可以进行拷贝
	typedef int(*ptr)(int);
	auto f33 = f1;

	//ptr f4 = f3;	//error，不存在从"lambda [void 0->void"到"ptr”的适当转换函数
	//可以赋值给函数指针
	ptr f4 = f1;

}

//int g1 = 10;
//auto m1 = [g1] {};	//error，无法在 lambda 中捕获带有静态存储持续时间的变量（全局变量）

struct A1
{
	void fun(int a)
	{
		auto f = [this]() {return this->_a; };
	}

	int _a;
};


//lambda表达式底层是如何走的：底层通过仿函数类实现的
struct Sum
{
	int operator()(int a, int b)
	{
		return a + b;
	}
};

void test3()
{
	auto f = [](int a, int b) {return a + b; };
	int sum = f(10, 20);
	Sum s;
	s(10, 20);
}

int main()
{
	test1();
	test2();
	test3();
	return 0;
}