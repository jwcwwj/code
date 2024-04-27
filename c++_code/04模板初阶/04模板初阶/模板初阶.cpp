#include <iostream>

using namespace std;

/* 
//��ʽʵ����
template<typename T>
void my_swap(T& a, T& b)
{
	T temp = a;		//���ﲻ��ʹ�����ã�ʹ������֮��ı�temp��ֵ���Ǹı�a��ֵ
	a = b;
	b = temp;
}

void test1()
{
	int a = 10;
	int b = 20;
	my_swap(a, b);
	cout << a << endl;	//20
	cout << b << endl;	//10
	double a1 = 1.2;
	double b1 = 2.3;
	my_swap(a1, b1);
	cout << a1 << endl;	//2.3
	cout << b1 << endl;	//1.2

	//my_swap(a, a1);	//error������û��������б�ƥ��ĺ���ģ��"my_swap��ʵ����������Ϊ:(int, double)
	//������䲻��ͨ�����룬��Ϊ�ڱ����ڼ䣬��������������ʵ����ʱ����Ҫ������ʵ�����ͣ�
	//ͨ��ʵ��a��T����Ϊint��ͨ��ʵ��a1��T����Ϊdouble���ͣ���ģ������б���ֻ��һ��T��
	//�������޷�ȷ���˴����׸ý�Tȷ��Ϊint ���� double���Ͷ�����
	//ע�⣺��ģ���У�������һ�㲻���������ת������
}
*/

/* 
//��ʽʵ����������һ��������
template<typename T>
T my_add(T a, T b)			//�����ββ���������
{
	return a + b;
}

void test2()
{
	int a = 10;
	int b = 20;
	double a1 = 1.2;
	double b1 = 2.3;
		
	//my_add(a, a1);	//error������û��������б�ƥ��ĺ���ģ��"my_swap��ʵ����������Ϊ:(int, double)
	//���������
	//1.�û��Լ���ǿ��ת��
	cout << my_add(a, (int)a1) << endl;		//11,doubleתint�������ݶ�ʧ
	//2.ʹ����ʾʵ����
	cout << my_add<int>(a, a1) << endl;		//11
}
*/

/*
template<typename T>
T max(T a, T b)
{
	std::cout << "max(T, T) called." << std::endl;
	return (a > b) ? a : b;
}

template<typename T1, typename T2>
auto max(T1 a, T2 b) -> decltype((a > b) ? a : b)
{
	std::cout << "max(T1, T2) called." << std::endl;
	return (a > b) ? a : b;
}

void test3()
{
	int i = 10;
	double d = 3.14;

	std::cout << "max(i, d) = " << max(i, d) << std::endl; // �Զ�����ת������� 10
	std::cout << "max(d, i) = " << max(d, i) << std::endl; // �Զ�����ת������� 10
}
*/

//��ģ��
//��̬˳���
//ע�⣺Vector���Ǿ�����࣬�Ǳ��������ݱ�ʵ�������������ɾ������ģ��
template<class T>
class Vector
{
public:
	Vector(size_t capacity = 10)
		: _pData(new T[capacity])
		, _size(0)
		, _capacity(capacity)
	{}
	// ʹ������������ʾ�������������������ⶨ�塣
	~Vector();
	void PushBack(const T& data)��
		void PopBack()��
		// ...
		size_t Size() { return _size; }
	T& operator[](size_t pos)
	{
		assert(pos < _size);
		return _pData[pos];
	}
private:
	T* _pData;
	size_t _size;
	size_t _capacity;
};
// ע�⣺��ģ���к�������������ж���ʱ����Ҫ��ģ������б�
template <class T>
Vector<T>::~Vector()
{
	if (_pData)
		delete[] _pData;
	_size = _capacity = 0;
}

void test4()
{
	// Vector������Vector<int>��������
	Vector<int> s1(10);
	Vector<double> s2;
}

int main()
{
	//test1();		//��ʽʵ����
	//test2();		//��ʽʵ����������һ��������
	//test3();
	test4();
	return 0;
}