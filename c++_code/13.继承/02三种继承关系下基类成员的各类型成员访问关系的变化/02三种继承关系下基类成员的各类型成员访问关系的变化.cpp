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
	string _name;	//����

private:
	int _age;		//����
};

//public�̳�
class Student1 : public Person
{
protected:
	int _stunum; // ѧ��

	void fun(Student1 s)		
	{
		s._name;	//protected���Է���
		//s._age;	//private���ɷ���
	}
};
 
void test1()
{
	Student1 s1;
	s1.Print();		//public���Է���
}

//protected�̳�
class Student2 : protected Person
{
protected:
	int _stunum; // ѧ��

	void fun(Student2 s2)
	{ 
		s2._name;
		cout << _name << endl;		//protected���Է���
		//cout << _age << endl;		//private�����Է���
	}
};

void test2()
{
	Student1 s2;
	s2.Print();		//public���Է���
}

//private�̳�
class Student3 : private Person
{
protected:
	int _stunum; // ѧ��
	void fun()
	{
		Print();
		_name;
		//_age;		//private�����Է���
	}
};

void test3()
{
	Student3 s3;
	//s3.Print();		//���ɷ���
}

int main()
{
	cout << sizeof(string) << endl;		//28
	test1();
	test2();
	test3();
	return 0;
}