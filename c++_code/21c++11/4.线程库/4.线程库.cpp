#include <iostream>
#include <thread>	//线程库
#include <vector>
#include <atomic>	//原子库
#include <mutex>	//互斥锁

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
	//空线程
	//thread t();

	//1.函数指针
	thread t1(fun, 10);		//参数：第一个参数是函数指针，后面的参数是函数的参数

	t1.joinable();	//判断线程是否结束，一定要在join的前面使用，写在后面一定返回false的结果
	//joinable写在join后面一定结束了，和join结合使用，joinable写在join的前面

	//线程等待	阻塞	如果线程没有结束，进行一个阻塞的操作
	t1.join();
	cout << "test()" << endl;
	//创建了两个线程：一个是主线程，一个是执行fun函数的子线程

	//2.仿函数对象
	//传递对象，不要传递类名
	Fun f;
	thread t2(f);
	t2.join();

	//3.lambda表达式
	thread t3([] {cout << "lambda" << endl; });
	t3.join();
}

//线程	值和引用的区别
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
	//成员函数显示取地址，this指针需要显示传递	&a是隐藏的this
	thread t1(&A::fun1,&a,10, 20);
	t1.join();

	int a2 = 1;
	thread t2(fun3, &a2);
	t2.join();
	cout << a2 << endl;

	//ref告诉对象这里创建的是引用，不要在线程栈中创建局部变量
	//参数如果为引用类型，需要加ref转换
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
	//t1.join();		//加上join会在这阻塞，等待前面线程执行完
	t1.detach();	//把线程从主线程中分离出去，和主线程形成竞争关系
	cout << "test" << endl;
	for (int i = 0; i < 10000; ++i)
		cout << "hhh" << " ";
	cout << endl;
}

void test4()
{
	thread t1([] {});
	t1.detach();		//不加这句线程非正常结束
	return;

	t1.join();
}

void test5()
{
	thread t1([] {});

	vector<int> v;
//	v.at(3) = 10;		//位置越界抛异常

	t1.join();
}

//RAII思想的实现
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

	threadManager tm(t1);	//RAII思想，不会资源没有释放的情况（通过一个对象来管理生命周期）
	//构造函数获取对象资源的管理权，析构函数释放对象的资源。
	return;
}

//原子类型不支持拷贝构造、移动构造（原子类型一般是对一个内容的写的操作，同样的内容大多
//是资源的，如果修改的不是同一个东西，数据不同步），原子操作是一种防拷贝和防赋值
//原子操作保证数据的写时安全的，数据的指令不会被打断。
//一条语句在底层中是分为好几条指令执行的
//原子操作：这个操作不会被打断，在CPU里面执行的话在一个时间片里面会把这个指令执行完，中间不会有中断。
//原子操作相当于最小的操作单元。
atomic<int> sum(0);		//变成串行操作	原子操作	和加锁对比，效率比较高
//int sum = 0;
//mutex mtx;					//锁对象	加锁和解锁比较耗时间
void fun5(int n)
{
	for (int i = 0; i < n; ++i)
	{
		//mtx.lock();	//加锁：锁住互斥量	是一个阻塞的过程，加锁是为了避免竞争
		sum++;
		//mtx.try_lock();		//非阻塞的行为
		//mtx.unlock();	//解锁：释放对互斥量的所有权
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
	//atomic<int> a2(a1);		//不支持拷贝，它是已删除的函数
	atomic<int> a2(0);
	//a2 = a1;					//不支持赋值，它是已删除的函数
}

//死锁的场景
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

	//防拷贝，保证一把锁只会被一个对象管理
	LockGuard(const LockGuard<Mtx>& lg) = delete;
	LockGuard& operator=(const LockGuard<Mtx>& lg) = delete;

private:
	Mtx& _mtx;			//这里要是应用==引用，因为互斥锁拷贝操作是删除的
};

void fun7()
{
	//mtx.lock();
	//创建一个守卫锁对象
	LockGuard<mutex> lg(mtx);	//创建对象的时候会调用构造函数加锁，结束时候会调用析构函数解锁
	cout << "fun7()" << endl;
	int n;
	cin >> n;		//给非0值会解锁，给0会造成死锁
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