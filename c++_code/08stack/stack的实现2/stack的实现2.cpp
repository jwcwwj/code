#include <iostream>
#include <list>

using namespace std;

//����STL�е�listʵ��
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
		_l.push_front(val);
		//_l.push_back(val);	//Ҳ���ԣ�����ҲҪʹ��pop_back()��back()�ӿ�
	}

	//��ջ
	void pop()
	{
		//βɾ
		_l.pop_front();
	}

	//��ȡջ��Ԫ��
	T& top()
	{
		//��ȡvector��β��Ԫ��
		return _l.front();
	}

	//��ȡsize
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