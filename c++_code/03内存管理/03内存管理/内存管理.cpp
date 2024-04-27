#include <iostream>
//#include <string.h>

using namespace std;

/*
//�ڴ�ֲ���
int globalVar = 1;	//ȫ�����ݶ�
static int staticGlobalVar = 1;	//���ݶ�

void test1()
{
	static int staticVar = 1;	//���ݶΣ����ݶΰ�����ȫ�����ݶκ;�̬����
	int localVar = 1;	//ջ
	int num1[10] = { 1, 2, 3, 4 };	//ջ
	char char2[] = "abcd";	//�ַ����飬char2��ջ�ϣ��ұ�"abcd"�ǳ����ַ������ڴ���Σ���仰�ǰѳ����ַ�������֮��ŵ��������ˣ�char2��ջ�ϣ�*charҲ��ջ��
	const char* pChar3 = "abcd";	//����ʹ��char*��pChar3��ջ�ϣ�ָ�����ַ���"abcd"��*pChar3�ڴ������
	int* ptr1 = (int*)malloc(sizeof(int) * 4);	//ptr1��ջ�ϣ��ұ߿��ٵĿռ��ڶ��ϣ�ptr1��ջ�ϣ�ָ��ѣ�*ptr1���ڶ���
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
	cout << sizeof(num1) << endl;	//40
	cout << sizeof(char2) << endl;	//5	��5��Ԫ�أ������и�'\0'
	cout << sizeof(pChar3) << endl;	//4/8	��һ��ָ�룬32λΪ4���ֽڣ�64λΪ8���ֽ�
	cout << sizeof(ptr1) << endl;	//4/8	��һ��ָ��
	cout << strlen(char2) << endl;	//4	��ע'\0'��λ��
	cout << strlen(pChar3) << endl;	//4
	free(ptr1);
	free(ptr3);
}
*/

/* 
//����2G���ڴ��4G���ڴ�
void test2()
{
	char*ptr = (char*)malloc(0x7fffffff);	//����2��G�Ŀռ�
	char*ptr = (char*)malloc(0Xffffffff);	//����4��G�Ŀռ䣬��32λ����ϵͳ�лᱨ��
}
*/

/* 
//new��delete	��������
void test3()
{
	//��������:
	//��̬����һ��int���͵Ŀռ�
	int* ptr = new int;
	//��̬����һ��int���͵Ŀռ䲢��ʼ��Ϊ10
	int* ptr1 = new int(10);
	//��̬����10��int���͵Ŀռ�
	int *ptr2 = new int[10];
	cout << *ptr << endl;   //û�г�ʼ���ĳ�ʼֵ��һ��
	cout << *ptr1 << endl;
	cout << *ptr2 << endl;
	delete ptr;
	delete ptr1;
	delete[] ptr2;
	//������ͷŵ�ʱ��new[]��delete[]����һ��
}

//new��delete	�Զ�������
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
	//������Ǹ�Test���͵Ŀռ�
	Test* ptr = new Test;
	delete ptr;
	//����10��Test���͵Ķ���
	Test* p2 = new Test[10];
	delete[] p2;
}
*/

/* 
//operator new����ԭ�ͣ�void* operator new(size_t n)
void test5()
{
	//operator newʹ�ú���malloc��operator deleteʹ�ú���malloc
	int* ptr = (int*)operator new(sizeof(int));
	int* ptr2 = (int*)malloc(sizeof(int));

	operator delete(ptr);
	free(ptr2);
}
*/

/* 
//����ڵ�ʹ���ڴ��������ͷſռ�
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
	//���:
	//memory pool allocate
	//memory pool deallocate
}
*/

/* 
//��λnew���ʽ
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
	//pt����ָ���ֻ��������Test������ͬ��С��һ�οռ䣬����������һ��������Ϊ���캯��û��ִ��
	Test* pt = (Test*)malloc(sizeof(Test));
	new(pt) Test; //ע�⣺���Test��Ĺ��캯���в���ʱ���˴���Ҫ����
	//new��λ���ʽ��new(ָ��) ����(�����б���ѡ��)	new(pt) Test(10);
	//delete pt;		//������������������delete
	pt->~Test();	//�ͷſռ�֮ǰ��ʾ������������������Դ
	free(pt);		//�ͷſռ�
	//��������
	//Test():00C99A80
	//~Test() :00C99A80
}
*/

//�ڶ���һ������4G�ڲ���64λ����ϵͳ�ſ��ԣ�32λ����ϵͳ���У�
void test8()
{
	void* p = new char[0xfffffffful];		//32λ��������ܴ�С���ó���0x7fffffff��ֻ����64λ������4G�ڴ� 
	cout << "new:" << p << endl;
}

int main()
{
	//test1();	//�ڴ�ֲ���
	//test2();	//����2G���ڴ��4G���ڴ�
	//test3();	//new��delete	��������
	//test4();	//new��delete	�Զ�������
	//test5();
	//test6();	//����ڵ��ڴ��
	//test7();	//��λnew���ʽ
	test8;	//�ڶ���һ������4G�ڲ���64λ����ϵͳ�ſ��ԣ�32λ����ϵͳ���У�
	return 0;
}