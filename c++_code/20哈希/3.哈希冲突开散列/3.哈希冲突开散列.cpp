#include <iostream>
//#include <list>
#include <vector> 
#include <utility>
#include <string>
#include <unordered_set>

using namespace std;

//开散列也叫做哈希桶	哈希桶理想情况是每个链表中存储一个数据
template <class V>
struct HashNode
{
	V _val;
	HashNode<V>* _next;		//链表节点

	HashNode(const V& val)
		:_val(val)
		,_next(nullptr)
	{}
};

//哈希表前置声明
template<class K, class V, class KeyOfValue, class HashFun = HashFun<K>>	
//template<class K, class V, class KeyOfValue, class HashFun>
class HTable;	

//哈希表迭代器：自定义类型
//通过封装单链表的节点实现
template<class K, class V, class KeyOfValue,class HashFun = HashFun<K>>
struct HashIterator
{
	typedef HashIterator<K,V,KeyOfValue,HashFun> Self;
	//哈希表指针
	typedef HTable<K, V, KeyOfValue, HashFun> HT;
	//成员：节点指针
	typedef HashNode<V> Node;

	HT* _hPtr;

	Node* _node;

	HashIterator(Node* node, HT* hPtr)
		:_node(node)
		,_hPtr(hPtr)
	{}

	V& operator*()
	{
		return _node->_val;
	}

	V* operator->()
	{
		return &_node->_val;
	}

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	Self& operator++()
	{
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			//查找下一个非空链表的头结点
			//计算当前节点在哈希表中的位置
			KeyOfValue kov;
			HashFun hfun;

			size_t idx = hfun(kov(_node->_val)) % _hPtr->_ht.size();
			//从下一个哈希位置开始查找
			++idx;
			while (idx < _hPtr->_ht.size())
			{
				if (_hPtr->_ht[idx])
				{
					//找到下一个非空链表
					_node = _hPtr->_ht[idx];
					break;
				}
				++idx;
			}

			//没有找到一个有效节点
			if (idx == _hPtr->_ht.size())
				_node = nullptr;
		}
		return *this;
	}

	/*
	iterator begin()
	{
		//第一个非空链表的头结点
		for (size_t i = 0; i < this->_ht.size(); ++i)
		{
			if (this->_ht[i])
			{
				return iterator(this->_ht[i], this);
			}
		}

		return iterator(nullptr, this);
	}

	iterator end()
	{
		return iterator(nullptr, this);
	}
	*/
};

//哈希表	
//HashFun：把类型不是数值的key，经过相应的运算转化为相应数值结果
//重定义默认参数：声明和定义只需一处给出默认值（一般推荐在声明处给出）
template<class K,class V,class KeyOfValue,class HashFun>
//哈希函数用来减少哈希冲突
//template<class K, class V, class KeyOfValue, class HashFun = HashFun<K>>
class HTable
{
public:
	typedef HashNode<V> Node;
	typedef	HashIterator<K, V, KeyOfValue, HashFun> iterator;

	//把迭代器类声明成友元类
	template<class K, class V, class KeyOfValue,class HashFun>
	friend struct HashIterator;

	iterator begin()
	{
		//第一个非空链表的头结点
		for (size_t i = 0; i < _ht.size(); ++i)
		{
			if (_ht[i])
			{
				return iterator(_ht[i], this);
			}
		}

		return iterator(nullptr, this);
	}

	iterator end()
	{
		return iterator(nullptr, this);
	}

	HTable(int n =10)
		:_ht(n)
		,_size(0)
	{}

	//bool insert(const V& val)	//这里的val可能是k，也可能是kv键值对
	pair<iterator,bool> insert(const V& val)
	{
		//0.检查容量
		checkCapacity();

		//1.计算哈希位置
		KeyOfValue kov;
		HashFun hfun;		//把K值经过相应的运算转化为相应的数值

		size_t idx = hfun(kov(val))  % _ht.size();

		//2.查找
		Node* cur = _ht[idx];		//cur是链表的首地址
		while (cur)
		{
			if (kov(cur->_val) == kov(val))
			{
				//key重复
				//return false;
				return make_pair(iterator(cur,this), false);
				//this是哈希表指针
			}

			cur = cur->_next;
		}

		//3.插入：头插
		cur = new Node(val);
		cur->_next = _ht[idx];
		_ht[idx] = cur;
		++_size;
		//return true;
		return make_pair(iterator(cur, this), true);
	}

	//素数表：减少哈希冲突的概率
	size_t GetNextPrime(size_t prime)
	{
		const int PRIMECOUNT = 28;
		const size_t primeList[PRIMECOUNT] =
		{
		53ul, 97ul, 193ul, 389ul, 769ul,
		1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
		49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
		1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
		50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
		};

		size_t i = 0;
		for (; i < PRIMECOUNT; ++i)
		{
			if (primeList[i] > prime)
				return primeList[i];
		}
		return primeList[PRIMECOUNT - 1];
	}

	//扩容
	void checkCapacity()
	{
		//_size是哈希桶元素个数的大小，_ht.size()是指针数组（vector）的大小
		if (_size == _ht.size())
		{
			//int newC = _size == 0 ? 10 : 2 * _size;
			size_t newC = GetNextPrime(_ht.size());

			//创建新的指针数组
			vector<Node*> newHt(newC);

			KeyOfValue kov;
			HashFun hfun;

			//遍历旧表
			for (size_t i = 0; i < _ht.size(); ++i)
			{
				Node* cur = _ht[i];		//链表的头结点
				//遍历单链表
				while(cur)
				{
					//记录下一个位置
					Node* next = cur->_next;

					//计算新的位置
					int idx = hfun(kov(cur->_val)) % newHt.size();

					//头插
					cur->_next = newHt[idx];
					newHt[idx] = cur;

					cur = next;
				}

				//旧表指针置空
				_ht[i] = nullptr;
			}

			//旧表和新表交换内内容
			swap(_ht, newHt);	//_size没有改变，不用交换
		}
	}

	Node* find(const K& key)
	{
		KeyOfValue kov;
		if (key < 0)
			return nullptr;

		size_t idx = key % _ht.size();

		Node* cur = _ht[idx];		//头结点
		while (cur)
		{
			//遍历链表找到key
			if (KeyOfValue(cur->_val) == key)
				return cur;
			else
				cur = cur->_next;
		}

		return nullptr;
	}

	bool erase(const K& key)
	{
		KeyOfValue kov;
		if (key < 0)
			return nullptr;

		size_t idx = key % _ht.size();

		Node* cur = _ht[idx];		//头结点
		Node* prev = nullptr;
		while (cur)
		{
			//单链表的删除
			if (KeyOfValue(cur->_val) == key)
			{
				if (prev == nullptr)
				{
					//删除的是头结点
					_ht[idx] = cur->_next;
				}
				else
				{
					//删除的不是头结点
					prev->_next = cur->_next;
				}

				--_size;
				delete cur;
				return true;
			}
			else
			{
				prev = cur;
				cur = cur->_next;
			}
		}
		return false;
	}

private:	
	vector<Node*> _ht;	//指针数组
	int _size;
};

template <class K>
struct HashFun
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

//特化
template <>
struct HashFun<string>
{
	size_t operator()(const string& key)
	{	
		size_t hash = 0;
		for (const auto& ch : key)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

template <class K>
class Set
{
	struct SetKeyOfValue
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};

public:
	//typename：因为哈希表没确定
	typedef typename HTable<K, K, SetKeyOfValue>::iterator iterator;

	iterator begin()
	{
		return _ht.begin();
	}

	iterator end()
	{
		return _ht.end();
	}

	pair<iterator, bool> insert(const K& key)
	{
		return _ht.insert(key);
	}

private:
	HTable<K, K, SetKeyOfValue> _ht;
};

void test1()
{
	Set<int> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(13);
	s.insert(44);
	s.insert(45);
	s.insert(17);
	s.insert(6);
	s.insert(16);
	s.insert(11);

	Set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;


	for (const auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}

template <class K, class V>
class Map
{
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& val)
		{
			return val.first;
		}
	};

public:
	typedef typename HTable<K, pair<K, V>, MapKeyOfValue>::iterator iterator;

	V& operator[](const K& key)
	{
		pair<iterator, bool> ret = _ht.insert(make_pair(key, V()));
		return (*ret.first).second;
	}

	iterator begin()
	{
		return _ht.begin();
	}

	iterator end()
	{
		return _ht.end();
	}

	pair<iterator, bool> insert(const pair<K, V>& val)
	{
		return _ht.insert(val);
	}

private:
	HTable<K, pair<K, V>, MapKeyOfValue> _ht;
};


void test2()
{
	Map<int,int> m;
	m.insert(make_pair(1, 1));
	m[20] = 20;		//插入
	m[30] = 30;
	m[1] = 100;		//修改
	m[30] = 300;	//修改
	m.insert(make_pair(20, 200));	//k不能重复，插入失败


	//Map<int, int>::iterator it = m.begin();
	struct HashIterator<int, struct std::pair<int, int>, struct Map<int, int>::MapKeyOfValue> it = m.begin();
	//auto it = m.begin();
	cout << typeid(it).name() << endl;
	while (it != m.end())
	{
		cout << (*it).first << " " << (*it).second << endl;
		++it;
	}
 
	for (const auto& p : m)
		cout << p.first << " " << p.second << endl;
}

void test3()
{
	Set<string> s;
	s.insert("1234");
}

/*
struct A
{
	int _a;
	string _b;
	double _d;

	bool operator==(A& a) const
	{
		return _a == a._a;// && _b == a._b;
		//return true;	//浮点数用 == 是不好的，浮点数是一个近似的数值
	}
};

struct HashFunA
{
	size_t operator()(const A& a) const
	{
		return a._a + (int)a._d;
	}
};

void test4()
{
	//Set<A> s;
	//s.insert(A());
	unordered_set<A, HashFunA> s2;
	s2.insert(A());
}
*/

struct A {
	int _a;
	string _b;
	double _d;

	bool operator==(const A& a) const {
		return _a == a._a && _b == a._b && _d == a._d;
	}
};

struct HashFunA {
	size_t operator()(const A& a) const {
		size_t hash = std::hash<int>{}(a._a);
		hash_combine(hash, std::hash<string>{}(a._b));
		hash_combine(hash, std::hash<double>{}(a._d));
		return hash;
	}

	// 辅助函数用于合并哈希值
	template <class T>
	static inline void hash_combine(std::size_t& seed, const T& val) {
		seed ^= std::hash<T>{}(val)+0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
};

void test4() {
	unordered_set<A, HashFunA> s2;
	s2.insert(A());
}

int main()
{
	test1();
	test2();
	test3();
	test4();
	return 0;
}