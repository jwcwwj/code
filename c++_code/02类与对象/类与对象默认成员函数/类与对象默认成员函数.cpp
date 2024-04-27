#define _CRT_SECURE_NO_WARNINGS   //����꣬��ֹ��ؾ���,���ڽ�ֹ������ĳЩ������������Ϣ��
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
	//����д�˹��캯���������Ͳ��������޲ι��죬һ������ֻ����һ��Ĭ�Ϲ��죬һ���һ��ȫȱʡ���캯��
	// 1.�޲ι��캯������һ��Ĭ�Ϲ��죬Ĭ�Ϲ��컹��ȫȱʡ���죬û�й��캯����ʱ��������Զ����õĹ��캯��Ҳ��Ĭ�Ϲ��졣
	Date()
	{
		cout << "Date()" << endl;
	}

	// 2.���ι��캯��
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
	A a;	//�������Զ����Ա��������Զ����Ա��Ĭ�Ϲ��캯��
};

//���캯��
void test1()
{
	//�����޲ι���
	Date d1;
	
	//�����вι���
	Date d2(2023, 6, 5);

	//������ʾ���ù��캯��
	//d1.Date(2023, 6, 5);		//error
	
	//�����
	//A(int)		�޲ι����Զ���
	//Date()
	//A(int)		�вι����Զ���
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
			free(_pData);	// �ͷŶ��ϵĿռ�
			_pData = NULL;	// ��ָ����Ϊ��
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
	SeqList a;	//�������Զ����Ա��������Զ����Ա��Ĭ����������
};

//��������
void test2()
{
	Date d1;
	//�����
	//Data(int, int, int)
	//~SeqList()		//��������Ĭ���������������Զ����Ա����������
}
*/

/*
//Ĭ�Ͽ�������	ǳ����
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

	//�������ʾ���忽�����죬���������Զ�����Ĭ�Ͽ�������
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
	Date d1(d);			//�������촫������
	//�����
	//Data(int, int, int)
	//Date(const Date& d)
	//~Date()
	//~Date()
}
*/

/*
//�����ʾ�����˹��캯������Ҫ�ֶ�ʵ���޲ι��캯���������޲ι��캯���Ƽ�ʹ��ȫȱʡ���캯����
class Date
{
public:
	~Date()
	{
		cout << "~Date()" << endl;
	}

	//�������ʾ���忽�����죬���������Զ�����Ĭ�Ͽ�������
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
	Date d;				//error����Date������Ĭ�Ϲ��캯��
}*/

/* 
//�е����������
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
	//�ж����ڶ����Ƿ����
	if (d1 == d2)
		cout << "�������" << endl;
	else
		cout << "���ڲ����" << endl;
	//�����
	//�������
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

//��ֵ���������
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
		//&d��ȡ���ö���ĵ�ַ
		if (this != &d)		//�Լ����Լ���ֵ��ֱ������	���ݵ�ַ�ж�
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
	//��ֵ��������޸��Ѿ����ڵĶ��������
	d3 = d1 = d2;		 //�ȼ���d3.operator=(d1.operator=(d2));
	//d3.operator=(d1.operator=(d2));	�����в���ʾ���帳ֵ�������Ĭ�ϸ�ֵ��������Զ������Զ��帳ֵ�����
	//���
	//operator=(A&)
	//operator=(A&)
}

class B
{
public:
	int get1()		//this��const B		this��ָ���ܸı�
	{
		_b = 10;
		//��const��Ա�����ڿ��Ե���������const��Ա������
		get2();		//����
		return _b;
	}

	int get2() const	//const this��const B* const	this��ָ���thisָ���ֵ�����ܸı�
	{
		//_b = 10;		//�������޸�
		//const��Ա�����ڿ��Ե��������ķ�const��Ա������
		//get1();	//����	ԭ��thisָ������ݲ����޸ģ����ܵ��÷�const��Ա����
		return _b;
	}

private:
	int _b;
};

void test7()
{
	B b;
	const B b1;
	//const������Ե��÷�const��Ա������
	//b1.get1();  //������	ԭ��b1��const���󣬱���b1�����ݲ����޸ģ���const��Ա�����ǿ����޸ĵģ�Υ���˺���
	//��const������Ե���const��Ա������
	b.get2();	//���Ե���
	//ԭ���Ƕ����Ȩ�޲��ܷŴ󣬵��ǿ�����С
}

//ȡ��ַ��constȡ��ַ����������
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
	int _year; // ��
	int _month; // ��
	int _day; // ��
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
	//test1();		//���캯��
	//test2();		//��������
	//test3();		//�������캯��ǳ����
	//test4();		//�����ʾ�����˹��캯������Ҫ�ֶ�ʵ���޲ι��캯���������޲ι��캯���Ƽ�ʹ��ȫȱʡ���캯����
	//test5();		//�е����������
	//test6();		//��ֵ���������
	test7();		//const���γ�Ա����
	return 0;
}