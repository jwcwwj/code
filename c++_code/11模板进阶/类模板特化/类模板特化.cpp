#include <iostream>

using namespace std;

//��ģ���ػ���
//Ӧ�ó�����������ȡ
//ǰ�᣺����һ��ͨ�õ�ģ��

template <class T1,class T2>
struct D
{
public:
	D(const T1& d1, const T2& d2)
		:_d1(d1)
		,_d2(d2)
	{
		cout << "D(T1, T2)" << endl;
	}

	T1 _d1;
	T2 _d2;
};

//�ػ���ģ��
//1.ȫ�ػ������е����Ͷ��Ǿ������ͣ�û�����͵�����
template<>
struct D<char, double>
{
	D(const char& d1, const double& d2)
		:_d1(d1)
		, _d2(d2)
	{
		cout << "D(char, double)" << endl;
	}

	char _d1;
	double _d2;
};

//ȫ�ػ�
void test1()
{
	D<int, int> d1(1,1);			//ͨ��ģ���ʵ����
	//�����D(T1, T2)
	D<char, double> d2('a', 1.1);	//ȫ�ػ��汾��ʵ����
	//�����D(char, double)
}

//2.1ƫ�ػ���ֻ�ػ���������
template <class T1>
struct D<T1, char>
{
	D(const T1& d1, const char& d2)
		:_d1(d1)
		, _d2(d2)
	{
		cout << "D(T1, char)" << endl;
	}

	T1 _d1;
	char _d2;
};

//ƫ�ػ�
void test2()
{
	D<int, char> d3(1, 'a');	//ƫ�ػ��汾��ʵ����
	//�����D(T1, char)
}

//2.2ƫ�ػ���ģ���������һ��������
template <class T1, class T2>
struct D<T1*,T2*>
{
public:
	D(const T1& d1, const T2& d2)
		:_d1(d1)
		, _d2(d2)
	{
		cout << "D(T1*, T2*)" << endl;
	}

	T1 _d1;
	T2 _d2;
};

//2.2ƫ�ػ���ģ���������һ��������
void test3()
{
	D<int*, int*> d4(1, 2);
	//�����D(T1*, T2*)
}

int main()
{
	//test1();		//ȫ�ػ�
	//test2();		//ƫ�ػ�
	test3();		//ƫ�ػ���ģ���������һ��������
	return 0;
}