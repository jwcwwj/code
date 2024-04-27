#include <iostream>
#include <vector>

using namespace std;

//借助STL中的vector实现
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
		_st.push_back(val);
	}

	//出栈
	void pop()
	{
		//尾删
		_st.pop_back();
	}

	//获取栈顶元素
	T& top()
	{
		//获取vector的尾部元素
		return _st.back();
	}

	//获取size
	size_t size() const
	{
		return _st.size();
	}

	bool empty() const
	{
		return _st.empty();
	}

private:
	vector<T> _st;
};

void test()
{
	Stack<int> st;
	for (int i = 0; i < 5; ++i)
	{
		st.push(i);
	}

	while (!st.empty())
	{
		cout << st.top() << " ";	//4 3 2 1 0
		st.pop();
	}
	cout << endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}