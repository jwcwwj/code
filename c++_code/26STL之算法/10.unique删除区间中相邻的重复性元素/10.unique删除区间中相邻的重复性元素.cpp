#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//unique：去重
//前提：元素必须要有序
//去重的接口不会删除任何一个元素
//返回值：去重之后的第一个重复元素的位置（最后一个有效位置的下一个位置）
//1 2 3 4 5 2 3 3 5		这是去重之后的序列，返回值就是第二个2的位置
//不会删除元素，找到重复的停止，再找一个不重复的值进行覆盖元素。（元素的个数是不会变的，有效元素的个数是不重复的个数）
void test()
{
	vector<int> v1 = { 12,12,13,1,5,9,12,23,16,23 };
	sort(v1.begin(), v1.end());		//sort无返回值

	for (auto& e : v1)
		cout << e << " ";	//1 5 9 12 12 12 13 16 23 23
	cout << endl;

	auto it = unique(v1.begin(), v1.end());
	for (auto& e : v1)
		cout << e << " ";	//1 5 9 12 13 16 23 16 23 23
	cout << endl;
	cout << *it << endl;	//16

	//遍历去重后的有效元素的位置
	for (vector<int>::iterator rit = v1.begin(); rit != it; rit++)
	{
		cout << *rit << " ";		//1 5 9 12 13 16 23
	}
	cout << endl;

	//只保留有效区间的元素，删除有效区间后面的元素
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