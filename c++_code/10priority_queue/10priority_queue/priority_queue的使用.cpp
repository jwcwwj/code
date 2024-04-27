#include <iostream>
#include <queue>
#include <functional>	//greater算法的头文件

using namespace std;

//priority_queue的第三个参数
//greater按 > 进行比较，建小堆
//less按 < 进行比较，建大堆

//仿函数类模板
template <class T>
struct Greater
{
	//在类中重载函数运算符
	bool operator()(const T& val1, const T& val2)
	{
		return val1 > val2;		//没有{}会报错，不知道为啥
	}
};

//大堆	内置类型
void test1()
{
	priority_queue<int> q;	//可以存放自定义类型，自定义类型必须支持大小关系的比较（比较规则）
	q.push(100);
	q.push(1);
	q.push(150);
	q.push(10);
	q.push(20);

	while (!q.empty())
	{
		cout << q.top() << " ";		//堆顶，整个优先队列的最值（默认是最大值）
		//输出：150 100 20 10 1
		q.pop();
	}

	cout << endl;
}

struct A
{
	A(int a)
		:_a(a)
	{}

	//建大堆
	bool operator<(const A& a) const		//匿名对象具有常性
	{
		return _a < a._a;
	}

	//建小堆
	bool operator>(const A& a) const
	{
		return _a > a._a;
	}

	//友元函数可以直接在类的内部声明处实现，不需要在同一作用域类的外部实现
	friend ostream& operator<<(ostream& _cout, const A& a)
	{
		_cout << a._a;
		return _cout;
	}

private:
	int _a;	
	//自定义成员的变量，可以重载 <<（输出运算符），提高类的封装性和安全性，把成员变量变为私有的。（使用友元在类外定义）
};

void test2()
{
	priority_queue<A> q;
	q.push(A(1));			//匿名对象具有常性
	q.push(A(2));
	q.push(A(3));
	q.push(A(4));

	while (!q.empty())
	{
		cout << q.top() << " ";	//4 3 2 1
		q.pop();
	}

	cout << endl;
}

void test3()
{
	priority_queue<int, vector<int>, Greater<int>> q;	//使用自己的类模板仿函数
	//priority_queue<int,vector<int>,greater<int>> q;		//按小堆进行创建
	//greater提供一个大于比较，建小堆，默认是按照小于来比较，建大堆 
	q.push(1);			//匿名对象具有常性
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		cout << q.top() << " ";	//1 2 3 4
		q.pop();
	}

	cout << endl;
}

//自定义类型	小堆
void test4()
{
	//如果在priority_queue中放自定义类型的数据，
	//用户需要在自定义类型中提供> 或者< 的重载.
	priority_queue<A, vector<A>, Greater<A>> q;
	q.push(A(1));			//匿名对象具有常性
	q.push(A(2));
	q.push(A(3));
	q.push(A(4));

	while (!q.empty())
	{
		cout << q.top() << " ";	//1 2 3 4
		q.pop();
	}

	cout << endl;
}

int main()
{
	//test1();	//大堆	内置类型
	//test2();	//大堆	自定义类型
	//test3();	//小堆	内置类型
	test4();	//小堆	自定义类型

	//使用类模板仿函数
	//Greater<int> g;
	//bool ret = g.operator()(10, 20);
	//ret = g(10, 20);	//简写形式		仿函数不是函数，是重载括号运算符

	return 0;
}