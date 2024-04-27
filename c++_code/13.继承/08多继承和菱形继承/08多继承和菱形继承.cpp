#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
	string _name; //����
};

class Student : public Person
{
protected:
	int _num; //ѧ��
};

class Teacher : public Person
{
protected:
	int _id; //ְ�����
};

class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; //���޿γ�
};

void Test()
{
	// �������ж������޷���ȷ֪�����ʵ�����һ��
	Assistant a;
	//a._name = "peter";	//error
	// ��Ҫ��ʾָ�������ĸ�����ĳ�Ա���Խ�����������⣬�����������������޷����
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