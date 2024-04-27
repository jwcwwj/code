#include <iostream>

using namespace std;

//不能被继承
//方法1：
class A final		//final表示最终的意思，类A不能被继承
{

};

/*
class B : public A	//不能继承类A（不能将“final”类类型用作基类）
{

};
*/

//方法2：基类的构造函数定义为私有的
class C
{
public:

private:
	C() {};
};

class D : public C
{};

void test()
{
	//D d;	//error，无法引用“D”的默认构造函数--它是已删除的函数

}

int main()
{
	test();
	return 0;
}