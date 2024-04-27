#include <iostream>
#include <string.h>

using namespace std;

//判等
template <class T>
bool isEqual(T& a, T& b)
{
	return a == b;
}

//模板的特化
//前提：已有一个通用的模板

//1.全特化
template <>
bool isEqual<const char*>(const char*& a,const char*& b)
{
	return strcmp(a, b) == 0;		//strcmp等于0表示相等，不等于0表示不相等
}

//1.也可以写一个普通的函数做全特化的事情
//2.当普通函数比模板函数合适的时候会调用普通函数（普通函数完全匹配）
//3.当普通的函数和模板函数同时存在时，作用一样，会调用普通函数
bool isEqual(const char* a, const char* b)
{
	return strcmp(a, b);
}

void test()
{
	//bool ret = isEqual(1, 2);
	//ret = isEqual(1.2, 1.2);
	bool ret = isEqual("123", "123");

	const char* ptr = "123";			//常量字符串
    const char ptr2[] = "123";			//加const为了和常量字符串类型一样

	ret = isEqual(ptr, ptr2);			
	cout << ret << endl;		//0
}

int main()
{
	test();
	return 0;
}