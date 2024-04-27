#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

void test1()
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
	//输出结果：
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
	//_a = 1  _b = 2
}

//vector迭代器
void test2()
{
	string str("12345678");
	vector<char> v(str.begin(), str.end());

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
		cout << *crit << " ";		//h g f e d c b a
	cout << endl;

	vector<char>::const_reverse_iterator crit = v.rbegin();
	while (crit != v.rend())
	{
		cout << *crit << " ";		//h g f e d c b a
		++crit;
	}
	cout << endl;
}

//范围for循环
void test3()
{
	string s("123456");
	vector<char> v(s.begin(), s.end());
	for (const auto& ch : v)
		cout << ch << " ";	//输出结果：1 2 3 4 5 6
	cout << endl;
}

struct B
{
	int a;
	char b;
	double c;
	char* d;
};

//max_size()：表示当前vector对象能够容纳的最大元素数量
//max_size 返回的是理论上可容纳的最大元素数量，实际上可能由于各种限制而无法达到这个数值。
void test4()
{
	vector<char> v1;
	vector<int> v2;
	vector<int*> v3;
	vector<double> v4;
	vector<B> v5;
	cout << v1.max_size() << endl;	//2147483647	用
	//2147483647 是一个整数，它是 int 类型的最大值（如果使用32位有符号整数表示）。
	cout << v2.max_size() << endl;	//1073741823
	cout << v3.max_size() << endl;	//1073741823
	cout << v4.max_size() << endl;	//536870911
	cout << v5.max_size() << endl;	//178956970
}

//capacity	size	resize	reserve  empty	shrink_to_fit
void test5()
{
	string s;
	vector<char> v(s.begin(),s.end());
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
	v.reserve(15);
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
	
	if (v.empty())
		cout << "empty容器是空的" << endl;		 
	else
		cout << "empty容器不是空的" << endl;	//empty容器不是空的	
}

//[] at	front back 
//data：获取vector容器的存放元素空间的首地址
void test6()
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
}

//赋值 assign：替换（清空原有容器中的元素，将新的元素添加进去） 
void test7()
{
	vector<int> v = { 1,2,3,4,5,6,7,8 };
	for (const auto& ch : v)
		cout << ch << " ";		//1 2 3 4 5
	cout << endl;
	cout << v.size() << endl;		//8
	cout << v.capacity() << endl;	//8

	vector<int> v1 = { 12,23,45,56 };	 
	v.assign(v1.begin(),v1.end());
	for (const auto& ch : v)
		cout << ch << " ";		//12 23 45 56
	cout << endl;
	cout << v.size() << endl;		//4
	cout << v.capacity() << endl;	//8

	v.assign(10,'a');
	for (const auto& ch : v)
		cout << ch << " ";		//97 97 97 97 97 97 97 97 97 97 
	cout << endl;
	cout << v.size() << endl;		//10
	cout << v.capacity() << endl;	//12
}

//push_back	pop_back insert erase
void test8()
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
}

struct C
{
	explicit C(int c,int b)
		:_c(c)
		,_b(b)
	{}

private:
	int _c;
	int _b;
};

//emplace emplace_back
void test9()
{
	vector<C> v;
	C c1(1,2);
	v.push_back(c1);
	//v.push_back(2,2);			//不允许单参构造，也不允许传递没有创建的对象
	v.emplace_back(2,2);		//支持的，用参数调用构造函数创建一个对象，把这个对象插入到vector末尾
	//emplace只需要传递构造函数需要的参数，接口内部直接创建对象	
	//自定义类型emplace_back比push_back有优势，emplace比insert有优势
	v.emplace_back(c1);
	v.insert(v.begin(), C(2, 3));
	//v.insert(v.begin(), 2, 3);	//error
	v.emplace(v.begin(), 5, 6);		//在头部插入(5,6)

	//总结：
	//push_back和insert插入的必须是已经创建的对象；
	//emplace和emplace_back可以插入匿名对象，没有创建的对象可以出入；
	//emplace和emplace_back在插入的时候构造对象，构造对象并插入
	//push_back和insert不会构造对象

	//emplace返回一个指向已插入元素的迭代器，emplace_back不返回值。
}

//增容的规则
void test10()
{
	vector<int> v;
	size_t c = v.capacity();	 
	cout << c << endl;		//0
	for (size_t i = 0; i < 200; ++i)
	{
		v.push_back(i);
		if (c != v.capacity())
		{
			c = v.capacity();
			cout << c << endl;
		}
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
	//在va2017中是1.5倍的增容，在Linux下是2倍的增容
}

//迭代器失效问题
void test11()
{
	vector<int> v(3, 10);		//3个元素，值为10
	vector<int>::iterator it = v.begin();
	
	cout << *it << endl;	//10
	v.push_back(4);
	//cout << *it << endl;//error,错误原因：在尾插的时候增容了，原先的空间释放了，迭代器指向原来的空间不能访问了
	//解决措施，每次增容之后重新获取容器的迭代器
	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";		//10 10 10 4
		++it;
	}
	cout << endl;

	//erase
	it = v.begin();
	cout << *it << endl;	//10
	v.erase(it);
	//cout << *it << endl;	//eror，错误原因：迭代器错位，编译器检查比较严格（迭代器指向的位置发生了变化）
	//迭代器失效，为了避免删除的是最后一个元素，下一个元素不可访问

	//会导致迭代器可能失效的接口：
	//增容：resize、reserve、push_back、insert、emplace、emplace_back
	//删除操作：erase、pop_back、clear（清空vector容器中的所有元素）
}

//删除所有的偶数
void test12()
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
}

//vector容器中的swap，vector没有提供find接口，algorithm提供了find接口
void test13()
{
	vector<int> v1 = { 1,2,3,4,5 };
	//在v1中查找元素2
	for (const auto&ch : v1)	
		cout << ch << " ";		//1 2 3 4 5
	cout << endl;
	
	vector<int>::iterator pos = find(v1.begin(),v1.end(),2);	//返回2位置的迭代器
	cout << *pos << endl;	//2
	v1.erase(pos);
	vector<int>::iterator it = v1.begin();
	while (it != v1.end())
	{
		cout << *it << " ";		//1 3 4 5
		++it;
	}
	cout << endl;

	vector<int> v2(8, 10);
	cout << v1.size() << endl;		//4
	cout << v1.capacity() << endl;	//5
	cout << v2.size() << endl;		//8
	cout << v2.capacity() << endl;	//8
	for (const auto&ch : v2)
		cout << ch << " ";		//10 10 10 10 10 10 10 10 
	cout << endl;

	v1.swap(v2);
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
		cout << *it << " ";		//10 10 10 10 10 10 10 10 
	cout << endl;
	for (vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
		cout << *it << " ";		//1 3 4 5
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
	test13();
	return 0;
}