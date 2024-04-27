#include <iostream>
#include <string>

using namespace std;

//override关键字的用处：（在子类用的关键字）
//强制派生类重写虚函数
//加override的虚函数必须是基类已经存在的虚函数
//使用"override"声明的成员函数不能重定义基类成员函数

class A 
{

};


class B : public A		 
{

}; 

class Person
{
public:
	virtual void BuyTicket() const  
	{
		cout << "买票-全价" << endl;
	}

	virtual ~Person()
	{
		cout << "~Person" << endl;
	}
};

class Student : public Person
{
public:
	//virtual void BuyTicket(int a) const override{}		//error，函数重写的参数不同

	virtual void BuyTicket() const	override
	{
		cout << "买票-全价" << endl;
	} 

	virtual ~Student()
	{
		delete[] ptr;
		cout << "~Student" << endl;
	}

protected:
	char* ptr = new char[100];
};

void fun(const Person& p)
{
	p.BuyTicket();
}

void test()
{

}

int main()
{
	test();
	return 0;
}