#include <iostream>
#include <string>

using namespace std;

// Student��_num��Person��_num�������ع�ϵ�����Կ�������������Ȼ���ܣ����Ƿǳ����׻���
class Person
{
protected:
	string _name = "С����"; // ����
	int _num = 111; // ���֤��
};
class Student : public Person
{
public:
	void Print()
	{
		cout << "����:" << _name << endl;
		cout << "���֤��:" << Person::_num << endl;
		cout << "ѧ��:" << _num << endl;
	}
protected:
	int _num = 999; // ѧ��
};

void test1()
{
	Student s1;
	s1.Print();
	//�����
	//����:С����
	//���֤��:111
	//ѧ��:999
}


// B�е�fun��A�е�fun���ǹ������أ���Ϊ������ͬһ������
// B�е�fun��A�е�fun�������أ���Ա�������㺯������ͬ�͹������ء�
class A
{
public:
	void fun()
	{
		cout << "func()" << endl;
	}
};
class B : public A
{
public:
	void fun(int i)
	{
		A::fun();
		cout << "func(int i)->" << i << endl;
	}
}; 

void test2()
{
	B b;
	b.fun(10);
	//�����
	//func()
	//func(int i)->10
}

int main()
{
	test1();
	test2();
	return 0;
}