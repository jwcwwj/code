#include <iostream>
#include <string>
#include <time.h>

using namespace std;

//二叉搜索树的节点
template <class K,class V>
//template <class T>
struct BNode
{
	//BNode(const T& data)
	BNode(const K& key,const V& value)
		//:_data(data)
		:_key(key)
		,_value(value)		//K,V构成的一个数据对
		, _left(nullptr)
		, _right(nullptr)
	{}

	K _key;		//类似于索引，可以是任何类型，不一定是个整数     
	V _value;	//类似于data
	typedef BNode<K, V> Node;
	//T _data; 
	//typedef BNode<T> Node;
	Node* _left;
	Node* _right;
};

//二叉搜索树：传统的二叉搜索树一般不存放重复的值，每个值都是唯一的
//template <class T>
template <class K,class V>
class BTree
{
public:
	//typedef BNode<T> Node;
	typedef BNode<K,V> Node;

	//构造函数：创建空树
	BTree()
		:_root(nullptr)
	{}

	//二叉搜索树的查找
	//Node* find(const T& val)
	Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			//每一的查找类似于二分查找的操作，平均时间复杂度是O(h)，h是树的高度。
			//最差是树像链表一样，是一条直线，最差的时间复杂度是O(n)，n是树的节点个数，树的也是高度。
			if (cur->_key == key)
				return cur;
			else if (cur->_key > key)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		return nullptr;		//表示没找到
	}

	//二叉搜索树节点的插入：不插入重复的值，插入重复的值会失败
	//二叉搜索树一般不存放重复的值
	bool insert(const K& key,const V& value)
	{
		if (_root == nullptr)
		{
			//空树
			_root = new Node(key,value);
			return true;
		}

		//剩下的元素插入不是空树的时候要进行搜索，保证不是重复的数据
		//新插入的元素一般是叶子节点：避免树的节点的连接
		//插入的平均时间复杂度是O(n)，取决于搜索（查找）的性能
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			//搜索：要记录父亲的节点，之后要插入
			parent = cur;
			if (cur->_key == key)
				return false;	//插入失败
			else if (cur->_key > key)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//插入
		if (parent->_key > key)
			parent->_left = new Node(key,value);
		else
			parent->_right = new Node(key,value);

		return true;		//插入成功
	}

	//中序遍历
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

	//拷贝二叉搜索树的数据和结构
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

	//拷贝构造
	BTree(const BTree<K,V>& btree)
		:_root(copy(btree._root))
	{
		//_root = copy(btree._root);
	}

	//销毁树
	void destory(Node* root)
	{
		if (root)
		{
			destory(root->_left);
			destory(root->_right);
			cout << "destory：" << root->_key << "->" << root->_value << endl;	//放在delete前面防止访问的是野指针
			delete root;
			//root = nullptr;
		}
	}

	//析构函数
	~BTree()
	{
		if (_root)
		{
			destory(_root);
			_root = nullptr;
		}
	}

	//二叉搜索树节点的删除
	bool erase(const K& key)
	{
		//查找
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_key == key)	//找到了
				break;
			parent = cur;		//更新父亲节点的位置，方便之后删除操作
			if (cur->_key > key)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//判断需要删除的节点是否找到了
		if (cur == nullptr)
			return false;

		//删除
		//1.删除的是叶子节点
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			//1.1特殊情况：删除的是叶子节点且是根节点
			if (cur == _root)
				_root = nullptr;
			else
			{
				//1.2一般情况：删除的是叶子节点，但不是根节点
				//判断删除的节点在父亲节点的哪一边
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}

			//删除节点
			delete cur;
		}
		//2.删除的是非叶子节点且要删除的节点的左边为空
		else if (cur->_left == nullptr)
		{
			//第一种情况可以归到第二种或者第三种，因为连接是nullptr（可以理解为是特例）。
			//2.1删除的是非叶子节点且是删除的节点是根节点
			if (cur == _root)
				_root = cur->_right;
			else
			{
				//2.2删除的是非叶子节点，但删除的节点不是根节点
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}

			//删除节点
			delete cur;
		}
		//3.删除的是非叶子节点且要删除的节点的右边为空
		else if (cur->_right == nullptr)
		{
			//3.1删除的是非叶子节点且是删除的节点是根节点
			if (cur == _root)
				_root = cur->_left;
			else
			{
				//3.2删除的是非叶子节点，但删除的节点不是根节点
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
			}

			//删除节点
			delete cur;
		}
		//4.删除的是叶子节点且左右子树都存在
		else
		{
			//4.1假设找左子树的最右节点
			Node* leftRigthMost = cur->_left;
			parent = cur;

			//找到左子树最右边的叶子节点
			while (leftRigthMost->_right)
			{
				parent = leftRigthMost;
				leftRigthMost = leftRigthMost->_right;
			}

			//交换左子树最右边的叶子节点的值和要删除节点的值
			swap(leftRigthMost->_key, cur->_key);
			swap(leftRigthMost->_value, cur->_value);

			//删除左子树最右节点
			if (parent->_right == leftRigthMost)
				//一直遍历到左子树的最右节点
				parent->_right = leftRigthMost->_left;
			else
				//leftRigthMost右边刚开始就是一个空树
				parent->_left = leftRigthMost->_left;
			//举例：//leftRigthMost右边刚开始就是一个空树
			//						5
			//				4
			//		2
			//	1		3
			//要删除的节点是5，leftRigthMost是4，4的右边没有节点
			//交换节点4和节点5的值
			//						4
			//				5
			//		2
			//	1		3
			//4的左边连接2，最后删除5
			//				4
			//		2
			//	1		3
			delete leftRigthMost;
		}

		return true;
	}

	//private:
	Node* _root;		//根节点
};

//K-V结构的二叉搜索树的插入和删除
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
	//插入的key值不能重复，插入重复的key值不会报错，会返回false，表示插入失败
	
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
	//输出：
	//0->100 1->10 2->50 3->30 4->40 5->50 6->60 7->70 8->80 9->90
	//0->100 1->10 2->50 7->70
	//destory：0->100
	//destory：1->10
	//destory：7->70
	//destory：2->50
}

int main()
{
	test();
	return 0;
}