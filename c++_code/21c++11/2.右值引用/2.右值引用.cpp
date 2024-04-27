#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int fun(int a)
{
	return a;		//�����������Ͻ�����ֵ��������ֵ
	//����ֵ���Ǿֲ�����a������a��һ������
}

//��ֵ����
void test1()
{
	//c�����о�������ֵ����ֵ��˵�������ֲ��� ����ȷ��
	//��ֵ�����Գ����ڸ�ֵ����ߣ�Ҳ���Գ����ڸ�ֵ���ұߡ�
	//��ֵ��ֻ�ܳ����ڸ�ֵ���ұߵġ�
	//����������ȫ��ȷ�ġ�
	//����һ��˵���ǣ�����ȡ��ַ������ֵ������ȡ��ַ������ֵ�����˵��Ҳ������ȫ��ȷ�ġ�

	int a = 10;
	int b = a;
	//a����ֵ
	//10 = b;		//error������������ֵ��ֻ�ܳ����� = ���ұ�

	int* pa = &a;
	//int* pi = &10;	//���ܸ�10ȡ��ַ

	//c++�е����ַ�ʽ��
	//��ֵ����������ʱ����������������������ֵ�������������Ͼ�Ҫ������,�����ķ���ֵ���ǽ���ֵ��
	//��ֵ��ʣ�µĶ�����ֵ��

	b = fun(a);
	//fun(a) = a;				//error��fun(a)����ֵ
	//int* pa2 = &(fun(a));		//error����ֵ����ȡ��ַ

	//֮ǰѧϰ�Ķ�����ֵ���ã����濴��ֵ����
	//��ֵ����&������������ֵ��Ҳ����������ֵ
	int a1 = 10;
	int& ra = a1;
	const int& ri = 10;
	const int& ri2 = fun(a1);

	//��ֵ����&&��ֻ��������ֵ
	//��ֵ���ò���������ֵ
	//int&& rra = a;	//error
	int&& rri = 10;
	int&& rri2 = fun(a);
}

class String
{
	friend ostream& operator<<(ostream& out,const String& str1);
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	//��������
	//��ֵ����
	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
		cout << "String(const String&)" << endl;
	}

	//��ֵ����		
	//�ƶ�����Ϳ������칹��������
	//�ƶ����죬ʹ���ƶ����壬�Ѷ����е���Դ�ƶ�����һ��������ȥ
	//�������������߿���Ч��
	//String(const String&& s)		//���ܼ�const�����ʽ�����ǿ��޸ĵ���ֵ
	String(String&& s)
		: _str(s._str)
	{
		s._str = nullptr;
		cout << "String(String&&)" << endl;
	}
	
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* pTemp = new char[strlen(s._str) + 1];
			strcpy(pTemp, s._str);
			delete[] _str;
			_str = pTemp;
		}
		cout << "String& operator=(const String&)" << endl;
		return *this;
	}

	//��ֵ��ֵ
	String& operator=(String&& s)
	{
		if (this != &s)
		{
			delete[] _str;
			_str = s._str;
			s._str = nullptr;
		}
		cout << "String& operator=(String&&)" << endl;
		return *this;
	}

	//ƴ��
	String operator+(const String& s)
	{
		char* pTemp = new char[strlen(_str) + strlen(s._str) + 1];
		strcpy(pTemp, _str);
		strcpy(pTemp + strlen(_str), s._str);
		String strRet(pTemp);
		return strRet;
	}

	~String()
	{
		if (_str) delete[] _str;
		cout << "~String()" << endl;
	}

	 
private:
	char* _str;
};

ostream& operator<<(ostream& out, const String& str1)
{
	out << str1._str;
	return out;
}

void test2()
{
	String s1("hello");
	String s2("world");
	String s3(s1 + s2);
	String s4(s2);
	String s5;
	//s5 = s2;
	s5 = s2 + s1;	
	//��ֵ������߿����͸�ֵ��Ч��

	//��ֵ����������ֵ����move������ı��������ڣ�ֻ�ǰѶ�������Դ���ֵ��Ϊ��ֵ
	String&& rs = std::move(s3);
	//String s6(move(s3));		 
	//cout << s3 << endl;	//error�������ʹ�ã�s3��Դ�Ѿ����ͷ���
	String&& s6(move(s3));
	cout << s3 << endl;
}

class Person
{
public:
	Person(const char* name, const char* sex, int age)
		: _name(name)
		, _sex(sex)
		, _age(age)
	{}
	
	Person(const Person& p)
		: _name(p._name)
		, _sex(p._sex)
		, _age(p._age)
	{}

#if 0
	Person(Person&& p)
		: _name(p._name)
		, _sex(p._sex)
		, _age(p._age)
	{}
#else	
	Person(Person&& p)
		: _name(move(p._name))
		, _sex(move(p._sex))
		, _age(p._age)
	{}
#endif
private:
	String _name;
	String _sex;
	int _age;
};
Person GetTempPerson()
{
	Person p("prety", "male", 18);
	return p;
}

void test3()
{
	Person p(GetTempPerson());
}

//����ת��
void Fun(int &x) { cout << "lvalue ref" << endl; }
void Fun(int &&x) { cout << "rvalue ref" << endl; }
void Fun(const int &x) { cout << "const lvalue ref" << endl; }
void Fun(const int &&x) { cout << "const rvalue ref" << endl; }
template<typename T>
void PerfectForward(T &&t) { Fun(std::forward<T>(t)); }
//void PerfectForward(const T& t) { Fun(t); }

void test4()
{
	PerfectForward(10); // rvalue ref
	int a;
	PerfectForward(a); // lvalue ref
	PerfectForward(std::move(a)); // rvalue ref
	const int b = 8;
	PerfectForward(b); // const lvalue ref
	PerfectForward(std::move(b)); // const rvalue ref
}

int main()
{
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}