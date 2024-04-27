#include <iostream>
#include <vector>
#include <stack>
#include <time.h>

using namespace std;

template <class T>
struct AVLNode
{
	AVLNode<T>* _parent;
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	T _val;	
	int _bf;	//平衡因子	右子树的高度 - 左子树的高度

	AVLNode(const T& val = T())
		:_parent(nullptr)
		,_left(nullptr)
		,_right(nullptr)
		,_val(val)
		,_bf(0)		//新创建的节点都是叶子节点，叶子节点的平衡因子都是0
	{}
};

template <class T>
class AVLTree
{
public:
	typedef AVLNode<T> Node;

	//插入		 
	bool insert(const T& val)
	{
		//二叉搜索树的插入
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}

		//调整
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->_val == val)
				return false;
			else if (cur->_val > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		//上面的循环结束之后，两种情况：
		//1.有重复的节点，插入失败，直接返回false；
		//2.没有重复的节点，parent是叶子节点，cur是nullptr；

		cur = new Node(val);
		if (parent->_val > val)
			parent->_left = cur;
		else
			parent->_right = cur;

		//AVL树是三叉链，需要连接新插入的节点的父节点（创建的新节点的左右子节点是nullptr）
		cur->_parent = parent;

		//调整：从parent开始	从下往上调整平衡因子
		//三个结束条件：一个是parent为nullptr，一个是parent的平衡因子为0，一个是发生旋转结束
		while (parent)
		{
			//更新parent的平衡因子
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			if (parent->_bf == 0)		//parent的比较短的子树高度 + 1
				//结束更新
				break;
			else if(parent->_bf == 1 || parent->_bf == -1)
				//继续向上更新，直到parent为nullptr或者parent的平衡因子是0
			{
				//平衡因子就3个值：-1 0 1
				//可能的结果：0变成-1 或 1，-1 或 1 变成 0
				cur = parent;
				parent = parent->_parent;
			}
			//旋转
			//平衡因子不是-1 0 1 这三个结果，变成-2 或着 2 要进行旋转操作
			else if (abs(parent->_bf) == 2)
			{
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					//左边的左边高
					//右旋
					RotateR(parent);		//旋转完之后parent和parnet->_parent的平衡因子都是0
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					//右边的右边高
					//左旋
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					//			parent
					//cur
					//	   subLR

					//保存subLR的bf
					Node* subLR = cur->_right;
					int bf = subLR->_bf;

					//左边的右边高
					//先左旋
					RotateL(cur);
					//后右旋
					RotateR(parent);

					//修正平衡因子
					if (bf == 1)
					{
						cur->_bf = -1;
						parent->_bf = 0;
					}
					else if(bf == -1)
					{
						cur->_bf = 0;
						parent->_bf = 1;
					}

					
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					//	parent
					//				cur
					//       subRL

					//保存subRL的bf
					Node* subRL = cur->_left;
					int bf = subRL->_bf;

					//右边的左边高
					//先右旋
					RotateR(cur);
					//再左旋
					RotateL(parent);

					//修正平衡因子
					if (bf == 1)
					{
						cur->_bf = 0;
						parent->_bf = -1;
					}
					else if(bf == -1)
					{
						cur->_bf = 1;
						parent->_bf = 0;
					}
				}

				break;
			}
		}
		return true;
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

		if(subLR)
			subLR->_parent = parent;

		if (parent == _root)
		{
			//需要更新根节点，根节点的父节点是nullptr
			_root = subL;
			subL->_parent = nullptr;
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

		//更新平衡因子
		subL->_bf = parent->_bf = 0;
	}

	//左旋
	//parent
	//			subR
	//	  subRL（不一定存在）
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//连接
		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;

		if (parent == _root)
		{
			//需要更新根节点，根节点的父节点是nullptr
			_root = subR;
			subR->_parent = nullptr;
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
		
		//更新平衡因子
		subR->_bf = parent->_bf = 0;
	}

	//中序序列
	void inorder()
	{
		_inorder(_root);
		cout << endl;
	}

	void _inorder(Node* root)
	{
		if (root)
		{
			_inorder(root->_left);
			cout << root->_val << " ";
			_inorder(root->_right);
		}
	}

	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftheight = Height(root->_left);
		int rightheight = Height(root->_right);
		return (leftheight > rightheight) ? leftheight + 1 : rightheight + 1;
	}

	bool _isBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		//查看平衡因子是否和左右子树的高度差一致
		int leftheight = Height(root->_left);
		int rightheight = Height(root->_right);
		if (rightheight - leftheight != root->_bf)
		{
			cout << "Node：" << root->_val << " bf：" << root->_bf << 
				" height gap：" << rightheight - leftheight << endl;
			return false;
		}

		return abs(root->_bf) < 2 && _isBalance(root->_left) && _isBalance(root->_right);
	}

	bool isBalance()
	{
		return _isBalance(_root);
	}


//private:
	Node* _root = nullptr;
};




//中序遍历
typedef AVLNode<int> Node;

vector<int> inorderTraversal(Node* root)
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

		vec.push_back(cur->_val);

		//访问右子树
		cur = cur->_right;        //循环访问当前节点为根的前序遍历
	}


	return vec;
}

void test()
{
	AVLTree<int> avl;
	avl.insert(5);
	avl.insert(3);
	avl.insert(1);	//右旋
	//	3
	//1		5
	avl.insert(0);
	avl.insert(2);
	//		3
	//	1		5
	//0	  2
	avl.insert(-1);		//右旋
	//			  3
	//		1		 5
	//	 0      2
	//-1
	//右旋调整
	//		1	 
	//	 0      3
	//-1      2    5
	cout << avl._root->_right->_bf << endl;		//0
	cout << avl._root->_bf << endl;				//0


	avl.insert(10);
	avl.insert(15);		//左旋
	//		1	 
	//	 0      3
	//-1      2    5
	//					10
	//						15

	//左旋之后
	//		1	 
	//	 0      3
	//-1      2    10
	//			 5	  15

	avl.insert(20); 

	avl.inorder();

	vector<int> v = inorderTraversal(avl._root);
	for (const auto& e : v)
		cout << e << " ";
	cout << endl;
	cout << avl.isBalance() << endl;
}

void test2()
{
	srand(time(nullptr));
	cout << "num:" << endl;
	int num;
	cin >> num;
	AVLTree<int> avl;
	for (int i = 0; i < num; ++i)
	{
		avl.insert(rand());
	}
	avl.inorder();
}

void test3()
{
	AVLTree<int> avl;

	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
				int num = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < num; ++i)
	{
		avl.insert(arr[i]);
	}
	avl.inorder();
	cout << avl.isBalance() << endl;
}


int main()
{
	test();
	test2();	
	test3();
	return 0;	
}