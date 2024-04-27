#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
	Person(const char* name = "peter")
		: _name(name)
	{
		cout << "Person()" << endl;
	}

	Person(const Person& p)
		: _name(p._name)
	{
		cout << "Person(const Person& p)" << endl;
	}

	Person& operator=(const Person& p)
	{
		cout << "Person operator=(const Person& p)" << endl;
		if (this != &p)
			_name = p._name;
		return *this;
	}

	~Person()
	{
		cout << "~Person()" << endl;
	}

protected:
	string _name; //姓名
};

class Student : public Person
{
public:
	//子类默认的构造函数，自动调用父类的构造函数
	Student(const char* name, int num)
		: Person(name)
		, _num(num)
	{
		cout << "Student()" << endl;
	}

	//子类默认的拷贝构造，自动调用父类的拷贝构造
	//显示定义的拷贝构造，默认调用父类的默认构造（指定之后调用父类拷贝构造）
	Student(const Student& s)
		: Person(s)		//切片，指定之后调用父类拷贝构造
		, _num(s._num)
	{
		cout << "Student(const Student& s)" << endl;
	}

	//显示定义的赋值运算符，不会自动调用父类的赋值运算符
	//子类默认的赋值运算符，自动调用父类的赋值运算符
	Student& operator = (const Student& s)
	{
		cout << "Student& operator= (const Student& s)" << endl;
		if (this != &s)
		{
			//需要显示调用父类的赋值运算符
			Person::operator =(s);		//这个算是自己写的，注意作用域（父类和子类的operator=是同名隐藏）	 
			_num = s._num;
		}
		return *this;
	}

	//显示定义的析构，在子类函数体执行完的时候，也会自动调用父类析构
	//子类的析构会自动调用父类的析构
	~Student()
	{
		cout << "~Student()" << endl;
		//父类的析构不需要显示写，会自动调用父类的析构
		//Person::~Person();		//必须加作用域才可以调用父类的析构（前提是父类没有资源），原因是父类和子类的析构时同名隐藏（父类和子类的析构函数底层函数名是相同的）
		//析构函数的名称：底层（destructor）
	}
protected:
	int _num; //学号
};

void test()
{
	Student s1("jack", 18);
	Student s2(s1);
	Student s3("rose", 17);
	s1 = s3;
	//输出：
	//Person()			父类的构造函数
	//Student()			子类的构造函数
	//Person(const Person& p)	父类的拷贝构造函数
	//Student(const Student& s)	子类的拷贝构造函数
	//Person()			父类的构造函数
	//Student()			子类的构造函数
	//Student& operator= (const Student& s)		子类的=运算符
	//Person operator=(const Person& p)			父类的=运算符
	//~Student()		子类的析构函数
	//~Person()			父类的析构函数
	//~Student()
	//~Person()
	//~Student()
	//~Person()
}

int main()
{
	test();
	return 0;
}