#include <iostream>
#include <string>

using namespace std;

//����
class Person
{
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}
protected:
	string _name = "peter"; //����
	int _age = 18;			//����
};

//������
class Student : public Person		//classĬ����private��staticĬ����public
{
protected:
	int _stuid; //ѧ��
};

class Teacher : public Person
{
protected:
	int _jobid; // ����
}; 

void test()
{
	Student s;
	Teacher t;
	s.Print();
	//�����
	//name:peter
	//age:18
	t.Print();
	//�����
	//name:peter
	//age:18
}

int main()
{
	test();
	return 0;
}