#include <iostream>
#include <string>

using namespace std;

class A
{
public:
	virtual void fun()
	{
		cout << "A::fun()" << endl;
	}

	void fun2()
	{
		cout << "A::fun2()" << endl;
	}

private:
	int _a = 1;
};

class B : public A
{
public:
	virtual void fun()
	{
		cout << "B::fun()" << endl;
	}
};
 
void f()
{

}

void test()
{
	B b;
	A a;
	cout << sizeof(A) << endl;	//8
	cout << sizeof(B) << endl;	//8
	static int si = 0;	//���ݶ�
	int i = 1;	//ջ
	int* p = new int;	//��
	void(*ptr)();		//����ָ��
	ptr = f;			//�����
	cout << "ջ��" << &i << endl;		//ջ��008FFB00
	cout << "�ѣ�" << p << endl;		//�ѣ�00CA5120
	cout << "���ݶΣ�" << &si << endl;	//���ݶΣ�009BC2F8
	cout << "����Σ�" << ptr << endl;	//����Σ�009B129E	 

	typedef void(*vfptr)();
	//��ȡ�����ǰ4���ֽڣ��������ָ��
	vfptr* vptr = (vfptr*)(*(int*)&b);
	cout << "���ָ�룺" << vptr << endl;	//���ָ�룺009B9B4C
}

int main()
{
	test();
	return 0;
}