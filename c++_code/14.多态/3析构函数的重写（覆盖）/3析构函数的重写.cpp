#include <iostream>
#include <string>

using namespace std;

class A{};

class B : public A{};

//析构函数重写的原因是析构函数名称在底层是一样的
class Person
{
public:
	//协变：返回值类型可以不同，但是必须是有继承关系的指针或者引用。
	virtual A* BuyTicket() const
	{
		cout << "买票-全价" << endl;
		return new A;
	}

	virtual ~Person()
	{
		cout << "~Person" << endl;
	}
};

class Student : public Person
{
public:
	virtual B* BuyTicket() const
	{
		cout << "买票-半价" << endl;
		return new B;
	}
	
	//子类的析构重写父类的析构
	//如果有多态，都会把父类的析构函数会写成虚函数（会避免资源和内存泄漏的问题）
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

//析构函数不是虚函数的情况（解释为什么析构函数需要设置为虚函数）
void test1()
{
	//析构函数不是虚函数，看的是左边的类型。
	Person* p = new Student();
	delete p;		//动态开辟要手动释放
	//输出：
	//~Person		没有释放Student子类开辟的空间，会有问题

	Student* s = new Student;
	delete s;
	//输出：
	//~Student
	//~Person
}

//派生类构造的顺序：先构造父类，再构造子类。
//派生类析构的顺序：先析构子类，再析构父类。

//析构函数为虚函数的情况
void test2()
{
	Person* p = new Student();		//虚函数看的是后面动态申请的对象类型，不是虚函数看的是前面指针的类型
	delete p;		//动态开辟要手动释放
	//输出：
	//~Student
	//~Person		 

	Student* s = new Student;
	delete s;
	//输出：
	//~Student
	//~Person
}

int main()
{
	//test1();
	test2();
	return 0;
}