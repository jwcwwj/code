#include <iostream>
#include <vector>

using namespace std;

//״̬
enum STATE
{
	EXIST,	//����״̬
	DELETE,	//ɾ��״̬
	EMPTY	//��״̬
};

//��ϣ������̽��
template<class K,class V>
struct HashNode
{
	pair<K, V> _kv;			//ֵ
	STATE _state = EMPTY;	//״̬
};

//˳���ʵ��hash	���ֳɵ�˳���vector
template<class K, class V>
class HashTable
{
public:
	typedef HashNode<K, V> Node;

	//���캯��
	//��ʾ������n��Ԫ�أ���ЧԪ�صĸ�����0��
	HashTable(size_t n = 10)
		:_hTable(n)			//vector�ĵ��ι���
		,_size(0)
	{}

	bool insert(const pair<K, V>& kv)
	{
		//0.�������
		checkCapacity();

		//1.�����ϣλ��
		int idx = kv.first % _hTable.size();

		//2.�ж�key�Ƿ���ڣ�key������ͬ����ͬ�Ͳ���ʧ��
		while (_hTable[idx]._state != EMPTY)
		{
			//ֻ�й�ϣ��ͻ�Ż������������һ����O(1)�Ĳ���
			if (_hTable[idx]._state == EXIST && kv.first == _hTable[idx]._kv.first)
			{
				//key������ͬ����ͬ�Ͳ���ʧ��
				return false;
			}

			//��������
			++idx;

			//����ߵ���Ľ���λ���ˣ��ʹӱ�ͷ��ʼ��������
			if (idx == _hTable.size())
				idx = 0;
		}

		//����
		_hTable[idx]._kv = kv;
		_hTable[idx]._state = EXIST;
		++_size;

		return true;
	}

	void checkCapacity()
	{
		//�������� ���ڵ��� 0.7 ��Ҫ����
		//�������ӣ���ЧԪ�صĸ���	/	��Ĵ�С
		//��������ʼ����С��1��
		//��������ԽС��������ϣ��ͻ�ĸ���ԽС
		if (_hTable.size() == 0 || _size * 10 / _hTable.size() >= 7)		//�����Ƚϱ��⸡�����ľ�����ʧ
		{
			//���±�
			int newC = _hTable.size() == 0 ? 10 : 2 * _hTable.size();
			HashTable<K, V> newHT(newC);

			for (int i = 0; i < _hTable.size(); ++i)
			{
				//����״̬λ���ڵ�����
				if (_hTable[i]._state == EXIST)
				{
					newHT.insert(_hTable[i]._kv);
				}
			}

			//����
			Swap(newHT);
		}
	}

	void Swap(HashTable<K, V>& HT)
	{
		swap(_hTable, HT._hTable);
		swap(_size, HT._size);			//_size������������ν����Ϊ������_size���
	}

	//����
	Node* find(const K& key)
	{
		//����λ��
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

	//ɾ��
	bool erase(const K& key)
	{
		Node* node = find(key);

		if (node)
		{
			//��ɾ����ֻ���޸�Ԫ�ص�״̬����ЧԪ�صĴ�С
			--_size;
			node->_state = DELETE;
			return true;
		}

		return false;
	}

private:
	vector<Node> _hTable;			//�ɱ�Ŀռ�����Զ���������������ʱ�����vector�����������ͷſռ�
	size_t _size;					//��ЧԪ�صĸ���
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