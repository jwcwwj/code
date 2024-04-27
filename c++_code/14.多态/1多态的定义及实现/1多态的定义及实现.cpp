#include <iostream>
#include <string>

using namespace std;

//多态条件：
//0.前提：继承
//1.有序函数
//2.子类重写父类的虚函数
//3.调用此函数的类型是基类的指针或引用(基类包括本类自身)

//如果调用此函数的类型是值（不满足多态），就会调用父类的虚函数。

class Person 
{
public:
	//虚函数：virtual + 正常的函数定义
	virtual void BuyTicket() const
	{
		cout << "买票-全价" << endl; 
	}
};

class Student : public Person
{
public:
	//虚函数重写：子类定义了一个和父类接口完全相同的函数
	//重写的虚函数：函数名、参数列表、返回值类型都和父类对应的一致
	//不是虚函数就是函数重写了，函数重写只要求基类和派生类有相同的函数名，参数可以不一样
	//两个基类和派生类的同名函数不构成重写（覆盖）就是重定义（隐藏）
	//虚函数：virtual + 正常的函数定义

	//注意：在重写基类虚函数时，派生类的虚函数在不加virtual关键字时，虽然也可以构成重写(因为继承后
	//基类的虚函数被继承下来了在派生类依旧保持虚函数属性), 但是该种写法不是很规范，不建议这样使用
	virtual void BuyTicket() const		//virtual在子类可以不写，但推荐写上
	{
		cout << "买票-半价" << endl;
	}
};

//多态：看参数实际指向哪一个对象(切片)
void fun(const Person& p)
{
	p.BuyTicket();
}
 
//非多态：看参数的类型(值拷贝)
void func(const Person p)
{
	p.BuyTicket();
}

void test()
{
	Person p;
	Student s;
	fun(p);		//买票-全价
	fun(s);		//买票-半价
	func(p);	//买票-全价
	func(s);	//买票-全价
}

int main()
{
	test();
	return 0;
}