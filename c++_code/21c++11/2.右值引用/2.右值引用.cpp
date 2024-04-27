#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int fun(int a)
{
	return a;		//生命周期马上结束的值叫做将亡值
	//返回值不是局部变量a，而是a的一个拷贝
}

//右值引用
void test1()
{
	//c语言中就有了左值和右值的说法，区分不是 很明确。
	//左值：可以出现在赋值的左边，也可以出现在赋值的右边。
	//右值：只能出现在赋值的右边的。
	//上面概念不是完全正确的。
	//还有一种说法是：可以取地址的是左值，不能取地址的是右值，这个说法也不是完全正确的。

	int a = 10;
	int b = a;
	//a是左值
	//10 = b;		//error，常量就是右值，只能出现在 = 的右边

	int* pa = &a;
	//int* pi = &10;	//不能给10取地址

	//c++中的区分方式：
	//右值：常量、临时变量（匿名变量）、将亡值（生命周期马上就要结束了,函数的返回值就是将亡值）
	//左值：剩下的都是左值。

	b = fun(a);
	//fun(a) = a;				//error，fun(a)是右值
	//int* pa2 = &(fun(a));		//error，右值不能取地址

	//之前学习的都是左值引用，下面看右值引用
	//左值引用&：可以引用左值，也可以引用右值
	int a1 = 10;
	int& ra = a1;
	const int& ri = 10;
	const int& ri2 = fun(a1);

	//右值引用&&：只能引用右值
	//右值引用不能引用左值
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

	//拷贝构造
	//左值引用
	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
		cout << "String(const String&)" << endl;
	}

	//右值引用		
	//移动构造和拷贝构造构成了重载
	//移动构造，使用移动语义，把对象中的资源移动到另一个对象中去
	//不进行深拷贝，提高拷贝效率
	//String(const String&& s)		//不能加const，表达式必须是可修改的左值
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

	//右值赋值
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

	//拼接
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
	//右值引用提高拷贝和赋值的效率

	//右值引用引用左值：加move，不会改变生命周期，只是把对象的属性从左值变为右值
	String&& rs = std::move(s3);
	//String s6(move(s3));		 
	//cout << s3 << endl;	//error，错误的使用，s3资源已经被释放了
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

//完美转发
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