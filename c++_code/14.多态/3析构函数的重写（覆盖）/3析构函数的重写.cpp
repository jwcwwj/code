#include <iostream>
#include <string>

using namespace std;

class A{};

class B : public A{};

//����������д��ԭ�����������������ڵײ���һ����
class Person
{
public:
	//Э�䣺����ֵ���Ϳ��Բ�ͬ�����Ǳ������м̳й�ϵ��ָ��������á�
	virtual A* BuyTicket() const
	{
		cout << "��Ʊ-ȫ��" << endl;
		return new A;
	}

	virtual ~Person()
	{
		cout << "~Person" << endl;
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
	
	//�����������д���������
	//����ж�̬������Ѹ��������������д���麯�����������Դ���ڴ�й©�����⣩
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

//�������������麯�������������Ϊʲô����������Ҫ����Ϊ�麯����
void test1()
{
	//�������������麯������������ߵ����͡�
	Person* p = new Student();
	delete p;		//��̬����Ҫ�ֶ��ͷ�
	//�����
	//~Person		û���ͷ�Student���࿪�ٵĿռ䣬��������

	Student* s = new Student;
	delete s;
	//�����
	//~Student
	//~Person
}

//�����๹���˳���ȹ��츸�࣬�ٹ������ࡣ
//������������˳�����������࣬���������ࡣ

//��������Ϊ�麯�������
void test2()
{
	Person* p = new Student();		//�麯�������Ǻ��涯̬����Ķ������ͣ������麯��������ǰ��ָ�������
	delete p;		//��̬����Ҫ�ֶ��ͷ�
	//�����
	//~Student
	//~Person		 

	Student* s = new Student;
	delete s;
	//�����
	//~Student
	//~Person
}

int main()
{
	//test1();
	test2();
	return 0;
}