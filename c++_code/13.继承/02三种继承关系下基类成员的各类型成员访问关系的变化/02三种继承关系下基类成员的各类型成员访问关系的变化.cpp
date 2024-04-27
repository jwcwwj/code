#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
	void Print()
	{
		cout << _name << endl;
	}

protected:
	string _name;	//姓名

private:
	int _age;		//年龄
};

//public继承
class Student1 : public Person
{
protected:
	int _stunum; // 学号

	void fun(Student1 s)		
	{
		s._name;	//protected可以访问
		//s._age;	//private不可访问
	}
};
 
void test1()
{
	Student1 s1;
	s1.Print();		//public可以访问
}

//protected继承
class Student2 : protected Person
{
protected:
	int _stunum; // 学号

	void fun(Student2 s2)
	{ 
		s2._name;
		cout << _name << endl;		//protected可以访问
		//cout << _age << endl;		//private不可以访问
	}
};

void test2()
{
	Student1 s2;
	s2.Print();		//public可以访问
}

//private继承
class Student3 : private Person
{
protected:
	int _stunum; // 学号
	void fun()
	{
		Print();
		_name;
		//_age;		//private不可以访问
	}
};

void test3()
{
	Student3 s3;
	//s3.Print();		//不可访问
}

int main()
{
	cout << sizeof(string) << endl;		//28
	test1();
	test2();
	test3();
	return 0;
}