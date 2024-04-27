#include <iostream>
#include <algorithm>	
#include <vector>
#include <functional>	//功能说明，比较操作需要包含的头文件（不包含好像也可以使用）

using namespace std;

void test()
{
	//默认是一个堆，最后给堆里面的数据做一个排序
	//partial_sort：第一个参数和第二个参数确定有序的个数，第三个参数的迭代器不能在第二个参数的迭代器的前面，第四个参数是比较规则，默认是按照小于比较的（增序）

	//局限性：容器的迭代器必须支持随机访问，迭代器可以进行位置的跳跃
	//比如：哈希表的迭代器（只能往后走）不能使用，还有红黑树的迭代器（不能发生跳跃，只能一个一个的进行移动）不能用，还有list的迭代器不能用（只能前后走，不能跳跃）

	vector<int> v1 = { 12,13,1,5,9,23,16 };
	partial_sort(v1.begin(), v1.begin() + 4, v1.end());		//1 5 9 12 ...
	for (auto& e : v1)
		cout << e << " ";	//1 5 9 12 13 23 16	前4个数据是递增的，剩下的数据是无序的
	cout << endl;

	//greater是按照大于进行比较的（降序），less是按照小于进行比较的（增序）。
	vector<int> v2 = { 12,13,1,5,9,23,16 };
	partial_sort(v2.begin(), v2.end(), v2.end(),greater<int>());		
	for (auto& e : v2)
		cout << e << " ";		//23 16 13 12 9 5 1
	cout << endl;

}

int main()
{
	test();
	return 0;
}