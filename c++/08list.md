# 1.list的介绍

list不是原生迭代器，list是双向带头循环链表，适合需要经常修改的。

1.list是可以在常数范围内在任意位置进行插入和删除的序列式容器，并且该容器可以前后双向迭代。

2.list的底层是双向链表结构，双向链表中每个元素存储在互不相关的独立节点中，在节点中通过指针指向其前一

个元素和后一个元素。

3.list与forward_list非常相似：最主要的不同在于forward_list是单链表，只能朝前迭代，已让其更简单高效。

4.与其他的序列式容器相比(array，vector，deque)，list通常在任意位置进行插入、移除元素的执行效率更好。

5.与其他序列式容器相比，list和forward_list最大的缺陷是不支持任意位置的随机访问，比如：要访问list的第6个

元素，必须从已知的位置(比如头部或者尾部)迭代到该位置，在这段位置上迭代需要线性的时间开销；list还需要一

些额外的空间，以保存每个节点的相关联信息(对于存储类型较小元素的大list来说这可能是一个重要的因素。

![image-20230625165454894](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230625165454894.png)



# 2.list的使用

## 2.1list的构造

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//构造函数
int main()
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

	for (const auto& e : l1)
		cout << e << " ";
	cout << endl;
	for (const auto& e : l2)
		cout << e << " ";
	cout << endl;
	for (const auto& e : l3)
		cout << e << " ";
	cout << endl;
	for (const auto& e : l4)
		cout << e << " ";
	cout << endl;

	//拷贝构造
	list<char> l5(l4);
	return 0;
}
//输出结果：
//
//5 5 5
//1 2 3 4 5 6
//a b c d e f
```



## 2.2list的迭代器

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//list iterator(迭代器) 
int main()
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
	//	随机访问迭代器提供了一系列功能，如能够进行迭代器加减运算、下标索引、随机访问等，
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

	return 0;
}
//输出结果：
//1 2 3 4 5 6
//6 5 4 3 2 1
//2
//1
```



## 2.3范围for循环

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//范围for循环：底层是通过迭代器实现的
int main()
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

	return 0;
}
//输出结果：
//1 2 3 4 5 6
//a a a a a a
```



## 2.4list的容量操作

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//empty	size max_size		list中不存在capacity接口，因为list底层是双向带头循环链表
int main()
{
	list<int> l;
	cout << l.size() << endl;	//0
	
	l.push_back(10);
	if (l.empty())
		cout << "list为空" << endl;
	else
		cout << l.size() << endl;	//1

	cout << l.max_size() << endl;	//357913941

	return 0;
}
//输出结果：
//0
//1
//357913941
```



## 2.5list列表元素访问

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//front back push_back push_front
int main()
{
	list<int> l;
	l.push_back(10);
	l.push_front(20);
	cout << l.front() << endl;	//20
	cout << l.back() << endl;	//10

	return 0;
}
//输出结果：
//20
//10
```



## 2.6list的赋值操作

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//assign：赋值，和=运算符逻辑一样的
int main()
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

	return 0;
}
//输出结果：
//1 2 3 4 5 6
//5 5 5
//1 2 3 4 5 6
//3 4 5 6 7 8
//3 4 5 6 7 8
```



## 2.7list容器的增删查改操作

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//emplace_front emplace_back push_back push_front insert insert pop_front pop_back   emplace erase clear
int main()
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

	return 0;
}
//输出结果：
//3 1 2 4
//3 5 5 5 1 2 4
//3 5 5 5 1 2 49 50 51 52 53 54 4
//15 5 5 5 1 2 49 50 51 52 53 54 0
//10 15 5 5 5 1 2 49 50 51 52 53 54 0
//5 5 5 1 2 49 50 51 52 53 54 0
//5 0
//list为空
```



## 2.8swap和resize

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//swap resize
int main()
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

	l2.resize(3, 4);
	for (const auto& ch : l2)
		cout << ch << " ";		//6 6 6 
	cout << endl;

	l1.resize(4);
	for (const auto& ch : l1)
		cout << ch << " ";		//1 0 0 0
	cout << endl;
	//resize减少节点个数，size就变小，给定值忽略。
	//resize增加节点个数，size就变大，用给的值填充，默认是类0值。

	return 0;
}
//输出结果：
//1
//6 6 6 6 6
//6 6 6
//1 0 0 0
```



## 2.9list拼接（splice）

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//splice：拼接		无返回值
int main()
{
	//被拼接的list就没有内容了
	std::list<int> l1, l2;
	std::list<int>::iterator it;

	for (int i = 1; i <= 4; ++i)
		l1.push_back(i);      //1 2 3 4

	for (int i = 1; i <= 3; ++i)
		l2.push_back(i * 10);   //10 20 30

	//1.拼接全部	在l1的begin迭代器位置拼接整个l2，l2就变为空了
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
	//总结：
	//splice函数的被拼接方拼接之后，拼接方的内容就不在了。
	//比如：l2的内容拼接到l1的里面，l2里面添加的内容就会在l1里面减少。

	return 0;
}
//输出结果：
//10 20 30 1 2 3 4
//l2为空
//10 20 30 1 2 3 4
//10 20 30 1 2 3 4 4
//10 20 30 1 2 3
//10 20 30 1 2 3 4 4 10 20 30 1 2
//3
```



## 2.10list删除（remove和remove_if）

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//删除 remove
int main()
{
	string s = "fabcdef";
	list<char> l(s.begin(), s.end());
	l.remove('f');	//删除容器l中的所有字符'f'，如果容器l中不存在'f'，就忽略这条语句
	for (const auto& ch : l)
		cout << ch << " ";		//a b c d e
	cout << endl;

	return 0;
}
//输出结果：
//a b c d e
```

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

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
int main()
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

	return 0;
}
//输出结果：
//5 6 7 8 9
//6 8
```



## 2.11list相邻元素去重（unique）

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//unique：相邻重复元素去重 无顺序
int main()
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

	return 0;
}
//输出结果：
//b a a a b b c d d e f f g h h
//b a b c d e f g h
```

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//仿函数，用于判断两个元素是否相等
struct MyComparator
{
	bool operator()(const int& a, const int& b) const
	{
		return a % 3 == b % 3;  // 按照元素对 3 取模的结果判断是否相等
	}
};

//unique仿函数	不推荐使用
int main()
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

	return 0;
}
//输出结果：
//1 2 4 8 10 11 13 14 16
```



## 2.12list的排序（sort）

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//由大到小排序
bool compareList(const int& a, const int& b)
{
	return a > b;
}

//sort	默认是按照有小到大排序	仿函数实现由大到小排序
int main()
{
	string s = "bfdghace";
	list<char> l(s.begin(), s.end());

	for (const auto& ch : l)
		cout << ch << " ";	//b f d g h a c e
	cout << endl;

	//从小到大排序
	l.sort();
	for (const auto& ch : l)
		cout << ch << " ";	//a b c d e f g h
	cout << endl;

	//仿函数实现从大到小排序
	l.sort(compareList);
	for (const auto& ch : l)
		cout << ch << " ";	//h g f e d c b a
	cout << endl;

	return 0;
}
//输出结果：
//b f d g h a c e
//a b c d e f g h
//h g f e d c b a
```



## 2.13合并有序的list（merage）

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//merge	合并有序的list	不是有序的输出结果无法预知或者报错(只有合并有序的才能预知结果)
//使用merge函数之后，把参数中的内容清空到调用函数的里面去。
int main()
{
	list<int> l1 = { 1,3,5,7,9,11 };
	list<int> l2 = { 2,4,6,8,10,12 };

	l1.merge(l2);

	for (const auto& ch : l1)
		cout << ch << " ";		//1 2 3 4 5 6 7 8 9 10 11 12
	cout << endl;

	if (l2.empty())
		cout << "l2为空" << endl;	//l2为空

	return 0;
}
//输出结果：
//1 2 3 4 5 6 7 8 9 10 11 12
//l2为空
```



## 2.14反转list(reverse)

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//reverse：反转list  容器提供接口就是用容器提供的，效率高，没有就使用algorithm提供的接口
int main()
{
	list<int> l = { 1,2,3,4,5,8,7,6 };
	l.reverse();
	for (const auto& ch : l)
		cout << ch << " ";	//6 7 8 5 4 3 2 1
	cout << endl;

	return 0;
}
//输出结果：
//6 7 8 5 4 3 2 1
```

list没有查找的接口，需要调用algorithm类中的find接口。



# 3.力扣题

单链表的定义：

struct ListNode {

​    int val;

​    struct ListNode *next;

};

## 203.移除链表元素

题目：给你一个链表的头节点 `head` 和一个整数 `val` ，请你删除链表中所有满足 `Node.val == val` 的节点，并

返回 **新的头节点** 。

```c
示例1：
输入：head = [1,2,6,3,4,5,6], val = 6
输出：[1,2,3,4,5]
示例2：
输入：head = [], val = 1
输出：[]
示例3：
输入：head = [7,7,7,7], val = 7
输出：[]
 
提示：
列表中的节点数目在范围 [0, 104] 内
1 <= Node.val <= 50
0 <= val <= 50
```

```c
方法1：不分特殊情况，统一遍历解法
1.遍历整个链表，分为要删除和不要删除进行移动；
2.要删除分为头结点和非头结点进行处理，遍历的节点进行统一连接。
struct ListNode* removeElements(struct ListNode* head, int val){
    //记录下一个节点
    struct ListNode* cur = head;
    struct ListNode* prev = NULL;   //确定是否是头结点
    while(cur)          //head == NULL 的特殊情况省略，是NULL就不进入循环，直接返回head就是NULL
    {
        //判断是否删除
        if(cur->val == val)
        {
            //判断删除的是否是头结点
            if(prev == NULL)    
            {
                //头节点删除
                head = cur->next;
            }
            else
            {
                //删除的不是头结点
                prev->next = cur->next;
            }
            //连接
            struct ListNode* next = cur->next;
            free(cur);
            cur = next;
        }
        else
        {
            //不删除，直接往后遍历
            prev = cur;
            cur = cur->next;
        }
    }
    return head;
}
时间复杂度：O(n)
空间复杂度：O(1)

方法2：递归
1.递归的终止条件：head为空，没有节点可以进行删除，当haed不为空时，递归的进行删除操作；
2.连接：这个函数是移除链表元素，head->next连接到下一个不是val放入节点，下一个节点是val就连接val的下一个节点；
3.返回值：head的值和要删除的val的值相等就返回head的下一个节点，不相等就返回head节点。
struct ListNode* removeElements(struct ListNode* head, int val){
    //缺点：没有真正删除节点
    //递归解题:要删除的值是头结点的话就返回下一个节点的地址，不是的话就返回头结点的地址
    //终止条件：链表为空就返回head
    if(head == NULL)
        return head;
    //递归过程
    head->next = removeElements(head->next, val);	//连接，连接到下一个删除之后的链表节点
    //返回值
    return head->val == val ? head->next : head;
}
时间复杂度：O(n)，n是链表的长度，递归过程需要遍历链表一次。
空间复杂度：O(n)，n是链表的长度。空间复杂度主要取决于递归调用栈，最多不会超过n层。
    
方法3：哑结点
1.创建了1个哑结点，哑结点的next指向头结点；
2.prev是1个要遍历节点的头一个节点，这里是确保删除下一个节点的时候号连接；
3.prev->next->val和val相等就删除、连接，不相等就遍历下一个节点；
4.连接完成之后进行删除创建的哑结点。
struct ListNode* removeElements(struct ListNode* head, int val){
    struct ListNode* dummyHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyHead->next = head;
    struct ListNode* prev = dummyHead;
    while(prev->next)
    {
        if(prev->next->val == val)
        {
            //删除  连接
            struct ListNode* next = prev->next;
            prev->next = prev->next->next;
            free(next);
            
        }
        else
        {
            //不删除  遍历
            prev = prev->next;
        }
    }
    struct ListNode* newnode = dummyHead->next;
    free(dummyHead); 
    return newnode;
}
时间复杂度：O(n),n是链表的长度。
空间复杂度：O(1),使用了一个结构体的大小。
    
方法4：特殊情况解法：
1.如果头结点的值是要删除的值，就改变头节点的指向；
2.遍历链表，分为要删除和不删除两种情况讨论。
struct ListNode* removeElements(struct ListNode* head, int val){
    
    struct ListNode* cur = head;
    struct ListNode* prev = NULL;
    //确定要删除的是不是头结点，是的话就修改头结点
    while(cur && cur->val == val)   //这里包含了cur == NULL的情况
    { 
        head = cur->next;
        free(cur);
        cur = head;
    }

    //遍历删除
    while(cur)
    {
        if(cur->val == val)
        {
            struct ListNode* next = cur->next;
            prev->next = next;
            free(cur);
            cur = next;
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
    return head;
}
```

## 206.反转链表

题目：给你单链表的头节点 `head` ，请你反转链表，并返回反转后的链表。

```c
示例1：
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
示例2：
输入：head = [1,2]
输出：[2,1]
示例 3：
输入：head = []
输出：[]

提示：
链表中节点的数目范围是 [0, 5000]
-5000 <= Node.val <= 5000

方法1：头插法
第一种写法：创建一个新头结点为NULL，从第一个头结点开始进行遍历，更新新的头结点。
struct ListNode* reverseList(struct ListNode* head){
    //头插法
    //if(head == NULL || head->next == NULL)
    //    return head;
    struct ListNode* cur = head;
    struct ListNode* newhead = NULL;
    while(cur)
    {
        struct ListNode* next = cur->next;
        cur->next = newhead;
        newhead = cur;
        cur = next;
    } 
    return newhead;
}

第二种写法：将第一个头结点作为新的头结点，从头结点的下一个节点进行遍历，通过特殊情况确定前两个节点都存在，第三个（NULL）节点可能为NULL，要确定next是否存在。
struct ListNode* reverseList(struct ListNode* head){
    //头插
    if(!head || !head->next)
        return head;
	//走到下面最少存在两个节点，next可能为NULL
    struct ListNode* newnode = head;    
    struct ListNode* cur = newnode->next;       //作为遍历的节点
    struct ListNode* next = cur->next;         
    newnode->next = NULL;    //使新的头结点指向空

    while(cur)
    {
        cur->next = newnode;
        newnode = cur;
        cur = next;
        if(next)		//next可能为NULL
            next = next->next;
    }

    return newnode;
}
时间复杂度：O(n)，n是链表的长度。需要遍历链表一次。
空间复杂度：O(1)，没有使用额外空间。

方法2：递归
1.结束条件：头结点或者头结点的下一个节点是NULL就返回头结点。
2.递归过程：此后，每次函数在返回的过程中，让当前结点的下一个结点的next指针指向当前节点。同时让当前结点的next指针指向NULL，从而实现从链表尾部开始的局部反转
当递归函数全部出栈后，链表反转完成。
3.返回值：返回最后一次的头结点。
4.最后一次处理：最后一个节点的next是NULL的时候就返回最后一个节点（翻转链表的新的头结点），倒数第二个节点的下一个节点是最后一个节点指向倒数第二个节点，倒数第二个节点指向NULL。
struct ListNode* reverseList(struct ListNode* head){
    //递归

    //结束
    if(!head || !head->next)
        return head;

    //循环
    struct ListNode* newnode = reverseList(head->next);

    //连接
    head->next->next = head;
    head->next = NULL;

    return newnode;
}
时间复杂度：O(n)，n是链表的长度，需要对链表的每个节点进行反转操作。
空间复杂度：O(n)，n是链表的长度，空间复杂度主要取决于递归调用的栈空间，最多为n层。

方法3：双指针		绕环拆环
1.不变性：head和next的关系，head不变（相对性的前进1位），cur循环之后云远在最后一位。
2.原链表的头结点就是反转之后链表的尾结点，使用head标记； .
3.定义指针cur，初始化为head； 
4.每次都让head 下一个结点的next指向cur，实现一次局部反转；
5.局部反转完成之后，cur和head的next指针同时往前移动一个位置；
6.循环上述过程，直至cur到达链表的最后一个结点。
struct ListNode* reverseList(struct ListNode* head)
{ 
    if(head == NULL)
        return head;
    struct ListNode* cur = head;
    while(head->next)
    {
        struct ListNode* next = head->next->next;		//记录
        head->next->next = cur;							//组环
        cur = head->next;						
        head->next = next;								//拆环 
    }
    return cur;
}
时间复杂度：O(n)，n是链表的长度，需要对链表的每个节点进行反转操作。
空间复杂度：O(1)，没有使用额外空间。
```

## 876.链表的中间节点

题目：给你单链表的头结点 `head` ，请你找出并返回链表的中间结点。如果有两个中间结点，则返回第二个中间结点。

```c
示例1：
输入：head = [1,2,3,4,5]
输出：[3,4,5]
解释：链表只有一个中间结点，值为3。
示例2：
输入：head = [1,2,3,4,5,6]
输出：[4,5,6]
解释：该链表有两个中间结点，值分别为 3 和 4 ，返回第二个结点。
 
提示：
链表的结点数范围是[1, 100]
1 <= Node.val <= 100
```

```c
方法1：快慢指针
1.定义两个指针，都指向链表头节点；
2.快指针fast一次走两步，慢指针slow一次走一步；
3.偶数的时候要两个中间节点的后一个节点，要确保最后一个节点的前提下确保第二个节点存在。（题目条件：如果有两个中间结点，则返回第二个中间结点。）
struct ListNode* middleNode(struct ListNode* head){
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}
时间复杂度:O(n)，快指针遍历了链表中的所有节点，n是链表的节点数目。
空间复杂度：O(1)，两个常数空间存放slow和fast两个指针。
   
方法2：计数法
1.第一次遍历统计链表元素的个数；
2.第二次遍历链表元素的一半元素。
struct ListNode* middleNode(struct ListNode* head){
    struct ListNode* cur = head;
    int len = 0;
    while(cur)
    {
        cur = cur->next;
        len++;
    } 
    cur = head;
    for(int i = 0; i < (len / 2); i++)
    {
        cur = cur->next;
    } 
    return cur;
}
时间复杂度：O(n)，n是链表的结点数目。
空间复杂度：O(1)，不需要使用额外空间。

方法3：数组
1.链表转化为数组，c++可以实现，但没必要。

```

## 剑指offer22.链表中的倒数第K个节点

题目：输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。

例如，一个链表有 6 个节点，从头节点开始，它们的值依次是 1、2、3、4、5、6。这个链表的倒数第 3 个节点是值为 4 的节点。

```c
示例：
给定一个链表: 1->2->3->4->5， 和 k = 2。
返回链表 4->5。
```

```c
方法1：快慢指针
1.快指针fast先走k步；
2.慢指针slow和快指针fast再同时走，直到快指针走到NULL为止返回慢指针slow。
struct ListNode* getKthFromEnd(struct ListNode* head, int k){
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while(k--)
    {
        //fast有可能不存在，就是链表的长度小于倒数的值
        if(fast)
            fast = fast->next;
        else
            return NULL;
    }
    while(fast)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}
时间复杂度：O(n)，n为链表的长度，遍历一次链表。
空间复杂度：O(1),没有使用额外空间。

方法2：顺序查找：把倒数的转化为正数的。
1.当前链表的长度为n，则我们知道链表的倒数第k个节点即为正数第n−k+1个节点，此时我们只需要顺序遍历完链表的n−k个节点即可到达倒数第 
k个节点。
2.我们首先求出链表的长度n，然后顺序遍历到链表的第n−k个节点返回即可。
struct ListNode* getKthFromEnd(struct ListNode* head, int k){
     //倒数的节点转换为正数的节点:倒数第k个节点就是正数第count - k + 1个节点
    struct ListNode* cur = head;
    int len = 0; //链表的长度
    while(len)
    {
        count++;
        cur = cur->next;
    }
    if(k > len)
        return NULL;    //防止k大于链表的长度
    cur = head;
    for(int i = 0;i < len - k;i++)
    {
        cur = cur->next;
    }
    return cur;
}
时间复杂度：O(n)，n为链表的长度，遍历两次链表。
空间复杂度：O(1),没有使用额外空间。
```

## 21.合并两个有序链表

题目：将两个升序链表合并为一个新的 **升序** 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

```c
示例1：
输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
示例 2：
输入：l1 = [], l2 = []
输出：[]
示例 3：
输入：l1 = [], l2 = [0]
输出：[0]

提示：
两个链表的节点数目范围是[0, 50]
-100 <= Node.val <= 100
l1 和 l2 均按非递减顺序排列
```

```c
方法1：哑结点
1.创建一个哑结点（记得释放），根据题目特殊处理链表可能为空的情况；
2.哑结点不能改变，去个零时节点指向哑结点进行遍历；
3.进行判断list1和list2的val的大小，小的放到临时节点的后面，再更新临时节点和两个链表的节点（这里可以取个临时节点，一般不要更新参数），直到其中一个链表更新完；
4.其中一个链表可能有剩余元素，处理剩余元素；
5.记录哑结点的下一个节点作为新的头结点，释放哑结点，返回新的头结点。
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    //链表可能为空
    if(list1 == NULL)
        return list2;
    if(list2 == NULL)
        return list1;
    //哑结点
    struct ListNode* dummyhead = (struct ListNode*)malloc(sizeof(struct ListNode));
    //遍历节点
    struct ListNode* cur = dummyhead;
    while(list1 && list2)
    {
        if(list1->val < list2->val)
        {
            cur->next = list1;
            list1 = list1->next;
        }
        else
        {
            cur->next = list2;
            list2 = list2->next;
        }
        cur = cur->next;    //遍历
    }
    //list1和list2有一个可能存在剩余节点
    cur->next = (list1 == NULL ? list2 : list1);
    struct ListNode* newnode = dummyhead->next;
    free(dummyhead);
    return newnode;
}    
时间复杂度：O(m + n)，m 和 n是两个链表的长度，while的循环次数不会超过m + n的和，剩下的操作都是常数级别的。
空间复杂度：O(1)，只需要常数的空间存放若干变量（哑结点）。

方法2：递归
1.结束条件：递归到其中一个链表为空就返回另外一个链表。
2.递归过程：如果 list1 或者 list2 一开始就是空链表 ，那么没有任何操作需要合并，所以我们只需要返回非空链表。否则，我们要判断 list1 和 list2 哪一个链表的头节点的值更小，然后递归地决定下一个添加到结果里的节点。如果两个链表有一个为空，递归结束。
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    
    if(!list1)
        return list2;
    if(!list2)
        return list1;

    if(list1->val <= list2->val)
    {
        //list1是整体的头节点
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    }
    else
    {
        list2->next = mergeTwoLists(list2->next, list1);
        return list2;
    }
}
时间复杂度：O(n + m)，n和m是两个链表的长度，因为每次递归都会去掉两个链表其中一个的头节点，至多只会递归每个头结点一次。
空间复杂度：O(n + m)，n和m是两个链表的长度，递归函数时会消耗栈空间，栈空间的大小取决于递归调用的深度，结束递归调用时函数最多会调用m + n次。

方法3：确定头结点
1.确定头结点；
2.进行判断list1和list2的val的大小，小的放到临时节点的后面，再更新临时节点和两个链表的节点（这里可以取个临时节点，一般不要更新参数），直到其中一个链表更新完；
3.其中一个链表可能有剩余元素，处理剩余元素；
4.返回newhead。
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    //链表可能为空
    if(list1 == NULL)
        return list2;
    if(list2 == NULL)
        return list1;
    //确定头结点
    struct ListNode* newhead = NULL;
    if(list1->val <= list2->val)
    {
        newhead = list1;
        list1 = list1->next;
    }
    else
    {
        newhead = list2;
        list2 = list2->next;
    }
    //遍历节点
    struct ListNode* cur = newhead;;
    while(list1 && list2)
    {
        if(list1->val <= list2->val)
        {
            cur->next = list1;
            list1 = list1->next;
        }
        else
        {
            cur->next = list2;
            list2 = list2->next;
        }
        cur = cur->next;    //遍历
    }
    //list1和list2可能有一个存在剩余节点
    cur->next = (list1 == NULL ? list2 : list1);
    return newhead;
}
时间复杂度：O(m + n)，m 和 n是两个链表的长度，while的循环次数不会超过m + n的和，剩下的操作都是常数级别的。
空间复杂度：O(1)，没有使用额外空间。
```

## 面试题02.04分割链表

题目：给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。

你不需要保留每个分区中各节点的初始相对位置。

```c
示例1：
输入：head = [1,4,3,2,5,2], x = 3
输出：[1,2,2,4,3,5]
示例2：
输入：head = [2,1], x = 2
输出：[1,2]

提示：
链表中节点的数目在范围 [0, 200] 内
-100 <= Node.val <= 100
-200 <= x <= 200
```

```c
方法1：创建两个哑结点
1.创建两个哑结点small和large；
2.small1和large1分别指向small和large，用来存储小于x的节点和大于x的节点；
3.大于x的链表的尾节点指向NULL，小于x的链表的尾节点指向大于x的真正的首节点；（这个顺序不能反，特殊情况大于x的没有一个值，会出现small1->next = large->next中的large没有初始化，是不确定的，会多一个没有确定指向节点，容易出现不确定的访问。）
4.释放两个哑结点，返回真正的新的头结点。
struct ListNode* partition(struct ListNode* head, int x){
    //if(head == NULL || head->next == NULL)
    //    return head;
    struct ListNode* small = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* large = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* small1 = small;
    struct ListNode* large1= large;
    while(head)
    {
        if(head->val < x)
        {
            small1->next = head;
            small1 = small1->next;
        }
        else
        {
            large1->next = head;
            large1 = large1->next;
        }
        head = head->next;
    }
    //不能修改顺序：写反了容易出现指向出错的情况  
    large1->next = NULL;
    small1->next = large->next;
    
    struct ListNode* newhead = small->next;
    free(small);
    free(large);
    return newhead; 
}
时间复杂度：O(n)，n是链表的长度，需要遍历一遍链表。
空间复杂度：O(1)，2个哑结点是常数级的空间。
    
方法2：小于x的头插，大于x的尾插。
1.确定head存在，这样确保tail存在；
2.先确定尾节点的位置，再创建一个临时指针指向尾节点；
3.遍历到临时节点的前一个节点，最后一个节点的大小不影响本题的结果，因为遍历处理后最后一个节点的前面节点都小于x，后面的节点都大于等于x节点；
4.首先判断val是否大于x，x大于val就要尾插，尾插要判断当前节点是不是首节点，是首节点要改变头结点的位置，小于就向后遍历。 
struct ListNode* partition(struct ListNode* head, int x)
{
    if(head == NULL)
        return head;
    //大的尾插
    struct ListNode* newhead = head, *cur = head, *tail = head;
    struct ListNode* prev = NULL;       //判断是不是头结点
    //查找链表尾部
    while(tail->next)
    {
        tail = tail->next;  
    }
    struct ListNode* tailcur = tail;    //尾插节点
    while(cur != tail)
    {
        if(cur->val >= x)
        {
            struct ListNode* next = cur->next;
            //尾插
            if(prev == NULL)    //判断是不是头部节点
            {
                //更新头部
                tailcur->next = cur;
                cur->next = NULL;
                newhead = next;
                cur = next;
            }
            else
            {
                //直接尾插 
                prev->next = next;
                tailcur->next = cur;
                cur->next = NULL;
                cur = next;
            }
            tailcur = tailcur->next;
        }
        else
        {
            prev = cur;
            //向后遍历
            cur = cur->next;
        }
    }
    return newhead;
}
时间复杂度：O(n)，n是链表的长度，遍历了n - 1个节点，最后一个节点的大小不影响结果（仅限本题）。
空间复杂度：O(1)，没有使用额外空间。
```

## 234.回文链表

题目：给你一个单链表的头节点 `head` ，请你判断该链表是否为回文链表。如果是，返回 `true` ；否则，返回 `false` 。

```c
示例1：
输入：head = [1,2,2,1]
输出：true
示例2：
输入：head = [1,2]
输出：false
 
提示：
链表中节点数目在范围[1, 105] 内
0 <= Node.val <= 9 
```

```c
方法1：快慢指针翻转后半段链表进新比较
1.快慢指针找中间节点，奇数找最中间一个，偶数找中间两个的后一个；
2.对后半段链表进行翻转；
3.遍历翻转后的链表，如果翻转后的后半段链表和前半段值不相等返回fasle，否则循环结束返回true。
备注：题目没说链表结构可不可以修改，不可以就把链表翻转封装成函数，最后调用一次恢复链表结构。
bool isPalindrome(struct ListNode* head){
//   if(head->next == NULL)
//      return true;
    struct ListNode* fast = head, *slow = head;
    //快慢指针找到中间节点  中间两个找后一个
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    struct ListNode* cur = slow;    //中间节点
    struct ListNode* newhead = NULL;
    //翻转后半段链表
    while(cur)
    {
        //头插
        struct ListNode* next = cur->next;
        cur->next = newhead;
        newhead = cur;
        cur = next;
    }
    while(newhead)  //这里不能使用head，head的末尾指向不确定，newhead的末尾指向是NULL
    {
        if(head->val != newhead->val)
            return false;
        head = head->next;
        newhead = newhead->next;
    }
    return true;
}
时间复杂度：O(n)，n是链表的长度，遍历了两遍链表。
空间复杂度，O(1)，没有使用额外空间。
    
方法2：将链表转换为数组
1.统计链表的长度，根据链表的长度有上限创建数组；
2.对比首尾数组，不相同返回false，知道循环结束返回true。
bool isPalindrome(struct ListNode* head){
    struct ListNode* cur = head;
    int arr[100000] = {0};		//可以不初始化，链表的最大长度
    //统计链表的长度
    int len = 0;
    while(cur)
    {
        cur = cur->next;
        ++len;
    }
    cur = head;
    //将链表放入数组中
    for(int i = 0; i < len; i++)
    {
        arr[i] = cur->val;
        cur = cur->next;
    }
    int start = 0;
    int end = len - 1;
    while(start < end)
    {
        if(arr[start] != arr[end])
            return false;
        ++start;
        --end;
    }
    return true;
}
时间复杂度：O(n)，你是链表长度，遍历了两边链表和一半数组；（链表也可以不统计长度，直接遍历head存储到数组中，这样只遍历一遍链表）
空间复杂度：O(n),n是链表的数组，创建了一个最大数组，比n大。
    
方法3：递归
1.思路：先递归到最后一个节点，再比较第一个节点和最后一个节点是否相等；
2.结束：end走到链表头结点，begin走到链表尾节点，如果相等begin走到NULL，最后返回true。
struct ListNode* begin;

bool recursivelyCheck(struct ListNode* end) {
    if (end != NULL) {
        if (!recursivelyCheck(end->next)) {     //递归到最后一个节点
            return false;
        }
        if (end->val != begin->val) {            //比较正向和反向的值是否相等
            return false;
        }
        begin = begin->next;
    }
    return true;
}

bool isPalindrome(struct ListNode* head) {
    begin = head;
    return recursivelyCheck(head);
}
时间复杂度：O(n)，n是链表的大小。
空间复杂度：O(n)，n是链表的大小，最多递归了n层。
    
第二种递归写法：
struct ListNode* begin;

bool recursivelyCheck(struct ListNode* end) {
    //递归的第二种写法：
    //递归的结束条件
    if(end == NULL)
        return true;
    //递归的调用过程：递归到最后一个节点，比较最后一个节点和第一个节点，在相等的情况下比较第二个节点和倒数第二个节点
    bool res = (recursivelyCheck(end->next) && (end->val == begin->val));
    begin = begin->next;
    return res;
}

bool isPalindrome(struct ListNode* head) {
    begin = head;
    return recursivelyCheck(head);
}

递归代码前提明白链表的反向打印：
void printListNode(struct ListNode* head) {
    if (head == NULL)
        return;
    printListNode(head->next);
    printf("%d",head->val);
}
    
方法4：反向哈希
方法5：栈，链表节点进栈，再出栈和链表节点进行比较。
```

## 160.相交链表

题目：给你两个单链表的头节点 `headA` 和 `headB` ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 `null` 。

![image-20230511010948906](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230511010948906.png)

题目数据 **保证** 整个链式结构中不存在环。

**注意**，函数返回结果后，链表必须 **保持其原始结构** 。

```c
示例1：
输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
输出：Intersected at '8'
解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。
从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,6,1,8,4,5]。
在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
— 请注意相交节点的值不为 1，因为在链表 A 和链表 B 之中值为 1 的节点 (A 中第二个节点和 B 中第三个节点) 是不同的节点。换句话说，它们在内存中指向两个不同的位置，而链表 A 和链表 B 中值为 8 的节点 (A 中第三个节点，B 中第四个节点) 在内存中指向相同的位置。
示例2：
输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
输出：null
解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。
由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。
这两个链表不相交，因此返回 null 。

提示：
listA 中节点数目为 m
listB 中节点数目为 n
1 <= m, n <= 3 * 104
1 <= Node.val <= 105
0 <= skipA <= m
0 <= skipB <= n
如果 listA 和 listB 没有交点，intersectVal 为 0
如果 listA 和 listB 有交点，intersectVal == listA[skipA] == listB[skipB]
```

```c
方法1：快慢指针
1.统计两个链表的长度，长度长的作为快指针fast，长度短的作为slow；
2.快指针fast先走两个链表的长度差值，最后再同时走，走到同一个节点表示有相同节点，走到NULL表示没有相交的节点。
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    //快慢指针
    struct ListNode* fast = headA;
    struct ListNode* slow = headB;
    //统计两个链表的长度
    int lena = 0,lenb = 0;
    while(fast)
    {
        ++lena;
        fast = fast->next;
    }
    while(slow)
    {
        ++lenb;
        slow = slow->next;
    } 
    //长度差值
    int len = lena - lenb;
    if(len > 0)
    {
        fast = headA;
        slow = headB;
    }
    else
    {
        len = -len;
        fast = headB;
        slow = headA;
    }

    //长的一条链表走两个链表长度的差值
    while(len--)
    {
        fast = fast->next;
    }
    while(slow && fast)     //循环全部结束，返回slow是NULL
    {
        if(slow == fast)
            break;
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
时间复杂度：O(m + n)，m 和 n是两个链表的长度，统计长度各遍历了一次链表，第二次遍历链表最多是两个链表各自的长度。
空间复杂度：O(1)，没有使用额外空间。
    
方法2：双指针  a + b + c爱情相遇
1.每步操作需要同时更新指针pA和pB。
2.如果指针pA不为空，则将指针pA移到下一个节点；如果指针pB不为空，则将指针pB移到下一个节点。
3.如果指针pA为空，则将指针pA移到链表headB的头节点；如果指针pB为空，则将指针pB移到链表headA的头节点。
4.当指针pA和pB指向同一个节点或者都为空时，返回它们指向的节点或者NULL。
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    //a + b + c爱情相遇法
    struct ListNode *pA = headA, *pB = headB;
    //题目是链表不为空
	/*
	//和下面写法一样
	while(A!=B)
    {
        if(A == NULL)
            A = headB;
        else
            A = A->next;
        if(B == NULL)
            B = headA;
        else
            B = B->next; 
    }
	*/
    
    //两个头结点同时遍历两个链表，如果为空就指向另外一个链表的头结点，直到两个节点的地址相等。
    //地址相等有两种情况，一种是地址相等非空，表明有相交节点。
    //另一种是两个节点的地址同时为空，表明两个链表不相交。
    while (pA != pB) {
        pA = pA == NULL ? headB : pA->next;     //注意不要将headB写成pB
        pB = pB == NULL ? headA : pB->next;
    }
    return pA;
}
时间复杂度：O(m + n)，m 和 n是两个链表的长度，最多需要两个指针各自遍历两个链表一次。
空间复杂度：O(1)，没有使用额外空间。

方法3：哈希集合
1.首先遍历链表headA，并将链表headA中的每个节点加入哈希集合中。然后遍历链表headB，对于遍历到的每个节点，判断该节点是否在哈希集合中；
2.如果当前节点不在哈希集合中，则继续遍历下一个节点；
3.如果当前节点在哈希集合中，则后面的节点都在哈希集合中，即从当前节点开始的所有节点都在两个链表的相交部分，因此在链表headB中遍历到的第一个在哈希集合中的节点就是两个链表相交的节点，返回该节点。
4.如果链表headB中的所有节点都不在哈希集合中，则两个链表不相交，返回NULL。
struct HashTable {
    struct ListNode *key;
    UT_hash_handle hh;
};

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct HashTable *hashTable = NULL;
    struct ListNode *temp = headA;
    while (temp != NULL) {
        struct HashTable *tmp;
        HASH_FIND(hh, hashTable, &temp, sizeof(struct HashTable *), tmp);
        if (tmp == NULL) {
            tmp = malloc(sizeof(struct HashTable));
            tmp->key = temp;
            HASH_ADD(hh, hashTable, key, sizeof(struct HashTable *), tmp);
        }
        temp = temp->next;
    }
    temp = headB;
    while (temp != NULL) {
        struct HashTable *tmp;
        HASH_FIND(hh, hashTable, &temp, sizeof(struct HashTable *), tmp);
        if (tmp != NULL) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
时间复杂度：O(m + n)，m 和 n是两个链表的长度，需要遍历两个链表各一次。
空间复杂度：O(m)，m是链表headA的长度，需要使用哈希集合存储链表headA的全部节点。

方法4：将链表headA组环，判断链表headB有没有环
1.找到链表headA的最后一个节点，将链表headA组成环；
2.判断链表headB是否有环，如果有环说明两个链表是相交的，如果没环说明两个链表不相交；
3.将链表headA拆环。
//将其中一个链表变成环，判断另外一个链表有没有环，最后不要忘记拆环
struct ListNode * hasCycle(struct ListNode *head) {
    //快慢指针判断链表是否有环，返回快慢指针相等的节点
    struct ListNode* slow,*fast;
    slow = fast = head;
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
            return fast;    //有环，第一个相遇的节点
    }

    return NULL;
}

struct ListNode *detectCycle(struct ListNode *head) {
    //如果链表有环，找到进环的节点
    if(head == NULL || head->next == NULL)
        return NULL;
    
    struct ListNode * node = hasCycle(head);    //第一个相遇的节点

    while(node && head)
    {
        //要是不相交（没环），head为NULL结束循环
        if(node == head)
        {
            return node;   //相交的节点
        }
        node = node->next;
        head = head->next;
    } 

    return NULL;
}

 struct ListNode* getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    //将其中的一个链表转换为环形链表，就是求另外一个链表是不是环形链表，是的话就有相交节点；
    
    //1.记录最后一个节点
    struct ListNode* cur = headA ;
    while(cur->next != NULL)
    {
         cur = cur->next;
    }
 
    struct ListNode* tmp = cur;   //最后一个节点
    tmp->next = headA;   //第一个链表变成圈
    
    //2.判断第二个链表是否有环
    //3.从相交的节点和第二个的头结点同时遍历找到相交的节点，就是第一个相交的节点
    
    struct ListNode* tmp1 = detectCycle(headB);

    //4.拆环
    cur->next = NULL;
    return tmp1;     
}
时间复杂度：O(2m + n)，也就是O(m + n)，m 和 n是链表的节点。
空间复杂度：O(1)，没有使用额外空间。
```

## 141.环形链表

题目：给你一个链表的头节点 head ，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。

如果链表中存在环 ，则返回 true 。 否则，返回 false 。

![image-20230511090920289](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230511090920289.png)

**提示：**

- 链表中节点的数目范围是 `[0, 104]`

- `-105 <= Node.val <= 105`

- `pos` 为 `-1` 或者链表中的一个 **有效索引** 。

  ```c
  方法1：快慢指针
  1.快指针一次走两步，慢指针一次走一步，都初始化为头结点；
  2.遍历快指针，如果快指针和慢指针相等表明有环，如果快指针为空表明没环。
  bool hasCycle(struct ListNode *head) {
      struct ListNode* slow = head;
      struct ListNode* fast = head;
      while(fast && fast->next)
      {
          slow = slow->next;
          fast = fast->next->next;
          if(slow == fast)
              return true;
      }
      return false;
  }
  时间复杂度：O(n)，n是链表的节点数，最少遍历一轮链表。
  空间复杂度：O(1)，没有使用额外空间。
   
  方法2：利用题目链表个数有限漏洞（也可以利用题目链表节点的取值范围）
  bool hasCycle(struct ListNode *head) {
      //利用题目个数有限漏洞
      int len =0;
      while(head)
      {
          head = head->next;
          ++len;
          if(len > 10000)
              return true;
      }  
      return false;
  }
  时间复杂度：O(n)，n是链表节点个数，最少遍历链表所有节点一次。
  空间复杂度：O(1)，没有使用额外空间。
  
  方法3：见缝插针（会损坏链表结构）
  1.在堆区开辟一个空间；
  2.遍历链表，让链表中的所有节点都指向在堆区开辟的空间；
  3.如果遍历到循环入口的节点，如果指向是堆区的空间那么表示有环，如果遍历到链表结尾是NULL表示没有换。
  bool hasCycle(struct ListNode *head) {
      //创建一个节点，改变链表的结构     把链表结构变成一个见缝插针的模型
      struct ListNode* temp = (struct ListNode*)malloc(sizeof(struct ListNode));
      
      temp->next = NULL;  //创建一个新的变量，必须初始化指向，可以不初始化值
      bool res = false;
  
      struct ListNode* current = head;
      while(current != NULL)
      {
          if(current->next == temp)
          {
              res = true;
              break;
          }
          struct ListNode* next = current->next;
          current->next = temp;
          current = next;   
      }
      
      //free(temp);       //不能释放，原因是释放之后会造成野指针
      return res; 
  }
  时间复杂度：O(n)，n是链表的长度，会遍历一次链表。
  空间复杂度：O(1)，使用了常数级的额外空间。
      
  方法4：哈希表（最容易想到的方法是遍历所有节点，每次遍历到一个节点时，判断该节点此前是否被访问过。）
  1.使用哈希表来存储所有已经访问过的节点；
  2.每次我们到达一个节点，如果该节点已经存在于哈希表中，则说明该链表是环形链表，否则就将该节点加入哈希表中。重复这一过程，直到我们遍历完整个链表即可。 
  struct hashTable {
      struct ListNode* key;
      UT_hash_handle hh;
  };
  
  struct hashTable* hashtable;
  
  struct hashTable* find(struct ListNode* ikey) {
      struct hashTable* tmp;
      HASH_FIND_PTR(hashtable, &ikey, tmp);
      return tmp;
  }
  
  void insert(struct ListNode* ikey) {
      struct hashTable* tmp = malloc(sizeof(struct hashTable));
      tmp->key = ikey;
      HASH_ADD_PTR(hashtable, key, tmp);
  }
  
  bool hasCycle(struct ListNode* head) {
      hashtable = NULL;
      while (head != NULL) {
          if (find(head) != NULL) {
              return true;
          }
          insert(head);
          head = head->next;
      }
      return false;
  }
  时间复杂度：O(n)，n是链表的节点数，最坏情况下遍历了链表每个节点一次。
  空间复杂度：O(n),n是链表的节点数，最坏情况下将每个节点插入到哈希表中一次。
  ```


## 142.环形链表ll

题目：给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

不允许修改链表。 

![image-20230511131516831](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230511131516831.png)

**提示：**

- 链表中节点的数目范围在范围 `[0, 104]` 内
- `-105 <= Node.val <= 105`
- `pos` 的值为 `-1` 或者链表中的一个有效索引

```c
方法1：快慢指针
1.先判断链表有环没，有环返回快慢指针第一次相遇的节点，没环返回NULL；
2.再同时遍历快慢指针第一次相遇的节点和头结点，直到两个节点相等，就是入环的节点。（原理：画图可以得出）
//判断链表是否有环，有环返回节点，没环返回NULL
struct ListNode* hasCycle(struct ListNode *head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
            return fast;
    }
    return NULL;
}

struct ListNode *detectCycle(struct ListNode *head) {
    //if(head == NULL || head->next == NULL)
    //    return NULL;
    //快慢指针
    struct ListNode* node = hasCycle(head); //环中的某一个节点
    struct ListNode* cur = head;
    while(node)
    {
        //判断地址 注意判断和遍历的先后顺序，有可能第一个节点就是相等的节点。（避免出现返回相交的第一个节点不对的情况）
        //比如示例2
        if(node == cur)
            return node;
        node = node->next;
        cur = cur->next;
    }
    return NULL;
}
时间复杂度：O(n)，n是链表的节点个数。
空间复杂度：O(1)，没有使用额外空间。
    
方法2：哈希表
1.遍历链表中的每一个节点，记录到哈希表中；
2.遍历遇到以前遍历过的节点就是入环的节点，没环就会遍历到NULL。
struct hashTable {
    struct ListNode* key;
    UT_hash_handle hh;
};

struct hashTable* hashtable;

struct hashTable* find(struct ListNode* ikey) {
    struct hashTable* tmp;
    HASH_FIND_PTR(hashtable, &ikey, tmp);
    return tmp;
}

void insert(struct ListNode* ikey) {
    struct hashTable* tmp = malloc(sizeof(struct hashTable));
    tmp->key = ikey;
    HASH_ADD_PTR(hashtable, key, tmp);
}

struct ListNode* detectCycle(struct ListNode* head) {
    hashtable = NULL;
    while (head != NULL) {
        if (find(head) != NULL) {
            return head;
        }
        insert(head);
        head = head->next;
    }
    return false;
}
时间复杂度：O(n)，n是链表中节点的数目，遍历链表中的每一个节点。
空间复杂度：O(n)，n是链表中节点的数目，遍历将链表中的每一个节点保存到哈希表中。
```

## 138.复制带随机指针的链表

题目：给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

构造这个链表的深拷贝。深拷贝应该正好由 n 个全新节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。

返回复制链表的头节点。

用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

val：一个表示 Node.val 的整数。
random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
你的代码只接受原链表的头节点 head 作为传入参数。

![image-20230512041312314](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230512041312314.png)

**示：**

`0 <= n <= 1000`

-104 <= Node.val <= 104`

Node.random` 为 `null或指向链表中的节点。

```c
方法1：节点拆分
1.拷贝链表的值和next；
2.拷贝链表的random；
3.拆分链表。
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

struct Node* copyRandomList(struct Node* head) {
    if(head == NULL)
        return head;
    struct Node* cur = head;
    //将拷贝的节点放在别拷贝节点的后面
    while(cur)
    {
        struct Node* newnode= (struct Node*)malloc(sizeof(struct Node));
        //拷贝数据
        newnode->val = cur->val;
        //cur newnode cur->next 按顺序进行连接
        newnode->next = cur->next;
        cur->next = newnode;
        cur = newnode->next;
    }

    cur = head;
    //拷贝随机指针
    while(cur)
    {
        //避免随机指针是NULL
        if(cur->random)
            cur->next->random = cur->random->next;
        else
            cur->next->random = NULL;
        cur = cur->next->next;
    }

    struct Node* copyhead = head->next;
    cur = head;
    //拆分链表
    while(cur)
    {
        struct Node* copy = cur->next;
        cur->next = copy->next;
        cur = cur->next;
        if(cur)
            copy->next = cur->next;
        //else
        //    copy->next = NULL;  //最后一个节点      //这个可以不写，因为最后一个copy的指向是NULL
    }
    
    /*
    //拆分链表
    while(cur)
    {
        //这个好理解一点
        struct Node* copy = cur->next;
        struct Node* next = copy->next; //next可能不存在
        cur->next = next;
        if(next)
            copy->next = next->next;
        else
            copy->next = NULL;  //最后一个节点
        cur = next;
    }
    */
    return copyhead;
}
时间复杂度：O(n)，n是链表的节点个数，遍历了链表3次。
空间复杂度：O(1)，返回值不计入空间复杂度。
    
方法2：哈希表和回溯
struct HashTable {
    struct Node *key, *val;
    UT_hash_handle hh;
} * cachedNode;

struct Node* deepCopy(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }
    struct HashTable* tmp;
    HASH_FIND_PTR(cachedNode, &head, tmp);
    if (tmp == NULL) {
        struct Node* headNew = malloc(sizeof(struct Node));
        headNew->val = head->val;
        tmp = malloc(sizeof(struct HashTable));
        tmp->key = head, tmp->val = headNew;
        HASH_ADD_PTR(cachedNode, key, tmp);
        headNew->next = deepCopy(head->next);
        headNew->random = deepCopy(head->random);
    }
    return tmp->val;
}

struct Node* copyRandomList(struct Node* head) {
    cachedNode = NULL;
    return deepCopy(head);
}
时间复杂度：O(n)，n是链表的长度。对于每个节点，我们至多访问其「后继节点」和「随机指针指向的节点」各一次，均摊每个点至多被访问两次。
空间复杂度：O(n)，n是链表的长度，为哈希表的空间开销。
```

## 147.对链表进程插入排序

题目：给定单个链表的头 head ，使用 插入排序 对链表进行排序，并返回 排序后链表的头 。

插入排序 算法的步骤:

插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。
每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。
重复直到所有输入数据插入完为止。
下面是插入排序算法的一个图形示例。部分排序的列表(黑色)最初只包含列表中的第一个元素。每次迭代时，从输入数据中删除一个元素(红色)，并就地插入已排序的列表中。

对链表进行插入排序。 

```c
示例1：
输入: head = [4,2,1,3]
输出: [1,2,3,4]
示例2：
输入: head = [-1,5,3,4,0]
输出: [-1,0,3,4,5]

提示：
列表中的节点数在 [1, 5000]范围内
-5000 <= Node.val <= 5000
```

```c
插入排序：在已近排好序的序列中插入元素。
方法1：不是哑结点的
1.链表的插入：假设第一个节点是有序的，要插入的节点是从第二个开始的，每次与最后一个节点进行比较，确定要不要插入；
2.要插入的话从头开始遍历，找到一个值大于自己的节点，插入到前边。
struct ListNode* insertionSortList(struct ListNode* head){
    //插入排序步骤：
    //在已近排好序的序列中，插入新的数据
    //第一个数据是有序的
    //插入过程：待插入的数据从有序序列的最后一个位置开始向前遍历，找到一个要插入数据小或者等于的数据
    //待插入的数据放入此数据的后面。
    //单链表是从头往后开始遍历 不能从后向前遍历.
    
  //  if(!head || !head->next)
  //      return head;          //题目规定最少1个节点

    //链表的插入排序是从前往后找，找到一个比他大的数据停止，插入到这个数据的前面。前面的数据小于等于自己。
    struct ListNode* tail = head,*cur = head->next,* prev ,*node = head;      //cur可以是head，指针可以不赋初值
    //tail:排好序数据的尾节点  cur：当前遍历的节点 prev：标记，判断要不要改变头结点 node：要插入位置的后一个节点
    while(cur)
    {
        if(cur->val < tail->val)   //与最后一个节点相比，小的话进行插入，不小的话移动tail和cur
        {
            //插入
            prev = NULL;
            node = head;    //每次重置
            //找到要插入的位置
            while(node && node->val <= cur->val)    //这里的条件可以不写node，node每次都是存在的(最少一个节点)
            {
                prev = node;
                node = node->next;
            }
            //prev cur node
            tail->next = cur->next;
            cur->next = node;
            if(prev)                //prev为NULL的时候就是在头结点处插入元素，要更新头结点。
                prev->next = cur;   //不为NULL就是在中间节点进行插入操作。 
            else
                head = cur;         //更新头节点
        }
        else
        {
            //不插入:需要移动排好序的元素的尾节点的指向
            tail = cur;
            //cur = cur->next;
        }
        cur = tail->next;  //移动cur
    }

    return head; 
}
时间复杂度：O(n * n)，遍历链表一次，每次插入一个元素要寻找插入的位置，需要遍历一次链表。
空间复杂度：O(1)，没有使用额外空间。

方法2：哑结点	  方便头的插入
struct ListNode* insertionSortList(struct ListNode* head)
{
    struct ListNode* dummyhead = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyhead->next = head;
    struct ListNode* cur = head->next, *tail = head, *prev = dummyhead;
    while(cur)
    {
        prev = dummyhead;
        if(tail->val > cur->val)
        {
            while(prev->next->val < cur->val)
            {
                //插入元素 
                prev = prev->next;
            }
            //prev cur prev->next
            tail->next = cur->next;
            cur->next = prev->next;
            prev->next = cur;
        }
        else
        {
            //不需要插入元素
            tail = cur;
        }
        cur = tail->next;
    }
    struct ListNode* newnode = dummyhead->next;
    free(dummyhead);
    return newnode;
}
时间复杂度：O(n * n)，遍历链表一次，每次插入一个元素要寻找插入的位置，需要遍历一次链表。
空间复杂度：O(1)，哑结点使用了常数级的额外空间。
```

## 82.删除排序链表中的重复元素ll

题目：给定一个已排序的链表的头 `head` ， *删除原始链表中所有重复数字的节点，只留下不同的数字* 。返回 *已排序的链表* 。

```c
示例1：
输入：head = [1,2,3,3,4,4,5]
输出：[1,2,5]
示例2：
输入：head = [1,1,1,2,3]
输出：[2,3]

提示：
链表中节点数目在范围 [0, 300] 内
-100 <= Node.val <= 100
题目数据保证链表已经按升序排列
```

```c
方法1：不使用哑结点
1.cur是遍历的节点，prev是遍历的节点的前一个节点，删除的时候prev的next指向遍历的节点的下一个节点；
2.如果cur->val和cur->next->val相等，就要删除，不相等就不删除（prev指向cur，cur指向下一个节点，prev修改表明之后删除不是在头元素删除元素了）；
3.删除分为头结点的删除和不是头结点的删除，如果prev的值NULL是头结点的删除，要更新头，不是NULL就是中间节点的删除，不需要更新头；
3.1删除头：要删除的节点记为x，在cur存在的情况下cur->val和x相等，就删除头结点，把头结点和cur指向下一个，重复3.1直到cur的val不等于x；
3.2不删除头：要删除的节点记为x，在cur存在的情况下cur->val和x相等，prev的next指向cur的next节点。
struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if(head == NULL)
        return head;
    //不使用哑结点
    struct ListNode* cur = head, *prev = NULL;
    while(cur && cur->next)
    {
        if(cur->val == cur->next->val)
        {
            int x = cur->val;
         	//删除的过程
            while(cur && cur->val == x)
            {
                struct ListNode* node = cur;
                cur = cur->next;
                free(node);
                if(prev == NULL)
                    head = cur;
                else
                    prev->next = cur;
            }
        }
        else
        {
            //不删除
            prev = cur;
            cur = cur->next;
        }
    }
    return head;
}
时间复杂度：O(n)，n是链表的节点个数。
空间复杂度：O(1)，没有使用额外空间。

方法2：哑结点
1.创建一个哑结点，哑结点的next指向head；
2.指针cur指向哑结点，进行遍历；
3.如果cur->next->val和cur->next->next->val相等就删除，否则遍历下一个节点；
4.删除的过程：用x记录下要删除的节点的值，把和x相等的值从第一个到最后一个都删除，知道那个值不等于x；
5.最后可能只存在一个元素（cur->next），cur->next->next指向的元素为NULL，但最后一个元素没被删除说明最后一个元素和删除的前一个元素不相等，没必要循环判断了；
6.最后用newhead指向哑结点的next，释放哑结点，返回newhead。
struct ListNode* deleteDuplicates(struct ListNode* head){
    if(head == NULL)
        return head;
    struct ListNode* dummyhead = (struct ListNode*)malloc(sizeof(struct ListNode));     //哑结点避免头的更新
    dummyhead->next = head;
    struct ListNode* cur = dummyhead;
    while(cur->next && cur->next->next)
    {
        if(cur->next->val == cur->next->next->val)
        {
            //删除
            int x = cur->next->val;
            while(cur->next && cur->next->val == x)
            {
                struct ListNode* next = cur->next;
                cur->next = cur->next->next;
                free(next);
            }
        }
        else
        {
            //不删除
            cur = cur->next;
        }
    }
    struct ListNode* newhead = dummyhead->next;
    free(dummyhead);
    return newhead;
}
时间复杂度：O(n)，n是链表的节点个数。
空间复杂度：O(1)，哑结点使用了常数级的额外空间。
    
方法3：递归
正确的过程：head->val和head->next->val相等就找到一个val不相等的节点返回（作为头结点），不相等头结点的next指向下一个递归函数，参数变为head->next。
//刚开始写的代码是这个	这个代码保留了重复数字中的一个
比如:
输入:[1,2,2,3,4,4,4,5]
输出:[1,2,3,4,5]
预期结果:[1,3,5]
struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    if(head->val != head->next->val)
        head->next = deleteDuplicates(head->next);
    else
        head = deleteDuplicates(head->next);
    return head;
}
//修改之后：
struct ListNode* deleteDuplicates(struct ListNode* head)
{
    //递归的最小结果
    if(head == NULL || head->next == NULL)
        return head;
    
    //递归过程
    if(head->val != head->next->val)
        head->next = deleteDuplicates(head->next);
    else
    {
        struct ListNode* cur = head->next->next;
        while(cur && cur->val == head->val)
            cur = cur->next;
        head = deleteDuplicates(cur);             //写成这个也可以return deleteDuplicates(cur); 都是修改本层递归的头结点
    }
    return head;
}
时间复杂度：O(n)，n是链表节点的个数，递归的时候刚好遍历了一遍链表。
空间复杂度：O(n)，递归的层数（栈）最多是链表的节点个数（相等的节点只递归一次），n是链表的节点个数。
    
方法4：字典树
```

## 83.删除排序链表中的重复元素

给定一个已排序的链表的头 `head` ， *删除所有重复的元素，使每个元素只出现一次* 。返回 *已排序的链表* 。

```c
示例1：
输入：head = [1,1,2]
输出：[1,2]
示例2：
输入：head = [1,1,2,3,3]
输出：[1,2,3]

提示：
链表中节点数目在范围 [0, 300] 内
-100 <= Node.val <= 100
题目数据保证链表已经按升序 排列
通过次数573,313提交次数1,079,575
```

```
方法1：遍历
struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    struct ListNode* cur = head;
    while(cur && cur->next)
    {
        if(cur->val == cur->next->val)
        {
            struct ListNode* next = cur->next;
            cur->next = cur->next->next;
            free(next);
        }
        else
        {
            cur = cur->next;
        }
    }   
    return head;
}
时间复杂度：O(n)，n是链表的节点的个数，遍历了一次链表。
空间复杂度：O(1)，没有使用额外空间。

方法2：递归
struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    if(head->val != head->next->val)
        head->next = deleteDuplicates(head->next);
    else
        head = deleteDuplicates(head->next);
    return head;
}
时间复杂度：O(n)，n是链表的节点的个数，遍历了链表的全部节点。
空间复杂度：O(n)，n是链表的节点的个数，递归了n层，使用了n个栈帧。
```

## 19.删除链表中倒数第K个结点

题目：给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。

```c
示例1：
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]

示例2：
输入：head = [1], n = 1
输出：[]

示例3：
输入：head = [1,2], n = 1
输出：[1]

提示：
链表中结点的数目为 sz
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
进阶：你能尝试使用一趟扫描实现吗？
```

```c
方法1：

```

## 328.奇偶链表

题目：给定单链表的头节点 head ，将所有索引为奇数的节点和索引为偶数的节点分别组合在一起，然后返回重新排序的列表。

第一个节点的索引被认为是 奇数 ， 第二个节点的索引为 偶数 ，以此类推。

请注意，偶数组和奇数组内部的相对顺序应该与输入时保持一致。

你必须在 O(1) 的额外空间复杂度和 O(n) 的时间复杂度下解决这个问题。 

```c
示例1：
输入: head = [1,2,3,4,5]
输出: [1,3,5,2,4]

示例2：
输入: head = [2,1,3,5,6,4,7]
输出: [2,3,6,7,1,5,4]

提示:
n ==  链表中的节点数
0 <= n <= 104
-106 <= Node.val <= 106
```

```c
方法1：


```

## 148.排序链表

题目：给你链表的头结点 `head` ，请将其按 **升序** 排列并返回 **排序后的链表** 。

```c
示例1：
输入：head = [4,2,1,3]
输出：[1,2,3,4]

示例2：
输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]

示例3：
输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]

提示：
链表中节点的数目在范围 [0, 5 * 104] 内
-105 <= Node.val <= 105
进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
    
时间复杂度O(nlogn)的排序算法有四种，分别是希尔排序，堆排序，快速排序和归并排序。这四个排序都非常重要。
稳定性：希尔排序、堆排序、快速排序是不稳定的，归并排序是稳定的。
```

```c
方法1：
```

## 2.两数相加

题目：给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

```c
示例1：
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807.

示例2：
输入：l1 = [0], l2 = [0]
输出：[0]

示例3：
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]

提示：
每个链表中的节点数在范围 [1, 100] 内
0 <= Node.val <= 9
题目数据保证列表表示的数字不含前导零
```

```c
方法1：
```

## 24.两两交换链表中的节点

题目：给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

```c
示例1：
输入：head = [1,2,3,4]
输出：[2,1,4,3]

示例2：
输入：head = []
输出：[]

示例3：
输入：head = [1]
输出：[1]

提示：

链表中节点的数目在范围 [0, 100] 内
0 <= Node.val <= 100
```

```c
方法1：迭代	使用哑结点
struct ListNode* swapPairs(struct ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    struct ListNode* dummyhead = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyhead->next = head;
    struct ListNode* cur = dummyhead;
    while(cur->next && cur->next->next)
    {
        struct ListNode* nextnext = cur->next->next;
        cur->next->next = nextnext->next;       //1指向3        3和4改变指向后就是1指向4
        nextnext->next = cur->next;             //2指向1
        cur->next = nextnext;                   //虚拟头结点指向2 
        cur = cur->next->next;                  //虚拟头结点更新
    }
    struct ListNode* newhead = dummyhead->next;
    free(dummyhead);
    return newhead;
}
时间复杂度：O(n)，n是链表的节点数量，需要对每个节点进行更新指针的操作。
空间复杂度：O(1)，哑结点使用了常数级别的空间。
  
方法2：细小处理	不使用堆开辟的哑结点，逻辑思路和方法1一样
struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode dummyHead;
    dummyHead.next = head;
    struct ListNode* cur = &dummyHead;
    while(cur->next && cur->next->next)
    {
        struct ListNode* nextnext = cur->next->next;
        cur->next->next = nextnext->next;       //1指向3        3和4改变指向后就是1指向4
        nextnext->next = cur->next;             //2指向1
        cur->next = nextnext;                   //虚拟头结点指向2 
        cur = cur->next->next;                  //虚拟头结点（遍历指针）更新
    }
    return dummyHead.next;
}
    
方法2：递归
1.终止条件：链表中没有节点或者只有1个节点；
2.递归过程：第二个节点是新的头结点，要指向swapPairs函数参数为第三个节点开始的链表的返回值，返回值就是第四个节点，第二个节点（头结点）指向第一个节点，第一个节点指向第四个节点，第四个节点指向第三个节点；
3.返回值：链表中的第二个节点作为新的头结点。
struct ListNode* swapPairs(struct ListNode* head)
{
    //递归
    //返回  只剩一个节点不交换
    if(head == NULL || head->next == NULL)
        return head;
    //过程  连接
    struct ListNode* newhead = head->next;
    head->next = swapPairs(newhead->next);
    newhead->next = head;
    return newhead;
}
时间复杂度：O(n)，n是链表的节点数量，需要对每个节点进行更新指针的操作。
空间复杂度：O(n)，n是链表的节点数量，空间复杂度主要取决于递归调用的栈空间。

方法3：栈	java实现的，c没有现成的栈，太麻烦了
1.过程借助栈先进后出的特性每次从链表中拿出两个节点放入栈中，再从栈中拿出两个节点放入要返回的链表中；
2.注意点：原链表中遍历的节点更新要早于从栈中取出节点插入要返回的链表，因为从栈中取出节点插入要返回的链表中会改变链表的指向，造成环。
class Solution {
	public ListNode swapPairs(ListNode head) {
		if(head==null || head.next==null) {
			return head;
		}
		//用stack保存每次迭代的两个节点
		Stack<ListNode> stack = new Stack<ListNode>();
		ListNode dummy = new ListNode(-1);
		ListNode cur = head;
		//head指向新的p节点，函数结束时返回head.next即可
		head = dummy;
		while(cur!=null && cur.next!=null) {
			//将两个节点放入stack中
			stack.add(cur);
			stack.add(cur.next);
			//当前节点往前走两步    这一步只能写在这，因为后面改变了指向
			cur = cur.next.next;
			//从stack中弹出两个节点，然后用p节点指向新弹出的两个节点
			dummy.next = stack.pop();
			dummy = dummy.next;
			dummy.next = stack.pop();
			dummy = dummy.next;
		}
		dummy.next = cur;   //处理剩余节点  忘记这一步后面节点会产生环
		return head.next;
	}
}
时间复杂度：O(n)，n是链表的节点数量，需要对每个节点进行更新指针的操作（遍历链表）。
空间复杂度：O(1)，栈消耗了两个空间，哑结点消耗了一个空间，都是常数级的空间。

方法4：奇偶计数器	先拆成两个链表，再合并，太麻烦了
方法5：变成数组
```

## 25.k个一组翻转链表

题目：给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。

k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

```c
示例1：
输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]
示例2：
输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5]
示例3：
输入：head = [1,2,3,4,5], k = 1
输出：[1,2,3,4,5]

提示：
链表中的节点数目为 n
1 <= k <= n <= 5000
0 <= Node.val <= 1000
```

```c
方法1：迭代 + 头插法翻转链表
1.记录要翻转链表的头尾结点，和头结点的前驱节点，和尾节点的后继节点；
2.前驱节点连接翻转链表之后的头结点，翻转之后的尾节点连接后继节点，更新节点。
//链表翻转  头插法
struct ListNode* reverselist(struct ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    struct ListNode* cur = head, *newhead = NULL;
    while(cur)
    {
        struct ListNode* next = cur->next;
        cur->next = newhead;
        newhead = cur;
        cur = next;
    }
    return newhead;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k){
    struct ListNode* dummyhead = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyhead->next = head;
    struct ListNode* cur = head;    		//准备要翻转链表的头结点
    struct ListNode* tail = dummyhead;		//准备要翻转链表的尾节点
    struct ListNode* prev = dummyhead;		//准备翻转链表头结点的前一个节点
    while(cur)
    {
        //记录链表区间的尾节点
        for(int i = 0; i < k; i++)
        {
            tail = tail->next;
            if(tail == NULL)
                break;  //跳出for循环
                //return dummyhead->next;     //这里不能使用break，使用break只是跳出了for循环，还在while循环里
        }
        if(tail == NULL)
            break;      //跳出while循环

        //记录翻转的下一个节点
        struct ListNode* tailnext = tail->next;
        tail->next = NULL;      //刚开始忘记切断链表结尾了，造成了死循环
        prev->next = reverselist(cur);      //前边的尾节点连接新的翻转
        cur->next = tailnext;               //当前的尾节点连接下一段翻转之后头结点
        prev = cur;                         //新的准备要翻转的前一个节点
        cur = cur->next;                    //准备翻转的头结点
        tail = prev;                        //记录准备要翻转的尾节点
    }
    
    struct ListNode* newhead = dummyhead->next;
    free(dummyhead);
    return newhead;
}
时间复杂度：O(n)，n是链表的节点数，遍历了一次链表，头插法的时间复杂度是O(k)，k是一次翻转链表的个数。
空间复杂度：O(1)，哑结点消耗的空间都是常数级的。
    
方法2：栈	java实现的，c没有现成的栈，比较麻烦
1.过程：把连续k个节点压入栈中，再取出连续k个节点。（过程比较简单，实现容易出错）
2.注意点：循环退出条件cur不为空的同时count小于k，当k等于1的时候要是没有cur不为空的条件就是死循环，因为最后一个count等于1结束之后的count就是0，之后会造成count一直等于0的死循环；
class Solution {
    public ListNode reverseKGroup(ListNode head, int k) {
        Stack<ListNode> stack = new Stack<ListNode>();
		ListNode dummy = new ListNode(-1);
        dummy.next = head;
        ListNode tail = dummy;
        ListNode cur = head;
        int count = 0;
        while (cur != null && count == 0) 
        {
            //连续k个元素进栈
            while (cur != null && count < k) 
            {
                stack.add(cur);
                cur = cur.next;
                count++;
            }
            if(count == k)
            {
                count = 0; 
                //取出k个元素
                while (!stack.isEmpty())
                {
                    tail.next = stack.pop();
                    tail = tail.next;
                }
                tail.next = cur;	//保证最后一次处理连接不用翻转的剩余元素，最后不进入循环也不用处理尾巴
            }
        }
        return dummy.next;
    }
}
时间复杂度：O(n)，n是链表的节点数，遍历了一次链表
空间复杂度：O(k)，k是要翻转链表的连续节点的个数，哑结点消耗的空间都是常数级的，但栈消耗的空间是O(k)。
    
方法3：递归
//链表翻转  头插法 
struct ListNode* reverselist(struct ListNode* head)
{
    struct ListNode* cur = head, *newhead = NULL;
    while(cur)
    {
        struct ListNode* next = cur->next;
        cur->next = newhead;
        newhead = cur;
        cur = next;
    }
    return newhead;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k)
{
    if(head == NULL)
        return head;
    //递归
    struct ListNode* tail = head;	
    //找到要翻转链表的结尾
    for(int i = 1; i < k; i++)
    {
        tail = tail->next;
        if(tail == NULL)
            return head;
    }
    
    struct ListNode* next = tail->next;
    //断开，避免成环
    tail->next = NULL;
    reverselist(head);
    head->next = reverseKGroup(next, k);
    return tail;
}
时间复杂度：O(n)，n是链表的节点数，遍历了一次链表
空间复杂度：O(k)，n是链表的节点数，递归了n层。

//另一种用头插翻转链表的递归	java写法
class Solution {
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode cur = head;
        int count = 0;
        while (cur != null && count != k)
        {
            //遍历到下一段头节点
            cur = cur.next;
            count++;
        }
        if (count == k) 
        {
            cur = reverseKGroup(cur, k);        //cur等于下一段翻转的新的头节点
            //进行翻转
            while (count != 0) 
            {
                //当前段链表把下一段链表翻转之后的头节点作为新的头插点
                count--;
                ListNode next = head.next;
                head.next = cur;
                cur = head;
                head = next;
            }
            head = cur;
        }
        return head;
    }
}
```





# 4.list的模拟实现

```c++
//#pragma warning(disable:4996)		//忽略4996这个错误
#define _CRT_SECURE_NO_WARNINGS		
//用于取消 Visual Studio 编译器（MSVC）在使用某些标准 C/C++ 函数时产生的安全警告信息
#include <iostream>
#include <string>
#include <algorithm> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

//节点模板
template<class T>
struct __list_node
{
	__list_node(const T& val = T())		//默认是0（类0值）
		:_next(nullptr)
		, _prev(nullptr)
		, _data(val)
	{}

	__list_node<T>* _next;
	__list_node<T>* _prev;
	T _data;
};

//迭代器模板
//例子：template<int, int&, int*> l;
template<class T, class Ref, class Ptr>
struct __list_iterator
{
	typedef __list_node<T> Node;		//节点
	typedef __list_iterator<T, Ref, Ptr> Self;		//自己本身类型

	//构造函数
	__list_iterator(Node* node)			//节点指针
		:_node(node)
	{}

	//*iterator：获取数据本身
	Ref operator*()			//Ref = T&
	{
		return _node->_data;
	}

	//it->_a   看起来是双目运算符，但it可以自动推到出来_a，所以是单目运算符
	//()里面的类型无法确定，返回模板的类型，再去->具体的变量
	Ptr operator->()		//Ptr = T*
	{
		return &_node->_data;
	}

	//返回迭代器本身，不是返回节点
	//前置++
	Self& operator++()
	{
		_node = _node->_next;
		return *this;			//引用返回
	}

	//后置++
	Self operator++(int)
	{
		Self tmp(*this);		//拷贝迭代器
		++(*this);
		return tmp;				//值返回
	}

	//前置--
	Self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	//后置--
	Self operator--(int)
	{
		Self tmp(*this);
		--(*this);
		return tmp;
	}

	bool operator!=(const Self& it)
	{
		//判断成员指针_node是否指向同一个节点
		return _node != it._node;
	}

	bool operator==(const Self& it)
	{
		return _node == it._node;		//这里也可以复用重载的!=运算符
	}

	Node* _node;		//封装节点
};

//list类模板
template<class T>
class my_list {
	typedef __list_node<T> Node;

public:
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;

	iterator begin()
	{
		return iterator(_head->_next);
	}

	iterator end()
	{
		return iterator(_head);
	}

	const_iterator begin() const
	{
		return const_iterator(_head->_next);
	}

	const_iterator end() const
	{
		return const_iterator(_head);
	}

	//构造函数，里面调用自定义节点类的构造函数，初始化值为0
	//第一个节点作为end迭代器，不算做链表中的值，相当于一个虚拟头结点
	//begin迭代器指向头结点的下一个节点，end迭代器指向头结点
	my_list()
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}

	//深拷贝
	my_list(const my_list<T>& l1)
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
		/*
		const_iterator it = l1.begin();
		while (it != l1.end())
		{
			push_back(*it);
			++it;
		}
		*/
		for (auto& e : l1)		//范围for是从begin迭代器遍历到end迭代器 
		{
			push_back(e);
		}
	}

	//赋值运算符重载的现代写法和传统写法
	/*
	my_list<T> operator=(const my_list<T> l1)
	{
		if (*this != l1) {
			clear();
			//const_iterator it = l1.begin();
			for (auto e : l1)
			{
				push_back(e);
			}
		}
		return *this;
	}
	*/

	//深拷贝的逻辑
	my_list<T> operator=(const my_list<T> l1)			//传值拷贝
	{
		swap(_head, l1._head);
		return *this;
	}

	//只留下end迭代器指向的位置，剩下节点全部释放
	void clear()
	{
		iterator it = begin();
		while (it != end())
		{
			//it = erase(it);
			erase(it++);
		}
	}

	iterator erase(iterator pos)
	{
		assert(pos != end());			//不是end迭代器指向的位置才有删除的必要
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* next = cur->_next;
		delete cur;
		prev->_next = next;
		next->_prev = prev;
		return iterator(next);		//返回删除节点的下一个节点的迭代器
	}

	void insert(iterator pos, const T& val)
	{
		//iterator是个对象，对象里面有节点元素
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* newNode = new Node(val);

		prev->_next = newNode;
		newNode->_prev = prev;
		newNode->_next = cur;
		cur->_prev = newNode;
	}

	void push_back(const T& val)
	{
		insert(end(), val);
	}

	void pop_back()
	{
		erase(--end());	//不能使用--end() - 1，原因是list容器不支持随机访问迭代器
	}

	void push_front(const T& x)
	{
		insert(begin(), x);
	}

	void pop_front()
	{
		erase(begin());
	}

	~my_list()
	{
		clear();		//清空之后只剩下虚拟头节点，就是end迭代器指向的位置
		delete _head;
		_head = nullptr;
	}

private:
	Node* _head;		//封装节点
};

void print_list(const my_list<int>& l1)
{
	my_list<int>::const_iterator it = l1.begin();

	while (it != l1.end())
	{
		cout << *it << " ";
		++it;
	}

	cout << endl;
}

struct A
{
	A(int a = 0, int b = 0, int c = 0)
		: _a(a)
		, _b(b)
		, _c(c)
	{}

	int _a;
	int _b;
	int _c;
};

int main()
{
	my_list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	print_list(l1);		//1 2 3 4

	cout << *(l1.end()) << endl;	//0，虚拟头结点的值是默认的类0值

	l1.clear();

	l1.push_front(1);
	print_list(l1);		//1	

	my_list<A> l;
	l.push_back(A());		//0 0 0
	l.push_back(A(1, 1, 1));
	l.push_back(A(2, 2, 2));
	l.push_back(A(3, 3, 3));
	l.push_back(A(4, 4, 4));

	A* ptr = new A(1, 2, 3);
	cout << "_a = " << ptr->_a << " _b = " << ptr->_b
		<< " _c = " << ptr->_c << endl;			//_a = 1 _b = 2 _c = 3

	my_list<A>::iterator it = l.begin();
	while (it != l.end())
	{
		//cout << "_a = " << (*it)._a << " _b = " << (*it)._b
		//	<< " _c = " << (*it)._c << endl;
		//或者
		//cout << "_a = " << it->_a << " _b = " << it->_b
		//		<< " _c = " << it->_c << endl;
		cout << "_a = " << it.operator->()->_a
			<< " _b = " << it.operator->()->_b
			<< " _c = " << it.operator->()->_c << endl;
		//简写，不要使用两个->，编译器识别不了
		cout << "_a = " << it->_a
			<< " _b = " << it->_b
			<< " _c = " << it->_c << endl;
		it++;
	}

	return 0;
}
//输出结果：
//1 2 3 4
//0
//1
//_a = 1 _b = 2 _c = 3
//_a = 0 _b = 0 _c = 0
//_a = 0 _b = 0 _c = 0
//_a = 1 _b = 1 _c = 1
//_a = 1 _b = 1 _c = 1
//_a = 2 _b = 2 _c = 2
//_a = 2 _b = 2 _c = 2
//_a = 3 _b = 3 _c = 3
//_a = 3 _b = 3 _c = 3
//_a = 4 _b = 4 _c = 4
//_a = 4 _b = 4 _c = 4
```



# 5.list和vector的对比

vector与list都是STL中非常重要的序列式容器，由于两个容器的底层结构不同，导致其特性以及应用场景不同。

序列式容器（Sequential Container）是一种在编程中常用的数据结构，用于存储一系列元素并维护它们的顺序。

序列式容器允许按照插入的顺序进行遍历和访问元素。

常见的序列式容器包括：

1. 向量（Vector）：动态数组，支持随机访问和快速在尾部插入/删除元素。
2. 列表（List）：双向链表，支持在任意位置插入/删除元素，但随机访问较慢。
3. 双端队列（Deque）：双向队列，类似向量，支持在头部和尾部插入/删除元素。
4. 队列（Queue）：先进先出（FIFO）的数据结构，通常使用列表或双端队列实现。
5. 栈（Stack）：后进先出（LIFO）的数据结构，通常使用列表实现。

序列式容器提供了一系列操作函数，如插入元素、删除元素、访问元素、迭代器遍历等，使得对数据的操作更加方

便和灵活。选择合适的序列式容器取决于具体的需求，例如需要高效的随机访问时可以选择vector，需要频繁的插

入/删除操作时可以选择list或deque。

C++标准库提供了丰富的序列式容器，如std::vector、std::list、std::deque、std::queue和std::stack等。你可以

根据具体的需求选择合适的容器来处理数据。

|            | vector                                                       | list                                                         |
| ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 底层结构   | 动态顺序表，一段连续空间                                     | 带头结点的双向循环链表                                       |
| 随机访问   | 支持随机访问，访问某个元素效率O(1)                           | 不支持随机访问，访问某个元素效率O(N)                         |
| 插入和删除 | 任意位置插入和删除效率低，需要移动元素，时间复杂度O(N)，插入时有可能需要增容（增容过程：开辟新空间，拷贝元素，释放旧空间，导致效率更低） | 任意位置插入和删除效率高，不需要移动元素，时间复杂度O(1)     |
| 空间利用率 | 底层为连续空间，不容易造成内存碎片，空间利用率高，缓存利用率高 | 底层节点动态开辟，小节点容易造成内存碎片，空间利用率低，缓存利用率低 |
| 迭代器     | 原生态指针                                                   | 对原生态指针（节点指针）进行封装                             |
| 迭代器失效 | 在插入元素时，要给所有的迭代器重新赋值，因为插入元素有可能会导致重新扩容，致使原来的迭代器失效，删除时当前迭代器需要重新赋值否则会失效。 | 删除元素会造成迭代器失效，插入元素不会造成迭代器失效，解决办法就是及时更新迭代器。 |
| 使用场景   | 需要高速存储，支持随机访问，不关心插入删除效率               | 大量插入和删除操作，不关心随机访问                           |

原生态指针（Raw Pointers）是指在编程语言中直接使用的指针类型，它们提供对内存地址的直接访问。原生态

指针通常用于底层的内存操作和与外部系统的交互。

在C++中，使用原生态指针需要谨慎操作，因为它们不提供自动的内存管理和安全检查，容易引发内存泄漏、悬垂

指针等问题。以下是一些与原生态指针相关的注意事项：

1. 内存分配和释放：原生态指针可以使用new运算符手动分配内存，使用delete运算符手动释放内存。但要确保

   在适当的时候释放内存，否则会导致内存泄漏。

2. 空指针检查：在使用原生态指针前，应该进行空指针检查，以避免悬垂指针和访问非法内存。

3. 指针算术：原生态指针可以进行指针算术操作，如指针加减，但要注意边界检查，确保不会越界访问。

4. 引用和解引用：使用*运算符可以解引用原生态指针，获取指针指向的值。通过&运算符可以获取变量的地

   址，得到原生态指针。

5. **指针的所有权和生命周期：原生态指针没有所有权和生命周期的概念，需要开发者手动管理指针的有效性和生**

   **命周期。**

为了减少原生态指针的使用带来的问题，现代C++推荐使用智能指针（Smart Pointers）来进行内存管理。智能指

针提供了更安全、方便的内存管理方式，如std::shared_ptr、std::unique_ptr、std::weak_ptr等。它们通过自动

化的内存释放和引用计数等机制，避免了手动管理原生态指针时的许多问题。



悬垂指针（Dangling Pointer）是指指向已经释放或无效的内存地址的指针。当一个指针指向的内存被释放或销毁

后，该指针仍然保留了原来的值，但这个值不再有效，因此称之为悬垂指针。

使用悬垂指针是一种常见的编程错误，可能导致程序运行时的未定义行为和难以预测的结果。访问悬垂指针可能会

导致程序崩溃、数据损坏、安全漏洞等问题。

悬垂指针通常发生在以下情况下：

1. 释放后未置空：当使用delete或free等方式释放内存后，没有将指针设置为nullptr或null，导致指针仍然保留

   了之前的地址，成为悬垂指针。

2. 堆栈上的引用：函数返回时，将指向局部变量的指针作为返回值返回，但局部变量的生命周期已经结束，导致

   返回的指针成为悬垂指针。

3. 对象销毁后的指针：当一个对象被销毁后，其成员函数中还存在指向该对象的指针，如果继续使用这个指针，

   就会产生悬垂指针。

为了避免悬垂指针的问题，可以采取以下措施：

1. 在释放内存后，将指针置为空指针或nullptr，以避免悬垂指针的产生。

2. 尽量使用智能指针（如std::shared_ptr、std::unique_ptr等）来管理内存，它们可以自动处理内存的释放，避

   免悬垂指针的问题。

3. 在函数返回时，避免返回指向局部变量的指针或引用。

4. 注意对象的生命周期，确保在使用指向对象的指针之前，确保对象仍然有效。