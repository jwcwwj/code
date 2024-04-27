#include <iostream>
#include <string>

using namespace std;

//查看使用了虚拟继承和没有使用虚拟继承的内存图

//不使用虚拟继承
class A1
{
public:
	int _a;
};

class B1 : public A1
{
public:
	int _b;
};

class C1 : public A1
{
public:
	int _c;
};

class D1 : public B1, public C1
{
public:
	int _d;
};

//没有使用虚拟继承
void test1()
{
	D1 d;
	d.B1::_a = 1;
	d._b = 3;
	d.C1::_a = 2;
	d._c = 4;
	d._d = 5;
}

//使用了虚拟继承
class A2
{
public:
	int _a;
};

class B2 : virtual public A2
{
public:
	int _b;
};

class C2 : virtual public A2
{
public:
	int _c;
};

class D2 : public B2, public C2
{
public:
	int _d;
};

//使用了虚拟继承
void test2()
{
	D2 d;
	d.B2::_a = 1;
	d._b = 3;
	d.C2::_a = 2;
	d._c = 4;
	d._d = 5;
}

int main()
{
	test1();
	test2();
	return 0;
}