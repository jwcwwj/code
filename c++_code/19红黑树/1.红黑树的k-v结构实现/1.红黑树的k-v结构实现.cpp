#include <iostream>

using namespace std;

enum COLOR
{
	BLACK,
	RED
};

template <class K,class V>
struct RBNode
{
	//typedef bool color;		STL�е�ʵ��
	RBNode<K, V>* _parent;
	RBNode<K, V>* _left;
	RBNode<K, V>* _right;

	pair<K, V> _kv;		//����
	COLOR _color;		//��ɫ

	//���캯��
	RBNode(const pair<K,V>& kv = pair<K,V>())
		:_parent(nullptr)
		,_left(nullptr)
		,_right(nullptr)
		,_kv(kv)
		,_color(RED)
	{}
};

template <class K, class V>
class RBTree
{
public:
	typedef RBNode<K, V> Node;

	RBTree()
		:_header(new Node)
	{
		//��������
		_header->_left = _header;
		_header->_right = _header;
	}

	//����
	bool insert(const pair<K,V>& kv)
	{
		//1.�������Ĳ���
		//������_header->_parent��nullptr
		if (_header->_parent == nullptr)
		{
			cout << "���ڵ����" << endl;
			//����	�������ڵ�
			Node* root = new Node(kv);

			//����
			_header->_parent = root;
			root->_parent = _header;
			_header->_left = _header->_right = root;

			//���ڵ��Ǻ�ɫ
			root->_color = BLACK;
		}

		//�Ӹ��ڵ㿪ʼ����
		Node* cur = _header->_parent;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			//��pair�е�key���бȽϣ�key�������ظ�
			if (cur->_kv.first == kv.first)
				return false;
			else if (cur->_kv.first > kv.first)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//����������Ľڵ�
		try
		{
			cur = new Node(kv);
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}

		if (parent->_kv.first > cur->_kv.first)
			parent->_left = cur;
		else
			parent->_right = cur;

		cur->_parent = parent;

		//2.�޸���ɫ���ߵ����ṹ
		//�ж��Ƿ��к�ɫ�����Ľڵ㣬��ɫ�����ͽ����޸�
		while (cur != _header->_parent && cur->_parent->_color == RED)
		{
			//	 gfather
			//parent
			//cur
			parent = cur->_parent;
			Node* gfather = parent->_parent;

			//ȷ������ڵ��λ��
			if (gfather->_left == parent)
			{
				//����Ľڵ����ұ�
				Node* uncle = gfather->_right;
				//uncle����
				if (uncle && uncle->_color == RED)
				{
					cout << "�޸���ɫ" << endl;
					//��������п��ܰѸ��ڵ����ɫ�Ӻ�ɫ�޸�Ϊ��ɫ������Ѻ�ɫ�޸�Ϊ��ɫ��������������Ӻ�ɫ�ڵ�ĸ���
					parent->_color = uncle->_color = BLACK;
					gfather->_color = RED;
					//��������
					cur = gfather;
				}
				else
				{
					cout << "��ת" << endl;
 					//�ж��Ƿ�Ϊ˫���ĳ���
					if (cur == parent->_right)
					{
						//����
						RotateL(parent);
						//����cur��parent��ָ���˻�Ϊ�����ĳ�����ֱ�������������ĳ���
						swap(cur, parent);
					}
					//���������
					//����ڵ���ڣ�������ɫΪ��
					//����ڵ㲻����
					//����Ҫ����
					RotateR(gfather);
					parent->_color = BLACK;
					gfather->_color = RED;
					break;
					//ϸ�ڣ��޸�֮ǰ���޸�֮��ĺ�ɫ�ڵ�ĸ����ǲ���ģ�ֻ�и��ĵط��п������Ӻ�ɫ�ڵ�ĸ�����
				}
			}
			else if(gfather->_right == parent)
			{
				//����Ľڵ������
				Node* uncle = gfather->_left;

				//uncle����
				if (uncle && uncle->_color == RED)
				{
					cout << "�޸���ɫ" << endl;
					//��������п��ܰѸ��ڵ����ɫ�Ӻ�ɫ�޸�Ϊ��ɫ������Ѻ�ɫ�޸�Ϊ��ɫ��������������Ӻ�ɫ�ڵ�ĸ���
					parent->_color = uncle->_color = BLACK;
					gfather->_color = RED;
					//��������
					cur = gfather;
				}
				else
				{
					cout << "��ת" << endl;
					//�ж��Ƿ�Ϊ˫���ĳ���
					if (cur == parent->_left)
					{
						//����
						RotateR(parent);
						//����cur��parent��ָ���˻�Ϊ�����ĳ�����ֱ�������������ĳ���
						swap(cur, parent);
					}
					//���������
					//����ڵ���ڣ�������ɫΪ��
					//����ڵ㲻����
					//����Ҫ����
					RotateL(gfather);
					parent->_color = BLACK;
					gfather->_color = RED;
					break;
					//ϸ�ڣ��޸�֮ǰ���޸�֮��ĺ�ɫ�ڵ�ĸ����ǲ���ģ�ֻ�и��ĵط��п������Ӻ�ɫ�ڵ�ĸ�����
				}
			}
		}

		//���ڵ����ɫ��Ϊ��ɫ
		_header->_parent->_color = BLACK;
		
		//����_header������ָ��
		_header->_left = leftMost();
		_header->_right = rightMost();
	}

	//����ڵ�
	Node* leftMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return cur;
	}

	//���ҽڵ�
	Node* rightMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_right)
		{
			cur = cur->_right;
		}
		return cur;
	}

	//�������
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

	//����
	//parent
	//			subR
	//	  subRL����һ�����ڣ�
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;

		//�ж�parent�ڵ��ǲ��Ǹ��ڵ�
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

		if (subLR)
			subLR->_parent = parent;

		//�ж�parent�ڵ��ǲ��Ǹ��ڵ�
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

	//��֤�����������������ʣ�
	//1.������ɫ
	//2.ÿ��·���ϵĺ�ɫ������ͬ
	//3.��ɫ��������
	bool isBalance()
	{
		if (_header->_parent == nullptr)
		{
			//��������Ϊ�Ǻ����	�и�����ڵ��Ǻ�ɫ��
			return true;
		}

		Node* root = _header->_parent;

		//1.������ɫ
		if (root->_color == RED)
			return false;

		//2.ÿ��·���ϵĺ�ɫ������ͬ
		//ͳ��һ��·���ϵĺ�ɫ�ڵ����
		int bCount = 0;	//��ɫ�ڵ�ĸ���
		Node* cur = root;
		while (cur)
		{
			if (cur->_color == BLACK)
				++bCount;
			cur = cur->_left;
		}

		//����ÿһ��·��
		int curBCount = 0;
		//������������ʼ�ĵ�	��ɫ�ڵ�ĸ���	��ǰ��ɫ�ĸ���	
		return _isBalance(root, bCount, curBCount);
	}

	bool _isBalance(Node* root, int& bCount, int curBCount)
	{
		//��rootΪ��ʱ��һ��·����������
		if (root == nullptr)
		{
			//�жϺ�ɫ�ڵ�ĸ����Ƿ���ͬ
			if (curBCount != bCount)
				return false;
			else
				return true;
		}

		//�жϽڵ��Ƿ�Ϊ��ɫ
		if (root->_color == BLACK)
			++curBCount;

		//�ж��Ƿ��к�ɫ�����Ľڵ�
		if (root->_parent && root->_color == RED && root->_parent->_color == RED)
		{
			cout << "Data��" << root->_kv.first << endl;
			return false;		//�к�ɫ�����Ľڵ�
		}

		_isBalance(root->_left, bCount, curBCount) && (root->_right, bCount, curBCount);
	}


private:
	Node* _header;	//ͷ���
};

void test()
{	
	RBTree<int, int> rbt;
	rbt.insert(make_pair(10, 10));
	rbt.insert(make_pair(15, 15));
	rbt.insert(make_pair(5, 5));
	rbt.insert(make_pair(2, 2));
}

void test2()
{
	RBTree<int, int> rbt;
	int n;
	cin >> n;
	for (int i = n; i > 0; --i)
	{
		rbt.insert(make_pair(i, i));
	}

	rbt.inorder();
	cout << rbt.isBalance() << endl;
}

int main()
{
	//test();
	test2();
	return 0;
}