#include <iostream>
#include <string>

using namespace std;

//final�ؼ��ֵ��ô������ڸ����õĹؼ��֣�
//1.�����࣬��ʾ���಻�ܱ��̳У���һ��������չ���࣬������
//2.�����麯������һ���麯���������final�ؼ��֣���ʾ���麯�������պ��������ܱ���д������麯���������п����ã������಻����д��

class A final			//�����࣬��ʾ���಻�ܱ��̳У���һ��������չ���࣬������
{

};

/* 
class B : public A		//error���������ܽ�"final"��������������
{

};
*/

class Person
{
public:
	//�����麯������һ���麯���������final�ؼ��֣���ʾ���麯�������պ��������ܱ���д
	//����麯���������п����ã������಻����д
	//final���εĺ�������ʾ��һ�����պ��������ܸı�ĺ���
	virtual void BuyTicket() const final		//const��������ں������棬���ܷ���final����
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
	/* 
	virtual void BuyTicket() const		//error�������޷���д"final"����
	{
		cout << "��Ʊ-���" << endl;
	}
	*/

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