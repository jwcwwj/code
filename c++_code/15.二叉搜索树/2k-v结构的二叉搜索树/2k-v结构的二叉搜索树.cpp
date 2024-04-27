#include <iostream>
#include <string>
#include <time.h>

using namespace std;

//�����������Ľڵ�
template <class K,class V>
//template <class T>
struct BNode
{
	//BNode(const T& data)
	BNode(const K& key,const V& value)
		//:_data(data)
		:_key(key)
		,_value(value)		//K,V���ɵ�һ�����ݶ�
		, _left(nullptr)
		, _right(nullptr)
	{}

	K _key;		//�������������������κ����ͣ���һ���Ǹ�����     
	V _value;	//������data
	typedef BNode<K, V> Node;
	//T _data; 
	//typedef BNode<T> Node;
	Node* _left;
	Node* _right;
};

//��������������ͳ�Ķ���������һ�㲻����ظ���ֵ��ÿ��ֵ����Ψһ��
//template <class T>
template <class K,class V>
class BTree
{
public:
	//typedef BNode<T> Node;
	typedef BNode<K,V> Node;

	//���캯������������
	BTree()
		:_root(nullptr)
	{}

	//�����������Ĳ���
	//Node* find(const T& val)
	Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			//ÿһ�Ĳ��������ڶ��ֲ��ҵĲ�����ƽ��ʱ�临�Ӷ���O(h)��h�����ĸ߶ȡ�
			//�������������һ������һ��ֱ�ߣ�����ʱ�临�Ӷ���O(n)��n�����Ľڵ����������Ҳ�Ǹ߶ȡ�
			if (cur->_key == key)
				return cur;
			else if (cur->_key > key)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		return nullptr;		//��ʾû�ҵ�
	}

	//�����������ڵ�Ĳ��룺�������ظ���ֵ�������ظ���ֵ��ʧ��
	//����������һ�㲻����ظ���ֵ
	bool insert(const K& key,const V& value)
	{
		if (_root == nullptr)
		{
			//����
			_root = new Node(key,value);
			return true;
		}

		//ʣ�µ�Ԫ�ز��벻�ǿ�����ʱ��Ҫ������������֤�����ظ�������
		//�²����Ԫ��һ����Ҷ�ӽڵ㣺�������Ľڵ������
		//�����ƽ��ʱ�临�Ӷ���O(n)��ȡ�������������ң�������
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			//������Ҫ��¼���׵Ľڵ㣬֮��Ҫ����
			parent = cur;
			if (cur->_key == key)
				return false;	//����ʧ��
			else if (cur->_key > key)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//����
		if (parent->_key > key)
			parent->_left = new Node(key,value);
		else
			parent->_right = new Node(key,value);

		return true;		//����ɹ�
	}

	//�������
	void inorder()
	{
		_inorder(_root);
	}

	void _inorder(Node* root)
	{
		if (root)
		{
			_inorder(root->_left);
			cout << root->_key << "->" << root->_value << " ";
			_inorder(root->_right);
		}
	}

	//�������������������ݺͽṹ
	Node* copy(Node* root)
	{
		if (root == nullptr)
			return root;

		Node* newNode = new Node(root->_key,root->_value);
		newNode->_left = copy(root->_left);
		newNode->_right = copy(root->_right);
		//newNode->_left = new Node(root->_left->_data);
		//newNode->_right = new Node(root->_right->_data);
		return newNode;
	}

	//��������
	BTree(const BTree<K,V>& btree)
		:_root(copy(btree._root))
	{
		//_root = copy(btree._root);
	}

	//������
	void destory(Node* root)
	{
		if (root)
		{
			destory(root->_left);
			destory(root->_right);
			cout << "destory��" << root->_key << "->" << root->_value << endl;	//����deleteǰ���ֹ���ʵ���Ұָ��
			delete root;
			//root = nullptr;
		}
	}

	//��������
	~BTree()
	{
		if (_root)
		{
			destory(_root);
			_root = nullptr;
		}
	}

	//�����������ڵ��ɾ��
	bool erase(const K& key)
	{
		//����
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_key == key)	//�ҵ���
				break;
			parent = cur;		//���¸��׽ڵ��λ�ã�����֮��ɾ������
			if (cur->_key > key)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//�ж���Ҫɾ���Ľڵ��Ƿ��ҵ���
		if (cur == nullptr)
			return false;

		//ɾ��
		//1.ɾ������Ҷ�ӽڵ�
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			//1.1���������ɾ������Ҷ�ӽڵ����Ǹ��ڵ�
			if (cur == _root)
				_root = nullptr;
			else
			{
				//1.2һ�������ɾ������Ҷ�ӽڵ㣬�����Ǹ��ڵ�
				//�ж�ɾ���Ľڵ��ڸ��׽ڵ����һ��
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}

			//ɾ���ڵ�
			delete cur;
		}
		//2.ɾ�����Ƿ�Ҷ�ӽڵ���Ҫɾ���Ľڵ�����Ϊ��
		else if (cur->_left == nullptr)
		{
			//��һ��������Թ鵽�ڶ��ֻ��ߵ����֣���Ϊ������nullptr���������Ϊ����������
			//2.1ɾ�����Ƿ�Ҷ�ӽڵ�����ɾ���Ľڵ��Ǹ��ڵ�
			if (cur == _root)
				_root = cur->_right;
			else
			{
				//2.2ɾ�����Ƿ�Ҷ�ӽڵ㣬��ɾ���Ľڵ㲻�Ǹ��ڵ�
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}

			//ɾ���ڵ�
			delete cur;
		}
		//3.ɾ�����Ƿ�Ҷ�ӽڵ���Ҫɾ���Ľڵ���ұ�Ϊ��
		else if (cur->_right == nullptr)
		{
			//3.1ɾ�����Ƿ�Ҷ�ӽڵ�����ɾ���Ľڵ��Ǹ��ڵ�
			if (cur == _root)
				_root = cur->_left;
			else
			{
				//3.2ɾ�����Ƿ�Ҷ�ӽڵ㣬��ɾ���Ľڵ㲻�Ǹ��ڵ�
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
			}

			//ɾ���ڵ�
			delete cur;
		}
		//4.ɾ������Ҷ�ӽڵ�����������������
		else
		{
			//4.1�����������������ҽڵ�
			Node* leftRigthMost = cur->_left;
			parent = cur;

			//�ҵ����������ұߵ�Ҷ�ӽڵ�
			while (leftRigthMost->_right)
			{
				parent = leftRigthMost;
				leftRigthMost = leftRigthMost->_right;
			}

			//�������������ұߵ�Ҷ�ӽڵ��ֵ��Ҫɾ���ڵ��ֵ
			swap(leftRigthMost->_key, cur->_key);
			swap(leftRigthMost->_value, cur->_value);

			//ɾ�����������ҽڵ�
			if (parent->_right == leftRigthMost)
				//һֱ�����������������ҽڵ�
				parent->_right = leftRigthMost->_left;
			else
				//leftRigthMost�ұ߸տ�ʼ����һ������
				parent->_left = leftRigthMost->_left;
			//������//leftRigthMost�ұ߸տ�ʼ����һ������
			//						5
			//				4
			//		2
			//	1		3
			//Ҫɾ���Ľڵ���5��leftRigthMost��4��4���ұ�û�нڵ�
			//�����ڵ�4�ͽڵ�5��ֵ
			//						4
			//				5
			//		2
			//	1		3
			//4���������2�����ɾ��5
			//				4
			//		2
			//	1		3
			delete leftRigthMost;
		}

		return true;
	}

	//private:
	Node* _root;		//���ڵ�
};

//K-V�ṹ�Ķ����������Ĳ����ɾ��
void test()
{
	BTree<int, int> b;
	b.insert(5, 50);
	b.insert(3, 30);
	b.insert(7, 70);
	b.insert(1, 10);
	b.insert(4, 40);
	b.insert(6, 60);
	b.insert(8, 80);
	b.insert(0, 100);
	b.insert(2, 50);
	b.insert(9, 90);
	//�����keyֵ�����ظ��������ظ���keyֵ���ᱨ���᷵��false����ʾ����ʧ��
	
	b.inorder();
	cout << endl;

	b.erase(5);
	b.erase(3);
	b.erase(8);
	b.erase(9);
	b.erase(4);
	b.erase(6);

	b.inorder();
	cout << endl;
	//�����
	//0->100 1->10 2->50 3->30 4->40 5->50 6->60 7->70 8->80 9->90
	//0->100 1->10 2->50 7->70
	//destory��0->100
	//destory��1->10
	//destory��7->70
	//destory��2->50
}

int main()
{
	test();
	return 0;
}