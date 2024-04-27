#include <iostream>
//#include <list>
#include <vector> 
#include <utility>
#include <string>
#include <unordered_set>

using namespace std;

//��ɢ��Ҳ������ϣͰ	��ϣͰ���������ÿ�������д洢һ������
template <class V>
struct HashNode
{
	V _val;
	HashNode<V>* _next;		//����ڵ�

	HashNode(const V& val)
		:_val(val)
		,_next(nullptr)
	{}
};

//��ϣ��ǰ������
template<class K, class V, class KeyOfValue, class HashFun = HashFun<K>>	
//template<class K, class V, class KeyOfValue, class HashFun>
class HTable;	

//��ϣ����������Զ�������
//ͨ����װ������Ľڵ�ʵ��
template<class K, class V, class KeyOfValue,class HashFun = HashFun<K>>
struct HashIterator
{
	typedef HashIterator<K,V,KeyOfValue,HashFun> Self;
	//��ϣ��ָ��
	typedef HTable<K, V, KeyOfValue, HashFun> HT;
	//��Ա���ڵ�ָ��
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
			//������һ���ǿ������ͷ���
			//���㵱ǰ�ڵ��ڹ�ϣ���е�λ��
			KeyOfValue kov;
			HashFun hfun;

			size_t idx = hfun(kov(_node->_val)) % _hPtr->_ht.size();
			//����һ����ϣλ�ÿ�ʼ����
			++idx;
			while (idx < _hPtr->_ht.size())
			{
				if (_hPtr->_ht[idx])
				{
					//�ҵ���һ���ǿ�����
					_node = _hPtr->_ht[idx];
					break;
				}
				++idx;
			}

			//û���ҵ�һ����Ч�ڵ�
			if (idx == _hPtr->_ht.size())
				_node = nullptr;
		}
		return *this;
	}

	/*
	iterator begin()
	{
		//��һ���ǿ������ͷ���
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

//��ϣ��	
//HashFun�������Ͳ�����ֵ��key��������Ӧ������ת��Ϊ��Ӧ��ֵ���
//�ض���Ĭ�ϲ����������Ͷ���ֻ��һ������Ĭ��ֵ��һ���Ƽ���������������
template<class K,class V,class KeyOfValue,class HashFun>
//��ϣ�����������ٹ�ϣ��ͻ
//template<class K, class V, class KeyOfValue, class HashFun = HashFun<K>>
class HTable
{
public:
	typedef HashNode<V> Node;
	typedef	HashIterator<K, V, KeyOfValue, HashFun> iterator;

	//�ѵ���������������Ԫ��
	template<class K, class V, class KeyOfValue,class HashFun>
	friend struct HashIterator;

	iterator begin()
	{
		//��һ���ǿ������ͷ���
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

	//bool insert(const V& val)	//�����val������k��Ҳ������kv��ֵ��
	pair<iterator,bool> insert(const V& val)
	{
		//0.�������
		checkCapacity();

		//1.�����ϣλ��
		KeyOfValue kov;
		HashFun hfun;		//��Kֵ������Ӧ������ת��Ϊ��Ӧ����ֵ

		size_t idx = hfun(kov(val))  % _ht.size();

		//2.����
		Node* cur = _ht[idx];		//cur��������׵�ַ
		while (cur)
		{
			if (kov(cur->_val) == kov(val))
			{
				//key�ظ�
				//return false;
				return make_pair(iterator(cur,this), false);
				//this�ǹ�ϣ��ָ��
			}

			cur = cur->_next;
		}

		//3.���룺ͷ��
		cur = new Node(val);
		cur->_next = _ht[idx];
		_ht[idx] = cur;
		++_size;
		//return true;
		return make_pair(iterator(cur, this), true);
	}

	//���������ٹ�ϣ��ͻ�ĸ���
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

	//����
	void checkCapacity()
	{
		//_size�ǹ�ϣͰԪ�ظ����Ĵ�С��_ht.size()��ָ�����飨vector���Ĵ�С
		if (_size == _ht.size())
		{
			//int newC = _size == 0 ? 10 : 2 * _size;
			size_t newC = GetNextPrime(_ht.size());

			//�����µ�ָ������
			vector<Node*> newHt(newC);

			KeyOfValue kov;
			HashFun hfun;

			//�����ɱ�
			for (size_t i = 0; i < _ht.size(); ++i)
			{
				Node* cur = _ht[i];		//�����ͷ���
				//����������
				while(cur)
				{
					//��¼��һ��λ��
					Node* next = cur->_next;

					//�����µ�λ��
					int idx = hfun(kov(cur->_val)) % newHt.size();

					//ͷ��
					cur->_next = newHt[idx];
					newHt[idx] = cur;

					cur = next;
				}

				//�ɱ�ָ���ÿ�
				_ht[i] = nullptr;
			}

			//�ɱ���±���������
			swap(_ht, newHt);	//_sizeû�иı䣬���ý���
		}
	}

	Node* find(const K& key)
	{
		KeyOfValue kov;
		if (key < 0)
			return nullptr;

		size_t idx = key % _ht.size();

		Node* cur = _ht[idx];		//ͷ���
		while (cur)
		{
			//���������ҵ�key
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

		Node* cur = _ht[idx];		//ͷ���
		Node* prev = nullptr;
		while (cur)
		{
			//�������ɾ��
			if (KeyOfValue(cur->_val) == key)
			{
				if (prev == nullptr)
				{
					//ɾ������ͷ���
					_ht[idx] = cur->_next;
				}
				else
				{
					//ɾ���Ĳ���ͷ���
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
	vector<Node*> _ht;	//ָ������
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

//�ػ�
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
	//typename����Ϊ��ϣ��ûȷ��
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
	m[20] = 20;		//����
	m[30] = 30;
	m[1] = 100;		//�޸�
	m[30] = 300;	//�޸�
	m.insert(make_pair(20, 200));	//k�����ظ�������ʧ��


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
		//return true;	//�������� == �ǲ��õģ���������һ�����Ƶ���ֵ
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

	// �����������ںϲ���ϣֵ
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