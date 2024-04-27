#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <stack>

using namespace std;

//二叉搜索树的节点
template <class T>
struct BNode
{
	BNode(const T& data)
		:_data(data)
		,_left(nullptr)
		,_right(nullptr)
	{}

	T _data;
	typedef BNode<T> Node;
	Node* _left;
	Node* _right;
};

//二叉搜索树：传统的二叉搜索树一般不存放重复的值，每个值都是唯一的
template <class T>
class BTree
{
public:
	typedef BNode<T> Node;

	//构造函数：创建空树
	BTree()
		:_root(nullptr)
	{}

	//二叉搜索树的查找
	Node* find(const T& val)
	{
		Node* cur = _root;
		while (cur)
		{
			//每一的查找类似于二分查找的操作，平均时间复杂度是O(h)，h是树的高度。
			//最差是树像链表一样，是一条直线，最差的时间复杂度是O(n)，n是树的节点个数，树的也是高度。
			if (cur->_data == val)
				return cur;
			else if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		return nullptr;		//表示没找到
	}

	//二叉搜索树节点的插入：不插入重复的值，插入重复的值会失败
	//二叉搜索树一般不存放重复的值
	bool insert(const T& val)
	{
		if (_root == nullptr)
		{
			//空树
			_root = new Node(val);
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
			if (cur->_data == val)
				return false;	//插入失败
			else if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//插入
		if (parent->_data > val)
			parent->_left = new Node(val);
		else
			parent->_right = new Node(val);

		/*
		cur = new Node(val);
		if (parent->_data > val)
			parent->_left = cur;
		else
			parent->_right = cur;
		*/

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
			cout << root->_data << " ";
			_inorder(root->_right);
		}
	}

	//拷贝二叉搜索树的数据和结构
	Node* copy(Node* root)
	{
		if (root == nullptr)
			return root;

		Node* newNode = new Node(root->_data);
		newNode->_left = copy(root->_left);
		newNode->_right = copy(root->_right);
		//newNode->_left = new Node(root->_left->_data);
		//newNode->_right = new Node(root->_right->_data);
		return newNode;	
	}

	//拷贝构造
	BTree(const BTree<T>& btree)
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
			cout << "destory：" << root->_data << endl;	//放在delete前面防止访问的是野指针
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
	bool erase(const T& val)
	{
		//查找
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_data == val)	//找到了
				break;
			parent = cur;		//更新父亲节点的位置，方便之后删除操作
			if (cur->_data > val)
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
			swap(leftRigthMost->_data, cur->_data);

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

//private:	//一般要将数据成员写成private，这里为了方便演示，也可以加上一个获取函数
	Node* _root;		//根节点
};

//二叉搜索树的中序遍历是有序的
//中序遍历：左 根 右 
void inorderTraversal(BNode<int>* root) 
{
	if (root == NULL)
		return;

	inorderTraversal(root->_left);
	cout << root->_data << " ";
	inorderTraversal(root->_right);
}

//插入，中序遍历输出
void test1()
{
	BTree<int> b;
	b.insert(50);
	b.insert(90);
	b.insert(30);
	b.insert(20);
	b.insert(80);
	b.insert(40);
	b.insert(70);
	b.insert(5);
	b.insert(500);

	inorderTraversal(b._root);
	cout << endl;
	
	b.inorder();
	cout << endl;
	
	b._inorder(b._root);
	printf("\n");
	//输出：
	//5 20 30 40 50 70 80 90 500
	//5 20 30 40 50 70 80 90 500
	//5 20 30 40 50 70 80 90 500
}

//随机数插入，中序遍历输出
void test2()
{
	BTree<int> b;
	srand(time(nullptr));	//随机数种子
	int num;
	cin >> num;
	for (int i = 0; i < num; ++i)
	{
		b.insert(rand());
	}

	b.inorder();
	cout << endl;
	BTree<int> copy(b);
	copy.inorder();
	cout << endl;
}

typedef BNode<int> Node;

vector<int> inorderTraversal1(Node* root)
{
	stack<Node*> st;
	vector<int> vec;    //保存遍历的节点的值，要返回的；
	Node* cur = root;

	//当前遍历的节点不为空（root节点不为空需要验证）或者栈不为空（栈刚开始为空需要去判断root）；
	while (cur || !st.empty())
	{
		//访问cur的最左边路径，直到为空节点，路径上的节点全部入栈，之后会访问栈顶元素的右子树
		while (cur)
		{
			st.push(cur);
			cur = cur->_left;
		}

		//获取栈顶元素
		cur = st.top();
		st.pop();
		//从栈中拿出一个节点就表示这个节点的左子树和根节点已经访问完成了

		vec.push_back(cur->_data);

		//访问右子树
		cur = cur->_right;        //循环访问当前节点为根的前序遍历
	}

	return vec;
}

//测试删除操作
void test3()
{
	BTree<int> b;
	b.insert(50);
	b.insert(90);
	b.insert(30);
	b.insert(20);
	b.insert(80);
	b.insert(40);
	b.insert(70);
	b.insert(5);
	b.insert(500);

	inorderTraversal(b._root);
	printf("\n");
	vector<int> v1 = inorderTraversal1(b._root);
	for (const auto& e : v1)
		cout << e << " ";
	cout << endl;
	b.erase(10);
	b.erase(30);
	b.erase(80);
	b.erase(40);
	b.erase(500);
	inorderTraversal(b._root);
	cout << endl;
	vector<int> v = inorderTraversal1(b._root);
	for (const auto& e : v)
		cout << e << " ";
	cout << endl;
	//输出：
	//5 20 30 40 50 70 80 90 500
	//5 20 50 70 90
	//destory：5
	//destory：20
	//destory：70
	//destory：90
	//destory：50
}



int main()
{
	//test1();
	//test2();
	test3();
	return 0;
}