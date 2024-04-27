#include <iostream>
#include <vector>

using namespace std;

template <class T, class Container = vector<T>,class Compare = less<T> >
class PriorityQueue
{
public:
	//向上调整
	void shiftUp(int child)
	{
		int parent = (child - 1) / 2;
		//调整
		while (child > 0)
		{
			//if (v[parent] < v[child])
			if (_cmp(v[parent],v[child]))
			{
				swap(v[parent], v[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;		//或者 return;
		}
	}

	//向下调整
	void shiftDown(int parent)
	{
		int child = parent * 2 + 1;
		//int child = 2 * parent + 1;		//初始化是左孩子
		while (child < v.size())
		{
			//从左右孩子中找到最大值
			//if (child + 1 < v.size() && v[child] < v[child + 1])
			if (child + 1 < v.size() && _cmp(v[child],v[child + 1]))
				//右孩子存在且右孩子的值大于左孩子的值
				++child;
			//if (v[parent] < v[child])
			if(_cmp(v[parent],v[child]))
			{
				swap(v[parent], v[child]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
				break;
		}
	}

	//构造函数	创造空的优先级队列
	PriorityQueue()
		:v()
	{}

	//迭代器区间构造
	template <class Iterator>
	PriorityQueue(Iterator first, Iterator last)
		:v(first, begin)
	{
		//将v中的结构调整成堆的结构
		int count = v.size();
		int root = ((count - 2) >> 1);	//等价于int count = (count - 2) / 2;
		for (; root >= 0; --root)
			shiftDown(root);		//从第一个非叶子节点向下调整建堆
	}

	void push(const T& val)
	{
		//尾插
		v.push_back(val);
		//向上调整
		shiftUp(v.size() - 1);
	}

	void pop()
	{
		if (empty())
			return;
		//交换首尾元素
		swap(v[0], v[v.size() - 1]);
		//或者	swap(v.front(), v.back());
		//尾删
		v.pop_back();
		//向下调整
		shiftDown(0);		
	}

	T& top()
	{
		return v[0];
		//return v.front();		也可以
	}

	size_t size()
	{
		return v.size();
	}

	bool empty()
	{
		return v.empty();
	}

private:
	Container v;
	//vector<T> v;		//使用vector的原因是list不支持随机访问（交换就是随机访问）
	Compare _cmp;
};

struct A
{
	A(int a)
		:_a(a)
	{}

	bool operator<(const A& a) const		//匿名对象具有常性
	{
		return _a < a._a;
	}

	int _a;
};

void test()
{
	//加了第三个参数仿函数就不支持自定义类型了，不知道为啥
	
	//仿函数的优点：在不修改源码的情况下，可以修改代码本身的逻辑
	//仿函数类属于STL中的一个组件

	//PriorityQueue<A> q;		//第二个参数缺省，用vector<T>代替
	PriorityQueue<int,vector<int>,greater<int>> q;

	q.push(1);			//匿名对象具有常性
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		cout << q.top() << " ";	//1 2 3 4
		q.pop();
	}

	cout << endl;
}

//迭代器区间构造测试	测试有问题		回头看
void test1()
{
	int arr[] = { 5,2,6,7,4,3,0,1 };
	PriorityQueue<int> q(arr, arr + sizeof(arr) / sizeof(arr[0]));
	while (!q.empty())
	{
		cout << q.top() << " ";
		q.pop();
	}

	cout << endl;
}

int main()
{
	//test();
	test1();
	return 0;
}