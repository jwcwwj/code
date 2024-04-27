#include <iostream>
#include <list>

using namespace std;

template <class T>
class Queue
{
public:
	//用list实现

	Queue()
	{}

	void push(const T& val)
	{
		_l.push_back(val);
		//_l.push_front(val);		//也可以
	}

	void pop()
	{
		_l.pop_front();
		//_l.pop_back();
	}

	T& front()
	{
		return _l.front();
		//return _l.back();
	}

	T& back()
	{
		return _l.back();
		//retunr _l.front();
	}

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
	Queue<int> q;
	for (int i = 0; i < 5; ++i)
		q.push(i);

	while (!q.empty())
	{
		cout << q.front() << " ";		//0 1 2 3 4
		q.pop();
	}

	cout << endl;
}

int main()
{
	test();
	return 0;
}