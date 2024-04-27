#include <iostream>
#include <map>
#include <string>

using namespace std;

//正向迭代器遍历
template <class T1,class T2>
void printMap(const map<T1, T2>& m)
{
	//map中的数据是pair 
	typename map<T1,T2>::const_iterator it = m.begin();
	while (it != m.end())
	{
		cout << (*it).first << " " << it->second << endl;
		it++;
	}
}

//反向迭代器遍历
template <class T1, class T2>
void printMapr(const map<T1, T2>& m)
{
	//map中的数据是pair 
	typename map<T1, T2>::const_reverse_iterator it = m.rbegin();
	while (it != m.rend())
	{
		cout << (*it).first << " " << it->second << endl;
		it++;
	}
}

//构造函数
void test1()
{
	map<int, int> m1;
	
	//匿名对象初始化
	pair<int, int> arr[] = { pair<int, int>(5,5),pair<int, int>(1,2),
	pair<int, int>(3,3),pair<int, int>(0,0),pair<int, int>(1,3) };
	map<int, int> m2(arr, arr + sizeof(arr) / sizeof(arr[0]));
	for (const auto& e : m2)
		cout << e.first << " " << e.second << endl;
	printMap(m2);		//正向迭代器遍历
	//输出：
	//0 0
	//1 2
	//3 3
	//5 5
	//0 0
	//1 2
	//3 3
	//5 5

	printMapr(m2);		//反向迭代器遍历
	//输出：
	//5 5
	//3 3
	//1 2
	//0 0

	//遍历顺序：按照key值从小到大遍历（底层是二叉搜索树，按照中序遍历进行遍历）
	//map中不能存放相同的key值，value值可以相同
	//map中不能修改key，可以修改value

	map<int, int, greater<int>> m3(arr, arr + sizeof(arr) / sizeof(arr[0]));
	for (const auto& e : m3)
		cout << e.first << " " << e.second << endl;
	//输出：	由大到小输出
	//5 5
	//3 3
	//1 2
	//0 0

	const auto& it = m3.begin();
	it->second = 10;	//value可以修改
	//it->first = 20;	//key不能修改

	//拷贝构造
	map<int, int> m4(m2);	
}

//访问：at、[]
void test2()
{
	//[]
	map<int, int> m;
	//访问（读）    修改（写）	  插入	
	m[4] = 10;	//相当于创建一个pair<int,int>(4,10)的对象进行插入
	cout << m[5] << endl;//输出：0（不指定value，默认是0）
	//相当于创建一个pair<int,int>(5,0)的对象进行插入
	
	for (const auto& e : m)
		cout << e.first << " " << e.second << endl;
	//输出：
	//4 10
	//5 0

	m[5] = 20;	//修改	m[5]的返回值是value&，直接修改vaule本身为20
	for (const auto& e : m)
		cout << e.first << " " << e.second << endl;
	//输出：
	//4 10
	//5 20

	//解释：
	//operator[](k)	等价于
	//(*( (this->insert(	make_pair(k,mapped_type()) ) ).first )).second	 
	//insert的返回值：pair<iterator,bool>	
	//*iterator：pair<int,int>
	
	//operator[](k)
	//1.创建一个pair对象，内容是：k	value（value缺省值是类0值）
	//2.插入第一步创建的pair对象
	//	2.1插入成功：返回pair<pair对象的迭代器,true>
	//	2.2插入失败：返回pair<已经存在的键值为k的pair对象的迭代器,false>
	//3.获取插入返回值的first成员：是一个map中的pair对象的迭代器
	//4.解引用第3步中的迭代器，拿到map中的pair对象
	//5.从第4步获得的map中的pair对象的value
	//	5.1如果插入成功，value是缺省值（插入）
	//	5.2如果插入失败，就是对应的key的value

	//at
	//at越界访问会抛异常
	cout << m.at(5) << endl;	//20
	//
	cout << m.at(6) << endl;	//不存在的key不会插入并且输出value，会抛异常

	//总结：一般使用，不使用at
}

//插入
void test3()
{
	map<int, int> m;

	//错误的插入方式：
	//auto ret = m.insert（1, 1）;	//error

	//正确的插入方式：
	//1.调用pair构造函数创建对象
	auto ret = m.insert(pair<int, int>(1, 1));
	//2.调用make_pair函数创建对象
	ret = m.insert(make_pair(2, 3));
	cout << ret.first->first << endl;	//2
	cout << ret.second << endl;		//1		表示插入成功了
	//第一个first是迭代器，第二个first是key
}

void test4()
{

}

void test5()
{

}

void test6()
{

}

int main()
{
	//test1();
	//test2();
	test3();
	test4();
	test5();
	test6();
	return 0;
}