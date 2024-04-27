#include <iostream>

using namespace std;

//只能在堆上创建对象
class HeapObj
{
public:
	//调用构造函数创建对象
	static HeapObj* getObj()
	{
		//拷贝的对象是在栈上
		//HeapObj* p = new HeapObj();
		//return p;
		return new HeapObj;
	}

	//静止构造函数的调用：私有（只能在类内部调用，不能在类外部调用）
private:
	HeapObj()
	{}

	//防拷贝	拷贝之后的局部对象在栈上
	//解决办法：
	//1.只声明，不实现；（但可以在类里面使用拷贝构造）	c++98
	//HeapObj(const HeapObj&);
	//2.把拷贝构造写为delete函数（有函数体也不能使用）	c++11
	HeapObj(const HeapObj&) = delete;

	//赋值运算符：不创建新的对象，只是修改已经存在的对象的内容
};

void test()
{
	HeapObj* ptr = HeapObj::getObj();
	HeapObj::getObj();
	//HeapObj copy(*ptr);		//拷贝是栈的上的对象，静止拷贝构造
}

int main()
{
	test();
	return 0;
}