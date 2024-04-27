# 1.vector的介绍

1.vector是表示可变大小数组的序列容器。（单端数组）

2.就像数组一样，vector也采用的连续存储空间来存储元素。也就是意味着可以采用下标对vector的元素进行访

问，和数组一样高效。但是又不像数组，它的大小是可以动态改变的，而且它的大小会被容器自动处理。

3.本质讲，vector使用动态分配数组来存储它的元素。当新元素插入时候，这个数组需要被重新分配大小；为了增

加存储空间。其做法是，分配一个新的数组，然后将全部元素移到这个数组。就时间而言，这是一个相对代价高的

任务，因为每当一个新的元素加入到容器的时候，vector并不会每次都重新分配大小。

4.vector分配空间策略：vector会分配一些额外的空间以适应可能的增长，因为存储空间比实际需要的存储空间更

大。不同的库采用不同的策略权衡空间的使用和重新分配。但是无论如何，重新分配都应该是对数增长的间隔大

小，以至于在末尾插入一个元素的时候是在常数时间的复杂度完成的。

5.因此，vector占用了更多的存储空间，为了获得管理存储空间的能力，并且以一种有效的方式动态增长。

6.与其它动态序列容器相比（deques, lists and forward_lists）， vector在访问元素的时候更加高效，在末尾添

加和删除元素相对高效。对于其它不在末尾的删除和插入操作，效率更低。比起lists和forward_lists统一的迭代器

和引用更好。

7.vector容器的迭代器是支持随机访问的迭代器。



# 2.vector的使用

## 2.1构造函数

```c++
//构造函数
struct A
{
	A(int a = 1,int b = 2)
		:_a(a)
		,_b(b)
	{}
	int _a = 1;
	int _b = 2;
};

ostream& operator<<(ostream& out, const A& aa)
{
	out << " _a = " << aa._a << "  _b = " << aa._b << endl;
	return out;
}

int main()
{
	//1.空vector
	vector<int> v1;
	vector<char> v2;

	//2.vector(n,value);		n：vector容器中的元素个数	value：值
	//内置类型：缺省的值为类0值
	//int:0	float/double:0.0	char:'\0'	指针:nullptr
	vector<int> v3(5);			//括号里面是创建的个数	5个0
	vector<int*> v4(5);
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); ++it)
		cout << *it << " ";		//输出结果：0 0 0 0 0
	cout << endl;

	//自定义类型：缺省值为默认构造创建的对象
	vector<A> v5(8);
	//vector<自定义类型> 变量名(num,构造函数(参数))
	vector<A> v6(5, A(5, 10));

	//3.区间构造
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v7(arr, arr + sizeof(arr)/sizeof(arr[0]));
	//vector<int> v8(arr.begin(), arr.end());		//error，错误原因：表达式必须包含类类型
	string str = "123456";
	vector<char> v9(str.begin(), str.end());

	//拷贝构造
	vector<A> v10(v5);
	for (vector<A>::iterator it = v10.begin(); it != v10.end(); ++it)
		cout << *it << " ";		
	
    return 0;
}
//输出结果：
//0 0 0 0 0
//_a = 1  _b = 2
//_a = 1  _b = 2
//_a = 1  _b = 2
//_a = 1  _b = 2
//_a = 1  _b = 2
//_a = 1  _b = 2
//_a = 1  _b = 2
//_a = 1  _b = 2
```



## 2.2vector容器迭代器

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

//vector的容器迭代器
int main()
{
	string str("12345678");
	vector<char> v(str.begin(),str.end());

	//正向迭代器
	vector<char>::iterator it = v.begin();
	int idx = 0;
	while (it != v.end())
	{
		cout << *it << " ";		//输出结果：1 2 3 4 5 6 7 8
		*it = 'a' + idx;
		++idx;
		++it;
	}
	cout << endl;

	//反向迭代器
	for (vector<char>::const_reverse_iterator crit = v.crbegin(); crit != v.crend(); ++crit)
		cout << *crit << " ";		//输出结果：h g f e d c b a
	cout << endl;

	vector<char>::const_reverse_iterator crit = v.rbegin();
	while (crit != v.rend())
	{
		cout << *crit << " ";		//输出结果：h g f e d c b a
		++crit;
	}
	cout << endl;
	
    return 0;
}
//输出结果：
//1 2 3 4 5 6 7 8
//h g f e d c b a
//h g f e d c b a
```



## 2.3vector容器范围for循环

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

//范围for循环
int main()
{
	string s("123456");
	vector<char> v(s.begin(), s.end());
	for (const auto& ch : v)
		cout << ch << " ";	//输出结果：1 2 3 4 5 6
	cout << endl;

	return 0;
}
//输出结果：
//1 2 3 4 5 6
```



## 2.4max_size()：表示当前vector对象能够容纳的最大元素数量

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

struct B
{
	char a;
};

//max_size()：表示当前vector对象能够容纳的最大元素数量
//max_size 返回的是理论上可容纳的最大元素数量，实际上可能由于各种限制而无法达到这个数值。
int main()
{
	vector<char> v1;
	vector<int> v2;
	vector<int*> v3;
	vector<double> v4;
	vector<B> v5;
	cout << v1.max_size() << endl;	//2147483647	
	//2147483647 是一个整数，它是 int 类型的最大值（如果使用32位有符号整数表示）。
	cout << v2.max_size() << endl;	//1073741823
	cout << v3.max_size() << endl;	//1073741823
	cout << v4.max_size() << endl;	//536870911
	cout << v5.max_size() << endl;	//178956970		这个数字是不确定的，取决于自定义类型。
	
	return 0;
}
//输出结果：
//2147483647
//1073741823
//1073741823
//536870911
//2147483647
```



## 2.5vector容器容量操作

capacity的代码在vs和g++下分别运行会发现，vs下capacity是按1.5倍增长的，g++是按2倍增长的。

这个问题经常会考察，不要固化的认为，顺序表增容都是2倍，具体增长多少是根据具体的需求定义的。vs是PJ版

本STL，g++是SGI版本STL。

reserve只负责开辟空间，如果确定知道需要用多少空间，reserve可以缓解vector增容的代价缺陷问题。（分配内

存，不初始化，不能访问；）

resize在开空间的同时还会进行初始化，影响size。  

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

//capacity	size	resize	reserve  empty	shrink_to_fit
int main()
{
	string s;
	vector<char> v(s.begin(), s.end());
	//string有效元素个数和容量
	cout << s.capacity() << endl;		//15
	cout << s.size() << endl;			//0
	//vector有效元素个数和容量
	cout << v.capacity() << endl;		//0
	cout << v.size() << endl;			//0

	//增大到有效元素的个数，改变size，如果增加到有效元素的个数大于容量就会改变capacity，否则不改变
	v.resize(10);
	cout << v.capacity() << endl;		//10
	cout << v.size() << endl;			//10

	//减小到有效元素的个数，改变size，不改变capacity
	v.resize(8);
	cout << v.capacity() << endl;		//10
	cout << v.size() << endl;			//8

	//减小到容量大小，不改变size和capacity
	v.reserve(5);
	cout << v.capacity() << endl;		//10
	cout << v.size() << endl;			//8

	//增加到容量大小，改变capacity，不改变size
	v.reserve(15);			//预留空间
	cout << v.capacity() << endl;		//15
	cout << v.size() << endl;			//8

	//总结：resize在缩小有效元素数量时，改变size，不改变capacity；
	//总结：resize在增大有效元素数量时，改变size，可能会改变capacity；
	//总结：reserve在缩小容量时，不改变size，也不改变capacity；
	//总结：reserve在增大容量时，不改变size，只改变capacity；

	v.shrink_to_fit();	//请求将 vector 对象的容量缩小为其当前元素数量
	cout << v.capacity() << endl;		//8
	cout << v.size() << endl;			//8	
	//shrink_to_fit将capacity缩减到和size一样
	//只有当容器的大小超过容量时，才会真正发生内存的释放和重新分配。
	//因此，在实际使用中，shrink_to_fit 并不能保证一定会缩减容器的内存使用。

	if (v.empty())		//返回值：返回1表示空的，返回0表示不是空的。
		cout << "empty容器是空的" << endl;
	else
		cout << "empty容器不是空的" << endl;	//empty容器不是空的

	return 0;
}
//输出结果：
//15
//0
//0
//0
//10
//10
//10
//8
//10
//8
//15
//8
//8
//8
//empty容器不是空的
```



## 2.6vector容器增删查改

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

//[] at	front back 
//data：获取vector容器的存放元素空间的首地址
int main()
{
	string str = "123456";
	vector<char> v(str.begin(), str.end());
	for (size_t i = 0; i < v.size(); ++i)
	{
		//cout << v.operator[](i) << " ";
		cout << v[i] << " ";	//1 2 3 4 5 6
	}
	cout << endl;

	//at和[]的区别
	cout << v.front() << endl;		//1
	cout << v.back() << endl;		//6

	char* ptr = v.data();		//获取vector容器的存放元素空间的首地址
	ptr[0] = '8';
	for (int i = 0; i < v.size(); i++)
		cout << ptr[i] << " ";		//8 2 3 4 5 6
	cout << endl;

	return 0;
}
//输出结果：
//1 2 3 4 5 6
//1
//6
//8 2 3 4 5 6
```

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

//赋值 assign：替换（清空原有容器中的元素，将新的元素添加进去） 	=运算符
int main()
{
	vector<int> v = { 1,2,3,4,5,6,7,8 };
	for (const auto& ch : v)
		cout << ch << " ";		//1 2 3 4 5 6 7 8
	cout << endl;

	cout << v.size() << endl;		//8
	cout << v.capacity() << endl;	//8

	vector<int> v1 = { 12,23,45,56 };
	v.assign(v1.begin(), v1.end());
	for (const auto& ch : v)
		cout << ch << " ";		//12 23 45 56
	cout << endl;

	cout << v.size() << endl;		//4
	cout << v.capacity() << endl;	//8

	v.assign(10, 'a');
	for (const auto& ch : v)
		cout << ch << " ";		//97 97 97 97 97 97 97 97 97 97 
	cout << endl;

	cout << v.size() << endl;		//10
	cout << v.capacity() << endl;	//12

	//=运算符
	vector<int> v2;
	v2 = v;

	for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		cout << *it << " ";				//97 97 97 97 97 97 97 97 97 97
	cout << endl;

	cout << v2.size() << endl;			//10
	cout << v2.capacity() << endl;		//10

	return 0;
}
//输出结果：
//1 2 3 4 5 6 7 8
//8
//8
//12 23 45 56
//4
//8
//97 97 97 97 97 97 97 97 97 97
//10
//12
//97 97 97 97 97 97 97 97 97 97
//10
//10
```

①插入：

尾插：v.push_back(10);  在最后一个元素后面插入元素10；

迭代器：v1.insert(v1.begin(), 100);	迭代器指向开始位置，在开始位置插入100；

v1.insert(v1.begin(), 2, 1000);		迭代器指向开始位置，在开始位置插入2个1000；

②删除：

尾删：v.pop_back();	删除最后一个元素；

迭代器：v1.erase(v1.begin());  删除迭代器指向的开始位置的元素；

v1.erase(v1.begin(), v1.end());	清空；

③清空：v.clear();

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

//push_back	pop_back insert erase
int main()
{
	string s = "123456";
	string s1("789");
	vector<char> v(s.begin(), s.end());

	v.push_back('7');
	v.pop_back();

	v.insert(v.begin(), '0');		//头插
	v.insert(--v.end(), 5, 'a');	//最后一个元素的前面放5个字符a
	v.insert(++v.begin(), s1.begin(), s1.end());	//在第一个元素的后面放入s1的全部内容

	for (const auto& ch : v)
		cout << ch << " ";		//0 7 8 9 1 2 3 4 5 a a a a a 6
	cout << endl;

	v.erase(v.begin());		//头删
	v.erase(++v.begin(), --v.end());		//删除第二个元素到倒数第二个元素区间的全部元素（区间左闭右开）

	for (const auto& ch : v)
		cout << ch << " ";		//7 6
	cout << endl;

	return 0;
}
//输出结果：
//0 7 8 9 1 2 3 4 5 a a a a a 6
//7 6
```

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

struct C
{
	explicit C(int c, int b)
		: _c(c)
		, _b(b)
	{}

private:
	int _c;
	int _b;
};

//emplace emplace_back
int main()
{
	vector<C> v;
	C c1(1, 2);
	v.push_back(c1);

	//v.push_back(2,2);			//explicit不允许单参构造，也不允许传递没有创建的对象
	v.emplace_back(2, 2);		//支持的，用参数调用构造函数创建一个对象，把这个对象插入到vector末尾
	//emplace只需要传递构造函数需要的参数，接口内部直接创建对象
	//自定义类型emplace_back比push_back有优势，emplace比insert有优势

	v.emplace_back(c1);
	v.insert(v.begin(), C(2, 3));
	//v.insert(v.begin(), 2, 3);	//error
	v.emplace(v.begin(), 5, 6);		//在头部插入(5,6)

	//总结：
	//push_back和insert插入的必须是已经创建的对象；
	//emplace和emplace_back可以插入匿名对象，没有创建的对象也可以插入；
	//emplace和emplace_back在插入的时候构造对象，构造对象并插入
	//push_back和insert不会构造对象

	//emplace返回一个指向已插入元素的迭代器，emplace_back不返回值。

	return 0;
}
//没有输出结果
```



## 2.7vector容器中的swap，vector中没有提供find接口，algorithm中提供了find接口

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

//vector容器中提供了swap接口，vector没有提供find接口，但是在algorithm提供了find接口
int main()
{
	vector<int> v1 = { 1,2,3,4,5 };
	 
	for (const auto&ch : v1)
		cout << ch << " ";		//1 2 3 4 5
	cout << endl;

	//在v1中查找元素2
	vector<int>::iterator pos = find(v1.begin(), v1.end(), 2);	//返回2所在位置的迭代器
	cout << *pos << endl;	//2
	v1.erase(pos);

	vector<int>::iterator it = v1.begin();
	while (it != v1.end())
	{
		cout << *it << " ";		//1 3 4 5
		++it;
	}
	cout << endl;

	vector<int> v2(8, 10);		//初始化为8个10
	cout << v1.size() << endl;		//4
	cout << v1.capacity() << endl;	//5
	cout << v2.size() << endl;		//8
	cout << v2.capacity() << endl;	//8
	for (const auto&ch : v2)
		cout << ch << " ";		//10 10 10 10 10 10 10 10 
	cout << endl;

	//交换
	v1.swap(v2);
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
		cout << *it << " ";		//10 10 10 10 10 10 10 10 
	cout << endl;

	for (vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
		cout << *it << " ";		//1 3 4 5
	cout << endl;

	return 0;
}
//输出结果：
//1 2 3 4 5
//2
//1 3 4 5
//4
//5
//8
//8
//10 10 10 10 10 10 10 10
//10 10 10 10 10 10 10 10
//1 3 4 5
```

```c++
v1.swap(v2);	交换v1和v2两个容器中的元素；
实际用途：收缩内存空间；
vector<int>(v).swap(v); 		让容器空间等于实际大小；
解释：vector<int>(v) 匿名对象    
  swap	容器交换
匿名对象用完系统立即回收匿名对象空间；

但vector<int>(v).swap(v) 并不是一个推荐的操作，因为这样做可能会增加代码的复杂性和可读性。在 C++11 及以后的版本中，可以使用 v.shrink_to_fit() 函数来请求容器减少其容量以匹配其当前大小，并尽可能释放已分配的内存。

v.shrink_to_fit()在vector容器中不会引起迭代器失效，但在list、deque等容器中会产生迭代器失效。
```



## 2.8增容的规则

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

//增容的规则
int main()
{
	vector<int> v;
	size_t c = v.capacity();
	cout << c << endl;		//0
	
	for (size_t i = 0; i < 200; ++i)
	{
		v.push_back(i);
		
		if (c != v.capacity())		//只有扩容了这两个值才会不一样
		{
			c = v.capacity();
			cout << c << endl;
		}
	}

	return 0;
}
//输出：
//1
//2
//3
//4
//6
//9
//13
//19
//28
//42
//63
//94
//141
//211
//在vs2017中是1.5倍的增容，在Linux下是2倍的增容。
```



## 2.9迭代器失效的问题

迭代器的主要作用就是让算法能够不用关心底层数据结构，其底层实际就是一个指针，或者是对指针进行了封装，

比如：vector的迭代器就是原生态指针T*。因此迭代器失效，实际就是迭代器底层对应指针所指向的空间被销毁

了，而使用一块已经被释放的空间，造成的后果是程序崩溃(即如果继续使用已经失效的迭代器，程序可能会崩

溃)。

对于vector可能会导致其迭代器失效的操作有：

1.会引起其底层空间改变的操作，都有可能是迭代器失效，比如：resize、reserve、insert、assign、push_back

等；

2.指定位置元素的删除操作：erase；

erase删除pos位置元素后，pos位置之后的元素会往前搬移，没有导致底层空间的改变，理论上讲迭代器不应该会

失效，但是：如果pos刚好是最后一个元素，删完之后pos刚好是end的位置，而end位置是没有元素的，那么po

s就失效了。因此删除vector中任意位置上元素时，vs就认为该位置迭代器失效了。（去看2.7 find代码）

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

//迭代器失效的问题
int main()
{
	vector<int> v(3, 10);		//3个元素，值为10
	vector<int>::iterator it = v.begin();

	cout << *it << endl;	//10
	v.push_back(4);

	//cout << *it << endl;//error,错误原因：在尾插的时候增容了，原先的空间释放了，迭代器指向原来的空间不能访问了。
	//解决措施，每次增容之后重新获取容器的迭代器。
	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";		//10 10 10 4
		++it;
	}
	cout << endl;

	//erase
	it = v.begin();
	cout << *it << endl;		//10
	v.erase(it);
	//cout << *it << endl;	//eror，错误原因：迭代器错位，编译器检查比较严格（迭代器指向的位置发生了变化）
	//迭代器失效，为了避免删除的是最后一个元素，下一个元素不可访问

	//会导致迭代器可能失效的接口：
	//增容：resize、reserve、push_back、insert、emplace、emplace_back
	//删除操作：erase、pop_back、clear（清空vector容器中的所有元素）

	return 0;
}
//输出结果：
//10
//10 10 10 4
//10
```

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

int main()
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	auto it = vec.begin();

	// 在 assign 操作之前保存迭代器位置
	size_t index = std::distance(vec.begin(), it);

	vec.assign(3, 42); // 使用重复元素进行 assign

	// 获取更新后的迭代器
	it = vec.begin() + index;

	// 现在可以继续使用 it 迭代器
	return 0;
}
//输出结果：没有输出结果

//distance函数原型
//template <class InputIt>
//typename iterator_traits<InputIt>::difference_type
//distance(InputIt first, InputIt last);
//InputIt 是迭代器类型，可以是指针或者类似指针的迭代器；
//first 是起始迭代器，表示要计算距离的起始位置；
//last 是结束迭代器，表示要计算距离的终止位置。
//注意，last 迭代器所指向的位置并不包含在距离范围内。
//iterator_traits<InputIt>::difference_type，即迭代器的差值类型。
```

迭代器失效的解决办法：在使用前，对迭代器重新赋值即可。



## 2.10删除所有的偶数

```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

//删除所有的偶数
int main()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			//std::vector 的 erase 成员函数会返回一个指向被删除元素之后的元素的迭代器，
			//或者如果删除的是最后一个元素，则返回 end() 迭代器。
			it = v.erase(it);
			//it = v.begin();	//在linux下不重新获取迭代器是可以通过的，windows下不行，为了安全还是重新获取迭代器
			//在linxu下最后一个元素要是偶数，会报错：段错误，非法访问。（不写下面else的时候）
		}
		else
			++it;
	}

	for (const auto& ch : v)
		cout << ch << " ";		//1 3 5
	cout << endl;

	return 0;
}
//输出结果：
//1 3 5
```



# 3.力扣

## 136.只出现一次的数字

题目：

给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一

次的元素。

你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。

提示：

1 <= nums.length <= 3 * 104

-3 * 104 <= nums[i] <= 3 * 104

除了某个元素只出现一次以外，其余每个元素均出现两次。 

```c++
示例 1 ：
输入：nums = [2,2,1]
输出：1

示例 2 ：
输入：nums = [4,1,2,1,2]
输出：4

示例 3 ：
输入：nums = [1]
输出：1
```

```c++
//方法1：异或位运算 + 范围for循环（只有这种方法符合时间复杂度是线性时间复杂度的要求）
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;    //返回的结果

        for(const auto& ch : nums)
            res = res ^ ch;

        return res;
    }
};
//总结异或（^）:
//异或的基本概念，异或是按位运输的；0与0异或的结果是0,1与1异或的结果是0,0与1（1与0）异或的结果是1。
//两个相同的数字异或的结果是0。
//任何数字与0异或都是数字本身。
```

```c++
//方法2：哈希表     （这里之前用的哈希思想创建的数组，但是哈希思想只能用于正数，不能用于负数）
/* 
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int num[3001] = {0};
        int res;        //要返回的结果        
        //统计每个元素的个数
        for(const auto& ch : nums)
            num[ch] += 1;

        for(int i = 1; i < 3001; i++)
        {
            if(num[i] == 1)
                res = i;
        }

        return res;
    }
};
*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        const int OFFSET = 3000;
	    unordered_map<int, int> countMap;
        int res;

	    for (int num : nums)
        {
		    int mappedNum = num + OFFSET;
		    countMap[mappedNum]++;
	    }

	    for (auto& pair : countMap) 
        {
		    if (pair.second == 1) 
		    	res = pair.first - OFFSET;
	    }

	    return res;
    }
};

//或者
class Solution {
public:
    int singleNumber(vector<int>& nums) {
	    unordered_map<int, int> countMap;
        int res;

	    for (int num : nums)
		    countMap[num]++;

	    for (auto& pair : countMap) 
        {
		    if (pair.second == 1) 
		    	res = pair.first;
	    }

	    return res;
    }
};
```

```c++
其余方法：暴力解法（双重循环）（n^2）、排序之后处理（nlogn）、java的话可以使用集合（集合中的数字不能重复，集合中的所有数字求和的结果 * 2 - vector中所有数字求和的结果。）
```



## 118.杨辉三角

题目：

给定一个非负整数 *`numRows`，*生成「杨辉三角」的前 *`numRows`* 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。

![img](https://pic.leetcode-cn.com/1626927345-DZmfxB-PascalTriangleAnimated2.gif)

**提示:**

- `1 <= numRows <= 30`

```c++
示例 1:
输入: numRows = 5
输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

示例 2:
输入: numRows = 1
输出: [[1]]
```

```c++
方法1：分情况初始化，每行尾插
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        //初始化行
        vector<vector<int>> mat(numRows);

        //初始化列
        for(int i = 0; i < numRows; ++i)
        {
            if(i == 0)
                mat[i].push_back(1);
            else if(i == 1)
            {
                mat[i].push_back(1);
                mat[i].push_back(1);
            }
            else
            {
                for(int j = 0; j <= i; ++j)
                {
                    if(j == 0 || j == i)
                        mat[i].push_back(1);
                    else
                        mat.operator[](i).push_back(mat[i - 1][j] + mat[i - 1][j - 1]);
                }
            } 
        }

        return mat;
    }
};

//代码中有多余的地方，修改一下
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        //初始化行
        vector<vector<int>> mat(numRows);

        //初始化列
        for(int i = 0; i < numRows; ++i)
        {
            
            for(int j = 0; j <= i; ++j)
            {
                if(j == 0 || j == i)
                    mat[i].push_back(1);
                else
                    mat.operator[](i).push_back(mat[i - 1][j] + mat[i - 1][j - 1]);
            } 
        }

        return mat;
    }
};
```

```c++
方法2：使用resize
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret(numRows);

        for(int i = 0;i < numRows;i++)
        {
            //ret[i].resize(i + 1, 1);      //等价于下面三行，一个是初始化全部，一个是初始化每行的首尾元素  
            ret[i].resize(i + 1);
            ret[i][0] = 1;
            ret[i][i] = 1;

            for(int j = 1; j < i; j++)
            {
                ret[i][j] = ret[i-1][j] + ret[i-1][j-1];
            }
        }

        return ret;
    }
};
```

```c++
方法3：创建之后插入
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret(numRows);

        //创建之后插入
        for(int i = 0; i < numRows; i++)
        {
            vector<int> temp(i + 1);
            for(int j = 0;j <= i; j++)
            {
                if(i == j || j ==0)
                    temp[j] = 1; 
                else
                    temp[j] = ret[i-1][j] + ret[i-1][j-1];
            }
            ret[i] = temp;
        }

        return ret;
    }
}; 
```



## 26.删除有序数组中的重复项

题目：

给你一个 升序排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的

新长度。元素的 相对顺序 应该保持 一致 。然后返回 nums 中唯一元素的个数。

考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：

更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。nums 的

其余元素与 nums 的大小不重要。

返回 k 。

**提示：**

- `1 <= nums.length <= 3 * 104`
- `-104 <= nums[i] <= 104`
- `nums` 已按 **升序** 排列

```c++
示例 1：
输入：nums = [1,1,2]
输出：2, nums = [1,2,_]
解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。

示例 2：
输入：nums = [0,0,1,1,1,2,2,3,3,4]
输出：5, nums = [0,1,2,3,4]
解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4 。不需要考虑数组中超出新长度后面的元素。
```

```c++
//方法1：快慢指针
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        //fast和slow表示的是索引
        int len = nums.size();
        int fast = 1;
        int slow = 1;   //使用慢指针记录唯一元素的数量

        while(fast < len)
        {
            if(nums[fast] != nums[fast - 1])
            {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }

        return slow;    
    }
};
```



## 137.只出现一次的数字||

题目：

给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出

现了一次的元素。

你必须设计并实现线性时间复杂度的算法且不使用额外空间来解决此问题。 

提示：

1 <= nums.length <= 3 * 104

-231 <= nums[i] <= 231 - 1

nums 中，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 

```c++
示例 1：
输入：nums = [2,2,3,2
输出：3
    
示例 2：
输入：nums = [0,1,0,1,0,1,99]
输出：99
```

```c++
方法1：哈希表
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> count;
        int res;

        for(const auto& ch : nums)
            count[ch]++;

        for(const auto& pair : count)
        {
            if(pair.second == 1)
                res = pair.first;
        }

        return res;
    }
};

//哈希表中的范围for循环按照新语法实现
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> count;
        int res;

        for(const auto& ch : nums)
            count[ch]++;

        for(const auto& [num, cou] : count)
        {
            if(cou == 1)
                res = num;
        }

        return res;
    }
};
```

```c++
方法2：位运算
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(int i = 0; i < 32; ++i)
        {
            //统计所有数字的二进制每位的和
            int total = 0;
            for(const auto num : nums)
                total += ((num >> i) & 1);
        
            if(total % 3)       //如果和的余数是1表明这个数字只出现了一次
                res |= (1 << i);
        }

        return res;
    }
};
```

```c++
//下面的方法理解的有点迷糊
方法3：数字电路设计 
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a = 0, b = 0;
        for (int num: nums) 
            tie(a, b) = pair{(~a & b & num) | (a & ~b & ~num), ~a & (b ^ num)};
        return b;
    }
};
//总结二进制：
//异或运算：x ^ 0 = x ， x ^ 1 = ~x
//与运算：x & 0 = 0 ， x & 1 = x

方法4：数字设计电路设计优化
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a = 0, b = 0;
        for (int num: nums) 
        {
            b = ~a & (b ^ num);
            a = ~b & (a ^ num);
        }
        return b;
    }
};
```



## 260.只出现一次的数字|||

题目：

给你一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两

个元素。你可以按 任意顺序 返回答案。

你必须设计并实现线性时间复杂度的算法且仅使用常量额外空间来解决此问题。

提示：

2 <= nums.length <= 3 * 104

-231 <= nums[i] <= 231 - 1

除两个只出现一次的整数外，nums 中的其他数字都出现两次 

```c++
示例 1：
输入：nums = [1,2,1,3,2,5]
输出：[3,5]
解释：[5, 3] 也是有效的答案。

示例 2：
输入：nums = [-1,0]
输出：[-1,0]

示例 3：
输入：nums = [0,1]
输出：[1,0]
```

```c++
方法1：哈希表 
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int , int> um;
        for(const auto& num : nums)
            um[num]++;
    
        vector<int> res;
        for(const auto& [num, count] : um)
        {
            if(count == 1)
                res.push_back(num);
        }

        return res;
    }
};

//把哈希表中的for循环改一下
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int , int> um;
        for(const auto& num : nums)
            um[num]++;
    
        vector<int> res;
        for(const auto& pair : um)
        {
            if(pair.second == 1)
                res.push_back(pair.first);
        }

        return res;
    }
};
```

```c++
方法2：位运算
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int temp = 0;
        for (int num: nums)
            temp ^= num; 

        //防止溢出
        int lsb = (temp == INT_MIN ? temp : temp & (-temp));  //最低有效位，获得二进制中最右边的1
        //解释INT_MIN：是最小整数，在二进制中指的是最高位是1，其余位是0的数字，
        //比如在8位二进制中最小的数字是10000000，最大数字01111111加1就是最小数字。（可以把二进制数字的范围看成一个转盘。）
        //如果这位是1，则表示这两个不同的数字在这位上不同。
        int type1 = 0, type2 = 0;
        for (int num: nums) {
            if (num & lsb) {
                type1 ^= num;
            }
            else {
                type2 ^= num;
            }
        }
        
        vector<int> res;
        res.resize(2);
        res[0] = type1;
        res[1] = type2;
        //res.push_back(type1);
        //res.push_back(type2);

        return res;
        //return {type1, type2};
    }
};

//换一种方法处理最低有效位
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int temp = 0;
        for (int num: nums)
            temp ^= num; 

        //防止溢出
        //int lsb = (temp == INT_MIN ? temp : temp & (-temp));  //最低有效位
        int binary;         //记录二进制要移动的位数
        for(int i = 0; i < 32; i++)
        {
            if(((temp >> i) & 1) == 1)      
            { 
                binary = i;
                break;
            }       
        }

        int lsb = (1 << binary);

        int type1 = 0, type2 = 0;
        for (int num: nums) {
            if (num & lsb) {
                type1 ^= num;
            }
            else {
                type2 ^= num;
            }
        }
        
        return {type1, type2};
    }
};
```



## 17.电话号码的字母组合

题目：

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2021/11/09/200px-telephone-keypad2svg.png)

**提示：**

- `0 <= digits.length <= 4`
- `digits[i]` 是范围 `['2', '9']` 的一个数字。

```c++
示例 1：
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
    
示例 2：
输入：digits = ""
输出：[]
    
示例 3：
输入：digits = "2"
输出：["a","b","c"]
```

```c++

```



## 169多数元素（数组中出现次数超过一半的数字）

题目：

给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

**提示：**

- `n == nums.length`
- `1 <= n <= 5 * 104`
- `-109 <= nums[i] <= 109`

```c++
示例 1：
输入：nums = [3,2,3]
输出：3

示例 2：
输入：nums = [2,2,1,1,1,2,2]
输出：2
```

```c++
方法1：哈希表
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res;
        unordered_map<int, int> count;
        for(const auto& num : nums)
            count[num]++;

        int temp = 0;
        for(const auto& pair : count)
        {
            if(pair.second > temp)
            {
                temp = pair.second;
                res = pair.first;
            }
        }

        return res;
    }
};

//换一种新的语法表示范围for循环
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res;
        unordered_map<int, int> count;
        for(const auto& num : nums)
            count[num]++;

        int temp = 0;
        for(const auto& [index, count] : count)
        {
            if(count > temp)
            {
                temp = count;
                res = index;
            }
        }

        return res;
    }
};

//在哈希表更新的时候直接统计，这样只需要遍历一次
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> counts;
        int res = 0, count = 0;
        for (int num: nums) {
            ++counts[num];
            if (counts[num] > count) 
            {
                res = num;
                count = counts[num];
            }
        }
        return res;
    }
};
```

```c++
方法2：排序
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];       //值是四舍五入的
    }
};
//时间复杂度是O(nlogn)，空间复杂度如果使用语言自带的是O(nlogn)，如果是堆排序是O(n)。
```

```c++
方法3：随机化
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res;
        while (true) {
            int temp = nums[rand() % nums.size()];     //数组中的随机值
            int count = 0;
            for (int num : nums)
            {
                if (num == temp)
                    ++count;
            }
            
            if (count > nums.size() / 2)
            {
                res = temp;
                break;
            }
        }
        return res;
    }
};
//最差的时间复杂度是无限大的，可能随机值一直都不是想要的
```

```c++
方法4：分治 
class Solution {
    int count_in_range(vector<int>& nums, int target, int lo, int hi) {
        int count = 0;
        for (int i = lo; i <= hi; ++i)
            if (nums[i] == target)
                ++count;
        return count;
    }

    int majority_element_rec(vector<int>& nums, int lo, int hi) {
        if (lo == hi)
            return nums[lo];
        int mid = (lo + hi) / 2;
        int left_majority = majority_element_rec(nums, lo, mid);
        int right_majority = majority_element_rec(nums, mid + 1, hi);
        if (count_in_range(nums, left_majority, lo, hi) > (hi - lo + 1) / 2)
            return left_majority;
        if (count_in_range(nums, right_majority, lo, hi) > (hi - lo + 1) / 2)
            return right_majority;
        return -1;
    }
    
public:
    int majorityElement(vector<int>& nums) {
        return majority_element_rec(nums, 0, nums.size() - 1);
    }
};
//时间复杂度是O(nlogn)，空间复杂度是O(logn)。
```

```c++
方法5：Boyer-Moore 投票算法
//分治算法的变种：是众数记为1，不是众数记为-1，和加起来必定大于0。
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int res = -1;
        for(const auto& num : nums)
        {
            if(res == num)
                count++;
            else
            {
                count--;
                if(count < 0)
                {
                    res = num;
                    count = 1;
                }
            }
        }

        return res;
    }
};
*/

//换种更好的写法：
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int res = -1;
        for(const auto& num : nums)
        {
            if(res == num)
                count++;
            else if(--count < 0)
            { 
                res = num;
                count = 1;
            }
        }

        return res;
    }
};
//时间复杂度是O(n)，空间复杂度是O(1)。
```

```c++
方法6：位运算
class Solution {
public:
    int majorityElement(vector<int>& nums) {
    	int res = 0;
    	for(int i = 0 ; i < 32; ++i)
    	{
        	int ones = 0;
        	for(int n : nums)
            	ones += (n >> i) & 1;              //位运算法统计每个位置上1出现的次数，每次出现则ones+1
        	res += (ones > nums.size()/2) << i;    //如果1出现次数大于1/2数组的长度，1即为这个位置的目标数字
   		}
    	return res;
    }
};
//解释：如果二进制的哪个位置的1的个数大于数组的长度的一般，表明数组中众数的这个位置是1.
```



## 53.最大子数组和（连续子数组的最大和）

题目：

给你一个整数数组 `nums` ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

**子数组** 是数组中的一个连续部分。

**提示：**

- `1 <= nums.length <= 105`
- `-104 <= nums[i] <= 104`

```c++
示例 1：
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。

示例 2：
输入：nums = [1]
输出：1
    
示例 3：
输入：nums = [5,4,-1,7,8]
输出：23
```

```c++
方法1：动态规划
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0;
        //int res = 0;      //这里错误的原因是：nums中只有一个元素，这个元素是负数。
        int res = nums[0];

        for (const auto& num: nums) 
        {
            pre = pre + num > num ? pre + num : num;    //更新子串的起始元素。（通俗点就是元素的值大于0，前面元素的和小于0，就将这个大于0的值当做新的起始元素。）
            res = max(res, pre);        //子串的最大值。
        }

        return res;
    }
};
//时间复杂度：O(n)，空间复杂度O(1)。

//动态规划的标准写法：
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size();
        vector<int> dp(size);
        dp[0] = nums[0];
        int res = dp[0];
        
        for(int i = 1; i < nums.size(); i++)
        {
            dp[i] = max(dp[i-1] + nums[i], nums[i]);
            res = max(dp[i], res);
        }

        return mm;
    }
};
```

```c++
方法2：比较起始值，和动态规划思想差不多
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = nums[0];
        int max_sum = 0;
        for(const auto& num : nums)
        {
            if(max_sum < 0 && num > 0)        //刚开始写的是num > 0。这样不符合字符串[-2,-1]输出的结果。
                max_sum = num;      //更新起始值
            else    
                max_sum += num;
            res = max(max_sum, res);        //子串的和的最大值
        }

        return res;
    }
};
```

```c++
方法3：分治 + 递归
class Solution {
public:
    struct Status {
        int lSum, rSum, mSum, iSum;
    };

    Status pushUp(Status l, Status r) {
        int iSum = l.iSum + r.iSum;
        int lSum = max(l.lSum, l.iSum + r.lSum);
        int rSum = max(r.rSum, r.iSum + l.rSum);
        int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
        return (Status) {lSum, rSum, mSum, iSum};
    };

    Status get(vector<int> &a, int l, int r) {
        if (l == r) 
            return (Status) {a[l], a[l], a[l], a[l]};
        
        int m = (l + r) >> 1;
        Status lSub = get(a, l, m);
        Status rSub = get(a, m + 1, r);
        return pushUp(lSub, rSub);
    }

    int maxSubArray(vector<int>& nums) {
        return get(nums, 0, nums.size() - 1).mSum;
    }
};

//分治算法
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        //类似寻找最大最小值的题目，初始值一定要定义成理论上的最小最大值
        int result = INT_MIN;
        int numsSize = nums.size();
        result = maxSubArrayHelper(nums, 0, numsSize - 1);
        return result;
    }

    int maxSubArrayHelper(vector<int> &nums, int left, int right)
    {
        if (left == right)
            return nums[left];
        int mid = (left + right) / 2;
        int leftSum = maxSubArrayHelper(nums, left, mid);
        int rightSum = maxSubArrayHelper(nums, mid + 1, right);
        int midSum = findMaxCrossingSubarray(nums, left, mid, right);
        int result = max(max(leftSum, rightSum), midSum);
        return result;
    }

    int findMaxCrossingSubarray(vector<int> &nums, int left, int mid, int right)
    {
        //左半边的最大值
        int leftSum = INT_MIN;
        int sum = 0;
        for (int i = mid; i >= left; i--)
        {
            sum += nums[i];
            leftSum = max(leftSum, sum);
        }

        //右半边的最大值
        int rightSum = INT_MIN;
        sum = 0;
        for (int i = mid + 1; i <= right; i++)
        {
            sum += nums[i];
            rightSum = max(rightSum, sum);
        }
        return (leftSum + rightSum);
    }
};
```

```c++
方法4：前缀和。       
//和"121题：买卖股票的最佳时机"做法一样。
class Solution {
public:
    int maxSubArray(vector<int> &nums) {
        int res = INT_MIN;      //要返回的结果，初始化为最小值
        int min_pre_sum = 0;
        int pre_sum = 0;
        
        for (const auto& num : nums) 
        {
            pre_sum += num;                             //当前的前缀和
            res = max(res, pre_sum - min_pre_sum);      //减去前缀和的最小值
            min_pre_sum = min(min_pre_sum, pre_sum);    //维护前缀和的最小值
        }
        
        return res;
    }
};
```

```c++
方法5：暴力法。       
//超时了
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int max = INT_MIN;
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; i++)
        {
            int sum = 0;
            for (int j = i; j < numsSize; j++)
            {
                sum += nums[j];
                if (sum > max)
                     max = sum;
            }
        }

        return max;
    }
};
```

```c++
方法6：贪心法
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int result = INT_MIN;
        int numsSize = int(nums.size());
        int sum = 0;
        for (int i = 0; i < numsSize; i++)
        {
            sum += nums[i];
            result = max(result, sum);
            //如果sum < 0，重新开始找子序串
            if (sum < 0)
                sum = 0;
        }

        return result;
    }
};
```



## 27.移除元素

题目：给你一个数组nums和一个值val，你需要原地移除所有数值等于val的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用O(1)额外空间并原地修改输入数组。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

```c
为什么返回数值是整数，但输出的答案是数组呢?
请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
你可以想象内部操作如下:
// nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
int len = removeElement(nums, val);
// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
} 
```

```c
示例1：
输入：nums = [3,2,2,3], val = 3
输出：2, nums = [2,2]
解释：函数应该返回新的长度2, 并且nums中的前两个元素均为2。你不需要考虑数组中超出新长度后面的元素。例如，函数返回的新长度为2，而nums = [2,2,3,3]或nums = [2,2,0,0]，也会被视作正确答案。
示例2：
输入：nums = [0,1,2,2,3,0,4,2], val = 2
输出：5, nums = [0,1,4,0,3]
解释：函数应该返回新的长度5,并且nums中的前五个元素为0,1,3,0,4。注意这五个元素可为任意顺序。你不需要考虑数组中超出新长度后面的元素。

提示：    
0 <= nums.length <= 100
0 <= nums[i] <= 50
0 <= val <= 100
```

```c++
方法1：快慢指针（覆盖删除）
1.i是要返回的索引，j是遍历的索引；
2.和val相等就遍历下一个，不相等就存储在数组以i为索引的数组。
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        int fast = 0;
        for( ; fast < nums.size(); fast++)
        {
            //slow存储要返回的长度
            //fast进行遍历，找到不是要删除的val放在slow索引的地方
            if(nums[fast] != val)
                nums[slow++] = nums[fast];
        }
        
        return slow;
    }
};
//时间复杂度：O(n)其中为序列的长度，我们只需要遍历该序列至多两次。（最坏情况下是两个索引各自都遍历了一遍）
```

```c++
方法2：首尾交换
1.遍历索引i，如果索引i的值和val相等就和最后一个元素（索引下标为numsSize - 1）进行交换，numsSize减1，不相等就遍历下一个元素；
2.交换之后索引不变，再重复步骤1。
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int res = 0;
        int len = nums.size();
        while(res < len)
        {
            if(nums[res] == val)
                nums[res] = nums[--len];
            else
                res++;
        }

        return res;
    }
};
//时间复杂度：O(n)，其中n为序列的长度，我们只需要遍历该序列至多一次。
//方法2相当于方法1的优化，提升了效率。
```



## 88.合并两个有序数组

题目：给你两个按非递减顺序排列的整数数组nums1和nums2，另有两个整数m和n，分别表示nums1和nums2

中的元素数目。

请你合并nums2到nums1中，使合并后的数组同样按非递减顺序排列。

注意：最终，合并后数组不应由函数返回，而是存储在数组nums1中。为了应对这种情况，nums1的初始长度为

m + n，其中前m个元素表示应合并的元素，后n个元素为0，应忽略nums2的长度为n。 

```c
示例1：
输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] ，合并结果是 [1,2,2,3,5,6]。 
示例2：
输入：nums1 = [1], m = 1, nums2 = [], n = 0
输出：[1]
解释：需要合并 [1] 和 []，合并结果是 [1]。
示例3：
输入：nums1 = [0], m = 0, nums2 = [1], n = 1
输出：[1]
解释：需要合并的数组是 [] 和 [1]，合并结果是 [1] 。
注意，因为 m = 0 ，所以nums1中没有元素。nums1中仅存的0仅仅是为了确保合并结果可以顺利存放到nums1中。

提示：
nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-109 <= nums1[i], nums2[j] <= 109
```

```c++
方法1：合并后直接进行排序（先将数组nums2放进数组nums1的尾部，然后直接对整个数组进行排序。）
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(const auto& num : nums1)
            if(num != 0)
                nums2.push_back(num);
        
        nums1 = nums2;

        sort(nums1.begin(), nums1.end());
    }
};
时间复杂度：O((m + n)log(m + n))，排序序列长度为m + n，套用快速排序的时间复杂度即可，平均情况为O((m + n)log(m + n))。
空间复杂度：O(log(m + n)),排序序列长度为m + n，套用快速排序的空间复杂度即可，平均情况为O(log(m + n))。
```

```c++
方法2：双指针
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> nums3;
        
        int nums1_begin = 0;
        int nums2_begin = 0;
    
        while(nums1_begin < m || nums2_begin < n)
        {
            if(nums1_begin == m)
                nums3.push_back(nums2[nums2_begin++]);
            else if(nums2_begin == n)
                nums3.push_back(nums1[nums1_begin++]);
            else if(nums1[nums1_begin] < nums2[nums2_begin])
                nums3.push_back(nums1[nums1_begin++]);
            else
                nums3.push_back(nums2[nums2_begin++]);
        }

        nums1 = nums3;
    }
};
时间复杂度：O(m + n)，指针移动单调递增，最多移动m + n次。
空间复杂度：O(m + n)，需要建立长度为m + n的中间数组nums3。
```

```
方法3：反向双指针（避免正向双指针的覆盖）
nums1的后半部分是空的，可以直接覆盖而不会影响结果。因此可以指针设置为从后向前遍历，每次取两者之中的较大者放进nums1的最后面。
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        while(m > 0 && n > 0)
        {
            if(nums1[m - 1] > nums2[n - 1])
            {    
                nums1[m + n - 1] = nums1[m - 1];
                m--;
            }
            else
            {
                nums1[m + n - 1] = nums2[n - 1];
                n--;
            }
        }

        while(n > 0)
        {
            nums1[n - 1] = nums2[n - 1];
            n--;
        }
    }
};

//反向双指针的另外一种写法：
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1, p2 = n - 1;
        int tail = m + n - 1;
        while (p1 >= 0 || p2 >= 0) 
        {
            if (p1 == -1) 
                nums1[tail--] = nums2[p2--];
            else if (p2 == -1) 
                break;
            else if (nums1[p1] > nums2[p2])  
                nums1[tail--] = nums1[p1--];
            else 
                nums1[tail--] = nums2[p2--];
        }
    }
}; 
时间复杂度：O(m + n)，指针移动单调递减，最多移动m + n次。
空间复杂度：O(1)，原地修改，不需要额外空间。
```



## 189.轮转数组

题目：给定一个整数数组nums，将数组中的元素向右轮转 k个位置，其中k是非负数。

```c
示例1:
输入: nums = [1,2,3,4,5,6,7], k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右轮转 1 步: [7,1,2,3,4,5,6]
向右轮转 2 步: [6,7,1,2,3,4,5]
向右轮转 3 步: [5,6,7,1,2,3,4]
示例2:
输入：nums = [-1,-100,3,99], k = 2
输出：[3,99,-1,-100]
解释: 
向右轮转 1 步: [99,-1,-100,3]
向右轮转 2 步: [3,99,-1,-100]

提示：
1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
0 <= k <= 105
```

```c++
方法1：暴力解法（超出时间限制）
1.先记录下最后一个元素，将前边的元素移动到后面进行逐个替换（倒着替换），再讲记录的最后一个元素放在第一个上面；
2.步骤1执行k次。
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        k %= len;
        for(int i = 0; i < k; i++)
        {
            int temp = nums[len - 1];
            for(int j = len - 2; j >= 0 ; j--)
                nums[j + 1] = nums[j];
            nums[0] = temp;
        }
    }
};
时间复杂度：O(n*n)，替换k轮，每次执行numsSize - 1次。
空间复杂度：O(1),没有使用凝额外空间。
```

```c++
方法2：使用额外空间
使用一块和数组一样大的中间数组，将数组中的值进行按newArr[(i + k) % numsSize] = nums[i]规律赋值，然后拷贝回原数组。 
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int> temp1;
        vector<int> temp2;
        int m = k % nums.size();

        while(m--)
        {
            temp1.push_back(nums.back());
            nums.pop_back();
        }

        while(!nums.empty())
        {
            temp2.push_back(nums.back());
            nums.pop_back();
        }

        while(!temp1.empty())
        {
            nums.push_back(temp1.back());
            temp1.pop_back();
        }

        while(!temp2.empty())
        {
            nums.push_back(temp2.back());
            temp2.pop_back();
        }
    }
};

//使用额外空间的另外一种写法
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        vector<int> temp(len);

        for(int i = 0; i < len; i++)
            temp[(k + i) % len] = nums[i];         
    
        nums = temp;
    }
};
时间复杂度：O(n)，进行了两次numsSize循环。
空间复杂度：O(n),使用了和数组长度一样的数组。
```

```c++
方法3：数组翻转
由于翻转的对称性质，先将前半段翻转，再将后半段进行翻转，最后翻转整个数组；
void my_swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void my_exchange(vector<int>& nums, int begin, int end)
{
    while(begin < end)
        my_swap(nums[begin++], nums[end--]);
}

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        k %= len;
        my_exchange(nums, 0, len - k - 1);
        my_exchange(nums, len - k, len - 1);
        my_exchange(nums, 0, len - 1);
    }
};
时间复杂度：O(n)，数组中每个元素被翻转2次，n为数组的长度。
空间复杂度：O(1)，没有使用额外空间。
```

```c++
方法4：环状替换（这个代码理解的不是很明白，尤其是为啥要计算最大公约数）
1.使用一个变量作为中间交换的桥梁，每次交换完的值可以再次使用；（前面的值赋值给后面的值要记录下后面的值，防止被覆盖）
2.最多执行k轮，每轮之间值相差k个，当本轮循环到和起始条件一样就执行下一轮，直到数组中的全部元素遍历完结束；
3.结束条件：当遍历的元素个数和数组中的个数相等时，表明每个元素都被遍历了一次，就跳出结束循环。
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        k = k % len;
        int count = gcd(k, len);        //最大公约数
        for (int start = 0; start < count; ++start) 
        {
            int current = start;
            int prev = nums[start];
            do {
                int next = (current + k) % len;
                swap(nums[next], prev);
                current = next;
            } while (start != current);
        }
    }
}; 
时间复杂度：O(n),看起来是双层循环但每个元素只遍历了一次，n是数组的长度。
空间复杂度：O(1),只需要1个常数空间。
```



## 989.数组形式的整数加法

题目：整数的数组形式num是按照从左到右的顺序表示其数字的数组。

例如，对于num = 1321 ，数组形式是 [1,3,2,1] 。

给定num，整数的数组形式，和整数k，返回整数num + k的数组形式 。

```c
示例1：
输入：num = [1,2,0,0], k = 34
输出：[1,2,3,4]
解释：1200 + 34 = 1234
示例2：
输入：num = [2,7,4], k = 181
输出：[4,5,5]
解释：274 + 181 = 455
示例3：
输入：num = [2,1,5], k = 806
输出：[1,0,2,1]
解释：215 + 806 = 1021
 
提示：
1 <= num.length <= 104
0 <= num[i] <= 9
num 不包含任何前导零，除了零本身
1 <= k <= 104
```

```c
方法1：逐个位置相加
1.计算要创建数组的长度，长度是数字和字母长度的最大值 + 1；
2.创建好之后数字和字母的低位相加，相加好的值放到从数组索引为0的值开始；
3.由于循环的判断条件是数组长度，可能数字的长度长，最后数字会存在高位还有值没有处理，需要单独加入到要返回的数组中；（这里也可以判断条件设置为两者没有计算完一致计算）
4.最后进行翻转；
注意点：
1.需要注意的是最后的*returnSize决定了要返回几位数字，数字的位数是从前往后数；（数组从索引0开始数）
2.这个要写什么想不起来了。
void exchange(int* num, int start,int end)
{
    while(start < end)
    {
        int temp = num[start];
        num[start] = num[end];
        num[end] = temp;
        ++start;
        --end;
    }
}

int* addToArrayForm(int* num, int numSize, int k, int* returnSize) {
    int temp = k;
    int len = 0;
    while(temp)
    {
        temp /= 10;
        ++len;
    }
    int lenmax = (len > numSize ? (len + 1) : (numSize + 1));
    int* res = (int*)malloc(sizeof(int) * lenmax);
    *returnSize = 0;	//需要注意的是最后的*returnSize决定了要返回几位数字，数字的位数是从前往后数
    //低位的值给高位，最后翻转
    for (int i = numSize - 1; i >= 0; --i) {
        int sum = num[i] + k % 10;
        k /= 10;
        if (sum >= 10) {
            k++;            //进位加1
            sum -= 10;      //减去进位的1，就是10
        }
        res[(*returnSize)++] = sum;    //低位加的值给高位
    }
    //计算k的剩余值
    for (; k > 0; k /= 10) {
        res[(*returnSize)++] = k % 10;
    }
    exchange(res,0,*returnSize - 1);
    return res;
}

方法2：将整个数组k加入数组表示表示数组的最低位逐个计算
例子：123 + 912，我们把它表示成[1,2,3+912]。然后，我们计算3+912=915。5留在当前这一位，将910/10=91 以进位的形式加入下一位。然后，我们再重复这个过程，计算 [1,2+91,5]。我们得到93，3留在当前位，将90/10=9以进位的形式加入下一位。继而又得到[1+9,3,5]，重复这个过程之后，最终得到结果[1,0,3,5]。 
void exchange(int* num, int start,int end)
{
    while(start < end)
    {
        int temp = num[start];
        num[start] = num[end];
        num[end] = temp;
        ++start;
        --end;
    }
}

int* addToArrayForm(int* num, int numSize, int k, int* returnSize) {
	int temp = k;
	int len = 0;
	while (temp)
	{
		temp /= 10;
		++len;
	}
	int lenmax = (len > numSize ? (len + 1) : (numSize + 1));
	int* res = (int*)malloc(sizeof(int) * lenmax);
	*returnSize = 0;
	for (int i = numSize - 1; i >= 0 || k > 0; --i, k /= 10) {
		if (i >= 0) {
			k += num[i];
		}
		res[(*returnSize)++] = k % 10;
	}

	exchange(res, 0, *returnSize - 1);
	return res;
}
时间复杂度：O(max(n,logk))，其中n为数组的长度。（这里理解有问题）
空间复杂度：O(1)，除了返回值之外没有使用额外空间。
```



# 4.实现vector

![image-20230624130752151](C:\Users\19827\AppData\Roaming\Typora\typora-user-images\image-20230624130752151.png)

vector的实现可以和string一样，下面写一个用迭代器实现的vector。

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

using namespace std;

char* Mystrcpy(char* dest, const char* src)
{
	assert(dest && src);   //断言
	char* tmp = dest;
	while (*dest++ = *src++)
	{
		;
	}
	return tmp;
}

template <class T>
class Vector
{
public:
	//迭代器
	typedef T* iterator;
	typedef const T* const_iterator;

	//默认构造函数
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{}

	//构造：n个val
	//Vector(size_t n,T& val = T())//匿名对象具有常性，没有const会报错，报错为：默认参数无法从int转化为T&
	/*
	Vector(size_t n, const T& val = T())   //匿名对象具有常性
		: _start(new T[n])		//申请能够存放n个元素的空间
		, _finish(_start + n)
		, _endOfStorage(_start + n)		//, _endOfStorage(_finish)
	{
		for (size_t i = 0; i < n; ++i)
		{
			_start[i] = val;
		}
	}
	*/

	Vector(int n, const T& value = T())
		: _start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{
		reserve(n);
		while (n--)
		{
			push_back(value);
		}
	}

	//拷贝构造
	Vector(const Vector<T>& v)
		: _start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{
		size_t n = v.capacity();
		_start = new T[n];
		for (size_t i = 0; i < v.size(); ++i)
		{
			_start[i] = v[i];
		}
		_finish = _start + v.size();
		_endOfStorage = _start + n; //_start + capacity()
		//这里的capacity()和size()可能是不一样的。
	}


	//如果使用iterator做迭代器，会导致初始化的迭代器区间[first,last)只能是vector的迭代器
	//重新声明迭代器，迭代器区间[first,last]可以是任意容器的迭代器
	template <class inputIterator>
	Vector(inputIterator first, inputIterator last)
		: _start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{
		//[first,last)
		reserve(last - first);		//预留空间
		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}

	//析构函数
	~Vector()
	{
		if (_start)
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
	}

	/*
	//赋值运算符
	//传统写法
	Vector<T>& operator=(const Vector<T>& v)
	{
		if (this != &v)
		{
			delete[] _start;
			size_t n = v.capacity();		//这里的capacity()一定是大于等于size()的。
			_start = new T[n];
			for (size_t i = 0; i < v.size(); i++)
			{
				_start[i] = v[i];
			}
			_finish = _start + v.size();
			_endOfStorage = _start + n;
		}
		return *this;
	}
	*/

	/*
	void Swap(Vector<T>& v)			//引用，内部修改相当于外部修改
	{
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endOfStorage, v._endOfStorage);
	}
	*/

	//赋值运算符现代写法
	Vector<T>& operator=(Vector<T> v)	//值拷贝
	{
		swap(v);
		return *this;
	}

	

	size_t size() const
	{
		return _finish - _start;
	}

	size_t capacity() const
	{
		return _endOfStorage - _start;
	}

	bool empty()
	{
		return _start == _finish;
	}

	iterator begin()
	{
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	const iterator begin() const
	{
		return _start;
	}

	const iterator end() const
	{
		return _finish;
	}

	T& operator[](size_t pos)
	{
		if (pos >= 0 && pos < size())
		{
			return _start[pos];
		}
	}

	const T& operator[](size_t pos) const
	{
		if (pos >= 0 && pos < size())
		{
			return _start[pos];
		}
	}

	//预留空间 或者 增容
	void reserve(size_t n)
	{
		if (n > capacity())
		{
			//保存原始的size
			size_t sz = size();
			//开空间
			T* arr = new T[n];
			//拷贝内容
			if (_start)
			{
				/*
				//自定义类型：浅拷贝  如果有资源，会产生资源被多次释放
				//memcpy(arr, _start, sizeof(T) * size());
				for (size_t i = 0; i < sz; i++)
					arr[i] = _start[i];
				delete[] _start;
				*/
				//深拷贝
				for (size_t i = 0; i < sz; i++)
				{
					//如果是自定义类型，调用赋值运算符重载函数
					//只要赋值运算符实现了深拷贝，此处即为深拷贝
					arr[i] = _start[i];
				}
				delete[] _start;
			}
			//更新
			_start = arr;
			_finish = _start + sz;		//空间变了，扩容_finish就变了
			_endOfStorage = _start + n;
		}
	}
	//1.memcpy是内存的二进制格式拷贝，将一段内存空间中内容原封不动的拷贝到另外一段内存空间中
	//2.如果拷贝的是内置类型的元素，memcpy即高效又不会出错，但如果拷贝的是自定义类型元素，
	//并且自定义类型元素中涉及到资源管理时，就会出错，因为memcpy的拷贝实际是浅拷贝。
	//结论：如果对象中涉及到资源管理时，千万不能使用memcpy进行对象之间的拷贝，
	//因为memcpy是浅拷贝，否则可能会引起内存泄漏甚至程序崩溃。

	//改变实际长度
	void resize(size_t n, const T& val = T())
	{
		//n > capacity 增容
		if (n > capacity())
		{
			reserve(n);
		}

		//szie < n < capacity [size,n - 1] 多出来的部分填充val
		if (n > size())
		{
			while (_finish != _start + n)		//这里的临界点是需要注意的，不确定的时候就画图确定
			{
				*_finish = val;
				++_finish;
			}
		}

		//n <= size，只修改size
		_finish = _start + n;
	}

	//插入某个元素	这里需要注意迭代器失效，也要明白在reserve函数中更新了_endOfStorage
	void insert(iterator pos, const T& val)
	{
		//有效区间:[0,size]
		if (pos >= _start && pos <= _finish)
		{
			//检查容量
			if (_finish == _endOfStorage)
			{
				//保存元素的个数
				size_t num = pos - _start;
				//增容会导致迭代器失效，增容要更新迭代器
				size_t n = _endOfStorage == nullptr ? 1 : 2 * capacity();
				reserve(n);
				//增容之后更新pos
				pos = _start + num;    //增容之后_start,_finish,_endOfStorage都自动更新了，而pos没有改变，不变的是_star和pos的相对位置关系
			}
		
			//移动元素:从后向前移动
			iterator end = _finish;
			while (end != pos)
			{
				*end = *(end - 1);
				end--;
			}

			//插入新的元素
			*pos = val;

			//更新
			++_finish;
		}
	}

	//删除某个元素
	iterator erase(iterator pos)
	{
		//检查位置
		if (pos < _finish && pos >= _start)
		{
			//移动元素:从前向后移动
			iterator start = pos + 1;
			while (start != _finish)
			{
				*(start - 1) = *start;
				start++;
			}

			//更新
			_finish--;
		}

		return pos;   //返回删除后的下一个元素移动后的位置
	}

	//尾插某个元素
	void push_back(const T& val)
	{
		//检查容量
		if (_finish == _endOfStorage)
		{
			//增容
			size_t newC = _endOfStorage == nullptr ? 1 : 2 * capacity();
			reserve(newC);   //预留空间 相当于 增容
		}

		//插入
		*_finish = val;

		//更新size
		_finish++;
	}

	//尾删最后一个元素
	void pop_back()
	{
		erase(end() - 1);
	}

private:
	//迭代器的设计每个容器的原理基本都相同，_finish不在实际长度中。
	iterator _start;		//指向数据块的开始
	iterator _finish;		//指向有效数据的尾	_finish指的位置不在vector实际长度中	
	iterator _endOfStorage;	//指向存储容量的尾
};

class String
{
public:
	String(const char* ptr = " ")
		:_ptr(new char[strlen(ptr) + 1])
	{
		strcpy(_ptr, ptr);
	}

	~String()
	{
		if (_ptr)
		{
			delete[] _ptr;
			_ptr = nullptr;
		}
	}

	String(const String& str)
		:_ptr(new char[strlen(str._ptr) + 1])
	{
		strcpy(_ptr, str._ptr);
	}

	String& operator=(const String& str)
	{
		if (this != &str)
		{
			delete[] _ptr;
			_ptr = new char[strlen(str._ptr) + 1];
			strcpy(_ptr, str._ptr);
		}
		return *this;
	}

private:
	char* _ptr;
};

struct A
{
	A(int a = 1)		//必须有无参构造	全缺省构造是无参
		:_a(a)
	{
		cout << "A(int)" << endl;
	}

	int _a = 10;
};

//普通打印
template <class T>
void printVector(const Vector<T>& v)
{
	typename Vector<T>::const_iterator it = v.begin();		//不加typename会报错：const_iterator类型从属名称的的使用必须以typename为前缀

	while (it != v.end())
	{
		cout << *it << " ";
		//*it = T();
		it++;
	}
	cout << endl;
}

//for循环打印
template <class T>
void printForVector(const Vector<T>& v)
{
	for (const auto& e : v)    //这里的const要自己加，不加的话推导出来的为int，vector中的内容就可以修改了。
	{
		cout << e << " ";
		//cout << typeid(e).name() << " ";
		//e = T();   
	}
	cout << endl;
}

//c++中的vector类没有提供<<运算符
template <class T>
ostream& operator<<(ostream& out, Vector<T>& v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		out << v[i] << " ";			//类型T的<<运算符也必须重载
	}

	out << endl;
	return out;
}

int main()
{
	Vector<int> v1(5, 10);

	Vector<int> v2(v1.begin(), v1.end());
	
	for (const auto& ch : v1)
		cout << ch << " ";
	cout << endl;

	for (const auto& ch : v2)
		cout << ch << " ";
	cout << endl;

    printForVector(v2);
    
	vector<vector<int>> v3;		//嵌套vector
	return 0;
}
//输出结果：
//10 10 10 10 10
//10 10 10 10 10
//10 10 10 10 10
```

问题：vector容器的区间构造实现有问题。

问题找到了，是我实现的构造n个val有问题，不是迭代器区间的构造函数有问题。

```c++
//自己之前写的有问题的代码：
Vector(size_t n, const T& val = T())   //匿名对象具有常性
	: _start(new T[n])		//申请能够存放n个元素的空间
	, _finish(_start + n)
	, _endOfStorage(_start + n)		//, _endOfStorage(_finish)
{
	for (size_t i = 0; i < n; ++i)
	{
		_start[i] = val;
	}
}
```

```c++
//修改之后正确的代码：
Vector(int n, const T& value = T())
	: _start(nullptr)
	, _finish(nullptr)
	, _endOfStorage(nullptr)
{
	reserve(n);
	while (n--)
	{
		push_back(value);
	}
}
```

原因不明。（在我认为两种代码都是对的，但是第一种代码不知道错在了哪里。）
