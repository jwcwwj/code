#include <iostream>

using namespace std;


template <class T>
void fun(const T& a)
{
	cout << "fun(const T&)";
}	

void test()
{
	fun(30);		//������ļ�����int���͵ĺ���ģ��ʵ����
}