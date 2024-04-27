#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//排列组合：
//前提：有序序列
//next_permutation是正向的排列组合	pre_permutation是反向的排列组合
void test()
{
	// 因为next_permutation函数是按照大于字典序获取下一个排列组合的
	// 因此在排序时必须保证序列是升序的
	vector<int> v = { 4, 1, 2, 3 };
	sort(v.begin(), v.end());
	
	//正向的排列组合
	do
	{
		cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << endl;
	} while (next_permutation(v.begin(), v.end()));
	cout << endl << endl << endl;

	// 因为prev_permutation函数是按照小于字典序获取下一个排列组合的
	// 因此在排序时必须保证序列是降序的
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