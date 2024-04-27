#include <iostream>

using namespace std;

/* 
class Time
{
public:
	Time(int hour,int minute,int second)
		:_hour(hour)
		,_minute(minute)
		,_second(second)
	{}

private:
	int _hour;
	int _minute;
	int _second;
};

class Date
{
public:
	Date(int year, int month, int day,Time t)
		//初始化列表，真正初始化的地方
		:_year(year)		//括号里面可以是值，也可以是表达式
		,_month(month)
		,_day(day)
		,_hour(12)
		//报错：类Time不存在默认构造函数
		//新添加的
		,_t(1,1,1)		//这样就可以了，一般不会出现这种情况，一般自定义成员的类使用全缺省构造函数
	{
		//不是初始化，只是赋初值
		//_year = year;
		//_month = month;
		//_day = day;
	}

private:
	int _year;
	int _month;
	int _day;
	const int _hour;
	Time _t;
};

void test1()
{
	Time t(2, 1, 1);
	Date d(2021, 3, 3,t);
}
*/

/*
class A
{
public:
	A(int a)
		:_a1(a)
		, _a2(_a1)
	{}
	
	void Print() {
		cout << _a1 << " " << _a2 << endl;
	}

private:
	//初始化顺序，和初始化列表无关
	int _a2;
	int _a1;
};

void test2()
{
	A aa(1);
	aa.Print();		//_a1 = 1	_a2 = -858993460
}
*/

/*
//explicit关键字
class Date
{
public:
	//这个代码加上explicit是错的，不加是对的，原因是explicit修饰构造函数会禁止单参构造隐式类型转换
	explicit Date(int year)
		:_year(year)
	{}

private:
	int _year;
	int _month;
	int _day;
};

void test3()
{
	Date d1(2018);		//构造函数	ok
	Date d2 = d1;		//拷贝构造	ok
	// 用一个整形变量给日期类型对象赋值
	// 实际编译器背后会用2019构造一个无名对象，最后用无名对象给d1对象进行赋值
	//d1 = 2019;			//error
	//为啥叫单参：d1 = 2019，2018;		//不存在这种写法
	//过程：叫做单参构造隐式类型转换
	//1.用2019调用构造函数创建匿名对象
	//2.调用赋值运算符，用匿名对象的内容赋值给d1
}
*/

/*
//实现一个类，计算程序中创建出了多少个类对象
class A
{
public:
	A()
	{
		++_scount;
	}

	A(const A& t)
	{
		++_scount;
	}

	static int GetACount()
	{
		return _scount;
	}

private:
	static int _scount;
};

int A::_scount = 0;

A funA(A a)
{
	return a;
}

void test4()
{
	cout << A::GetACount() << endl;	//0
	A a1, a2;	//2次构造函数
	A a3(a1);	//1次拷贝构造
	A a4 = funA(a1);	//2次拷贝构造：传值参数拷贝构造和返回值拷贝构造
	cout << A::GetACount() << endl;	//5	
	//静态成员访问方式：对象.static成员
	cout << a1._scount << endl;
	//类::staitc成员
	cout << A::_scount << endl;
}
*/

/* 
class B
{
public:
	B(int b = 0)
		:_b(b)
	{}
	
	int _b;
};
*/

/*
//c++11的成员初始化新玩法，可以在申明的时候给出缺省值
class A
{
public:
	void Print()
	{
		cout << a << endl;
		cout << b._b << endl;
		cout << p << endl;
	}
private:
	// 非静态成员变量，可以在成员声明时给缺省值。
	int a = 10;
	B b = 20;
	int* p = (int*)malloc(4);
	static int n;	//静态成员不可以，是在类外定义的
};

int A::n = 10;

void test5()
{
	A a;	//适合于编译器生成的默认构造
	a.Print();
}
*/

/* 
//c++11的成员初始化新玩法，可以在申明的时候给出缺省值
class A
{
public:
	A(int a = 1)	
		:_a(a)
	{}

private:
	int _a = 0;	//在构造函数中给出缺省值就按缺省值来，这里是备用值，没有别的值的时候使用
};

void test6()
{
	A a;	//a._a = 1
}
*/

/* 
//没使用友元函数时
class Date
{
public:
	Date(int year, int month, int day)
		:_year(year)
		,_month(month)
		,_day(day)
	{}

	ostream& operator<<(ostream& _cout)
	{
		_cout << _year << "-" << _month << "-" << _day << endl;
		return _cout;
	}

private:
	int _year;
	int _month;
	int _day;
};

void test7()
{
	Date d(2017, 12, 24);
	d << cout;
	d.operator << (cout);
	//和我们想的cout << d;不一样
}
*/

/*
//使用友元函数之后
class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
	friend istream& operator>>(istream& _cin, Date& d);

public:
	Date(int year, int month, int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{} 

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day << endl;
	return _cout;
}

istream& operator>>(istream& _cin, Date& d)
{
	_cin >> d._year;
	_cin >> d._month;
	_cin >> d._day;
	return _cin;
}

void test8()
{
	Date d(2023, 6, 9);
	Date d1(1998, 11, 3);
	cin >> d >> d1;			//等价于operator>>(operator>>(cin, d), d1);
	cout << d << d1 << endl;		//等价于operator<<(operator<<(cout, d), d1) << endl;
	//endl是本来就支持的，不需要友元函数重砸。
	//d.operator<<(cout, d);		//error，原因是友元函数不属于类的成员函数，是普通函数
	//友元只是为了让类外的函数可以访问类内的私有成员，突破封装的限制
	//控制台结果，前两行输入，后两行输出
	//1998 11 03
	//2023 6 9
	//1998 - 11 - 3
	//2023 - 6 - 9
	cout << endl;
	cout.operator<<(endl);	//在输出流中重载了<<操作符
}
*/

/* 
class Date; // 前置声明		//可以把类放在一个.h文件中，.cpp定义函数
class Time
{
	friend class Date; // 声明日期类为时间类的友元类，则在日期类中就直接访问Time类中的私有成员变量
public:
	Time(int hour = 10, int minute = 10, int second = 10)
		: _hour(hour)
		, _minute(minute)
		, _second(second)
	{}
private:
	int _hour;
	int _minute;
	int _second;
};

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	void SetTimeOfDate(int hour, int minute, int second)
	{
		// 直接访问时间类私有的成员变量
		_t._hour = hour;
		_t._minute = minute;
		_t._second = second;
	}

private:
	int _year;
	int _month;
	int _day;
	Time _t;
};
*/

/* 
//内部类
class A
{
private:
	static int k;
	int h;

public:		//类B要是在private里，在类A的外部是不可以实例化的，在类A中可以
	class B
	{
	public:
		void foo(const A& a)
		{
			cout << k << endl;//OK
			cout << a.h << endl;//OK
		}
	};

};
int A::k = 1;

void test9()
{
	A::B b;		//类B要是私有的，就不允许在类A的外部实例化，只能在类A中实例化 
	//自己类中不能实例化自己（在类B中实例化类B），报错：不允许使用不完整的类型
	b.foo(A());
}
*/

//外部类的大小不包含内部类的大小
class A
{
private:
	static int k;
	int h;

public:		
	class B
	{
	public:
		int a;
		int b;
		int c;
		void foo(const A& a)
		{
			cout << k << endl;//OK
			cout << a.h << endl;//OK
		}
	};
};
int A::k = 1;

void test10()
{
	cout << sizeof(A) << endl;	//4
	cout << sizeof(A::B) << endl;	//12
}

int main()
{
	//test1();		//初始化列表
	//test2();		//初始化列表变量声明顺序
	//test3();		//explicit关键字
	//test4();		//static	实现一个类，计算程序中创建出了多少个类对象
	//test5();		//c++11的成员初始化新玩法，可以在申明的时候给出缺省值
	//test6();		//c++11的成员初始化新玩法
	//test7();		//没使用友元函数时
	//test8();		//使用友元函数之后
	//test9();		//内部类
	test10();		//外部类的大小不包含内部类的大小
	return 0;
}