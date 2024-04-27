#include <iostream>
#include <string>

using namespace std;

//final关键字的用处：（在父类用的关键字）
//1.修饰类，表示该类不能被继承，是一个不能扩展的类，最终类
//2.修饰虚函数：给一个虚函数后面加上final关键字，表示该虚函数是最终函数，不能被重写（这个虚函数在子类中可以用，但子类不能重写）

class A final			//修饰类，表示该类不能被继承，是一个不能扩展的类，最终类
{

};

/* 
class B : public A		//error，报错：不能将"final"类类型用作基类
{

};
*/

class Person
{
public:
	//修饰虚函数：给一个虚函数后面加上final关键字，表示该虚函数是最终函数，不能被重写
	//这个虚函数在子类中可以用，但子类不能重写
	//final修饰的函数，表示是一个最终函数，不能改变的函数
	virtual void BuyTicket() const final		//const必须紧跟在函数后面，不能放在final后面
	{
		cout << "买票-全价" << endl;
	}

	virtual ~Person()
	{
		cout << "~Person" << endl;
	}
};

class Student : public Person
{
public:
	/* 
	virtual void BuyTicket() const		//error，报错：无法重写"final"函数
	{
		cout << "买票-半价" << endl;
	}
	*/

	virtual ~Student()
	{
		delete[] ptr;
		cout << "~Student" << endl;
	}

protected:
	char* ptr = new char[100];
};

void fun(const Person& p)
{
	p.BuyTicket();
}

void test()
{

}

int main()
{
	test();
	return 0;
}