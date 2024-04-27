#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
	vector<int> v1{ 10, 20, 30, 30, 20, 10, 10, 20 };
	//����һ�����ڵ�����
	vector<int>::iterator it = find(v1.begin(), v1.end(), 30);		//��ʼ�ͽ����ĵ����������ǿ��Ե�����
	if (it != v1.end())
	{
		cout << *it << endl;			//30
	}
	//����һ�������ڵ�����
	it = find(v1.begin(), v1.end(), 100);
	if (it != v1.end())
	{
		cout << *it << endl;			
	}
	else
	{
		cout << "v1�в�����100�������" << endl;
	}


	vector<int> v2{ 0,1,2,3,4,5,6,7,8,9,10 };

	//�ҵ�һ������
	it = find_if(v2.begin(), v2.end(), IsOdd);		 	
	cout << *it << endl;		//1

	//�ҵ�һ��ż��
	it = find_if(v2.begin(), v2.end(), Iso());		 
	cout << *it << endl;	//0
}

int main()
{
	test();
	return 0;
}