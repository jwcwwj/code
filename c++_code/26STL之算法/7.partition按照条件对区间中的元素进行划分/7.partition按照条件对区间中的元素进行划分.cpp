#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//判断是不是奇数
bool isOdd(int a)
{
	return a % 2 == 1;
}

void test()
{
	vector<int> v1 = { 12,13,1,5,9,23,16 };
	partition(v1.begin(), v1.end(), isOdd);		//从前找偶数，从后找奇数，将找到的偶数和找到的奇数进行交换
	//返回值：满足被划分后的条件的下一个位置（迭代器）
	for (const auto& e : v1)
		cout << e << " ";		//23 13 1 5 9 12 16	返回值就是12的位置
	cout << endl;
}

int main()
{
	test();
	return 0;
}