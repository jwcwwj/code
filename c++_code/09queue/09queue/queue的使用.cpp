#include <iostream>
#include <queue>

using namespace std;

void test()
{
	queue<int> q;
	for (int i = 0; i < 5; ++i)
		//��βԪ�����
		q.push(i);

	while (!q.empty())
	{
		//��ȡ��ͷԪ��
		cout << q.front() << " ";		//0 1 2 3 4
		q.pop();		//��ͷԪ�س���
	}
	cout << endl;
}

int main()
{
	test();
	return 0;
}