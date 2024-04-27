#include <iostream>

using namespace std;

//只能在栈上创建对象(禁止在堆上创建对象)
//方法1：
class StackObj
{
public:
	//共有的方法调用构造函数创建对象
	static StackObj getObj()	//static只能调用static函数
	{
		return StackObj();
	}

private:
	//构造函数私有，类外部无法调用，只能在类内部调用
	StackObj()
	{}

	//拷贝是在栈上创建对象
};

StackObj so = StackObj::getObj();	//在全局创建对象，是在数据段

void test1()
{
	StackObj so = StackObj::getObj();
	//new StackObj();		//堆上无法创建对象
}

//方法2：
class StackObj1
{
public:
	//静止调用operator new
	void* operator new(size_t n) = delete;
};

void test2()
{
	//StackObj1* so = new StackObj1;	//它是已删除的函数
	StackObj1 so1;
}

int main()
{
	test1();
	test2();
	return 0;
}