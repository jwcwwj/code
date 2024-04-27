#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//������ϣ�
//ǰ�᣺��������
//next_permutation��������������	pre_permutation�Ƿ�����������
void test()
{
	// ��Ϊnext_permutation�����ǰ��մ����ֵ����ȡ��һ��������ϵ�
	// ���������ʱ���뱣֤�����������
	vector<int> v = { 4, 1, 2, 3 };
	sort(v.begin(), v.end());
	
	//������������
	do
	{
		cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << endl;
	} while (next_permutation(v.begin(), v.end()));
	cout << endl << endl << endl;

	// ��Ϊprev_permutation�����ǰ���С���ֵ����ȡ��һ��������ϵ�
	// ���������ʱ���뱣֤�����ǽ����
	//sort(v.begin(), v.end());
	
	sort(v.begin(), v.end(), greater<int>());
	
	do
	{
		cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << endl;
	} while (prev_permutation(v.begin(), v.end()));
}

int main()
{
	test();
	return 0;
}