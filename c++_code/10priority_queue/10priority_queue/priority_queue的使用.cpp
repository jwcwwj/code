#include <iostream>
#include <queue>
#include <functional>	//greater�㷨��ͷ�ļ�

using namespace std;

//priority_queue�ĵ���������
//greater�� > ���бȽϣ���С��
//less�� < ���бȽϣ������

//�º�����ģ��
template <class T>
struct Greater
{
	//���������غ��������
	bool operator()(const T& val1, const T& val2)
	{
		return val1 > val2;		//û��{}�ᱨ����֪��Ϊɶ
	}
};

//���	��������
void test1()
{
	priority_queue<int> q;	//���Դ���Զ������ͣ��Զ������ͱ���֧�ִ�С��ϵ�ıȽϣ��ȽϹ���
	q.push(100);
	q.push(1);
	q.push(150);
	q.push(10);
	q.push(20);

	while (!q.empty())
	{
		cout << q.top() << " ";		//�Ѷ����������ȶ��е���ֵ��Ĭ�������ֵ��
		//�����150 100 20 10 1
		q.pop();
	}

	cout << endl;
}

struct A
{
	A(int a)
		:_a(a)
	{}

	//�����
	bool operator<(const A& a) const		//����������г���
	{
		return _a < a._a;
	}

	//��С��
	bool operator>(const A& a) const
	{
		return _a > a._a;
	}

	//��Ԫ��������ֱ��������ڲ�������ʵ�֣�����Ҫ��ͬһ����������ⲿʵ��
	friend ostream& operator<<(ostream& _cout, const A& a)
	{
		_cout << a._a;
		return _cout;
	}

private:
	int _a;	
	//�Զ����Ա�ı������������� <<�������������������ķ�װ�ԺͰ�ȫ�ԣ��ѳ�Ա������Ϊ˽�еġ���ʹ����Ԫ�����ⶨ�壩
};

void test2()
{
	priority_queue<A> q;
	q.push(A(1));			//����������г���
	q.push(A(2));
	q.push(A(3));
	q.push(A(4));

	while (!q.empty())
	{
		cout << q.top() << " ";	//4 3 2 1
		q.pop();
	}

	cout << endl;
}

void test3()
{
	priority_queue<int, vector<int>, Greater<int>> q;	//ʹ���Լ�����ģ��º���
	//priority_queue<int,vector<int>,greater<int>> q;		//��С�ѽ��д���
	//greater�ṩһ�����ڱȽϣ���С�ѣ�Ĭ���ǰ���С�����Ƚϣ������ 
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

//�Զ�������	С��
void test4()
{
	//�����priority_queue�з��Զ������͵����ݣ�
	//�û���Ҫ���Զ����������ṩ> ����< ������.
	priority_queue<A, vector<A>, Greater<A>> q;
	q.push(A(1));			//����������г���
	q.push(A(2));
	q.push(A(3));
	q.push(A(4));

	while (!q.empty())
	{
		cout << q.top() << " ";	//1 2 3 4
		q.pop();
	}

	cout << endl;
}

int main()
{
	//test1();	//���	��������
	//test2();	//���	�Զ�������
	//test3();	//С��	��������
	test4();	//С��	�Զ�������

	//ʹ����ģ��º���
	//Greater<int> g;
	//bool ret = g.operator()(10, 20);
	//ret = g(10, 20);	//��д��ʽ		�º������Ǻ��������������������

	return 0;
}