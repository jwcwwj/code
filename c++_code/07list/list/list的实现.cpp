#include <iostream>

using namespace std;
	
//节点模板
template<class T>
struct __list_node
{
	__list_node(const T& val = T())		//默认是0
		:_next(nullptr)
		,_prev(nullptr)
		,_data(val)
	{}

	__list_node<T>* _next;
	__list_node<T>* _prev;
	T _data;
};

//迭代器模板
//例子：template<int, int&, int*> l;
template<class T, class Ref, class Ptr>	
struct __list_iterator 
{
	typedef __list_node<T> Node;		//节点
	typedef __list_iterator<T, Ref, Ptr> Self;		//自己本身类型
	
	//构造函数
	__list_iterator(Node* node)			//节点指针
		:_node(node)
	{}

	//*iterator：获取数据本身
	Ref operator*()			//Ref = T&
	{		
		return _node->_data;
	}

	//it->_a   看起来是双目运算符，但it可以自动推到出来_a，所以是单目运算符
	//()里面的类型无法确定，返回模板的类型，再去->具体的变量
	Ptr operator->()		//Ptr = T*
	{
		return &_node->_data;
	}
	
	//返回迭代器本身，不是返回节点
	//前置++
	Self& operator++() 
	{
		_node = _node->_next;
		return *this;			//引用返回
	}
	
	//后置++
	Self operator++(int)
	{
		Self tmp(*this);		//拷贝迭代器
		++(*this);
		return tmp;				//值返回
	}
	
	//前置--
	Self& operator--()
	{
		_node = _node->_next;
		return *this;
	}
	
	//后置--
	Self operator--(int) 
	{
		Self tmp(*this);
		--(*this);
		return tmp;
	}
	
	bool operator!=(const Self& it) 
	{
		//判断成员指针_node是否指向同一个节点
		return _node != it._node;
	}
	
	bool operator==(const Self& it) 
	{
		return _node == it._node;		//这里也可以复用重载的!=运算符
	}

	Node* _node;		//封装节点
};

//list类模板
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
	
	//构造函数，里面调用自定义节点类的构造函数，初始化值为0
	//第一个节点作为end迭代器，不算做链表中的值，相当于一个虚拟头结点
	//begin迭代器指向头结点的下一个节点，end迭代器指向头结点
	list()	
	{
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
	}
	
	//深拷贝
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
		for (auto& e : l1)		//范围for是从begin迭代器遍历到end迭代器 
		{		
			push_back(e);
		}
	}

	//赋值运算符重载的现代写法和传统写法
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

	//深拷贝的逻辑
	list<T> operator=(const list<T> l1)			//传值拷贝
	{
		swap(_head, l1._head);
		return *this;
	}

	//只留下end迭代器指向的位置，剩下节点全部释放
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
		//assert(pos != end());			//不是end迭代器指向的位置才有删除的必要
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* next = cur->_next;
		delete cur;
		prev->_next = next;
		next->_prev = prev;
		return iterator(next);		//返回删除节点的下一个节点的迭代器
	}

	void insert(iterator pos, const T& val)
	{
		//iterator是个对象，对象里面有节点元素
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
		erase(--end());	//不能使用--end() - 1，原因是list容器不支持随机访问迭代器
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
		clear();		//清空之后只剩下虚拟头节点，就是end迭代器指向的位置
		delete _head;
		_head = nullptr;
	}

private:
	Node* _head;		//封装节点
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

	cout << *(l1.end()) << endl;	//0，虚拟头结点的值是默认的类0值

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
		//或者
		//cout << "_a = " << it->_a << " _b = " << it->_b
		//		<< " _c = " << it->_c << endl;
		cout << "_a = " << it.operator->()->_a 
			<< " _b = " << it.operator->()->_b 
			<< " _c = " << it.operator->()->_c << endl;
		//简写，不要使用两个->，编译器识别不了
		cout << "_a = " << it->_a
			<< " _b = " << it->_b
			<< " _c = " << it->_c << endl;
		it++;
	}
	//输出：
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
