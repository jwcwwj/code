#include <iostream>
#include <vector>

using namespace std;

template <class T, class Container = vector<T>,class Compare = less<T> >
class PriorityQueue
{
public:
	//���ϵ���
	void shiftUp(int child)
	{
		int parent = (child - 1) / 2;
		//����
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
				break;		//���� return;
		}
	}

	//���µ���
	void shiftDown(int parent)
	{
		int child = parent * 2 + 1;
		//int child = 2 * parent + 1;		//��ʼ��������
		while (child < v.size())
		{
			//�����Һ������ҵ����ֵ
			//if (child + 1 < v.size() && v[child] < v[child + 1])
			if (child + 1 < v.size() && _cmp(v[child],v[child + 1]))
				//�Һ��Ӵ������Һ��ӵ�ֵ�������ӵ�ֵ
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

	//���캯��	����յ����ȼ�����
	PriorityQueue()
		:v()
	{}

	//���������乹��
	template <class Iterator>
	PriorityQueue(Iterator first, Iterator last)
		:v(first, begin)
	{
		//��v�еĽṹ�����ɶѵĽṹ
		int count = v.size();
		int root = ((count - 2) >> 1);	//�ȼ���int count = (count - 2) / 2;
		for (; root >= 0; --root)
			shiftDown(root);		//�ӵ�һ����Ҷ�ӽڵ����µ�������
	}

	void push(const T& val)
	{
		//β��
		v.push_back(val);
		//���ϵ���
		shiftUp(v.size() - 1);
	}

	void pop()
	{
		if (empty())
			return;
		//������βԪ��
		swap(v[0], v[v.size() - 1]);
		//����	swap(v.front(), v.back());
		//βɾ
		v.pop_back();
		//���µ���
		shiftDown(0);		
	}

	T& top()
	{
		return v[0];
		//return v.front();		Ҳ����
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
	//vector<T> v;		//ʹ��vector��ԭ����list��֧��������ʣ���������������ʣ�
	Compare _cmp;
};

struct A
{
	A(int a)
		:_a(a)
	{}

	bool operator<(const A& a) const		//����������г���
	{
		return _a < a._a;
	}

	int _a;
};

void test()
{
	//���˵����������º����Ͳ�֧���Զ��������ˣ���֪��Ϊɶ
	
	//�º������ŵ㣺�ڲ��޸�Դ�������£������޸Ĵ��뱾����߼�
	//�º���������STL�е�һ�����

	//PriorityQueue<A> q;		//�ڶ�������ȱʡ����vector<T>����
	PriorityQueue<int,vector<int>,greater<int>> q;

	q.push(1);			//����������г���
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

//���������乹�����	����������		��ͷ��
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