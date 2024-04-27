#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
	string _name; //����
};

class Student : virtual public Person
{
protected:
	int _num; //ѧ��
};

class Teacher : virtual public Person
{
protected:
	int _id; //ְ�����
};

class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; //���޿γ�
};

void test()
{
	Assistant a;
	a._name = "peter";	//����̳�֮��Ͳ�����������
	a.Student::_name = "xxx";
	a.Teacher::_name = "yyy";		//�ĵ���ͬһ������
	cout << sizeof(Person) << endl;		//28
	cout << sizeof(Student) << endl;	//36 = 4(ָ��) + 28 + 4
	cout << sizeof(Teacher) << endl;	//36 = 4(ָ��) + 28 + 4
	cout << sizeof(Assistant) << endl;	//72 = 8 + 8 + 28 + 28
}

int main()
{
	test();
	return 0;
}