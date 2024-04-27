#include <iostream>
#include <string>

using namespace std;

//�����ࣺһ�����ж����˴��麯���������ͽ��������ࡣ���������ǲ�����ʵ�������ࣩ
class A
{
public:
	virtual void fun() = 0;		//���麯��
};

//�̳��˳�������࣬��Ҫ�ѳ������е����д��麯����ʵ�֣��������ܱ�ʵ������
class B : public A
{
public:
	virtual void fun()
	{
		cout << "B::fun()" << endl;
	}
};

class C : public A
{
public:
	virtual void fun()
	{
		cout << "C::fun()" << endl;
	}
};

//�̳��˳�������࣬û��ȫ��ʵ�ּ̳еĳ������еĴ��麯������ô�����Ҳ���������ࡣ
class D : public A
{
	
};

void test()
{
	A* b = new B;
	A* c = new C;
	b->fun();
	c->fun();
	//�����
	//B::fun()
	//C::fun()
}

int main()
{
	test();
	return 0;
}