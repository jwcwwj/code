#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <utility>

using namespace std;

struct A
{
public:
	explicit A(int a = 10)
		:_a(a)
	{}

	A(int a,int b,int c)
		:_a(a)
	{}

	int _a;
};

template <class T>
class Vector
{
public:
	Vector(size_t n)
		: _arr(new T[n])
		, _size(0)
		, _capacity(n)
	{}

	/*
	//������
	Vector(size_t n,size_t n2.size_t n3)
		: _arr(new T[n])
		, _size(0)
		, _capacity(n)
	{}
	*/

	Vector(const initializer_list<T>& lst)		//�������������ʼ���б�
		:_arr(new T(lst.size()))
		, _size(lst.size())
		, _capacity(_size)
	{
		int idx = 0;
		for (const auto& e : lst)
			_arr[idx++] = e;
	}

private:
	T* _arr;
	size_t _size;
	size_t _capacity;
};

//��ʼ���б�
void test1()
{
	int a = 100;
	A a1(100);
	//A a2 = 100;		//���ι������ʽ����ת��(����explicit�Ͳ���ʹ�õ��ι�����)

	int arr[] = { 1,2,3,4 };

	//c++11��֧���������ͺ��Զ������͵��б��ʼ��
	//���������б��ʼ��
	int b = { 10 };
	int c{ 100 };

	//�Զ�������
	//A a3 = { 1 };		//���ι������ʽ����ת��
	A a4{ 5 };

	A a5 = { 1,2,3 };	//c++11֧�ֶ�ι������ʽ����ת��
	A a6{ 4,5,6 };

	vector<int> v = { 1,2,3,4,5 };
	for (auto& e : v)
		cout << e << " ";
	cout << endl;

	list<int> l = { 1,2,3,4,5 };
	set<int> s = { 3,4,5,2,1,4,2 };		//�����ȥ�ص�
	map<int, int> m = { {1,2},{2,3} };		//�ȳ�ʼ��pair��������pair�����ʼ��map����
	
	pair<int, int> p = { 1,3 };		//�б��ʼ����ʼpair���͵Ķ���
	map<int, int> m1 = { p };

	//�Զ���������࣬�����Ҫʵ�ֳ�ʼ���б���г�ʼ������Ҫ����һ�����캯����
	//����Ϊ��ʼ���б�initializer_list��	ֻ��begin��end��size�ӿ�
	Vector<int> v2 = { 1,2,3 };		//�Լ�����������м�initializer_list<T> 
	Vector<int> v3 = { 1 };
}

int fun(int a)
{
	return a;
}

//�����Ƶ�
void test2()
{
	auto a = 10;
	int b = 1;
	int c = 2;
	decltype(b + c) d;		//�Ƶ�d
	cout << typeid(d).name() << endl;	//int
	cout << typeid(decltype(fun(a))).name() << endl;	//int	����ֵ������
	cout << typeid(decltype(fun)).name() << endl;		//int __cdecl(int)	����ָ�������
}

class A1
{
public:
	A1(int a)
	{}

	A1() = default;		//�ñ�������ʾ����һ���޲εĹ��캯����Ĭ�ϵĹ��캯����

	A1(const A1&) = default;

	A1& operator=(const A1&) = default;
};

class B
{
public:
	B()
	{}

	B(const	B&) = delete;	//����delete��ʾ���Ѿ�ɾ���ĺ���

	B& operator=(const B&) = delete;

	void func() = delete;		//deleteֻ����ɾ����ʱ��ʹ��
};

void fun1() = delete;

//Ĭ�ϳ�Ա��������
void test3()
{
	//1.default������default��ʾ��Ĭ�ϵĺ���
	//û��̫���ʵ���ô������� �ñ�������ʾ����һ���޲εĹ��캯����

	//2.delete������delete��ʾ���Ѿ�ɾ���ĺ���
	B b;
	//B copy(b);		//����ʹ���ˣ���ֹ������
	//b.func();			//����ʹ����
	//fun1();			//����ʹ����

	//deleteֻ���������������У��������ں���������
	//delete�����ڳ�Ա�����ͷǳ�Ա�����ж�����ʹ��
}

//������ֵ�c++11���﷨���ǿ��п��޵�
 
int main()
{
	//test1();
	//test2();
	test3();
	return 0;
}