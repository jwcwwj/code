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
	int _bf;	//ƽ������	�������ĸ߶� - �������ĸ߶�

	AVLNode(const T& val = T())
		:_parent(nullptr)
		,_left(nullptr)
		,_right(nullptr)
		,_val(val)
		,_bf(0)		//�´����Ľڵ㶼��Ҷ�ӽڵ㣬Ҷ�ӽڵ��ƽ�����Ӷ���0
	{}
};

template <class T>
class AVLTree
{
public:
	typedef AVLNode<T> Node;

	//����		 
	bool insert(const T& val)
	{
		//�����������Ĳ���
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}

		//����
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
		//�����ѭ������֮�����������
		//1.���ظ��Ľڵ㣬����ʧ�ܣ�ֱ�ӷ���false��
		//2.û���ظ��Ľڵ㣬parent��Ҷ�ӽڵ㣬cur��nullptr��

		cur = new Node(val);
		if (parent->_val > val)
			parent->_left = cur;
		else
			parent->_right = cur;

		//AVL��������������Ҫ�����²���Ľڵ�ĸ��ڵ㣨�������½ڵ�������ӽڵ���nullptr��
		cur->_parent = parent;

		//��������parent��ʼ	�������ϵ���ƽ������
		//��������������һ����parentΪnullptr��һ����parent��ƽ������Ϊ0��һ���Ƿ�����ת����
		while (parent)
		{
			//����parent��ƽ������
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			if (parent->_bf == 0)		//parent�ıȽ϶̵������߶� + 1
				//��������
				break;
			else if(parent->_bf == 1 || parent->_bf == -1)
				//�������ϸ��£�ֱ��parentΪnullptr����parent��ƽ��������0
			{
				//ƽ�����Ӿ�3��ֵ��-1 0 1
				//���ܵĽ����0���-1 �� 1��-1 �� 1 ��� 0
				cur = parent;
				parent = parent->_parent;
			}
			//��ת
			//ƽ�����Ӳ���-1 0 1 ��������������-2 ���� 2 Ҫ������ת����
			else if (abs(parent->_bf) == 2)
			{
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					//��ߵ���߸�
					//����
					RotateR(parent);		//��ת��֮��parent��parnet->_parent��ƽ�����Ӷ���0
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					//�ұߵ��ұ߸�
					//����
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					//			parent
					//cur
					//	   subLR

					//����subLR��bf
					Node* subLR = cur->_right;
					int bf = subLR->_bf;

					//��ߵ��ұ߸�
					//������
					RotateL(cur);
					//������
					RotateR(parent);

					//����ƽ������
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

					//����subRL��bf
					Node* subRL = cur->_left;
					int bf = subRL->_bf;

					//�ұߵ���߸�
					//������
					RotateR(cur);
					//������
					RotateL(parent);

					//����ƽ������
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

	//����
	//			parent
	//subL
	//	   subLR����һ�����ڣ�
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//����
		subL->_right = parent;
		parent->_left = subLR;

		if(subLR)
			subLR->_parent = parent;

		if (parent == _root)
		{
			//��Ҫ���¸��ڵ㣬���ڵ�ĸ��ڵ���nullptr
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

		//����ƽ������
		subL->_bf = parent->_bf = 0;
	}

	//����
	//parent
	//			subR
	//	  subRL����һ�����ڣ�
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//����
		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;

		if (parent == _root)
		{
			//��Ҫ���¸��ڵ㣬���ڵ�ĸ��ڵ���nullptr
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
		
		//����ƽ������
		subR->_bf = parent->_bf = 0;
	}

	//��������
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

		//�鿴ƽ�������Ƿ�����������ĸ߶Ȳ�һ��
		int leftheight = Height(root->_left);
		int rightheight = Height(root->_right);
		if (rightheight - leftheight != root->_bf)
		{
			cout << "Node��" << root->_val << " bf��" << root->_bf << 
				" height gap��" << rightheight - leftheight << endl;
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




//�������
typedef AVLNode<int> Node;

vector<int> inorderTraversal(Node* root)
{
	stack<Node*> st;
	vector<int> vec;    //��������Ľڵ��ֵ��Ҫ���صģ�
	Node* cur = root;

	//��ǰ�����Ľڵ㲻Ϊ�գ�root�ڵ㲻Ϊ����Ҫ��֤������ջ��Ϊ�գ�ջ�տ�ʼΪ����Ҫȥ�ж�root����
	while (cur || !st.empty())
	{
		//����cur�������·����ֱ��Ϊ�սڵ㣬·���ϵĽڵ�ȫ����ջ��֮������ջ��Ԫ�ص�������
		while (cur)
		{
			st.push(cur);
			cur = cur->_left;
		}

		//��ȡջ��Ԫ��
		cur = st.top();
		st.pop();
		//��ջ���ó�һ���ڵ�ͱ�ʾ����ڵ���������͸��ڵ��Ѿ����������

		vec.push_back(cur->_val);

		//����������
		cur = cur->_right;        //ѭ�����ʵ�ǰ�ڵ�Ϊ����ǰ�����
	}


	return vec;
}

void test()
{
	AVLTree<int> avl;
	avl.insert(5);
	avl.insert(3);
	avl.insert(1);	//����
	//	3
	//1		5
	avl.insert(0);
	avl.insert(2);
	//		3
	//	1		5
	//0	  2
	avl.insert(-1);		//����
	//			  3
	//		1		 5
	//	 0      2
	//-1
	//��������
	//		1	 
	//	 0      3
	//-1      2    5
	cout << avl._root->_right->_bf << endl;		//0
	cout << avl._root->_bf << endl;				//0


	avl.insert(10);
	avl.insert(15);		//����
	//		1	 
	//	 0      3
	//-1      2    5
	//					10
	//						15

	//����֮��
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