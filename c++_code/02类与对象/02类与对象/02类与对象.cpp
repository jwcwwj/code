#define _CRT_SECURE_NO_WARNINGS   //定义宏，禁止相关警告,用于禁止或屏蔽某些编译器警告信息。
#include <iostream>   

using namespace std;

//类的简单使用
struct Student
{
	void SetStudentInfo(const char* name, const char* gender, int age)
	{
		strcpy(_name, name);		//c++使用strcpy_s或者加上#define _CRT_SECURE_NO_WARNINGS（必须放在第一行）
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
	s.SetStudentInfo("Peter", "男", 18);
	s.PrintStudentInfo();	//Pater	男	18
}

//类的对齐
class A
{
	int a;		//4 + 4		//int是4个字节，double是8个字节，a要对齐b补充4个字节
	double b;	//8
	char c;		//1 + 3
	int  d;		//4
};

class B
{
	int a;		//4 + 4
	double b;	//8
	int  d;		//4
	char c;		//1 + 3		加3是要满足类的大小要是最大字节的整数倍
};

class C
{
	int a;		//4 + 4
	double b;	//8
	char c;		//1 + 7
	//B中变量的最大对齐值是8
	B e;		//24
};

class D
{
	int a;		//4 + 4
	double b;	//8
	//B中变量的最大对齐值是8
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

//指针计算偏移量
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

//offsetof宏计算偏移量
void test4()
{
	std::cout << "offset of i: " << offsetof(MyClass, i) << std::endl;	//0
	std::cout << "offset of c: " << offsetof(MyClass, c) << std::endl;	//4
	std::cout << "offset of d: " << offsetof(MyClass, d) << std::endl;	//8
}

//大小端
void test5()
{
	int a = 1;	//0x00 00 00 01
	char* pa = (char*)&a;	//取一位低地址字节
	if (*pa)
		cout << "是小端" << endl;		//低地址是1说明低地址存低位，是小端
	else
		cout << "是大端" << endl;
}

//大小端
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
		cout << "是小端" << endl;		//低地址是1说明低地址存低位，是小端
	else
		cout << "是大端" << endl;
}

//this指针	结果相同，证明调用函数传的第一个形参是this指针，就是调用对象的地址
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

//this指针可以为空吗
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
	//p->PrintA();		//不可以调用访问了this指针指向的对象，因为this指针为nullptr，空指针不能解引用。
	p->Show();			//可以调用，没有访问this指针指向的对象，也没有修改this指针指向的对象
	//总结：this指针能不能为空是看情况的，不访问或者修改this指针指向对象的值就可以使用，否则不能使用
}

int main()
{
	//test1();		//类的简单使用
	//test2();		//类的对齐
	//test3();		//指针计算偏移量
	//test4();		//offsetof宏计算偏移量
	//test5();		//大小端
	//test6();		//大小端
	//test7();		//this指针
	test8();		//this指针可以为空（nullptr）吗
	return 0;
}