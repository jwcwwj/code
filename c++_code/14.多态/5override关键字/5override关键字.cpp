#include <iostream>
#include <string>

using namespace std;

//override�ؼ��ֵ��ô������������õĹؼ��֣�
//ǿ����������д�麯��
//��override���麯�������ǻ����Ѿ����ڵ��麯��
//ʹ��"override"�����ĳ�Ա���������ض�������Ա����

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
		cout << "��Ʊ-ȫ��" << endl;
	}

	virtual ~Person()
	{
		cout << "~Person" << endl;
	}
};

class Student : public Person
{
public:
	//virtual void BuyTicket(int a) const override{}		//error��������д�Ĳ�����ͬ

	virtual void BuyTicket() const	override
	{
		cout << "��Ʊ-ȫ��" << endl;
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