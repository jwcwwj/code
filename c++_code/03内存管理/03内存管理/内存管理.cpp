#include <iostream>
//#include <string.h>

using namespace std;

/*
//内存分布区
int globalVar = 1;	//全局数据段
static int staticGlobalVar = 1;	//数据段

void test1()
{
	static int staticVar = 1;	//数据段，数据段包括了全局数据段和静态数据
	int localVar = 1;	//栈
	int num1[10] = { 1, 2, 3, 4 };	//栈
	char char2[] = "abcd";	//字符数组，char2在栈上，右边"abcd"是常量字符串，在代码段，这句话是把常量字符串复制之后放到数组中了，char2在栈上，*char也在栈上
	const char* pChar3 = "abcd";	//不能使用char*，pChar3在栈上，指向常量字符串"abcd"，*pChar3在代码段上
	int* ptr1 = (int*)malloc(sizeof(int) * 4);	//ptr1在栈上，右边开辟的空间在堆上，ptr1在栈上，指向堆，*ptr1是在堆上
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
	cout << sizeof(num1) << endl;	//40
	cout << sizeof(char2) << endl;	//5	有5个元素，后面有个'\0'
	cout << sizeof(pChar3) << endl;	//4/8	是一个指针，32位为4个字节，64位为8个字节
	cout << sizeof(ptr1) << endl;	//4/8	是一个指针
	cout << strlen(char2) << endl;	//4	关注'\0'的位置
	cout << strlen(pChar3) << endl;	//4
	free(ptr1);
	free(ptr3);
}
*/

/* 
//申请2G的内存和4G的内存
void test2()
{
	char*ptr = (char*)malloc(0x7fffffff);	//申请2个G的空间
	char*ptr = (char*)malloc(0Xffffffff);	//申请4个G的空间，在32位操作系统中会报错
}
*/

/* 
//new和delete	内置类型
void test3()
{
	//内置类型:
	//动态申请一个int类型的空间
	int* ptr = new int;
	//动态申请一个int类型的空间并初始化为10
	int* ptr1 = new int(10);
	//动态申请10个int类型的空间
	int *ptr2 = new int[10];
	cout << *ptr << endl;   //没有初始化的初始值都一样
	cout << *ptr1 << endl;
	cout << *ptr2 << endl;
	delete ptr;
	delete ptr1;
	delete[] ptr2;
	//申请和释放的时候new[]和delete[]都在一起
}

//new和delete	自定义类型
class Test
{
public:
	Test()
		:_data(0)
	{
		cout << "Test():" << this << endl;
	}

	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};

void test4()
{
	//申请的那个Test类型的空间
	Test* ptr = new Test;
	delete ptr;
	//申请10个Test类型的对象
	Test* p2 = new Test[10];
	delete[] p2;
}
*/

/* 
//operator new函数原型：void* operator new(size_t n)
void test5()
{
	//operator new使用很像malloc，operator delete使用很像malloc
	int* ptr = (int*)operator new(sizeof(int));
	int* ptr2 = (int*)malloc(sizeof(int));

	operator delete(ptr);
	free(ptr2);
}
*/

/* 
//链表节点使用内存池申请和释放空间
struct ListNode
{
	ListNode* _next;
	ListNode* _prev;
	int _data;
	void* operator new(size_t n)
	{
		void* p = nullptr;
		p = allocator<ListNode>().allocate(1);
		cout << "memory pool allocate" << endl;
		return p;
	}
	void operator delete(void* p)
	{
		allocator<ListNode>().deallocate((ListNode*)p, 1);
		cout << "memory pool deallocate" << endl;
	}
};

class List
{
public:
	List()
	{
		_head = new ListNode;
		_head->_next = _head;
		_head->_prev = _head;
	}
	~List()
	{
		ListNode* cur = _head->_next;
		while (cur != _head)
		{
			ListNode* next = cur->_next;
			delete cur;
			cur = next;
		}
		delete _head;
		_head = nullptr;
	}
private:
	ListNode* _head;
};

void test6()
{
	List l;
	//输出:
	//memory pool allocate
	//memory pool deallocate
}
*/

/* 
//定位new表达式
class Test
{
public:
	Test()
		: _data(0)
	{
		cout << "Test():" << this << endl;
	}

	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};

void test7()
{
	//pt现在指向的只不过是与Test对象相同大小的一段空间，还不能算是一个对象，因为构造函数没有执行
	Test* pt = (Test*)malloc(sizeof(Test));
	new(pt) Test; //注意：如果Test类的构造函数有参数时，此处需要传参
	//new定位表达式：new(指针) 类型(参数列表（可选）)	new(pt) Test(10);
	//delete pt;		//下面两步合起来就是delete
	pt->~Test();	//释放空间之前显示调用析构函数清理资源
	free(pt);		//释放空间
	//输出结果：
	//Test():00C99A80
	//~Test() :00C99A80
}
*/

//在堆上一次申请4G内部（64位操作系统才可以，32位操作系统不行）
void test8()
{
	void* p = new char[0xfffffffful];		//32位下数组的总大小不得超过0x7fffffff，只能在64位下申请4G内存 
	cout << "new:" << p << endl;
}

int main()
{
	//test1();	//内存分布区
	//test2();	//申请2G的内存和4G的内存
	//test3();	//new和delete	内置类型
	//test4();	//new和delete	自定义类型
	//test5();
	//test6();	//链表节点内存池
	//test7();	//定位new表达式
	test8;	//在堆上一次申请4G内部（64位操作系统才可以，32位操作系统不行）
	return 0;
}