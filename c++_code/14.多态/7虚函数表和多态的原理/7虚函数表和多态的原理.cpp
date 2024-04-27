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
	static int si = 0;	//数据段
	int i = 1;	//栈
	int* p = new int;	//堆
	void(*ptr)();		//函数指针
	ptr = f;			//代码段
	cout << "栈：" << &i << endl;		//栈：008FFB00
	cout << "堆：" << p << endl;		//堆：00CA5120
	cout << "数据段：" << &si << endl;	//数据段：009BC2F8
	cout << "代码段：" << ptr << endl;	//代码段：009B129E	 

	typedef void(*vfptr)();
	//获取对象的前4个字节，就是虚表指针
	vfptr* vptr = (vfptr*)(*(int*)&b);
	cout << "虚表指针：" << vptr << endl;	//虚表指针：009B9B4C
}

int main()
{
	test();
	return 0;
}