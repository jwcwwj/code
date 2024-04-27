#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
	Person() { ++_count; }

protected:
	string _name;			//����

public:
	static int _count;		//ͳ���˵ĸ�����
};

int Person::_count = 0;		//�����ʼ����̬��Ա

class Student : public Person
{
protected:
	int _stuNum; // ѧ��
};

class Graduate : public Student
{
protected:
	string _seminarCourse;		//�о���Ŀ
}; 

void test()
{
	Student s1;
	Student s2;
	Student s3;
	Graduate s4;
	cout << "����:" << Person::_count << endl;	//������4
	Student::_count = 0;
	cout << "����:" << Person::_count << endl;	//������0
}

int main()
{
	test();
	return 0;
}