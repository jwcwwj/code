#include <iostream>
#include <string>

using namespace std;

class Person
{
protected:
	string _name;	//姓名
	string _sex;	//性别
	int _age;		//年龄
};

class Student : public Person
{
public:
	int _No; // 学号
};

void test()
{
	Student sobj;
	//1.子类对象可以赋值给父类对象/指针/引用（切片）
	//和内置类型的隐式类型转换一样
	//子类 -> 父类
	Person pobj = sobj;		//发生了拷贝，不是一个对象
	Person* pp = &sobj;
	Person& rp = sobj;

	//2.基类对象（父类）不能赋值给派生类（子类）对象
	//sobj = pobj;		//error
	
	//3.基类（父类）的指针可以通过强制类型转换赋值给派生类（子类）的指针
	//父类指针、引用不能直接赋值给子类指针引用
	Student* ps1 = (Student*)pp; //这种情况转换是可以的。	pp里面存放的是Student的地址
	ps1->_No = 10;
	pp = &pobj;		//pp里面存放的是Person的地址

	//下面的情况访问不到子类新增的成员，不要写
	Student* ps2 = (Student*)pp; // 这种情况转换时虽然可以，但是会存在越界访问的问题
	//ps2->_No = 10;	//error，越界访问
}

int main()
{
	test();
	return 0;
}