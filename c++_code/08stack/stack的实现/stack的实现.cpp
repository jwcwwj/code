#include <iostream>
#include <vector>

using namespace std;

//����STL�е�vectorʵ��
template <class T> 
class Stack
{
public:
	Stack()
	{}

	//����Ĳ�������O(1)�Ĳ���
	//��ջ
	void push(const T& val)
	{
		//β��
		_st.push_back(val);
	}

	//��ջ
	void pop()
	{
		//βɾ
		_st.pop_back();
	}

	//��ȡջ��Ԫ��
	T& top()
	{
		//��ȡvector��β��Ԫ��
		return _st.back();
	}

	//��ȡsize
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