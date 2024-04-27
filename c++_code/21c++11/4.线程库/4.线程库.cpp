#include <iostream>
#include <thread>	//�߳̿�
#include <vector>
#include <atomic>	//ԭ�ӿ�
#include <mutex>	//������

using namespace std;

void fun(int a)
{
	cout << "fun(int a)" << endl;
}

struct Fun
{
	void operator()()
	{
		cout << "Fun operator()" << endl;
	}
};

void test1()
{
	//���߳�
	//thread t();

	//1.����ָ��
	thread t1(fun, 10);		//��������һ�������Ǻ���ָ�룬����Ĳ����Ǻ����Ĳ���

	t1.joinable();	//�ж��߳��Ƿ������һ��Ҫ��join��ǰ��ʹ�ã�д�ں���һ������false�Ľ��
	//joinableд��join����һ�������ˣ���join���ʹ�ã�joinableд��join��ǰ��

	//�̵߳ȴ�	����	����߳�û�н���������һ�������Ĳ���
	t1.join();
	cout << "test()" << endl;
	//�����������̣߳�һ�������̣߳�һ����ִ��fun���������߳�

	//2.�º�������
	//���ݶ��󣬲�Ҫ��������
	Fun f;
	thread t2(f);
	t2.join();

	//3.lambda���ʽ
	thread t3([] {cout << "lambda" << endl; });
	t3.join();
}

//�߳�	ֵ�����õ�����
class A
{
public:
	void fun1(int a, int b)
	{
		cout << "fun1(int,int)" << a << b << endl;
	}
};

void fun2(int& a)
{
	a *= 2;
}

void fun3(int* ptr)
{
	*ptr *= 2;
}

void test2()
{
	A a;
	//��Ա������ʾȡ��ַ��thisָ����Ҫ��ʾ����	&a�����ص�this
	thread t1(&A::fun1,&a,10, 20);
	t1.join();

	int a2 = 1;
	thread t2(fun3, &a2);
	t2.join();
	cout << a2 << endl;

	//ref���߶������ﴴ���������ã���Ҫ���߳�ջ�д����ֲ�����
	//�������Ϊ�������ͣ���Ҫ��refת��
	thread t3(fun2, ref(a2));
	t3.join();
	cout << a2 << endl;
}

void fun4(int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << "jisajhadaa" << endl;
}

void test3()
{
	thread t1(fun4, 10000);
	//t1.join();		//����join�������������ȴ�ǰ���߳�ִ����
	t1.detach();	//���̴߳����߳��з����ȥ�������߳��γɾ�����ϵ
	cout << "test" << endl;
	for (int i = 0; i < 10000; ++i)
		cout << "hhh" << " ";
	cout << endl;
}

void test4()
{
	thread t1([] {});
	t1.detach();		//��������̷߳���������
	return;

	t1.join();
}

void test5()
{
	thread t1([] {});

	vector<int> v;
//	v.at(3) = 10;		//λ��Խ�����쳣

	t1.join();
}

//RAII˼���ʵ��
class threadManager
{
public:
	threadManager(thread& t)
		:_t(t)
	{}

	~threadManager()
	{
		if (_t.joinable())
		{
			_t.join();
		}
	}

private:
	thread& _t;
};

void test6()
{
	thread t1([] {});

	try
	{
		vector<int> v;
		v.at(3) = 10;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;	//invalid vector<T> subscript
	}

	threadManager tm(t1);	//RAII˼�룬������Դû���ͷŵ������ͨ��һ�������������������ڣ�
	//���캯����ȡ������Դ�Ĺ���Ȩ�����������ͷŶ������Դ��
	return;
}

//ԭ�����Ͳ�֧�ֿ������졢�ƶ����죨ԭ������һ���Ƕ�һ�����ݵ�д�Ĳ�����ͬ�������ݴ��
//����Դ�ģ�����޸ĵĲ���ͬһ�����������ݲ�ͬ������ԭ�Ӳ�����һ�ַ������ͷ���ֵ
//ԭ�Ӳ�����֤���ݵ�дʱ��ȫ�ģ����ݵ�ָ��ᱻ��ϡ�
//һ������ڵײ����Ƿ�Ϊ�ü���ָ��ִ�е�
//ԭ�Ӳ���������������ᱻ��ϣ���CPU����ִ�еĻ���һ��ʱ��Ƭ���������ָ��ִ���꣬�м䲻�����жϡ�
//ԭ�Ӳ����൱����С�Ĳ�����Ԫ��
atomic<int> sum(0);		//��ɴ��в���	ԭ�Ӳ���	�ͼ����Աȣ�Ч�ʱȽϸ�
//int sum = 0;
//mutex mtx;					//������	�����ͽ����ȽϺ�ʱ��
void fun5(int n)
{
	for (int i = 0; i < n; ++i)
	{
		//mtx.lock();	//��������ס������	��һ�������Ĺ��̣�������Ϊ�˱��⾺��
		sum++;
		//mtx.try_lock();		//����������Ϊ
		//mtx.unlock();	//�������ͷŶԻ�����������Ȩ
	} 
}

void test7()
{
	int n;
	cin >> n;
	thread t1(fun5, n);
	thread t2(fun5, n);
	t1.join();
	t2.join();
	//fun5(n);
	//fun5(n);
	cout << sum << endl;

	atomic<int> a1(0);
	//atomic<int> a2(a1);		//��֧�ֿ�����������ɾ���ĺ���
	atomic<int> a2(0);
	//a2 = a1;					//��֧�ָ�ֵ��������ɾ���ĺ���
}

//�����ĳ���
mutex mtx;
template <class Mtx>
class LockGuard
{
public:
	LockGuard(Mtx& mtx)
		:_mtx(mtx)
	{
		_mtx.lock();
	}

	~LockGuard()
	{
		_mtx.unlock();
	}

	//����������֤һ����ֻ�ᱻһ���������
	LockGuard(const LockGuard<Mtx>& lg) = delete;
	LockGuard& operator=(const LockGuard<Mtx>& lg) = delete;

private:
	Mtx& _mtx;			//����Ҫ��Ӧ��==���ã���Ϊ����������������ɾ����
};

void fun7()
{
	//mtx.lock();
	//����һ������������
	LockGuard<mutex> lg(mtx);	//���������ʱ�����ù��캯������������ʱ������������������
	cout << "fun7()" << endl;
	int n;
	cin >> n;		//����0ֵ���������0���������
	if (n == 0)
		return;
	//mtx.unlock();
}

void fun8()
{
	mtx.lock();
	cout << "fun8()" << endl;
	mtx.unlock();
}

void test8()
{
	thread t1(fun7);
	thread t2(fun8);

	t1.join();
	t2.join();
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	test8();
	return 0;
}