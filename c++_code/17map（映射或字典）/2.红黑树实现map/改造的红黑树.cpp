#include <iostream>

using namespace std;

enum COLOR
{
	BLACK,
	RED
};

template <class V>
struct RBNode
{
	//typedef bool color;		STL中的实现
	RBNode<V>* _parent;
	RBNode<V>* _left;
	RBNode<V>* _right;

	V _val;		//数据
	COLOR _color;		//颜色

	//构造函数
	RBNode(const V& val = V())
		: _parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _val(val)
		, _color(RED)
	{}
};

template <class V>
struct RBTreeIterator
{
	typedef RBNode<V> Node;
	typedef RBTreeIterator<V> Self;
	Node* _node;

	RBTreeIterator(Node* node)
		:_node(node)
	{}

	V& operator*()
	{
		return _node->_val;
	}

	V& operator->()
	{
		return &_node->_val;
	}

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	//中序遍历
	Self& operator++()
	{
		if (_node->_right)
		{
			//右子树的最左节点
			_node = _node->_right;
			while (_node->_left)
			{
				_node = _node->_left;
			}
		}
		else
		{
			//回退
			Node* parent = _node->_parent;
			while (_node == parent->_right)
			{
				_node = parent;
				parent = _node->_parent;
			}

			if(_node->_right != parent)		//防止_node是parent节点,_node->_right == parent(避免没有右子树的情况)
				_node = parent;
		}
		return *this;
	}

	//反向中序遍历
	Self& operator--()
	{
		if (_node->_left)
		{
			//访问左子树的最右节点
			_node = _node->_left;
			while (_node->_right)
			{
				_node = _node->_right;
			}
		}
		else
		{
			//回退
			Node* parent = _node->_parent;
			while (_node == parent->_left)
			{
				_node = parent;
				parent = _node->_parent;
			}

			//防止_node是parent节点,_node->_left == parent(避免没有左子树的情况)
			if (_node->_left != parent)		 
				_node = parent;
		}
		return *this;
	}
};

//keyofvalue：通过value获取对应的key
template <class K, class V,class keyofvalue>
class RBTree
{
public:
	typedef RBNode<V> Node; 
	typedef RBTreeIterator<V> iterator;

	RBTree()
		:_header(new Node)
	{
		//创建空树
		_header->_left = _header;
		_header->_right = _header;
	}

	//迭代器
	iterator begin()
	{
		return iterator(_header->_left);
	}

	iterator end()
	{
		return iterator(_header);
	}

	iterator rbegin()
	{
		return iterator(_header->_right);
	}

	iterator rend()
	{
		return iterator(_header);
	}


	//插入
	//bool insert(const V& val)
	pair<iterator,bool> insert(const V& val)
	{
		//1.搜索树的插入
		//空树；_header->_parent：nullptr
		if (_header->_parent == nullptr)
		{
			cout << "根节点插入" << endl;
			//空树	创建根节点
			Node* root = new Node(val);

			//连接
			_header->_parent = root;
			root->_parent = _header;
			_header->_left = _header->_right = root;

			//根节点是黑色
			root->_color = BLACK;
			//return true;
			return make_pair(iterator(root), true);
		}

		//从根节点开始搜索
		Node* cur = _header->_parent;
		Node* parent = nullptr;

		keyofvalue kov;

		while (cur)
		{
			parent = cur;
			//和pair中的key进行比较，key不允许重复
			//if (cur->_val.first == val.first)
			if (kov(cur->_val) == kov(val))
				//return false;		//key值不允许重复
				return make_pair(iterator(cur), false);
			//else if (cur->_val.first > val.first)
			else if (kov(cur->_val) > kov(val))
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//创建待插入的节点
		try
		{
			cur = new Node(val);
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}

		//记录下，后面要返回make_pair
		Node* node = cur;

		//if (parent->_val.first > cur->_val.first)
		if(kov(parent->_val) > kov(cur->_val))
			parent->_left = cur;
		else
			parent->_right = cur;

		cur->_parent = parent;

		//2.修改颜色或者调整结构
		//判断是否有红色连续的节点，红色连续就进行修改
		while (cur != _header->_parent && cur->_parent->_color == RED)
		{
			//	 gfather
			//parent
			//cur
			parent = cur->_parent;
			Node* gfather = parent->_parent;

			//确定叔叔节点的位置
			if (gfather->_left == parent)
			{
				//叔叔的节点在右边
				Node* uncle = gfather->_right;
				//uncle存在
				if (uncle && uncle->_color == RED)
				{
					cout << "修改颜色" << endl;
					//这种情况有可能把根节点的颜色从黑色修改为红色，最后会把红色修改为黑色，这种情况会增加黑色节点的个数
					parent->_color = uncle->_color = BLACK;
					gfather->_color = RED;
					//继续更新
					cur = gfather;
				}
				else
				{
					cout << "旋转" << endl;
					//判断是否为双旋的场景
					if (cur == parent->_right)
					{
						//左旋
						RotateL(parent);
						//交换cur和parent的指向，退化为右旋的场景，直接走下面右旋的场景
						swap(cur, parent);
					}
					//两种情况：
					//叔叔节点存在，并且颜色为黑
					//叔叔节点不存在
					//都需要右旋
					RotateR(gfather);
					parent->_color = BLACK;
					gfather->_color = RED;
					break;
					//细节：修改之前和修改之后的黑色节点的个数是不变的（只有根的地方有可能增加黑色节点的个数）
				}
			}
			else if (gfather->_right == parent)
			{
				//叔叔的节点在左边
				Node* uncle = gfather->_left;

				//uncle存在
				if (uncle && uncle->_color == RED)
				{
					cout << "修改颜色" << endl;
					//这种情况有可能把根节点的颜色从黑色修改为红色，最后会把红色修改为黑色，这种情况会增加黑色节点的个数
					parent->_color = uncle->_color = BLACK;
					gfather->_color = RED;
					//继续更新
					cur = gfather;
				}
				else
				{
					cout << "旋转" << endl;
					//判断是否为双旋的场景
					if (cur == parent->_left)
					{
						//右旋
						RotateR(parent);
						//交换cur和parent的指向，退化为左旋的场景，直接走下面右旋的场景
						swap(cur, parent);
					}
					//两种情况：
					//叔叔节点存在，并且颜色为黑
					//叔叔节点不存在
					//都需要左旋
					RotateL(gfather);
					parent->_color = BLACK;
					gfather->_color = RED;
					break;
					//细节：修改之前和修改之后的黑色节点的个数是不变的（只有根的地方有可能增加黑色节点的个数）
				}
			}
		}

		//根节点的颜色改为黑色
		_header->_parent->_color = BLACK;

		//更新_header的左右指向
		_header->_left = leftMost();
		_header->_right = rightMost();

		//return true;
		return make_pair(iterator(node), true);
	}

	//最左节点
	Node* leftMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return cur;
	}

	//最右节点
	Node* rightMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_right)
		{
			cur = cur->_right;
		}
		return cur;
	}

	//中序遍历
	void inorder()
	{
		_inorder(_header->_parent);
		cout << endl;
	}

	void _inorder(Node* root)
	{
		if (root)
		{
			_inorder(root->_left);
			cout << root->_kv.first << " ";
			_inorder(root->_right);
		}
	}

	//左旋
	//parent
	//			subR
	//	  subRL（不一定存在）
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;

		//判断parent节点是不是根节点
		if (parent == _header->_parent)
		{
			_header->_parent = subR;
			subR->_parent = _header;
		}
		else
		{
			Node* pparent = parent->_parent;
			if (pparent->_left == parent)
				pparent->_left = subR;
			else
				pparent->_right = subR;
			subR->_parent = pparent;
		}

		parent->_parent = subR;
	}

	//右旋
	//			parent
	//subL
	//	   subLR（不一定存在）
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//连接
		subL->_right = parent;
		parent->_left = subLR;

		if (subLR)
			subLR->_parent = parent;

		//判断parent节点是不是根节点
		if (parent == _header->_parent)
		{
			_header->_parent = subL;
			subL->_parent = _header;
		}
		else
		{
			Node* pparent = parent->_parent;
			if (pparent->_left == parent)
				pparent->_left = subL;
			else
				pparent->_right = subL;
			subL->_parent = pparent;
		}

		parent->_parent = subL;
	}

	//验证满不满足红黑树的性质：
	//1.根：黑色
	//2.每条路径上的黑色个数相同
	//3.红色不能连续
	bool isBalance()
	{
		if (_header->_parent == nullptr)
		{
			//空树被认为是红黑树	有个虚拟节点是黑色的
			return true;
		}

		Node* root = _header->_parent;

		//1.根：黑色
		if (root->_color == RED)
			return false;

		//2.每条路径上的黑色个数相同
		//统计一条路径上的黑色节点个数
		int bCount = 0;	//黑色节点的个数
		Node* cur = root;
		while (cur)
		{
			if (cur->_color == BLACK)
				++bCount;
			cur = cur->_left;
		}

		//遍历每一条路径
		int curBCount = 0;
		//参数：遍历起始的点	黑色节点的个数	当前黑色的个数	
		return _isBalance(root, bCount, curBCount);
	}

	bool _isBalance(Node* root, int& bCount, int curBCount)
	{
		//当root为空时，一条路径遍历结束
		if (root == nullptr)
		{
			//判断黑色节点的个数是否相同
			if (curBCount != bCount)
				return false;
			else
				return true;
		}

		//判断节点是否为黑色
		if (root->_color == BLACK)
			++curBCount;

		//判断是否有红色连续的节点
		if (root->_parent && root->_color == RED && root->_parent->_color == RED)
		{
			cout << "Data：" << root->_kv.first << endl;
			return false;		//有红色连续的节点
		}

		_isBalance(root->_left, bCount, curBCount) && (root->_right, bCount, curBCount);
	}

private:
	Node* _header;	//头结点
};



