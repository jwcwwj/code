#include <iostream>
#include <vector>

using namespace std;

//�쳣�Ļ���ʹ��
void fun1()
{
	int i;
	cin >> i;

	if(!i)
		//���쳣
		throw "string error";

	cout << "fun1()" << endl;
}

void fun2()
{
	int* arr = new int[100];
	//��c�������쳣ֻ��debug�汾����Ч
	try
	{
		fun1();
	}
	catch (int err)
	{
		//�쳣�׳��������ڻ����ڣ�����֮���������ڽ���
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
		//�����������͵��쳣���޷�������ԵĴ���
		delete[] arr;
		cout << "catch...,delete[]" << endl;
		throw;		//�����׳�
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

//�쳣�̳���ϵ
void test2()
{
	try
	{
		vector<int> v;
		v.at(3) = 10;
		v.reserve(1000000000);
	}
	catch (exception& e)	//һ�����������û���ָ�룬������̬����Ϊ
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