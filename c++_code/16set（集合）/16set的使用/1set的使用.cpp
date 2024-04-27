#include <iostream>
#include <string>
#include <set>

using namespace std;

//构造函数
void test1()
{
	//1.无参构造
	set<int> s1;

	//区间构造
	int arr[] = { 5,3,1,4,4 };
	set<int> s2(arr, arr + sizeof(arr) / sizeof(arr[0]));	//4是重复的，只会存储一个4

	for (const auto ch : s2)
		cout << ch << " ";		//1 3 4 5 迭代器遍历数据天然有序的，set迭代器是按中序遍历的
	cout << endl;

	for (set<int>::iterator it = s2.begin(); it != s2.end(); it++)
	{
		cout << *it << " ";		//1 3 4 5	 
		//*it = 10;	//set迭代器不支持修改，原因：set的底层是二叉搜索树，修改了会破坏二叉搜索树的结构
	}
	cout << endl;

	cout << "reverse iterator:";
	set<int>::reverse_iterator rit = s2.rbegin();
	while(rit != s2.rend())
	{
		cout << *rit << " ";	//5 4 3 1
		++rit;
	}
	cout << endl;

	//拷贝构造
	set<int> s3(s2);
	for (auto ch : s3)
		cout << ch << " ";	//1 3 4 5
	cout << endl;
}

//容量操作	size	max_size	empty 
void test2()
{
	int arr[] = { 5,3,1,4,4 };
	set<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));	//4是重复的，只会存储一个4

	if (!s.empty())
		cout << s.size() << endl;		//4
	else
		cout << "s集合为空" << endl;

	cout << "int类型的集合最大存储容量" << s.max_size() << endl;	//int类型的集合最大存储容量214748364
}

template <class T>
void printSet(const set<T>& s)
{
	for (auto& e : s)
		cout << e << " ";
	cout << endl;
}

//插入
void test3()
{
	//插入：
	//1.函数原型pair<iterator, bool> insert(const value_type& x)	最常用的
	//返回值：pair<iterator, bool>	iterator是插入的迭代器的位置，bool是插入成功（true）或者失败（false）
	//set中不能有重复的数据，set中没有要插入的数据寻找合适的位置进行插入，返回true；
	//set中有要插入的数据，插入失败，返回false。
	//插入失败也会返回迭代器的位置，就是和插入失败的数据（值）相等的元素位置
	//插入成功了就是返回插入的新的数据的位置
	int arr[] = { 5,3,1,4,10 };
	set<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));	
	
	auto ret = s.insert(10);	//简写，auto进行推断
	cout << ret.second << endl;	//0(false)	表示插入失败

	pair<set<int>::iterator, bool> ret1 = s.insert(10);
	//解引用插入的迭代器位置就是插入的数据
	cout << *ret1.first << endl;		//10	插入失败就是之前已经存在的数据

	ret1 = s.insert(20);
	cout << *ret1.first << endl;		//20	插入成功就是新插入数据的位置 
	cout << ret1.second << endl;		//1(true)	表示插入成功
	//插入失败：已有数据的迭代器，false
	//插入成功：新插入数据的迭代器，true


	//2.函数原型：iterator insert(iterator position,const value_type& val);
	//第一个参数只是一个建议，因为二叉搜索树的性质，只是将插入的数据靠近给定的迭代器的位置
	//线性容器一般表示在这个迭代器的前面插入一个数据
	//set插入完成后要满足二叉搜索树的性质
	s.insert(ret.first, 100);
	printSet(s);		//1 3 4 5 10 20 100
	//insert(iterator,val);		iterator只是一个位置建议，最终数据的位置不一定在指定迭代器之前

	//3.插入一个区间
	//函数原型：
	//template<class InputIterator>	
	//void insert(InputIterator first,InputIterator last);

	int arr2[] = { 5,12,17,13,25,20,18,12 };
	s.insert(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
	printSet(s);	//1 3 4 5 10 12 13 17 18 20 25 100
}

//删除
void test4()
{
	int arr[] = { 17,20,12,17,13,25,5,18,12 };
	set<int> s;
	s.insert(arr, arr + sizeof(arr) / sizeof(arr[0]));
	printSet(s);	//5 12 13 17 18 20 25

	//删除
	//1.按值删除
	//函数原型：size_type erase erase(const value_type& val);
	//返回值：删除的数据个数	只能是1或者0，因为元素不重复	(size_type是内部的数据，外部接收返回值用整形类型接收)
	int size = s.erase(18);
	printSet(s);	//5 12 13 17 20 25
	cout << size << endl;	//1	数据存在，删除成功

	size = s.erase(1000);
	cout << size << endl;	//0	数据不存在，删除失败

	//2.按迭代器位置删除
	//函数原型：void erase(iterator position);
	//删除是按二叉搜索树有序遍历的位置删除的，不是按插入的位置删除的
	s.erase(s.begin());	//左闭右开的区间，不要删除end迭代器位置（会报错，越界），包括begin，不包括end
	printSet(s);		//12 13 17 20 25		删除的不是第一个插入的元素，是最小的元素

	//3.按迭代器区间删除
	//无返回值
	s.erase(++s.begin(), --s.end());
	printSet(s);		//12 25
}

//swap：浅拷贝，只会交换根节点的指向  clear   
void test5()
{
	int arr1[] = { 5,3,2,6,4 };
	int arr2[] = { 8,7,9,6,4 };
	set<int> s1(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
	set<int> s2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));

	cout << "交换前：" << endl;
	cout << "s1:";
	printSet(s1);
	cout << "s2:";
	printSet(s2);
	//交换前：
	//s1: 2 3 4 5 6
	//s2: 4 6 7 8 9

	s1.swap(s2);

	cout << "交换后：" << endl;
	cout << "s1:";
	printSet(s1);
	cout << "s2:";
	printSet(s2);
	//交换后：
	//s1 : 4 6 7 8 9
	//s2 : 2 3 4 5 6

	cout << s1.size() << endl;		//5
	s1.clear();
	cout << s1.size() << endl;		//0
}

//emplace：构造并且插入数据（和insert的区别是insert的数据必须先创建好，emplace不用）
struct Person
{
	std::string name;
	int age;

	Person(const std::string& n, int a)
		: name(n)
		, age(a)
	{}

	//指定比较规则
	//这里必须使用两个const进行修饰参数
	//否则会报错：二进制"<":没有找到接受" const_Ty"类型的左操作数的运算符(或没有可接受的转换)
	bool operator<(const Person& other) const
	{
		return age < other.age;
	}
};

void test6()
{
	set<Person> people;

	//使用emplace直接构造并插入元素
	people.emplace("Alice", 25);
	people.emplace("Bob", 30);
	people.emplace("Charlie", 20);

	//遍历打印set中的元素
	for (const auto& person : people)
	{
		std::cout << person.name << " - " << person.age << std::endl;
	}
	//输出：
	//Charlie - 20
	//Alice - 25
	//Bob - 30
}

//find	count
void test7()
{
	set<int> s;
	s.insert(20);
	s.insert(30);
	s.insert(50);
	s.insert(40);
	s.insert(10);
	printSet(s);		//10 20 30 40 50

	//find：找到了返回找到的数据的迭代器位置，没有找到返回end迭代器位置
	//找到了
	set<int>::iterator it = s.find(30);
	cout << *it << endl;	//30
	s.erase(it);
	printSet(s);		//10 20 40 50

	//没有找到
	auto it2 = s.find(60);
	if (it2 == s.end())
		cout << "没有找到" << endl;	//没有找到

	//count:统计指定数据的个数，返回值是0或者1

	//找到了
	int size = s.count(20);
	cout << size << endl;	//1

	//没有找到
	size = s.count(100);
	cout << size << endl;	//0
}

//set中的查找、插入和删除的时间复杂度都是O(logn)

//set默认是按照less比较的，默认是增序（小于的数据放在左边，大于的数据放在右边）
void test8()
{
	//自定义对象的比较规则，在类中要重载 > 运算符和重载 < 运算符，指定比较规则
	//和优先队列一样，set构造函数有3个参数，第一个对象，第二个是比较规则，第三个是底层容器
	
	//默认是按照小于进行比较的
	//less按照小于比较，是增序的，greater按照大于比较，是降序的
	set<int,greater<int>> s;	
	s.insert(20);
	s.insert(30);
	s.insert(50);
	s.insert(40);
	s.insert(10);

	for (const auto& e : s)
		cout << e << " ";
	cout << endl;
}

//set的key和value必须一样，map中的key不能一样，map中的key和value可以不一样

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	test8();
	return 0;
}