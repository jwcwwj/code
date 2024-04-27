#include <iostream>
#include <string>

using namespace std;

class Student;

class Person
{
public:
	friend void Display(const Person& p, const Student& s);
protected:
	string _name = "jac"; // 姓名
};

class Student : public Person
{
	//friend void Display(const Person& p, const Student& s);
protected:
	int _stuNum; // 学号
};

void Display(const Person& p, const Student& s)
{
	cout << p._name << endl;		//输出：jac		没有指定值输出空字符串
	//友元关系不能继承
	//cout << s._stuNum << endl;		//error
} 

void test()
{
	Person p;
	Student s;
	Display(p, s);
}

int main()
{
	test();
	return 0;
}