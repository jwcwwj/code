#include <iostream>
#include <time.h>

using namespace std;

//1. ��ͨ�������ռ�
namespace N1 // N1Ϊ�����ռ������
{
	// �����ռ��е����ݣ��ȿ��Զ��������Ҳ���Զ��庯��
	int a = 10;
	int Add(int left, int right)
	{
		return left + right;
	}
}

//2. �����ռ����Ƕ��
namespace N2
{
	int a = 20;
	int b = 30;
	int Add(int left, int right)
	{
		return left + right;
	}
	namespace N3	//Ƕ�������ռ�
	{
		int c = 40;
		int d = 50;
		int Sub(int left, int right)
		{
			return left - right;
		}
	}
}

//3. ͬһ��������������ڶ����ͬ���Ƶ������ռ�,����������ϳ�ͬһ�������ռ��С�
namespace N1
{
	int Mul(int left, int right)
	{
		return left * right;
	}
}

void test1()
{
	//�����ռ������ʹ�÷�ʽ
	//01�������ռ����Ƽ��������޶���	�Ƽ�ʹ��	����ϲ����һ��
	cout << "N1::a = " << N1::a << endl;	//10
	cout << "N2::N3::c - N2::b = " << N2::N3::Sub(N2::N3::c, N2::b) << endl;	//10
	//cout << "N2::N3::c - N2::b = " << N2::N3::Sub(c, N2::b) << endl;			//error
	//cout << "N2::N3::c - N2::b = " << N2::N3::Sub(N2::N3::c,b) << endl;			//error
	//02ʹ��using�������ռ��г�Ա����	�Ƽ�ʹ�ã���һ�㲻ʹ��	�ڿռ�Ƕ�׶��ʱ��ʹ�ã�һ��ʹ�õ�һ��
	using N2::N3::c;
	cout << "N2::N3::c - N2::b = " << N2::N3::Sub(c, N2::b) << endl;	//10
	using N2::b;
	cout << "N2::N3::c - N2::b = " << N2::N3::Sub(c, b) << endl;			//10
	using N1::a;
	cout << a << endl;		//10
	//03ʹ��using namespace �����ռ���������	���Ƽ�ʹ��		�ڶ��˺���������ʱ�����ײ�����ͻ
	using namespace N1;
	cout << a << endl;	//10
}

//ȫȱʡ����
void TestFunc(int a = 10, int b = 20, int c = 30)
{
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}

//��ȱʡ����
void TestFunc1(int a, int b = 10, int c = 20)
{
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}

void test2()
{
	//constexpr�ؼ��֣�c++11������
	//constexpr�ؼ��ֿ�����һ��������ɱ���ʱ����
	constexpr int a = 5;
	int arr[a];
	for (int i = 0; i < a; i++)
	{
		arr[i] = i;
	}
	for (int i = 0; i < a; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int add(int a, int b)
{
	return a + b;
}

//�������Ͳ�ͬ
int add(char a, int b)
{
	return a + b;
}

//����˳��ͬ
int add(int a, char b)
{
	return a + b;
}

//����������ͬ
int add(int a, char b,int c)
{
	return a + b + c;
}

void test3()
{
	//������
	const int a = 10;
	//int& ra = a; // ��������ʱ�����aΪ����
	const int& ra = a;
	// int& b = 10; // ��������ʱ�����bΪ����
	const int& b = 10;
	double d = 12.34;
	//int& rd = d; // ��������ʱ��������Ͳ�ͬ
	const int& rd = d;
}

struct A 
{
	int a[100000]; 
};

void TestFunc1(A a) {}
void TestFunc2(A& a) {}
 
void test4()
{
	A a;
	// ��ֵ��Ϊ��������
	size_t begin1 = clock();
	for (size_t i = 0; i < 1000000; ++i)
		TestFunc1(a);
	size_t end1 = clock();
	// ��������Ϊ��������
	size_t begin2 = clock();
	for (size_t i = 0; i < 1000000; ++i)
		TestFunc2(a);
	size_t end2 = clock();
	// �ֱ���������������н������ʱ��
	cout << "TestFunc1(A)-time:" << end1 - begin1 << endl;		//TestFunc1(A) - time:25487
	cout << "TestFunc2(A&)-time:" << end2 - begin2 << endl;		//TestFunc2(A&) - time:18
}

A a;
// ֵ����
A TestFunc1() { return a; }
// ���÷���
A& TestFunc2() { return a; }

void test5()
{
	// ��ֵ��Ϊ�����ķ���ֵ����
	size_t begin1 = clock();
	for (size_t i = 0; i < 1000000; ++i)
		TestFunc1();
	size_t end1 = clock();
	// ��������Ϊ�����ķ���ֵ����
	size_t begin2 = clock();
	for (size_t i = 0; i < 1000000; ++i)
		TestFunc2();
	size_t end2 = clock();
	// �������������������֮���ʱ��
	cout << "TestFunc1 time:" << end1 - begin1 << endl;		//TestFunc1 time : 49019
	cout << "TestFunc2 time:" << end2 - begin2 << endl;		//TestFunc2 time : 21
}

void test6()
{
	//auto�ؼ�����ָ�����ͺ��������ͽ������ʹ��
	int x = 10;
	auto a = &x;
	auto* b = &x;
	auto& c = x;
	//ָ�벻����auto��auto*����Ϊ�ұ�&ȡ��ַ��
	cout << typeid(a).name() << endl;	//int*
	cout << typeid(b).name() << endl;	//int*
	cout << typeid(c).name() << endl;	//int	��Ϊx��int���͵ģ����������ͺ�ʵ�������һ��
	cout << typeid(x).name() << endl;	//int ʵ��
	*a = 20;
	*b = 30;
	c = 40;
}

void fun(int ptr) 
{
	cout << "fun(int)" << endl;
}

void fun(int* ptr) 
{
	cout << "fun(int*)" << endl;
}

//nullptr
void test7()
{
	bool result1 = nullptr == NULL;  // ���Ϊ 1
	bool result2 = nullptr == 0;     // ���Ϊ 1
	bool result3 = nullptr != NULL;  // ���Ϊ 0
	bool result4 = nullptr != 0;     // ���Ϊ 0
	fun(NULL);			//fun(int)	���滻��Ԥ����NULL�ȼ���0	�ڴ�ͳ��Cͷ�ļ�(stddef.h)��
	fun(nullptr);		//fun(int*)	�ؼ���
	fun((int*)NULL);	//fun(int*)
	fun(0);				//fun(int)
}

int main()
{
	//test1();		//�����ռ�
	//test2();		//constexpr�ؼ��֣�c++11������
	//test3();		//������
	//test4();		//��������ֵ�ʹ�����
	//test5();		//����ֵ��ֵ���غ����÷���
	//test6();		//auto�ؼ���
	//cout << typeid(nullptr).name() << endl;		//std::nullptr_t
	//foo(nullptr);
	//test7();

	return 0;
}