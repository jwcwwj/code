#define _CRT_SECURE_NO_WARNINGS   //定义宏，禁止相关警告,用于禁止或屏蔽某些编译器警告信息。
#include <iostream>   
#include <assert.h>

using namespace std;

/* 
class A
{
public:
	A(int a = 10)
	{
		_a = a;
		cout <<  "A(int)" << endl;
	}

private:
	int _a;
};

class Date
{
public:
	//类中写了构造函数编译器就不会生成无参构造，一个类中只能有一个默认构造，一般给一个全缺省构造函数
	// 1.无参构造函数，回一个默认构造，默认构造还有全缺省构造，没有构造函数的时候编译器自动调用的构造函数也是默认构造。
	Date()
	{
		cout << "Date()" << endl;
	}

	// 2.带参构造函数
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
		cout <<  "Data(int, int, int)" << endl;
	}

private:
	int _year;
	int _month;
	int _day;
	A a;	//类中有自定义成员，会调用自定义成员的默认构造函数
};

//构造函数
void test1()
{
	//调用无参构造
	Date d1;
	
	//调用有参构造
	Date d2(2023, 6, 5);

	//不能显示调用构造函数
	//d1.Date(2023, 6, 5);		//error
	
	//输出：
	//A(int)		无参构造自定义
	//Date()
	//A(int)		有参构造自定义
	//Data(int, int, int)
}
*/

/*
typedef int DataType;
class SeqList
{
public:
	SeqList(int capacity = 10)
	{
		_pData = (DataType*)malloc(capacity * sizeof(DataType));
		assert(_pData);
		_size = 0;
		_capacity = capacity;
	}
	~SeqList()
	{
		cout << "~SeqList()" << endl;
		if (_pData)
		{
			free(_pData);	// 释放堆上的空间
			_pData = NULL;	// 将指针置为空
			_capacity = 0;
			_size = 0;
		}
	}
private:
	int* _pData;
	size_t _size;
	size_t _capacity;
};

class Date
{
public:
 	Date(int year = 2023, int month = 6, int day = 5)
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "Data(int, int, int)" << endl;
	}

private:
	int _year;
	int _month;
	int _day;
	SeqList a;	//类中有自定义成员，会调用自定义成员的默认析构函数
};

//析构函数
void test2()
{
	Date d1;
	//输出：
	//Data(int, int, int)
	//~SeqList()		//编译器的默认析构函数调用自定义成员的析构函数
}
*/

/*
//默认拷贝构造	浅拷贝
class Date
{
public:
	Date(int year = 2023, int month = 6, int day = 5)
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "Data(int, int, int)" << endl;
	}

	~Date()
	{
		cout << "~Date()" << endl;
	}

	//如果不显示定义拷贝构造，编译器会自动生成默认拷贝构造
	Date(const Date& d)
	{
		cout << "Date(const Date& d)" << endl;
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

private:
	int _year;
	int _month;
	int _day;
};

void test3()
{
	Date d;
	Date d1(d);			//拷贝构造传递引用
	//输出：
	//Data(int, int, int)
	//Date(const Date& d)
	//~Date()
	//~Date()
}
*/

/*
//如果显示定义了构造函数，需要手动实现无参构造函数，这里无参构造函数推荐使用全缺省构造函数。
class Date
{
public:
	~Date()
	{
		cout << "~Date()" << endl;
	}

	//如果不显示定义拷贝构造，编译器会自动生成默认拷贝构造
	Date(const Date& d)
	{
		cout << "Date(const Date& d)" << endl;
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

private:
	int _year;
	int _month;
	int _day;
};

void test4()
{
	Date d;				//error，类Date不存在默认构造函数
}*/

/* 
//判等运算符重载
class Date
{
	//friend bool operator==(const Date& d1, const Date& d2);
public:
	Date(int year = 2023, int month = 6, int day = 5)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	
	bool operator==(const Date& d)
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}

private:
	int _year;
	int _month;
	int _day;
};


//bool operator==(const Date& d1,const Date& d2)
//{
//	return d1._year == d2._year && d1._month == d2._month && d1._day == d2._day;
//}

void test5()
{
	Date d1(2023, 6, 6);
	Date d2(2023, 6, 6);
	//判断日期对象是否相等
	if (d1 == d2)
		cout << "日期相等" << endl;
	else
		cout << "日期不相等" << endl;
	//输出：
	//日期相等
}
*/

class A
{
public:
	A& operator=(A& a)
	{
		if(this != &a)
			_a = a._a;
		cout << "operator=(A&)" << endl;
		return *this;
	}

	int _a;
};

//赋值运算符重载
class Date
{
public:
	Date(int year = 2023, int month = 6, int day = 5)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	bool operator==(const Date& d)
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}

	/* 
	Date& operator=(Date& d)
	{
		//&d是取引用对象的地址
		if (this != &d)		//自己给自己赋值，直接跳过	根据地址判断
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		cout << "operator+(Date&)" << endl;
		return *this;
	}
	*/

private:
	int _year;
	int _month;
	int _day;
	A a;
};

void test6()
{
	Date d1(2023, 6, 5);
	Date d2(1, 1, 1);
	Date d3(1998, 11, 3);
	//赋值运算符：修改已经存在的对象的内容
	d3 = d1 = d2;		 //等价于d3.operator=(d1.operator=(d2));
	//d3.operator=(d1.operator=(d2));	在类中不显示定义赋值运算符，默认赋值运算符会自动调用自定义赋值运算符
	//输出
	//operator=(A&)
	//operator=(A&)
}

class B
{
public:
	int get1()		//this：const B		this的指向不能改变
	{
		_b = 10;
		//非const成员函数内可以调用其它的const成员函数吗
		get2();		//可以
		return _b;
	}

	int get2() const	//const this：const B* const	this的指向和this指向的值都不能改变
	{
		//_b = 10;		//不允许修改
		//const成员函数内可以调用其它的非const成员函数吗
		//get1();	//不能	原因：this指针的内容不能修改，不能调用非const成员函数
		return _b;
	}

private:
	int _b;
};

void test7()
{
	B b;
	const B b1;
	//const对象可以调用非const成员函数吗
	//b1.get1();  //不可以	原因：b1是const对象，表明b1的内容不能修改，非const成员函数是可以修改的，违背了含义
	//非const对象可以调用const成员函数吗
	b.get2();	//可以调用
	//原则是对象的权限不能放大，但是可以缩小
}

//取地址及const取地址操作符重载
class Date
{
public:
	Date* operator&()
	{
		return this;
	}
	const Date* operator&() const
	{
		return this;
	}
private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
};

void test8()
{
	Date obja;
	Date* pa = &obja;
	const Date objb;
	const Date* pa = &objb;
}

int main()
{
	//test1();		//构造函数
	//test2();		//析构函数
	//test3();		//拷贝构造函数浅拷贝
	//test4();		//如果显示定义了构造函数，需要手动实现无参构造函数，这里无参构造函数推荐使用全缺省构造函数。
	//test5();		//判等运算符重载
	//test6();		//赋值运算符重载
	test7();		//const修饰成员函数
	return 0;
}