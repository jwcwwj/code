#include <iostream>
#include <string>

using namespace std;

class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }

private:
	int a;
};

class Derive :public  Base {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
	virtual void func4() { cout << "Derive::func4" << endl; }

private:
	int b;
};

typedef void(*vfptr)();		//vfptr是函数指针

void printVTable(vfptr vfTable[])	//函数指针数组
{
	cout << "虚表地址：" << vfTable << endl;
	vfptr* fptr = vfTable;
	while (*fptr != nullptr)
	{
		(*fptr)();		//*fptr是虚函数指针
		++fptr;
	}
}

void test()
{
	Base b;
	Derive d;
	cout << "Base：" << endl;
	//思路：取出b、d对象的头4bytes，就是虚表的指针，前面我们说了虚函数表本质是一个存虚函数指针的指针数组，
	//这个数组最后面放了一个nullptr
	//1.先取b的地址，强转成一个int*的指针
	//2.再解引用取值，就取到了b对象头4bytes的值，这个值就是指向虚表的指针
	//3.再强转成vfptr*，因为虚表就是一个存vfptr类型(虚函数指针类型)的数组。
	//4.虚表指针传递给printVTable进行打印虚表
	//5.需要说明的是这个打印虚表的代码经常会崩溃，因为编译器有时对虚表的处理不干净，
	//虚表最后面没有放nullptr，导致越界，这是编译器的问题。
	//我们只需要点目录栏的 - 生成 - 清理解决方案，再编译就好了。
	vfptr* vftable = (vfptr*)(*(int*)&b);	
	//vftable就是前4个字节的值，是一个指向虚函数指针数组的指针（虚函数表指针），指向指针数组的首地址
	printVTable(vftable);
	//输出：
	//Base：
	//虚表地址：00CC9B34
	//Base::func1
	//Base::func2

	cout << "Derive：" << endl;
	vftable = (vfptr*)(*(int*)&d);
	printVTable(vftable);
	//Derive：
	//虚表地址：00CC9B64
	//Derive::func1
	//Base::func2
	//Derive::func3
	//Derive::func4
}

int main()
{
	test();
	return 0;
}