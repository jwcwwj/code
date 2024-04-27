#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
	Person(const char* name = "peter")
		: _name(name)
	{
		cout << "Person()" << endl;
	}

	Person(const Person& p)
		: _name(p._name)
	{
		cout << "Person(const Person& p)" << endl;
	}

	Person& operator=(const Person& p)
	{
		cout << "Person operator=(const Person& p)" << endl;
		if (this != &p)
			_name = p._name;
		return *this;
	}

	~Person()
	{
		cout << "~Person()" << endl;
	}

protected:
	string _name; //����
};

class Student : public Person
{
public:
	//����Ĭ�ϵĹ��캯�����Զ����ø���Ĺ��캯��
	Student(const char* name, int num)
		: Person(name)
		, _num(num)
	{
		cout << "Student()" << endl;
	}

	//����Ĭ�ϵĿ������죬�Զ����ø���Ŀ�������
	//��ʾ����Ŀ������죬Ĭ�ϵ��ø����Ĭ�Ϲ��죨ָ��֮����ø��࿽�����죩
	Student(const Student& s)
		: Person(s)		//��Ƭ��ָ��֮����ø��࿽������
		, _num(s._num)
	{
		cout << "Student(const Student& s)" << endl;
	}

	//��ʾ����ĸ�ֵ������������Զ����ø���ĸ�ֵ�����
	//����Ĭ�ϵĸ�ֵ��������Զ����ø���ĸ�ֵ�����
	Student& operator = (const Student& s)
	{
		cout << "Student& operator= (const Student& s)" << endl;
		if (this != &s)
		{
			//��Ҫ��ʾ���ø���ĸ�ֵ�����
			Person::operator =(s);		//��������Լ�д�ģ�ע�������򣨸���������operator=��ͬ�����أ�	 
			_num = s._num;
		}
		return *this;
	}

	//��ʾ����������������ຯ����ִ�����ʱ��Ҳ���Զ����ø�������
	//������������Զ����ø��������
	~Student()
	{
		cout << "~Student()" << endl;
		//�������������Ҫ��ʾд�����Զ����ø��������
		//Person::~Person();		//�����������ſ��Ե��ø����������ǰ���Ǹ���û����Դ����ԭ���Ǹ�������������ʱͬ�����أ��������������������ײ㺯��������ͬ�ģ�
		//�������������ƣ��ײ㣨destructor��
	}
protected:
	int _num; //ѧ��
};

void test()
{
	Student s1("jack", 18);
	Student s2(s1);
	Student s3("rose", 17);
	s1 = s3;
	//�����
	//Person()			����Ĺ��캯��
	//Student()			����Ĺ��캯��
	//Person(const Person& p)	����Ŀ������캯��
	//Student(const Student& s)	����Ŀ������캯��
	//Person()			����Ĺ��캯��
	//Student()			����Ĺ��캯��
	//Student& operator= (const Student& s)		�����=�����
	//Person operator=(const Person& p)			�����=�����
	//~Student()		�������������
	//~Person()			�������������
	//~Student()
	//~Person()
	//~Student()
	//~Person()
}

int main()
{
	test();
	return 0;
}