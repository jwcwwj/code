#include <iostream>
#include <array>			//��̬������

using namespace std;

//template <class T,double num>		//��������ģ������ǷǱ�׼��
//struct A
//{};

struct B
{};

//template <class T,B obj>		 //����������ģ�����������Ϊ������
//struct C
//{};

template <class T,char ch>
struct D
{};

void test()
{
	//array<T,size_t>		size_t�Ƿ�����ģ�����
	array<int, 10> arr;			//��̬���飬�ȼ���int arr[10]
	//������ģ�����ֻ�����������ͣ����ܸ������������Զ�����������
	B b;
	//C<int,b> c;		//�������ʽ���뺬�г���ֵ
	D<float, 'a'> d;
}

int main()
{
	test();
	return 0;
}