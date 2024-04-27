#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
	string _name; //姓名
};

class Student : public Person
{
protected:
	int _num; //学号
};

class Teacher : public Person
{
protected:
	int _id; //职工编号
};

class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; //主修课程
};

void Test()
{
	// 这样会有二义性无法明确知道访问的是哪一个
	Assistant a;
	//a._name = "peter";	//error
	// 需要显示指定访问哪个父类的成员可以解决二义性问题，但是数据冗余问题无法解决
	a.Student::_name = "xxx";
	a.Teacher::_name = "yyy";
}

void test()
{
	cout << sizeof(Person) << endl;		//28
	cout << sizeof(Student) << endl;	//32
	cout << sizeof(Teacher) << endl;	//32
	cout << sizeof(Assistant) << endl;	//92 = 32 + 32 + 28
}

int main()
{
	test();
	return 0;
}