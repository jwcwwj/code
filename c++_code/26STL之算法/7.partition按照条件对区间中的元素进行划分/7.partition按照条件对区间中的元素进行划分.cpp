#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//�ж��ǲ�������
bool isOdd(int a)
{
	return a % 2 == 1;
}

void test()
{
	vector<int> v1 = { 12,13,1,5,9,23,16 };
	partition(v1.begin(), v1.end(), isOdd);		//��ǰ��ż�����Ӻ������������ҵ���ż�����ҵ����������н���
	//����ֵ�����㱻���ֺ����������һ��λ�ã���������
	for (const auto& e : v1)
		cout << e << " ";		//23 13 1 5 9 12 16	����ֵ����12��λ��
	cout << endl;
}

int main()
{
	test();
	return 0;
}