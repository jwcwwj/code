#include <iostream>
#include <vector>

using namespace std;

//状态
enum STATE
{
	EXIST,	//存在状态
	DELETE,	//删除状态
	EMPTY	//空状态
};

//哈希表：线性探测
template<class K,class V>
struct HashNode
{
	pair<K, V> _kv;			//值
	STATE _state = EMPTY;	//状态
};

//顺序表实现hash	用现成的顺序表vector
template<class K, class V>
class HashTable
{
public:
	typedef HashNode<K, V> Node;

	//构造函数
	//表示创建了n个元素，有效元素的个数是0个
	HashTable(size_t n = 10)
		:_hTable(n)			//vector的单参构造
		,_size(0)
	{}

	bool insert(const pair<K, V>& kv)
	{
		//0.检查容量
		checkCapacity();

		//1.计算哈希位置
		int idx = kv.first % _hTable.size();

		//2.判断key是否存在，key不能相同，相同就插入失败
		while (_hTable[idx]._state != EMPTY)
		{
			//只有哈希冲突才会走这个搜索，一般是O(1)的操作
			if (_hTable[idx]._state == EXIST && kv.first == _hTable[idx]._kv.first)
			{
				//key不能相同，相同就插入失败
				return false;
			}

			//继续搜索
			++idx;

			//如果走到表的结束位置了，就从表头开始继续搜索
			if (idx == _hTable.size())
				idx = 0;
		}

		//插入
		_hTable[idx]._kv = kv;
		_hTable[idx]._state = EXIST;
		++_size;

		return true;
	}

	void checkCapacity()
	{
		//负载因子 大于等于 0.7 需要增容
		//负载因子：有效元素的个数	/	表的大小
		//负载因子始终是小于1的
		//负载因子越小，产生哈希冲突的概率越小
		if (_hTable.size() == 0 || _size * 10 / _hTable.size() >= 7)		//整数比较避免浮点数的精度损失
		{
			//开新表
			int newC = _hTable.size() == 0 ? 10 : 2 * _hTable.size();
			HashTable<K, V> newHT(newC);

			for (int i = 0; i < _hTable.size(); ++i)
			{
				//插入状态位存在的数据
				if (_hTable[i]._state == EXIST)
				{
					newHT.insert(_hTable[i]._kv);
				}
			}

			//交换
			Swap(newHT);
		}
	}

	void Swap(HashTable<K, V>& HT)
	{
		swap(_hTable, HT._hTable);
		swap(_size, HT._size);			//_size交不交换无所谓，因为两个的_size相等
	}

	//查找
	Node* find(const K& key)
	{
		//计算位置
		int idx = key % _hTable.size();
		while (_hTable[idx]._state != EMPTY)
		{
			if (_hTable[idx]._state == EXIST && key == _hTable[idx]._kv.first)
			{
				return &_hTable[idx];
			}

			++idx;

			if (idx == _hTable.size())
			{
				idx = 0;
			}
		}

		return nullptr;
	}

	//删除
	bool erase(const K& key)
	{
		Node* node = find(key);

		if (node)
		{
			//假删除：只是修改元素的状态和有效元素的大小
			--_size;
			node->_state = DELETE;
			return true;
		}

		return false;
	}

private:
	vector<Node> _hTable;			//旧表的空间会在自动调用析构函数的时候调用vector的析构函数释放空间
	size_t _size;					//有效元素的个数
};

void test()
{
	HashTable<int, int> ht;
	ht.insert(make_pair(1, 1));
	ht.insert(make_pair(14, 14));
	ht.insert(make_pair(16, 16));
	ht.insert(make_pair(11, 11));
	ht.insert(make_pair(14, 140));
	ht.insert(make_pair(15, 1));
	ht.insert(make_pair(18, 14));
	ht.insert(make_pair(20, 16));
	ht.insert(make_pair(21, 11));
	ht.insert(make_pair(22, 140));
	ht.insert(make_pair(23, 1));
	ht.insert(make_pair(24, 14));
	ht.insert(make_pair(25, 16));
	ht.insert(make_pair(26, 11));
	ht.insert(make_pair(27, 140));
	ht.insert(make_pair(28, 11));
	ht.insert(make_pair(29, 140));

	cout << ht.find(11) << endl;
	cout << ht.find(100) << endl;

	cout << ht.erase(11) << endl;
	cout << ht.erase(100) << endl;
}

int main()
{
	test();
	return 0;
}