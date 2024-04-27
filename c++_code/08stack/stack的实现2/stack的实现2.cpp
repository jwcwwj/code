#include <iostream>
#include <list>

using namespace std;

//借助STL中的list实现
template <class T>
class Stack
{
public:
	Stack()
	{}

	//下面的操作都是O(1)的操作
	//入栈
	void push(const T& val)
	{
		//尾插
		_l.push_front(val);
		//_l.push_back(val);	//也可以，下面也要使用pop_back()和back()接口
	}

	//出栈
	void pop()
	{
		//尾删
		_l.pop_front();
	}

	//获取栈顶元素
	T& top()
	{
		//获取vector的尾部元素
		return _l.front();
	}

	//获取size
	size_t size() const
	{
		return _l.size();
	}

	bool empty() const
	{
		return _l.empty();
	}

private:
	list<T> _l;
};

void test()
{
	Stack<int> st;
	for (int i = 0; i < 8; ++i)
	{
		st.push(i);
	}

	while (!st.empty())
	{
		cout << st.top() << " ";	//7 6 5 4 3 2 1 0
		st.pop();
	}
	cout << endl;
}

int main()
{
	test();
	//system("pause");
	return 0;
}