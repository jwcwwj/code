#include <iostream>
#include <string>

using namespace std;

class Student;

class Person
{
public:
	friend void Display(const Person& p, const Student& s);
protected:
	string _name = "jac"; // ����
};

class Student : public Person
{
	//friend void Display(const Person& p, const Student& s);
protected:
	int _stuNum; // ѧ��
};

void Display(const Person& p, const Student& s)
{
	cout << p._name << endl;		//�����jac		û��ָ��ֵ������ַ���
	//��Ԫ��ϵ���ܼ̳�
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