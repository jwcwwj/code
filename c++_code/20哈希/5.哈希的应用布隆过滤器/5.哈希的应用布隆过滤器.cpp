#include <iostream>
#include <vector>
#include <string>

using namespace std;

//位图
class BitSet
{
public:
	//位图的内存大小和数据范围有关系
	BitSet(size_t range)
		:_bit(range / 32 + 1)
	{}

	//存储信息
	void set(size_t num)
	{
		//计算位置
		//1.计算整数位置：/ 32
		int idx = num / 32;
		//2.计算bit位置： % 32
		int bitIdx = num % 32;
		//把对应的bit位置置为1
		//按位或运算把对应的bit位置为1
		_bit[idx] |= (1 << bitIdx);
	}

	//查找信息
	bool test(size_t num)
	{
		int idx = num / 32;
		int bitIdx = num % 32;
		return (_bit[idx] >> bitIdx) & 1;
	}

	//删除信息
	void reset(size_t num)
	{
		int idx = num / 32;
		int bitIdx = num % 32;
		if (test(num))
			_bit[idx] &= ~(1 << bitIdx);
	}

private:
	vector<int> _bit;	//整数数组
};

//m：需要的bit位大小
//n：元素个数
//k：哈希函数个数
//k = m / n * ln2
//m = k * n * 1.4

//布隆过滤器	概率型容器：判断存在结果不一定正确		
//一般不提供删除操作：删除操作会存在误删
//使用场景：存放各种数据的简单信息
//时间复杂度：O(k)
template <class T,class Hash1, class Hash2, class Hash3>
class BloomFilter
{
public:
	BloomFilter(size_t num)
		: _bit(5 * num)
		, _bitCount(5 * num)
		,_size(0)
	{}

	//存储信息：使用多个bit位存储信息
	void set(const T& val)
	{
		Hash1 h1;
		Hash2 h2;
		Hash3 h3;
		
		int idx1 = h1(val) % _bitCount;		//将val经过哈希函数转换成数字可能会很大
		int idx2 = h2(val) % _bitCount;
		int idx3 = h3(val) % _bitCount;
		
		_bit.set(idx1);		//将数字idx1的bit位设置为1
		_bit.set(idx2);
		_bit.set(idx3);

		_size++;
	}

	//查找
	bool test(const T& val)
	{
		Hash1 h1;
		Hash2 h2;
		Hash3 h3;
		
		int idx1 = h1(val) % _bitCount;		//将val经过哈希函数转换成数字可能会很大
		int idx2 = h2(val) % _bitCount;
		int idx3 = h3(val) % _bitCount;
		
		if (!_bit.test(idx1))
			return false;
		if (!_bit.test(idx2))
			return false;
		if (!_bit.test(idx3))
			return false;

		//可以判断一定不存在，但不能保证一定存在
		return true;	//大多数情况下存在，但也可能不存在（结果有一定可能是错误的）
	}
	
	//布隆过滤器一般没有删除的接口
	//原因：因为不同元素占多个bit位，删除的这个元素的bit位可能是别的元素的bit位，
	//会误伤别的元素。
	//解决办法：代价比较大，
	//给每个bit位给一个累加计数器，多个数据包含这个bit位，
	//有多少数据包含这个bit位，这个bit位的计数器就是多少
	//累加计数器的问题：要是2位bit位的话，累加计数器最大值是3，要是加到4就会回到0。（累加计数器溢出/回绕问题）
	//提前不知道有多杀搜个数据包含这个bit位，就不知道要开多大的空间。（开32位也可能溢出）

private:
	BitSet _bit;	//封装位图
	size_t _bitCount;	//bit位的个数
	size_t _size;
};

//哈希函数
struct HashFun1
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (const auto& ch : str)
			hash = hash * 131 + ch;
		return hash;
	} 
};

struct HashFun2
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (const auto& ch : str)
			hash = hash * 1313131 + ch;
		return hash;
	}
};

struct HashFun3
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (const auto& ch : str)
			hash = hash * 65599 + ch;
		return hash;
	}
};

void test()
{
	BloomFilter<string, HashFun1, HashFun2, HashFun3> bf(10);		
	//最多10个数据，50个bit位

	string str1 = "https://bbs.hupu.com/clippers-postdate";
	string str2 = "https://my.hupu.com/155535087800136";
	string str3 = "https://bbs.hupu.com/61330352.html";
	string str4 = "https://bbs.hupu.com/61330353.html";

	bf.set(str1);
	bf.set(str2);
	bf.set(str3);

	cout << bf.test(str1) << endl;
	cout << bf.test(str2) << endl;
	cout << bf.test(str3) << endl;
	cout << bf.test(str4) << endl;

	//位图只能处理数值类型的数据，布隆过滤器可以处理不是数值类型的数据
	//布隆过滤器实现：位图 + 哈希函数
}

int main()
{
	test();
	return 0;
}