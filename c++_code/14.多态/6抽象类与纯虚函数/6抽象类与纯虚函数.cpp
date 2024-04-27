#include <iostream>
#include <string>

using namespace std;

//抽象类：一个类中定义了纯虚函数，这个类就叫做抽象类。（抽象类是不具有实例化的类）
class A
{
public:
	virtual void fun() = 0;		//纯虚函数
};

//继承了抽象类的类，需要把抽象类中的所有纯虚函数都实现，这个类才能被实例化。
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

//继承了抽象类的类，没有全部实现继承的抽象类中的纯虚函数，那么这个类也叫做抽象类。
class D : public A
{
	
};

void test()
{
	A* b = new B;
	A* c = new C;
	b->fun();
	c->fun();
	//输出：
	//B::fun()
	//C::fun()
}

int main()
{
	test();
	return 0;
}