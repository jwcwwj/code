#include <iostream>
#include <thread>
#include <mutex> 

using namespace std;

//单例模式
//1.恶汉
//2.对象只能被创建一次
class singleton
{
public:
	//共有的方法获取对象
	static singleton* getSingletion()
	{
		//获取已存在对象的地址
		return &_singleton;	
	}

private:
	//构造函数私有
	singleton()
	{}

	//定义一个类的静态成员
	static singleton _singleton;		//静态成员存放在静态数据区

	//只有一份
	//防止拷贝
	singleton(const singleton&) = delete;

};

//静态成员类外初始化
singleton singleton::_singleton;

//singleton::getSingletion();
//singleton g;

void test()
{
	cout << sizeof(singleton) << endl;
	//singleton::_singleton;
	singleton* ptr = singleton::getSingletion();
} 


//懒汉：第一次使用的时候创建对象
mutex mtx;	//全局锁

class singleton2
{
public:
	//共有的方法获取对象
	static singleton2* getSingleton()	//static对象只能调用static函数
	{
		//第一次检查：提高效率
		if (_sin == nullptr)
		{
			mtx.lock();
			//第一次检查：线程安全
			if (_sin == nullptr)
			{
				_sin = new singleton2;
				cout << _sin << endl;
				//第一次使用创建
				//return new singleton2;	
				//懒汉需要修改对象的内容，恶汉不需要（所以需要处理懒汉多线程，不处理会有线程安全的问题）
			}
			mtx.unlock();
		}
		return _sin;		//不是第一次创建直接返回
	}

private:
	//构造函数私有
	singleton2()
	{}

	//防止拷贝
	singleton2(const singleton2&) = delete;

	//指针成员
	static singleton2* _sin;		//构造函数之前调用，初始值为nullptr
	//程序结束时，系统自动调用它的析构函数从而释放单例对象
};

singleton2* singleton2::_sin = nullptr;

void fun2(int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout << singleton2::getSingleton() << endl;	//输出地址
	}
}

void test2()
{
	//第一次创建
	//singleton2* ptr = singleton2::getSingleton();
	//下面的直接返回对象，不创建对象
	//ptr = singleton2::getSingleton();

	//多线程
	int n;
	cin >> n;
	thread t1(fun2, n);
	thread t2(fun2, n);
	t1.join();
	t2.join();
}

int main()
{
	//test();
	test2();
	return 0;
}