#include <iostream>
#include <numeric>		//数值头文件	累加需要包含的头文件
#include <vector>

using namespace std;

//accumulate：该算法作用是对区间中的元素进行累加
struct Mul2
{
	//x = Mul2(x,y);
	int operator()(int x, int y) { return x + 2 * y; }		//x是累加的值，y是新的要加的值
};

void test()
{
	// 对区间中的元素进行累加
	vector<int> v{ 10, 20, 30 };
	cout << accumulate(v.begin(), v.end(), 0) << endl;	//60
	// 对区间中的每个元素乘2，然后累加
	cout << accumulate(v.begin(), v.end(), 0, Mul2()) << endl;	//120
	cout << accumulate(v.begin(), v.end(), 50, Mul2()) << endl;	//170
}

int main()
{
	test();
	return 0;
}

//1.STL算法代码敲完		8
//2.STL算法md文档		3
//3.STL总结md文档		11
//4.网站整理			12