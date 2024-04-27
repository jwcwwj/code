#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <stack>

using namespace std;

//�����������Ľڵ�
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

//��������������ͳ�Ķ���������һ�㲻����ظ���ֵ��ÿ��ֵ����Ψһ��
template <class T>
class BTree
{
public:
	typedef BNode<T> Node;

	//���캯������������
	BTree()
		:_root(nullptr)
	{}

	//�����������Ĳ���
	Node* find(const T& val)
	{
		Node* cur = _root;
		while (cur)
		{
			//ÿһ�Ĳ��������ڶ��ֲ��ҵĲ�����ƽ��ʱ�临�Ӷ���O(h)��h�����ĸ߶ȡ�
			//�������������һ������һ��ֱ�ߣ�����ʱ�临�Ӷ���O(n)��n�����Ľڵ����������Ҳ�Ǹ߶ȡ�
			if (cur->_data == val)
				return cur;
			else if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		return nullptr;		//��ʾû�ҵ�
	}

	//�����������ڵ�Ĳ��룺�������ظ���ֵ�������ظ���ֵ��ʧ��
	//����������һ�㲻����ظ���ֵ
	bool insert(const T& val)
	{
		if (_root == nullptr)
		{
			//����
			_root = new Node(val);
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
			if (cur->_data == val)
				return false;	//����ʧ��
			else if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//����
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
			cout << root->_data << " ";
			_inorder(root->_right);
		}
	}

	//�������������������ݺͽṹ
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

	//��������
	BTree(const BTree<T>& btree)
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
			cout << "destory��" << root->_data << endl;	//����deleteǰ���ֹ���ʵ���Ұָ��
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
	bool erase(const T& val)
	{
		//����
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_data == val)	//�ҵ���
				break;
			parent = cur;		//���¸��׽ڵ��λ�ã�����֮��ɾ������
			if (cur->_data > val)
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
			swap(leftRigthMost->_data, cur->_data);

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

//private:	//һ��Ҫ�����ݳ�Աд��private������Ϊ�˷�����ʾ��Ҳ���Լ���һ����ȡ����
	Node* _root;		//���ڵ�
};

//��������������������������
//����������� �� �� 
void inorderTraversal(BNode<int>* root) 
{
	if (root == NULL)
		return;

	inorderTraversal(root->_left);
	cout << root->_data << " ";
	inorderTraversal(root->_right);
}

//���룬����������
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
	//�����
	//5 20 30 40 50 70 80 90 500
	//5 20 30 40 50 70 80 90 500
	//5 20 30 40 50 70 80 90 500
}

//��������룬����������
void test2()
{
	BTree<int> b;
	srand(time(nullptr));	//���������
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

		vec.push_back(cur->_data);

		//����������
		cur = cur->_right;        //ѭ�����ʵ�ǰ�ڵ�Ϊ����ǰ�����
	}

	return vec;
}

//����ɾ������
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
	//�����
	//5 20 30 40 50 70 80 90 500
	//5 20 50 70 90
	//destory��5
	//destory��20
	//destory��70
	//destory��90
	//destory��50
}



int main()
{
	//test1();
	//test2();
	test3();
	return 0;
}