#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//构造函数
void test1()
{
	unordered_map<int, int> m;
	m.insert(make_pair(1, 1));
	m.insert(pair<int, int>(2, 2));
	m[3] = 3;

	for (int i = 4; i < 10; ++i)
	{
		m[i] = i;
	}

	for (const auto& e : m)
		cout << e.first << " " << e.second << endl;
	
	//只有正向迭代器，没有反向迭代器
	//迭代器遍历是无序的
	//时间复杂度是O(1)
	//遍历的顺序和插入的顺序无关
	unordered_map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << (*it).first << " " << (*it).second << endl;
		it++;
	}

	//查找数据为3的一个区间，返回迭代器区间
	auto range = m.equal_range(3);
	it = range.first;
	while(it != range.second)
	{
		cout << (*it).first << " ";
		++it;			//3
	}

	unordered_multimap<int, int> mm;		
	mm.insert(make_pair(1, 1));
	mm.insert(make_pair(2, 2));
	mm.insert(make_pair(3, 3));
	mm.insert(make_pair(3, 3));
	mm.insert(make_pair(3, 3));
	mm.insert(make_pair(3, 3));
	mm.insert(make_pair(4, 4));
	mm.insert(make_pair(5, 5));
	auto range1 = mm.equal_range(3);
	it = range1.first;
	while (it != range1.second)
	{
		cout << (*it).first << " ";
		++it;			//3
	}
}

//迭代器
//哈希结构的容器没有反向的迭代器
void test2()
{

}

void test3()
{

}

int main()
{
	test1();
	test2();
	test3();
	return 0;
}