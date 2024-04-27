#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

struct A
{
public:
	A(int age = 1,int id = 1,string name = " ")
		:_age(age)
		,_id(id)
		,_name(name)
	{}

	bool operator<(const A&	a)
	{
		//operator��д�����������{}
		return _age < a._age;
	}

	int _age;
	int _id;
	string _name;
};

class Less
{
public:
	bool operator()(const A& a, const A& b)
	{
		return a._id > b._id;
	}
};

void test1()
{
	int array[] = { 4,1,8,5,3,7,0,9,2,6 };
	// Ĭ�ϰ���С�ڱȽϣ��ų������������
	std::sort(array, array + sizeof(array) / sizeof(array[0]));
	// �����Ҫ������Ҫ�ı�Ԫ�صıȽϹ���
	std::sort(array, array + sizeof(array) / sizeof(array[0]), greater<int>()); //��������
	greater<int> a;
	std::sort(array, array + sizeof(array) / sizeof(array[0]), a);

	vector<A> vec = { {18,1,"a"},{29,3,"b"},{13,25,"c"} };
	sort(vec.begin(), vec.end());
	sort(vec.begin(), vec.end(), Less());		//��������
	//����ıȽϷ�ʽ���º��������� > ���� <�����������ָ�룬lambda���ʽ
	sort(vec.begin(),vec.end(),
		[](const A& a, const A& b)
	{
		return a._name < b._name;
	});
}

void test2()
{
	//lambda���ʽ��{��׽�б�}(�����б�)(mutable��ѡ)->����ֵ����{������}
	//��׽�б������������еı���
	int a = 10;
	int b = 20;
	[a, b] {return a + b; };
	//�����б������ں����Ĳ����б�
	[a, b](int c, int d, int e) {return a + b + c; };
	//����ֵ�������ں����ķ���ֵ
	[a, b](int c)->int {return a + b + c; };
	//�����壺�����ں����ĺ����壬�����ж��ָ��
	//mutable���޸Ĳ�׽�б��б���������Ϊ��const��Ĭ��Ϊconst����
	//[a, b](int c)->int {a = 10; };	//a,b������Ĭ��Ϊconst���ԣ����ʽ�����ǿ��޸ĵ���ֵ��
	[a, b](int c)mutable->int {a = 10; b = 20;  return a; };
	//�����б�ͷ���ֵ���Ժ���
	[] {};
	//����ֵ����һ�㲻��д�����������Զ��Ƶ�
	[a, b] {return a + b; };
	//�����mutable����ʹ�����б�Ϊ�գ������б�Ҳ��Ҫ��ʾд����
	[a, b]()mutable {return a + b; };
	//[a, b]->int {return a + b; };		//error���˴�������ʹ������
	[a, b]()->int {return a + b; };

	//����д��ȫ����lambda���ʽ�Ķ��壬��û��ʹ�ã�ָ�������
	//����д����lambda���ʽ��ʹ��
	auto f = [a, b](int c) {return a + b + c; };
	cout << typeid(f).name() << endl;//class <lambda_b2e39ab5e00dc83db94af3e20fe2d53e>
	//cout << f << endl;
	int e = f(10);
	
	/*
	typedef int(*ptr1)(int);
	ptr1 fff;
	cout << fff(10) << endl;
	//��������ú���ָ�����auto�أ�
	*/

	cout << e << endl;	//40
	//[=]����ֵ����ʽ��׽���������е����б���
	auto f2 = [=]() {return a + b + e; };
	//[&]�������õ���ʽ��׽���������е����б���
	auto f3 = [&]() {a = 1; b = 1000; };
	f3();	//�޸�a��b��ֵ
	
	//[=,&����x]��x������ʽ��׽����������ֵ����ʽ��׽
	//[&,����x]��xֵ��ʽ��׽�������������õ���ʽ��׽
	//����Ĳ�׽��ʽ��[=,����x]��[&,&����x]
	//[this]����׽��Ա�����е�thisָ��

	int g = 10;
	auto m = [g] {};

	//lambda���ʽ���ܽ��и�ֵ�����Խ��п���
	auto f1 = [](int a) {return a; };
	auto f22 = [](int a) {return a; };
	
	//����ֱ�ӽ��и�ֵ
	//f = f22;		//error
	
	//���Խ��п���
	typedef int(*ptr)(int);
	auto f33 = f1;

	//ptr f4 = f3;	//error�������ڴ�"lambda [void 0->void"��"ptr�����ʵ�ת������
	//���Ը�ֵ������ָ��
	ptr f4 = f1;

}

//int g1 = 10;
//auto m1 = [g1] {};	//error���޷��� lambda �в�����о�̬�洢����ʱ��ı�����ȫ�ֱ�����

struct A1
{
	void fun(int a)
	{
		auto f = [this]() {return this->_a; };
	}

	int _a;
};


//lambda���ʽ�ײ�������ߵģ��ײ�ͨ���º�����ʵ�ֵ�
struct Sum
{
	int operator()(int a, int b)
	{
		return a + b;
	}
};

void test3()
{
	auto f = [](int a, int b) {return a + b; };
	int sum = f(10, 20);
	Sum s;
	s(10, 20);
}

int main()
{
	test1();
	test2();
	test3();
	return 0;
}