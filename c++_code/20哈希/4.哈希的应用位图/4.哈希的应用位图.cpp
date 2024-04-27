#include <iostream>
#include <vector>

using namespace std;

//位图：只能处理数值类型的数据
//使用场景：存放不重复数据的简单信息，不需要存放数据本身
//优点：节省空间，查找效率高，查找的时间复杂度是O(1)
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
		if(test(num))
			_bit[idx] &= ~(1 << bitIdx);
	}

private:
	vector<int> _bit;	//整数数组
};

void test()
{
	BitSet bit(512);
	bit.set(1);
	bit.set(512);
	bit.set(32);
	bit.set(64);
	bit.set(15);
	bit.set(47);
	//cout << bit._bit[0] << endl;
	//cout << bit._bit[16] << endl;
	//cout << bit.test(47) << endl;
	bit.reset(15);
	bit.reset(1);
}

int main()
{
	test();
	return 0;
}