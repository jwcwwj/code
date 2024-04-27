#include <iostream>
#include <algorithm>		//count与count_if需要的头文件
#include <vector>

using namespace std;

//count与count_if：该算法的作用是统计区间中某个元素出现的次数
//函数统计奇数的个数
bool IsOdd(int i)
{
	return ((i % 2) == 1);
}

//仿函数统计偶数的个数
struct Iso
{
	bool operator()(int i)
	{
		return i % 2 == 0;
	}
};

void test()
{
	// 统计10在v1中出现的次数
	vector<int> v1{ 10, 20, 30, 30, 20, 10, 10, 20 };
	cout << count(v1.begin(), v1.end(), 10) << endl;		//3
	// 统计v2中有多少个偶数
	vector<int> v2{ 0,1,2,3,4,5,6,7,8,9,10 };
	cout << count_if(v2.begin(), v2.end(), IsOdd) << endl;		//5
	cout << count_if(v2.begin(), v2.end(), Iso()) << endl;		//6
}

int main()
{
	test();
	return 0;
}