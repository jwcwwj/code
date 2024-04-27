#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
	vector<int> v1{ 10, 20, 30, 30, 20, 10, 10, 20 };
	//查找一个存在的数据
	vector<int>::iterator it = find(v1.begin(), v1.end(), 30);		//开始和结束的迭代器区间是可以调整的
	if (it != v1.end())
	{
		cout << *it << endl;			//30
	}
	//查找一个不存在的数据
	it = find(v1.begin(), v1.end(), 100);
	if (it != v1.end())
	{
		cout << *it << endl;			
	}
	else
	{
		cout << "v1中不存在100这个数据" << endl;
	}


	vector<int> v2{ 0,1,2,3,4,5,6,7,8,9,10 };

	//找第一个奇数
	it = find_if(v2.begin(), v2.end(), IsOdd);		 	
	cout << *it << endl;		//1

	//找第一个偶数
	it = find_if(v2.begin(), v2.end(), Iso());		 
	cout << *it << endl;	//0
}

int main()
{
	test();
	return 0;
}