#include <iostream>
#include <string>

using namespace std;

// Student的_num和Person的_num构成隐藏关系，可以看出这样代码虽然能跑，但是非常容易混淆
class Person
{
protected:
	string _name = "小李子"; // 姓名
	int _num = 111; // 身份证号
};
class Student : public Person
{
public:
	void Print()
	{
		cout << "姓名:" << _name << endl;
		cout << "身份证号:" << Person::_num << endl;
		cout << "学号:" << _num << endl;
	}
protected:
	int _num = 999; // 学号
};

void test1()
{
	Student s1;
	s1.Print();
	//输出：
	//姓名:小李子
	//身份证号:111
	//学号:999
}


// B中的fun和A中的fun不是构成重载，因为不是在同一作用域
// B中的fun和A中的fun构成隐藏，成员函数满足函数名相同就构成隐藏。
class A
{
public:
	void fun()
	{
		cout << "func()" << endl;
	}
};
class B : public A
{
public:
	void fun(int i)
	{
		A::fun();
		cout << "func(int i)->" << i << endl;
	}
}; 

void test2()
{
	B b;
	b.fun(10);
	//输出：
	//func()
	//func(int i)->10
}

int main()
{
	test1();
	test2();
	return 0;
}