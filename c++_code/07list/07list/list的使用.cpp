#include <iostream>
#include <list>
#include <vector>

using namespace std;

//构造函数
void test1()
{
	//无参构造
	list<int> l1;

	//n个val
	list<int> l2(3, 5);		//三个元素值为5的链表

	//区间构造（迭代器或者指针）
	string str = "123456";
	list<char> l3(str.begin(), str.end());
	char arr[] = "abcdef";
	list<char> l4(arr, arr + sizeof(arr) / sizeof(arr[0]));

	//拷贝构造
	list<char> l5(l4);
}

//list iterator(迭代器) 
void test2()
{
	string s("123456");
	list<char> l(s.begin(), s.end());
	list<char>::iterator it = l.begin();
	while (it != l.end())
	{
		cout << *it << " ";		//1 2 3 4 5 6
		++it;
	}
	cout << endl;

	list<char>::const_reverse_iterator crit = l.crbegin();
	while (crit != l.crend())
	{
		cout << *crit << " ";	//6 5 4 3 2 1
		++crit;
	}
	cout << endl;

	it = l.begin();
	it++;
	cout << *it << endl;	//2
	--it;
	cout << *it << endl;	//1
	//it = it + 1;	//error，不支持，只有随机访问迭代器支持
	//vector迭代器支持，可以直接跳过多个元素
	//迭代器分为3类，分别是前向迭代器、双向迭代器、随机访问迭代器
	//随机访问迭代器提供了一系列功能，如能够进行迭代器加减运算、下标索引、随机访问等，
	//使得我们能够方便地操作容器中的元素。这些容器可以根据实际需求选择，以便最高效地存储和操作数据。

	//支持随机访问的迭代器
	//std::array：固定大小的数组容器。
	//std::vector：动态数组容器。
	//std::deque：双端队列容器。
	//std::string：字符串容器。
	//std::valarray：值数组容器，用于数值计算。
	//std::map 和 std::multimap：关联容器，提供键值对的映射。
	//std::set 和 std::multiset：关联容器，存储不重复的元素，按照一定顺序排序。
	//std::unordered_map 和 std::unordered_multimap：无序关联容器，提供键值对的映射。
	//std::unordered_set 和 std::unordered_multiset：无序关联容器，存储不重复的元素，无序排列。
}

//范围for：底层是通过迭代器实现的
void test3()
{
	string s("123456");
	list<char> l(s.begin(), s.end());
	for (const auto& ch : l)
		cout << ch << " ";		//1 2 3 4 5 6
	cout << endl;

	for (auto& ch : l)		//&的原因：内置类型不影响效率，自定义类型&比值的效率高（&不用拷贝）
	{
		ch = 'a';
		cout << ch << " ";		//a a a a a a
	}
	cout << endl;
}

//empty	size max_size		list中不存在capacity接口，因为list底层是双向带头循环链表
void test4()
{
	list<int> l;
	cout << l.size() << endl;	//0
	l.push_back(10);
	if (l.empty())
		cout << "list为空" << endl;	
	else
		cout << l.size() << endl;	//1
	
	cout << l.max_size() << endl;	//357913941
}

//front back
void test5()
{
	list<int> l;
	l.push_back(10);
	l.push_front(20);
	cout << l.front() << endl;	//20
	cout << l.back() << endl;	//10
}

//assign：赋值，和=运算符逻辑一样的
void test6()
{
	string s("123456");
	list<char> l(s.begin(), s.end());
	for (const auto& ch : l)
		cout << ch << " ";		//1 2 3 4 5 6
	cout << endl;

	//n个val赋值
	l.assign(3, '5');
	for (const auto& ch : l)
		cout << ch << " ";		//5 5 5
	cout << endl;

	//区间赋值
	l.assign(s.begin(), s.end());
	for (const auto& ch : l)
		cout << ch << " ";		//1 2 3 4 5 6
	cout << endl;

	char arr[] = { 51,52,53,54,55,56 };
	l.assign(arr, arr + sizeof(arr) / sizeof(arr[0]));
	for (const auto& ch : l)
		cout << ch << " ";		//3 4 5 6 7 8
	cout << endl;

	//=运算符
	list<char> l2;
	l2 = l;
	for (list<char>::iterator it = l2.begin(); it != l2.end(); ++it)
		cout << *it << " ";		//3 4 5 6 7 8
	cout << endl;
}

//emplace_front emplace_back push_back push_front pop_front pop_back emplace insert erase clear
void test7()
{
	//加了emplace表示可以直接构造，先构造再插入
	list<int> l;
	l.push_front(1);
	l.push_back(2);
	l.insert(l.begin(), 3);
	l.insert(l.end(), 4);

	for (const auto& ch : l)
		cout << ch << " ";		//3 1 2 4
	cout << endl;

	l.insert(++l.begin(), 3, 5);			//在begin迭代器的下一个位置插入3个5
	//前置++是在begin迭代器的下一个位置插入，后置++是在begin迭代器的位置插入
	for (const auto& ch : l)
		cout << ch << " ";		//3 5 5 5 1 2 4
	cout << endl;

	//区间插入
	string s = "123456";
	l.insert(--l.end(), s.begin(), s.end());
	for (const auto& ch : l)
		cout << ch << " ";		//3 5 5 5 1 2 49 50 51 52 53 54 4
	cout << endl;
	l.pop_front();
	l.pop_back();

	//emplace
	l.emplace_back();		//不传参数默认是插入0，因为拷贝构造默认值是类0值
	l.emplace_front(15);
	for (const auto& ch : l)
		cout << ch << " ";		//15 5 5 5 1 2 49 50 51 52 53 54 0
	cout << endl;

	l.emplace(l.begin(), 10);	//begin迭代器位置插入10
	//l.emplace(l.begin(), 3, 7);	//error，不能实现，begin迭代器位置插入3个7
	for (const auto& ch : l)
		cout << ch << " ";		//10 15 5 5 5 1 2 49 50 51 52 53 54 0
	cout << endl;

	//erase返回值：迭代器，被删除元素的下一个元素的位置
	//删除单个值
	list<int>::iterator it = l.erase(l.begin());
	l.erase(it);
	for (const auto& ch : l)
		cout << ch << " ";		//5 5 5 1 2 49 50 51 52 53 54 0
	cout << endl;

	//删除一个区间的所有值
	l.erase(++l.begin(), --l.end());		//左闭右开，删除第一个参数的位置，不删除第二个参数的位置
	for (const auto& ch : l)
		cout << ch << " ";		//5 0
	cout << endl;

	//迭代器失效问题：
	//1.插入元素不会造成迭代器失效，因为list不会增容，插入节点就使用这个节点的空间。
	//2.删除元素会造成迭代器失效，因为删除节点会使这个节点的内容丢失，迭代器指向的内容是不存在的。

	//list中会导致迭代器失效的接口：erase、pop_back、pop_front
	l.clear();	//清空list
	if (l.empty())
		cout << "list为空" << endl;		//list为空
	else
		cout << "list不为空" << endl;
}

//swap resize
void test8()
{
	list<int> l1(5, 6);
	list<int> l2(1, 1);

	l1.swap(l2);		//无返回值

	for (const auto& ch : l1)
		cout << ch << " ";		//1
	cout << endl;

	for (const auto& ch : l2)
		cout << ch << " ";		//6 6 6 6 6
	cout << endl;

	l2.resize(3,4);
	for (const auto& ch : l2)
		cout << ch << " ";		//6 6 6 
	cout << endl;

	l1.resize(4);
	for (const auto& ch : l1)
		cout << ch << " ";		//1 0 0 0
	cout << endl;
	//resize减少节点个数，size就变小，resize增加节点个数，size就变大，用给的值填充，默认是类0值
}

//splice：拼接		无返回值
void test9()
{
	//被拼接的list就没有内容了
	std::list<int> l1, l2;
	std::list<int>::iterator it;

	for (int i = 1; i <= 4; ++i)
		l1.push_back(i);      //1 2 3 4

	for (int i = 1; i <= 3; ++i)
		l2.push_back(i * 10);   //10 20 30

	//1.拼接全部
	l1.splice(l1.begin(), l2);  
	for (const auto& ch : l1)
		cout << ch << " ";	//10 20 30 1 2 3 4
	cout << endl;

	if (l2.empty())
		cout << "l2为空" << endl;	//l2为空

	l2 = l1;
	for (const auto& ch : l2)
		cout << ch << " ";	//10 20 30 1 2 3 4
	cout << endl;

	//2.拼接一个
	l1.splice(l1.end(), l2, --l2.end());	//参数1：拼接到的位置，参数2：被拼接的list，参数3：被拼接的位置（只有当前位置）

	for (const auto& ch : l1)
		cout << ch << " ";	//10 20 30 1 2 3 4 4
	cout << endl;

	for (const auto& ch : l2)
		cout << ch << " ";	//10 20 30 1 2 3 
	cout << endl;

	//3.拼接一个区间
	l1.splice(l1.end(), l2, l2.begin(), --l2.end());
	for (const auto& ch : l1)
		cout << ch << " ";	//10 20 30 1 2 3 4 4 10 20 30 1 2 
	cout << endl;

	for (const auto& ch : l2)
		cout << ch << " ";	//3
	cout << endl;
}

//remove
void test10()
{
	string s = "fabcdef";
	list<char> l(s.begin(), s.end());
	l.remove('f');	//删除容器l中的所有字符'f'，如果容器l中不存在'f'，就忽略这条语句
	for (const auto& ch : l)
		cout << ch << " ";		//abcde
	cout << endl;

	//仿函数	函数指针
	//l.remove_if();			//之后看
}

//仿函数 函数指针
//函数
bool single_digit(const int& value) 
{
	return (value < 5); 
}

//类
struct is_odd
{
	bool operator() (const int& value) 
	{
		return (value % 2) == 1;
	}
};

//remove_if		删除指定规则的内容
void test11()
{
	list<int> l;
	for (int i = 0; i < 10; ++i)
		l.push_back(i);

	l.remove_if(single_digit);		//删除小于5的数字
	
	for (const auto& ch : l)
		cout << ch << " ";			//5 6 7 8 9 
	cout << endl;

	l.remove_if(is_odd());			//删除奇数的数字

	for (const auto& ch : l)
		cout << ch << " ";			//6 8
}

//unique：相邻重复元素去重	有序的		无需的先排序后去重
void test12()
{
	string s = "baaabbcddeffghh";
	list<char> l(s.begin(), s.end());

	for (const auto& ch : l)
		cout << ch << " ";	//a a a b b c d d e f f g h h
	cout << endl;

	l.unique();

	for (const auto& ch : l)
		cout << ch << " ";	//a b c d e f g h
	cout << endl;

	double arr[] = { 1.2,3.5,4.2,7.2,8.3,10.2,12.5,16 };
	list<double> l1(arr, arr + sizeof(arr) / sizeof(arr[0]));
}

//由大到小排序
bool compareList(const int& a, const int& b)
{
	return a > b;
}

//sort	默认是按照有小到大排序	仿函数实现由大到小排序
void test13()
{
	string s = "bfdghace";
	list<char> l(s.begin(), s.end());

	for (const auto& ch : l)
		cout << ch << " ";	//b f d g h a c e
	cout << endl;

	l.sort();

	for (const auto& ch : l)
		cout << ch << " ";	//a b c d e f g h
	cout << endl;

	l.sort(compareList);

	for (const auto& ch : l)
		cout << ch << " ";	//h g f e d c b a
	cout << endl;
}

//仿函数，用于判断两个元素是否相等
struct MyComparator
{
	bool operator()(const int& a, const int& b) const
	{
		return a % 3 == b % 3;  // 按照元素对 3 取模的结果判断是否相等
	}
};

//unique仿函数	不推荐使用
void test14()
{
	std::list<int> l = { 1, 2, 4, 7, 8, 10, 11, 13, 14, 16 };

	// 使用 unique 去除相邻重复元素，传入自定义的仿函数
	l.unique(MyComparator());

	// 输出去重后的结果
	for (const auto& num : l) 
	{
		std::cout << num << " ";		//1 2 4 8 10 11 13 14 16
	}
	std::cout << std::endl;
}

//merge	合并有序的list	不是有序的输出结果无法预知或者报错
void test15()
{
	list<int> l1 = { 1,3,5,7,9,11 };
	list<int> l2 = { 2,4,6,8,10,12 };
	
	l1.merge(l2);
	
	for (const auto& ch : l1)
		cout << ch << " ";		//1 2 3 4 5 6 7 8 9 10 11 12
	cout << endl;

	if (l2.empty())
		cout << "l2为空" << endl;	//l2为空
}

//reverse：反转list  容器提供接口就是用容器提供的，效率高，没有就使用algorithm提供的接口
void test16()
{
	list<int> l = { 1,2,3,4,5,8,7,6 };
	l.reverse();
	for (const auto& ch : l)
		cout << ch << " ";	//6 7 8 5 4 3 2 1
	cout << endl;
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();	 
	//test9();
	//test10();
	//test11();
	//test12();
	//test13();
	//test14();
	//test15();
	test16();
	return 0;
}