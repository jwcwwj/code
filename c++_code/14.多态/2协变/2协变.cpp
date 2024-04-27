#include <iostream>
#include <string>

using namespace std;

class A{};

class B : public A{};

class Person
{
public:
	//协变：返回值类型可以不同，但是必须是有继承关系的指针或者引用。
	virtual A* BuyTicket() const
	{
		cout << "买票-全价" << endl;
		return new A;
	}
};

class Student : public Person
{
public:
	virtual B* BuyTicket() const
	{
		cout << "买票-半价" << endl;
		return new B;
	}
};

void fun(const Person& p)
{
	p.BuyTicket();
}

void test()
{
	Person p;
	Student s;
	fun(p);		//买票-全价
	fun(s);		//买票-半价
}

int main()
{
	test();
	return 0;
}