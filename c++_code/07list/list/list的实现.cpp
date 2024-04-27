#include <iostream>

using namespace std;
	
//�ڵ�ģ��
template<class T>
struct __list_node
{
	__list_node(const T& val = T())		//Ĭ����0
		:_next(nullptr)
		,_prev(nullptr)
		,_data(val)
	{}

	__list_node<T>* _next;
	__list_node<T>* _prev;
	T _data;
};

//������ģ��
//���ӣ�template<int, int&, int*> l;
template<class T, class Ref, class Ptr>	
struct __list_iterator 
{
	typedef __list_node<T> Node;		//�ڵ�
	typedef __list_iterator<T, Ref, Ptr> Self;		//�Լ���������
	
	//���캯��
	__list_iterator(Node* node)			//�ڵ�ָ��
		:_node(node)
	{}

	//*iterator����ȡ���ݱ���
	Ref operator*()			//Ref = T&
	{		
		return _node->_data;
	}

	//it->_a   ��������˫Ŀ���������it�����Զ��Ƶ�����_a�������ǵ�Ŀ�����
	//()����������޷�ȷ��������ģ������ͣ���ȥ->����ı���
	Ptr operator->()		//Ptr = T*
	{
		return &_node->_data;
	}
	
	//���ص������������Ƿ��ؽڵ�
	//ǰ��++
	Self& operator++() 
	{
		_node = _node->_next;
		return *this;			//���÷���
	}
	
	//����++
	Self operator++(int)
	{
		Self tmp(*this);		//����������
		++(*this);
		return tmp;				//ֵ����
	}
	
	//ǰ��--
	Self& operator--()
	{
		_node = _node->_next;
		return *this;
	}
	
	//����--
	Self operator--(int) 
	{
		Self tmp(*this);
		--(*this);
		return tmp;
	}
	
	bool operator!=(const Self& it) 
	{
		//�жϳ�Աָ��_node�Ƿ�ָ��ͬһ���ڵ�
		return _node != it._node;
	}
	
	bool operator==(const Self& it) 
	{
		return _node == it._node;		//����Ҳ���Ը������ص�!=�����
	}

	Node* _node;		//��װ�ڵ�
};

//list��ģ��
template<class T>
class list {
	typedef __list_node<T> Node;

public:
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;

	iterator begin() 
	{
		return iterator(_head->_next);
	}
	
	iterator end() 
	{
		return iterator(_head);
	}
	
	const_iterator begin() const 
	{
		return const_iterator(_head->_next);
	}
	
	const_iterator end() const 
	{
		return const_iterator(_head);
	}
	
	//���캯������������Զ���ڵ���Ĺ��캯������ʼ��ֵΪ0
	//��һ���ڵ���Ϊend�������������������е�ֵ���൱��һ������ͷ���
	//begin������ָ��ͷ������һ���ڵ㣬end������ָ��ͷ���
	list()	
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}
	
	//���
	list(const list<T>& l1) 
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
		/*
		const_iterator it = l1.begin();
		while (it != l1.end())
		{
			push_back(*it);
			++it;
		}
		*/
		for (auto& e : l1)		//��Χfor�Ǵ�begin������������end������ 
		{		
			push_back(e);
		}
	}

	//��ֵ��������ص��ִ�д���ʹ�ͳд��
	/*
	list<T> operator=(const list<T> l1)
	{
		if (*this != l1) {
			clear();
			//const_iterator it = l1.begin();
			for (auto e : l1)
			{
				push_back(e);
			}
		}
		return *this;
	}
	*/

	//������߼�
	list<T> operator=(const list<T> l1)			//��ֵ����
	{
		swap(_head, l1._head);
		return *this;
	}

	//ֻ����end������ָ���λ�ã�ʣ�½ڵ�ȫ���ͷ�
	void clear() 
	{
		iterator it = begin();
		while (it != end()) 
		{
			//it = erase(it);
			erase(it++);
		}
	}

	iterator erase(iterator pos) 
	{
		//assert(pos != end());			//����end������ָ���λ�ò���ɾ���ı�Ҫ
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* next = cur->_next;
		delete cur;
		prev->_next = next;
		next->_prev = prev;
		return iterator(next);		//����ɾ���ڵ����һ���ڵ�ĵ�����
	}

	void insert(iterator pos, const T& val)
	{
		//iterator�Ǹ����󣬶��������нڵ�Ԫ��
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* newNode = new Node(val);

		prev->_next = newNode;
		newNode->_prev = prev;
		newNode->_next = cur;
		cur->_prev = newNode;
	}

	void push_back(const T& val) 
	{
		insert(end(), val);
	}

	void pop_back() 
	{
		erase(--end());	//����ʹ��--end() - 1��ԭ����list������֧��������ʵ�����
	}

	void push_front(const T& x) 
	{
		insert(begin(), x);
	}
	
	void pop_front() 
	{
		erase(begin());
	}
	
	~list() 
	{
		clear();		//���֮��ֻʣ������ͷ�ڵ㣬����end������ָ���λ��
		delete _head;
		_head = nullptr;
	}

private:
	Node* _head;		//��װ�ڵ�
};

void print_list(const list<int>& l1) 
{
	list<int>::const_iterator it = l1.begin();
	
	while (it != l1.end())
	{
		cout << *it << " ";
		++it;
	}
	
	cout << endl;
}

struct A
{
	A(int a = 0,int b = 0,int c = 0)
		:_a(a)
		,_b(b)
		,_c(c)
	{}

	int _a;
	int _b;
	int _c;
};

void test1()
{
	list<int> l1;
	l1.push_back(1);
	l1.push_back(1);
	l1.push_back(1);
	l1.push_back(1);
	print_list(l1);		//1 2 3 4

	cout << *(l1.end()) << endl;	//0������ͷ����ֵ��Ĭ�ϵ���0ֵ

	l1.clear();

	l1.push_front(1);		
	print_list(l1);		//1	
}

void test2()
{
	list<A> l;
	l.push_back(A());
	l.push_back(A(1,1,1));
	l.push_back(A(2,2,2));
	l.push_back(A(3,3,3));
	l.push_back(A(4,4,4));

	A* ptr = new A(1, 2, 3);
	cout << "_a = " << ptr->_a << " _b = " << ptr->_b
		<< " _c = " << ptr->_c << endl;	//_a = 1 _b = 2 _c = 3
	
	list<A>::iterator it = l.begin();
	while (it != l.end())
	{
		//cout << "_a = " << (*it)._a << " _b = " << (*it)._b
		//	<< " _c = " << (*it)._c << endl;
		//����
		//cout << "_a = " << it->_a << " _b = " << it->_b
		//		<< " _c = " << it->_c << endl;
		cout << "_a = " << it.operator->()->_a 
			<< " _b = " << it.operator->()->_b 
			<< " _c = " << it.operator->()->_c << endl;
		//��д����Ҫʹ������->��������ʶ����
		cout << "_a = " << it->_a
			<< " _b = " << it->_b
			<< " _c = " << it->_c << endl;
		it++;
	}
	//�����
	//_a = 0 _b = 0 _c = 0
	//_a = 1 _b = 1 _c = 1
	//_a = 2 _b = 2 _c = 2
	//_a = 3 _b = 3 _c = 3
	//_a = 4 _b = 4 _c = 4
}

int main()
{
	//test1();
	test2();
	system("pause");
	return 0;
}
