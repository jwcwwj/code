#define _CRT_SECURE_NO_WARNINGS   //����꣬��ֹ��ؾ���,���ڽ�ֹ������ĳЩ������������Ϣ��
#include <iostream>   

using namespace std;

//��ļ�ʹ��
struct Student
{
	void SetStudentInfo(const char* name, const char* gender, int age)
	{
		strcpy(_name, name);		//c++ʹ��strcpy_s���߼���#define _CRT_SECURE_NO_WARNINGS��������ڵ�һ�У�
		strcpy(_gender, gender);
		_age = age;
	}
	void PrintStudentInfo()
	{
		cout << _name << " " << _gender << " " << _age << endl;
	}
	char _name[20];
	char _gender[3];
	int _age;
};

void test1()
{
	Student s;
	s.SetStudentInfo("Peter", "��", 18);
	s.PrintStudentInfo();	//Pater	��	18
}

//��Ķ���
class A
{
	int a;		//4 + 4		//int��4���ֽڣ�double��8���ֽڣ�aҪ����b����4���ֽ�
	double b;	//8
	char c;		//1 + 3
	int  d;		//4
};

class B
{
	int a;		//4 + 4
	double b;	//8
	int  d;		//4
	char c;		//1 + 3		��3��Ҫ������Ĵ�СҪ������ֽڵ�������
};

class C
{
	int a;		//4 + 4
	double b;	//8
	char c;		//1 + 7
	//B�б�����������ֵ��8
	B e;		//24
};

class D
{
	int a;		//4 + 4
	double b;	//8
	//B�б�����������ֵ��8
	B e;		//24
	char c;		//1 + 7
};


void test2()
{
	cout << sizeof(A) << endl;	//24
	cout << sizeof(B) << endl;	//24
	cout << sizeof(C) << endl;	//48
	cout << sizeof(D) << endl;	//48
}

class MyClass 
{
public:
	int i;
	char c;
	double d;
};

//ָ�����ƫ����
void test3()
{
	MyClass obj;
	std::cout << "offset of i: " << (char*)&obj.i - (char*)&obj << std::endl;	//0
	std::cout << "offset of c: " << (char*)&obj.c - (char*)&obj << std::endl;	//4
	//std::cout << "offset of c: " << (double*)&obj.c - (double*)&obj << std::endl;	//0
	std::cout << "offset of d: " << (char*)&obj.d - (char*)&obj << std::endl;	//8
	//std::cout << "offset of d: " << (int*)&obj.d - (int*)&obj << std::endl;	//2
	//std::cout << "offset of d: " << (double*)&obj.d - (double*)&obj << std::endl;	//1
}

//offsetof�����ƫ����
void test4()
{
	std::cout << "offset of i: " << offsetof(MyClass, i) << std::endl;	//0
	std::cout << "offset of c: " << offsetof(MyClass, c) << std::endl;	//4
	std::cout << "offset of d: " << offsetof(MyClass, d) << std::endl;	//8
}

//��С��
void test5()
{
	int a = 1;	//0x00 00 00 01
	char* pa = (char*)&a;	//ȡһλ�͵�ַ�ֽ�
	if (*pa)
		cout << "��С��" << endl;		//�͵�ַ��1˵���͵�ַ���λ����С��
	else
		cout << "�Ǵ��" << endl;
}

//��С��
void test6()
{
	union A
	{
		char a;
		int b;
	};

	A obja;
	obja.b = 1; //0x 00 00 00 01
	if(obja.a)
		cout << "��С��" << endl;		//�͵�ַ��1˵���͵�ַ���λ����С��
	else
		cout << "�Ǵ��" << endl;
}

//thisָ��	�����ͬ��֤�����ú������ĵ�һ���β���thisָ�룬���ǵ��ö���ĵ�ַ
class MyClass1 
{
public:
	void print() 
	{
		std::cout << "Address of object: " << this << std::endl;
	}
};

void test7()
{
	MyClass1 obj;
	std::cout << "Address of object: " << &obj << std::endl;
	obj.print();
}

//thisָ�����Ϊ����
class A1
{
public:
	void PrintA()
	{
		cout << _a << endl;
	}
	
	void Show()
	{
		cout << "Show()" << endl;
	}

private:
	int _a;
};

void test8()
{
	A1* p = nullptr;
	//p->PrintA();		//�����Ե��÷�����thisָ��ָ��Ķ�����Ϊthisָ��Ϊnullptr����ָ�벻�ܽ����á�
	p->Show();			//���Ե��ã�û�з���thisָ��ָ��Ķ���Ҳû���޸�thisָ��ָ��Ķ���
	//�ܽ᣺thisָ���ܲ���Ϊ���ǿ�����ģ������ʻ����޸�thisָ��ָ������ֵ�Ϳ���ʹ�ã�������ʹ��
}

int main()
{
	//test1();		//��ļ�ʹ��
	//test2();		//��Ķ���
	//test3();		//ָ�����ƫ����
	//test4();		//offsetof�����ƫ����
	//test5();		//��С��
	//test6();		//��С��
	//test7();		//thisָ��
	test8();		//thisָ�����Ϊ�գ�nullptr����
	return 0;
}