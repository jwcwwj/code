#include <iostream>
#include <list>
#include <vector>
#include <algorithm>	//使用merge要包含的头文件

using namespace std;

//将两个有序序列合并成一个有序序列
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