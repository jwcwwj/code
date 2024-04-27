#include <iostream>
#include <algorithm>		//count��count_if��Ҫ��ͷ�ļ�
#include <vector>

using namespace std;

//count��count_if�����㷨��������ͳ��������ĳ��Ԫ�س��ֵĴ���
//����ͳ�������ĸ���
bool IsOdd(int i)
{
	return ((i % 2) == 1);
}

//�º���ͳ��ż���ĸ���
struct Iso
{
	bool operator()(int i)
	{
		return i % 2 == 0;
	}
};

void test()
{
	// ͳ��10��v1�г��ֵĴ���
	vector<int> v1{ 10, 20, 30, 30, 20, 10, 10, 20 };
	cout << count(v1.begin(), v1.end(), 10) << endl;		//3
	// ͳ��v2���ж��ٸ�ż��
	vector<int> v2{ 0,1,2,3,4,5,6,7,8,9,10 };
	cout << count_if(v2.begin(), v2.end(), IsOdd) << endl;		//5
	cout << count_if(v2.begin(), v2.end(), Iso()) << endl;		//6
}

int main()
{
	test();
	return 0;
}