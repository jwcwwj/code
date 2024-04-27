#include <iostream>
#include <string>

using namespace std;

class A{};

class B : public A{};

class Person
{
public:
	//Э�䣺����ֵ���Ϳ��Բ�ͬ�����Ǳ������м̳й�ϵ��ָ��������á�
	virtual A* BuyTicket() const
	{
		cout << "��Ʊ-ȫ��" << endl;
		return new A;
	}
};

class Student : public Person
{
public:
	virtual B* BuyTicket() const
	{
		cout << "��Ʊ-���" << endl;
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
	fun(p);		//��Ʊ-ȫ��
	fun(s);		//��Ʊ-���
}

int main()
{
	test();
	return 0;
}