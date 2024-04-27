#include <iostream>
#include <vector>

using namespace std;

//异常的基本使用
void fun1()
{
	int i;
	cin >> i;

	if(!i)
		//抛异常
		throw "string error";

	cout << "fun1()" << endl;
}

void fun2()
{
	int* arr = new int[100];
	//在c语言中异常只在debug版本下有效
	try
	{
		fun1();
	}
	catch (int err)
	{
		//异常抛出生命周期还存在，处理之后生命周期结束
	}
	catch (char* str)
	{
		cout << str << endl;
	}
	catch (double d)
	{

	}
	catch (...)
	{
		//捕获任意类型的异常，无法做针对性的处理
		delete[] arr;
		cout << "catch...,delete[]" << endl;
		throw;		//重新抛出
	}

	cout << "fun2()" << endl;

	delete[] arr;
	cout << "delete[]" << endl;
}

void fun3()
{
	fun2();
	cout << "fun3()" << endl;
}

void test1()
{
	try
	{
		fun3();
	}
	catch (int i)
	{

	}
	catch (char* str)
	{
		cout << str << endl;
	}
	catch (...)
	{
		cout << "..." << endl;
	}

	cout << "test()" << endl;
}

//异常继承体系
void test2()
{
	try
	{
		vector<int> v;
		v.at(3) = 10;
		v.reserve(1000000000);
	}
	catch (exception& e)	//一般这里是引用或者指针，产生多态的行为
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "..." << endl;
	}
}

int main()
{
	//test1();
	test2();
	return 0;
}