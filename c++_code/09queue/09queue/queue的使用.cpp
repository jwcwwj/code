#include <iostream>
#include <queue>

using namespace std;

void test()
{
	queue<int> q;
	for (int i = 0; i < 5; ++i)
		//队尾元素入队
		q.push(i);

	while (!q.empty())
	{
		//获取队头元素
		cout << q.front() << " ";		//0 1 2 3 4
		q.pop();		//队头元素出队
	}
	cout << endl;
}

int main()
{
	test();
	return 0;
}