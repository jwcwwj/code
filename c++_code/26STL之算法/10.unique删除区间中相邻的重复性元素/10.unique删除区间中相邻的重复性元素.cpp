#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//unique��ȥ��
//ǰ�᣺Ԫ�ر���Ҫ����
//ȥ�صĽӿڲ���ɾ���κ�һ��Ԫ��
//����ֵ��ȥ��֮��ĵ�һ���ظ�Ԫ�ص�λ�ã����һ����Чλ�õ���һ��λ�ã�
//1 2 3 4 5 2 3 3 5		����ȥ��֮������У�����ֵ���ǵڶ���2��λ��
//����ɾ��Ԫ�أ��ҵ��ظ���ֹͣ������һ�����ظ���ֵ���и���Ԫ�ء���Ԫ�صĸ����ǲ����ģ���ЧԪ�صĸ����ǲ��ظ��ĸ�����
void test()
{
	vector<int> v1 = { 12,12,13,1,5,9,12,23,16,23 };
	sort(v1.begin(), v1.end());		//sort�޷���ֵ

	for (auto& e : v1)
		cout << e << " ";	//1 5 9 12 12 12 13 16 23 23
	cout << endl;

	auto it = unique(v1.begin(), v1.end());
	for (auto& e : v1)
		cout << e << " ";	//1 5 9 12 13 16 23 16 23 23
	cout << endl;
	cout << *it << endl;	//16

	//����ȥ�غ����ЧԪ�ص�λ��
	for (vector<int>::iterator rit = v1.begin(); rit != it; rit++)
	{
		cout << *rit << " ";		//1 5 9 12 13 16 23
	}
	cout << endl;

	//ֻ������Ч�����Ԫ�أ�ɾ����Ч��������Ԫ��
	v1.erase(it, v1.end());
	for (auto& e : v1)
		cout << e << " ";	//1 5 9 12 13 16 23
	cout << endl;

}

int main()
{
	test();
	return 0;
}