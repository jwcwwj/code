#include <iostream>
#include <list>
#include <vector>
#include <algorithm>	//ʹ��mergeҪ������ͷ�ļ�

using namespace std;

//�������������кϲ���һ����������
void test()
{
	vector<int> v1 = { 1,2,3 };
	list<int> v2 = { 4,5,6 };
	vector<int> v3(v1.size() + v2.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(),v3.begin());
	for (auto& e : v3)
		cout << e << " ";	//1 2 3 4 5 6
	cout << endl;
}

int main()
{
	test();
	return 0;
}