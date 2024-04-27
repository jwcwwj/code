#include <iostream>
#include <string>

using namespace std;

//基类
class Person
{
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}
protected:
	string _name = "peter"; //姓名
	int _age = 18;			//年龄
};

//派生类
class Student : public Person		//class默认是private，static默认是public
{
protected:
	int _stuid; //学号
};

class Teacher : public Person
{
protected:
	int _jobid; // 工号
}; 

void test()
{
	Student s;
	Teacher t;
	s.Print();
	//输出：
	//name:peter
	//age:18
	t.Print();
	//输出：
	//name:peter
	//age:18
}

int main()
{
	test();
	return 0;
}