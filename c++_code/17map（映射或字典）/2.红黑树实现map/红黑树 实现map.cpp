#include "改造的红黑树.cpp"

template <class K,class T>
class Map
{
	//内部类
	struct MapKeyOfValue
	{
		//仿函数：重载()运算符
		const K& operator()(const pair<K, T>& val)
		{
			return val.first;
		}
	};

public:
	typedef typename RBTree<K, pair<K, T>, MapKeyOfValue>::iterator iterator;

	iterator begin()
	{
		return _rbt.begin();
	}

	iterator end()
	{
		return _rbt.end();
	}

	iterator rbegin()
	{
		return _rbt.rbegin();
	}

	iterator rend()
	{
		return _rbt.rend();
	}

	pair<iterator,bool> insert(const pair<K, T>& kv)
	{
		return _rbt.insert(kv);
	}

	T& operator[](const K& key)
	{
		pair<iterator,bool> ret = _rbt.insert(make_pair(key, T()));
		return (*ret.first).second;		//pair中没有重载->
		//等价于	return ret.first.operator->()->second;
	}


private:
	typedef RBTree<K, pair<K, T>, MapKeyOfValue> rbt;
	rbt _rbt;
};

void test()
{
	Map<int, int> m;
	m.insert(make_pair(1, 1));
	m.insert(make_pair(2, 1));
	m.insert(make_pair(3, 1));
	m.insert(make_pair(4, 1));

	m[5] = 1;
	m[2] = 3;
	m[3] = 30;

	Map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << (*it).first << " " << (*it).second << endl;
		++it;
	}

	cout << endl;

	//中序遍历特殊情况，以正向迭代器为例
	//m.insert(4);
	//m.insert(3);
	Map<int, int>::iterator rit = m.rbegin();
	while (rit != m.rend())
	{
		cout << (*rit).first << " " << (*rit).second << endl;
		--rit;			//注意这里是--
	}

}

template <class K>
class Set
{
	struct SetKeyOfValue
	{
		const K& operator()(const K& val)
		{
			return val;
		}
	};

public:

	typedef typename RBTree<K, K, SetKeyOfValue>::iterator iterator;


	pair<iterator,bool> insert(const K& val)
	{
		return _rbt.insert(val);
	}

private:
	typedef RBTree<K, K, SetKeyOfValue> rbt;
	rbt _rbt;
};
 
void test2()
{
	Set<int> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);
}

int main()
{
	test();
	test2();
	return 0;
}