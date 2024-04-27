#include <iostream>

using namespace std;


template <class T>
void fun(const T& a)
{
	cout << "fun(const T&)";
}	

void test()
{
	fun(30);		//让这个文件产生int类型的函数模板实例化
}