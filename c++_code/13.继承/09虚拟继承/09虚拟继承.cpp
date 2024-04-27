#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
	string _name; //姓名
};

class Student : virtual public Person
{
protected:
	int _num; //学号
};

class Teacher : virtual public Person
{
protected:
	int _id; //职工编号
};

class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; //主修课程
};

void test()
{
	Assistant a;
	a._name = "peter";	//虚拟继承之后就不会有歧义了
	a.Student::_name = "xxx";
	a.Teacher::_name = "yyy";		//改的是同一个内容
	cout << sizeof(Person) << endl;		//28
	cout << sizeof(Student) << endl;	//36 = 4(指针) + 28 + 4
	cout << sizeof(Teacher) << endl;	//36 = 4(指针) + 28 + 4
	cout << sizeof(Assistant) << endl;	//72 = 8 + 8 + 28 + 28
}

int main()
{
	test();
	return 0;
}