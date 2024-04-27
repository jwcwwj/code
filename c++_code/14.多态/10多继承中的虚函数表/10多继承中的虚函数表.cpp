#include <iostream>
#include <string>

using namespace std;

class Base1
{
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }

private:
	int b1;
};

class Base2
{
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }

private:
	int b2;
};

class Derive : public Base1, public Base2 {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }

private:
	int d1;
};

typedef void(*vfptr)();

void printVTable(vfptr vfTable[])
{
	cout << "虚表地址：" << vfTable << endl;
	vfptr* fptr = vfTable;
	while (*fptr != nullptr)
	{
		(*fptr)();
		++fptr;
	}
}

void test()
{
	Derive d;
	cout << "Derive：" << endl;
	vfptr* vTableb1 = (vfptr*)(*(int*)&d);
	printVTable(vTableb1);
	//输出：
	//Derive：
	//虚表地址：002A9B94
	//Derive::func1
	//Base1::func2
	//Derive::func3
	//派生类新添加的虚函数的虚函数指针放在第一个虚函数表继承的虚函数的虚函数指针的后面

	vfptr* vTableb2 = (vfptr*)(*(int*)((char*)&d + sizeof(Base1)));		//指针偏移
	printVTable(vTableb2);
	//虚表地址：002A9BA8
	//Derive::func1
	//Base2::func2
}

int main()
{	
	test();
	return 0;
}