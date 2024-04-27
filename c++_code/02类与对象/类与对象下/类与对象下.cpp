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
		//��ʼ���б�������ʼ���ĵط�
		:_year(year)		//�������������ֵ��Ҳ�����Ǳ��ʽ
		,_month(month)
		,_day(day)
		,_hour(12)
		//������Time������Ĭ�Ϲ��캯��
		//����ӵ�
		,_t(1,1,1)		//�����Ϳ����ˣ�һ�㲻��������������һ���Զ����Ա����ʹ��ȫȱʡ���캯��
	{
		//���ǳ�ʼ����ֻ�Ǹ���ֵ
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
	//��ʼ��˳�򣬺ͳ�ʼ���б��޹�
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
//explicit�ؼ���
class Date
{
public:
	//����������explicit�Ǵ�ģ������ǶԵģ�ԭ����explicit���ι��캯�����ֹ���ι�����ʽ����ת��
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
	Date d1(2018);		//���캯��	ok
	Date d2 = d1;		//��������	ok
	// ��һ�����α������������Ͷ���ֵ
	// ʵ�ʱ������������2019����һ������������������������d1������и�ֵ
	//d1 = 2019;			//error
	//Ϊɶ�е��Σ�d1 = 2019��2018;		//����������д��
	//���̣��������ι�����ʽ����ת��
	//1.��2019���ù��캯��������������
	//2.���ø�ֵ���������������������ݸ�ֵ��d1
}
*/

/*
//ʵ��һ���࣬��������д������˶��ٸ������
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
	A a1, a2;	//2�ι��캯��
	A a3(a1);	//1�ο�������
	A a4 = funA(a1);	//2�ο������죺��ֵ������������ͷ���ֵ��������
	cout << A::GetACount() << endl;	//5	
	//��̬��Ա���ʷ�ʽ������.static��Ա
	cout << a1._scount << endl;
	//��::staitc��Ա
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
//c++11�ĳ�Ա��ʼ�����淨��������������ʱ�����ȱʡֵ
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
	// �Ǿ�̬��Ա�����������ڳ�Ա����ʱ��ȱʡֵ��
	int a = 10;
	B b = 20;
	int* p = (int*)malloc(4);
	static int n;	//��̬��Ա�����ԣ��������ⶨ���
};

int A::n = 10;

void test5()
{
	A a;	//�ʺ��ڱ��������ɵ�Ĭ�Ϲ���
	a.Print();
}
*/

/* 
//c++11�ĳ�Ա��ʼ�����淨��������������ʱ�����ȱʡֵ
class A
{
public:
	A(int a = 1)	
		:_a(a)
	{}

private:
	int _a = 0;	//�ڹ��캯���и���ȱʡֵ�Ͱ�ȱʡֵ���������Ǳ���ֵ��û�б��ֵ��ʱ��ʹ��
};

void test6()
{
	A a;	//a._a = 1
}
*/

/* 
//ûʹ����Ԫ����ʱ
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
	//���������cout << d;��һ��
}
*/

/*
//ʹ����Ԫ����֮��
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
	cin >> d >> d1;			//�ȼ���operator>>(operator>>(cin, d), d1);
	cout << d << d1 << endl;		//�ȼ���operator<<(operator<<(cout, d), d1) << endl;
	//endl�Ǳ�����֧�ֵģ�����Ҫ��Ԫ�������ҡ�
	//d.operator<<(cout, d);		//error��ԭ������Ԫ������������ĳ�Ա����������ͨ����
	//��Ԫֻ��Ϊ��������ĺ������Է������ڵ�˽�г�Ա��ͻ�Ʒ�װ������
	//����̨�����ǰ�������룬���������
	//1998 11 03
	//2023 6 9
	//1998 - 11 - 3
	//2023 - 6 - 9
	cout << endl;
	cout.operator<<(endl);	//���������������<<������
}
*/

/* 
class Date; // ǰ������		//���԰������һ��.h�ļ��У�.cpp���庯��
class Time
{
	friend class Date; // ����������Ϊʱ�������Ԫ�࣬�����������о�ֱ�ӷ���Time���е�˽�г�Ա����
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
		// ֱ�ӷ���ʱ����˽�еĳ�Ա����
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
//�ڲ���
class A
{
private:
	static int k;
	int h;

public:		//��BҪ����private�����A���ⲿ�ǲ�����ʵ�����ģ�����A�п���
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
	A::B b;		//��BҪ��˽�еģ��Ͳ���������A���ⲿʵ������ֻ������A��ʵ���� 
	//�Լ����в���ʵ�����Լ�������B��ʵ������B��������������ʹ�ò�����������
	b.foo(A());
}
*/

//�ⲿ��Ĵ�С�������ڲ���Ĵ�С
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
	//test1();		//��ʼ���б�
	//test2();		//��ʼ���б��������˳��
	//test3();		//explicit�ؼ���
	//test4();		//static	ʵ��һ���࣬��������д������˶��ٸ������
	//test5();		//c++11�ĳ�Ա��ʼ�����淨��������������ʱ�����ȱʡֵ
	//test6();		//c++11�ĳ�Ա��ʼ�����淨
	//test7();		//ûʹ����Ԫ����ʱ
	//test8();		//ʹ����Ԫ����֮��
	//test9();		//�ڲ���
	test10();		//�ⲿ��Ĵ�С�������ڲ���Ĵ�С
	return 0;
}