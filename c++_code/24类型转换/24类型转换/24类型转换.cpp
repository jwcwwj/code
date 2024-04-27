#include <iostream>

using namespace std;

class A
{
public:
	virtual void fun(){}
};

class B : public A
{

};

void test()
{
	//c语言
	int a = 10;
	double f = 1.2;
	//隐式类型转换
	a = f;

	int* pa = &a;
	//强制类型转换
	a = (int)pa;

	int* p = (int*)malloc(4);

	//c++的类型转换
	//1.static_cast：支持所有的隐式类型转换
	//特殊情况：继承中把父类的向子类转换(只能是指针或者引用，不能是值类型)
	//不支持其他的强制类型转换
	a = static_cast<int>(f);
	A* a1 = new A;
	//B* b1 = (B*)a1;		//不安全
	B* b1 = static_cast<B*>(a1);

	A a2;
	B b2;
	//a2 = (A)b2;		//error
	//b2 = static_cast<B>(a2);			//error


	//2.reinterpret_cast：支持强制类型转换（重写解释）
	A a3;
	A* a4 = &a3;
	//a3 = reinterpret_cast<A>(a4);		//error
	a = reinterpret_cast<int>(pa);


	//3.const_cast：去除变量的const属性
	volatile const int c = 10;
	volatile const int* pcc = &c;		
	int* pc = const_cast<int*>(&c);
	*pc = 20;
	//*pcc = 30;		//error，表达式必须是可修改的左值
	cout << *pc << endl;	//20
	//cout << c << endl;		//10，原因是编译器看见const做了一个优化，没有从内存中读取数据，而是依据const确定值没变，是10，实际在内存中的值是20
	//解决办法：加上关键字volatile，表示每次获取数据从寄存器中读取数据，不能从暂存中读取数据
	cout << c << endl;			//20
	//语法只在编译时有效，程序运行起来就可以穿透这个语法的限制


	//4.dynamic_cast：只用于多态场景下的父类引用/指针向子类引用/指针转换
	//检查转换是否安全，只有安全才会转换成功，不安全返回nullptr
	//父类 -> 子类	向下转型
	//子类 -> 父类	向上转型
	A* pppa = new A;
	B* pppb = dynamic_cast<B*>(pppa);
	B* pppb1 = static_cast<B*>(pppa);
	cout << pppb << endl;		//00000000  	不安全的转换	相当于做了一个类型检查	安全转换成功，不安全转换失败
	cout << pppb1 << endl;		//00BAF320		

	A* pppa2 = new B;
	pppb = dynamic_cast<B*>(pppa2);
	pppb1 = static_cast<B*>(pppa2);
	cout << pppb << endl;		//00BAF350
	cout << pppb1 << endl;		//00BAF350
}

int main()
{
	test();
	return 0;
}